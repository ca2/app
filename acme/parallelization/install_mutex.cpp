// Created by camilo on 2021-08-31 14:49 BRT <3ThomasBS__!!
#include "framework.h"
#include "install_mutex.h"
#include "acme/_operating_system.h"


//namespace install
//{
//
//
//   mutex::mutex(::particle * pparticle, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrSuffix) :
//#ifdef WINDOWS_DESKTOP
//      ::mutex(pmatter, false, "Global\\::ca2::account::ccwarehouse::install::" + strPlatform + "::200010001951042219770204-11dd-ae16-0800200c7784" + strSuffix, &((SECURITY_ATTRIBUTES &)m_securityattributes))
//      , synchronization("Global\\::ca2::account::ccwarehouse::install::" + strPlatform + "::200010001951042219770204-11dd-ae16-0800200c7784" + strSuffix)
//#else
//      ::mutex(pparticle, false, "Global\\::ca2::account::ccwarehouse::spa::" + strPlatform + "::200010001951042219770204-11dd-ae16-0800200c7784" + strSuffix)
//#endif
//   {
//
//   }
//
//
//   admin_mutex::admin_mutex(::particle * pparticle, const ::scoped_string & scopedstrPlatform, const ::scoped_string & scopedstrSuffix) :
//#ifdef WINDOWS_DESKTOP
//      mutex(pmatter, false, "Global\\::ca2::account::ccwarehouse::" + strPlatform + "::200010001951042219770204-11dd-ae16-0800200c7784" + strSuffix, &((SECURITY_ATTRIBUTES &)m_securityattributes))
//#else
//      mutex(pparticle, false, "Global\\::ca2::account::ccwarehouse::" + strPlatform + "::200010001951042219770204-11dd-ae16-0800200c7784" + strSuffix)
//#endif
//   {
//
//   }
//
//
//} // namespace install



//
//#ifdef WINDOWS_DESKTOP
//
//null_dacl_security_attributes::null_dacl_security_attributes()
//{
//
//   zero(((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes)));
//
//   ((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes)).nLength = sizeof(((SECURITY_ATTRIBUTES &)m_securityattributes));
//
//   ((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes)).bInheritHandle = false; // matter uninheritable
//
//   // declare and initialize a security descriptor
//   zero(((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes)));
//
//   bool bInitOk = InitializeSecurityDescriptor(&((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes)), SECURITY_DESCRIPTOR_REVISION) != false;
//
//   if (bInitOk)
//   {
//      // give the security descriptor a Null Dacl
//      // done using the  "true, (PACL)nullptr" here
//      bool bSetOk = SetSecurityDescriptorDacl(&((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes)), true, (PACL)nullptr, false) != false;
//
//      if (bSetOk)
//      {
//
//         ((SECURITY_ATTRIBUTES &)m_securityattributes).lpSecurityDescriptor = &((SECURITY_ATTRIBUTES &)((SECURITY_ATTRIBUTES &)m_securityattributes));
//
//
//      }
//
//   }
//
//}
//
//#endif
//
//

