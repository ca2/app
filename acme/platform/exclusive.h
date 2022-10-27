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

      ::pointer < ::mutex >     m_pmutex;


      exclusive(::particle * pparticle, string str ARG_SEC_ATTRS_DEF);
      ~exclusive() override;


      bool exclusive_fails() const;


   };


} // namespace acme



