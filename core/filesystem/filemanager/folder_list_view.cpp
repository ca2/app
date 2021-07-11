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

      //set_data_key_modifier(strDataKeyModifier);

      m_bRecursive = bRecursive;

      _001UpdateColumns();

      _001OnUpdateItemCount();

      if(bRecursive)
      {

         auto pdata = __create_new < folder_list_data > ();

         SetDataInterface(pdata);

         pdata->set_data_key_modifier(strDataKeyModifier);

         auto papplication = get_application();

         pdata->initialize_data_client(papplication->dataserver());

      }
      else
      {

         auto pdata = __create_new < databaseuser::data_key_mesh_data > ();

         SetDataInterface(pdata);

         pdata->set_data_key_modifier(strDataKeyModifier);

         auto papplication = get_application();

         pdata->initialize_data_client(papplication->dataserver());

      }

      fork([&]()
      {

         _001OnUpdateItemCount();

      });

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

      if(m_bRecursive)
         __throw(::exception::exception("incorrect usage of this class object"));

      if(stra.get_size() == 0)
         return true;

      __pointer(databaseuser::data_key_mesh_data) pdata = m_pmeshdata.cast <databaseuser::data_key_mesh_data >();

      if(!pdata->add_unique(stra))
         return false;

      _001OnUpdateItemCount();

      return true;

   }


   bool folder_list_view::add_unique(const string_array & stra, int_array & baRecursive)
   {

      if(!m_bRecursive)
         __throw(::exception::exception("incorrect usage of this class object"));

      if(stra.get_size() == 0)
         return true;

      auto pdata = m_pmeshdata.cast <folder_list_data> ();

      if (!pdata->add_unique(stra, baRecursive))
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

      if(m_bRecursive)
      {

         __pointer(folder_list_data) pdata = m_pmeshdata.cast <folder_list_data >();

         if(!pdata->erase(stra))
            return false;

      }
      else
      {

         auto pdata = m_psimplemeshdata.cast <databaseuser::data_key_mesh_data > ();

         if (!pdata->erase(stra))
         {

            return false;

         }

      }

      _001OnUpdateItemCount();

      return true;

   }


   void folder_list_view::GetSel(string_array & stra)
   {

      if(m_bRecursive)
      {

         __pointer(folder_list_data) pdata = m_pmeshdata.cast <folder_list_data >();
         pdata->GetSel(this,stra);

      }
      else
      {

         __pointer(databaseuser::data_key_mesh_data) pdata = m_psimplemeshdata.cast <databaseuser::data_key_mesh_data >();
         pdata->GetSel(this,stra);

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


} // namespace filemanager



