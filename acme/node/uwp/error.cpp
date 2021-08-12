#include "framework.h"
//#include "uwp.h"


string get_error_message(::u32 dwError)
{

   return get_last_error_message(dwError);

}
