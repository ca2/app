#include "framework.h"
#include "folder.h"


IMPLEMENT_FACTORY(folder_zip)
{

   pfactory->add_factory_item < ::folder_zip::folder, ::folder >();

}



//FACTORY_ITEM(::folder_zip::folder)
//END_FACTORY()


//__FACTORY_EXPORT void folder_zip_factory(::factory::factory * pfactory)
//{
//
//   pfactory->add_factory_item < ::folder_zip::folder, ::folder >();
//   
//}



