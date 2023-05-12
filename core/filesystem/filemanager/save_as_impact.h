// From save_as_name_impact by camilo on 2023-05-05 19:11 <3ThomasBorregaardSorensen!!
#pragma once


#include "impact_base.h"
#include "aura/user/user/button.h"


namespace filemanager
{


   class CLASS_DECL_CORE save_as_impact:
      virtual public ::filemanager_show < ::user::split_impact >
   {
   public:

      
      ::pointer < save_as_edit_impact >      m_pedit;
      ::pointer < save_as_button_impact >    m_pbutton;


      save_as_impact();
      ~save_as_impact() override;


      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void on_create_split_impact() override;

   };


} // namespace filemanager





