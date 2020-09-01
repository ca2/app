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


   ::estatus script_composite::initialize(::object* pobjectContext)
   {

      auto estatus = script_interface::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   void script_composite::finalize()
   {

      script_interface::finalize();

      __finalize_and_release(m_pinterface);

   }


} // namespace dynamic_source



