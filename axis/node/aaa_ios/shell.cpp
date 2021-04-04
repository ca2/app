//
//  user_shell_ios.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 30/12/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"

#include "aura/compress/zip/context.h"

#include "shell.h"


bool ios_get_file_image(::image * pimage, const char * psz);


namespace ios
{


   shell::shell()
   {

      defer_create_mutex();
      //begin();

      //SHGetImageList(SHIL_SMALL, IID_IImageList, m_pilSmall);
      //SHGetImageList(SHIL_LARGE, IID_IImageList, m_pilLarge);
      //SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);
      //SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pilJumbo);
      /// SHGetMalloc(&m_pmalloc);

      //int iThreadCount = get_processor_count() * 2;

//      int iThreadCount = 1; // for ios
//
//      for (index i = 0; i < iThreadCount; i++)
//      {
//
//         m_threadaGetImage.add(::fork(get_application(),
//                                      [&]()
//         {
//
//            ::parallelization::set_priority(::priority_highest);
//            shell_run();
//
//         }));
//
//      }

   }


   shell::~shell()
   {

   }


   i32 shell::get_image_by_extension(image_key & key, color32_t crBk)
   {

      return 0x80000000;

   }


   i32 shell::get_foo_image(image_key imagekey, color32_t crBk)
   {

      i32 iImage = -1;

      m_imagemap.set_at(imagekey, iImage);

      return iImage;

   }


