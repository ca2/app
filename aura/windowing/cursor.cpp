// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"


namespace windowing
{


   cursor::cursor()
   {

      load_system_default_cursor_hint();

   }


   cursor::~cursor()
   {


   }


   ::e_status cursor::load_system_default_cursor_hint()
   {

      m_bLoadSystemDefaultCursorHint = true;

      return ::success;

   }

   
   ::e_status cursor::create_from_image(const ::image * pimage, ::i32 xHotspot, ::i32 yHotspot)
   {

      __throw(error_interface_only);
      
      return error_interface_only;

   }

   
   ::e_status cursor::load_default_cursor(enum_cursor ecursor)
   {

      __throw(error_interface_only);

      return error_interface_only;

   }


   ::file::path cursor::get_file_path() const
   {

      return "";

   }


   //__pointer(cursor) cursor::set_cursor_file(const ::file::path& pathParam, bool bFromCache)
   //{

   //   auto path = pathParam;

   //   auto psystem = m_psystem->m_paurasystem;

   //   if (psystem->m_bImaging)
   //   {

   //      //fork([this, pcursor, path, bFromCache]()
   //      {

   //         pcursor->initialize_system_default();

   //         auto psession = get_session();

   //         auto puser = psession->user();

   //         auto pwindowing = puser->windowing();

   //         if (pwindowing->load_cursor(pcursor, path, true, bFromCache))
   //         {

   //            //return pcursor;

   //         }
   //         else
   //         {


   //            {

   //               //return pcursor;

   //            }

   //            //return nullptr;

   //         }

   //      }//);

   //   }

   //   return pcursor;

   //}


} // namespace windowing



