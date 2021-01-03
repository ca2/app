#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::apex::department
   {
   public:


      userfs();
      virtual ~userfs();

      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual ::e_status init1() override;


   };



} // namespace userfs



