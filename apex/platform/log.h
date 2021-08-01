#pragma once


namespace sockets
{

   class base_socket_handler;
   class base_socket;

}


namespace apex
{


   class CLASS_DECL_APEX log :
      virtual public ::trace::log
   {
   public:




      bool                                m_bTrace;
      __composite(::trace::trace)         m_ptrace;
      ::mutex                             m_mutexTrace;
      string_array                        m_straSeparator;
      FILE *                              m_pfile;
      bool                                m_bInitialized;
      string                              m_strLogPath;
      id                                  m_id;
      i32                                 m_iYear;
      i32                                 m_iMonth;
      i32                                 m_iDay;


      log();
      virtual ~log();


      void load_flags(const ::property_set & set);


      //void print(const char * psz, ...) override;


      ::e_status initialize_log(enum_trace_level etracelevelMin, const ::id & id) override;

      //virtual bool initialize(id id);
      ::e_status destroy() override;

      ::e_status process_init() override;

      virtual void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const char * psz) const override;

      void set_trace_category(e_trace_category ecategory, enum_trace_level elevelMin);

      virtual void success(const char * psz);

      //void set_extended_log(bool bSet = true) override;


   };


   CLASS_DECL_APEX i32 SimpleDebugReport(i32, const char *, i32, const char *, const char * pszFormat, va_list list);


} // namespace apex



