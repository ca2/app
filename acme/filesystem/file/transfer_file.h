#pragma once


namespace file
{


   class CLASS_DECL_ACME transfer_file :
      virtual public ::file::reference
   {
   public:


      ::pointer<::file::timeout_file>      m_pointimeoutfile;
      ::pointer<memory_base>    m_pmemory;
      ::pointer<::memory_file>       m_pmemoryfileIn;
      ::pointer<::memory_file>       m_pmemoryfileOut;
      ::pointer < ::mutex >                        m_spmutex;


      transfer_file(::particle * pparticle, ::pointer< ::mutex > pmutex = nullptr);
      transfer_file(::particle * pparticle, ::memory_file * pmemoryfileIn);
      virtual ~transfer_file();


      //      virtual filesize seek(filesize lOff, ::enum_seek eseek);
      //    virtual filesize get_length() const;


   };


} // namespace file



