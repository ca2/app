#pragma once


namespace sockets
{

   class base_socket_handler;
   class base_socket;

}


namespace apex
{


   class CLASS_DECL_APEX log :
      virtual public ::log
   {
   public:




      bool                                m_bTrace;
      __composite(::trace)                m_ptrace;
      ::mutex                             m_mutexTrace;
      string_array                        m_straSeparator;
      FILE *                              m_pfile;
      bool                                m_bInitialized;
      string                              m_strLogPath;
      atom                                  m_atom;
      i32                                 m_iYear;
      i32                                 m_iMonth;
      i32                                 m_iDay;


      log();
      virtual ~log();


      void load_flags(const ::property_set & set);


      //void print(const char * psz, ...) override;


      void initialize_log(enum_trace_level etracelevelMin, const ::atom & atom) override;

      //virtual bool initialize(atom atom);
      void destroy() override;

      void process_init() override;

      //virtual void __tracea(enum_trace_level elevel, const char * pszFunction, const char * pszFileName, i32 iLine, const char * psz) const override;

      void set_trace_category(enum_trace_category etracecategory, enum_trace_level etracelevelMinimum);

      virtual void success(const char * psz);

      //void set_extended_log(bool bSet = true) override;


   };


   CLASS_DECL_APEX i32 SimpleDebugReport(i32, const char *, i32, const char *, const char * pszFormat, va_list list);


} // namespace apex



