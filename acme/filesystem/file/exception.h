#pragma once


#include "acme/exception/exception.h"


namespace file
{


   class CLASS_DECL_ACME exception :
      public ::exception
   {
   public:


   //   ::i32                m_lOsError;
   //   int                  m_iErrNo;
   //   ::file::path         m_path;
   //   string               m_strAdd;
   //   ::file::e_open        m_eopen;


   exception(const ::e_status & estatus, const ::error_code & errorcode, const ::file::path & path, const ::string & strMessage, const ::file::e_open & eopen = e_null, const ::string & strDetails = "");

//      virtual ~exception();
//
//      virtual void dump(dump_context &) const;
//
//
//      virtual void     get_status();
//      virtual ::i32 get_os_error();
//      virtual string get_file_path();
//
//#ifdef WINDOWS
//      virtual bool get_error_message(string & str, unsigned int * pnHelpContext = nullptr);
//#endif
//
   };


   //using exception_pointer = ::pointer<exception>


   CLASS_DECL_ACME bool should_ignore_file_exception_callstack(const ::e_status& estatus);

   //CLASS_DECL_ACME void throw_exception(const ::e_status& estatus, ::i32 lOsError, int iErrNo, const ::file::path& path, const ::file::e_open & eopen);

   //CLASS_DECL_ACME void throw_::exception(const ::e_status& estatus, ::i32 lOsError, const ::file::path& path = nullptr);

   //CLASS_DECL_ACME void throw_stdio_exception(const ::e_status& estatus, ::i32 lDOSError, const ::file::path& path);

//#ifdef WINDOWS
//
//   CLASS_DECL_ACME void throw_os_error(DWORD dwError, const ::file::path& path = nullptr);
//
//#endif

   //CLASS_DECL_ACME void throw ::file::exception(errno_to_status(errno), (int iErrNo, const ::file::path& path = nullptr);

   CLASS_DECL_ACME int dos_to_os_error(int lDosErr);

   const char* status_short_description(const ::e_status& estatus);


} // namespace file



