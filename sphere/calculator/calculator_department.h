#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE department :
      virtual public ::apex::department
   {
   public:


      department(::layered * pobjectContext);
      virtual ~department();


      virtual ::e_status init_instance() override;



   };


} // namespace calculator






