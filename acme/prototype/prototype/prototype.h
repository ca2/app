// Created by camilo on 2023-11-24 14:58 <3ThomasBorregaardSorensen!!
#pragma once


namespace prototype
{


   class CLASS_DECL_ACME prototype :
      virtual public particle
   {
   public:


      ::pointer < ::mathematics::mathematics > m_pmathematics;
      
      prototype();
      ~prototype();

#ifdef DEBUG
      ::i64 increment_reference_count() override;
      ::i64 decrement_reference_count() override;
#endif
      

      void on_initialize_particle() override;

      
      class time random(const class time & d1, const class time & d2);


   };



} // namespace prototype




