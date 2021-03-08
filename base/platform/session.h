#pragma once


namespace base
{


   class CLASS_DECL_BASE session:
      virtual public ::axis::session,
      virtual public ::user::document_manager_container
   {
   public:


      session();
      virtual ~session();


      virtual ::e_status initialize(::layered * pobjectContext) override;


      inline ::base::user* user() { return m_puser ? m_puser->m_pbaseuser : nullptr; }


   };


} // namespace base



