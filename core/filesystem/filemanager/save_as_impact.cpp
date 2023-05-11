#include "framework.h"
#include "save_as_impact.h"
#include "save_as_button_impact.h"
#include "save_as_edit_impact.h"
#include "data.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/platform/context.h"
#include "acme/filesystem/file/item.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/platform/sequencer.h"
#include "acme/platform/system.h"
#include "acme/user/nano/nano.h"
#include "apex/filesystem/filesystem/dir_context.h"
#include "apex/filesystem/filesystem/file_context.h"
#include "apex/filesystem/fs/data.h"
#include "apex/platform/context.h"
#include "aura/user/user/frame.h"


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

         if (ptopic->m_atom == id_topic_saved)
         {

            if (top_level_frame()->m_bModal)
            {

               top_level_frame()->EndModalLoop("yes");

            }

         }
         else if (ptopic->m_atom == id_topic_save_failed)
         {

            if (top_level_frame()->m_bModal)
            {

               top_level_frame()->EndModalLoop("no");

            }

         }
         else if (ptopic->m_puserelement == this && ptopic->m_atom == id_initialize)
         {
            //            filemanager_document() = pupdate->filemanager_document();
            /*            m_pserverNext = simpledb::AppGet()->GetDataServer();
                        AddClient(this);
                        SetDataInterface(&m_datainterface);
                        AddClient(&m_datainterface);
                        string str;
                        str.format("file_list(%d,%d)", filemanager_data()->m_iTemplate, filemanager_data()->m_iDocument);
                        if(filemanager_data()->m_bTransparentBackground)
                        {
                        ::user::list::m_etranslucency = ::user::list::e_translucency_present;
                        }
                        DISetSection(str);
                        _001UpdateColumns();*/
         }
         else if (ptopic->m_atom == id_filter)
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



