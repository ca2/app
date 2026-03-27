// From group_new_release_prefix.h by camilo on 2024-03-24 22:36 <3ThomasBorregaardSorensen!!
#pragma once


#include "group.h"


namespace coding
{


   class CLASS_DECL_CODING group_checkout_for_another_system :
      virtual public group
   {
   public:


      ::string m_strSlashedSystem;


      group_checkout_for_another_system();
      ~group_checkout_for_another_system() override;


      //virtual void initialize_group_new_release_prefix(const ::string_array& straMachineBox);
      virtual void initialize_group_checkout_for_another_system(const ::scoped_string & scopedstrSlashedSystem);


      ::collection::count get_size() override;
      enum_integrate get_eintegrate(::collection::index i) override;
      ::string get_name(::collection::index i) override;
      ::string get_short_name(::collection::index i) override;

      void integrate() override;


   };


} // namespace coding



