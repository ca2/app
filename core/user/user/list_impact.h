#pragma once


#include "list_base.h"
#include "berg/user/user/margin.h"
#include "berg/user/user/show.h"


namespace user
{


   class CLASS_DECL_CORE list_impact:
      virtual public ::user::show < ::user::margin < ::user::list_base > >
   {
   public:


      using BASE_VIEW = ::user::show < ::user::margin < ::user::list_base > >;


      list_impact();
      virtual ~list_impact();


      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      
      void on_selection_change() override;


   };


} // namespace user




