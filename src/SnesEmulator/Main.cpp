#include <iostream>
#include <bitset>
#include <thread>
#include <filesystem>

#include "Output.h"
#include "Emulator.h"
#include "VideoRenderer.h"

int main(int, char**)
{
    Output::System outputSystem("logconfig.txt");
    Output output(outputSystem, "main");

    while (true)
    {
        try
        {
            Rom rom(output);

            {
                std::string pickedTitle;
                {
                    Output::Lock lock(output);
                    output.printLine(lock, "Welcome to Naffnuff's SNES emulator!");
                    std::vector<std::string> titles;
                    while (titles.empty())
                    {
                        for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator("."))
                        {
                            std::string extension = entry.path().extension().string();
                            if (entry.is_regular_file() && (extension == ".smc" || extension == ".sfc"))
                            {
                                std::string filename = entry.path().filename().string();
                                titles.push_back(filename);
                                output.printLine(lock, titles.size(), ". ", filename);
                            }
                        }
                        if (titles.empty())
                        {
                            output.printLine(lock, "Put some ROM images in the same folder as the application file and press enter!");
                            int dummy = std::getchar();
                            dummy = dummy;
                        }
                    }
                    output.printLine(lock);
                    while (pickedTitle.empty())
                    {
                        output.printLine(lock, "Enter command or game index (h for help): ");
                        std::string command = "43";
                        //std::getline(std::cin, command);
                        try
                        {
                            if (command.empty())
                            {
                            }
                            else if (command == "h")
                            {
                                output.printLine(lock, "Keyboard controls:");
                                output.printLine(lock, "Toggle fullscreen: Space");
                                output.printLine(lock, "Up: W");
                                output.printLine(lock, "Left: A");
                                output.printLine(lock, "Down: S");
                                output.printLine(lock, "Right: D");
                                output.printLine(lock, "A: L");
                                output.printLine(lock, "B: K");
                                output.printLine(lock, "X: I");
                                output.printLine(lock, "Y: J");
                                output.printLine(lock, "L: U");
                                output.printLine(lock, "R: O");
                                output.printLine(lock, "Start: ,");
                                output.printLine(lock, "Select: .");
                                output.printLine(lock, "Or connect a controller!");
                            }
                            else
                            {
                                int inputValue = stoi(command);
                                --inputValue;
                                if (inputValue >= 0 && inputValue < titles.size())
                                {
                                    pickedTitle = titles[inputValue];
                                }
                            }
                        }
                        catch (const std::exception& e)
                        {
                            output.error("Bad input: ", e.what());
                        }
                    }
                }
                rom.loadFromFile(pickedTitle);
            }

            Emulator emulator(output, rom);
            emulator.initialize();
            emulator.run();
        }
        catch (const std::exception& e)
        {
            output.error("Failure: ", e.what());
            output.error("Press [RETURN] to restart");
            std::getchar();
        }
    }

    output.info("Success");
    std::getchar();
    return 0;
}