   i32 shell::get_image(image_key imagekey, const unichar * lpcszExtra, color32_t crBk)
   {

      i32 iImage = 0x80000000;

      if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
      {

         ::file::path path = pcontext->m_papexcontext->dir().matter("cloud.ico");

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

      if (::str::ends_ci(imagekey.m_strPath, ".aura"))
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
               psystem->imaging().Createcolor_blend_ImageList(
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
      strsize iFind = ::str::find_ci("://", imagekey.m_strPath);
      strsize iFind2 = ::str::find_ci(":", imagekey.m_strPath);
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
            return get_image_by_extension(imagekey, crBk);

         }

         if (imagekey.m_eattribute.has(file_attribute_directory))
         {

            return get_image_by_extension(imagekey, crBk);

         }

      }

      //#ifdef WINDOWS_DESKTOP

      string strExtension;

      if (::str::ends_ci(imagekey.m_strPath, ".sln"))
      {
         output_debug_string("test");
      }

      auto pimage48 = __create_image({48,  48});

      pimage48->fill(0);

      string strPath = imagekey.m_strPath;

      if (ios_get_file_image(pimage48, strPath))
      {
         
         auto pimage16 = __create_image({16,  16});

         pimage16->fill(0);

         {
            
            synchronous_lock sl1(m_pilHover[16]->mutex());
            
            synchronous_lock sl2(m_pil[16]->mutex());
            
            if (ios_get_file_image(pimage16, strPath))
            {
               
               iImage = m_pil[16]->add_image(pimage16, 0, 0);
               
               m_pilHover[16]->add_image(pimage16, 0, 0);

            }
            else
            {

               pimage16->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

               pimage16->get_graphics()->StretchBlt(0, 0, 48, 48, pimage48->get_graphics(), 0, 0, pimage48->width(), pimage48->height());

               iImage = m_pil[16]->add_image(pimage16, 0, 0);

               m_pilHover[16]->add_image(pimage16, 0, 0);

            }

         }

         synchronous_lock sl1(m_pilHover[48]->mutex());

         synchronous_lock sl2(m_pil[48]->mutex());

         iImage = m_pil[48]->add_image(pimage48, 0, 0);

         m_pilHover[48]->add_image(pimage48, 0, 0);

         if (crBk == 0)
         {

            psystem->imaging().color_blend(
            m_pil[48],
            m_pilHover[48],
            rgb(255, 255, 240),
            64);

         }
         else
         {

            *m_pil[48] = *m_pilHover[48];

         }

         return iImage;

      }

      string str(imagekey.m_strPath);

      iImage = -1;


      //#endif

      return iImage;

   }


//   i32 ios::get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, color32_t crBk)
//   {
//
//#ifdef WINDOWS_DESKTOP
//
//      return get_foo_image(pfork, oswindow, key, crBk);
//
//#else
//
//      return 0x80000000;
//
//#endif // WINDOWS_DESKTOP
//
//   }


//   i32 ios::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, LPITEMIDLIST lpiidlChild, const unichar * lpcszExtra, color32_t crBk)
////      {
////
////         int iImage = 0x80000000;
////
////         ::ios::comptr < IShellFolder> lpsf;
////
////         if (pfork->m_pfolder.is_set())
////         {
////
////            lpsf = pfork->m_pfolder;
////
////         }
////         else
////         {
////
////            lpsf = _017GetShellParentFolder(pfork, lpiidlAbsolute);
////
////            pfork->m_pfolder = lpsf;
////
////            pfork->m_strFolder = ::file::path(imagekey.m_strPath).folder();
////
////         }
////
////         if (lpsf.is_null())
////         {
////
////            return 0x80000000;
////
////         }
////
////         i32 iType;
////         switch (imagekey.m_eicon)
////         {
////         case icon_normal:
////            iType = 0;
////            break;
////         case icon_open:
////            iType = GIL_OPENICON;
////            break;
////         default:
////            // unexpected icon type
////            ASSERT(false);
////            return 0x80000000;
////         }
////
////
////         string strFilePath(imagekey.m_strPath);
////
////         char szPath[_MAX_PATH * 6];
////         WCHAR wszPath[_MAX_PATH * 6];
////         string strPath;
////
////         const char * pszPathParam = imagekey.m_strPath;
////
////         HICON hicon16 = nullptr;
////         HICON hicon48 = nullptr;
////         HRESULT hrIconLocation;
////         HRESULT hrExtract;
////         string strExpandEnv;
////
////         string strPathEx(strFilePath);
////         string strExtra;
////
////         ::str::international::unicode_to_utf8(strExtra, lpcszExtra);
////
////         if (strExtra.get_length() > 0)
////         {
////            strPathEx += ":" + strExtra;
////         }
////
////         wstring wstrPath;
////         i32 iIcon = 0x80000000;
////
////         SHFILEINFOW shfi16;
////         SHFILEINFOW shfi48;
////
////         ::ios::comptr < IExtractIconW > lpiextracticon;
////         ::ios::comptr < IShellIconOverlayIdentifier > lpioverlay;
////         ::ios::comptr < IExtractImage > lpiextractimage;
////
////         ::u32 uExtractIconLocationFlags = 0;
////
////         bool bMaybeLink = true;
////
////         if (SUCCEEDED(lpsf->GetUIObjectOf(
////            oswindow,
////            1,
////            (LPCITEMIDLIST *)&lpiidlChild,
////            IID_IExtractIconW,
////            nullptr,
////            lpiextracticon)))
////         {
////
////            if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
////               iType,
////               wszPath,
////               sizeof(wszPath) / sizeof(wszPath[0]),
////               &iIcon,
////               &uiExtractIconLocationFlags)))
////            {
////
////               if (wcscmp(wszPath, L"*") == 0)
////               {
////
////                  strsize iFind = strFilePath.reverse_find('.');
////
////                  imagekey.m_iIcon = 0x80000000;
////                  imagekey.m_strExtension = (char*)&strFilePath[iFind+1];
////                  imagekey.m_strPath = "";
////
////                  bMaybeLink = false;
////
////               }
////               else
////               {
////
////                  strFilePath = wszPath;
////
////                  strFilePath = expand_env(strFilePath);
////
////                  imagekey.set_path(strFilePath);
////
////                  if (::str::ends_ci(strFilePath, ".lnk"))
////                  {
////
////                     string strTarget;
////
////                     string strFolder;
////
////                     string strParams;
////
////                     //if(pcontext->m_papexcontext->file().resolve_link(strTarget, strFilePath, psystem->ui_from_handle))
////                     if (pcontext->m_papexcontext->file().resolve_link(strTarget, strFolder, strParams, strFilePath, nullptr))
////                     {
////
////                        if (m_straThemeableIconName.get_count() > 0)
////                        {
////
////                           index i = m_straThemeableIconName.predicate_find_first(
////                              [=](auto & str)
////                           {
////                              return ::str::ends_ci(imagekey.m_strPath, str);
////                           }
////                           );
////
////                           if (i >= 0)
////                           {
////
////                              string str = m_straThemeableIconName[i];
////
////                              if (::str::ends_ci(imagekey.m_strPath, str))
////                              {
////
////                                 strExpandEnv = imagekey.m_strPath;
////                                 strExpandEnv.replace_ci(str, m_strShellThemePrefix + str);
////                                 imagekey.m_strPath = (char*)strExpandEnv.c_str();
////
////                              }
////
////                           }
////
////                        }
////
////                     }
////
////                  }
////
////                  imagekey.m_iIcon = iIcon;
////
////                  imagekey.m_strExtension = "";
////
////               }
////            }
////         }
////         else if (SUCCEEDED(lpsf->GetUIObjectOf(
////            oswindow,
////            1,
////            (LPCITEMIDLIST *)&lpiidlChild,
////            IID_IShellIconOverlayIdentifier,
////            nullptr,
////            lpioverlay)))
////         {
////            int iIndex = 0;
////            ::u32 dwFlags = 0;
////            if (SUCCEEDED(hrIconLocation = lpioverlay->GetOverlayInfo(
////               wszPath,
////               sizeof(wszPath),
////               &iIndex,
////               &dwFlags)))
////            {
////               if (*wszPath == L'*' && wszPath[1] == '\0')
////               {
////                  strsize iFind = strFilePath.reverse_find('.');
////
////                  imagekey.m_iIcon = 0x80000000;
////                  imagekey.m_strExtension = (char *)&strFilePath.Mid(iFind);
////                  imagekey.m_strPath = "";
////               }
////               else
////               {
////                  strFilePath = expand_env(szPath);
////                  imagekey.m_strPath = (char *)strFilePath.c_str();
////                  imagekey.m_iIcon = iIcon;
////                  imagekey.m_strExtension = "";
////               }
////            }
////         }
////         else if (SUCCEEDED(lpsf->GetUIObjectOf(
////            oswindow,
////            1,
////            (LPCITEMIDLIST *)&lpiidlChild,
////            IID_IExtractImage,
////            nullptr,
////            lpiextractimage)))
////         {
////            SIZE32 s;
////            s.cx = 48;
////            s.cy = 48;
////            ::u32 dwDepth = 32;
////            ::u32 dwFlags = 0;
////            if (SUCCEEDED(hrIconLocation = lpiextractpimage->GetLocation(
////               wszPath,
////               sizeof(wszPath),
////               nullptr,
////               &s,
////               dwDepth,
////               &dwFlags)))
////            {
////               string strP = wszPath;
////               if (strcmp(strP, "*") == 0)
////               {
////                  strsize iFind = strFilePath.reverse_find('.');
////
////                  imagekey.m_iIcon = 0x80000000;
////                  imagekey.m_strExtension = (char *)&strFilePath.Mid(iFind);
////                  imagekey.m_strPath = "";
////               }
////               else
////               {
////                  //imagekey.m_strPath = expand_env(strP);
////                  strFilePath = expand_env(strP);
////                  imagekey.m_strPath = (char *)strFilePath.c_str();
////                  imagekey.m_iIcon = iIcon;
////                  imagekey.m_strExtension = "";
////               }
////            }
////         }
////         else
////         {
////
////            imagekey.m_strPath = (char *)strFilePath.c_str();
////            imagekey.m_iIcon = iIcon;
////            imagekey.m_strExtension = "";
////
////         }
////
////         if (bMaybeLink && imagekey.m_iIcon == 0x80000000)
////         {
////
////            string strTarget;
////
////            string strFolder;
////
////            string strParams;
////
////            if (pcontext->m_papexcontext->file().resolve_link(strTarget, strFolder, strParams, strFilePath, nullptr))
////            {
////
////               wstring wstr = ::str::international::utf8_to_unicode(strTarget);
////
////               imagekey.set_path(strTarget);
////
////               return get_image(pfork, oswindow, imagekey, nullptr, crBk);
////
////
////            }
////
////         }
////
////         synchronous_lock synchronouslock(mutex());
////
////         if (!m_pimagemap->lookup(imagekey, iImage))
////         {
////
////            synchronouslock.unlock();
////
////            if (imagekey.m_iIcon == 0x80000000)
////            {
////
////               if (wcslen(wszPath) > 0 && wcscmp(wszPath, L"*") != 0)
////               {
////
////                  ::file::path p = wszPath;
////
////                  string strExtension = p.extension();
////
////                  if (m_strShellThemePrefix.has_char())
////                  {
////
////                     image_key imagekey;
////
////                     string strFooPath = m_strShellThemePrefix + "foo." + strExtension;
////
////                     imagekey.m_strPath = (char *)(const char *)strFooPath;
////                     imagekey.m_iIcon = 0;
////                     imagekey.m_strExtension = "";
////
////                     {
////
////                        synchronous_lock synchronouslock(mutex());
////
////                        if (m_pimagemap->lookup(imagekey, iImage))
////                           return iImage;
////
////                     }
////
////                     ::file::path p = ::file::path(strFooPath);
////
////                     string strIcon;
////
////                     strIcon = pacmedir->config() / "ios/app_theme" / m_strShellThemePrefix + strExtension + ".ico";
////
////                     for (auto iSize : m_iaSize)
////                     {
////
////                        HICON hicon = (HICON)LoadImage(nullptr, strIcon, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////                        iImage = add_icon(iSize, hicon, crBk);
////
////                     }
////
////                     synchronous_lock synchronouslock(mutex());
////
////                     m_pimagemap->set_at(imagekey, iImage);
////
////                     return iImage;
////
////                  }
////
////                  try
////                  {
////
//////                     hicon16 = nullptr;
////
////                     strPath.Truncate(0);
////
////                     strPath.free_extra();
////
////                     strPath = imagekey.m_strPath;
////
////                     HICON hicon32 = nullptr;
////
////                     SHGetFileInfoW(
////                        wszPath,
////                        FILE_ATTRIBUTE_NORMAL,
////                        &shfi16,
////                        sizeof(shfi16),
////                        SHGFI_ICON
////                        | SHGFI_OVERLAYINDEX
////                        | SHGFI_SMALLICON);
////                     hicon16 = shfi16.hIcon;
////                     SHGetFileInfoW(
////                        wszPath,
////                        FILE_ATTRIBUTE_NORMAL,
////                        &shfi48,
////                        sizeof(shfi48),
////                        SHGFI_ICON
////                        | SHGFI_OVERLAYINDEX
////                        | SHGFI_LARGEICON);
////
////                     hicon48 = shfi48.hIcon;
////
////                     if (hicon16 != nullptr || hicon48 != nullptr)
////                     //if (hicon48 != nullptr)
////                     {
////                        bool b16 = false;
////                        bool b48 = false;
////                        iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
////                        if (!b16 && shfi16.hIcon != nullptr)
////                        {
////                           ::DestroyIcon(shfi16.hIcon);
////                        }
////                        if (!b48 && shfi48.hIcon != nullptr)
////                        {
////                           ::DestroyIcon(shfi48.hIcon);
////                        }
////                        //                        iImage = add_icon_set(pfork, nullptr, &shfi48, crBk);
////                        synchronous_lock synchronouslock(mutex());
////
////                        m_pimagemap->set_at(imagekey, iImage);
////
////                     }
////
////                  }
////                  catch (...)
////                  {
////
////                  }
////
////               }
////
////               if (iImage < 0)
////               {
////
////                  iImage = get_foo_image(pfork, oswindow, imagekey, crBk);
////
////               }
////
////            }
////            else
////            {
////
////               try
////               {
////
////                  HICON hicon32 = nullptr;
////
////                  if (strlen(pszPathParam) > 0)
////                  {
////
////                     SHGetFileInfoW(
////                        wstring(pszPathParam),
////                        FILE_ATTRIBUTE_NORMAL,
////                        &shfi16,
////                        sizeof(shfi16),
////                        SHGFI_ICON
////                        | SHGFI_SMALLICON);
////                     hicon16 = shfi16.hIcon;
////                     SHGetFileInfoW(
////                        wstring(pszPathParam),
////                        FILE_ATTRIBUTE_NORMAL,
////                        &shfi48,
////                        sizeof(shfi48),
////                        SHGFI_ICON
////                        | SHGFI_LARGEICON);
////
////                     hicon48 = shfi48.hIcon;
////
////                     bool b16 = false;
////                     bool b48 = false;
////                     iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
////                     if (!b16 && shfi16.hIcon != nullptr)
////                     {
////                        ::DestroyIcon(shfi16.hIcon);
////                     }
////                     if (!b48 && shfi48.hIcon != nullptr)
////                     {
////                        ::DestroyIcon(shfi48.hIcon);
////                     }                     //iImage = add_icon_set(pfork, nullptr, &shfi48, crBk);
////
////                     synchronous_lock synchronouslock(mutex());
////
////                     m_pimagemap->set_at(imagekey, iImage);
////
////                  }
////                  else
////                  {
////                     HICON hicon16;
////                     ExtractIconExW(
////                        wstring(imagekey.m_strPath),
////                        imagekey.m_iIcon,
////                        &hicon32,
////                        &hicon16,
////                        1);
////
////                     if (hicon48 == nullptr && ::str::ends_ci(imagekey.m_strPath, ".ico"))
////                     {
////
////                        hicon48 = (HICON)LoadImage(nullptr, imagekey.m_strPath, IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
////
////                     }
////                     if (hicon48 == nullptr)
////                     {
////
////                        hicon48 = ExtractResourceIcon(imagekey.m_strPath, 48, 48, imagekey.m_iIcon);
////
////                     }
////
////                     if (hicon48 == nullptr)
////                     {
////
////                        if (hicon32 != nullptr)
////                        {
////
////                           hicon48 = hicon32;
////                        }
////                        else
////                        {
////
////                           hicon48 = hicon16;
////
////                        }
////
////                     }
////
////                     if (hicon16 == nullptr)
////                     {
////                        SHGetFileInfoW(
////                           L"foo",
////                           FILE_ATTRIBUTE_NORMAL,
////                           &shfi16,
////                           sizeof(shfi16),
////                           SHGFI_USEFILEATTRIBUTES
////                           | SHGFI_ICON
////                           | SHGFI_SMALLICON);
////                        hicon16 = shfi16.hIcon;
////                     }
////                     if (hicon48 == nullptr)
////                     {
////                        SHGetFileInfoW(
////                           L"foo",
////                           FILE_ATTRIBUTE_NORMAL,
////                           &shfi48,
////                           sizeof(shfi48),
////                           SHGFI_USEFILEATTRIBUTES
////                           | SHGFI_ICON
////                           | SHGFI_LARGEICON);
////                        hicon48 = shfi48.hIcon;
////                     }
////
////                     //iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk);
////                     bool b16 = false;
////                     bool b48 = false;
////                     iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
////                     if (!b16 && shfi16.hIcon != nullptr)
////                     {
////                        ::DestroyIcon(shfi16.hIcon);
////                     }
////                     if (!b48 && shfi48.hIcon != nullptr)
////                     {
////                        ::DestroyIcon(shfi48.hIcon);
////                     }                     synchronous_lock synchronouslock(mutex());
////
////                     m_pimagemap->set_at(imagekey, iImage);
////
////                  }
////
////               }
////               catch (...)
////               {
////               }
////            }
////         }
////         else
////         {
////            synchronous_lock synchronouslock(mutex());
////
////
////         }
////
////         return iImage;
////
////      }


//   i32 ios::get_foo_image(per_fork * pfork, oswindow oswindow, image_key imagekey, color32_t crBk)
//   {
//
//      i32 iImage = -1;
////
////         SHFILEINFOW shfi16;
////
////         SHFILEINFOW shfi48;
////
////         wstring wstrFilePath;
////
////         imagekey.m_strPath = "foo";
////
////         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
////
////         {
////
////            synchronous_lock synchronouslock(mutex());
////
////            if (m_pimagemap->lookup(imagekey, iImage))
////            {
////
////               return iImage;
////
////            }
////
////         }
////
////         if (imagekey.m_eattribute.has(file_attribute_directory))
////         {
////
////            SHGetFileInfoW(
////               L"foo",
////               FILE_ATTRIBUTE_DIRECTORY,
////               &shfi16,
////               sizeof(shfi16),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_SMALLICON);
////
////            SHGetFileInfoW(
////               L"foo",
////               FILE_ATTRIBUTE_DIRECTORY,
////               &shfi48,
////               sizeof(shfi48),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_LARGEICON);
////
////         }
////         else
////         {
////
////            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_strExtension);
////
////            SHGetFileInfoW(
////               wstrFilePath,
////               FILE_ATTRIBUTE_NORMAL,
////               &shfi16,
////               sizeof(shfi16),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_SMALLICON);
////
////            SHGetFileInfoW(
////               wstrFilePath,
////               FILE_ATTRIBUTE_NORMAL,
////               &shfi48,
////               sizeof(shfi48),
////               SHGFI_USEFILEATTRIBUTES
////               | SHGFI_ICON
////               | SHGFI_LARGEICON);
////
////         }
////         per_fork f(false);
////         if (pfork == nullptr)
////         {
////            f.init();
////            pfork = &f;
////
////         }
////
////         bool b16 = false;
////         bool b48 = false;
////         iImage = add_icon_set(pfork, &shfi16, &shfi48, crBk, b16, b48);
////         if (!b16 && shfi16.hIcon != nullptr)
////         {
////            ::DestroyIcon(shfi16.hIcon);
////         }
////         if (!b48 && shfi48.hIcon != nullptr)
////         {
////            ::DestroyIcon(shfi48.hIcon);
////         }         synchronous_lock synchronouslock(mutex());
//
//      m_pimagemap->set_at(imagekey, iImage);
//
//      return iImage;
//
//   }





