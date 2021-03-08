#pragma once


namespace core
{


   class CLASS_DECL_CORE session :
      virtual public ::bred::session
   {
   public:


      session();
      virtual ~session();

      void common_construct();


      virtual ::e_status initialize(::layered * pobjectContext) override;


      inline ::core::user* user() { return m_puser ? m_puser->m_pcoreuser : nullptr; }


   };


} // namespace core




