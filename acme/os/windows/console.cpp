#include "framework.h"
#include "acme/operating_system.h"
#include "acme/os/console.h"


void std_out_buffer::write(const void * pdata, memsize nCount)
{

#ifdef WINDOWS

   DWORD dw;

   WriteFile(GetStdHandle(STD_OUTPUT_HANDLE), pdata, (::u32)nCount, &dw, nullptr);

#else

   fwrite(pdata, nCount, 1, stdout);


#endif

}
