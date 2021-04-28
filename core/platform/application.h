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

      inline ::core::application* get_application() const { return m_pcoreapplication; }
      inline ::core::session* get_session() const { return m_pcoresession; }
      inline ::core::system* get_system() const { return m_pcoresystem; }
      inline ::core::user* user() const;



      virtual ::e_status initialize(::object * pobject) override;
      virtual __pointer(progress_control) show_progress(::user::interaction* puiParent, const char* pszTitle, ::count iProgressCount);

   };


} // namespace core




