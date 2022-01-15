#include "framework.h"
#include "_.h"


namespace dynamic_source
{


   script_composite::script_composite()
   {

   }


   script_composite::~script_composite()
   {

   }


   void script_composite::initialize(::object * pobject)
   {

      //auto estatus = 
      
      script_interface::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


   void script_composite::destroy()
   {

      //auto estatus =
      
      script_interface::destroy();

      __destroy_and_release(m_pinterface);

      //return estatus;

   }


} // namespace dynamic_source



