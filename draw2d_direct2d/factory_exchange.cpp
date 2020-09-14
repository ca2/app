#include "framework.h"
//#include "aura/printer.h"
#include "printer.h"


CLASS_DECL_AURA void init_draw2d_mutex();


extern CLASS_DECL_AURA image_array * g_pimagea;


namespace draw2d_direct2d
{


   factory_exchange::factory_exchange()
   {

      if (g_pimagea == nullptr)
      {

         g_pimagea = new image_array;

      }

      create_factory < image, ::image >();
      create_factory < bitmap, ::draw2d::bitmap >();
      create_factory < graphics_path, ::draw2d::path >();
      create_factory < pen, ::draw2d::pen >();
      create_factory < brush, ::draw2d::brush >();
      create_factory < palette, ::draw2d::palette >();
      create_factory < region, ::draw2d::region >();
      create_factory < font, ::draw2d::font >();

      create_factory < graphics, ::draw2d::graphics > ();

   }


   factory_exchange::~factory_exchange()
   {

      finalize();

   }


//#if defined(_UWP)
//
//   void factory_exchange::draw2d_direct2d_initialize()
//   {
//
//   }
//
//#endif


} // namespace draw2d_direct2d


//extern "C"
//void draw2d_factory_exchange()
//{
//
//   ::get_context_system()->m_pDraw2dFactoryExchange = new ::draw2d_direct2d::factory_exchange();
//
//}

//extern "C"
//void factory_exchange()
//{
//
//   draw2d_factory_exchange();
//
//}



