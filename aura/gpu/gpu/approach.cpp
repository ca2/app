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


   void approach::initialize(::object * pobject)
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


   void approach::defer_init_glew()
   {

      return ::success;

   }


} // namespace gpu



