#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif

int_bool delete_hcursor(HCURSOR hcursor);


//HCURSOR CreateAlphaCursor(oswindow window, const ::image * pimage, int xHotSpot, int yHotSpot);


#ifdef MACOS

using HCURSOR = void *; // NSCursor

void set_cursor_image(void * pimage, int xHotSpot, int yHotSpot);

#endif

//HCURSOR load_default_cursor(e_cursor ecursor);

namespace draw2d
{

   cursor::cursor()
   {

      m_bDefaultCursor = false;

#if defined(WINDOWS_DESKTOP) || defined(MACOS)

      m_hcursor = nullptr;

#endif

   }


   bool cursor::to(::draw2d::graphics_pointer & pgraphics, const ::point & point)
   {

      pgraphics->set_alpha_mode(::draw2d::alpha_mode_blend);

      return pgraphics->draw(point - m_szHotspotOffset, m_pimage->get_size(), m_pimage->g(), nullptr);

   }


   bool cursor::set_current(::user::interaction * pinteraction, ::aura::session * psession)
   {

      sync_lock sl(psession->mutex());

//#if defined(MACOS) || defined(WINDOWS_DESKTOP)
//
//      HCURSOR hcursor = get_HCURSOR(pinteraction);
//
//      if (hcursor == nullptr)
//      {
//
//         return false;
//
//      }
//
//      if (!::SetCursor(hcursor))
//      {
//
//         return false;
//
//      }
//
//#elif defined(_UWP)
//      #if defined(_UWP)

//#else

      if(::is_null(pinteraction))
      {

         return false;

      }

      HCURSOR hcursor = get_HCURSOR(pinteraction);

      if(hcursor == NULL_HCURSOR)
      {

         return false;

      }

      if (System.m_bImaging)
      {

         if (!System.imaging().window_set_mouse_cursor(pinteraction->get_handle(), hcursor))
         {

            return false;

         }

      }

      return true;

   }


   bool cursor::reset(::user::interaction * pinteraction, ::aura::session * psession)
   {

      sync_lock sl(psession->mutex());

      if(::is_null(pinteraction))
      {

         return false;

      }

      System.imaging().window_set_mouse_cursor(pinteraction->get_handle(), 0);

      return true;

   }

#ifdef WINDOWS_DESKTOP

   bool cursor::initialize_system_default()
   {

      LPCTSTR psz;

      if (m_ecursor == cursor_arrow)
      {

         psz = IDC_ARROW;

      }
      else if (m_ecursor == cursor_size_top || m_ecursor == cursor_size_bottom)
      {

         psz = IDC_SIZENS;

      }
      else if (m_ecursor == cursor_size_left || m_ecursor == cursor_size_right)
      {

         psz = IDC_SIZEWE;

      }
      else if (m_ecursor == cursor_size_top_left || m_ecursor == cursor_size_bottom_right)
      {

         psz = IDC_SIZENWSE;

      }
      else if (m_ecursor == cursor_size_top_right || m_ecursor == cursor_size_bottom_left)
      {

         psz = IDC_SIZENESW;

      }
      else if (m_ecursor == cursor_text_select)
      {

         psz = IDC_IBEAM;

      }
      else if (m_ecursor == cursor_hand)
      {

         psz = IDC_HAND;

      }
      else if (m_ecursor == cursor_none)
      {

         return false;

      }
      else
      {

         psz = IDC_ARROW;

      }

      HCURSOR hcursor = ::LoadCursor(nullptr, psz);

      if (hcursor == nullptr)
      {

         return false;

      }

      m_hcursor = hcursor;

      m_bDefaultCursor = true;

      return true;

   }


#else


   bool cursor::initialize_system_default()
   {

      return true;

   }


#endif


   HCURSOR cursor::get_HCURSOR(::user::interaction * pinteraction)
   {

      if(m_hcursor == NULL_HCURSOR || m_bDefaultCursor)
      {

//#ifdef LINUX
//
//         if(::is_null(pinteraction))
//         {
//
//            return HNULL;
//
//         }
//
//#ifdef RASPBIAN
//
//         m_hcursor = HNULL;
//
//#else

  //       m_hcursor = ::CreateAlphaCursor(pinteraction->get_handle(), m_pimage,m_szHotspotOffset.cx,m_szHotspotOffset->cy);

//#endif
//
//#else

         if (::is_ok(m_pimage))
         {

            auto& imaging = System.imaging();

            // SCAFFOLD comment?!.... first parameter (oswindow) is not used in windows (but at other OS(es))...
            HCURSOR hcursor = imaging.CreateAlphaCursor(pinteraction->get_handle(), m_pimage,m_szHotspotOffset.cx,m_szHotspotOffset.cy);

            if (!hcursor)
            {

               hcursor = imaging.load_default_cursor(m_ecursor);

            }

            if (hcursor)
            {

               if (m_hcursor)
               {


                  ::delete_hcursor(m_hcursor);

               }

               m_hcursor = hcursor;

               m_bDefaultCursor = false;

            }

         }
         else if(!m_bDefaultCursor)
         {

            m_hcursor = System.imaging().load_default_cursor(m_ecursor);

         }

//#endif

      }

      return m_hcursor;

   }


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



