#include "framework.h"
#include "experience/experience.h"
#include "experience/control_box.h"
#include "experience/control_box_button.h"
#include "user/style.h"



__FACTORY_EXPORT void experience_nanoui_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::experience_nanoui::experience, ::experience::experience >();
   pfactory->add_factory_item < ::experience_nanoui::control_box, ::experience::control_box >();
   pfactory->add_factory_item < ::experience_nanoui::control_box_button, ::experience::button >();
   pfactory->add_factory_item < ::experience_nanoui::style, ::user::style >();
                
   //pfactory->add_factory_item < ::experience_nanoui::still, ::user::still >();

}



