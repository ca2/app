#pragma once

#if defined(MCHECK) || defined(_VLD) || defined(__MCRTDBG)

#error "Either MCHECK, _VLD, __MCRTDBG or MEMDLEAK were defined"

#endif

