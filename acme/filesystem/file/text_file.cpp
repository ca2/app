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

      __UNREFERENCED_PARAMETER(scopedstr);


   }


   bool text_file::read_string(string & str)
   {
      __UNREFERENCED_PARAMETER(str);
      return false;
   }


   unsigned int text_file::read_full_string(string & str)
   {
      unsigned int uRead;
      unsigned int uTotal = 0;
      string strLine;
      while((uRead = read_string(strLine)) > 0)
      {
         str += strLine;
      }
      return uTotal;
   }


} // namespace file



