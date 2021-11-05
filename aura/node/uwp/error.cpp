#include "framework.h"
//#include "universal_windows.h"


string get_error_message(::u32 dwError)
{

   return get_last_error_message(dwError);

}
