// Created by camilo on 2024-02-24 03:59 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "application.h"
#include "group_machine_box.h"
#include "impact_interface.h"
#include "integration.h"
#include "item.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/operating_system/summary.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/platform/node.h"
#include "acme/prototype/prototype/url.h"
#include "aura/user/user/still.h"


namespace coding
{


   group_machine_box::group_machine_box()
   {

   }


   group_machine_box::~group_machine_box()
   {

   }


   void group_machine_box::initialize_group_machine_box(const ::string_array & straMachineBox)
   {

      m_straMachineBox = straMachineBox;

   }


   ::collection::count group_machine_box::get_size()
   {

      return m_straMachineBox.size();

   }


   ::coding::enum_integrate group_machine_box::get_eintegrate(::collection::index i)
   {

      return e_integrate_machine_box;

   }


   ::string group_machine_box::get_name(::collection::index i)
   {

      return m_straMachineBox[i];

   }


   ::string group_machine_box::get_short_name(::collection::index i)
   {

      auto strBoxSlashed = get_box_slashed(get_machine_path(get_name(i)));

      return strBoxSlashed;

   }


   void group_machine_box::do_session(const ::file::path & pathMachine, const ::scoped_string& strTopicThenPowerOff, const ::scoped_string& strTopicDoneThenPoweredOff, const ::scoped_string & scopedstrBlock)
   {

      ::string strSlashed = get_box_slashed(pathMachine);

      if (strSlashed.is_empty())
      {

         throw ::exception(::error_failed);

      }

      ::file::path pathBoxHostIntegration;

      pathBoxHostIntegration = node()->get_default_base_integration_folder();

      pathBoxHostIntegration /= strSlashed;

      ::file::path pathParentIntegration;

      pathParentIntegration = pathBoxHostIntegration / "parent_integration.txt";

      ::file::path pathSlashedParent;

      pathSlashedParent = "_____";

      pathSlashedParent /= node()->operating_system_summary()->m_strSystemAmbientReleaseArchitecture;

      file_system()->put_block(pathParentIntegration, pathSlashedParent);

      ::file::path pathTopicThenPowerOff;

      pathTopicThenPowerOff = pathBoxHostIntegration / strTopicThenPowerOff;

      auto pathTopicDoneThenPoweredOff = pathBoxHostIntegration / strTopicDoneThenPoweredOff;

      file_system()->defer_erase(pathTopicDoneThenPoweredOff);

      auto pathChildStatus = pathBoxHostIntegration / "main_status.txt";

      file_system()->defer_erase(pathChildStatus);

      file_system()->put_block(pathTopicThenPowerOff, scopedstrBlock);

      ::string strMainStatus;

      //strMainStatus = "machine_box:" + strSlashed;

      strMainStatus = strSlashed;

      m_pintegration->main_status(strMainStatus);

      start_box(pathMachine);

      ::string strChildStatusPrefix;

      strChildStatusPrefix = strSlashed;

      strChildStatusPrefix += ":";

      ::string strChildStatus;

      while (true)
      {

         if (file_system()->exists(pathTopicDoneThenPoweredOff))
         {

            break;

         }

         preempt(1_s);

         string strStatus;

         strStatus = file_system()->as_string(pathChildStatus);

         strStatus.case_insensitive_begins_eat(strChildStatusPrefix);

         m_pitem->m_pstillStatus->set_window_text(strStatus);

         m_pintegration->m_pimpactinterface->set_topic_text2(strStatus);

         if (strChildStatus != strStatus)
         {

            strChildStatus = strStatus;

            _synchronous_lock synchronouslock(m_pintegration->synchronization());

            m_pintegration->m_straLine3.add_item(strChildStatus);

            m_pintegration->m_pimpactinterface->on_lines_change();

         }

      }

   }


   void group_machine_box::integrate()
   {

      ::string strMachineBox;

      strMachineBox = m_pitem->m_strName1;

      strMachineBox.trim();

      auto pathCheckoutMachine = get_checkout_machine_path(strMachineBox);

      auto pathMachine = get_machine_path(strMachineBox);

      if (pathCheckoutMachine.has_character())
      {

         m_pintegration->main_status("Starting Machine for Checkout \""+pathCheckoutMachine+"\"...");

         ::string strAnotherSystem = get_box_slashed(pathMachine);

         do_session(
            pathCheckoutMachine,
            "checkout_then_power_off.txt",
            "checkout_then_powered_off.txt",
            strAnotherSystem);

      }

      if (pathMachine.has_character())
      {

         m_pintegration->main_status("Starting Machine for Building \"" + pathMachine + "\"...");

         do_session(
            pathMachine,
            "build_then_power_off.txt",
            "built_then_powered_off.txt");

      }

      //::string strSlashed = get_box_slashed(get_machine_path(strMachineBox));

      //if (strSlashed.is_empty())
      //{

      //   throw ::exception(::error_failed);

      //}

      //::file::path pathBoxHostIntegration;

      //pathBoxHostIntegration = "C:/integration/_____";

      //pathBoxHostIntegration /= strSlashed;

      //::file::path pathParentIntegration;

      //pathParentIntegration = pathBoxHostIntegration / "parent_integration.txt";

      //::file::path pathSlashedParent;

      //pathSlashedParent = "_____";

      //pathSlashedParent /= node()->operating_system_summary()->m_strSlashedIntegration;

      //file_system()->put_block(pathParentIntegration, pathSlashedParent);


      //file_system()->defer_erase(pathBuiltThenPoweredOff);

      //auto pathChildStatus = pathBoxHostIntegration / "main_status.txt";

      //file_system()->defer_erase(pathChildStatus);

      //file_system()->touch(pathBuildThenPowerOff);

      //::string strMainStatus;

      ////strMainStatus = "machine_box:" + strSlashed;

      //strMainStatus = strSlashed;

      //m_pintegration->main_status(strMainStatus);

      //start_box(strMachineBox);

      //::string strChildStatusPrefix;

      //strChildStatusPrefix = strSlashed;

      //strChildStatusPrefix += ":";

      //::string strChildStatus;

      //while (true)
      //{

      //   if (file_system()->exists(pathBuiltThenPoweredOff))
      //   {

      //      break;

      //   }

      //   preempt(1_s);

      //   string strStatus;

      //   strStatus = file_system()->as_string(pathChildStatus);

      //   strStatus.case_insensitive_begins_eat(strChildStatusPrefix);

      //   m_pitem->m_pstillStatus->set_window_text(strStatus);

      //   m_pintegration->m_pimpactinterface->set_topic_text2(strStatus);

      //   if (strChildStatus != strStatus)
      //   {

      //      strChildStatus = strStatus;

      //      _synchronous_lock synchronouslock(m_pintegration->synchronization());

      //      m_pintegration->m_straLine2.add_item(strChildStatus);

      //      m_pintegration->m_pimpactinterface->on_lines_change();

      //   }

      //}

   }


