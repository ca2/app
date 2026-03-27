// Created by camilo on 2024-02-24 03:44 <3ThomasBorregaardSorensen!!
#pragma once


#include "_constant.h"


namespace coding
{


   class CLASS_DECL_CODING group :
      virtual public ::particle
   {
   public:


      integration* m_pintegration;
      item* m_pitem;


      group();
      ~group() override;

      
      virtual ::collection::count get_size();
      virtual ::coding::enum_integrate get_eintegrate(::collection::index i);
      virtual ::string get_name(::collection::index i);
      virtual ::string get_short_name(::collection::index i);


      virtual void call_integrate(item* pitem);
      virtual void integrate();


   };


} // namespace coding