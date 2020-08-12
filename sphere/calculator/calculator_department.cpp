#include "framework.h"


namespace calculator
{

   department::department(::object * pobject) :
      ::aura::department(pobject)
   {
   }

   department::~department()
   {
   }


   bool department::init_instance()
   {

      if (!::aura::department::init_instance())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



