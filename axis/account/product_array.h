#pragma once


#include "acme/prototype/collection/string_map.h"
//#include "acme/prototype/prototype/pointer.h"


namespace account
{


   class CLASS_DECL_AXIS product_array :
      virtual public ::particle
   {
   public:

      
      department *                                 m_pdepartment;
      string_map_base < ::pointer<product >>            m_map;
      

      product_array();
      ~product_array() override;


      virtual void initialize_product_array(department* pdepartment);
      
      virtual product * get_product(const ::scoped_string & scopedstrAppId, bool bFetch = false, bool bInteractive = true);
//      virtual product * interactive_get_product(const ::scoped_string & scopedstrAppId);
//      virtual product * noninteractive_get_product(const ::scoped_string & scopedstrAppId);
      
      
      virtual void _get_product(const ::scoped_string & scopedstrAppId, bool bInteractive);

      
      bool is_licensed(const ::scoped_string & scopedstrAppId, bool bInteractive = true);
      
      
      bool _is_licensed(const ::scoped_string & scopedstrAppId, bool bInteractive = true);
      

      ::collection::count clear_all_cache();
      bool clear_cache(const ::scoped_string & scopedstrAppId);


   };


} // namespace account



