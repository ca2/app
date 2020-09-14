#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list_callback :
      virtual public ::object
   {
   public:

      __pointer(::image_list)           m_pimagelistSubItemHover;
      __pointer(::image_list)           m_pimagelistItemHover;
      __pointer(::image_list)           m_pimagelistNormal;

      file_list_callback();
      virtual ~file_list_callback();

      virtual bool initialize_file_list_callback();

      virtual i32 GetActionButtonCount();
      virtual __pointer(::image_list) GetActionButtonImageList(id i);
      virtual void InitializeActionButton(id i, __pointer(::user::button) pbutton);
      virtual void OnButtonAction(id i, __pointer(::file::item)  item);

      virtual bool GetMenuItemCallback(id iId);
      virtual void OnMenuItemAction(id iId, const ::file::item_array & itema);
      virtual void GetMenuItemUpdate(id iId, const ::file::item_array & itema, ::user::command * pcommand);

   };


} // namespace filemanager
