//Created on 2013-03-16 00:37 BRT <3ThomasBS_ My Sweet!!
#include "framework.h"

#include "mysql/mysql_database.h"

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
//   //
//   //
//   //
//   factory_exchange::factory_exchange()
//   {
//
//      add_factory_item < ::imaging_wic::image_context, ::image_context >();
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

__FACTORY_EXPORT void database_mysql_factory(::factory::factory * pfactory)
{

   pfactory->add_factory_item < ::mysql::database, ::database::database >();

}




//imaging_wic::factory_exchange g_imagingwicfactoryexchange;
