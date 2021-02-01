#pragma once


namespace acme
{


   class CLASS_DECL_ACME exclusive :
      virtual public ::matter
   {
   public:


      string                  m_strId;

#ifdef WINDOWS

      ::u32                   m_dwLastError;
      bool                    m_bResourceException;

#else

      int                     m_iFile;
      int                     m_iLock;

#endif

      __pointer(::mutex)      m_pmutex;


      exclusive(string str ARG_SEC_ATTRS_DEF);
      virtual ~exclusive();


      bool exclusive_fails() const;


   };


} // namespace acme



