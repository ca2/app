#include "framework.h"
////#include "_filemanager.h"


namespace filemanager
{


   //callback::callback()
   //{

   //}

   //callback::~callback()
   //{

   //}

   
   void callback::on_file_manager_open(::filemanager::data* pdata, const ::file::item_array& itema, const ::action_context& action_context)
   {

   }


   void callback::on_file_manager_open_context_menu_folder(::filemanager::data * pdata, ::file::item * pitem, string_array & straCommand, string_array & straCommandTitle, const ::action_context & context)
   {
      UNREFERENCED_PARAMETER(pitem);
      UNREFERENCED_PARAMETER(straCommand);
      UNREFERENCED_PARAMETER(straCommandTitle);
      UNREFERENCED_PARAMETER(context);
      __throw(todo("core"));
      //if (pdata->m_pdocument != nullptr)
      //{
      //   pdata->m_pdocument->OpenSelectionProperties();
      //}
   }

   void callback::on_file_manager_open_context_menu_file(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & context)
   {
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(context);
      __throw(todo("core"));
      //if (pdata->m_pdocument != nullptr)
      //{
      //   pdata->m_pdocument->OpenSelectionProperties();
      //}
   }

   void callback::on_file_manager_open_context_menu(::filemanager::data * pdata, const ::action_context & context)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(context);
   }

   //void callback::on_request(::create * pcreate)
   //{

   //   Application.do_request(pcreate);

   //}

   void callback::on_file_manager_open_folder(::filemanager::data * pdata, ::file::item * pitem, const ::action_context & context)
   {
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(pitem);
      UNREFERENCED_PARAMETER(context);
   }

   
   void callback::on_file_manager_item_command(::filemanager::data * pdata, id id, const ::file::item_array & itema)
   {
   
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(itema);
   
   }

   
   void callback::on_file_manager_item_update(::filemanager::data * pdata, ::message::command * pcommand, const ::file::item_array & itema)
   {
   
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(pcommand);
      UNREFERENCED_PARAMETER(itema);
   
   }


   void callback::on_file_manager_initialize_form_pre_data(::filemanager::data * pdata, id id, ::user::form * pinteractionForm)
   {
      
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(pinteractionForm);

   }


   //bool callback::GetFileManagerItemCallback(::filemanager::data * pdata, id id, const ::file::item_array & itema)
   //{
   //   UNREFERENCED_PARAMETER(pdata);
   //   UNREFERENCED_PARAMETER(id);
   //   UNREFERENCED_PARAMETER(itema);
   //   return false;
   //}


   bool callback::get_file_manager_item_callback(::filemanager::data * pdata, id id, const ::file::item_array & itema)
   {
      
      UNREFERENCED_PARAMETER(pdata);
      UNREFERENCED_PARAMETER(id);
      UNREFERENCED_PARAMETER(itema);

      return false;

   }


} // namespace filemanager



