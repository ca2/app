// From install_impact_interface.h by camilo on 2024-05-04 05:42 <3ThomasBorregaardSorensen!!
#pragma once


#include "application.h"
#include "apex/platform/app_consumer.h"


namespace coding
{


   class CLASS_DECL_CODING install_log_interface :
      virtual public app_consumer < application >
   {
   public:

      
      install_log_interface();
      ~install_log_interface() override;


      virtual void install_status(install * pinstall, const ::scoped_string& scopedstr);
      virtual void install_status2(install* pinstall, const ::scoped_string& scopedstr);
      virtual void install_append_status2(install* pinstall, const ::scoped_string& scopedstr);


      virtual void on_update_install_status(install* pinstall);


   };


} // namespace coding