   //bool ios::get_icon(
   //   per_fork * pfork,
   //   oswindow oswindow,
   //   IShellFolder * lpsf,
   //   LPITEMIDLIST lpiidlAbsolute,
   //   LPITEMIDLIST lpiidlChild,
   //   const unichar * lpcszExtra,
   //   e_icon eicon,
   //   HICON * phicon16,
   //   HICON * phicon48)
   //{

   //   single_lock synchronouslock(mutex(), true);

   //   if (lpsf == nullptr)
   //      return false;
   //   i32 iType;
   //   switch (eicon)
   //   {
   //   case icon_normal:
   //      iType = 0;
   //      break;
   //   case icon_open:
   //      iType = GIL_OPENICON;
   //      break;
   //   default:
   //      // unexpected icon type
   //      ASSERT(false);
   //      return false;
   //   }


   //   WCHAR szFilePath[_MAX_PATH * 10];
   //   SHGetPathFromIDListW(
   //      lpiidlAbsolute,
   //      szFilePath);
   //   string strFilePath(szFilePath);

   //   //   WCHAR wszFilePath[_MAX_PATH * 10];
   //   SHGetPathFromIDListW(
   //      lpiidlAbsolute,
   //      szFilePath);

   //   char szPath[_MAX_PATH * 10];
   //   string strPath;
   //   //   i32 iImage = 0x80000000;

