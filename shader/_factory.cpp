#include "framework.h"
#include "application.h"


__FACTORY_EXPORT void app_shader_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_shader::application, ::acme::application >();

}




