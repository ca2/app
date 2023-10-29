#include "framework.h"
#include "main_window.h"
#include "acme/constant/id.h"
#include "acme/constant/message.h"
#include "acme/handler/item.h"
#include "acme/user/user/tool.h"
#include "aura/windowing/window.h"
#include "aura/platform/application.h"


inline bool is_custom_size(enum_display edisplay)
{

   return edisplay == e_display_normal
         || edisplay == e_display_compact
         || edisplay == e_display_broad
         || edisplay == e_display_minimal
         || edisplay == e_display_fixed_size
         || edisplay == e_display_center;

}


namespace user
{


   main_window::main_window()
   {

      m_flagNonClient -= e_non_client_focus_rect;

      m_ewindowflag += ::e_window_flag_miniaturizable;

      m_bEnableDragClient = true;

      m_bEnableDragResize = true;

      m_bEnableDefaultControlBox = true;

      m_bDefaultClickHandling = true;

      m_bDefaultMouseHoverHandling = true;

      m_bDefaultParentMouseMessageHandling = true;

      m_bExtendOnParentIfOnlyClient = true;

      //m_ewindowflag |= e_window_flag_desktop_window;

   }


   main_window::~main_window()
   {

   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::frame::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_create, pchannel, this, &main_window::on_message_create);

      //install_click_default_mouse_handling(pchannel);
      
      //install_hover_default_mouse_handling(pchannel);

   }


   //void main_window::on_create_user_interaction()
   //{

   //   defer_set_icon();

   //   if (m_bEnableDefaultControlBox && should_show_platform_control_box())
   //   {

   //      {

   //         auto pitemClose = __new(::item(::e_element_close_button, ::id_close_app));

   //         tool().add_item(pitemClose);

   //         user_item(pitemClose)->m_ezorder = e_zorder_front;

   //      }

   //      {

   //         auto pitemMaximize = __new(::item(::e_element_maximize_button, ::id_maximize));

   //         tool().add_item(pitemMaximize);

   //         user_item(pitemMaximize)->m_ezorder = e_zorder_front;

   //      }

   //      {

   //         auto pitemMinimize = __new(::item(::e_element_minimize_button, ::id_minimize));

   //         tool().add_item(pitemMinimize);

   //         user_item(pitemMinimize)->m_ezorder = e_zorder_front;
   //         
   //      }

   //   }

   //}


   void main_window::on_message_create(::message::message * pmessage)
   {

      defer_set_icon();

      if (m_bEnableDefaultControlBox && should_show_platform_control_box())
      {

         {

            auto pitemClose = __new(::item(::e_element_close_button, ::id_close_app));

            tool().add_item(pitemClose);

            user_item(pitemClose)->m_ezorder = e_zorder_front;

         }

         {

            auto pitemMaximize = __new(::item(::e_element_maximize_button, ::id_maximize));

            tool().add_item(pitemMaximize);

            user_item(pitemMaximize)->m_ezorder = e_zorder_front;

         }

         {

            auto pitemMinimize = __new(::item(::e_element_minimize_button, ::id_minimize));

            tool().add_item(pitemMinimize);

            user_item(pitemMinimize)->m_ezorder = e_zorder_front;
            
         }

      }

   }


   void main_window::input_client_rectangle(::rectangle_i32 & rectangle, enum_layout elayout)
   {
      
      rectangle = this->rectangle(elayout);
   
      if(is_top_level() && ::is_set(m_pwindow))
      {
         
         rectangle.top() += (::i32) m_pwindow->get_top_margin();
         
      }
      
   }


   void main_window::initial_frame_placement()
   {


#if defined(SANDBOXED_PLATFORM)


#else

      if (!m_rectangleInitialRateOrSize.is_empty())
      {

         place_rate_or_size(m_rectangleInitialRateOrSize);

         display(e_display_normal);

      }
      else
      {

         WindowDataLoadWindowRectangle();

      }

#endif

      auto edisplay = const_layout().sketch().display();

      if(is_custom_size(edisplay))
      {

         auto sizeMinimum = frame::get_window_minimum_size();

         auto rectangleX = const_layout().state(e_layout_sketch).raw_rectangle();

         auto sizeFrame = rectangleX.size();

         if(sizeFrame.cx() < sizeMinimum.cx() || sizeFrame.cy() < sizeMinimum.cy())
         {

            ::rectangle_f64 rectangleRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

            place_rate_or_size(rectangleRateOrSize);

            display(e_display_normal);

         }

      }

   }


   ::index main_window::get_preferred_restore(::rectangle_i32 & rectanglePreferredRestore)
   {

      //return calculate_window_rectangle_in_main_monitor(prectanglePreferredRestore, m_rectangleInitialRateOrSize);

      return -1;

   }


   void main_window::create_main_window()
   {

      //::rectangle_i32 rectangleWindow;

      //bool bInitialFramePosition = _001FancyInitialFramePlacement(rectangleWindow, m_rectangleInitialRateOrSize);

      //place(rectangleWindow);

      initial_frame_placement();

      ::pointer<::aura::application>papp = get_app();

      string strCaption = papp->get_app_user_friendly_task_bar_name();

      set_window_text(strCaption);

      //bool bOk = 
      
      create_host(e_parallelization_synchronous);

      //if (!bOk)
      //{

      //   return false;

      //}

      //return ::success;

   }



   bool main_window::should_redraw_on_mouse_activate()
   {

      return false;

   }


   bool main_window::should_redraw_on_mouse_hover()
   {

      return false;

   }


} // namespace user



