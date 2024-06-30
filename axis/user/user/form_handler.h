// Created by camilo on 2023-07-14 14:48 <3ThomasBorregaardSorensen!!
#pragma once


#include "aura/user/user/form_handler.h"
#include "axis/user/user/multiple_option.h"
#include "line_layout.h"


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


      template < typename MULTIPLE_OPTION = ::user::multiple_option>
      ::pointer < MULTIPLE_OPTION >create_multiple_option(::user::interaction* puserinteractionParent, const ::data::property & property, const ::atom_array & atomaOptions, const ::string_array& straName)
      {

         auto pmultipleoption = __create_new<MULTIPLE_OPTION>();

         pmultipleoption->create_child(puserinteractionParent);

         pmultipleoption->m_propertyOption = property;

         for (::collection::index i = 0; i < atomaOptions.size(); i++)
         {

            auto& atom = atomaOptions[i];
            auto& name = straName[i];

            pmultipleoption->add_item(name, atom);

         }

         pmultipleoption->display();

         pmultipleoption->set_need_layout();

         return pmultipleoption;

      }


   };


} // namespace axis



