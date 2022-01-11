#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::acme::department
   {
   public:


      userfs();
      virtual ~userfs();

      virtual void initialize(::object * pobject) override;

      virtual void init1() override;


   };



} // namespace userfs



