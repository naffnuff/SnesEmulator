using Microsoft.Win32;
using System.Runtime.InteropServices;
using System;
using Common;

namespace CPU
{
    namespace AddressMode
    {

        // Absolute
        // addr
        public abstract class Absolute<Operator> : Instruction3Byte<Operator> where Operator : IOperator
        {
            public override int InvokeOperator(Operator o, Byte lowByte, Byte highByte)
            {
                MemoryAccess access = state.GetMemoryAccess(lowByte, highByte);
                return o.Invoke(state, access);
            }

            public override string ToString(Operator o)
            {
                return o.ToString() + " $" + OperandToString();
            }
        };
    }
}
