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


   ::estatus approach::initialize(::object* pobjectContext)
   {

      ::estatus estatus = ::object::initialize(pobjectContext);

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


   ::estatus approach::defer_init_glew()
   {

      return ::success;

   }


} // namespace gpu



