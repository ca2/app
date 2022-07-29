#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "_library.h"
#endif


__FACTORY_EXPORT void app_app_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_app::application, ::app >();

}




