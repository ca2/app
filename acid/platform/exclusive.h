#pragma once





namespace acid
{


   class CLASS_DECL_ACID exclusive :
      virtual public ::particle
   {
   public:


      string                  m_strId;

// #ifdef WINDOWS

//       ::u32                   m_dwLastError;
//       bool                    m_bResourceException;

// #else

//       int                     m_iFile;
//       int                     m_iLock;

// #endif

      // ::pointer < ::mutex >     m_pmutex;


      //exclusive(::particle * pparticle, string str ARG_SEC_ATTRS_DEF);
      exclusive();
      ~exclusive() override;


      virtual bool exclusive_fails() const;


   };


} // namespace acid



