// Created by camilo on 2024-02-25 11:50 <3ThomasBorregaardSorensen!!
#pragma once


#include "group.h"
#include "acme/parallelization/semaphore.h"


namespace coding
{


   class CLASS_DECL_CODING group_netnode :
      virtual public group
   {
   public:


      ::string_array    m_straNetnode;


     ::pointer < ::semaphore >      m_psemaphore;


      group_netnode();
      ~group_netnode() override;


      virtual void initialize_group_netnode(const ::string_array & straNetnode);

      ::collection::count get_size() override;
      enum_integrate get_eintegrate(::collection::index i) override;
      ::string get_name(::collection::index i) override;


      virtual void start_integration(::coding::integration * pintegration);

//      virtual void start_netnode(const ::scoped_string& scopedstrNetnode);

  //    virtual void monitor_netnode(const ::scoped_string& scopedstrNetnode);

      //virtual ::string running_status();

      virtual void wait_to_finish();


   };


} // namespace coding



