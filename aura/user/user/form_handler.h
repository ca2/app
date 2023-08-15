// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


   class CLASS_DECL_AURA form_handler :
      virtual public ::particle
   {
   public:


      form_handler();
      ~form_handler() override;


      template < typename LABEL >
      ::pointer < LABEL >create_label(::user::interaction * puserinteractionParent, const ::scoped_string & scopedstrLabel)
      {

         auto plabel = __create_new<LABEL>();

         plabel->m_bAutoResize = true;

         plabel->create_child(puserinteractionParent);

         plabel->set_window_text(scopedstrLabel);

         plabel->display();

         plabel->set_need_layout();

         return plabel;

      }


      template < typename CHECK_BOX >
      ::pointer < CHECK_BOX >create_check_box(::user::interaction * puserinteractionParent, const ::scoped_string & scopedstrLabel)
      {

         auto pcheckbox = __create_new<CHECK_BOX>();

         pcheckbox->m_bAutoResize = true;

         pcheckbox->create_child(puserinteractionParent);

         pcheckbox->set_window_text(scopedstrLabel);

         pcheckbox->display();

         pcheckbox->set_need_layout();

         return pcheckbox;

      }


      template < typename BUTTON >
      ::pointer < BUTTON >create_button(::user::interaction* puserinteractionParent, const ::scoped_string& scopedstrName)
      {

         auto pbutton = __create_new<BUTTON>();

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

         auto pedit = __create_new<EDIT>();

         //pbutton->m_bAutoResize = true;

         pedit->create_child(puserinteractionParent);

         //pbutton->set_window_text(scopedstrName);

         pedit->display();

         return pedit;

      }


      virtual void design_form(::user::interaction * puserinteraction);


   };


} //namespace user



