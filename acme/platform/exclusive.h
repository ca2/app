#pragma once


namespace acme
{


   class CLASS_DECL_ACME exclusive :
      virtual public ::generic
   {
   public:


      string                  m_strId;

#ifdef WINDOWS

      DWORD                   m_dwLastError;
      bool                    m_bResourceException;

#else

      int                     m_iFile;
      int                     m_iLock;

#endif

      __pointer(::mutex)      m_pmutex;


      exclusive(string str, LPSECURITY_ATTRIBUTES psa);
      virtual ~exclusive();


      bool exclusive_fails() const;


   };


} // namespace acme



