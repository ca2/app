// From tab_impact.cpp by camilo on 2022-08-27 18:16 <3ThomasBorregaadSorensen!!
#include "framework.h"
#include "tab_drop_target_window.h"
#include "tab.h"
#include "acme/constant/message.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/message/user.h"


namespace user
{


   tab_drop_target_window::tab_drop_target_window()
   {
   }


   tab_drop_target_window::~tab_drop_target_window()
   {

   }


   void tab_drop_target_window::initialize_tab_drop_target_window(::user::tab * ptab, index iTab)
   {

      //auto estatus = 

      ::user::interaction::initialize(ptab);

      //if (!estatus)
      //{

      //   return estatus;

      //}



      m_positiona.add(e_position_top);

      m_positiona.add(e_position_right);

      m_positiona.add(e_position_bottom);

      m_positiona.add(e_position_left);

      m_ptab = ptab;

      m_iTab = iTab;

      //return estatus;

   }


   void tab_drop_target_window::install_message_routing(::channel * pchannel)
   {

      ::user::interaction::install_message_routing(pchannel);

      MESSAGE_LINK(e_message_left_button_up, pchannel, this, &tab_drop_target_window::on_message_left_button_up);

   }


   void tab_drop_target_window::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      ::color::color crBorderNormal = argb(80, 127, 127, 80);

      ::color::color crBorderSelect = argb(100, 40, 40, 20);

      ::color::color crBorder;

      ::color::color crBkNormal = argb(160, 150, 200, 255);

      ::color::color crBkSelect = argb(180, 255, 230, 155);

      ::color::color crBk;

      auto pointCursor = get_cursor_position();
      
      screen_to_client()(pointCursor);

      enum_position epositionDrag = m_ptab->DragHitTest(pointCursor);

      for (auto eposition : m_positiona)
      {

         ::rectangle_i32 rectangle;

         m_ptab->GetDragRect(rectangle, eposition);

         if (eposition == epositionDrag)
         {

            crBk = crBkSelect;

            crBorder = crBorderSelect;

         }
         else
         {

            crBk = crBkNormal;

            crBorder = crBorderNormal;

         }

         pgraphics->fill_rectangle(rectangle, crBk);

         pgraphics->draw_inset_rectangle(rectangle, crBorder, 1.0);

      }

   }


   //bool tab_drop_target_window::get_translucency(::user::enum_translucency & etranslucency, ::enum_element eelement, ::user::interaction * pinteraction)
   //{

   //   etranslucency = e_translucency_present;

   //   return true;

   //}

   void tab_drop_target_window::on_message_left_button_up(::message::message * pmessage)
   {

      auto pmouse = pmessage->m_union.m_pmouse;

      release_mouse_capture();

      auto point(pmouse->m_point);

      screen_to_client()(point);

      enum_position eposition = m_ptab->DragHitTest(point);

      m_ptab->_001OnDropTab(m_iTab, eposition);

      display(e_display_none);

      start_destroying_window();

      pmessage->m_bRet = true;

   }


   bool tab_drop_target_window::has_pending_graphical_update()
   {

      return true;

   }


} // namespace user



