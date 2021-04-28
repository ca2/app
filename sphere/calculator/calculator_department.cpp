#include "framework.h"


namespace calculator
{

   department::department(::object * pobject) :
      ::acme::department(pobject)
   {
   }

   department::~department()
   {
   }


   bool department::init_instance()
   {

      if (!::acme::department::init_instance())
      {

         return false;

      }

      return true;

   }


} // namespace calculator



