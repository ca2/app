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


   ::e_status approach::initialize(::context_object * pcontextobject)
   {

      ::e_status estatus = ::object::initialize(pcontextobject);

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



