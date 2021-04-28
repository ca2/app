#include "framework.h"
//#include "aura/printer.h"
#include "printer.h"


CLASS_DECL_AURA void init_draw2d_mutex();


extern CLASS_DECL_AURA image_array * g_pimagea;


//namespace draw2d_direct2d
//{

extern "C"
void draw2d_direct2d_factory_exchange(::factory_map * pfactorymap)
   {

      if (g_pimagea == nullptr)
      {

         g_pimagea = new image_array;

      }

      create_factory < ::draw2d_direct2d::image, ::image >();
      create_factory < ::draw2d_direct2d::bitmap, ::draw2d::bitmap >();
      create_factory < ::draw2d_direct2d::path, ::draw2d::path >();
      create_factory < ::draw2d_direct2d::pen, ::draw2d::pen >();
      create_factory < ::draw2d_direct2d::brush, ::draw2d::brush >();
      create_factory < ::draw2d_direct2d::palette, ::draw2d::palette >();
      create_factory < ::draw2d_direct2d::region, ::draw2d::region >();
      create_factory < ::draw2d_direct2d::font, ::write_text::font >();

      create_factory < ::draw2d_direct2d::graphics, ::draw2d::graphics > ();

   }


   //factory_exchange::~factory_exchange()
   //{

   //   finalize();

   //}


//#if defined(_UWP)
//
//   void factory_exchange::draw2d_direct2d_initialize()
//   {
//
//   }
//
//#endif

//
//} // namespace draw2d_direct2d
//

//extern "C"
//void draw2d_factory_exchange(::factory_map * pfactorymap)
//{
//
//   psystem->m_pDraw2dFactoryExchange = new ::draw2d_direct2d::factory_exchange();
//
//}

//extern "C"
//void factory_exchange()
//{
//
//   draw2d_factory_exchange(::factory_map * pfactorymap);
//
//}



