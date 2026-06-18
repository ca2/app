// Created by camilo on 2024-02-24 03:56 <3ThomasBorregaardSorensen!!
#pragma once


#include "group.h"


namespace coding
{


   class CLASS_DECL_CODING group_machine_box :
      virtual public group
   {
   public:


      string_array m_straMachineBox;


      group_machine_box();
      ~group_machine_box() override;


      virtual void initialize_group_machine_box(const ::string_array & straMachineBox);

      ::collection::count get_size() override;
      enum_integrate get_eintegrate(::collection::index i) override;
      ::string get_name(::collection::index i) override;
      ::string get_short_name(::collection::index i) override;

      ::file::path get_machine_path(const ::scoped_string& strMachineBox);
      ::file::path get_checkout_machine_path(const ::scoped_string& strMachineBox);


      virtual void do_session(const ::file::path& pathMachine, const ::scoped_string& strTopicThenPowerOff, const ::scoped_string& strTopicDoneThenPoweredOff, const ::scoped_string& scopedstrBlock = {});

      void integrate() override;
      virtual void start_box(const ::scoped_string& strMachineBox);
      virtual ::string get_box_slashed(const ::scoped_string& strMachineBox);
      virtual ::string get_box_slashed_operating_system_no_release(const ::string& str, const ::string& strOperatingSystem);
      virtual ::string get_box_slashed_distro(const ::string& str, const ::string& strDistro);
      virtual ::string get_box_slashed_distro_branch(const ::string& str, const ::string& strNick, const ::string& strDistro, const ::string& strBranch);


   };


} // namespace coding



