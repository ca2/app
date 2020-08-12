#include "framework.h"


//namespace draw2d_quartz2d
//{
//   
//
//   void factory_exchange()
//   {
//      
//     
//
//   }
//   
//   
//} // namespace draw2d_quartz2d


extern "C" void draw2d_factory_exchange()
{
   
   create_factory < ::draw2d_quartz2d::image        , ::image >();
   create_factory < ::draw2d_quartz2d::graphics     , ::draw2d::graphics > ();
   create_factory < ::draw2d_quartz2d::bitmap       , ::draw2d::bitmap > ();
   create_factory < ::draw2d_quartz2d::pen          , ::draw2d::pen > ();
   create_factory < ::draw2d_quartz2d::brush        , ::draw2d::brush > ();
   create_factory < ::draw2d_quartz2d::palette      , ::draw2d::palette > ();
   create_factory < ::draw2d_quartz2d::region       , ::draw2d::region > ();
   create_factory < ::draw2d_quartz2d::font         , ::draw2d::font > ();
   create_factory < ::draw2d_quartz2d::path         , ::draw2d::path > ();

}



