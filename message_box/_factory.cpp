#include "framework.h"


__FACTORY_EXPORT void app_message_box_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::app_message_box::application, ::app >();

}