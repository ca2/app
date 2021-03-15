#include "framework.h"


namespace account
{


   product_array::product_array()
   {

      defer_create_mutex();

   }



   product_array::~product_array()
   {

   }


   ::e_status product_array::initialize_product_array(department* pdepartment)
   {

      auto estatus = ::object::initialize(pdepartment);

      if (!estatus)
      {

         return estatus;

      }

      return estatus;

   }


//   product * product_array::interactive_get_product(string strAppId)
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
//   product * product_array::noninteractive_get_product(string strAppId)
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


   bool product_array::is_licensed(string strAppId, bool bInteractive)
   {

      product * pproduct = get_product(strAppId, true, bInteractive);

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


   void product_array::_get_product(string strAppId, bool bInteractive)
   {

      product * pproduct = nullptr;

      {

         synchronization_lock synchronizationlock(mutex());

         m_map[strAppId] = __new(::account::product);

         pproduct = get_product(strAppId);

      }

      if(pproduct == nullptr)
      {

         return;

      }

      pproduct->do_license(strAppId, bInteractive);

   }



//   bool product_array::is_licensed(string strAppId, bool bInteractive)
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

   ::count product_array::clear_all_cache()
   {

      ::count count = m_map.get_count();

      m_map.remove_all();

      return count;

   }


   bool product_array::clear_cache(string strAppId)
   {

      return m_map.remove_key(strAppId) != false;

   }


   product * product_array::get_product(string strAppId, bool bFetch, bool bInteractive)
   {

      auto & pproduct = m_map[strAppId];

      if(bFetch && pproduct.is_null())
      {

         _get_product(strAppId, bInteractive);

      }

      return m_map[strAppId];

   }


} // namespace account



