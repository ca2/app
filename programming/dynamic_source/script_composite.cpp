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


   void script_composite::finalize()
   {

      ::defer_finalize__destroy_and_release(m_pinterface);

      ::dynamic_source::script_interface::finalize();

   }


   void script_composite::destroy()
   {

      script_interface::destroy();

   }


} // namespace dynamic_source



