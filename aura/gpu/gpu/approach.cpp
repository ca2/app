#include "framework.h"
#include "_.h"
#include "_gpu.h"


namespace gpu
{


   approach::approach()
   {

   }


   approach::~approach()
   {

   }


   ::e_status approach::initialize(::object * pobject)
   {

      ::e_status estatus = ::object::initialize(pobject);

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



