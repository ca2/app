#pragma once


#include "apex/handler/manager.h"
#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_AQUA controller :
      virtual public ::particle
   {
   public:


      ::logic::boolean           m_bOpened;


      controller();
      ~controller() override;



      virtual bool is_opened() const;


      // void dump(dump_context&) const override;
      // void assert_ok() const override;


      virtual ::user::interaction* impact_at(::collection::index iImpact);
      virtual ::collection::count impact_count();


   };


} // namespace user



