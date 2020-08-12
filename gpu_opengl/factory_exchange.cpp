#include "framework.h"


//namespace gpu_opengl
//{
//
//
//#define new AURA_NEW
//
//
//   factory_exchange::factory_exchange()
//   {
//
//
//   }
//
//
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//
//
//} // namespace gpu_opengl
namespace gpu_opengl
{

   class factory_exchange
   {
   public:

      factory_exchange()
      {

         create_factory < ::opengl::opengl, ::gpu::approach >();

         create_factory < ::opengl::program, ::gpu::program >();

         create_factory < ::opengl::shader, ::gpu::shader >();

         create_factory < ::opengl::buffer, ::gpu::buffer >();

      }


      

   };

   factory_exchange g_factoryexchange;



} // namespace gpu_opengl



