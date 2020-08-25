#include "framework.h"
//#include "_filemanager.h"
#include "aura/update.h"



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

      ::filemanager::impact::install_message_routing(pchannel);
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
         return;

      bool bPathView = Application.is_false("no_path_view");

      SetPaneCount(bPathView ? 2 : 1);

      SetSplitOrientation(orientation_horizontal);

      if (bPathView)
      {

         set_position(0, 24);

         m_panea[0]->m_bFixedSize = true;

         initialize_split_layout();

         path_view * ppathview = create_pane_view < path_view >(0);

         if (ppathview == nullptr)
         {

            System.message_box("Could not create filemanager path view");

         }

      }
      else
      {

         initialize_split_layout();

      }


      main_view * pmainview = create_pane_view < main_view >(bPathView ? 1 : 0);

      if (pmainview == nullptr)
      {

         System.message_box("Could not create file list ::user::impact");

      }

      //SetPane(, pmainview, false);

      //pmainview->create_views();

   }


   void view::update(::update * pupdate)
   {

      ::filemanager::impact::update(pupdate);

      ::user::split_view::update(pupdate);

      if (filemanager_document() == pupdate->cast < ::user::document >(id_document))
      {

         //if (pupdate->m_id == id_initialize)
         //{

         //   string str;

         //   str.Format("(%s)", filemanager_data()->m_id.str().c_str());

         //   __pointer(::database::client) pframe = GetParentFrame();

         //   if (pframe != nullptr)
         //   {

         //      pframe->set_data_key_modifier(str);

         //   }

         //}
         //else
         if (pupdate->m_id == id_pop)
         {

            OnActivateFrame(WA_INACTIVE, GetParentFrame());

            __pointer(::user::frame_window) spframewindow = GetParentFrame();

            if (spframewindow.is_set())
            {

               spframewindow->ActivateFrame(display_normal);

            }

            OnActivateView(TRUE, this, this);

            set_need_redraw();

         }
         else if (pupdate->m_id == id_create_bars)
         {

            __pointer(simple_frame_window) pframe = GetParentFrame();

            if (pframe != nullptr)
            {

               pframe->create_bars();

            }

         }
         else if (pupdate->m_id == id_topic_start)
         {

            if (filemanager_document()->m_emode != ::userfs::mode_import && get_pane_count() == 2)
            {

               __pointer(simple_frame_window) pframe = GetParentFrame();

               if (pframe != nullptr)
               {

                  pframe->create_bars();

               }

               ::filemanager::save_as_view * ptopview = create_view < ::filemanager::save_as_view >();

               if (ptopview == nullptr)
               {

                  System.message_box("Could not create folder tree ::user::impact");

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
               
               strName = strPrefix + System.datetime().international().get_gmt_date_time() + strSuffix;

               strName.replace(":", "-");

               ptopview->m_pedit->_001SetText(strName, pupdate->m_actioncontext);

               filemanager_data()->m_pdocument->m_strTopic = strName;

               set_position(0, 28);

               set_position(1, 56);

               ::rect rectClient;

               get_client_rect(rectClient);

               set_need_layout();

               pframe->set_need_layout();

            }

         }
         else if (pupdate->m_id == id_topic_cancel)
         {

            if (base_class < ::filemanager::save_as_view >::bases(get_pane_window(0)))
            {
               //RemovePaneAt(0);
               //set_position(0, 49);
               //on_layout(::draw2d::graphics_pointer & pgraphics);
            }

         }
         else if (pupdate->m_id == id_topic_ok)
         {

            if (filemanager_document()->m_emode == ::userfs::mode_import)
            {

               pupdate->m_bRet = filemanager_data()->m_pdocumentTopic->on_filemanager_open(filemanager_document(), pupdate->m_pfileitem->m_filepathUser);

            }

         }

      }

      //tab_view * ptabview = GetParentFrame()->GetTypedParent < tab_view >();
      //if (ptabview != nullptr)
      //{
      //   ptabview->on_update(this, eupdate, pobject);
      //}

   }

} // namespace filemanager



