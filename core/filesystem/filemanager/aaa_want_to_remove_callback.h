#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE callback :
      virtual public ::object
   {
   public:


      callback();
      virtual ~callback();


      virtual void on_request(::request * prequest) override;


      virtual void OnFileManagerOpenContextMenuFolder(::filemanager::data * pdata, ::file::item * pitem, string_array & straCommand, string_array & straCommandTitle, const ::action_context & action_context);
      virtual void OnFileManagerOpenContextMenuFile(::filemanager::data * pdata, const ::file::item_array & itema, const ::action_context & action_context);
      virtual void OnFileManagerOpenContextMenu(::filemanager::data * pdata, const ::action_context & action_context);
      virtual void OnFileManagerOpenFolder(::filemanager::data * pdata, ::file::item * pitem, const ::action_context & action_context);
      virtual bool GetFileManagerItemCallback(::filemanager::data * pdata, atom atom, const ::file::item_array & itema);
      virtual void OnFileManagerItemUpdate(::filemanager::data * pdata, ::message::command * pcommand, const ::file::item_array & itema);
      virtual void OnFileManagerItemCommand(::filemanager::data * pdata, atom pszId, const ::file::item_array & itema);
      virtual void OnFileManagerInitializeFormPreData(::filemanager::data * pdata, atom uId, ::user::form * pform);


   };


} // namespace filemanager





