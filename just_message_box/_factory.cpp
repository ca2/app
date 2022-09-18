#include "framework.h"


__FACTORY_EXPORT void app_just_message_box_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_just_message_box::application, ::acme::application >();

}