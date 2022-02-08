#pragma once


namespace filemanager
{

   
   class data;


   class CLASS_DECL_AURA callback :
      virtual public ::object
   {
   public:


      //callback();
      //virtual ~callback();


      //virtual void on_request(::create * pcreate);


      virtual void on_file_manager_open_context_menu_folder(::filemanager::data * pdata, ::file::item * pitem, string_array & straCommand, string_array & straCommandTitle, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu_file(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & action_context);
      virtual void on_file_manager_open_context_menu(::filemanager::data * pdata, const ::action_context & action_context);
      virtual void on_file_manager_open_folder(::filemanager::data * pdata, ::file::item * pitem, const ::action_context & action_context);
      virtual void on_file_manager_item_update(::filemanager::data * pdata, ::message::command * pcommand, const ::file::item_array & itema);
      virtual void on_file_manager_item_command(::filemanager::data * pdata, atom pszId, const ::file::item_array & itema);
      virtual void on_file_manager_initialize_form_pre_data(::filemanager::data * pdata, atom uId, ::user::form * pinteractionForm);
      virtual void on_file_manager_open(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & action_context);

      virtual bool get_file_manager_item_callback(::filemanager::data* pdata, atom atom, const ::file::item_array& itema);


   };


} // namespace filemanager





