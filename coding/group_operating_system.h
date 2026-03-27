// Created by camilo on 2024-02-24 03:51 <3ThomasBorregaardSorensen!!
#pragma once


#include "group.h"


namespace coding
{


   class CLASS_DECL_CODING group_operating_system :
      virtual public group
   {
   public:


      ::numeric_array_base < enum_integrate >     m_eintegratea;
      //map < enum_integrate, ::pointer < task_group > > m_taskgroup;

      group_operating_system();
      ~group_operating_system() override;


      virtual void initialize_group_operating_system(const enum_integrate* pe, ::collection::count c);
      
      ::collection::count get_size() override;
      enum_integrate get_eintegrate(::collection::index i) override;
      ::string get_name(::collection::index i) override;


   };


} // namespace coding



