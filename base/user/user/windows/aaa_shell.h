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


         virtual ::e_status initialize(::object * pobject) override;


         virtual i32 impl_get_file_image(oswindow oswindow, const image_key & key) override;


         i32 get_file_image(oswindow oswindow, image_key key, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * pcszExtra, color32_t crBk);

         i32 get_image_by_file_extension(oswindow oswindow, image_key & key);


         i32 add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, color32_t crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);
         i32 add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, color32_t crBk, bool & bUsedImageList16, bool & bUsedImageList48, int iImage);


         i32 get_file_image(oswindow oswindow, image_key key, const unichar * pcszExtra, color32_t crBk);



///         virtual i32 get_extension_image(oswindow oswindow, const ::string & strExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk = 0) override;

         i32 add_icon(int iSize, HICON hicon, color32_t crBk, int iImage);

         i32 add_icon_path(::file::path path, color32_t crBk, int iImage);

         i32 add_system_icon(int iSize, IImageList * plist, SHFILEINFOW * pinfo, color32_t crBck, bool & bUsedImageList, int iImage);


         virtual ::user::shell::e_folder get_folder_type(::object * pobject, const unichar * pcszPath) override;

         virtual ::user::shell::e_folder get_folder_type(::object * pobject, const ::string & pcszPath) override;



         virtual void set_image_ico(string strIconLocation, i32 & iImage, color32_t crBk);
         virtual void set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, color32_t crBk);




      };


   } // namespace windows


} // namespace filemanager


