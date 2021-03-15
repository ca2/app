#include "framework.h"



namespace calculator
{


   calculator::calculator()
   {
   
   }


   calculator::~calculator()
   {

   }


   ::e_status calculator::initialize(::context_object * pcontextobject)
   {

      auto estatus = ::apex::department::initialize(pcontextobject);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


} // namespace calculator





