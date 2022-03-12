// created by Camilo <3CamiloSasukeThomasBorregaardSoerensen  - Honoring Thomas Borregaard S�rensen MY ONLY LORD
// recreated by Camilo 2021-02-01 20:19
#include "framework.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/cursor.h"
#include "cursor.h"



namespace windowing
{


   cursor::cursor()
   {

      //load_system_default_cursor_hint();

   }


   cursor::~cursor()
   {


   }


   void cursor::set_cursor(enum_cursor ecursor)
   {

      m_ecursor = ecursor;

      //return ::success;

   }


//   void cursor::load_system_default_cursor_hint()
//   {
//
//      m_bLoadSystemDefaultCursorHint = true;
//
//      return ::success;
//
//   }

   
   void cursor::set_image(const ::image * pimage, ::i32 xHotspot, ::i32 yHotspot)
   {

      m_pimage = pimage;

      m_szHotspotOffset.cx = xHotspot;

      m_szHotspotOffset.cy = yHotspot;
      
      //return ::success;

   }

   
   void cursor::set_file_path(const ::file::path & path)
   {

      m_path = path;

      //return ::success;

   }


   ::file::path cursor::get_file_path() const
   {

      return "";

   }


   void cursor::_create_os_cursor()
   {

      throw ::interface_only();

      //throw ::interface_only();

   }


   //virtual void defer_create_os_cursor();


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



