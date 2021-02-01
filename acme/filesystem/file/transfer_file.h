#pragma once


namespace file
{


   class CLASS_DECL_ACME transfer_file :
      virtual public ::file::reference
   {
   public:


      __pointer(::file::timeout_file)       m_pointimeoutfile;
      __pointer(memory_base)     m_pmemory;
      __pointer(::memory_file)        m_pmemoryfileIn;
      __pointer(::memory_file)        m_pmemoryfileOut;
      ::mutex                        m_spmutex;


      transfer_file(::matter * pobject, ::mutex * pmutex = nullptr);
      transfer_file(::matter * pobject, ::memory_file * pmemoryfileIn);
      virtual ~transfer_file();


      //      virtual filesize seek(filesize lOff, ::file::e_seek  nFrom);
      //    virtual filesize get_length() const;


   };


} // namespace file



