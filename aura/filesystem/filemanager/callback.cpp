#include "framework.h"
#include "callback.h"
////#include "acme/exception/exception.h"


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
      __UNREFERENCED_PARAMETER(pitem);
      __UNREFERENCED_PARAMETER(straCommand);
      __UNREFERENCED_PARAMETER(straCommandTitle);
      __UNREFERENCED_PARAMETER(context);
      throw ::exception(todo, "core");
      //if (pdata->m_pdocument != nullptr)
      //{
      //   pdata->m_pdocument->OpenSelectionProperties();
      //}
   }

   void callback::on_file_manager_open_context_menu_file(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(itema);
      __UNREFERENCED_PARAMETER(context);
      throw ::exception(todo, "core");
      //if (pdata->m_pdocument != nullptr)
      //{
      //   pdata->m_pdocument->OpenSelectionProperties();
      //}
   }

   void callback::on_file_manager_open_context_menu(::filemanager::data * pdata, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(context);
   }

   //void callback::on_request(::create * pcreate)
   //{

   //   papp->do_request(pcreate);

   //}

   void callback::on_file_manager_open_folder(::filemanager::data * pdata, ::file::item * pitem, const ::action_context & context)
   {
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(pitem);
      __UNREFERENCED_PARAMETER(context);
   }

   
   void callback::on_file_manager_item_command(::filemanager::data * pdata, atom atom, const ::file::item_array & itema)
   {
   
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(atom);
      __UNREFERENCED_PARAMETER(itema);
   
   }

   
   void callback::on_file_manager_item_update(::filemanager::data * pdata, ::message::command * pcommand, const ::file::item_array & itema)
   {
   
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(pcommand);
      __UNREFERENCED_PARAMETER(itema);
   
   }


   void callback::on_file_manager_initialize_form_pre_data(::filemanager::data * pdata, atom atom, ::user::form * pinteractionForm)
   {
      
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(atom);
      __UNREFERENCED_PARAMETER(pinteractionForm);

   }


   //bool callback::GetFileManagerItemCallback(::filemanager::data * pdata, atom atom, const ::file::item_array & itema)
   //{
   //   __UNREFERENCED_PARAMETER(pdata);
   //   __UNREFERENCED_PARAMETER(atom);
   //   __UNREFERENCED_PARAMETER(itema);
   //   return false;
   //}


   bool callback::get_file_manager_item_callback(::filemanager::data * pdata, atom atom, const ::file::item_array & itema)
   {
      
      __UNREFERENCED_PARAMETER(pdata);
      __UNREFERENCED_PARAMETER(atom);
      __UNREFERENCED_PARAMETER(itema);

      return false;

   }


} // namespace filemanager



