#include "framework.h"


namespace user
{


   split_view::split_view()
   {

      m_flagNonClient -= non_client_background;

   }


   split_view::~split_view()
   {

   }


   void split_view::install_message_routing(::channel * pchannel)
   {

      split_layout::install_message_routing(pchannel);
      impact::install_message_routing(pchannel);

      IGUI_MSG_LINK(WM_CREATE, pchannel, this, &split_view::_001OnCreate);

      //IGUI_MSG_LINK(WM_SIZE, pchannel, this, &split_view::_001OnSize);
      //IGUI_MSG_LINK(WM_SHOWWINDOW, pchannel, this, &split_view::_001OnShowWindow);

   }



   void split_view::assert_valid() const
   {
      impact::assert_valid();
   }

   void split_view::dump(dump_context & dumpcontext) const
   {
      impact::dump(dumpcontext);
   }

   void split_view::_001OnCreate(::message::message * pmessage)
   {

      SCAST_PTR(::message::create, pcreate, pmessage);

      pcreate->previous();

      if (!(m_ewindowflag & window_flag_window_created))
      {

         create_split_impact();

      }

   }


   bool split_view::create_split_impact()
   {


      bool bOk = true;

      try
      {

         on_create_split_impact();

      }
      catch (...)
      {

         bOk = false;

         string strMessage;
#if defined(APPLEOS) || defined(LINUX) || defined(ANDROID)
         strMessage.Format("split_view::on_create_impact failed to create views for split view %s", typeid(this).name());
#else
         strMessage.Format("split_view::on_create_impact failed to create views for split view %s", typeid(this).raw_name());
#endif

         message_box_timeout(strMessage, nullptr, 10_s, message_box_icon_exclamation);

      }

      for (index i = 0; i < get_pane_count(); i++)
      {

         auto pholder = get_pane_holder(i);

         if (pholder.is_set())
         {

            pholder->set_need_layout();

         }

      }

      //set_need_layout();

      return bOk;

   }


   void split_view::update(::update * pupdate)
   {

   }


   void split_view::_001OnSize(::message::message * pmessage)
   {
      SCAST_PTR(::message::size, psize, pmessage);
      psize->previous();
      //on_layout(::draw2d::graphics_pointer & pgraphics);
   }


   bool split_view::pre_create_window(::user::create_struct& cs)
   {
      
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;

      return impact::pre_create_window(cs);

   }


   void split_view::on_create_split_impact()
   {

      Application.on_create_split_view(this);

   }


   void split_view::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      UNREFERENCED_PARAMETER(pgraphics);

   }

   void split_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_layout::_001OnDraw(pgraphics);


//      i32 i;

      //::rect rect;

      //COLORREF cr = ARGB(190, 92, 92, 80);

      //for(i = 0; i < get_pane_count(); i++)
      //{
      //
      //   CalcPaneRect(i, &rect);

      //   // Top
      //   pgraphics->fill_rect(
      //      rect.left,
      //      rect.top,
      //      rect.width(),
      //      m_cyBorder,
      //      cr);

      //   // Right
      //   pgraphics->fill_rect(
      //      rect.right - m_cxBorder,
      //      rect.top,
      //      m_cxBorder,
      //      rect.height(),
      //      cr);

      //   // Bottom
      //   pgraphics->fill_rect(
      //      rect.left,
      //      rect.bottom - m_cyBorder,
      //      rect.width(),
      //      m_cyBorder,
      //      cr);

      //   // Left
      //   pgraphics->fill_rect(
      //      rect.left,
      //      rect.top,
      //      m_cxBorder,
      //      rect.height(),
      //      cr);

      //}

   }


   void split_view::_001OnShowWindow(::message::message * pmessage)
   {
      SCAST_PTR(::message::show_window, pshowwindow, pmessage);
      pshowwindow->previous();
      //on_layout(::draw2d::graphics_pointer & pgraphics);
   }


} // namespace user