   //   HICON hicon16 = nullptr;
   //   HICON hicon48 = nullptr;
   //   HRESULT hrIconLocation;
   //   HRESULT hrExtract;
   //   image_key imagekey;


   //   string strPathEx(strFilePath);
   //   string strExtra;

   //   ::str::international::unicode_to_utf8(strExtra, lpcszExtra);

   //   if (strExtra.get_length() > 0)
   //   {
   //      strPathEx += ":" + strExtra;
   //   }



   //   i32 iIcon = 0x80000000;
   //   ::u32 uFlags = 0;

   //   SHFILEINFO shfi16;
   //   SHFILEINFO shfi48;

   //   ::ios::comptr< IExtractIcon > lpiextracticon;

   //   if (SUCCEEDED(lpsf->GetUIObjectOf(
   //      oswindow,
   //      1,
   //      (LPCITEMIDLIST *)&lpiidlChild,
   //      IID_IExtractIcon,
   //      nullptr,
   //      lpiextracticon)))
   //   {
   //      if (SUCCEEDED(hrIconLocation = lpiextracticon->GetIconLocation(
   //         iType,
   //         szPath,
   //         sizeof(szPath),
   //         &iIcon,
   //         &uFlags)))
   //      {
   //         strPath = szPath;
   //         if (strPath == "*")
   //         {
   //            strsize iFind = strFilePath.reverse_find('.');

