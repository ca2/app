// Created by camilo with chatgpt and lowluds on 2025-02-12 21:32 <3ThomasBorregaardSorensen.cpp
#pragma once


namespace platform
{


   struct test_case :
      virtual public ::particle
   {


      ::string m_strName;
      ::procedure m_procedure;


      test_case(const ::scoped_string& scopedstr, const ::procedure& procedure);
      ~test_case() override;

      ::string& name() { return m_strName; }
      void run() override;
      

   };


   class CLASS_DECL_ACME prober :
      virtual public ::particle
   {
   public:



      ::pointer_array < test_case > m_testcasea;


      virtual void add_prober(const ::scoped_string& name, const ::procedure& test);

      void run() override;
      void expect(bool condition, const ::scoped_string& message);

      

   };


}




