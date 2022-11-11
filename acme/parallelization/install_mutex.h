// Created by camilo on 2021-08-31 14:49 BRT <3ThomasBS__!!
#pragma once


//#include "mutex.h"
//
//
//#ifdef WINDOWS_DESKTOP
//
//
//class security_attributes
//{
//public:
//
//   char sz[32]; // I hope it is enough to hold SECURITY_ATTRIBUTES;
//
//};
//
//
//class null_dacl_security_attributes
//{
//public:
//
//   security_attributes m_securityattributes;
//
//   security_attributes m_securitydescriptor;
//
//   null_dacl_security_attributes();
//
//};
//
//#endif
//
//
//
//namespace install
//{
//
//
//   class CLASS_DECL_ACME mutex :
//#ifdef WINDOWS_DESKTOP
//      public null_dacl_security_attributes,
//#endif
//      public ::pointer < ::mutex >
//   {
//   public:
//
//      mutex(::particle * pparticle, string strPlatform, string strSuffix = "");
//
//   };
//
//
//   class CLASS_DECL_ACME admin_mutex :
//#ifdef WINDOWS_DESKTOP
//      public null_dacl_security_attributes,
//#endif
//      public ::pointer < ::mutex >
//   {
//   public:
//
//      admin_mutex(::particle * pparticle, string strPlatform, string strSuffix = "");
//
//   };
//
//
//} // namespace install
//
//
//
