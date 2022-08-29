#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "core/filesystem/filemanager/_filemanager.h"
#endif
#include "core/user/databaseuser/_component.h"
#include "folder_list_impact.h"
#include "folder_list_data.h"
#include "core/user/user/list_column.h"
#include "data.h"
#include "aura/user/user/check_box.h"


namespace filemanager
{


   folder_list_impact::folder_list_impact()
   {

      m_bRecursive = true;

   }


   folder_list_impact::~folder_list_impact()
   {

   }


   void folder_list_impact::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact_base::install_message_routing(pchannel);
      ::simple_list_impact::install_message_routing(pchannel);

   }


   void folder_list_impact::initialize(string strDataKeyModifier,bool bRecursive)
   {

      m_bRecursive = bRecursive;

      _001UpdateColumns();

      _001OnUpdateItemCount();

      m_pfolderlistdata = __create_new < folder_list_data > ();

      m_pfolderlistdata->set_data_key_modifier(strDataKeyModifier);

      set_data_interface(m_pfolderlistdata);

      _001OnUpdateItemCount();

   }


   void folder_list_impact::_001InsertColumns()
   {

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth = 400;
         pcolumn->m_iSubItem = 0;
         pcolumn->m_text = m_pcontext->__text("text://filemanager/folder_list_impact/folder_path/Folder Path");


      }

      if(m_bRecursive)
      {

         auto pcolumn                     = new_list_column();
         pcolumn->m_atom                    = "check_recursive";
         pcolumn->m_iWidth                = 80;
         pcolumn->m_iSubItem              = 1;
         pcolumn->m_text                  = m_pcontext->__text("text://filemanager/folder_list_impact/recursive/Recursive");

         auto pcheckbox = __create_new <  ::user::check_box >();
         pcheckbox->m_atom = pcolumn->m_atom;
         pcheckbox->add_function(::user::e_control_function_check_box);
         _001AddControl(pcheckbox);

      }

   }


   bool folder_list_impact::add_unique(const string_array & stra)
   {

      if (stra.get_size() == 0)
      {

         return true;

      }

      auto pfolderlistdata = m_pfolderlistdata;

      if (!pfolderlistdata->add_unique(stra))
      {

         return false;

      }

      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_impact::add_unique(const string_array & stra, int_array & baRecursive)
   {

      if (stra.get_size() == 0)
      {

         return true;

      }

      auto pfolderlistdata = m_pfolderlistdata;

      if (!pfolderlistdata->add_unique(stra, baRecursive))
      {

         return false;

      }

      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_impact::erase(const string_array & stra)
   {

      if (stra.get_size() == 0)
      {

         return true;

      }

      if(m_pfolderlistdata)
      {

         if (!m_pfolderlistdata->erase(stra))
         {

            return false;

         }

      }

      _001OnUpdateItemCount();

      return true;

   }


   void folder_list_impact::GetSel(string_array & stra)
   {

      if (m_pfolderlistdata)
      {

         m_pfolderlistdata->GetSel(this, stra);

      }


   }


   void folder_list_impact::handle(::topic * ptopic, ::context * pcontext)
   {

      FILEMANAGER_SHOW_IMPACT::handle(ptopic, pcontext);

      if (ptopic->m_atom == INITIALIZE_ID)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         initialize(__string(filemanager_data()->m_atom), filemanager_data()->m_bEnableRecursiveFolderSelectionList);

      }

   }


   void folder_list_impact::on_check_save(::user::interaction* puserinteraction)
   {

      if (puserinteraction->m_atom == "check_recursive")
      {

         if (m_pfolderlistdata)
         {

            bool bCheck = puserinteraction->bcheck();

            bool iItem = puserinteraction->m_iItem;

            m_pfolderlistdata->set_recursive(iItem, bCheck);

         }

      }
      
   }


   void folder_list_impact::on_check_load(::user::interaction* puserinteraction)
   {

      if (puserinteraction->m_atom == "check_recursive")
      {

         if (m_pfolderlistdata)
         {

            auto iItem = puserinteraction->m_iItem;

            bool bCheck = m_pfolderlistdata->get_recursive(iItem);

            puserinteraction->_001SetCheck(bCheck, ::e_source_sync);

         }

      }

   }


} // namespace filemanager



