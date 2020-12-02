#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "aura/update.h"



namespace filemanager
{


   main_view::main_view()
   {

      //m_ppropform = nullptr;

      //m_flag

   }


   main_view::~main_view()
   {

   }


   void main_view::install_message_routing(::channel * pchannel)
   {

      ::filemanager::impact::install_message_routing(pchannel);
      ::user::split_view::install_message_routing(pchannel);

   }


   void main_view::assert_valid() const
   {

      ::user::split_view::assert_valid();

   }


   void main_view::dump(dump_context & dumpcontext) const
   {

      ::user::split_view::dump(dumpcontext);

   }





   void main_view::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //auto pstyle = get_style(pgraphics);

      //color32_t crBackground = get_color(pstyle, ::user::element_background);

      //if ((crBackground & ARGB(255, 0, 0, 0)) != 0)
      //{

      //   ::rect rectClient;

      //   get_client_rect(rectClient);

      //   pgraphics->fill_rect(rectClient, ARGB(255, 255, 255, 255));

      //}

   }


   void main_view::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(orientation_vertical);

      set_position_rate(0,0.3);

      initialize_split_layout();

      left_view * pleftview = create_pane_view < left_view >(0);

      if(pleftview == nullptr)
      {

         System.message_box("Could not create folder tree ::user::impact");

      }

      //pleftview->create_views();

      m_pfilelist = create_pane_view < file_list >(1);

      if(m_pfilelist == nullptr)
      {

         message_box("Could not create file list ::user::impact");

      }

      m_ppreview = create_view < preview >();

      m_ppreview->display(e_display_none);

   }


   void main_view::OpenSelectionProperties()
   {

      auto itema = m_pfilelist->get_selected_items();

      if(m_ppropform == nullptr)
      {

         __compose(m_ppropform, __new(file_properties_form));

      }

      __pointer(::user::interaction) puie = m_ppropform->open(this,itema);

      if(puie == nullptr)
         return;

      SetPane(1,puie,false);

      set_need_layout();

   }


   void main_view::on_command(::user::command * pcommand)
   {

      if(pcommand->m_id == "change_view")
      {

         if(m_ppreview->is_window_visible())
         {

            SetPane(1,m_pfilelist,false);

            set_need_layout();

            m_ppreview->display(e_display_none);


         }
         else
         {

            SetPane(1,m_ppreview,false);

            set_need_layout();

            m_pfilelist->display(e_display_none);

         }

         pcommand->m_bRet = true;

      }

   }


   void main_view::on_subject(::promise::subject * psubject, ::promise::context * pcontext)
   {

      ::filemanager::impact::on_subject(psubject, pcontext);

      ::user::split_view::on_subject(psubject, pcontext);

      if (psubject->id() == OPEN_DOCUMENT_UPDATE)
      {

         output_debug_string("filemanager::main_view ::update_open_document");

      }

      if (filemanager_document() == psubject->cast < ::user::document >(DOCUMENT_ID))
      {

         if (psubject->id() == id_open_selection_properties)
         {

            OpenSelectionProperties();

         }
         else if (psubject->id() == id_pop)
         {

            OnActivateFrame(e_activate_inactive, ((GetParentFrame())));

            GetParentFrame()->ActivateFrame(e_display_normal);

            OnActivateView(TRUE, this, this);

            set_need_redraw();

            __pointer(frame) pframe = GetParentFrame();

            if (pframe != nullptr)
            {
               //xxx               pframe->WindowDataLoadWindowRect();
               //xxx          pframe->WindowDataEnableSaveWindowRect(true);
            }

         }
         else if (psubject->id() == id_create_bars)
         {

            __pointer(simple_frame_window) pframe = GetParentFrame();

            //if(pframe != nullptr)
            {

               //                    pframe->create_bars();
            }

         }

      }

   }


} // namespace filemanager



