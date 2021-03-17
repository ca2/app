#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "aura/update.h"
#include "base/user/user/split_pane.h"


namespace filemanager
{


   view::view()
   {

   }


   view::~view()
   {

   }


   void view::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact::install_message_routing(pchannel);
      ::user::split_view::install_message_routing(pchannel);

   }


   void view::assert_valid() const
   {
      ::user::split_view::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::user::split_view::dump(dumpcontext);
   }


   void view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      auto papplication = get_application();

      bool bPathView = papplication->is_false("no_path_view");

      SetPaneCount(bPathView ? 2 : 1);

      SetSplitOrientation(e_orientation_horizontal);

      if (bPathView)
      {

         set_position(0, 24);

         m_splitpanecompositea[0]->m_bFixedSize = true;

         initialize_split_layout();

         path_view * ppathview = create_pane_view < path_view >(0);

         if (ppathview == nullptr)
         {

            message_box("Could not create filemanager path view");

         }

      }
      else
      {

         initialize_split_layout();

      }


      main_view * pmainview = create_pane_view < main_view >(bPathView ? 1 : 0);

      if (pmainview == nullptr)
      {

         message_box("Could not create file list ::user::impact");

      }

      //SetPane(pmainview, false);

      //pmainview->create_views();

   }


   void view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      ::filemanager_impact::on_subject(psubject, pcontext);

      ::user::split_view::on_subject(psubject, pcontext);

      auto psystem = get_system();

      if (filemanager_document() == psubject->cast < ::user::document >(id_document))
      {

         //if (psubject->id() == id_initialize)
         //{

         //   string str;

         //   str.Format("(%s)", filemanager_data()->m_id.str().c_str());

         //   __pointer(::database::client) pframe = get_parent_frame();

         //   if (pframe != nullptr)
         //   {

         //      pframe->set_data_key_modifier(str);

         //   }

         //}
         //else
         if (psubject->id() == id_pop)
         {

            OnActivateFrame(e_activate_inactive, get_parent_frame());

            __pointer(::user::frame_window) spframewindow = get_parent_frame();

            if (spframewindow.is_set())
            {

               spframewindow->ActivateFrame(e_display_normal);

            }

            OnActivateView(true, this, this);

            set_need_redraw();

         }
         else if (psubject->id() == id_create_bars)
         {

            __pointer(simple_frame_window) pframe = get_parent_frame();

            if (pframe != nullptr)
            {

               pframe->create_bars();

            }

         }
         else if (psubject->id() == id_topic_start)
         {

            if (filemanager_document()->m_emode != ::userfs::mode_import && get_pane_count() == 2)
            {

               __pointer(simple_frame_window) pframe = get_parent_frame();

               if (pframe != nullptr)
               {

                  pframe->create_bars();

               }

               ::filemanager::save_as_view * ptopview = create_view < ::filemanager::save_as_view >();

               if (ptopview == nullptr)
               {

                  message_box("Could not create folder tree ::user::impact");

               }

               InsertPaneAt(0, ptopview, true);

               ::file::path path = filemanager_data()->m_pdocumentTopic->get_file_path();

               string strName;

               string strPrefix;

               if (path.title().has_char())
               {

                  strPrefix = path.title() + " - ";

               }

               string strSuffix;

               if (path.ext().has_char())
               {

                  strSuffix = "." + path.ext();

               }
               else if (filemanager_data()->m_pdocumentTopic->get_save_file_extension().has_char())
               {

                  strSuffix = "." + filemanager_data()->m_pdocumentTopic->get_save_file_extension();

               }

               strName = strPrefix + psystem->datetime().international().get_gmt_date_time() + strSuffix;

               strName.replace(":", "-");

               ptopview->m_pedit->_001SetText(strName, psubject->m_actioncontext);

               filemanager_data()->m_pdocument->m_strTopic = strName;

               set_position(0, 28);

               set_position(1, 56);

               ::rectangle_i32 rectClient;

               get_client_rect(rectClient);

               set_need_layout();

               pframe->set_need_layout();

            }

         }
         else if (psubject->id() == id_topic_cancel)
         {

            if (base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
            {
               //RemovePaneAt(0);
               //set_position(0, 49);
               //on_layout(::draw2d::graphics_pointer & pgraphics);
            }

         }
         else if (psubject->id() == id_topic_ok)
         {

            if (filemanager_document()->m_emode == ::userfs::mode_import)
            {

               psubject->m_bRet = filemanager_data()->m_pdocumentTopic->on_filemanager_open(filemanager_document(), psubject->m_pfileitem->m_filepathUser);

            }

         }

      }

      //tab_view * ptabview = get_parent_frame()->GetTypedParent < tab_view >();
      //if (ptabview != nullptr)
      //{
      //   ptabview->on_update(this, eupdate, pobject);
      //}

   }

} // namespace filemanager



