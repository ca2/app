#include "framework.h"
#include "graphics.h"
#include "graphics_extension.h"
////#include "acme/exception/exception.h"


namespace draw2d
{


   graphics_extension::graphics_extension()
   {

   }


   graphics_extension::~graphics_extension()
   {

   }


   void graphics_extension::text_out(::draw2d::graphics_pointer & pgraphics, i32 x, i32 y, const ::scoped_string & scopedstr, size_f64 & s)
   {

      s = pgraphics->get_text_extent(scopedstr);

      return pgraphics->text_out(x, y, scopedstr);

      //return ::TextOutU((HDC)pgraphics->get_os_data(), x, y, pcsz, iCount);


   }


   void graphics_extension::get_text_extent(::draw2d::graphics_pointer & pgraphics, const ::scoped_string & scopedstr, ::size_f64_array & sizea)
   {


      throw ::exception(todo);
      /*string str(pcsz);

      strsize iLen = str.length();
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


   //void graphics_extension::get_text_extent(::draw2d::graphics_pointer& pgraphics, const ::scoped_string & scopedstr, size_i32 & size)
   //{

   //   //synchronous_lock ml(&user_synchronization());

   //   /*string str(pwsz);

   //   if(pgraphics == nullptr)
   //      return;
   //   ::GetTextExtentPoint32U(
   //      (HDC)pgraphics->get_os_data(),
   //      (const ::string &) str,
   //      str.length(),
   //      &size);*/

   //   size = pgraphics->get_text_extent(scopedstr);


   //}


   void graphics_extension::get_text_extent(::draw2d::graphics_pointer& pgraphics, const ::scoped_string & scopedstr, size_f64 & size)
   {

      /*::GetTextExtentPoint32U(
         (HDC)pgraphics->get_os_data(),
         pcsz,

         iCount,
         &size);*/

      size = pgraphics->get_text_extent(scopedstr);

   }


} // namespace draw2d



