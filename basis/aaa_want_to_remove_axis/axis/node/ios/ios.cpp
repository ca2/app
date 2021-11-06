#include "framework.h"


namespace ios
{

   i32 function()
   {
      return 0;
   }


   ::u32 GetTempPath(string & str)
   {
      //return ::GetTempPathW(MAX_PATH * 8,wtostring(str,MAX_PATH * 8));
      
      str = "/::payload/tmp/ca2/";
      
      return str.get_length();
      
   }


} // namespace ios



