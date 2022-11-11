#include "framework.h"
#include "style_base.h"
#include "interaction.h"
#include "acme/constant/id.h"
#include "acme/platform/node.h"
#include "aura/platform/system.h"


namespace user
{


   style_base::style_base()
   {

      //m_bDarkMode = true;

   }


   style_base::~style_base()
   {


   }



   void style_base::on_initialize_particle()
   {

      //auto estatus = 
      
      ::manager::on_initialize_particle();

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = acmesystem()->m_paurasystem;

      auto psignal = psystem->get_signal(id_operating_system_user_color_change);

      psignal->add_handler(this);

      on_user_color();

      //return estatus;

   }


   void style_base::on_user_color()
   {


      //if (is_different(m_bDarkMode, bDarkMode))
      {

         auto psystem = acmesystem();

         auto pnode = psystem->node();

         auto bDarkMode = pnode->dark_mode();

         m_bDarkMode = bDarkMode;


         //m_bDarkMode = bDarkMode;

         //auto psystem = acmesystem();

         //psystem->m_papexsystem->signal(id_user_style_change);

      }

   }


   //bool style_base::is_dark_mode() const
   //{

   //   return

   //   //auto psystem = acmesystem();

   //   //auto pnode = psystem->node();

   //   //auto bDarkMode = pnode->dark_mode();

   //   //return bDarkMode;

   //}


   void style_base::handle(::topic * ptopic, ::context * pcontext)
   {

      if (ptopic->m_atom == id_operating_system_user_color_change)
      {

         on_user_color();

      }

   }



   bool style_base::_001OnDrawSplitLayout(::draw2d::graphics_pointer & pgraphics, ::user::split_layout * psplitlayout)
   {

      return false;

   }


   bool style_base::_001OnDrawMainFrameBackground(::draw2d::graphics_pointer & pgraphics,::user::frame * pframe)
   {

      return false;

   }


   bool style_base::draw_check(::user::interaction * pinteraction, ::enum_check echeck, const ::rectangle_i32 & rectangle, ::draw2d::graphics_pointer & pgraphics)
   {

      return false;

   }


   bool style_base::simple_ui_draw_focus_rect(::user::interaction * pinteraction,::draw2d::graphics_pointer & pgraphics)
   {

      return false;

   }


   bool style_base::_001DrawToolbarItem(::draw2d::graphics_pointer & pgraphics, index iItem, ::user::toolbar * ptoolbar)
   {

      return false;

   }


   bool style_base::_001DrawSimpleScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   bool style_base::_001DrawScrollBar(::draw2d::graphics_pointer & pgraphics, ::user::scroll_bar * pbar)
   {

      return false;

   }


   enum_control_type style_base::get_control_type() const
   {

      return e_control_type_none;

   }


   ::color::color style_base::get_color(::user::interaction* pinteraction, ::enum_element eelement, ::user::enum_state estate)
   {

      if (::is_set(pinteraction))
      {

         auto econtroltype = pinteraction->get_control_type();

         if (econtroltype == ::user::e_control_type_list)
         {

            if (eelement == ::e_element_background)
            {

               return ::color::color(0, 0, 0, 0);

            }

         }

      }

      return ::color::color();

   }


   bool style_base::get_int(::user::interaction * pinteraction, int & i, ::user::enum_int eint, ::user::enum_state estate)
   {

      return false;

   }


   bool style_base::get_double(::user::interaction* pinteraction, double & d, ::user::enum_double edouble, ::user::enum_state estate)
   {

      return false;

   }


} // namespace user











