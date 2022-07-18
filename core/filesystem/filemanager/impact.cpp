#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "aura/update.h"
#include "base/user/user/split_pane.h"


namespace filemanager
{


   impact::impact()
   {

   }


   impact::~impact()
   {

   }


   void impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::split_view::install_message_routing(pchannel);

   }


   void impact::assert_ok() const
   {
      ::user::split_view::assert_ok();
   }

   void impact::dump(dump_context & dumpcontext) const
   {
      ::user::split_view::dump(dumpcontext);
   }


   void impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      auto papp = get_app();

      bool bPathImpact = papp->is_false("no_path_view");

      SetPaneCount(bPathImpact ? 2 : 1);

      SetSplitOrientation(e_orientation_horizontal);

      if (bPathImpact)
      {

         auto preferredDensity = preferred_density();

         set_position(0, (::i32) (24.0 * preferredDensity));

         m_splitpanecompositea[0]->m_bFixedSize = true;

         initialize_split_layout();

         path_view * ppathview = create_pane_view < path_view >(0);

         if (ppathview == nullptr)
         {

            output_error_message("Could not create filemanager path impact");

         }

      }
      else
      {

         initialize_split_layout();

      }


      main_impact * pmainview = create_pane_view < main_impact >(bPathImpact ? 1 : 0);

      if (pmainview == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      //SetPane(pmainview, false);

      //pmainview->create_views();

   }


   void impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      ::user::split_view::handle(ptopic, pcontext);

      auto psystem = m_psystem->m_paurasystem;

      auto pdocumentSubject = ptopic->cast < ::user::document >(id_document);

      if (filemanager_document() == pdocumentSubject)
      {

         //if (ptopic->m_atom == id_initialize)
         //{

         //   string str;

         //   str.format("(%s)", filemanager_data()->m_atom.str().c_str());

         //   __pointer(::database::client) pframe = get_parent_frame();

         //   if (pframe != nullptr)
         //   {

         //      pframe->set_data_key_modifier(str);

         //   }

         //}
         //else
         if (ptopic->m_atom == id_pop)
         {

            OnActivateFrame(e_activate_inactive, parent_frame());

            auto pframe = parent_frame();

            if (::is_set(pframe))
            {

               pframe->ActivateFrame(e_display_restored);

            }

            OnActivateImpact(true, this, this);

            set_need_redraw();

         }
         else if (ptopic->m_atom == id_create_bars)
         {

            auto pframe = parent_frame();

            if (pframe != nullptr)
            {

               pframe->m_puserframewindow->create_bars();

            }

         }
         else if (ptopic->m_atom == id_topic_start)
         {

            if (filemanager_document()->m_emode != ::userfs::mode_import && get_pane_count() == 2)
            {

               auto pframe = parent_frame();

               if (pframe != nullptr)
               {

                  pframe->m_puserframewindow->create_bars();

               }

               ::filemanager::save_as_view * ptopview = create_view < ::filemanager::save_as_view >();

               if (ptopview == nullptr)
               {

                  output_error_message("Could not create folder tree ::user::impact");

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

               if (filemanager_data()->m_pdocumentTopic->get_save_file_extension().has_char())
               {

                  strSuffix = "." + filemanager_data()->m_pdocumentTopic->get_save_file_extension();

               }
               else if (path.final_extension().has_char())
               {

                  string strExtension = ptopic->payload("file_extension");

                  if (strExtension.has_char())
                  {

                     strSuffix = "." + strExtension;

                  }
                  else
                  {

                     strSuffix = "." + path.final_extension();

                  }

               }

               //auto psystem = m_psystem;

               auto pdatetime = psystem->datetime();

               strName = strPrefix + pdatetime->international().get_date_time() + strSuffix;

               strName.find_replace(":", "-");

               ptopview->m_pedit->_001SetText(strName, ptopic->m_actioncontext);

               filemanager_data()->m_pdocument->m_strTopic = strName;

               set_position(0, 28);

               set_position(1, 56);

               ::rectangle_i32 rectangleClient;

               get_client_rect(rectangleClient);

               set_need_layout();

               pframe->set_need_layout();

            }

         }
         else if (ptopic->m_atom == id_topic_cancel)
         {

            if (base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
            {
               //RemovePaneAt(0);
               //set_position(0, 49);
               //on_layout(pgraphics);
            }

         }
         else if (ptopic->m_atom == id_topic_ok)
         {

            if (filemanager_document()->m_emode == ::userfs::mode_import)
            {

               ptopic->m_bRet = filemanager_data()->m_pdocumentTopic->on_filemanager_open(filemanager_document(), ptopic->_extended_topic()->m_pfileitem->user_path());

            }

         }

      }

      //tab_view * ptabimpact = get_parent_frame()->GetTypedParent < tab_view >();
      //if (ptabimpact != nullptr)
      //{
      //   ptabimpact->on_update(this, eupdate, pobject);
      //}

   }

} // namespace filemanager



