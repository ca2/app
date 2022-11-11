#include "framework.h"
#include "folder_selection_list_impact.h"
#include "document.h"
#include "folder_list_impact.h"
#include "tree.h"
#include "acme/constant/id.h"
#include "acme/handler/item.h"
#include "acme/platform/context.h"
#include "core/user/user/tree.h"


namespace filemanager
{


   folder_selection_list_impact::folder_selection_list_impact()
   {

      m_ptree = nullptr;
      m_pusertree = nullptr;
      m_pdata = nullptr;
      m_plistview = nullptr;

   }


   folder_selection_list_impact::~folder_selection_list_impact()
   {

   }


   void folder_selection_list_impact::install_message_routing(::channel * pchannel)
   {

      ::user::split_impact::install_message_routing(pchannel);

   }


   void folder_selection_list_impact::on_create_split_impact()
   {

      SetPaneCount(2);

      SetSplitOrientation(e_orientation_vertical);

      set_position_rate(0, 0.30);

      initialize_split_layout();

      m_pusertree = create_impact < ::user::tree_impact >(get_document(), get_pane_holder(0));

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

      m_plistview = create_impact < folder_list_impact >(get_document(), get_pane_holder(1));

      if(m_plistview == nullptr)
      {

         output_error_message("Could not create file list");

      }

   }


   void folder_selection_list_impact::FolderAdd()
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


   void folder_selection_list_impact::FolderRemove()
   {

      string_array wstraSel;

      m_plistview->GetSel(wstraSel);

      m_plistview->erase(wstraSel);

   }


   void folder_selection_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      ::filemanager_impact_base::handle(ptopic, pcontext);

   }


   void folder_selection_list_impact::_001OnAdd(::message::message * pmessage)
   {

      FolderAdd();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   void folder_selection_list_impact::_001OnRemove(::message::message * pmessage)
   {

      FolderRemove();

      if (pmessage != nullptr)
      {

         pmessage->m_bRet = true;

      }

   }


   data * folder_selection_list_impact::filemanager_data()
   {

      return m_pdata;

   }


   void folder_selection_list_impact::browse_sync(const ::action_context & context)
   {

      auto pdocument = get_document();

      auto ptopic = create_topic(id_synchronize_folder_selection);

      ptopic->m_actioncontext = context + ::e_source_selection;

      pdocument->update_all_impacts(ptopic);

   }


} // namespace filemanager



