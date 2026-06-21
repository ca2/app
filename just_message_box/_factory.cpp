#include "framework.h"
#include "application.h"

__FACTORY_EXPORT void just_message_box_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::just_message_box::application, ::platform::application >();

}
