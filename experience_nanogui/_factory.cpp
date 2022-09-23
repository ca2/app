#include "framework.h"
#include "experience/experience.h"
#include "experience/control_box.h"
#include "experience/control_box_button.h"
#include "user/style.h"



__FACTORY_EXPORT void experience_nanogui_factory(::factory::factory* pfactory)
{

   pfactory->add_factory_item < ::experience_nanogui::experience, ::experience::experience >();
   pfactory->add_factory_item < ::experience_nanogui::control_box, ::experience::control_box >();
   pfactory->add_factory_item < ::experience_nanogui::control_box_button, ::experience::button >();
   pfactory->add_factory_item < ::experience_nanogui::style, ::user::style >();
                
   //pfactory->add_factory_item < ::experience_nanogui::still, ::user::still >();

}