   //            imagekey.m_iIcon = 0x80000000;
   //            imagekey.m_strExtension = (char*)&strFilePath[iFind];
   //            imagekey.m_strPath = "";
   //         }
   //         else
   //         {
   //            imagekey.m_strPath = (char *)strPath.c_str();
   //            imagekey.m_iIcon = iIcon;
   //            imagekey.m_strExtension = nullptr;
   //         }
   //      }
   //   }
   //   if (pcontext->m_papexcontext->dir().is(::str::international::unicode_to_utf8(szFilePath)))
   //   {
   //      if (imagekey.m_iIcon == 0x80000000)
   //      {
   //         SHGetFileInfo(
   //            "foo",
   //            FILE_ATTRIBUTE_DIRECTORY,
   //            &shfi16,
   //            sizeof(shfi16),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_SMALLICON);
   //         SHGetFileInfo(
   //            "foo",
   //            FILE_ATTRIBUTE_DIRECTORY,
   //            &shfi48,
   //            sizeof(shfi48),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_LARGEICON);
   //      }
   //      else
   //      {
   //         strPath = "foo." + string(imagekey.m_strExtension);
   //         SHGetFileInfo(
   //            strPath,
   //            FILE_ATTRIBUTE_NORMAL,
   //            &shfi16,
   //            sizeof(shfi16),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_SMALLICON);
   //         SHGetFileInfo(
   //            strPath,
   //            FILE_ATTRIBUTE_NORMAL,
   //            &shfi48,
   //            sizeof(shfi48),
   //            SHGFI_USEFILEATTRIBUTES
   //            | SHGFI_ICON
   //            | SHGFI_LARGEICON);
   //      }
   //      *phicon16 = shfi16.hIcon;
   //      *phicon48 = shfi48.hIcon;
   //   }
   //   else
   //   {
   //      try
   //      {
   //         hicon16 = nullptr;
   //         strPath.Truncate(0);
   //         strPath.free_extra();
   //         strPath = imagekey.m_strPath;
   //         iIcon = imagekey.m_iIcon;
   //         bool bExtract = false;
   //         //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.get_length() + 1);
   //         //char * lpsz = (char *) ::GlobalLock(hglobal);
   //         //strcpy(lpsz, strPath);
   //         try
   //         {
   //            if ((hrIconLocation == S_OK && !(uFlags & GIL_NOTFILENAME))
   //               && lpiextracticon.is_null()
   //               && (NOERROR == (hrExtract = lpiextracticon->Extract(
   //                  strPath,
   //                  iIcon,
   //                  &hicon48,
   //                  &hicon16,
   //                  0x00100030)))
   //               )
   //            {
   //               bExtract = true;
   //               *phicon16 = hicon16;
   //               *phicon48 = hicon48;
   //            }
   //         }
   //         catch (...)
   //         {
   //         }
   //         //::GlobalUnlock(hglobal);
   //         //::GlobalFree(hglobal);
   //         if (!bExtract)
   //         {
   //            if (strlen(imagekey.m_strPath) <= 0)
   //            {
   //               SHGetFileInfo(
   //                  (const char *)lpiidlAbsolute,
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi16,
   //                  sizeof(shfi16),
   //                  SHGFI_PIDL
   //                  | SHGFI_ICON
   //                  | SHGFI_SMALLICON);
   //               hicon16 = shfi16.hIcon;
   //               SHGetFileInfo(
   //                  (const char *)lpiidlAbsolute,
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi48,
   //                  sizeof(shfi48),
   //                  SHGFI_PIDL
   //                  | SHGFI_ICON
   //                  | SHGFI_LARGEICON);
   //               hicon16 = shfi16.hIcon;
   //               hicon48 = shfi48.hIcon;
   //            }
   //            else
   //            {
   //               ExtractIconEx(
   //                  imagekey.m_strPath,
   //                  imagekey.m_iIcon,
   //                  &hicon48,
   //                  &hicon16,
   //                  1);
   //            }
   //            if (hicon16 == nullptr)
   //            {
   //               SHGetFileInfo(
   //                  "foo",
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi16,
   //                  sizeof(shfi16),
   //                  SHGFI_USEFILEATTRIBUTES
   //                  | SHGFI_ICON
   //                  | SHGFI_SMALLICON);
   //               hicon16 = shfi16.hIcon;
   //            }
   //            if (hicon48 == nullptr)
   //            {
   //               SHGetFileInfo(
   //                  "foo",
   //                  FILE_ATTRIBUTE_NORMAL,
   //                  &shfi48,
   //                  sizeof(shfi48),
   //                  SHGFI_USEFILEATTRIBUTES
   //                  | SHGFI_ICON
   //                  | SHGFI_LARGEICON);
   //               hicon48 = shfi48.hIcon;
   //            }
   //            *phicon16 = hicon16;
   //            *phicon48 = hicon48;
   //         }
   //      }
   //      catch (...)
   //      {
   //      }
   //   }

