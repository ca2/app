#include "framework.h"
//#include "_filemanager.h"


namespace filemanager
{


   file_list_callback::file_list_callback()
   {
      m_pimagelistSubItemHover = nullptr;
      m_pimagelistItemHover = nullptr;
      m_pimagelistNormal = nullptr;

   }

   file_list_callback::~file_list_callback()
   {

   }


   bool file_list_callback::initialize_file_list_callback()
   {

      m_pimagelistSubItemHover = __new(image_list);

      m_pimagelistItemHover = __new(image_list);

      m_pimagelistNormal = __new(image_list);

      ::draw2d::graphics_pointer spgraphics(e_create);

      spgraphics->CreateCompatibleDC(nullptr);

      m_pimagelistSubItemHover->create(16, 16, 0, 10, 10);

      m_pimagelistSubItemHover->add_file("matter://filemanager/execute_16.png");
      m_pimagelistSubItemHover->add_file("matter://filemanager/check_off_16.png");
      m_pimagelistSubItemHover->add_file("matter://filemanager/check_on_16.png");

      System.imaging().change_hue(
      m_pimagelistNormal,
      m_pimagelistSubItemHover,
      RGB(220, 220, 215),
      0.50);

      System.imaging().color_blend(
      m_pimagelistItemHover,
      m_pimagelistSubItemHover,
      RGB(220, 220, 215),
      127);

      return true;

   }


   i32 file_list_callback::GetActionButtonCount()
   {
      return 0;
   }

   void file_list_callback::InitializeActionButton(id id, __pointer(::user::button) pbutton)
   {
      switch (id)
      {
      case 0: // ExecuteButton
      {
         pbutton->m_plist->m_pimagelistNormal = m_pimagelistSubItemHover;
         pbutton->m_plist->m_iImageNormal = 0;
         pbutton->m_plist->m_pimagelistItemHover = m_pimagelistSubItemHover;
         pbutton->m_plist->m_iImageItemHover = 0;
         pbutton->m_plist->m_pimagelistSubItemHover = m_pimagelistSubItemHover;
         pbutton->m_plist->m_iImageSubItemHover = 0;
      }
      break;
      }
   }

   void file_list_callback::OnButtonAction(id i, __pointer(::file::item)  item)
   {
      UNREFERENCED_PARAMETER(i);
      UNREFERENCED_PARAMETER(item);
   }



   bool file_list_callback::GetMenuItemCallback(id iId)
   {
      UNREFERENCED_PARAMETER(iId);
      return false;
   }

   void file_list_callback::OnMenuItemAction(id iId, const ::file::item_array & itema)
   {
      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(itema);
   }


   void file_list_callback::GetMenuItemUpdate(id iId, const ::file::item_array & itema, ::user::command * pcommand)
   {

      UNREFERENCED_PARAMETER(iId);
      UNREFERENCED_PARAMETER(itema);
      UNREFERENCED_PARAMETER(pcommand);

   }


   __pointer(image_list) file_list_callback::GetActionButtonImageList(id i)
   {

      UNREFERENCED_PARAMETER(i);

      return nullptr;

   }


} // namespace filemanager



