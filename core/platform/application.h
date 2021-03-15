#pragma once


namespace core
{


   class CLASS_DECL_CORE application :
      virtual public ::bred::application
   {
   public:


      application();
      virtual ~application();

      void common_construct();

      inline ::core::application* get_application() const { return m_papplication ? m_papplication.cast < ::core::application >() : nullptr; }
      inline ::core::session* get_session() const { return m_psession ? m_psession.cast < ::core::session >() : nullptr; }
      inline ::core::system* get_system() const;
      inline ::core::user* user() const;



      virtual ::e_status initialize(::context_object * pcontextobject) override;
      virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

   };


} // namespace core




