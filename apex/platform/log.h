#pragma once


namespace sockets
{

   class base_socket_handler;
   class base_socket;

}


namespace apex
{


   class CLASS_DECL_APEX log :
      virtual public ::object
   {
   public:


      bool                       m_bLog;
      bool                       m_bExtendedLog;
      bool                       m_bLogFileName;
      bool                       m_bLogFunctionName;
      bool                       m_bLogThreadName;


      bool                       m_bTrace;
      __composite(::apex::trace::trace) m_ptrace;
      ::mutex                    m_mutexTrace;
      string_array                    m_straSeparator;
      FILE *                     m_pfile;
      bool                       m_bInitialized;
      string                     m_strLogPath;
      id                         m_id;
      i32                        m_iYear;
      i32                        m_iMonth;
      i32                        m_iDay;


      log();
      virtual ~log();


      void load_flags(const ::property_set & set);


      virtual void print(const char * psz, ...);


      virtual ::estatus initialize_apex_log(e_trace_level etracelevelMin, const ::id & id);
      //virtual bool initialize(id id);
      virtual void finalize() override;

      virtual bool process_init();

      virtual void __tracea(::elemental * pcontextobject, e_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const char * psz) override;

      void set_trace_category(e_trace_category ecategory, e_trace_level elevelMin);

      virtual void success(const char * psz);

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();


   };


   CLASS_DECL_APEX i32 SimpleDebugReport(i32, const char *, i32, const char *, const char * pszFormat, va_list list);


} // namespace apex



