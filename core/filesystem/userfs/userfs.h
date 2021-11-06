#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::acme::department
   {
   public:


      userfs();
      virtual ~userfs();

      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status init1() override;


   };



} // namespace userfs



