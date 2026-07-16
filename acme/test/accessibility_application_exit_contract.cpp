#include "acme/framework.h"
#include "acme/accessibility/application.h"
#include <type_traits>


using post_and_wait_signature =
   ::e_status (::accessibility::application::*)(const class ::time &);

using force_exit_signature =
   ::e_status (::accessibility::application::*)(const class ::time &);


static_assert(std::is_same_v <
   decltype(&::accessibility::application::post_and_wait_to_exit),
   post_and_wait_signature >);

static_assert(std::is_same_v <
   decltype(&::accessibility::application::force_exit),
   force_exit_signature >);


int main()
{
   return 0;
}
