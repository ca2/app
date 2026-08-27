#include "platform.h"
#include "graphics.h"
#include "graphics_extension.h"
#include "graphics_pointer.h"


namespace draw2d
{


   graphics_extension::graphics_extension()
   {

   }


   graphics_extension::~graphics_extension()
   {

   }


   void graphics_extension::text_out(::draw2d::graphics_pointer & pdraw2dgraphics, ::i32 x, ::i32 y, const ::scoped_string & scopedstr, ::f64_size & s)
   {

      s = pdraw2dgraphics->get_text_extent(scopedstr);

      return pdraw2dgraphics->text_out(x, y, scopedstr);

      //return ::TextOutU((HDC)pdraw2dgraphics->get_os_data(), x, y, pcsz, iCount);


   }


   void graphics_extension::get_text_extent(::draw2d::graphics_pointer & pdraw2dgraphics, const ::scoped_string & scopedstr, ::f64_size_array & sizea)
   {


      throw ::exception(todo);
      /*string str(pcsz);

      character_count iLen = str.length();
      sizea.allocate(iLen);
      if(iLen > 0)
      {
         sizea[0] = 0;
      }
      for(::i32 i = 1; i < iLen; i++)
      {
         ::GetTextExtentPoint32U(
         (HDC)pdraw2dgraphics->get_os_data(),
         str,
         i,
         &sizea[i]);
      }*/

   }


   //void graphics_extension::get_text_extent(::draw2d::graphics_pointer& pdraw2dgraphics, const ::scoped_string & scopedstr, i32_size & size)
   //{

   //   //synchronous_lock ml(&user_synchronization());

   //   /*string str(pwsz);

   //   if(pdraw2dgraphics == nullptr)
   //      return;
   //   ::GetTextExtentPoint32U(
   //      (HDC)pdraw2dgraphics->get_os_data(),
   //      (const ::string &) str,
   //      str.length(),
   //      &size);*/

   //   size = pdraw2dgraphics->get_text_extent(scopedstr);


   //}


   void graphics_extension::get_text_extent(::draw2d::graphics_pointer& pdraw2dgraphics, const ::scoped_string & scopedstr, ::f64_size & size)
   {

      /*::GetTextExtentPoint32U(
         (HDC)pdraw2dgraphics->get_os_data(),
         pcsz,

         iCount,
         &size);*/

      size = pdraw2dgraphics->get_text_extent(scopedstr);

   }


} // namespace draw2d



