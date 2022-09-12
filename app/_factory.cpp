#include "framework.h"

#include "application.h"


__FACTORY_EXPORT void app_app_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_app::application, ::app >();

}




