#include "framework.h"


namespace draw2d_xlib
{


   factory_exchange::factory_exchange()
   {

      init_xlib_mutex(pobject);

      create_factory < image                   >  (__type(pimage));
      create_factory < graphics              >  (__type(::draw2d::graphics));
      create_factory < bitmap                >  (__type(::draw2d::bitmap));
      create_factory < pen                   >  (__type(::draw2d::pen));
      create_factory < brush                 >  (__type(::draw2d::brush));
      create_factory < palette               >  (__type(::draw2d::palette));
      create_factory < region                >  (__type(::draw2d::region));
      create_factory < font                  >  (__type(::draw2d::font));
      create_factory < path                  >  (__type(::draw2d::path));

   }


   factory_exchange::~factory_exchange()
   {

   }


} // namespace win


extern "C"
void factory_exchange()
{
   draw2d_xlib::factory_exchange factoryexchange();
}


