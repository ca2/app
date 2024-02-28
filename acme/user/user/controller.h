#pragma once


//#include "apex/handler/manager.h"
//#include "apex/message/channel.h"


namespace user
{


   class CLASS_DECL_ACME controller :
      virtual public ::particle
   {
   public:


      boolean           m_bOpened;


      controller();
      ~controller() override;



      virtual bool is_opened() const;


      // void dump(dump_context&) const override;
      // void assert_ok() const override;


      virtual ::user::interaction* impact_at(::index iImpact);
      virtual ::count impact_count();


      virtual void id_update_all_impacts(const ::atom & atom);
      //virtual void update_all_impacts(impact * pimpact, const ::atom & atom);
      virtual void update_all_impacts(::topic * ptopic);


   };


} // namespace user



