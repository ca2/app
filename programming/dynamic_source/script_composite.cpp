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


   ::e_status script_composite::initialize(::context_object * pcontextobject)
   {

      auto estatus = script_interface::initialize(pcontextobject);

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



