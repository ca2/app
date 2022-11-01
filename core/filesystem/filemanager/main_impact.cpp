#include "framework.h"
#include "main_impact.h"
#include "left_impact.h"
#include "thumbnail.h"
#include "file_list.h"
#include "file_properties_form.h"
#include "document.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"
#include "base/user/user/frame_window.h"


namespace filemanager
{


   main_impact::main_impact()
   {

      //m_ppropform = nullptr;

      //m_flag

   }


   main_impact::~main_impact()
   {

   }


   void main_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::user::split_impact::install_message_routing(pchannel);

   }


//   void main_impact::assert_ok() const
//   {
//
//      ::user::split_impact::assert_ok();
//
//   }
//
//
//   void main_impact::dump(dump_context & dumpcontext) const
//   {
//
//      ::user::split_impact::dump(dumpcontext);
//
//   }





   void main_impact::_001OnDraw(::draw2d::graphics_pointer & pgraphics)
   {

      //auto pstyle = get_style(pgraphics);

      //::color::color crBackground = get_color(pstyle, ::e_element_background);

      //if ((crBackground & argb(255, 0, 0, 0)) != 0)
      //{

      //   ::rectangle_i32 rectangleClient;

      //   get_client_rect(rectangleClient);

      //   pgraphics->fill_rectangle(rectangleClient, argb(255, 255, 255, 255));

      //}

   }


   void main_impact::on_create_split_impact()
   {

      if (get_pane_count() > 0)
      {

         return;

      }

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0,0.3);

      initialize_split_layout();

      left_impact * pleftview = create_pane_impact < left_impact >(0);

      if(pleftview == nullptr)
      {

         output_error_message("Could not create folder tree ::user::impact");

      }

      //pleftview->create_impacts();

      m_pfilelist = create_pane_impact < file_list >(1);

      if(m_pfilelist == nullptr)
      {

         output_error_message("Could not create file list ::user::impact");

      }

      m_pthumbnail = create_impact < thumbnail >();

      m_pthumbnail->display(e_display_none);

   }


   void main_impact::OpenSelectionProperties()
   {

      auto itema = m_pfilelist->get_selected_items();

      if(m_ppropform == nullptr)
      {

         __construct(m_ppropform, __new(file_properties_form));

      }

      ::pointer<::user::interaction>puie = m_ppropform->open(this,itema);

      if(puie == nullptr)
         return;

      SetPane(1,puie,false);

      set_need_layout();

   }


   void main_impact::on_command(::message::command * pcommand)
   {

      if(pcommand->m_atom == "change_impact")
      {

         if(m_pthumbnail->is_window_visible())
         {

            SetPane(1,m_pfilelist,false);

            set_need_layout();

            m_pthumbnail->display(e_display_none);


         }
         else
         {

            SetPane(1,m_pthumbnail,false);

            set_need_layout();

            m_pfilelist->display(e_display_none);

         }

         pcommand->m_bRet = true;

      }

   }


   void main_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

      ::user::split_impact::handle(ptopic, pcontext);

      if (ptopic->m_atom == OPEN_DOCUMENT_UPDATE)
      {

         output_debug_string("filemanager::main_impact ::update_open_document");

      }

      if (filemanager_document() == ptopic->cast < ::user::document >(DOCUMENT_ID))
      {

         if (ptopic->m_atom == id_open_selection_properties)
         {

            OpenSelectionProperties();

         }
         else if (ptopic->m_atom == id_pop)
         {

            OnActivateFrame(e_activate_inactive, parent_frame());

            parent_frame()->ActivateFrame(e_display_restored);

            OnActivateImpact(true, this, this);

            set_need_redraw();

            //auto pframe = parent_frame();

            //if (pframe != nullptr)
            //{
            //   //xxx               pframe->WindowDataLoadWindowRect();
            //   //xxx          pframe->WindowDataEnableSaveWindowRect(true);
            //}

         }
         else if (ptopic->m_atom == id_create_bars)
         {

            //auto pframe = parent_frame();

            //if(pframe != nullptr)
            {

               //                    pframe->create_bars();
            }

         }

      }

   }


} // namespace filemanager



