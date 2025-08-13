// Refactor and Tidy core filemanager component a bit Fix ca2/app#61 by
// camilo on 2023 - 11 - 16 03:54 < 3ThomasBorregaardSorensen!!
#include "framework.h"
#include "document.h"
#include "list_impact.h"
#include "list_data.h"
////#include "data.h"
#include "acme/handler/item.h"
#include "acme/handler/topic.h"
#include "acme/platform/application.h"
//#include "acme/handler/sequence.h"
#include "aura/user/user/check_box.h"
#include "core/user/user/list_column.h"


namespace filemanager
{

   namespace folder
   {

      list_impact::list_impact()
      {

         m_bRecursive = true;

      }


      list_impact::~list_impact()
      {

      }


      void list_impact::install_message_routing(::channel * pchannel)
      {

         ::filemanager_impact_base::install_message_routing(pchannel);
         ::simple_list_impact::install_message_routing(pchannel);

      }


      document * list_impact::get_document()
      {

         return dynamic_cast <class document *>(::user::impact::get_document());

      }

      void list_impact::initialize_folder_list_impact(const ::scoped_string & scopedstrDataKeyModifier, bool bRecursive)
      {

         m_bRecursive = bRecursive;

         set_pending_column_update();

         update_impact();

         m_pfolderlistdata = __create_new < folder::list_data >();

         m_pfolderlistdata->set_data_key_modifier(scopedstrDataKeyModifier);

         set_data_interface(m_pfolderlistdata);

         update_impact();

      }


      void list_impact::on_insert_columns()
      {

         {

            auto pcolumn = new_list_column();

            pcolumn->m_iWidth = 400;
            pcolumn->m_iSubItem = 0;
            pcolumn->m_text = m_papplication->__text("text://filemanager/list_impact/folder_path/Folder Path");


         }

         if (m_bRecursive)
         {

            auto pcolumn = new_list_column();
            pcolumn->id() = "check_recursive";
            pcolumn->m_iWidth = 80;
            pcolumn->m_iSubItem = 1;
            pcolumn->m_text = m_papplication->__text("text://filemanager/list_impact/recursive/Recursive");

            auto pcheckbox = __create_new <  ::user::check_box >();
            pcheckbox->id() = pcolumn->id();
            pcheckbox->add_function(::user::e_control_function_check_box);
            _001AddControl(pcheckbox);

         }

      }


      bool list_impact::add_unique(const string_array_base & stra)
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

         update_impact();

         return true;

      }


      bool list_impact::add_unique(const string_array_base & stra, ::int_array_base & baRecursive)
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

         update_impact();

         return true;

      }


      bool list_impact::erase(const string_array_base & stra)
      {

         if (stra.get_size() == 0)
         {

            return true;

         }

         if (m_pfolderlistdata)
         {

            if (!m_pfolderlistdata->erase(stra))
            {

               return false;

            }

         }

         update_impact();

         return true;

      }


      void list_impact::GetSel(string_array_base & stra)
      {

         if (m_pfolderlistdata)
         {

            m_pfolderlistdata->GetSel(this, stra);

         }


      }


      void list_impact::handle(::topic * ptopic, ::handler_context * phandlercontext)
      {

         FILEMANAGER_SHOW_IMPACT::handle(ptopic, phandlercontext);

         if (ptopic->id() == id_initialize)
         {

            //if (filemanager_data()->m_bPassBk)
            //{

            //   ::user::list::m_bBackgroundBypass = true;

            //}

            auto pdocument = get_document();

            initialize_folder_list_impact(
               pdocument->m_atomFolderSelectionList,
               pdocument->m_bEnableRecursiveFolderSelectionList);

         }

      }


      void list_impact::on_check_save(::user::interaction * puserinteraction)
      {

         if (puserinteraction->id() == "check_recursive")
         {

            if (m_pfolderlistdata)
            {

               bool bChecked = puserinteraction->is_checked();

               bool iItem = puserinteraction->m_item.m_iItem;

               m_pfolderlistdata->set_recursive(iItem, bChecked);

            }

         }

      }


      void list_impact::on_check_load(::user::interaction * puserinteraction)
      {

         if (puserinteraction->id() == "check_recursive")
         {

            if (m_pfolderlistdata)
            {

               auto iItem = puserinteraction->m_item.m_iItem;

               bool bCheck = m_pfolderlistdata->get_recursive(iItem);

               puserinteraction->set_check(bCheck, ::e_source_sync);

            }

         }

      }


   } // namespace folder


} // namespace filemanager



