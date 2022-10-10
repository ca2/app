#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list_callback :
      virtual public ::object
   {
   public:

      ::pointer<::image_list>          m_pimagelistSubItemHover;
      ::pointer<::image_list>          m_pimagelistItemHover;
      ::pointer<::image_list>          m_pimagelistNormal;

      file_list_callback();
      virtual ~file_list_callback();

      virtual bool initialize_file_list_callback();

      virtual i32 GetActionButtonCount();
      virtual ::pointer<::image_list>GetActionButtonImageList(atom i);
      virtual void InitializeActionButton(atom i, ::pointer<::user::button>pbutton);
      virtual void OnButtonAction(atom i, ::pointer<::file::item> item);

      virtual bool GetMenuItemCallback(atom iId);
      virtual void OnMenuItemAction(atom iId, const ::file::item_array & itema);
      virtual void GetMenuItemUpdate(atom iId, const ::file::item_array & itema, ::message::command * pcommand);

   };


} // namespace filemanager
