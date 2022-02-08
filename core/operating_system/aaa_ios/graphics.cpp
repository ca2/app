#include "framework.h"



bool mm1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const ::string & psz);


bool ios1_get_file_image(unsigned int * pcr, int cx, int cy, int iScan, const ::string & psz)
{

   static ::mutex * pmutex = nullptr;

   if(pmutex == nullptr)
   {

      pmutex = new ::mutex();

   }

   synchronous_lock synchronouslock(pmutex);


   return mm1_get_file_image(pcr, cx, cy, iScan, psz);


}


bool ios_get_file_image(::image * pimage, const ::string & psz)
{

   if(!ios1_get_file_image(pimage->get_data(), pimage->width(), pimage->height(), pimage->scan_size(), psz))
   {

      return false;

   }

   return true;

}

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



int_bool delete_hcursor(HCURSOR h)
{
   
   return 1;
   
}







namespace draw2d
{


   CLASS_DECL_CORE string default_font_name()
   {
   
      return "ArialMT";
   
   }


} // namespace draw2d
