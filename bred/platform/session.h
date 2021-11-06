#pragma once


namespace bred
{


   class CLASS_DECL_BRED session :
      virtual public ::base::session
   {
   public:


      session();
      virtual ~session();

      void common_construct();


      virtual ::e_status initialize(::object * pobject) override;


      virtual void on_instantiate_application(::application* papp) override;


      //inline ::bred::user* user() { return m_puser ? m_puser->m_pbreduser : nullptr; }


   };


} // namespace base




