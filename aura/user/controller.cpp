#include "framework.h"


namespace user
{
   
   
   controller::controller()
   {


   }


   controller::~controller()
   {

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



