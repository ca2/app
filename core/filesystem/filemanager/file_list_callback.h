// Added ::draw2d::domain_consumer base to filemanager::file_list_callback by
//   camilo on 2026-09-24 05:31 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "aura/graphics/draw2d/domain_consumer.h"


namespace filemanager
{


   class CLASS_DECL_CORE file_list_callback :
      virtual public ::object,
      virtual public ::draw2d::domain_consumer
   {
   public:

      ::image::image_list_pointer           m_pimagelistSubItemHover;
      ::image::image_list_pointer           m_pimagelistItemHover;
      ::image::image_list_pointer           m_pimagelistNormal;

      file_list_callback();
      virtual ~file_list_callback();

      virtual bool initialize_file_list_callback(::draw2d::domain * pdraw2ddomain);

      virtual ::i32 GetActionButtonCount();
      virtual ::image::image_list_pointer GetActionButtonImageList(atom i);
      virtual void InitializeActionButton(const ::atom & atomButton, ::pointer<::user::button>pbutton);
      virtual void OnButtonAction(atom i, ::pointer<::file::item> item);

      virtual bool GetMenuItemCallback(atom iId);
      virtual void OnMenuItemAction(atom iId, const ::file::item_array & itema);
      virtual void GetMenuItemUpdate(atom iId, const ::file::item_array & itema, ::message::command * pcommand);

   };


} // namespace filemanager
