#pragma once


namespace aura
{


   class exclusive :
      virtual public ::object
   {
   public:


      string                  m_strId;

#ifdef WINDOWS

      ::u32                   m_dwLastError;
      bool                    m_bResourceException;

#else

      ::i32                     m_iFile;
      ::i32                     m_iLock;

#endif


      exclusive(string str, LPSECURITY_ATTRIBUTES psa);
      virtual ~exclusive();


      bool exclusive_fails() const;


   };


} // namespace aura