   //   return true;

   //}



   //i32 ios::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, color32_t crBk)
   //{

   //   i32 iImage = get_image(pfork, oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra, crBk);

   //   _017ItemIDListFree(pfork, lpiidlChild);

   //   return iImage;

   //}





//      bool ios::get_icon( oswindow oswindow, const char * psz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
//
//         per_fork fork;
//         LPITEMIDLIST lpiidlAbsolute;
//         _017ItemIDListParsePath(oswindow, &lpiidlAbsolute, psz);
//         bool bGet = get_icon(oswindow, lpiidlAbsolute, lpcszExtra, eicon, phicon16, phicon48);
//         _017ItemIDListFree(&fork, lpiidlAbsolute);
//         return bGet;
//
//      }
//
//      bool ios::get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
//
//         wstring wstr;
//
////         ::ios::comptr < IShellFolder > lpsf = _017GetShellFolder(wstr, lpiidlAbsolute);
//         ::ios::comptr < IShellFolder > lpsf = _017GetShellFolder(lpiidlAbsolute);
//
//
//         LPITEMIDLIST lpiidlChild = _017ItemIDListGetLast(pfork, lpiidlAbsolute);
//         bool bGet = get_icon(
//            oswindow,
//            lpsf,
//            lpiidlAbsolute,
//            lpiidlChild,
//            lpcszExtra,
//            eicon,
//            phicon16,
//            phicon48);
//
//         _017ItemIDListFree(pfork, lpiidlChild);
//
//         return bGet;
//      }
//








//   e_folder ios::get_folder_type(::object * pobject, const char * pcsz)
//   {
//
//      return get_folder_type(papp, ::str::international::utf8_to_unicode(pcsz));
//
//   }


//   e_folder ios::get_folder_type(::object * pobject, const unichar * lpcszPath)
//   {
//
//      string strPath;
//
//      ::str::international::unicode_to_utf8(strPath, lpcszPath);
//
//      if (dir::is(strPath))
//      {
//         return folder_file_system;
//      }
//      else if (zip::util().is_unzippable(papp, strPath))
//      {
//         return folder_zip;
//      }
//      else
//      {
//         return folder_none;
//      }
//
//   }

   //int ios::run()
   //{

   //   // These images are the Shell standard extra-large icon size. This is typically 48x48, but the size can be customized by the user.

   //   return 0;

   //   while (this->task_get_run())
   //   {

   //      if (!do_call())
   //      {

   //         sleep(100_ms);

   //      }

   //      try
   //      {

   //         {

   //         restart:

   //            {

   //               synchronous_lock synchronouslock(mutex());

   //               for (auto & folder : m_mapFolder)
   //               {

   //                  if (folder.element2().m_millisStart.elapsed() > 30000)
   //                  {

   //                     m_mapFolder.erase_key(folder.element1());

   //                     goto restart;

   //                  }

   //               }

   //            }

   //         }

   //         //int i = 20;

   //         //while (task_get_run() && i >= 0)
   //         //{

   //         //   sleep(500_ms);

   //         //   i--;

   //         //}


   //      }
   //      catch (...)
   //      {


   //      }


   //   }


   //   return 0;

   //}

   //bool ios::do_call()
   //{

   //   if (m_callCurrent.m_bCall)
   //   {

   //      m_callCurrent.m_iImage = get_image(
   //         m_callCurrent.m_oswindow,
   //         m_callCurrent.m_pimagekey,
   //         m_callCurrent.m_lpcszExtra,
   //         m_callCurrent.m_colorBk);
   //      m_callCurrent.m_bCall = false;
   //      m_eventReady.SetEvent();

   //      return true;

   //   }

   //   return false;

