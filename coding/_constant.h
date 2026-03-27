//
// Created by camilo on 05/03/23.
//
// enum_install from integration/code by camilo on
//     2024-05-04 04:09 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/prototype/domain_enumeration.h"


namespace coding
{

   enum enum_repository: int
   {

      e_repository_none,
      e_repository_tool_os,
      e_repository_simple,

   };


   enum enum_integrate_group : int
   {

      e_integrate_group_operating_system,
      e_integrate_group_third,
      e_integrate_group_machine_box,
      e_integrate_group_orhestration,

   };


   enum enum_integrate : long long
   {


      e_integrate_none = 0,
      e_integrate_all = -1,
      e_integrate_new_release_prefix = 1,
      e_integrate_main = 2,
      e_integrate_port = 3,
      e_integrate_machine_box = 4,
      e_integrate_netnode = 5,
      e_integrate_checkout_for_another_system = 6,
      e_integrate_openssl = 7,
      e_integrate_ffmpeg = 8,
      e_integrate_id_mask = 0xffff,

      // BRANCH FLAGS
      e_integrate_branch_microsoft = 1 << 16,
      e_integrate_branch_linux = 1 << 17,
      e_integrate_branch_apple = 1 << 18,
      e_integrate_branch_bsd = 1 << 19,

      // SYSTEM TYPE
      e_integrate_system_type_desktop = 1 << 20,
      e_integrate_system_type_mobile = 2 << 20,
      e_integrate_system_type_universal = 4 << 20,

      // SYSTEM
      e_integrate_system_windows = e_integrate_branch_microsoft | e_integrate_system_type_desktop,
      e_integrate_system_universal_windows = e_integrate_branch_microsoft | e_integrate_system_type_universal,
      e_integrate_system_macos = e_integrate_branch_apple | e_integrate_system_type_desktop,
      e_integrate_system_ios = e_integrate_branch_apple | e_integrate_system_type_mobile,

      /// LINUX DISTROS - Only ok with e_integrate_branch_linux
      e_integrate_distro_debian = 1 << 25,
      e_integrate_distro_ubuntu = 1 << 26,
      e_integrate_distro_fedora = 1 << 27,
      e_integrate_distro_opensuse_tumbleweed = 1 << 28,
      e_integrate_distro_manjaro = 1 << 29,

      /// BSD OPERATING SYSTEMS - Only ok with e_integrate_branch_bsd
      e_integrate_bsd_freebsd = 1 << 25,
      e_integrate_bsd_openbsd = 1 << 26,
      e_integrate_bsd_netbsd = 1ll << 27,

      // DESKTOP ENVIRONMENT FLAGS
      e_integrate_desktop_environment_none = 0,
      e_integrate_desktop_environment_gnome = 1 << 31,
      e_integrate_desktop_environment_kde = 1ll << 32,
      e_integrate_desktop_environment_xfce = 1ll << 33,

