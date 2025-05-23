#include "framework.h"
#include "interaction_layout.h"


namespace user
{


   interaction_layout::interaction_layout()
   {

      m_iStateCount = sizeof(m_statea) / sizeof(m_statea[0]);

      //m_pstate = nullptr;

      m_bFillParent = true;

      m_sizeSpan.cx() = 1;

      m_sizeSpan.cy() = 1;

      m_sizeWeight.cx() = 1.0;

      m_sizeWeight.cy() = 1.0;

      m_elayoutexperience = e_layout_experience_none;

      //sketch() = e_display_none;
      //window() = e_display_none;
      //design() = e_display_none;

   }


   interaction_layout::~interaction_layout()
   {

      destroy_state();

   }


   void interaction_layout::create_state(int iStateCount)
   {

      if (iStateCount == m_iStateCount)
      {

         return;

      }

      destroy_state();

      if (iStateCount == e_layout_count_child || iStateCount == e_layout_count_owner)
      {

         m_iStateCount = iStateCount;

         //m_pstate = ___new window_state[m_iStateCount];

         //for (int iState = 0; iState < m_iStateCount; iState++)
         //{

         //   m_pstate[iState].set_interaction_layout(this);

         //}

      }

      design() = e_display_none;

      sketch() = e_display_none;

   }


   void interaction_layout::destroy_state()
   {

//      synchronous_lock synchronouslock(this->synchronization());

      //if (::is_set(m_pstate))
      //{

      //   delete m_pstate;

      //}

      //m_pstate = nullptr;

   }



   //void interaction_layout::on_layout(::draw2d::graphics_pointer & pgraphics)
   //{


   //}





   //void interaction_layout::set_placement(const ::int_rectangle & rectangleParam)
   //{

   //   ::int_rectangle rectangle(rectangleParam);

   //   rectangle.deflate(m_rectanglePadding);

   //   request() = rectangle;

   //}


   ::int_point interaction_layout::get_parent_accumulated_scroll(enum_layout elayout) const
   {

      return ::int_point();

   }


   void interaction_layout::on_add_layout(::user::interaction_layout * playout)
   {

   }


   //void interaction_layout::move_to(int x, int y)
   //{
   //
   //   layout().sketch().m_point.set(x, y);
   //
   //   set_pending_request();
   //
   //}


   //void interaction_layout::move_to(const int_point & point)
   //{

   //   move_to(point.x(), point.y());

   //}


   //void interaction_layout::set_size(int cx, int cy)
   //{
   //
   //   layout().sketch().m_size.set(cx, cy);
   //
   //   set_pending_request();
   //
   //}


   //void interaction_layout::set_size(const ::int_size& size)
   //{

   //   set_size(size.cx(), size.cy());

   //}


   //void interaction_layout::set_dim(const ::int_point& point, const ::int_size& size)
   //{
   //
   //   layout().sketch().m_point = point;
   //
   //   layout().sketch().m_size = size;
   //
   //   set_pending_request();
   //
   //}


   //void interaction_layout::place(const ::int_rectangle& rectangle)
   //{
   //
   //   set_dim(rectangle.origin(), rectangle.size());
   //
   //}


   //void interaction_layout::set_dim(int x, int y, int cx, int cy)
   //{
   //
   //   set_dim(::int_point(x, y), ::int_size(cx, cy));
   //
   //}


   //zorder interaction_layout::order(enum_layout elayout)
   //{
   //
   //   return state(elayout).zorder();
   //
   //}


#undef INFO_LAYOUT_DISPLAY





