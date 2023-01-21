#include "framework.h"
#include "main_window.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"
#include "aura/windowing/window.h"
#include "aura/platform/application.h"


inline bool is_custom_size(enum_display edisplay)
{

   return edisplay == e_display_restored
         || edisplay == e_display_restore
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

      m_bEnableDragClient = true;

      m_bEnableDragResize = true;

      m_bClickDefaultMouseHandling = true;

      m_bHoverDefaultMouseHandling = true;

      m_bExtendOnParentIfClientOnly = true;

      //m_ewindowflag |= e_window_flag_desktop_window;

   }


   main_window::~main_window()
   {

   }


   void main_window::install_message_routing(::channel * pchannel)
   {

      ::user::frame::install_message_routing(pchannel);

      //install_click_default_mouse_handling(pchannel);
      
      //install_hover_default_mouse_handling(pchannel);

   }


   void main_window::on_create_user_interaction()
   {

      defer_set_icon();

      add_user_item(__new(::item(::e_element_close_button, ::id_close_app)));
      add_user_item(__new(::item(::e_element_maximize_button, ::id_maximize)));
      add_user_item(__new(::item(::e_element_minimize_button, ::id_minimize)));

   }


   void main_window::input_client_rectangle(RECTANGLE_I32 & rectangle)
   {
      
      get_client_rect(rectangle);
   
      if(is_top_level() && ::is_set(m_pwindow))
      {
         
         rectangle.top += (::i32) m_pwindow->get_top_margin();
         
      }
      
   }


   void main_window::initial_frame_placement()
   {


#if defined(SANDBOXED_PLATFORM)


#else

      if (!m_rectangleInitialRateOrSize.is_empty())
      {

         place_rate_or_size(m_rectangleInitialRateOrSize);

         display(e_display_restored);

      }
      else
      {

         WindowDataLoadWindowRect();

      }

#endif

      auto edisplay = const_layout().sketch().display();

      if(is_custom_size(edisplay))
      {

         auto sizeMinimum = frame::get_window_minimum_size();

         auto rectangleClient = const_layout().state(e_layout_sketch).client_rect();

         auto sizeFrame = rectangleClient.size();

         if(sizeFrame.cx < sizeMinimum.cx || sizeFrame.cy < sizeMinimum.cy)
         {

            ::rectangle_f64 rectangleRateOrSize = { 0.05, 0.05, 0.4, 0.4 };

            place_rate_or_size(rectangleRateOrSize);

            display(e_display_restored);

         }

      }

   }


   ::index main_window::get_preferred_restore(RECTANGLE_I32 & rectanglePreferredRestore)
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
      
      create_host();

      //if (!bOk)
      //{

      //   return false;

      //}

      //return ::success;

   }


} // namespace user



