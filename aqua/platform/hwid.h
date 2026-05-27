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
            ::u32 ebx;
            ::u32 edx;
            ::u32 ecx;
        } regs;
    public:
        CPUVendorID();
        ::string toString() const
        {
            ::i8 str[12];
            ::memory_copy(str, &regs, sizeof(str)); //this way avoid all kinds of UB
            return ::string(str, 12);
        }
    };

    ::string makeHWID();
}
