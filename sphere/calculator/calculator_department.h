#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE department :
      virtual public ::acme::department
   {
   public:


      department(::object * pobject);
      virtual ~department();


      virtual ::e_status init_instance() override;



   };


} // namespace calculator






