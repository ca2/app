#include "framework.h"


namespace user
{


   layout::layout()
   {

      m_ewindowflag += window_flag_enable | window_flag_graphical;

      m_bFillParent = true;

      m_sizeSpan.cx = 1;

      m_sizeSpan.cy = 1;

      m_sizeWeight.cx = 1.0;

      m_sizeWeight.cy = 1.0;

      ui_state().m_edisplay3 = display_none;

      request_state().m_edisplay3 = display_none;

      m_elayoutexperience = layout_experience_none;

   }


   layout::~layout()
   {


   }


   void layout::on_layout(::draw2d::graphics_pointer & pgraphics)
   {


   }


   class control_descriptor& layout::descriptor()
   {

      return *m_pdescriptor;

   }


   const class control_descriptor& layout::descriptor() const
   {

      return *m_pdescriptor;

   }


   bool layout::window_is_full_screen_enabled()
   {

      return true;

   }


   void layout::set_placement(const ::rect & rectParam)
   {

      ::rect rect(rectParam);

      rect.deflate(m_rectPadding);

      place(rect);

   }


   ::point layout::get_parent_accumulated_scroll() const
   {

      return ::point();

   }


   void layout::on_add_layout(::user::layout * playout)
   {

   }


#undef INFO_LAYOUT_DISPLAY


   bool layout::display(::edisplay edisplay, ::eactivation eactivation)
   {

      bool bToggle = false;

      if (edisplay == display_normal)
      {

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display display_normal");

         #endif

      }
      else if (edisplay == display_hide)
      {

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display display_hide");

         #endif

      }
      else if (edisplay == display_default)
      {

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display display_default");

         #endif

      }
      else if (edisplay == display_zoomed)
      {

         output_debug_string("display_zoomed");

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display display_zoomed");

         #endif

      }
      else if (edisplay == display_iconic)
      {

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display display_iconic");

         #endif

      }
      else if (edisplay == display_full_screen)
      {

         output_debug_string("display_full_screen");

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display display_full_screen");

         #endif

      }
      else
      {

         #ifdef INFO_LAYOUT_DISPLAY

         INFO("layout::display (unknown)");

         #endif

      }

#if DEBUG_LEVEL > 0

      if (edisplay == display_normal)
      {

         if (m_pdescriptor.is_set() && m_pdescriptor->m_puserinteractionParent == nullptr)
         {

            INFO("Parent is Null. Display Request -> normal");

         }

      }
      else if (edisplay == display_hide)
      {

         if (m_pdescriptor.is_set() && m_pdescriptor->m_puserinteractionParent == nullptr)
         {

            INFO("Parent is Null. Display Request -> hide");

         }

      }

#endif

      if (edisplay == display_default)
      {

         auto edisplayCurrent = m_stateRequest2.m_edisplay3;

         auto edisplayStored = m_windowrect.m_edisplay;

         auto edisplayPrevious = m_windowrect.m_edisplayPrevious;

         if (edisplayCurrent == display_undefined)
         {

            edisplay = display_normal;

         }
         else if (::is_screen_visible(edisplayCurrent))
         {

            edisplay = edisplayCurrent;

         }
         else if (::is_screen_visible(edisplayStored))
         {

            edisplay = edisplayStored;

         }
         else if (::is_screen_visible(edisplayPrevious))
         {

            edisplay = edisplayPrevious;

         }
         else
         {

            edisplay = ::display_normal;

         }

         set_display_request(edisplay);

      }
      else
      {

         set_display_request(edisplay);

      }

      request_state().m_eactivation = eactivation;

      if (!window_do_display())
      {

         return false;

      }

      m_bRequestReady = true;

      return true;

   }


#undef INFO_LAYOUT_DISPLAY


   bool layout::window_do_display()
   {

      return true;

   }


   void layout::set_reposition(bool bSetThis)
   {

   }


   void layout::_set_reposition(bool bSetThis)
   {

      UNREFERENCED_PARAMETER(bSetThis);

   }


   void layout::set_need_redraw(bool bAscendants)
   {


   }


   void layout::post_redraw(bool bAscendants)
   {


   }


   bool layout::window_move(i32 x, i32 y)
   {

      request_state().m_point = {x, y};

      set_need_redraw();

      return true;

   }


   bool layout::is_this_visible()
   {

      return m_ewindowflag & window_flag_is_window && ::is_visible(display_state());

   }


   string layout::get_class_style(string strClass)
   {

      if (strClass.is_empty())
      {

         return "";

      }

      if (strClass.find(',') < 0)
      {

         strClass.trim();

         string strStyle;

         if (m_pdescriptor->m_puserinteractionParent != NULL)
         {

            strStyle += m_pdescriptor->m_puserinteractionParent->get_class_style(strClass);

         }

         if (m_pdescriptor->m_playout != NULL && m_pdescriptor->m_puserinteractionParent != m_pdescriptor->m_playout)
         {

            strStyle += m_pdescriptor->m_playout->get_class_style(strClass);

         }

         if (m_pdescriptor.is_set())
         {

            strStyle += m_pdescriptor->m_mapClassStyle[strClass];

         }

         return strStyle;

      }

      string_array straClass;

      straClass.add_tokens(strClass, ",", false);

      string strStyle;

      for (auto & str : straClass)
      {

         strStyle +=  get_class_style(str);

         if (strStyle.has_char())
         {

            strStyle += ";";

         }

      }

      return strStyle;

   }


   bool layout::set_class_style(string strClass, string strStyle)
   {

      if (strClass.find(",") >= 0)
      {

         return false;

      }

      m_pdescriptor->m_mapClassStyle[strClass] = strStyle;

      return true;

   }


   void layout::get_window_rect(RECT* prect) const
   {

      ::set_rect_point_size(prect, ui_state().m_pointScreen, ui_state().m_size);

   }


   string layout::get_full_style()
   {

      string strStyle = get_class_style(m_pdescriptor->m_strClass);

      if (strStyle.has_char())
      {

         strStyle += ";";


      }

      strStyle += m_pdescriptor->m_strStyle;

      return strStyle;

   }


   void layout::sync_style()
   {

      string strStyle = get_full_style();

      load_style(strStyle);

   }


   void layout::load_style(string strStyle)
   {

      string_array stra;

      stra.explode(";", strStyle);

      for (auto & str : stra)
      {

         string_array straItem;

         straItem.explode(":", str);

         if (straItem.get_size() == 2)
         {

            string strKey = straItem[0];

            strKey.trim();

            strKey.make_lower();

            string strValue = straItem[1];

            strValue.trim();

            strValue.make_lower();

            m_pdescriptor->m_setStyle[strKey] = strValue;

            if (strKey.compare_ci("padding") == 0)
            {

               m_rectPadding.left = atoi(strValue);
               m_rectPadding.top = atoi(strValue);
               m_rectPadding.right = atoi(strValue);
               m_rectPadding.bottom = atoi(strValue);


            }
            else if (strKey.compare_ci("cell-padding") == 0)
            {

               m_iCellPadding = atoi(strValue);

            }


         }

      }

   }


   bool layout::is_this_screen_visible() const
   {

      if(display_request() == display_iconic)
      {

         return ::is_screen_visible(window_display());

      }

      return ::is_screen_visible(display_request());

   }


   void layout::set_initial_dim(const ::point & p, const ::size & s)
   {

      set_dim(p, s);

      m_stateRequest2.m_pointScreen = p;

      m_state2 = m_stateRequest2;
      m_stateWindow3 = m_stateRequest2;
      m_stateProcess2 = m_stateRequest2;

   }


} // namespace user



