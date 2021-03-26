#pragma once


namespace dynamic_source
{


   class script_instance;


   class CLASS_DECL_APP_PROGRAMMING script_composite :
      virtual public script_interface
   {
   public:


      __pointer(script_interface)      m_pinterface;


      script_composite();
      virtual ~script_composite();


      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status finalize() override;

   };


} // namespace dynamic_source



