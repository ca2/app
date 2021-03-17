//Created on 2013-03-16 00:37 BRT <3ThomasBS_ My Sweet!!
#include "framework.h"
#include "mysql/mysql_database_impl.h"

//namespace imaging_wic
//{
//
//   class factory_exchange
//   {
//   public:
//
//
//      factory_exchange();
//      virtual ~factory_exchange();
//
//   };
//
//
//   //#define new ACME_NEW
//   //
//   //
//   factory_exchange::factory_exchange()
//   {
//
//      create_factory < ::imaging_wic::context_image, ::context_image >();
//
//   }
//
//   //
//   factory_exchange::~factory_exchange()
//   {
//
//   }
//   //
//   //
//} // namespace imaging_wic
////

extern "C"
void imaging_wic_factory_exchange(::factory_map * pfactorymap)
{

   pfactorymap->create_factory < ::mysql::database_impl, ::database::database >();

}




//imaging_wic::factory_exchange g_imagingwicfactoryexchange;