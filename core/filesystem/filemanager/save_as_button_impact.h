// From save_as_name_impact by camilo on 2023-05-05 19:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "impact_base.h"
#include "aura/user/user/button.h"


namespace filemanager
{


   class CLASS_DECL_CORE save_as_button_impact :
      virtual public ::filemanager_show < ::user::show < ::user::button > >
   {
   public:


      save_as_button_impact();
      ~save_as_button_impact() override;


      void install_message_routing(::channel * pchannel) override;


      bool on_click(::item * pitem) override;
      void handle(::topic * ptopic, ::context * pcontext) override;


      virtual void save_document(::file::path path);

      virtual void cancel_save_document();


   };



} // namespace filemanager



