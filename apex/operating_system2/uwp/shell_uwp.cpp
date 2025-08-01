//
//  user_shell_metrowin.cpp
//  apex
//
//  Created by Camilo Sasuke Thomas Borregaard Soerensen on 30/12/16.
//  Copyright (c) 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//
#include "framework.h"
#include "apex/compress/zip/context.h"
#include "apex/user/shell.h"
#include "shell_uwp.h"


bool uwp_get_file_image(::image::image *pimage, const ::scoped_string & scopedstr);


namespace universal_windows
{


   shell::shell()
   {

      defer_create_synchronization();

   }


   shell::~shell()
   {

   }


   int shell::get_image_by_extension(const image_key & imagekey, color32_t crBk)
   {

      int iImage = -1;
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
//            synchronous_lock synchronouslock(this->synchronization());
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
//         }         synchronous_lock synchronouslock(this->synchronization());

      m_imagemap.set_at(imagekey, iImage);

      return iImage;

   }


   shell::e_folder shell::get_folder_type(::particle * pparticle, const_char_pointer lpcsz)
   {

      return get_folder_type(pparticle, utf8_to_unicode(lpcsz));

   }


   shell::e_folder shell::get_folder_type(::particle * pparticle, const unichar * lpcszPath)
   {

      string strPath;

      unicode_to_utf8(strPath, lpcszPath);

      if (         auto psystem = system();

         auto pdirectorysystem = psystem->m_pdirectorysystem;

pdirectorysystem->is(strPath))
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


   int shell::impl_get_file_image(const image_key & imagekey)
   {

      int iImage = I32_MINIMUM;

      if (case_insensitive_string_begins(imagekey.m_strPath, "uifs:"))
      {

         ::file::path path = directory()->matter("cloud.ico");

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
      else if (case_insensitive_string_begins(imagekey.m_strPath, "fs:"))
      {

         ::file::path path = directory()->matter("remote.ico");

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
      else if (case_insensitive_string_begins(imagekey.m_strPath, "ftp:"))
      {

         ::file::path path = directory()->matter("ftp.ico");

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

      if (case_insensitive_string_ends(imagekey.m_strPath, ".apex"))
      {
            
         string str = file()->as_string(imagekey.m_strPath);

         if (str.case_insensitive_begins_eat("ca2prompt\r\n"))
         {

            str.trim();

            /*HICON hicon16 = (HICON) ::LoadImage(nullptr, directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            HICON hicon48 = (HICON) ::LoadImage(nullptr, directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
            synchronous_lock sl1(m_pil48Hover->synchronization());
            synchronous_lock sl2(m_pil48->synchronization());
            iImage = m_pil16->add_icon_os_data(hicon16);
            m_pil48Hover->add_icon_os_data(hicon48);

            if (crBk == 0)
            {
               ::apexacmesystem()->imaging().Createcolor_blend_ImageList(
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
      auto pFind = imagekey.m_strPath.is_empty() ? -1 : ::str::case_insensitive_find("://", imagekey.m_strPath);

      character_count iFind2 = imagekey.m_strPath.is_empty() ? -1 : ::str::case_insensitive_find(":", imagekey.m_strPath);

      if (::is_set(pFind) || iFind2 >= 2)
      {

         string strProtocol = string(imagekey.m_strPath).left(maximum(iFind, iFind2));

         int i = 0;

         while (i < strProtocol.length() && character_isalnum(strProtocol[i]))
         {

            i++;

         }

         if (i > 0 && i == strProtocol.length())
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

      if (case_insensitive_string_ends(imagekey.m_strPath, ".sln"))
      {
            
         informationf("test");

      }

      auto pimage48 = create_image({48,  48});

      pimage48->fill(0);

      string strPath = imagekey.m_strPath;

      if (uwp_get_file_image(pimage48, strPath))
      {
            
         auto pimage16 = __create_image({16,  16});

         pimage16->fill(0);

         {

            synchronous_lock sl1(m_pimagelistHover[16]->synchronization());

            synchronous_lock sl2(m_pimagelist[16]->synchronization());

            if (uwp_get_file_image(pimage16, strPath))
            {

               iImage = m_pimagelist[16]->add_image(pimage16, 0, 0);

               m_pimagelistHover[16]->add_image(pimage16, 0, 0);

            }
            else
            {

               pimage48->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

               pimage48->get_graphics()->StretchBlt(0, 0, 48, 48, pimage16->get_graphics(), 0, 0, pimage16->width(), pimage16->height());

               iImage = m_pimagelist[16]->add_image(pimage16, 0, 0);

               m_pimagelistHover[16]->add_image(pimage16, 0, 0);

            }

         }

         synchronous_lock sl1(m_pimagelistHover[48]->synchronization());

         synchronous_lock sl2(m_pimagelist[48]->synchronization());

         iImage = m_pimagelist[48]->add_image(pimage48, 0, 0);

         m_pimagelistHover[48]->add_image(pimage48, 0, 0);

         if (imagekey.m_cr == 0)
         {

            ::apexacmesystem()->imaging().color_blend(m_pimagelist[48], m_pimagelistHover[48], rgb(255, 255, 240), 64);

         }
         else
         {

            *m_pimagelist[48] = *m_pimagelistHover[48];

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

   
} // namespace universal_windows


bool uwp_get_file_image(::image::image *pimage, const ::scoped_string & scopedstr)
{

   return false;

}