   //}

//   i32 ios::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, const unichar * lpcszExtra, color32_t crBk)
//   {
//
//      i32 iImage = 0x80000000;
//
//      if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
//      {
//
//         ::file::path path = pcontext->m_papexcontext->dir().matter("cloud.ico");
//
////            for (auto iSize : m_iaSize)
////            {
////
////
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////               iImage = add_icon(iSize, hicon, crBk);
////
////            }
//
//         single_lock synchronouslock(mutex(), true);
//
//         m_pimagemap->set_at(imagekey, iImage);
//
//         return iImage;
//
//      }
//      else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
//      {
//
//         ::file::path path = pcontext->m_papexcontext->dir().matter("remote.ico");
//
////            for (auto iSize : m_iaSize)
////            {
////
////
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////               iImage = add_icon(iSize, hicon, crBk);
////
////            }
//
//         single_lock synchronouslock(mutex(), true);
//
//         m_pimagemap->set_at(imagekey, iImage);
//
//         return iImage;
//
//      }
//      else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
//      {
//
//         ::file::path path = pcontext->m_papexcontext->dir().matter("ftp.ico");
//
////            for (auto iSize : m_iaSize)
////            {
////
////
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////               iImage = add_icon(iSize, hicon, crBk);
////
////            }
//
//         single_lock synchronouslock(mutex(), true);
//
//         m_pimagemap->set_at(imagekey, iImage);
//
//         return iImage;
//
//      }
//
//
//
//
//
//      if (::str::ends_ci(imagekey.m_strPath, ".aura"))
//      {
//         string str = pcontext->m_papexcontext->file().as_string(imagekey.m_strPath);
//         if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
//         {
//            str.trim();
//            HICON hicon16 = (HICON) ::LoadImage(nullptr, pcontext->m_papexcontext->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
//            HICON hicon48 = (HICON) ::LoadImage(nullptr, pcontext->m_papexcontext->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
//            synchronous_lock sl1(m_pil48Hover->mutex());
//            synchronous_lock sl2(m_pil48->mutex());
//            iImage = m_pil16->add_icon_os_data(hicon16);
//            m_pil48Hover->add_icon_os_data(hicon48);
//
//            if (crBk == 0)
//            {
//               psystem->imaging().Createcolor_blend_ImageList(
//                  m_pil48,
//                  m_pil48Hover,
//                  rgb(255, 255, 240),
//                  64);
//            }
//            else
//            {
//               *m_pil48 = *m_pil48Hover;
//            }*/
//
//         }
//         return iImage;
//      }
//      // try to find "uifs:// http:// ftp:// like addresses"
//      // then should show icon by extension or if is folder
//      strsize iFind = imagekey.m_strPath.find_ci("://");
//      strsize iFind2 = imagekey.m_strPath.find_ci(":");
//      if (iFind >= 0 || iFind2 >= 2)
//      {
//         string strProtocol = string(imagekey.m_strPath).Left(maximum(iFind, iFind2));
//         i32 i = 0;
//
//         while (i < strProtocol.get_length() && ansi_char_is_alphanumeric(strProtocol[i]))
//         {
//
//            i++;
//
//         }
//
//         if (i > 0 && i == strProtocol.get_length())
//         {
//
//            // heuristically valid protocol
//            return get_image_by_extension(pfork, oswindow, imagekey, crBk);
//
//         }
//
//         if (imagekey.m_eattribute.has(file_attribute_directory))
//         {
//
//            return get_image_by_extension(pfork, oswindow, imagekey, crBk);
//
//         }
//
//      }
//
//      //#ifdef WINDOWS_DESKTOP
//
//      string strExtension;
//
//      if (::str::ends_ci(imagekey.m_strPath, ".sln"))
//      {
//         output_debug_string("test");
//      }
//
//      ::image_pointer pimage48;
//
//      image48 = create_image({48,  48});
//
//      pimage->Fill(0);
//
//      string strPath = imagekey.m_strPath;
//
//      if (ios_get_file_image(image48, strPath))
//      {
//         ::image_pointer pimage16;
//
//         image16 = create_image({16,  16});
//
//         pimage->Fill(0);
//
//         {
//            synchronous_lock sl1(m_pilHover[16]->mutex());
//            synchronous_lock sl2(m_pil[16]->mutex());
//            if (ios_get_file_image(image16, strPath))
//            {
//               iImage = m_pil[16]->add_image(image16, 0, 0);
//               m_pilHover[16]->add_image(image16, 0, 0);
//
//
//            }
//            else
//            {
//
//               pimage->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//               pimage->get_graphics()->StretchBlt(0, 0, 48, 48, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());
//
//               iImage = m_pil[16]->add_image(image16, 0, 0);
//
//               m_pilHover[16]->add_image(image16, 0, 0);
//
//            }
//
//         }
//
//         synchronous_lock sl1(m_pilHover[48]->mutex());
//
//         synchronous_lock sl2(m_pil[48]->mutex());
//
//         iImage = m_pil[48]->add_image(image48, 0, 0);
//
//         m_pilHover[48]->add_image(image48, 0, 0);
//
//         if (crBk == 0)
//         {
//
//            psystem->imaging().Createcolor_blend_ImageList(
//            m_pil[48],
//            m_pilHover[48],
//            rgb(255, 255, 240),
//            64);
//
//         }
//         else
//         {
//
//            *m_pil[48] = *m_pilHover[48];
//
//         }
//
//         return iImage;
//
//      }
//
//      string str(imagekey.m_strPath);
//
//      iImage = -1;
//
//      return iImage;
//
//   }
//
//
//   ios::per_fork::per_fork(bool bInit)
//   {
//
//      if (bInit)
//      {
//
//         init();
//
//      }
//
//   }


//   ios::per_fork::~per_fork()
//   {
//
//   }
//
//
//   void ios::per_fork::init()
//   {
//
////         SHGetImageList(SHIL_SMALL, IID_IImageList, m_pilSmall);
////         SHGetImageList(SHIL_LARGE, IID_IImageList, m_pilLarge);
////         SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);
////         SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pilJumbo);
////         SHGetDesktopFolder(&m_pfolderDesktop);
////         SHGetMalloc(&m_pmalloc);
//
//   }
//
//
//   void ios::shell_run()
//   {
//
//      per_fork fork;
//
//      synchronous_lock synchronouslock(&m_mutexQueue);
//
//      while (task_get_run())
//      {
//
//         if(m_keyptra.is_empty())
//         {
//
//            synchronouslock.unlock();
//
//            sleep(100_ms);
//
//         }
//         else
//         {
//
//            image_key * pkey = m_keyptra.first();
//
//            m_keyptra.erase_at(0);
//
//            synchronouslock.unlock();
//
//            int iImage = get_image(&fork, pkey->m_oswindow, *pkey, nullptr, pkey->m_cr);
//
//            {
//
//               synchronous_lock s(mutex());
//
//               m_pimagemap->set_at(*pkey, iImage);
//
//            }
//
//            delete pkey;
//
//         }
//
//         synchronouslock.lock();
//
//      }
//
//   }


//   i32 ios::get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//   {
//
//      i32 iImage = 0x80000000;
//
//      {
//         
//         if (colorref_get_a_value(crBk) != 255)
//         {
//
//            crBk = 0;
//
//         }
//
//         image_key imagekey;
//
//         imagekey.set_path(strPath);
//
//         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         imagekey.m_eattribute = eattribute;
//
//         imagekey.m_eicon = eicon;
//
//         imagekey.m_iIcon = 0;
//
//         imagekey.m_oswindow = oswindow;
//
//         imagekey.m_cr = crBk;
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
//         image_key * pstore = new image_key(imagekey);
//
//         {
//
//            synchronous_lock synchronouslock(&m_mutexQueue);
//
//            m_keyptra.add(pstore);
//
//         }
//
//         imagekey.set_path("foo");
//
//         iImage = get_foo_image(nullptr, oswindow, imagekey, imagekey.m_cr);
//
//         synchronous_lock synchronouslock(mutex());
//
//         m_pimagemap->set_at(imagekey, iImage);
//
//      }
//
//      return iImage;
//
//   }
//
//
//   i32 ios::get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//   {
//
//      i32 iImage = 0x80000000;
//
//      {
//
//         if (colorref_get_a_value(crBk) != 255)
//         {
//
//            crBk = 0;
//
//         }
//
//         image_key imagekey;
//
//         imagekey.m_strPath = (char *) (const char *) "foo";
//
//         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         imagekey.m_strExtension = (char *)strExtension.c_str();
//
//         imagekey.m_eattribute = eattribute;
//
//         imagekey.m_eicon = eicon;
//
//         imagekey.m_iIcon = 0;
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
//         per_fork f;
//
//         iImage = get_image(&f, oswindow, imagekey, nullptr, crBk);
//
//         synchronous_lock synchronouslock(mutex());
//
//         m_pimagemap->set_at(imagekey, iImage);
//
//      }
//
//      return iImage;
//
//   }
//
//
//   int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
//   {
//
//      if (crBk == 0)
//      {
//
//         return m_pilHover[iSize]->predicate_add_image([&](auto pimage)
//         { psystem->imaging().Createcolor_blend_image(pimage, rgb(255, 255, 240), 64); }
//         , m_pil[iSize], iImage);
//
//      }
//      else
//      {
//
//         iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);
//
//         {
//
//            ::image_pointer pimage;
//            pimage = create_image({iSize,  iSize});
//            pimage->Fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
//            pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            m_pilHover[iSize]->draw(pimage->get_graphics(), iImage, ::point(), 0);
//            m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//            m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
//            m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//         }
//
//         {
//
//            ::image_pointer & d = *m_pilHover[iSize]->m_pimage;
//            size s = m_pil[iSize]->m_pimage->get_size();
//            ::image_pointer pimage;
//            pimage = create_image(s);
//            pimage->Fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
//            pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//            pimage->get_graphics()->draw(::point(), d.size(), d.get_graphics());
//            pimage->get_graphics()->fill_solid_rect_dim(0, 0, d.size().cx, d.size().cy, argb(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
//            m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//            m_pil[iSize]->m_pimage->g()->draw(::point(), d->size(), pimage->get_graphics());
//            m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//         }
//
//         return iImage;
//
//      }
//
//   }

