#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE department :
      virtual public ::acme::department
   {
   public:


      department(::object * pobject);
      virtual ~department();


      virtual void init_instance() override;



   };


} // namespace calculator






