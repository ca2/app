//
// Created by camilo on 2024-06-05 16:32 <3ThomasBorregaardSorensen!!
//
#pragma once


#include "code_application.h"
#include "apex/platform/app_consumer.h"


namespace coding
{


    class CLASS_DECL_CODING code :
        virtual public app_consumer < ::coding::code_application >
    {
    public:


       ::map < ::coding::enum_install, ::pointer < ::coding::install > >   m_installmap;

       ::atom_map_base < ::pointer < ::coding::option > >   m_optionmap;


        ::coding::e_mode                          m_emode;

        ::numeric_array_base< ::coding::enum_install >      m_einstalla;

        //::pointer<::coding::impact>               m_pimpact;

        ::string                                            m_strMainStatus;
        ::string                                            m_strMainStatus2;
        ::string                                            m_strMayNeedRestartStatus;

        ::map < ::coding::enum_install, ::numeric_array_base< ::coding::enum_install > > m_einstallaDependency;

        // installations can be installed without a soft dependency,
        // but if the soft dependency is selected to install,
        // the depending installation will be done after the soft
        // dependency.
        ::map < ::coding::enum_install, ::numeric_array_base< ::coding::enum_install > > m_einstallaSoftDependency;
        ::atom_array m_atomaOptions;

        code();
        ~code() override;


        virtual void set_main_status1(const ::scoped_string& scopedstr);

        //::pointer < ::parallelization::queue > system_install_queue();
        //::pointer < ::parallelization::queue > download_queue();

        //
        //    virtual bool is_install_selected(::coding::enum_install einstall);
        //virtual void install_tool_windows();

        //virtual void install_app_simple();


#if TORTOISE_SVN
      void install_tortoise_svn();
#endif
#if SMART_SVN
      void install_smart_svn();
#endif
        void setup_coding();

        map < ::coding::enum_install, ::pointer < ::coding::install > >& install_map();

        ::coding::enum_install get_next(::coding::enum_install einstall);

        void install_main_item_type2(::coding::enum_install einstall);


        //virtual void defer_download_source(string strRepos, string strFolder);
        //virtual void add_download_source(string strRepos, string strFolder);
        //virtual void start_download_source();
        //bool is_installed_svn_command();
        //bool is_installed_smart_svn();
        //virtual void defer_start_installation(::coding::enum_install einstall);
        //::file::path download(enum_inst

        virtual void defer_sources();


        // virtual ::pointer<::user::multiple_option > create_option(
        //    const ::data::property & property,
        //    ::user::interaction* puserinteractionParent,
        //    const ::atom_array & atomaOptions,
        //    const ::string_array & straName);

        virtual void create_install(::coding::enum_install einstall, ::user::interaction* puserinteractionParent,
           const ::numeric_array_base<::coding::enum_install>& einstallaDependency,
           const ::numeric_array_base<::coding::enum_install>& einstallaSoftDependency = {});

    };


} // integration_code
