using Common;

namespace CPU.AddressMode
{
    public interface IOperator
    {
        void Invoke(IState state, MemoryAccess access);
    }
}