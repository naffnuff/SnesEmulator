#pragma once

#include <atomic>

#define AUDIO_BUFFER_DIAGNOSTICS false

namespace Audio {

class OutputBuffer
{
private:
    struct Node
    {
        float data = 0.f;
#if AUDIO_BUFFER_DIAGNOSTICS
        const size_t index = 0;
#endif
        std::atomic<Node*> next = nullptr;
    };

public:
    OutputBuffer(Output& output, const std::string& logName)
        : output(output, logName)
    {
        first = new Node();
        last = first;
        currentRead = first;
        currentWrite = first;
        first->next.store(first, std::memory_order_relaxed);
    }

    // assumes the read thread has been terminated
    ~OutputBuffer()
    {
        last->next.store(nullptr, std::memory_order_relaxed);
        Node* node = first;
        while (node)
        {
            Node* nextNode = node->next.load(std::memory_order_relaxed);
            delete node;
            node = nextNode;
        }
    }

private:
    void ensureSize()
    {
        // if write is about to overtake read, extend the buffer
        if (currentWrite == currentRead)
        {
            Node* extendedFirst = new Node{ first->data
#if AUDIO_BUFFER_DIAGNOSTICS
                , size
#endif
            };
            Node* extendedLast = extendedFirst;
            Node* oldNode = first;

            if (currentWrite == first)
            {
                currentWrite = extendedFirst;
            }

            for (int i = 1; i < size; ++i)
            {
                Node* nextNode = new Node{ oldNode->data
#if AUDIO_BUFFER_DIAGNOSTICS
                    , size + i
#endif
                };
                extendedLast->next.store(nextNode, std::memory_order_relaxed);
                extendedLast = nextNode;
                oldNode = oldNode->next.load(std::memory_order_relaxed);
                if (currentWrite == oldNode)
                {
                    currentWrite = extendedLast;
                }
            }

            extendedLast->next.store(first, std::memory_order_relaxed);

            // make sure the buffer extension is fully formed before being published to read

            // prevents reordering
            std::atomic_thread_fence(std::memory_order_seq_cst);

            // synchronization point
            last->next.store(extendedFirst, std::memory_order_release);

            last = extendedLast;

            size <<= 1;
        }
    }

public:
    float read()
    {
        const float value = currentRead->data;

        // synchronization point
        currentRead = currentRead->next.load(std::memory_order_acquire);

        return value;
    }

    void write(float value)
    {
        ensureSize();
        currentWrite->data = value;
        currentWrite = currentWrite->next.load(std::memory_order_relaxed);

#if AUDIO_BUFFER_DIAGNOSTICS
        const size_t outputLag = getLag();
        maxOutputLag = std::max<size_t>(maxOutputLag, outputLag);

        if (lastDebugOutputCounter++ == 100000)
        {
            output.debug("Current buffer size ", size);
            output.debug("Current ouput lag ", outputLag);
            output.debug("Max output lag ", maxOutputLag);
            lastDebugOutputCounter = 0;
        }
    }

    size_t getLag() const
    {
        const size_t readIndex = currentRead->index;
        const size_t writeIndex = currentWrite->index;

        if (readIndex < writeIndex)
        {
            return writeIndex - readIndex;
        }
        else
        {
            return size + writeIndex - readIndex;
        }
#endif
    }

private:
    Output output;

    Node* first = nullptr;
    Node* last = nullptr;
    Node* currentRead = nullptr;
    Node* currentWrite = nullptr;

    size_t size = 1;

#if AUDIO_BUFFER_DIAGNOSTICS
    int lastDebugOutputCounter = 0;
    size_t maxOutputLag = 0;
#endif
};

}