   ::string group_machine_box::get_box_slashed_distro(const ::string& str, const ::string& strDistro)
   {

      auto find = str.find("-" + strDistro + "-");

      if (!find)
      {

         return {};

      }

      ::string strRelease = str;

      strRelease.truncate(find);

      strRelease.find_replace("-", ".");

      return strDistro + "/" + strRelease;

   }


   ::string group_machine_box::get_box_slashed_operating_system_no_release(const ::string& str, const ::string& strOperatingSystem)
   {

      auto find = str.find("-" + strOperatingSystem + "-");

      if (!find)
      {

         auto prefix = strOperatingSystem + "-";

         if (!str.case_insensitive_begins(prefix))
         {

            return {};

         }

         find = str.c_str();

      }

      ::string strRelease = str;

      strRelease.truncate(find);

      strRelease.find_replace("-", ".");

      //return strDistro + "/" + strRelease;

      return strOperatingSystem;

   }


   ::string group_machine_box::get_box_slashed_distro_branch(const ::string& str, const ::string& strNick, const ::string& strDistro, const ::string& strBranch)
   {

      auto find = str.find("-" + strNick + "-");

      if (!find)
      {

         auto prefix = strNick + "-";

         if (!str.case_insensitive_begins(prefix))
         {

            return {};

         }

         find = str.c_str();

      }

      ::string strRelease = str;

      strRelease.truncate(find);

      strRelease.find_replace("-", ".");

      if (strRelease.has_character())
      {

         return strDistro + "/" + strBranch + "/" + strRelease;

      }
      else
      {

         return strDistro + "/" + strBranch;

      }

   }


   ::file::path group_machine_box::get_machine_path(const ::scoped_string& strMachineBox)
   {

      auto strName = strMachineBox();

      auto findComma = strName.rear_find(',');

      if (findComma)
      {

         strName.begin() = findComma + 1;
         strName.m_erange = e_range_none;

      }

      return strName;

   }


   ::file::path group_machine_box::get_checkout_machine_path(const ::scoped_string& strMachineBox)
   {

      auto strName = strMachineBox;

      ::string strPrefix("checkout:");

      auto findCheckout = strName.find(strPrefix);

      if (!findCheckout)
      {

         return {};

      }

      auto rangeCheckout = strName(findCheckout + strPrefix.length());

      auto findComma = rangeCheckout.find(',');

      if (!findComma)
      {

         return {};

      }

      rangeCheckout.m_end = findComma;

      return rangeCheckout;

   }


   ::string group_machine_box::get_box_slashed(const ::scoped_string& scopedstrMachineBox)
   {

      ::file::path pathVmx(scopedstrMachineBox);

      ::string str = pathVmx.name();

      str.case_insensitive_ends_eat(".vmx");

      ::string strSlashed;

      strSlashed = get_box_slashed_distro(str, "ubuntu");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro(str, "kubuntu");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro(str, "xubuntu");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "fedora", "fedora", "workstation");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "kfedora", "fedora", "kde");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "debiang", "debian", "gnome");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "kdebian", "debian", "kde");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "opensuse", "opensuse-tumbleweed", "kde");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "opensuseg", "opensuse-tumbleweed", "gnome");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "kmanjaro", "manjaro", "kde");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "manjarog", "manjaro", "gnome");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_operating_system_no_release(str, "macos");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "freebsdg", "freebsd", "gnome");

      if (strSlashed.has_character()) return strSlashed;

      strSlashed = get_box_slashed_distro_branch(str, "kfreebsd", "freebsd", "gnome");

      if (strSlashed.has_character()) return strSlashed;

      return {};

   }


   void group_machine_box::start_box(const ::scoped_string& scopedstrMachineBox)
   {

      ::string strMachine;

      strMachine = scopedstrMachineBox;

      strMachine.trim();

      if (strMachine.case_insensitive_ends(".vmx"))
      {

         //strMachine.find_replace("\\", "\\\\");

         node()->command_system("\"C:\\Program Files (x86)\\VMware\\VMware Workstation\\vmrun.exe\" -T ws start \"" + strMachine + "\"", 5_minutes);

      }

   }


} // namespace coding



