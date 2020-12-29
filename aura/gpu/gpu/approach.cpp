#include "framework.h"
#include "_.h"


namespace gpu
{


   approach::approach()
   {

   }


   approach::~approach()
   {

   }


   ::e_status approach::initialize(::layered * pobjectContext)
   {

      ::e_status estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


   context * approach::create_context()
   {

      return nullptr;

   }


   ::e_status approach::defer_init_glew()
   {

      return ::success;

   }


} // namespace gpu



