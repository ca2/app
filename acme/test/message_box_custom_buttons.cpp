#include "acme/framework.h"
#include "acme/user/interface/message_box.h"
#include <type_traits>


using add_button_signature = void (::user_interface::message_box::*)(
   const ::scoped_string &, enum_dialog_result, ::i8);


static_assert(std::is_same_v <
   decltype(&::user_interface::message_box::add_button),
   add_button_signature >);


static_assert(std::is_same_v <
   decltype(::user_interface::message_box::m_bCustomButtons),
   bool >);


int main()
{
   return 0;
}
