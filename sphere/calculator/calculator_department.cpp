#include "framework.h"


namespace calculator
{

   department::department(::object * pobject) :
      ::apex::department(pobject)
   {
   }

   department::~department()
   {
   }


   bool department::init_instance()
   {

      if (!::apex::department::init_instance())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



