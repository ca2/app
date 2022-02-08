#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "_data.h"
#include "aura/update.h"
#include "core/user/user/_tree.h"


namespace filemanager
{


   folder_selection_list_view::folder_selection_list_view()
   {

      m_ptree = nullptr;
      m_pusertree = nullptr;
      m_pdata = nullptr;
      m_plistview = nullptr;

   }


   folder_selection_list_view::~folder_selection_list_view()
   {

   }


   void folder_selection_list_view::install_message_routing(::channel * pchannel)
   {

      ::user::split_view::install_message_routing(pchannel);

   }


   void folder_selection_list_view::on_create_split_impact()
   {

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.30);

      initialize_split_layout();

      m_pusertree = create_view  < ::user::tree_view >(get_document(), get_pane_holder(0));

      if(m_pusertree == nullptr)
      {

         output_error_message("Could not create folder tree impact");

      }

      auto ptree = filemanager_document()->__create_new < tree >();
      
      if(ptree == nullptr)
      {

         output_error_message("Could not create folder tree");
      
      }
      else
      {

         m_ptree = ptree;

         ptree->m_pdocument = get_document();

         m_pusertree->merge(m_ptree, true);

      }

      m_plistview = create_view < folder_list_view >(get_document(), get_pane_holder(1));

      if(m_plistview == nullptr)
      {

         output_error_message("Could not create file list");

      }

   }


   void folder_selection_list_view::FolderAdd()
   {

      string_array straSel;

      m_ptree->GetSelectedFilePath(straSel);

      if(m_plistview->m_bRecursive)
      {

         int_array ia;

         m_plistview->add_unique(straSel, ia);

      }
      else
      {

         m_plistview->add_unique(straSel);

      }

   }


   void folder_selection_list_view::FolderRemove()
   {

      string_array wstraSel;

      m_plistview->GetSel(wstraSel);

      m_plistview->erase(wstraSel);

   }


   void folder_selection_list_view::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

   }


   void folder_selection_list_view::_001OnAdd(::message::message * pmessage)
   {

      FolderAdd();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void folder_selection_list_view::_001OnRemove(::message::message * pmessage)
   {

      FolderRemove();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   data * folder_selection_list_view::filemanager_data()
   {

      return m_pdata;

   }


   void folder_selection_list_view::browse_sync(const ::action_context & context)
   {

      auto pdocument = get_document();

      ::extended_topic extendedtopic(id_synchronize_folder_selection);

      extendedtopic.m_actioncontext = context + ::e_source_selection;

      pdocument->update_all_views(&extendedtopic);

   }


} // namespace filemanager



