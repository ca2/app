// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/form_handler.h"


namespace axis
{


   class CLASS_DECL_AXIS form_handler :
      virtual public ::user::form_handler
   {
   public:


      form_handler();
      ~form_handler() override;


      ::pointer < ::user::line_layout > create_line_layout(::user::interaction * puserinteractionParent, enum_orientation eorientation);


      template < typename CHECK_BOX = ::user::check_box>
      ::pointer < CHECK_BOX >create_check_box_with_label(::user::interaction* puserinteractionParent, const ::scoped_string& scopedstr, ::pointer < ::user::still > * pstill = nullptr)
      {

         auto pline = create_line_layout(puserinteractionParent, e_orientation_horizontal);

         auto pcheckbox = __create_new<CHECK_BOX>();

         pcheckbox->m_bAutoResize = true;

         pcheckbox->create_child(pline);

         auto plabel = create_label < ::user::still >(pline, scopedstr);

         if (pstill)
         {

            *pstill = plabel;

         }

         //pcheckbox->set_window_text(scopedstrLabel);

         pcheckbox->display();

         pcheckbox->set_need_layout();

         return pcheckbox;

      }


   };


} // namespace axis



