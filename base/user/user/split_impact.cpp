#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "base/user/user/_component.h"
#endif
#include "split_impact.h"
#include "split_pane.h"
#include "aura/message/user.h"
#include "base/platform/application.h"


namespace user
{


   split_impact::split_impact()
   {

      m_flagNonClient -= e_non_client_background;

   }


   split_impact::~split_impact()
   {

   }


   void split_impact::install_message_routing(::channel * pchannel)
   {

      split_layout::install_message_routing(pchannel);
      impact::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &split_impact::on_message_create);

      //MESSAGE_LINK(e_message_size, pchannel, this, &split_impact::on_message_size);
      //MESSAGE_LINK(e_message_show_window, pchannel, this, &split_impact::on_message_show_window);

   }



   void split_impact::assert_ok() const
   {
      impact::assert_ok();
   }

   void split_impact::dump(dump_context & dumpcontext) const
   {
      impact::dump(dumpcontext);
   }

   void split_impact::on_message_create(::message::message * pmessage)
   {

      __pointer(::message::create) pcreate(pmessage);

      pcreate->previous();

      if (!(m_ewindowflag & e_window_flag_window_created))
      {

         create_split_impact();

      }

   }


   bool split_impact::create_split_impact()
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
#if defined(__APPLE__) || defined(LINUX) || defined(ANDROID) || defined(FREEBSD)
         strMessage.format("split_impact::on_create_impact failed to create views for split impact %s", typeid(this).name());
#else
         strMessage.format("split_impact::on_create_impact failed to create views for split impact %s", typeid(this).raw_name());
#endif

         //message_box(strMessage, nullptr, e_message_box_icon_exclamation)->get_object(10_s);

         output_error_message(strMessage);

      }

      for (index i = 0; i < get_pane_count(); i++)
      {

         auto pholder = get_pane_holder(i);

         if (pholder)
         {

            pholder->set_need_layout();

         }

      }

      //set_need_layout();

      return bOk;

   }


   void split_impact::handle(::topic * ptopic, ::context * pcontext)
   {

   }


   void split_impact::on_message_size(::message::message * pmessage)
   {
      __pointer(::message::size) psize(pmessage);
      psize->previous();
      //on_layout(pgraphics);
   }


   bool split_impact::pre_create_window(::user::system * pusersystem)
   {

#ifdef WINDOWS_DESKTOP



#endif

      return impact::pre_create_window(pusersystem);

   }


   void split_impact::on_create_split_impact()
   {

      auto papp = get_app();

      papp->on_create_split_impact(this);

   }


   void split_impact::_001OnNcDraw(::draw2d::graphics_pointer & pgraphics)
   {

      __UNREFERENCED_PARAMETER(pgraphics);

   }

   void split_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::user::split_layout::_001OnDraw(pgraphics);


//      i32 i;

      //::rectangle_i32 rectangle;

      //::color32_t color32 = argb(190, 92, 92, 80);

      //for(i = 0; i < get_pane_count(); i++)
      //{
      //
      //   CalcPaneRect(i, &rectangle);

      //   // Top
      //   pgraphics->fill_rectangle(
      //      rectangle.left,
      //      rectangle.top,
      //      rectangle.width(),
      //      m_cyBorder,
      //      color32);

      //   // Right
      //   pgraphics->fill_rectangle(
      //      rectangle.right - m_cxBorder,
      //      rectangle.top,
      //      m_cxBorder,
      //      rectangle.height(),
      //      color32);

      //   // Bottom
      //   pgraphics->fill_rectangle(
      //      rectangle.left,
      //      rectangle.bottom - m_cyBorder,
      //      rectangle.width(),
      //      m_cyBorder,
      //      color32);

      //   // Left
      //   pgraphics->fill_rectangle(
      //      rectangle.left,
      //      rectangle.top,
      //      m_cxBorder,
      //      rectangle.height(),
      //      color32);

      //}

   }


   void split_impact::on_message_show_window(::message::message * pmessage)
   {
      __pointer(::message::show_window) pshowwindow(pmessage);
      pshowwindow->previous();
      //on_layout(pgraphics);
   }


   bool split_impact::on_prepare_impact_data(::user::impact_data* pimpactdata)
   {

      //if (!add_tab(pimpactdata->m_atom, pimpactdata->m_atomTitle))
      //{

      //   return false;

      //}

      split_pane * ppane = m_splitpanecompositea[pimpactdata->m_atom.index()];

      if (ppane != nullptr)
      {

         if (!pimpactdata->m_pplaceholder)
         {

            auto pplaceholder = get_new_place_holder(ppane->m_rectangleClient);

            pimpactdata->m_pplaceholder = pplaceholder;

         }

         ppane->m_pplaceholder = pimpactdata->m_pplaceholder;

         ppane->m_pimpactdata = pimpactdata;

      }

      return true;

   }



} // namespace user




