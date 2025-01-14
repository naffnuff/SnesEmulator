
namespace Common
{
    public interface IState
    {
        void ApplyBreakpoint(int i);

        byte ApplyProgramByte();
        global::CPU.AddressMode.MemoryAccess GetMemoryAccess(byte lowByte, byte highByte);
        void PrintProgramByte(int i, string ss);
    }
}