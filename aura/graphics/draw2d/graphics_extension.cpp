#include "framework.h"


namespace draw2d
{


   graphics_extension::graphics_extension()
   {

   }


   graphics_extension::~graphics_extension()
   {

   }


   bool graphics_extension::text_out(::draw2d::graphics_pointer & pgraphics, i32 x, i32 y, const char * pcsz, strsize iCount, size_i32 & s)

   {
      s = pgraphics->GetTextExtent(string(pcsz,iCount));

      return pgraphics->text_out(x, y, string(pcsz, iCount));

      //return ::TextOutU((HDC)pgraphics->get_os_data(), x, y, pcsz, iCount);


   }


   void graphics_extension::GetTextExtent(::draw2d::graphics_pointer & pgraphics, const char * pcsz, ::size_array & sizea)
   {


      __throw(todo);
      /*string str(pcsz);

      strsize iLen = str.get_length();
      sizea.allocate(iLen);
      if(iLen > 0)
      {
         sizea[0] = 0;
      }
      for(i32 i = 1; i < iLen; i++)
      {
         ::GetTextExtentPoint32U(
         (HDC)pgraphics->get_os_data(),
         str,
         i,
         &sizea[i]);
      }*/

   }


   void graphics_extension::GetTextExtent(::draw2d::graphics_pointer& pgraphics, const char * psz, size_i32 & size)
   {

      //synchronous_lock ml(&user_mutex());

      /*string str(pwsz);

      if(pgraphics == nullptr)
         return;
      ::GetTextExtentPoint32U(
         (HDC)pgraphics->get_os_data(),
         (const char *) str,
         str.get_length(),
         &size);*/

      size = pgraphics->GetTextExtent(psz);


   }


   void graphics_extension::GetTextExtent(::draw2d::graphics_pointer& pgraphics, const char * pcsz, strsize iCount, size_i32 & size)
   {

      /*::GetTextExtentPoint32U(
         (HDC)pgraphics->get_os_data(),
         pcsz,

         iCount,
         &size);*/

      size = pgraphics->GetTextExtent(string(pcsz, iCount));

   }


} // namespace draw2d