   i32 shell::impl_get_file_image(const image_key & imagekey)
   {

      i32 iImage = 0x80000000;

      image_key * pstore = new image_key(imagekey);

      {

         synchronous_lock synchronouslock(&m_mutexQueue);

         m_keyptra.add(pstore);

      }
      
      image_key i2(imagekey);

      i2.set_path("foo");

      iImage = get_foo_image(i2, i2.m_cr);

      synchronous_lock synchronouslock(mutex());

      m_imagemap.set_at(imagekey, iImage);

      return iImage;

   }


   void shell::do_initialize()
   {

      on_update_sizes_interest();

      fork([&]()
      {

         synchronous_lock synchronouslock(&m_mutexQueue);

         while (task_get_run())
         {

            if(m_keyptra.is_empty())
            {

               synchronouslock.unlock();

               sleep(100_ms);

            }
            else
            {

               image_key * pkey = m_keyptra.first();

               m_keyptra.erase_at(0);

               synchronouslock.unlock();

               int iImage = get_image(*pkey, nullptr, pkey->m_cr);

               {

                  synchronous_lock s(mutex());

                  m_imagemap.set_at(*pkey, iImage);

               }

               delete pkey;

            }

            synchronouslock.lock();

         }

         return 0;

      });


   }

   shell::e_folder shell::get_folder_type(::object * pobject, const char * lpcszPath)
   {

      string strPath(lpcszPath);

      if (dir::is(strPath))
      {
         return folder_file_system;
      }
      else
      {
         
         ::zip_context context(this);
      
         if (context.is_unzippable(strPath))
         {
            
            return folder_zip;
      
         }
         else
         {

            return folder_none;
      
         }

      }

   }


} // namespace shell



