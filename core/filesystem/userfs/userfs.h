#pragma once


namespace userfs
{


   class CLASS_DECL_CORE userfs :
      virtual public ::apex::department
   {
   public:


      userfs();
      virtual ~userfs();

      virtual ::e_status initialize(::context_object * pcontextobject) override;

      virtual ::e_status init1() override;


   };



} // namespace userfs



