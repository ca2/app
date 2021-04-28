#include "framework.h"
#include "aura/operating_system.h"
#include "aura/user/_user.h"
//#ifndef WINDOWS
//#include "acme/os/cross/windows/_windows.h"
//#endif


int_bool delete_hcursor(hcursor hcursor);


//hcursor CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot);


#ifdef MACOS

using hcursor = void *; // NSCursor

void set_cursor_image(void * pimage, int xHotSpot, int yHotSpot);

#endif

//hcursor load_default_cursor(enum_cursor ecursor);

namespace draw2d
{

   cursor::cursor()
   {

      m_bDefaultCursor = false;

//#if defined(WINDOWS_DESKTOP) || defined(MACOS)
//
//      m_hcursor = nullptr;
//
//#endif

   }


   cursor::~cursor()
   {


   }


   //bool cursor::to(::draw2d::graphics_pointer & pgraphics, const ::point_i32 & point)
   //{


   //}







   ::e_status cursor::finalize()
   {

      m_pimage.release();

      m_pimageCursor.release();

      auto estatus = ::matter::finalize();

      return estatus;

   }


   ::windowing::cursor * cursor::get_cursor()
   {

      return m_pcursor;

   }


#ifdef WINDOWS_DESKTOP

   bool cursor::initialize_system_default()
   {

      LPCTSTR psz;

      if (m_ecursor == e_cursor_arrow)
      {

         psz = IDC_ARROW;

      }
      else if (m_ecursor == e_cursor_size_top || m_ecursor == e_cursor_size_bottom)
      {

         psz = IDC_SIZENS;

      }
      else if (m_ecursor == e_cursor_size_left || m_ecursor == e_cursor_size_right)
      {

         psz = IDC_SIZEWE;

      }
      else if (m_ecursor == e_cursor_size_top_left || m_ecursor == e_cursor_size_bottom_right)
      {

         psz = IDC_SIZENWSE;

      }
      else if (m_ecursor == e_cursor_size_top_right || m_ecursor == e_cursor_size_bottom_left)
      {

         psz = IDC_SIZENESW;

      }
      else if (m_ecursor == e_cursor_text_select)
      {

         psz = IDC_IBEAM;

      }
      else if (m_ecursor == e_cursor_hand)
      {

         psz = IDC_HAND;

      }
      else if (m_ecursor == e_cursor_none)
      {

         return false;

      }
      else
      {

         psz = IDC_ARROW;

      }

      hcursor hcursor = ::LoadCursor(nullptr, psz);

      if (hcursor == nullptr)
      {

         return false;

      }

      //m_hcursor = hcursor;

      m_bDefaultCursor = true;

      return true;

   }


#else


   bool cursor::initialize_system_default()
   {

      return true;

   }


#endif



   void cursor_alloc(::object * pobject,cursor_pointer & pcursor,int xHotspot,int yHotspot)
   {

      pobject->__construct(pcursor);

      pcursor->m_szHotspotOffset.cx = xHotspot;

      pcursor->m_szHotspotOffset.cy = yHotspot;

   }


   image_pointer cursor_get_image(cursor * pcursor)
   {

      return pcursor->m_pimage;

   }


} // namespace draw2d



