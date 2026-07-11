#include "acme/framework.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/filesystem/filesystem/resource_folder_pool.h"
#include <type_traits>


static_assert(::std::is_same_v <
   decltype(::std::declval < file_context & >().resource_folder()),
   resource_folder_lease >);


int main()
{

   return 0;

}
