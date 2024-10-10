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
      string_map < ::pointer<product >>            m_map;
      

      product_array();
      ~product_array() override;


      virtual void initialize_product_array(department* pdepartment);
      
      virtual product * get_product(string strAppId, bool bFetch = false, bool bInteractive = true);
//      virtual product * interactive_get_product(string strAppId);
//      virtual product * noninteractive_get_product(string strAppId);
      
      
      virtual void _get_product(string strAppId, bool bInteractive);

      
      bool is_licensed(string strAppId, bool bInteractive = true);
      
      
      bool _is_licensed(string strAppId, bool bInteractive = true);
      

      ::collection::count clear_all_cache();
      bool clear_cache(string strAppId);


   };


} // namespace account



