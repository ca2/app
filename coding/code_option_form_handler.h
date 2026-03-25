// Created as main_item.h by camilo on 2024-04-27 22:43 <3ThomasBorregaardSorensen!!
// From main_item.h by camilo on 2024-04-27 22:50 <3ThomasBorregaardSorensen!!
// From install_base.h by camilo on 2024-04-27 22:58 <3ThomasBorregaardSorensen!!
// Here remains ui concern by camilo on 2024-05-04 04:11 <3ThomasBorregaardSorensen!!
// As option_form_handler by camilo on 2024-05-27 20:15 <3ThomasBorregaardSorensen!!
#pragma once


#include "code_application.h"
#include "apex/platform/app_consumer.h"
#include "axis/user/user/multiple_option.h"
#include "berg/user/user/form_handler.h"
#include "berg/user/user/impact.h"
#include "coding/install_impact_interface.h"
#include "coding/install_log_interface.h"


namespace coding
{


   class CLASS_DECL_CODING option_form_handler :
      virtual public app_consumer < ::coding::code_application, ::berg::form_handler, ::coding::install_impact_interface >
   {
   public:


      ::pointer < ::coding::option >       m_poption;
      ::pointer < ::coding::code >    m_pcode;


      ::pointer < ::user::multiple_option >     m_pmultipleoption;


      option_form_handler();
      ~option_form_handler() override;


      ::pointer<::user::multiple_option > create_option_form_handler(::coding::code * pcode, ::coding::option * poption, ::user::interaction* puserinteractionParent);


   };


} // namespace coding