      e_integrate_windows = e_integrate_branch_microsoft | e_integrate_system_type_desktop | e_integrate_main,
      e_integrate_windows_port = e_integrate_system_windows | e_integrate_system_type_desktop | e_integrate_port,
      e_integrate_windows_openssl = e_integrate_system_windows | e_integrate_system_type_desktop | e_integrate_openssl,
      e_integrate_windows_ffmpeg = e_integrate_system_windows | e_integrate_system_type_desktop | e_integrate_ffmpeg,
      e_integrate_universal_windows_port = e_integrate_system_universal_windows | e_integrate_port,
      e_integrate_universal_windows_openssl = e_integrate_system_universal_windows | e_integrate_openssl,
      e_integrate_universal_windows_ffmpeg = e_integrate_system_universal_windows | e_integrate_ffmpeg,
      e_integrate_ubuntu = e_integrate_branch_linux | e_integrate_distro_ubuntu | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_fedora = e_integrate_branch_linux | e_integrate_distro_fedora | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_debiang = e_integrate_branch_linux | e_integrate_distro_debian | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_manjarog = e_integrate_branch_linux | e_integrate_distro_manjaro | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_opensuse_tumbleweed = e_integrate_branch_linux | e_integrate_distro_opensuse_tumbleweed | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_opensuseg_tumbleweed = e_integrate_branch_linux | e_integrate_distro_opensuse_tumbleweed | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_kdebian = e_integrate_branch_linux | e_integrate_distro_debian | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_kubuntu = e_integrate_branch_linux | e_integrate_distro_ubuntu | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_kfedora = e_integrate_branch_linux | e_integrate_distro_fedora | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_kmanjaro = e_integrate_branch_linux | e_integrate_distro_manjaro | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_xubuntu = e_integrate_branch_linux | e_integrate_distro_ubuntu | e_integrate_desktop_environment_xfce | e_integrate_main,
      e_integrate_macos = e_integrate_branch_apple | e_integrate_main,
      e_integrate_macos_openssl = e_integrate_system_macos | e_integrate_openssl,
      e_integrate_macos_ffmpeg = e_integrate_system_macos | e_integrate_ffmpeg,
      e_integrate_ios_openssl = e_integrate_system_ios | e_integrate_openssl,
      e_integrate_ios_ffmpeg = e_integrate_system_ios | e_integrate_ffmpeg,
      e_integrate_freebsdg = e_integrate_branch_bsd | e_integrate_bsd_freebsd | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_kfreebsd = e_integrate_branch_bsd | e_integrate_bsd_freebsd | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_openbsdg = e_integrate_branch_bsd | e_integrate_bsd_openbsd | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_kopenbsd = e_integrate_branch_bsd | e_integrate_bsd_openbsd | e_integrate_desktop_environment_kde | e_integrate_main,
      e_integrate_netbsdg = e_integrate_branch_bsd | e_integrate_bsd_netbsd | e_integrate_desktop_environment_gnome | e_integrate_main,
      e_integrate_knetbsd = e_integrate_branch_bsd | e_integrate_bsd_netbsd | e_integrate_desktop_environment_kde | e_integrate_main,


      e_integrate_uploading = INT_MAX / 2,
      e_integrate_finished = INT_MAX,


   };


   DECLARE_ENUMERATION(e_integrate, enum_integrate);

   enum enum_task : int
   {

      e_task_none,

      e_task_ordinal_0 = 0,
      e_task_ordinal_1 = 1,
      e_task_ordinal_2 = 2,
      e_task_ordinal_3 = 3,
      e_task_ordinal_4 = 4,
      e_task_ordinal_5 = 5,
      e_task_ordinal_6 = 6,
      e_task_ordinal_7 = 7,

      e_task_platform_win32 = 0,
      e_task_platform_multi_arch = 0,
      e_task_platform_x64 = 4,

      e_task_configuration_debug = 0,
      e_task_configuration_release = 1,
      e_task_configuration_static = 2,

      e_task_ordinal_mask = 7, 

      e_task_configuration_static_debug = e_task_configuration_static | e_task_configuration_debug,
      e_task_configuration_static_release = e_task_configuration_static | e_task_configuration_release,

      e_task_win32_debug = e_task_platform_win32 | e_task_configuration_debug,
      e_task_win32_release = e_task_platform_win32 | e_task_configuration_release,
      e_task_win32_static_debug = e_task_platform_win32 | e_task_configuration_static_debug,
      e_task_win32_static_release = e_task_platform_win32 | e_task_configuration_static_release,
      e_task_x64_debug = e_task_platform_x64 | e_task_configuration_debug,
      e_task_x64_release = e_task_platform_x64 | e_task_configuration_release,
      e_task_x64_static_debug = e_task_platform_x64 | e_task_configuration_static_debug,
      e_task_x64_static_release = e_task_platform_x64 | e_task_configuration_static_release,

      e_task_multi_arch_debug = e_task_platform_multi_arch | e_task_configuration_debug,
      e_task_multi_arch_release = e_task_platform_multi_arch | e_task_configuration_release,

