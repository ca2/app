#pragma once


namespace calculator
{


   class CLASS_DECL_SPHERE department :
      virtual public ::aura::department
   {
   public:


      department(::object * pobject);
      virtual ~department();


      virtual ::estatus init_instance() override;



   };


} // namespace calculator






