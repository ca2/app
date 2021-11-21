#include "framework.h"
//#include "android.h"


namespace android
{


   namespace axis
   {


      factory_exchange::factory_exchange()
      {

         //add_factory_item < file_set                 >(__type(::file::set);
         add_factory_item < ::android::axis::file_system   >(__type(::file::system),1);
         add_factory_item < ::android::axis::dir           >(__type(::file::system_dir),1);
         add_factory_item <crypto                   >(__type(::crypto::crypto),1);
         add_factory_item <ip_enum                  >(__type(::net::ip_enum);
         add_factory_item <copydesk                 >(__type(::user::copydesk);

      }


      factory_exchange::~factory_exchange()
      {

      }


   } // namespace axis


} // namespace android


void __node_axis_factory(::factory::factory * pfactory)
{

   ::android::axis::factory_exchange factoryexchange();

}


