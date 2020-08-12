#include "framework.h"



string get_sys_temp_path()
{

   return ::dir::path(getenv("HOME"), ".ca2", "time");

}
