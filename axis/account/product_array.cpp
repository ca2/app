#include "framework.h"
#include "product_array.h"
#include "department.h"
#include "product.h"
#include "acme/parallelization/synchronous_lock.h"


namespace account
{


   product_array::product_array()
   {

      defer_create_synchronization();

   }



   product_array::~product_array()
   {

   }


   void product_array::initialize_product_array(department* pdepartment)
   {

      //auto estatus = 
      
      ::particle::initialize(pdepartment);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      //return estatus;

   }


//   product * product_array::interactive_get_product(const ::scoped_string & scopedstrAppId)
//   {
//
//      if(get_product22(strAppId) != nullptr)
//      {
//
//         return get_product22(strAppId);
//
//      }
//
//      return _get_product(strAppId, true);
//
//   }
//
//
//   product * product_array::noninteractive_get_product(const ::scoped_string & scopedstrAppId)
//   {
//
//      if(get_product22(strAppId) != nullptr)
//      {
//
//         return get_product22(strAppId);
//
//      }
//
//      return _get_product(strAppId, false);
//
//   }


   bool product_array::is_licensed(const ::scoped_string & scopedstrAppId, bool bInteractive)
   {

      product * pproduct = get_product(scopedstrAppId, true, bInteractive);

//      if(bInteractive)
//      {
//
//         pproduct = interactive_get_product(strAppId);
//
//      }
//      else
//      {
//
//         pproduct = noninteractive_get_product(strAppId);
//
//      }

      if(::is_null(pproduct))
      {

         return false;

      }

      return pproduct->is_licensed();

   }


   void product_array::_get_product(const ::scoped_string & scopedstrAppId, bool bInteractive)
   {

      product * pproduct = nullptr;

      {

         synchronous_lock synchronouslock(this->synchronization());

         m_map[scopedstrAppId] = øallocate ::account::product();

         pproduct = get_product(scopedstrAppId);

      }

      if(pproduct == nullptr)
      {

         return;

      }

      pproduct->do_license(scopedstrAppId, bInteractive);

   }



//   bool product_array::is_licensed(const ::scoped_string & scopedstrAppId, bool bInteractive)
//   {
//
//      product * pproduct;
//
//      if(bInteractive)
//      {
//
//         pproduct = interactive_get_product(strAppId);
//
//      }
//      else
//      {
//
//         pproduct = interactive_get_product(strAppId);
//
//      }
//
//      if(::is_null(pproduct))
//      {
//
//         return false;
//
//      }
//
//      return pproduct->is_ok();
//
//   }
//

   ::collection::count product_array::clear_all_cache()
   {

      ::collection::count count = m_map.get_count();

      m_map.erase_all();

      return count;

   }


   bool product_array::clear_cache(const ::scoped_string & scopedstrAppId)
   {

      return m_map.erase(scopedstrAppId);

   }


   product * product_array::get_product(const ::scoped_string & scopedstrAppId, bool bFetch, bool bInteractive)
   {

      auto & pproduct = m_map[scopedstrAppId];

      if(bFetch && pproduct.is_null())
      {

         _get_product(scopedstrAppId, bInteractive);

      }

      return m_map[scopedstrAppId];

   }


} // namespace account



