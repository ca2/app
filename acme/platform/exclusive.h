#pragma once





namespace acme
{


   class CLASS_DECL_ACME exclusive :
      virtual public ::particle
   {
   public:


      string                  m_strId;

// #ifdef WINDOWS

//       unsigned int                   m_dwLastError;
//       bool                    m_bResourceException;

// #else

//       int                     m_iFile;
//       int                     m_iLock;

// #endif

      // ::pointer < ::mutex >     m_pmutex;


      //exclusive(::particle * pparticle, const ::scoped_string & scopedstr ARG_SEC_ATTRS_DEF);
      exclusive();
      ~exclusive() override;


      virtual bool exclusive_fails() const;


   };


} // namespace acme



