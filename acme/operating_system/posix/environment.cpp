#include "framework.h"
#include "environment.h"
#include "acme/filesystem/filesystem/acme_directory.h"

::string current_working_directory();

namespace acme_posix
{


   ::status < ::string > environment::lookup(const ::scoped_string & scopedstrKey)
   {

      // Special keys

      if(scopedstrKey == "slashed_pwd")
      {

         /// slashed_pwd
         // if pwd is unknown, not set or empty returns a "/";

         auto p = getenv("PWD");

         if(::is_null(p) || *p == '\0')
         {

            auto current_directory = ::current_working_directory();

            if(current_directory.is_empty())
            {

               return ::string("/");

            }

         }

         return ::string(p);

      }

      ::string strKey(scopedstrKey);

      auto p = getenv(strKey);

      if(::is_null(p))
      {

         return error_not_found;

      }

      return ::string(p);

   }


} // namespace acme_posix



::pointer < ::operating_system::environment > operating_system_get_environment()
{

   auto p = ::place(new ::acme_posix::environment());
   
   return p;

}




