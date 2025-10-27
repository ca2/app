// Created by camilo with mummys on 2025-10-21 13:40 <3ThomasBorregaardSørensen!!
#pragma once


CLASS_DECL_ACME::string _017Time(const class ::time& time);


class CLASS_DECL_ACME item_n40585
{
public:


   ::string          m_strPath;
   class ::time      m_timeGetHere;
   class ::time      m_timeLockElapsed;
   class ::time      m_timeLookUpElapsed;
   class ::time      m_timeLock2Elapsed;
   class ::time      m_timeShouldBuildElapsed;
   class ::time      m_timeCreateInstanceElapsed;
   class ::time      m_timeInit2Elapsed;
   class ::time      m_timeInit1Elapsed;
   class ::time      m_timeCreateInstanceStrictElapsed;

   ///class ::time      m_timeRealPathMapAllocationElapsed;
   class ::time      m_timeT1;
   class ::time      m_timeInitializeElapsed;
   class ::time      m_timeRunCreateElapsed;
   class ::time      m_timeCallCreateElapsed;
   class ::time      m_timeInitElapsed;
   class ::time      m_timeRunElapsed;

   item_n40585() { }
   item_n40585(
      const ::scoped_string& scopedstrName,
      const class ::time& timeGetHere,
      const class ::time& timeLockElapsed,
      const class ::time& timeLockUpElapsed,
      const class ::time& timeLock2Elapsed,
      const class ::time& timeShouldBuildElapsed
   );
   ~item_n40585();


   ::string as_string() const;
  

};


class CLASS_DECL_ACME information_n40585 :
   virtual public ::particle
{
public:


   ::array_base < item_n40585 > m_itema;

   
   class ::time         m_timeHandleRootHandleLocaleElapsed;
   class ::time         m_timeHandleRootPadding1Elapsed;
   class ::time         m_timeHandleRootRootInitElapsed;
   class ::time         m_timeHandleRootPadding2Elapsed;
   class ::time         m_timeHandleRootDateTimeElapsed;
   class ::time         m_timeHandleRootMainElapsed;
   class ::time         m_timeHandleRootSysIncludePathElapsed;
   class ::time         m_timeHandleRootOnBeforeIncludeElapsed;
   class ::time         m_timeHandleRootSiteOnBeforeIncludeElapsed;
   class ::time         m_timeHandleRootSubdomainOnBeforeIncludeElapsed;
   ::string             m_strHandleRootRootInit;
   ::string             m_strHandleRootRootInitSiteStandardRoot;
   ::string             m_strHandleRootSiteOnBeforeInclude;


   ::string as_string() const;

   ::string handle_locale_as_string() const;


};


CLASS_DECL_ACME::string as_string(const ::item_n40585& item);



