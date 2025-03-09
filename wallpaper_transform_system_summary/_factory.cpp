#include "framework.h"
#include "wallpaper_transform.h"


IMPLEMENT_FACTORY(wallpaper_transform_system_summary)
{

   pfactory->add_factory_item < ::wallpaper_transform_system_summary::wallpaper_transform, ::image::wallpaper_transform >();
   pfactory->add_factory_item < ::wallpaper_transform_system_summary::wallpaper_transform, ::component_implementation >();

}



//FACTORY_ITEM(::wallpaper_system_summary::folder)
//END_FACTORY()


//__FACTORY_EXPORT void wallpaper_system_summary_factory(::factory::factory * pfactory)
//{
//
//   pfactory->add_factory_item < ::wallpaper_system_summary::folder, ::folder >();
//   
//}



