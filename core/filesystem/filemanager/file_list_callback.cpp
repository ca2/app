#include "framework.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/imaging.h"
#include "aura/graphics/image/drawing.h"
#include "file_list_callback.h"
#include "core/platform/system.h"
#include "aura/user/user/button.h"


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

      m_pimagelistSubItemHover = __create_new < ::image_list >();

      m_pimagelistItemHover = __create_new < ::image_list >();

      m_pimagelistNormal = __create_new < ::image_list >();

      ::draw2d::graphics_pointer spgraphics(e_create, this);

      spgraphics->CreateCompatibleDC(nullptr);

      m_pimagelistSubItemHover->create(16, 16, 0, 10, 10);

      m_pimagelistSubItemHover->add(image_payload(this, "matter://filemanager/execute_16.png"));
      m_pimagelistSubItemHover->add(image_payload(this, "matter://filemanager/check_off_16.png"));
      m_pimagelistSubItemHover->add(image_payload(this, "matter://filemanager/check_on_16.png"));

      auto psystem = acmesystem()->m_pcoresystem;

      psystem->imaging().change_hue(
      m_pimagelistNormal,
      m_pimagelistSubItemHover,
      rgb(220, 220, 215),
      0.50);

      m_pimagelistItemHover->color_blend(
      m_pimagelistSubItemHover,
      rgb(220, 220, 215),
      127);

      return true;

   }


   i32 file_list_callback::GetActionButtonCount()
   {
      return 0;
   }

   void file_list_callback::InitializeActionButton(atom atom, ::pointer<::user::button>pbutton)
   {
      switch (atom)
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

   void file_list_callback::OnButtonAction(atom i, ::pointer<::file::item> item)
   {
      __UNREFERENCED_PARAMETER(i);
      __UNREFERENCED_PARAMETER(item);
   }



   bool file_list_callback::GetMenuItemCallback(atom iId)
   {
      __UNREFERENCED_PARAMETER(iId);
      return false;
   }

   void file_list_callback::OnMenuItemAction(atom iId, const ::file::item_array & itema)
   {
      __UNREFERENCED_PARAMETER(iId);
      __UNREFERENCED_PARAMETER(itema);
   }


   void file_list_callback::GetMenuItemUpdate(atom iId, const ::file::item_array & itema, ::message::command * pcommand)
   {

      __UNREFERENCED_PARAMETER(iId);
      __UNREFERENCED_PARAMETER(itema);
      __UNREFERENCED_PARAMETER(pcommand);

   }


   ::pointer<::image_list>file_list_callback::GetActionButtonImageList(atom i)
   {

      __UNREFERENCED_PARAMETER(i);

      return nullptr;

   }


} // namespace filemanager



