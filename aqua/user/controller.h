#pragma once


#include "apex/handler/manager.h"
#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_AQUA controller :
      virtual public channel,
      virtual public ::manager
   {
   public:


      controller();
      ~controller() override;


      // void dump(dump_context&) const override;
      // void assert_ok() const override;


      virtual ::user::interaction* impact_at(::index iImpact) const;
      virtual ::count impact_count() const;


   };


} // namespace user



