#include "framework.h"
#include "application.h"


__FACTORY_EXPORT void app_net_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_net::application, ::platform::application >();

}




