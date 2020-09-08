#pragma once


namespace filemanager
{

   
   class data;


   class CLASS_DECL_ACME callback :
      virtual public ::generic
   {
   public:


      //callback();
      //virtual ~callback();


      //virtual void on_request(::create * pcreate);


      virtual void on_file_manager_open_context_menu_folder(::filemanager::data * pdata, ::file::item * pitem, string_array & straCommand, string_array & straCommandTitle, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu_file(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu(::filemanager::data * pdata, const ::action_context & action_context);
      virtual void on_file_manager_open_folder(::filemanager::data * pdata, ::file::item * pitem, const ::action_context & action_context);
      virtual void on_file_manager_item_update(::filemanager::data * pdata, ::user::command * pcommand, const ::file::item_array & itema);
      virtual void on_file_manager_item_command(::filemanager::data * pdata, id pszId, const ::file::item_array & itema);
      virtual void on_file_manager_initialize_form_pre_data(::filemanager::data * pdata, id uiId, ::user::interaction * pinteractionForm);
      virtual void on_file_manager_open(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & action_context);

      virtual bool get_file_manager_item_callback(::filemanager::data* pdata, id id, const ::file::item_array& itema);


   };


} // namespace filemanager





