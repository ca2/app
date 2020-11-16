#pragma once


namespace file
{


   class CLASS_DECL_ACME exception :
      public ::io_exception
   {
   public:


      ::i32              m_lOsError;
      int               m_iErrNo;
      ::file::path      m_path;
      string            m_strAdd;
      ::efileopen       m_efileopen;


      exception(const ::estatus & estatus = error_file, ::i32 lOsError = -1, int iErrNo = -1, const ::file::path & path = nullptr, const ::efileopen & efileopen = 0);

      virtual ~exception();

      virtual void dump(dump_context &) const;


      virtual ::estatus     get_status();
      virtual ::i32 get_os_error();
      virtual string get_file_path();

#ifdef WINDOWS
      virtual bool get_error_message(string & str, PUINT pnHelpContext = nullptr);
#endif

   };


   using exception_pointer = __pointer(exception);


   CLASS_DECL_ACME bool should_ignore_file_exception_callstack(const ::estatus & estatus);

   CLASS_DECL_ACME void throw_exception(const ::estatus& estatus, ::i32 lOsError, int iErrNo, const ::file::path& path, const ::efileopen& efileopen);

   CLASS_DECL_ACME void throw_status(const ::estatus& estatus, ::i32 lOsError, const ::file::path& path = nullptr);

   CLASS_DECL_ACME void throw_stdio_exception(const ::estatus& estatus, ::i32 lDOSError, const ::file::path& path);

#ifdef WINDOWS

   CLASS_DECL_ACME void throw_os_error(DWORD dwError, const ::file::path& path = nullptr);

#endif

   CLASS_DECL_ACME void throw_errno(int iErrNo, const ::file::path& path = nullptr);

   CLASS_DECL_ACME ::estatus errno_to_status(i32 nErrno);

   CLASS_DECL_ACME int dos_to_os_error(int lDosErr);

   const char* status_message(const ::estatus& estatus);


} // namespace file



