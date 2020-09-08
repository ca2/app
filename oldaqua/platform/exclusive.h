#pragma once


namespace aqua
{


   class exclusive :
      virtual public ::object
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


      exclusive(string str, LPSECURITY_ATTRIBUTES psa);
      virtual ~exclusive();


      bool exclusive_fails() const;


   };


} // namespace aqua



