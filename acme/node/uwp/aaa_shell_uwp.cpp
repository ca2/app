//
//  user_shell_metrowin.cpp
//  acme
//
//  Created by Camilo Sasuke Tsumanuma on 30/12/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "acme/compress/zip/context.h"
#include "acme/user/shell.h"
#include "shell_uwp.h"


bool uwp_get_file_image(::image * pimage, const char * psz);


namespace uwp
{


   shell::shell()
   {

      defer_create_mutex();

   }


   shell::~shell()
   {

   }


   i32 shell::get_image_by_extension(const image_key & imagekey, color32_t crBk)
   {

      i32 iImage = -1;
//
//         SHFILEINFOW shfi16;
//
//         SHFILEINFOW shfi48;
//
//         wstring wstrFilePath;
//
//         imagekey.m_strPath = "foo";
//
//         imagekey.m_pszShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         {
//
//            synchronous_lock synchronouslock(mutex());
//
//            if (m_pimagemap->lookup(imagekey, iImage))
//            {
//
//               return iImage;
//
//            }
//
//         }
//
//         if (imagekey.m_eattribute.has(file_attribute_directory))
//         {
//
//            SHGetFileInfoW(
//               L"foo",
//               FILE_ATTRIBUTE_DIRECTORY,
//               &shfi16,
//               sizeof(shfi16),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_SMALLICON);
//
//            SHGetFileInfoW(
//               L"foo",
//               FILE_ATTRIBUTE_DIRECTORY,
//               &shfi48,
//               sizeof(shfi48),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_LARGEICON);
//
//         }
//         else
//         {
//
//            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_pszExtension);
//
//            SHGetFileInfoW(
//               wstrFilePath,
//               FILE_ATTRIBUTE_NORMAL,
//               &shfi16,
//               sizeof(shfi16),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_SMALLICON);
//
//            SHGetFileInfoW(
//               wstrFilePath,
//               FILE_ATTRIBUTE_NORMAL,
//               &shfi48,
//               sizeof(shfi48),
//               SHGFI_USEFILEATTRIBUTES
//               | SHGFI_ICON
//               | SHGFI_LARGEICON);
//
//         }
//         per_fork f(false);
//         if (pfork == nullptr)
//         {
//            f.init();
//            pfork = &f;
//
//         }
//
//         bool b16 = false;
//         bool b48 = false;
//         iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
//         if (!b16 && shfi16.hIcon != nullptr)
//         {
//            ::DestroyIcon(shfi16.hIcon);
//         }
//         if (!b48 && shfi48.hIcon != nullptr)
//         {
//            ::DestroyIcon(shfi48.hIcon);
//         }         synchronous_lock synchronouslock(mutex());

      m_imagemap.set_at(imagekey, iImage);

      return iImage;

   }


   shell::e_folder shell::get_folder_type(::matter * pobject, const char * lpcsz)
   {

      return get_folder_type(pobject, ::str::international::utf8_to_unicode(lpcsz));

   }


   shell::e_folder shell::get_folder_type(::matter * pobject, const unichar * lpcszPath)
   {

      string strPath;

      ::str::international::unicode_to_utf8(strPath, lpcszPath);

      if (dir::is(strPath))
      {
            
         return folder_file_system;

      }
      else
      {

         zip_context zip(get_context());

         if (zip.is_unzippable(strPath))
         {

            return folder_zip;

         }
         else
         {

            return folder_none;

         }

      }

   }


