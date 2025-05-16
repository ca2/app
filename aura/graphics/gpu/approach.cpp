#include "framework.h"
#include "approach.h"
#include "acme/exception/interface_only.h"
//#include "_.h"
//#include "_gpu.h"


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


   ::pointer < ::gpu::context > approach::create_context(::particle * pparticle)
   {

      return nullptr;

   }


   void approach::defer_init_gpu_library()
   {

      //return ::success;

   }


   ::gpu::payload approach::load_dds(const ::scoped_string & scopedstrImagePath)
   {

      throw interface_only();

      return {};

   }


} // namespace gpu



