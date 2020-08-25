#pragma once


#include <shlobj.h>
#include <Shellapi.h>
#include <CommonControls.h>


namespace user
{


   namespace shell
   {


      class CLASS_DECL_BASE windows :
         virtual public ::user::shell::shell
      {
      public:


         comptr < IMalloc >                              m_pmalloc;
         comptr < IShellFolder >                         m_pfolderDesktop;
         comptr < IImageList >                           m_pilSmall;
         comptr < IImageList >                           m_pilLarge;
         comptr < IImageList >                           m_pilExtraLarge;
         comptr < IImageList >                           m_pilJumbo;



         windows();
         virtual ~windows();


         virtual ::estatus initialize(::object * pobjectContext) override;


         virtual i32 impl_get_file_image(oswindow oswindow, const image_key & key) override;


         i32 get_file_image(oswindow oswindow, image_key key, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * pcszExtra, COLORREF crBk);

         i32 get_image_by_file_extension(oswindow oswindow, image_key & key);


         i32 add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
         i32 add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, COLORREF crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);


         i32 get_file_image(oswindow oswindow, image_key key, const unichar * pcszExtra, COLORREF crBk);



///         virtual i32 get_extension_image(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk = 0) override;

         i32 add_icon(int iSize, HICON hicon, COLORREF crBk, int iImage);

         i32 add_icon_path(::file::path path, COLORREF crBk, int iImage);

         i32 add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, COLORREF crBck, bool & bUsedImageList, int iImage);


         virtual ::user::shell::e_folder get_folder_type(::object * pobject, const unichar * pcszPath) override;

         virtual ::user::shell::e_folder get_folder_type(::object * pobject, const char * pcszPath) override;



         virtual void set_image_ico(string strIconLocation, i32 & iImage, COLORREF crBk);
         virtual void set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, COLORREF crBk);




      };


   } // namespace windows


} // namespace filemanager


