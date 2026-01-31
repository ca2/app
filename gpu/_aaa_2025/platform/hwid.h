#pragma once
//#include <string>
//#include <memory.h>

namespace hwid
{
    class CPUVendorID
    {
    private:
        struct
        {
            unsigned int ebx;
            unsigned int edx;
            unsigned int ecx;
        } regs;
    public:
        CPUVendorID();
        ::string toString() const
        {
            char str[12];
            ::memory_copy(str, &regs, sizeof(str)); //this way avoid all kinds of UB
            return ::string(str, 12);
        }
    };

    ::string makeHWID();
}