   //bool interaction_layout::layout().sketch().is_visible() const
   //{
   //
   //   return ::is_visible(layout().sketch().display());
   //
   //}


//   bool interaction_layout::display(::e_display edisplay, const ::user::activation & useractivation)
//   {
//
//      bool bToggle = false;
//
//      if (edisplay == e_display_normal)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display e_display_normal";
//
//         #endif
//
//      }
//      else if (edisplay == e_display_hide)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display e_display_hide";
//
//         #endif
//
//      }
//      else if (edisplay == e_display_default)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display e_display_default";
//
//         #endif
//
//      }
//      else if (edisplay == e_display_zoomed)
//      {
//
//         informationf("e_display_zoomed");
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display e_display_zoomed";
//
//         #endif
//
//      }
//      else if (edisplay == e_display_iconic)
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display e_display_iconic";
//
//         #endif
//
//      }
//      else if (edisplay == e_display_full_screen)
//      {
//
//         informationf("e_display_full_screen");
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display e_display_full_screen";
//
//         #endif
//
//      }
//      else
//      {
//
//         #ifdef INFO_LAYOUT_DISPLAY
//
//         information() << "interaction_layout::display (unknown)";
//
//         #endif
//
//      }
//
//#if DEBUG_LEVEL > 0
//
//      if (edisplay == e_display_normal)
//      {
//
//         if (m_pdescriptor.is_set() && m_puserinteractionParent == nullptr)
//         {
//
//            information() << "Parent is Null. Display Request -> normal";
//
//         }
//
//      }
//      else if (edisplay == e_display_hide)
//      {
//
//         if (m_pdescriptor.is_set() && m_puserinteractionParent == nullptr)
//         {
//
//            information() << "Parent is Null. Display Request -> hide";
//
//         }
//
//      }
//
//#endif
//
//      if (edisplay == e_display_default)
//      {
//
//         auto edisplayCurrent = m_stateRequest2.m_edisplay3;
//
//         auto edisplayStored = m_windowdisplayandlayout.m_edisplay;
//
//         auto edisplayPrevious = m_windowdisplayandlayout.m_edisplayPrevious;
//
//         if (edisplayCurrent == e_display_undefined)
//         {
//
//            edisplay = e_display_normal;
//
//         }
//         else if (::is_screen_visible(edisplayCurrent))
//         {
//
//            edisplay = edisplayCurrent;
//
//         }
//         else if (::is_screen_visible(edisplayStored))
//         {
//
//            edisplay = edisplayStored;
//
//         }
//         else if (::is_screen_visible(edisplayPrevious))
//         {
//
//            edisplay = edisplayPrevious;
//
//         }
//         else
//         {
//
//            edisplay = ::e_display_normal;
//
//         }
//
//         set_display_request(edisplay);
//
//      }
//      else
//      {
//
//         set_display_request(edisplay);
//
//      }
//
//      layout().sketch().XXXm_eactivation = XXXeactivation;
//
//      if (!sketch_on_display())
//      {
//
//         return false;
//
//      }
//
//      layout().set_need_redraw();
//
//      m_bPendingRequest = true;
//
//      return true;
//
//   }





   void interaction_layout::set_reposition(bool bSetThis)
   {

   }


   void interaction_layout::_set_reposition(bool bSetThis)
   {

      __UNREFERENCED_PARAMETER(bSetThis);

   }


   //void interaction_layout::set_pending_request(bool bSet)
   //{

   //   m_bPendingRequest = bSet;

   //}


   void interaction_layout::post_redraw(bool bAscendants)
   {


   }


   //bool interaction_layout::window_move(int x, int y)
   //{

   //   layout().sketch().m_point = {x, y};

   //   layout().set_need_redraw();

   //   return true;

   //}


   //bool interaction_layout::is_this_visible()
   //{

   //   return m_ewindowflag & e_window_flag_is_window && ::is_visible(layout().design().display());

   //}





   //void interaction_layout::window_rectangle(::int_rectangle* prectangle) const
   //{

   //   ::set_rect_point_size(prectangle, ui_state().m_pointScreen, ui_state().m_size);

   //}




   //bool interaction_layout::is_this_screen_visible() const
   //{

   //   if(layout().sketch().display() == e_display_iconic)
   //   {

   //      return ::is_screen_visible(window_display());

   //   }

   //   return ::is_screen_visible(layout().sketch().display());

   //}


   void interaction_layout::set_initial_dim(const ::int_point & p, const ::int_size & s)
   {

      sketch().set_visual_state_origin(p);

      sketch().m_size = s;

      design() = sketch();

      if (is_top_level())
      {

         window() = design();

         window().reset_pending();

      }

   }


} // namespace user



