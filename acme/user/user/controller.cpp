#include "framework.h"
#include "controller.h"


namespace user
{


   controller::controller()
   {


   }


   controller::~controller()
   {

   }


   bool controller::is_opened() const
   {

      return m_bOpened;

   }


   ::user::interaction* controller::impact_at(::index iImpact)
   {

      return nullptr;

   }


   ::count controller::impact_count()
   {

      return 0;

   }



   void controller::id_update_all_impacts(const ::atom & atom)
   {

   }
   //virtual void update_all_impacts(impact * pimpact, const ::atom & atom);
   
   void controller::update_all_impacts(::topic * ptopic)
   {


   }


//   void controller::dump(dump_context&dumpcontext) const
//   {
//
//      channel::dump(dumpcontext);
//
//   }
//
//
//   void controller::assert_ok() const
//   {
//
//      channel::assert_ok();
//
//   }


} // namespace user



