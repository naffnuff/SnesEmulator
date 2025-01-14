namespace Common
{
    public interface IInstruction
    {
        string? ToString();
        string OpcodeToString();
        void ApplyBreakpoints();
        int Execute();
        int Size();
    }

    public abstract class InstructionBase : IInstruction
    {
        protected IState state;

        public abstract string OpcodeToString();
        public abstract int Execute();
        public abstract int Size();

        protected string OperandToString()
        {
            string ss = "";
            for (int i = Size() - 1; i > 0; --i)
            {
                state.PrintProgramByte(i, ss);
            }
            return ss;
        }

        public void ApplyBreakpoints()
        {
            for (int i = 0; i < Size(); ++i)
            {
                state.ApplyBreakpoint(i);
            }
        }

        protected Byte ApplyByte()
        {
            return state.ApplyProgramByte();
        }
    }

    public abstract class Instruction1Byte<Operator> : InstructionBase
    {
        public abstract int InvokeOperator(Operator o);

        protected int ApplyOperand(Operator o)
        {
            ApplyByte();
            int cycles = InvokeOperator(o);
            return cycles;
        }

        public override int Size()
        {
            return 1;
        }
    }

    public abstract class Instruction2Byte<Operator> : InstructionBase
    {
        public abstract int InvokeOperator(Operator o, Byte lowByte);

        protected int ApplyOperand(Operator o)
        {
            ApplyByte();
            int cycles = InvokeOperator(o, ApplyByte());
            return cycles;
        }

        public override int Size()
        {
            return 2;
        }
    }

    public abstract class Instruction3Byte<Operator> : InstructionBase
    {
        public abstract int InvokeOperator(Operator o, Byte lowByte, Byte highByte);

        protected int ApplyOperand(Operator o)
        {
            ApplyByte();
            int cycles = InvokeOperator(o, ApplyByte(), ApplyByte());
            return cycles;
        }

        public override int Size()
        {
            return 3;
        }
    }

    public abstract class Instruction4Byte<Operator> : InstructionBase
    {
        public abstract int InvokeOperator(Operator o, Byte lowByte, Byte highByte, Byte bankByte);

        protected int ApplyOperand(Operator o)
        {
            ApplyByte();
            int cycles = InvokeOperator(o, ApplyByte(), ApplyByte(), ApplyByte());
            return cycles;
        }

        public override int Size()
        {
            return 4;
        }
    }
}
