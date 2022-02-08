#include "framework.h"


namespace user
{


   controller::controller()
   {


   }


   controller::~controller()
   {

   }


   ::user::interaction* controller::impact_at(::index iImpact) const
   {

      return nullptr;

   }


   ::count controller::impact_count() const
   {

      return 0;

   }


   void controller::dump(dump_context&dumpcontext) const
   {

      channel::dump(dumpcontext);

   }


   void controller::assert_ok() const
   {

      channel::assert_ok();

   }



} // namespace user



