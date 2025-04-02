#pragma once


#include "list.h"
#include "base/user/user/margin.h"
#include "base/user/user/show.h"


namespace user
{


   class CLASS_DECL_CORE list_impact:
      virtual public ::user::show < ::user::margin < ::user::list > >
   {
   public:


      using BASE_VIEW = ::user::show < ::user::margin < ::user::list > >;


      list_impact();
      virtual ~list_impact();


      void install_message_routing(::channel * pchannel) override;


      void handle(::topic * ptopic, ::handler_context * pcontext) override;

      
      void on_selection_change() override;


   };


} // namespace user




