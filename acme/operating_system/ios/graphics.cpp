#include "framework.h"



bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const ::scoped_string & scopedstr);


bool ios1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const ::scoped_string & scopedstr)
{

   static ::pointer< ::mutex > pmutex = nullptr;

   if(pmutex == nullptr)
   {

      pmutex = memory_new ::pointer < ::mutex >();

   }

   synchronous_lock synchronouslock(pmutex);

   return mm1_get_file_image(pcr, cx, cy, iScan, psz);

}


//
//bool ios_get_file_image(::image * pimage, const ::scoped_string & scopedstr)
//{
//
//   if(!ios1_get_file_image(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), psz))
//   {
//
//      return false;
//
//   }
//
//   return true;
//
//}

//
//
//
//bool os_init_imaging()
//{
//
//   return true;
//
//}
//
//
//void os_term_imaging()
//{
//
//}
//
//
//


//
//int_bool delete_hcursor(HCURSOR h)
//{
//   
//   return 1;
//   
//}
//






namespace draw2d
{


   CLASS_DECL_ACME string default_font_name()
   {
   
      return "ArialMT";
   
   }


} // namespace draw2d
