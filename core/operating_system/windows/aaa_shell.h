#pragma once


#include <shlobj.h>
#include <Shellapi.h>
#include <CommonControls.h>


#include "core/user/user/shell.h"


namespace windows
{


   class CLASS_DECL_CORE shell :
      virtual public ::user::shell
      //, virtual public ::user::message_queue_listener
   {
   public:


      comptr < IMalloc >                              m_pmalloc;
      comptr < IShellFolder >                         m_pfolderDesktop;
      comptr < IImageList >                           m_pimagelistSmall;
      comptr < IImageList >                           m_pimagelistLarge;
      comptr < IImageList >                           m_pimagelistExtraLarge;
      comptr < IImageList >                           m_pimagelistJumbo;
      //::pointer<::user::message_queue>             m_pmessagequeue;



      shell();
      virtual ~shell();


      virtual void initialize(::object * pobject) override;


      virtual i32 impl_get_file_image(const image_key & key) override;


      i32 get_file_image(image_key key, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * pcszExtra, ::color::color crBk);

      i32 get_image_by_file_extension(image_key & key);


      i32 add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, ::color::color crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
      i32 add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, ::color::color crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);


      i32 get_file_image(image_key key, const unichar * pcszExtra, ::color::color crBk);



///         virtual i32 get_extension_image(const ::string & strExtension, e_file_attribute eattribute, e_icon eicon, ::color::color crBk = 0) override;

      i32 add_icon(int iSize, HICON hicon, ::color::color crBk, int iImage);

      i32 add_icon_path(::file::path path, ::color::color crBk, int iImage);

      i32 add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, ::color::color crBck, bool & bUsedImageList, int iImage);


      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const unichar * pcszPath) override;

      virtual ::user::shell::e_folder get_folder_type(::object * pobject, const ::string & pcszPath) override;



      virtual void set_image_ico(string strIconLocation, i32 & iImage, ::color::color crBk);
      virtual void set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, ::color::color crBk);

      virtual void finish(::property_object * pobject) override;

      //int shell::add_hover_image(int iSize, int iImage, ::color::color crBk)

   };


} // namespace filemanager




