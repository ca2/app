#include "framework.h"
#include "dropbox.h"
//#include "uncompress.h"
#include "acme/prototype/prototype/factory.h"


__FACTORY_EXPORT void dropbox_factory(::factory::factory * pfactory)
{
   //
   pfactory->add_factory_item < ::dropbox::dropbox, ::platform::department >();
   // pfactory->add_factory_item < ::compress_zlib::uncompress, ::uncompress >();
   //
}



