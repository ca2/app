#pragma once


#include <shlobj.h>
#include <Shellapi.h>
#include <CommonControls.h>


#include "aura/user/user/shell.h"


namespace windows
{


   class CLASS_DECL_CORE shell :
      virtual public ::user::shell,
      virtual public ::user::message_queue_listener
   {
   public:


      comptr < IMalloc >                              m_pmalloc;
      comptr < IShellFolder >                         m_pfolderDesktop;
      comptr < IImageList >                           m_pilSmall;
      comptr < IImageList >                           m_pilLarge;
      comptr < IImageList >                           m_pilExtraLarge;
      comptr < IImageList >                           m_pilJumbo;
      __composite(::user::message_queue)              m_pmessagequeue;



      shell();
      virtual ~shell();


      virtual ::estatus initialize(::object * pobjectContext) override;


      virtual i32 impl_get_file_image(const image_key & key) override;


      i32 get_file_image(image_key key, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * pcszExtra, COLORREF crBk);

      i32 get_image_by_file_extension(image_key & key);


      i32 add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
      i32 add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);


      i32 get_file_image(image_key key, const unichar * pcszExtra, COLORREF crBk);



///         virtual i32 get_extension_image(const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;

      i32 add_icon(int iSize, HICON hicon, COLORREF crBk, int iImage);

      i32 add_icon_path(::file::path path, COLORREF crBk, int iImage);

      i32 add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, COLORREF crBck, bool & bUsedImageList, int iImage);


      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const unichar * pcszPath) override;

      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const char * pcszPath) override;



      virtual void set_image_ico(string strIconLocation, i32 & iImage, COLORREF crBk);
      virtual void set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, COLORREF crBk);

      virtual void set_finish() override;

      //int shell::add_hover_image(int iSize, int iImage, COLORREF crBk)

   };


} // namespace filemanager




