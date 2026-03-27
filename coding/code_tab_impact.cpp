#include "framework.h"
#include "code.h"
#include "code_tab_impact.h"
#include "code_impact.h"
//#include "code_options_impact_handler.h"
#include "coding/code_application.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/filesystem/file/memory_file.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/user/user/frame_interaction.h"


namespace coding
{


    tab_impact::tab_impact()
    {

        m_bSaveCurrentMode = false;

    }


    tab_impact::~tab_impact()
    {


    }


    void tab_impact::install_message_routing(::channel* pchannel)
    {

        ::user::tab_impact::install_message_routing(pchannel);

        USER_MESSAGE_LINK(::user::e_message_create, pchannel, this, &tab_impact::on_message_create);

    }


    void tab_impact::on_message_create(::message::message* pmessage)
    {

        if (pmessage->previous())
        {

            return;

        }

       add_tab("Options", APP_OPTIONS_IMPACT);
        add_tab("Initial Setup", as_domainid(e_mode_initial_setup));

        m_bSaveCurrentMode = false;

        set_current_tab_by_id(as_domainid(e_mode_initial_setup));

        m_bSaveCurrentMode = true;

        m_papp->fork([this]()
        {

            while(true)
            {

                try
                {

                    if(m_papp->defer_first_stage())
                    {

                        break;

                    }

                }
                catch(...)
                {


                }

                sleep(300_ms);

            }

        });

        m_papp->fork([this]()
        {

            m_papp->wait_first_stage();

            user_post([this]()
            {

                printf_line("Going to add more 3 tabs...");
                printf_line("Going to add more 3 tabs...");
                printf_line("Going to add more 3 tabs...");

                add_tab("Git Credential Manager", as_domainid(e_mode_gcm));
                add_tab("SSH", as_domainid(e_mode_ssh));
                add_tab("Cloud", as_domainid(e_mode_standard));

                auto emode = m_papp->get_code_mode();

                if (emode != e_mode_standard
                   && emode != e_mode_ssh
                   && emode != e_mode_gcm)
                {

                   emode = e_mode_gcm;

                }

                m_papp->set_code_mode(emode);
                   
                auto domainid = as_domainid(emode);

                m_bSaveCurrentMode = false;

                set_current_tab_by_id(domainid);

                m_bSaveCurrentMode = true;

                parent_frame()->m_bNeedPerformLayout = true;

                m_bNeedPerformLayout = true;

                parent_frame()->set_need_layout();

                set_need_layout();

                parent_frame()->set_need_redraw();

                set_need_redraw();

                parent_frame()->post_redraw();

            });

        });

    }


    void tab_impact::on_change_cur_sel()
    {

        ::user::tab_impact::on_change_cur_sel();

        if(m_bSaveCurrentMode && m_pimpactdata->id().get_type() == ::atom::e_type_domainid)
        {

            m_papp->set_code_mode((e_mode)m_pimpactdata->id().as_domainid());

        }

    }


    void tab_impact::on_create_impact(::user::impact_data* pimpactdata)
    {

//       if(pimpactdata->m_atom == "options")
//       {
//
//          create_impact<::coding::options_impact_handler>(pimpactdata);
//
//       }
       if (pimpactdata->id() == as_domainid(e_mode_initial_setup)
            || pimpactdata->id() == as_domainid(e_mode_ssh)
            || pimpactdata->id() == as_domainid(e_mode_gcm)
            || pimpactdata->id() == as_domainid(e_mode_standard))
        {

            create_impact<::coding::impact>(pimpactdata);

        }

        pimpactdata->m_eflag.set(::user::e_flag_hide_all_others_on_show);

        ::user::tab_impact::on_create_impact(pimpactdata);

    }


    void tab_impact::handle(::topic* ptopic, ::handler_context* phandlercontext)
    {

        if (ptopic->id() == ::id_click)
        {

            if (ptopic->user_interaction_id() == "integration_code")
            {

                m_papp->fork([this]()
                {

                    m_papp->code(m_papp->get_code_mode())->setup_coding();

                });

            }

        }

        ::user::tab_impact::handle(ptopic, phandlercontext);

    }



} // namespace coding