      e_task_openssl = 0x0001 << 16,
      e_task_ffmpeg = 0x0002 << 16,
      e_task_ios_openssl = 0x0011 << 16,
      e_task_ios_ffmpeg = 0x0012 << 16,
      e_task_port = 0x0100 << 16,
      e_task_windows = 0x1000 << 16,
      e_task_macos = 0x1001 << 16,

      
      e_task_group_mask = 0xffff << 16,

      
      e_task_ffmpeg_win32_debug = e_task_ffmpeg | e_task_win32_debug,
      e_task_ffmpeg_win32_release = e_task_ffmpeg | e_task_win32_release,
      e_task_ffmpeg_win32_static_debug = e_task_ffmpeg | e_task_win32_static_debug,
      e_task_ffmpeg_win32_static_release = e_task_ffmpeg | e_task_win32_static_release,
      e_task_ffmpeg_x64_debug = e_task_ffmpeg | e_task_x64_debug,
      e_task_ffmpeg_x64_release = e_task_ffmpeg | e_task_x64_release,
      e_task_ffmpeg_x64_static_debug = e_task_ffmpeg | e_task_x64_static_debug,
      e_task_ffmpeg_x64_static_release = e_task_ffmpeg | e_task_x64_static_release,

      e_task_openssl_win32_debug = e_task_openssl | e_task_win32_debug,
      e_task_openssl_win32_release = e_task_openssl | e_task_win32_release,
      e_task_openssl_win32_static_debug = e_task_openssl | e_task_win32_static_debug,
      e_task_openssl_win32_static_release = e_task_openssl | e_task_win32_static_release,
      e_task_openssl_x64_debug = e_task_openssl | e_task_x64_debug,
      e_task_openssl_x64_release = e_task_openssl | e_task_x64_release,
      e_task_openssl_x64_static_debug = e_task_openssl | e_task_x64_static_debug,
      e_task_openssl_x64_static_release = e_task_openssl | e_task_x64_static_release,

      e_task_port_win32_debug = e_task_port | e_task_win32_debug,
      e_task_port_win32_release = e_task_port | e_task_win32_release,
      e_task_port_win32_static_debug = e_task_port | e_task_win32_static_debug,
      e_task_port_win32_static_release = e_task_port | e_task_win32_static_release,
      e_task_port_x64_debug = e_task_port | e_task_x64_debug,
      e_task_port_x64_release = e_task_port | e_task_x64_release,
      e_task_port_x64_static_debug = e_task_port | e_task_x64_static_debug,
      e_task_port_x64_static_release = e_task_port | e_task_x64_static_release,

   };


   enum enum_phase
   {
     
      e_phase_new_release_prefix,
      e_phase_checkout,
      e_phase_application_list,
      e_phase_prepare_applications,
      e_phase_project_list,
      e_phase_prepare_projects,
      e_phase_cmake,
      e_phase_clean,
      e_phase_count,
      
   };


   enum enum_install
   {

      
      e_install_none,


      e_install_cloud_data_provider,
      e_install_smart_git,
      e_install_patch_shell,
      e_install_deps,
      e_install_setup_folders,
      e_install_tool_os,


      e_install_windows_first = 100,
      e_install_visual_studio = e_install_windows_first,
      e_install_git_scm,
      e_install_tortoise_git,
      e_install_msys2,
      e_install_strawberry_perl,


      e_install_repository_first = 200,
      e_install_repositories,
      e_install_browser,


      e_install_linux_first = 400,
      e_install_git_credential_manager = e_install_linux_first,
      e_install_jetbrains_toolbox,
      e_install_jetbrains_clion,
      e_install_visual_studio_code,
      
      e_install_macos_first = 500,
      e_install_xcode = e_install_macos_first,

      e_install_storage_first = 900,
      e_install_storage_windows,
      e_install_storage_universal_windows,


   };


   CLASS_DECL_CODING enum_task as_task_group(enum_integrate eintegrate);


// } // namespace integration_integration
//
//
// namespace coding
// {


   enum enum_mode
   {

      e_mode_none,
      e_mode_initial_setup,
      e_mode_gcm,
      e_mode_ssh,
      e_mode_standard,


   };


   DECLARE_DOMAIN_ENUMERATION(e_mode, enum_mode, ::e_domain_1024);

   using code_map = ::map < e_mode, ::pointer < code > >;


} // namespace coding





