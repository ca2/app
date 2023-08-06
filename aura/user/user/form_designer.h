// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{

   class CLASS_DECL_AURA form_designer :
      virtual public ::particle
   {
   public:


      form_designer();
      ~form_designer() override;


      template < typename LABEL >
      ::pointer < LABEL >create_label(::user::interaction * puserinteractionParent, const ::scoped_string & scopedstrLabel)
      {

         auto plabel = __create_new<LABEL>();

         plabel->m_bAutoResize = true;

         plabel->create_child(puserinteractionParent);

         plabel->set_window_text(scopedstrLabel);

         plabel->display();

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


   };


} //namespace user



