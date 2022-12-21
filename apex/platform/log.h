#pragma once


#include "acme/platform/log.h"
//#include "acme/primitive/collection/string_array.h"


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
      ::pointer<::trace>               m_ptrace;
      ::pointer < ::mutex >                             m_pmutexTrace;
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


      //void print(const ::scoped_string & scopedstr, ...) override;


      void initialize_log(enum_trace_level etracelevelMin, const ::atom & atom) override;

      //virtual bool initialize(atom atom);
      void destroy() override;

      void process_init() override;

      //virtual void __tracea(enum_trace_level elevel, const ::scoped_string & scopedstrFunction, const ::file::path & path, i32 iLine, const ::scoped_string & scopedstr) const override;

      void set_trace_category(enum_trace_category etracecategory, enum_trace_level etracelevelMinimum);

      virtual void success(const ::scoped_string & scopedstr);

      //void set_extended_log(bool bSet = true) override;


   };


   CLASS_DECL_APEX i32 SimpleDebugReport(i32, const char *, i32, const char *, const ::scoped_string & scopedstrFormat, va_list list);


} // namespace apex



