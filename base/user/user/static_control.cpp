#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_user.h"
#endif


namespace user
{


   static_control::static_control()
   {

      m_etype = type_text;

      m_bLButtonDown = false;

      m_bHover = false;

   }


   static_control::~static_control()
   {

      DestroyWindow();

   }



   bool static_control::create_window(::user::interaction * puiParent,id id)
   {

      return ::user::interaction::create_window(puiParent, id);

   }


   ::draw2d::font_pointer static_control::get_font(style * pstyle, enum_element eelement, estate estate) const
   {

      if (pstyle)
      {

         if (pstyle->m_pfontStill)
         {

            return pstyle->m_pfontStill;

         }

         if (pstyle->m_pfont)
         {

            return pstyle->m_pfont;

         }

      }

      return nullptr;

   }


   void static_control::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &static_control::_001OnCreate);
      MESSAGE_LINK(e_message_left_button_down, pchannel, this, &static_control::_001OnLButtonDown);
      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &static_control::_001OnLButtonUp);
      MESSAGE_LINK(e_message_mouse_move, pchannel, this, &static_control::_001OnMouseLeave);
      MESSAGE_LINK(e_message_mouse_leave, pchannel, this, &static_control::_001OnMouseMove);

   }

   void static_control::_001OnCreate(::message::message * pmessage)
   {

      descriptor().set_control_type(e_control_type_static);

      pmessage->previous();

      if (pmessage->m_bRet)
         return;

   }

   void static_control::_001OnLButtonDown(::message::message * pmessage)
   {

//      SCAST_PTR(::message::mouse, pmouse, pmessage);
      UNREFERENCED_PARAMETER(pmessage);

      m_bLButtonDown = true;

   }


   void static_control::_001OnLButtonUp(::message::message * pmessage)
   {

//      SCAST_PTR(::message::mouse, pmouse, pmessage);
      UNREFERENCED_PARAMETER(pmessage);

      if (m_bLButtonDown)
      {

         m_bLButtonDown = false;

         ::user::control_event ev;
         ev.m_puie = this;
         ev.m_eevent = ::user::e_event_button_clicked;
         ev.m_actioncontext = ::e_source_user;

         on_control_event(&ev);

      }


   }

   void static_control::_001OnMouseMove(::message::message * pmessage)
   {

//      SCAST_PTR(::message::mouse, pmouse, pmessage);
      UNREFERENCED_PARAMETER(pmessage);
   }


   void static_control::_001OnMouseLeave(::message::message * pmessage)
   {

//      SCAST_PTR(::message::mouse, pleave, pmessage);
      UNREFERENCED_PARAMETER(pmessage);

      m_bLButtonDown = false;

   }

   void static_control::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {



      color32_t crText = ARGB(255, 0, 0, 0);

      if(m_bHover)
      {

         auto psession = Session;

         auto point = psession->get_cursor_pos();

         ::rect rectWindow;

         get_window_rect(rectWindow);

         if(rectWindow.contains(point))
         {

            crText = ::color(255, 0, 0, 0);

         }
         else
         {

            crText = ::color(255, 0, 0, 0);

         }

      }
      else
      {

         crText = ::color(255, 0, 0, 0);

      }

      pgraphics->set_text_color(crText);

      pgraphics->set_font(this, ::user::e_element_none);

      pgraphics->text_out(0, 0, get_window_text());

   }


   bool static_control::OnChildNotify(::message::base * pbase)
   {

#ifdef WINDOWS_DESKTOP

      if (pbase->m_id != WM_DRAWITEM)
         return ::user::interaction::OnChildNotify(pbase);

#ifdef WINDOWS_DESKTOP

//      DrawItem((LPDRAWITEMSTRUCT)pbase->m_lparam);

#endif

#endif

      return true;

   }


   void static_control::static_set_icon(::draw2d::icon * picon)
   {

      if(picon == nullptr)
         return;

      m_etype = type_icon;

      m_picon = picon;

   }


   ::draw2d::icon * static_control::static_get_icon()
   {

      return m_etype == type_icon ? m_picon : nullptr;

   }


#ifdef WINDOWS_DESKTOP


   HENHMETAFILE static_control::SetEnhMetaFile(HENHMETAFILE hMetaFile)
   {

      //ASSERT(is_window());

      //return (HENHMETAFILE)send_message( STM_SETIMAGE, IMAGE_ENHMETAFILE, (LPARAM)hMetaFile);

      return nullptr;

   }


   HENHMETAFILE static_control::GetEnhMetaFile()
   {

      //ASSERT(is_window());

      //return (HENHMETAFILE)send_message( STM_GETIMAGE, IMAGE_ENHMETAFILE, 0L);

      return nullptr;

   }


#endif


   void static_control::static_set_bitmap(::draw2d::bitmap * pbitmap)
   {


      if(pbitmap == nullptr)
         return;

      m_etype = type_icon;

      m_pbitmap = pbitmap;


   }


   ::draw2d::bitmap * static_control::static_get_bitmap()
   {

      return m_etype == type_bitmap ? m_pbitmap : nullptr;

   }


   void static_control::static_set_cursor(::draw2d::cursor * pcursor)
   {

      if(pcursor == nullptr)
         return;

      m_etype = type_cursor;

      m_pcursor = pcursor;

   }


   ::draw2d::cursor *  static_control::static_get_cursor()
   {

      return m_etype == type_cursor ? m_pcursor : nullptr;

   }

   ::user::static_control::enum_type static_control::get_type()
   {

      return m_etype;

   }


} // namespace user







