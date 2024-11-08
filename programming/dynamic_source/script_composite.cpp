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

      m_pinterface.defer_destroy();

      script_interface::destroy();

   }


} // namespace dynamic_source