   i32 shell::impl_get_file_image(const image_key & imagekey)
   {

      i32 iImage = 0x80000000;

      if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
      {

         ::file::path path = pcontext->m_papexcontext->dir().matter("cloud.ico");

//       for (auto iSize : m_iaSize)
//       {
//
//          HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//          iImage = add_icon(iSize, hicon, crBk);
//
//       }

         single_lock synchronouslock(mutex(), true);

         m_imagemap.set_at(imagekey, iImage);

         return iImage;

      }
      else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
      {

         ::file::path path = pcontext->m_papexcontext->dir().matter("remote.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(mutex(), true);

         m_imagemap.set_at(imagekey, iImage);

         return iImage;

      }
      else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
      {

         ::file::path path = pcontext->m_papexcontext->dir().matter("ftp.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(mutex(), true);

         m_imagemap.set_at(imagekey, iImage);

         return iImage;

      }

      if (::str::ends_ci(imagekey.m_strPath, ".acme"))
      {
            
         string str = pcontext->m_papexcontext->file().as_string(imagekey.m_strPath);

         if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
         {

            str.trim();

            /*HICON hicon16 = (HICON) ::LoadImage(nullptr, pcontext->m_papexcontext->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            HICON hicon48 = (HICON) ::LoadImage(nullptr, pcontext->m_papexcontext->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
            synchronous_lock sl1(m_pil48Hover->mutex());
            synchronous_lock sl2(m_pil48->mutex());
            iImage = m_pil16->add_icon_os_data(hicon16);
            m_pil48Hover->add_icon_os_data(hicon48);

            if (crBk == 0)
            {
               ::acme::get_system()->imaging().Createcolor_blend_ImageList(
                  m_pil48,
                  m_pil48Hover,
                  rgb(255, 255, 240),
                  64);
            }
            else
            {
               *m_pil48 = *m_pil48Hover;
            }*/

         }

         return iImage;

      }

      // try to find "uifs:// http:// ftp:// like addresses"
      // then should show icon by extension or if is folder
      strsize iFind = imagekey.m_strPath.is_empty() ? -1 : ::str::find_ci("://", imagekey.m_strPath);

      strsize iFind2 = imagekey.m_strPath.is_empty() ? -1 : ::str::find_ci(":", imagekey.m_strPath);

      if (iFind >= 0 || iFind2 >= 2)
      {

         string strProtocol = string(imagekey.m_strPath).Left(maximum(iFind, iFind2));

         i32 i = 0;

         while (i < strProtocol.get_length() && ansi_char_is_alphanumeric(strProtocol[i]))
         {

            i++;

         }

         if (i > 0 && i == strProtocol.get_length())
         {

            // heuristically valid protocol
            return get_image_by_extension(imagekey, imagekey.m_cr);

         }

         if (imagekey.m_eattribute.has(file_attribute_directory))
         {

            return get_image_by_extension(imagekey, imagekey.m_cr);

         }

      }

      string strExtension;

      if (::str::ends_ci(imagekey.m_strPath, ".sln"))
      {
            
         output_debug_string("test");

      }

      auto pimage48 = create_image({48,  48});

      pimage48->fill(0);

      string strPath = imagekey.m_strPath;

      if (uwp_get_file_image(pimage48, strPath))
      {
            
         auto pimage16 = __create_image({16,  16});

         pimage16->fill(0);

         {

            synchronous_lock sl1(m_pilHover[16]->mutex());

            synchronous_lock sl2(m_pil[16]->mutex());

            if (uwp_get_file_image(pimage16, strPath))
            {

               iImage = m_pil[16]->add_image(pimage16, 0, 0);

               m_pilHover[16]->add_image(pimage16, 0, 0);

            }
            else
            {

               pimage48->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

               pimage48->get_graphics()->StretchBlt(0, 0, 48, 48, pimage16->get_graphics(), 0, 0, pimage16->width(), pimage16->height());

               iImage = m_pil[16]->add_image(pimage16, 0, 0);

               m_pilHover[16]->add_image(pimage16, 0, 0);

            }

         }

         synchronous_lock sl1(m_pilHover[48]->mutex());

         synchronous_lock sl2(m_pil[48]->mutex());

         iImage = m_pil[48]->add_image(pimage48, 0, 0);

         m_pilHover[48]->add_image(pimage48, 0, 0);

         if (imagekey.m_cr == 0)
         {

            ::acme::get_system()->imaging().color_blend(m_pil[48], m_pilHover[48], rgb(255, 255, 240), 64);

         }
         else
         {

            *m_pil[48] = *m_pilHover[48];

         }

         return iImage;

      }

      string str(imagekey.m_strPath);

      iImage = -1;

      return iImage;

   }


   void shell::do_initialize()
   {

   }

   
} // namespace uwp


bool uwp_get_file_image(::image * pimage, const char * psz)
{

   return false;

}



