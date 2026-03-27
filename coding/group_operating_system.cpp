// Created by camilo on 2024-02-24 03:52 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "group_operating_system.h"


namespace coding
{


   group_operating_system::group_operating_system()
   {


   }


   group_operating_system::~group_operating_system()
   {

   }


   void group_operating_system::initialize_group_operating_system(const enum_integrate* pe, ::collection::count c)
   {

      m_eintegratea.assign(pe, c);

   }


   ::collection::count group_operating_system::get_size()
   {

      return m_eintegratea.size();

   }


   enum_integrate group_operating_system::get_eintegrate(::collection::index i)
   {

      return m_eintegratea[i];

   }


   ::string group_operating_system::get_name(::collection::index i)
   {

      switch (get_eintegrate(i))
      {
#ifdef WINDOWS
      case e_integrate_windows:
         return "Windows";
      case e_integrate_windows_port:
         return "Windows port";
      case e_integrate_windows_openssl:
         return "Windows OpenSSL";
      case e_integrate_windows_ffmpeg:
         return "Windows FFMPEG";
      case e_integrate_universal_windows_port:
         return "Universal Windows port";
      case e_integrate_universal_windows_openssl:
         return "Universal Windows OpenSSL";
      case e_integrate_universal_windows_ffmpeg:
         return "Universal Windows FFMPEG";
#endif
#ifdef LINUX
      case e_integrate_ubuntu:
         return "Ubuntu";
      case e_integrate_fedora:
         return "Fedora";
      case e_integrate_kubuntu:
         return "Kubuntu";
      case e_integrate_kfedora:
         return "Kfedora";
         case e_integrate_xubuntu:
            return "Xubuntu";
      case e_integrate_opensuse_tumbleweed:
         return "KopenSUSE";
      case e_integrate_opensuseg_tumbleweed:
         return "openSUSEg";
      case e_integrate_kmanjaro:
         return "KManjaro";
      case e_integrate_manjarog:
         return "Manjarog";
      case e_integrate_kdebian:
         return "KDebian";
      case e_integrate_debiang:
         return "Debiang";
#endif
#if defined(FREEBSD)
      case e_integrate_kfreebsd:
         return "KFreeBSD";
      case e_integrate_freebsdg:
         return "FreeBSDg";
#endif
#if defined(OPENBSD)
      case e_integrate_kopenbsd:
         return "KOpenBSD";
      case e_integrate_openbsdg:
         return "OpenBSDg";
#endif
#if defined(NETBSD)
      case e_integrate_knetbsd:
         return "KNetBSD";
      case e_integrate_netbsdg:
         return "NetBSDg";
#endif
#ifdef MACOS
      case e_integrate_macos:
         return "macOS";
      case e_integrate_macos_openssl:
         return "macOS OpenSSL";
      case e_integrate_macos_ffmpeg:
         return "macOS FFMPEG";
      case e_integrate_ios_openssl:
         return "iOS OpenSSL";
      case e_integrate_ios_ffmpeg:
         return "iOS FFMPEG";
#endif
      default:
         return "";
      }

   }


} // namespace integration_integration



