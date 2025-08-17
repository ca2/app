// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/button.h"
#include "aura/user/user/check_box.h"
#include "aura/user/user/still.h"


namespace user
{


   class CLASS_DECL_AURA form_handler :
      virtual public ::object
   {
   public:

      ::write_text::font_pointer m_pfontTitle1;
      ::write_text::font_pointer m_pfontTitle2;

      form_handler();
      ~form_handler() override;


      template < typename LABEL = ::user::still>
      ::pointer < LABEL >create_label(::user::interaction* puserinteractionParent)
      {

         auto plabel = øcreate_new<LABEL>();

         plabel->m_bAutoResize = true;

         plabel->create_child(puserinteractionParent);

         plabel->display();

         plabel->set_need_layout();

         return plabel;

      }

      template < typename LABEL =::user::still>
      ::pointer < LABEL >create_label(::user::interaction * puserinteractionParent, const ::data::property& propertyTitle)
      {

         auto plabel = create_label<LABEL>(puserinteractionParent);

         plabel->set_text_property(propertyTitle);

         return plabel;

      }


      template < typename LABEL = ::user::still>
      ::pointer < LABEL >create_label(::user::interaction* puserinteractionParent, const ::scoped_string & scopedstrLabel)
      {

         auto plabel = create_label<LABEL>(puserinteractionParent);

         plabel->set_window_text(scopedstrLabel);

         return plabel;

      }


      ::write_text::font_pointer get_title1_font();

      template < typename LABEL = ::user::still >
      ::pointer < LABEL >create_title1(::user::interaction* puserinteractionParent, const ::scoped_string& scopedstrTitle1)
      {

         auto plabel = create_label<LABEL>(puserinteractionParent, scopedstrTitle1);

         plabel->m_pfont = get_title1_font();

         return plabel;

      }

      ::write_text::font_pointer get_title2_font();

      template < typename LABEL = ::user::still >
      ::pointer < LABEL >create_title2(::user::interaction* puserinteractionParent, const ::data::property & propertyTitle)
      {

         auto plabel = create_label<LABEL>(puserinteractionParent, propertyTitle);

         plabel->m_pfont = get_title2_font();

         return plabel;

      }


      template < typename CHECK_BOX = ::user::check_box>
      ::pointer < CHECK_BOX >create_check_box(::user::interaction * puserinteractionParent, const ::atom & atom)
      {

         auto pcheckbox = øcreate_new<CHECK_BOX>();

         pcheckbox->m_bAutoResize = true;

         pcheckbox->create_control(puserinteractionParent, atom);

         //pcheckbox->set_window_text(scopedstrLabel);

         pcheckbox->display();

         pcheckbox->set_need_layout();

         return pcheckbox;

      }


      template < typename CHECK_BOX = ::user::check_box>
      ::pointer < CHECK_BOX >create_check_box(::user::interaction * puserinteractionParent, const ::data::property & property)
      {

         auto pcheckbox = create_check_box<CHECK_BOX>(puserinteractionParent, property.atom());

         pcheckbox->set_check_property(property);

         return pcheckbox;

      }


      template < typename BUTTON =::user::button>
      ::pointer < BUTTON >create_button(::user::interaction* puserinteractionParent, const ::scoped_string& scopedstrName)
      {

         auto pbutton = øcreate_new<BUTTON>();

         pbutton->m_bAutoResize = true;

         pbutton->create_child(puserinteractionParent);

         pbutton->set_window_text(scopedstrName);

         pbutton->display();

         pbutton->set_need_layout();

         return pbutton;

      }


      template < typename EDIT >
      ::pointer < EDIT >create_edit(::user::interaction* puserinteractionParent)
      {

         auto pedit = øcreate_new<EDIT>();

         //pbutton->m_bAutoResize = true;

         pedit->create_child(puserinteractionParent);

         //pbutton->set_window_text(scopedstrName);

         pedit->display();

         return pedit;

      }


      virtual void design_form(::user::interaction * puserinteraction);


   };


} //namespace user



