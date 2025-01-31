#include "framework.h"
#include "save_as_impact.h"
#include "save_as_button_impact.h"
#include "save_as_edit_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/file_system.h"
//#include "acme/handler/sequence.h"
#include "acme/platform/system.h"
#include "acme/user/micro/user.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/context.h"
#include "aura/user/user/frame_interaction.h"


namespace filemanager
{


   save_as_impact::save_as_impact()
   {



   }


   save_as_impact::~save_as_impact()
   {


   }


   void save_as_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::split_impact::install_message_routing(pchannel);

   }


   void save_as_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::user::impact::handle(ptopic, pcontext);

      ////__update(::update)
      {

         if (ptopic->id() == id_topic_saved)
         {

            if (top_level_frame()->m_bModal)
            {

               top_level_frame()->set_dialog_result("yes");

            }

         }
         else if (ptopic->id() == id_topic_save_failed)
         {

            if (top_level_frame()->m_bModal)
            {

               top_level_frame()->set_dialog_result("no");

            }

         }
         else if (ptopic->m_puserelement == this && ptopic->id() == id_initialize)
         {
            //            filemanager_document() = pupdate->filemanager_document();
            /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                        AddClient(this);
                        SetDataInterface(&m_datainterface);
                        AddClient(&m_datainterface);
                        string str;
                        str.formatf("file_list(%d,%d)", get_document()->m_iTemplate, get_document()->m_iDocument);
                        if(get_document()->m_bTransparentBackground)
                        {
                        ::user::list::m_etranslucency = ::user::list::e_translucency_present;
                        }
                        DISetSection(str);
                        _001UpdateColumns();*/
         }
         else if (ptopic->id() == id_filter)
         {
            /*if(ptopic->payload(id_filter).is_empty())
            {
            FilterClose();
            }
            else
            {
            FilterBegin();
            Filter1(ptopic->payload(id_filter));
            FilterApply();
            }*/
         }

      }

   }


   void save_as_impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.8);

      initialize_split_layout();

      m_pedit = create_pane_impact < save_as_edit_impact >(0);

      if (!m_pedit)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      m_pbutton = create_pane_impact < save_as_button_impact >(1);

      m_pbutton->set_window_text("Save");

   }


} // namespace filemanager



