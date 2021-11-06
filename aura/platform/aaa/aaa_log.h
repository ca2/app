#pragma once


namespace sockets
{

   class base_socket_handler;
   class base_socket;

}


namespace aura
{


   class CLASS_DECL_AURA log :
      virtual public ::object
   {
   public:


      bool                       m_bLog;
      bool                       m_bExtendedLog;
      bool                       m_bLogFileName;
      bool                       m_bLogFunctionName;
      bool                       m_bLogThreadName;


      bool                       m_bTrace;
      __composite(::aura::trace::trace) m_ptrace;
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


      virtual void print(const ::string & psz, ...);


      virtual ::e_status initialize_aura_log(enum_trace_level etracelevelMin, const ::id & id);
      //virtual bool initialize(id id);
      virtual ::e_status destroy() override;

      virtual bool process_init();

      virtual void __tracea(::matter * pobject, enum_trace_level elevel, const ::string & pszFunction, const ::string & pszFileName, i32 iLine, const ::string & psz) override;

      void set_trace_category(e_trace_category ecategory, enum_trace_level elevelMin);

      virtual void success(const ::string & psz);

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();


   };


   CLASS_DECL_AURA i32 SimpleDebugReport(i32, const ::string &, i32, const ::string &, const ::string & pszFormat, va_list list);


} // namespace aura



