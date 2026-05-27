#pragma once





namespace acme
{


   class CLASS_DECL_ACME exclusive :
      virtual public ::particle
   {
   public:


      string                  m_strId;

// #ifdef WINDOWS

//       ::u32                   m_dwLastError;
//       bool                    m_bResourceException;

// #else

//       ::i32                     m_iFile;
//       ::i32                     m_iLock;

// #endif

      // ::pointer < ::mutex >     m_pmutex;


      //exclusive(::particle * pparticle, const ::scoped_string & scopedstr ARG_SEC_ATTRS_DEF);
      exclusive();
      ~exclusive() override;


      virtual bool exclusive_fails() const;


   };


} // namespace acme



