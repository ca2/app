#include "framework.h"
#include "text_file.h"


namespace file
{


   text_file::text_file()
   {

   }


   text_file::~text_file()
   {

   }


   void text_file::write_string(const ::scoped_string & scopedstr)

   {

      UNREFERENCED_PARAMETER(scopedstr);


   }


   bool text_file::read_string(string & str)
   {
      UNREFERENCED_PARAMETER(str);
      return false;
   }


   ::u32 text_file::read_full_string(string & str)
   {
      ::u32 uRead;
      ::u32 uTotal = 0;
      string strLine;
      while((uRead = read_string(strLine)) > 0)
      {
         str += strLine;
      }
      return uTotal;
   }


} // namespace file



