#include "framework.h"
#include "core/filesystem/filemanager/_filemanager.h"
#include "core/user/databaseuser/_databaseuser.h"


namespace filemanager
{


   folder_list_view::folder_list_view()
   {

      m_bRecursive = true;

   }


   folder_list_view::~folder_list_view()
   {

   }


   void folder_list_view::install_message_routing(::channel * pchannel)
   {

      ::filemanager_impact::install_message_routing(pchannel);
      ::simple_list_view::install_message_routing(pchannel);

   }


   void folder_list_view::initialize(string strDataKeyModifier,bool bRecursive)
   {

      m_bRecursive = bRecursive;

      _001UpdateColumns();

      _001OnUpdateItemCount();

      m_pfolderlistdata = __create_new < folder_list_data > ();

      m_pfolderlistdata->set_data_key_modifier(strDataKeyModifier);

      set_data_interface(m_pfolderlistdata);

      _001OnUpdateItemCount();

   }


   void folder_list_view::_001InsertColumns()
   {

      {

         auto pcolumn = new_list_column();

         pcolumn->m_iWidth = 400;
         pcolumn->m_iSubItem = 0;
         pcolumn->m_text = m_pcontext->__text("text://filemanager/folder_list_view/folder_path/Folder Path");


      }

      if(m_bRecursive)
      {

         auto pcolumn                     = new_list_column();
         pcolumn->m_id                    = "check_recursive";
         pcolumn->m_iWidth                = 80;
         pcolumn->m_iSubItem              = 1;
         pcolumn->m_text                  = m_pcontext->__text("text://filemanager/folder_list_view/recursive/Recursive");

         auto pcheckbox = __create_new <  ::user::check_box >();
         pcheckbox->m_id = pcolumn->m_id;
         pcheckbox->add_function(::user::e_control_function_check_box);
         _001AddControl(pcheckbox);

      }

   }


   bool folder_list_view::add_unique(const string_array & stra)
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


   bool folder_list_view::add_unique(const string_array & stra, int_array & baRecursive)
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


   bool folder_list_view::erase(const string_array & stra)
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


   void folder_list_view::GetSel(string_array & stra)
   {

      if (m_pfolderlistdata)
      {

         m_pfolderlistdata->GetSel(this, stra);

      }


   }


   void folder_list_view::on_subject(::subject::subject * psubject, ::subject::context * pcontext)
   {

      FILEMANAGER_SHOW_IMPACT::on_subject(psubject, pcontext);

      if (psubject->id() == INITIALIZE_ID)
      {

         if (filemanager_data()->m_bPassBk)
         {

            ::user::list::m_bBackgroundBypass = true;

         }

         initialize(__str(filemanager_data()->m_id), filemanager_data()->m_bEnableRecursiveFolderSelectionList);

      }

   }


   void folder_list_view::on_check_save(::user::interaction* puserinteraction)
   {

      if (puserinteraction->m_id == "check_recursive")
      {

         if (m_pfolderlistdata)
         {

            bool bCheck = puserinteraction->bcheck();

            bool iItem = puserinteraction->m_iItem;

            m_pfolderlistdata->set_recursive(iItem, bCheck);

         }

      }
      
   }


   void folder_list_view::on_check_load(::user::interaction* puserinteraction)
   {

      if (puserinteraction->m_id == "check_recursive")
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



