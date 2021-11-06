#include "framework.h"
//#include "android.h"


namespace android
{


   namespace axis
   {


      factory_exchange::factory_exchange()
      {

         //create_factory < file_set                 >(__type(::file::set);
         create_factory < ::android::axis::file_system   >(__type(::file::system),1);
         create_factory < ::android::axis::dir           >(__type(::file::system_dir),1);
         create_factory <crypto                   >(__type(::crypto::crypto),1);
         create_factory <ip_enum                  >(__type(::net::ip_enum);
         create_factory <copydesk                 >(__type(::user::copydesk);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace android


void __node_axis_factory_exchange(::factory_map * pfactorymap)
{

   ::android::axis::factory_exchange factoryexchange();

}


