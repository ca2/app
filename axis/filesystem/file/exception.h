#pragma once


namespace file
{


   class CLASS_DECL_AURA exception :
      public ::io_exception
   {
   public:


      LONG              m_lOsError;
      int               m_iErrNo;
      ::file::path      m_path;
      string            m_strAdd;
      ::efileopen       m_efileopen;


      exception(const ::estatus & estatus = error_file, LONG lOsError = -1, int iErrNo = -1, const ::file::path & path = nullptr, const ::efileopen & efileopen = 0);

      virtual ~exception();

      virtual void dump(dump_context &) const;


      virtual ::estatus     get_status();
      virtual LONG get_os_error();
      virtual string get_file_path();

      virtual bool get_error_message(string & str, PUINT pnHelpContext = nullptr);


   };


   using exception_pointer = __pointer(exception);


   CLASS_DECL_AURA bool should_ignore_file_exception_callstack(const ::estatus & estatus);

   CLASS_DECL_AURA void throw_exception(const ::estatus& estatus, LONG lOsError, int iErrNo, const ::file::path& path, const ::efileopen& efileopen);

   CLASS_DECL_AURA void throw_status(const ::estatus& estatus, LONG lOsError, const ::file::path& path = nullptr);

   CLASS_DECL_AURA void throw_stdio_exception(const ::estatus& estatus, LONG lDOSError, const ::file::path& path);

   CLASS_DECL_AURA void throw_os_error(LONG lOsError, const ::file::path& path = nullptr);

   CLASS_DECL_AURA void throw_errno(int iErrNo, const ::file::path& path = nullptr);

   CLASS_DECL_AURA ::estatus os_error_to_status(LONG lOsError);

   CLASS_DECL_AURA ::estatus errno_to_status(i32 nErrno);

   CLASS_DECL_AURA int dos_to_os_error(int lDosErr);

   const char* status_message(const ::estatus& estatus);


} // namespace file



