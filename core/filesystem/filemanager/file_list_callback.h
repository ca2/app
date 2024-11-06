#pragma once


namespace filemanager
{


   class CLASS_DECL_CORE file_list_callback :
      virtual public ::object
   {
   public:

      ::image::image_list_pointer           m_pimagelistSubItemHover;
      ::image::image_list_pointer           m_pimagelistItemHover;
      ::image::image_list_pointer           m_pimagelistNormal;

      file_list_callback();
      virtual ~file_list_callback();

      virtual bool initialize_file_list_callback();

      virtual int GetActionButtonCount();
      virtual ::image::image_list_pointer GetActionButtonImageList(atom i);
      virtual void InitializeActionButton(const ::atom & atomButton, ::pointer<::user::button>pbutton);
      virtual void OnButtonAction(atom i, ::pointer<::file::item> item);

      virtual bool GetMenuItemCallback(atom iId);
      virtual void OnMenuItemAction(atom iId, const ::file::item_array & itema);
      virtual void GetMenuItemUpdate(atom iId, const ::file::item_array & itema, ::message::command * pcommand);

   };


} // namespace filemanager
