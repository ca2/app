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

         auto plabel = __create_new<CHECK_BOX>();

         plabel->m_bAutoResize = true;

         plabel->create_child(puserinteractionParent);

         plabel->set_window_text(scopedstrLabel);

         plabel->display();

         return plabel;


      }


   };


} //namespace user



