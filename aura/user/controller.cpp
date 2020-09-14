#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


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


   void controller::assert_valid() const
   {

      channel::assert_valid();

   }



} // namespace user



