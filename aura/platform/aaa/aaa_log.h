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
      ::pointer<::aura::trace::trace>m_ptrace;
      ::pointer < ::mutex >                    m_pmutexTrace;
      string_array                    m_straSeparator;
      FILE *                     m_pfile;
      bool                       m_bInitialized;
      string                     m_strLogPath;
      atom                         id();
      int                        m_iYear;
      int                        m_iMonth;
      int                        m_iDay;


      log();
      virtual ~log();


      void load_flags(const ::property_set & set);


      virtual void print(const ::scoped_string & scopedstr, ...);


      virtual void initialize_aura_log(enum_trace_level etracelevelMin, const ::atom & atom);
      //virtual bool initialize(atom atom);
      virtual void destroy() override;

      virtual bool process_init();

      virtual void __tracea(::particle * pparticle, enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::scoped_string & scopedstrFileName, int iLine, const ::scoped_string & scopedstr) override;

      void set_trace_category(e_trace_category ecategory, enum_trace_level elevelMin);

      virtual void success(const ::scoped_string & scopedstr);

      virtual void set_extended_log(bool bSet = true);
      virtual bool get_extended_log();


   };


   CLASS_DECL_AURA int SimpleDebugReport(int, const ::string &, int, const ::string &, const ::scoped_string & scopedstrFormat, va_list list);


} // namespace aura



