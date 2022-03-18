#include "framework.h"


__FACTORY_EXPORT void experience_tranquillum_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::experience_tranquillum::experience, ::experience::experience >();
   pfactory->add_factory_item < ::experience_tranquillum::control_box, ::experience::control_box >();
   pfactory->add_factory_item < ::experience_tranquillum::control_box_button, ::experience::button >();
   pfactory->add_factory_item < ::experience_tranquillum::style, ::user::style >();

}



