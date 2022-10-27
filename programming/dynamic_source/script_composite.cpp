#include "framework.h"
#include "script_composite.h"


namespace dynamic_source
{


   script_composite::script_composite()
   {

   }


   script_composite::~script_composite()
   {

   }


   void script_composite::initialize(::particle * pparticle)
   {

      //auto estatus = 
      
      script_interface::initialize(pparticle);

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



