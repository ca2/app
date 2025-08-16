#pragma once


//////#include "acme/exception/exception.h"


namespace file
{


   class CLASS_DECL_ACME exception :
      public ::exception
   {
   public:


   //   int                m_lOsError;
   //   int                  m_iErrNo;
   //   ::file::path         m_path;
   //   string               m_strAdd;
   //   ::file::e_open        m_eopen;


      exception(const ::e_status& estatus, const ::error_code& errorcode, const ::file::path& path, ::file::e_open eopen = {}, const ::scoped_string& strMessage = nullptr, const ::scoped_string& scopedstrDetails = nullptr);
   exception(const ::file::exception& exception);
   ~exception() override;

   ::pointer < ::subparticle > clone() override;

//      virtual ~exception();
//
//      virtual void dump(dump_context &) const;
//
//
//      virtual void     get_status();
//      virtual int get_os_error();
//      virtual string get_file_path();
//
//#ifdef WINDOWS
//      virtual bool get_error_message(string & str, unsigned int * pnHelpContext = nullptr);
//#endif
//
   };


   //using exception_pointer = ::pointer<exception>


   CLASS_DECL_ACME bool should_ignore_file_exception_callstack(const ::e_status& estatus);

   //CLASS_DECL_ACME void throw_exception(const ::e_status& estatus, int lOsError, int iErrNo, const ::file::path& path, ::file::e_open eopen);

   //CLASS_DECL_ACME void throw_::exception(const ::e_status& estatus, int lOsError, const ::file::path& path = nullptr);

   //CLASS_DECL_ACME void throw_stdio_exception(const ::e_status& estatus, int lDOSError, const ::file::path& path);

//#ifdef WINDOWS
//
//   CLASS_DECL_ACME void throw_os_error(DWORD dwError, const ::file::path& path = nullptr);
//
//#endif

   //CLASS_DECL_ACME void throw ::file::exception(errno_status(errno), (int iErrNo, const ::file::path& path = nullptr);

   CLASS_DECL_ACME int dos_to_os_error(int lDosErr);

   const_char_pointer status_short_description(const ::e_status& estatus);


} // namespace file



