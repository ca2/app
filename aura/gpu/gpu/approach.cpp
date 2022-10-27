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


   void approach::initialize(::particle * pparticle)
   {

      ::object::initialize(pparticle);

   }


   context * approach::create_context()
   {

      return nullptr;

   }


   void approach::defer_init_glew()
   {

      //return ::success;

   }


   ::gpu::uniform approach::load_dds(const ::string & strImagePath)
   {

      throw interface_only();

      return -1;

   }


} // namespace gpu



