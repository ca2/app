#include "platform.h"
#include "folder.h"

IMPLEMENT_FACTORY(folder_google_drive)
{
   pfactory->add_factory_item < ::folder_google_drive::folder, ::folder >();
   pfactory->add_factory_item < ::folder_google_drive::folder, ::fs::data >();
}
