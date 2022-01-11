#include "framework.h"
#include "shell.h"
#include "aura/os/windows/_windows.h"


namespace user
{


   namespace shell
   {


      windows::windows()
      {

         //m_iMaxThreadCount = maximum(4, ::get_processor_count());

         m_iMaxThreadCount = 1;

         defer_create_mutex();

         m_iThread = 0;

         defer_co_initialize_ex(false);

         SHGetDesktopFolder(&m_pfolderDesktop);

         SHGetMalloc(&m_pmalloc);

         SHGetImageList(SHIL_SMALL, IID_IImageList, (void **) &m_pilSmall);

         SHGetImageList(SHIL_LARGE, IID_IImageList, (void **)& m_pilLarge);

         SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, (void **)& m_pilExtraLarge);

         SHGetImageList(SHIL_JUMBO, IID_IImageList, (void **)& m_pilJumbo);



      }


      windows::~windows()
      {

      }




//      i32 windows::thread::get_image_by_file_extension(oswindow oswindow, image_key & imagekey, color32_t crBk)
//      {
//
//#ifdef WINDOWS_DESKTOP
//
//         return get_foo_image(oswindow, imagekey, crBk);
//
//#else
//
//         return 0x80000000;
//
//#endif // WINDOWS_DESKTOP
//
//      }


      // returned image should be "Definitive" icon/pimage->
      // maybe fallback but not temporary
      i32 windows::get_file_image(oswindow oswindow, image_key imagekey, const itemidlist & pidlAbsolute, const itemidlist & pidlChild, const unichar * pcszExtra, color32_t crBk)

      {

         comptr < IShellFolder> psf;


         psf = pidlAbsolute.get_shell_folder();


         if (psf.is_null())

         {

            return get_image_by_file_extension(oswindow, imagekey);

         }

         int iImage = 0x80000000;

         i32 iType;

         switch (imagekey.m_eicon)
         {
         case icon_normal:
            iType = 0;
            break;
         case icon_open:
            iType = GIL_OPENICON;
            break;
         default:
            // unexpected icon type
            ASSERT(false);
            return 0x80000000;
         }

         string strFileParam(imagekey.m_strPath);

         string strResource;

         WCHAR wszPath[_MAX_PATH * 6];

         WCHAR szPath[_MAX_PATH * 6];

         HICON hicon16 = nullptr;

         HICON hicon48 = nullptr;

         HRESULT hrIconLocation = E_FAIL;

         HRESULT hrExtract = E_FAIL;

         HRESULT hrExtractIconUI = E_FAIL;

         HRESULT hrGetOverlayInfo = E_FAIL;

         HRESULT hrGetLocation = E_FAIL;

         string strExtra;

         string strPathEx;

         strPathEx = strFileParam;

         ::str::international::unicode_to_utf8(strExtra, pcszExtra);


         if (strExtra.get_length() > 0)
         {

            strPathEx += ":" + strExtra;

         }

         comptr < IExtractIconW > piextracticon;


         comptr < IShellIconOverlayIdentifier > pioverlay;


         comptr < IExtractImage > piextractimage;


         ::u32 uExtractIconLocationFlags = 0;

         string strIconLocation;

         //if (strFileParam.compare_ci(::dir::bookmark()) == 0)
         //{

         //   strIconLocation = pcontext->m_papexcontext->dir().matter("aura.ico");

         //   output_debug_string("aura.ico");

         //   return -1;

         //   //imagekey.set_path(strIconLocation);

         //   //imagekey.m_iIcon = 0;

         //   //imagekey.m_strExtension = "";

         //}
         if (SUCCEEDED(hrExtractIconUI = psf->GetUIObjectOf(

                                         oswindow,
                                         1,
                                         (LPCITEMIDLIST *)&pidlChild.m_pidl,
                                         IID_IExtractIconW,
                                         nullptr,
            (void **)& piextracticon)))

         {

            int iIcon = 0;

            if (SUCCEEDED(hrIconLocation = piextracticon->GetIconLocation(

                                           iType,
                                           wszPath,
                                           sizeof(wszPath) / sizeof(wszPath[0]),
                                           &iIcon,
                                           &uiExtractIconLocationFlags)))
            {

               if (wcscmp(wszPath, L"*") == 0)
               {

                  imagekey.m_iIcon = 0x80000000;

                  imagekey.set_extension(strFileParam);

                  imagekey.m_strPath = "";

               }
               else
               {

                  strIconLocation = expand_env(wszPath);

                  imagekey.set_path(strIconLocation);

                  imagekey.m_iIcon = iIcon;

                  imagekey.m_strExtension = "";

               }

            }

         }

         if(FAILED(hrIconLocation))
         {

            if (SUCCEEDED(psf->GetUIObjectOf(

                          oswindow,
                          1,
                          (LPCITEMIDLIST *)&pidlChild.m_pidl,
                          IID_IShellIconOverlayIdentifier,
                          nullptr,
               (void **)& pioverlay)))

            {

               int iIndex = 0;

               ::u32 dwFlags = 0;

               if (SUCCEEDED(hrGetOverlayInfo = pioverlay->GetOverlayInfo(

                                                wszPath,
                                                sizeof(wszPath),
                                                &iIndex,
                                                &dwFlags)))
               {

                  if (wcscmp(wszPath, L"*") == 0)
                  {

                     imagekey.m_iIcon = 0x80000000;

                     imagekey.set_extension(strFileParam);

                     imagekey.m_strPath = "";

                  }
                  else
                  {

                     imagekey.set_path(expand_env(szPath));

                     imagekey.m_iIcon = iIndex;

                     imagekey.m_strExtension = "";

                  }

               }

            }
            else
            {

               if (SUCCEEDED(psf->GetUIObjectOf(
                             oswindow,
                             1,
                             (LPCITEMIDLIST *)&pidlChild.m_pidl,
                             IID_IExtractImage,
                             nullptr,
                  (void **)& piextractimage)))

               {

                  size s;

                  s.cx = 48;

                  s.cy = 48;

                  ::u32 dwDepth = 32;

                  ::u32 dwFlags = 0;

                  if (SUCCEEDED(hrGetLocation = piextractimage->GetLocation(

                                                wszPath,
                                                sizeof(wszPath),
                                                nullptr,
                                                &s,
                                                dwDepth,
                                                &dwFlags)))
                  {


                     if (wcscmp(wszPath, L"*") == 0)
                     {

                        imagekey.m_iIcon = 0x80000000;

                        imagekey.set_path(strFileParam);

                        imagekey.m_strPath = "";

                     }
                     else
                     {

                        imagekey.set_path(expand_env(wszPath));

                        imagekey.m_iIcon = 0;

                        imagekey.m_strExtension = "";

                     }

                  }

               }
               else
               {

                  imagekey.set_path(strFileParam);

                  imagekey.m_iIcon = 0;

               }

            }

         }

         ::file::path pathTarget;

         if (((FAILED(hrIconLocation) && FAILED(hrGetLocation))
               || imagekey.m_iIcon == 0x80000000
               || !pcontext->m_papexcontext->file().exists(strIconLocation))
               && ::str::ends_ci(strFileParam, ".lnk"))
         {

            pcontext->m_papexcontext->file().resolve_link(pathTarget, strFileParam);

            if (!pcontext->m_papexcontext->file().exists(pathTarget) && !pcontext->m_papexcontext->dir().is(pathTarget))
            {

               if (pathTarget.ends_ci(".exe"))
               {

                  imagekey.set_path(pathTarget);

               }
               else
               {

                  imagekey.set_path("");

               }

               iImage = get_image_by_file_extension(oswindow, imagekey);

               return iImage;

            }

            if (FAILED(hrIconLocation) && FAILED(hrGetLocation))
            {

               imagekey.set_path(pathTarget);

               iImage = get_file_image(oswindow, imagekey, pcszExtra, crBk);


               return iImage;

            }

         }
         else
         {

            pathTarget = strFileParam;

         }

         if (imagekey.m_iIcon == 0x80000000)
         {

            if (imagekey.m_strShellThemePrefix.has_char())
            {

               string strExtension = file_extension_dup(pathTarget);

               image_key imagekeyTheme;

               string strFooPath = imagekey.m_strShellThemePrefix + "foo." + strExtension;

               imagekeyTheme.set_path(strFooPath);

               imagekeyTheme.m_iIcon = 0;

               if (contains_image(imagekeyTheme, iImage))
               {

                  return iImage;

               }

               string strIcon;

               strIcon =          auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->config() / "shell/app_theme" / imagekey.m_strShellThemePrefix + strExtension + ".ico";

               if (pcontext->m_papexcontext->file().exists(strIcon))
               {

                  if (reserve_image(imagekeyTheme, iImage))
                  {

                     add_icon_path(strIcon, crBk, iImage);

                  }

                  return iImage;

               }

            }

            if (wcscmp(wszPath, L"*") == 0)
            {

               return get_image_by_file_extension(oswindow, imagekey);

            }

         }

         if (uiExtractIconLocationFlags & GIL_NOTFILENAME)
         {

            if (reserve_image(imagekey, iImage))
            {

               HICON hicon = nullptr;

               HRESULT hrExtract = E_FAIL;

               synchronous_lock synchronouslock(mutex());

               auto iaSize = m_iaSize;

               synchronouslock.unlock();

               for (auto iSize : iaSize)
               {

                  if (iSize <= 16)
                  {

                     if (SUCCEEDED(hrExtract = piextracticon->Extract(

                                               wszPath,
                                               imagekey.m_iIcon,
                                               nullptr,
                                               &hicon,
                                               iSize << 16)))
                     {

                        add_icon(iSize, hicon, crBk, iImage);

                        ::DestroyIcon(hicon);

                     }

                  }
                  else
                  {

                     if (SUCCEEDED(hrExtract = piextracticon->Extract(

                                               wszPath,
                                               imagekey.m_iIcon,
                                               &hicon,
                                               nullptr,
                                               iSize)))
                     {

                        add_icon(iSize, hicon, crBk, iImage);

                        ::DestroyIcon(hicon);

                     }

                  }

               }

            }

            return iImage;

         }
         else if(strIconLocation.has_char())
         {

            if (strIconLocation.ends_ci(".ico"))
            {

               set_image_ico(strIconLocation, iImage, crBk);

            }
            else
            {

               set_image_resource(strIconLocation, iImage, imagekey, crBk);


            }

            return iImage;

         }

         //if (imagekey.m_iIcon >= 0 && strFileParam.get_length() > 0)
         //{

         //   SHFILEINFOW shfi16;

         //   SHFILEINFOW shfi48;

         //   wstring wstrPath(strFileParam);

         //   SHGetFileInfoW(
         //   wstrPath,
         //   FILE_ATTRIBUTE_NORMAL,
         //   &shfi16,
         //   sizeof(shfi16),
         //   SHGFI_ICON
         //   | SHGFI_SMALLICON);

         //   SHGetFileInfoW(
         //   wstrPath,
         //   FILE_ATTRIBUTE_NORMAL,
         //   &shfi48,
         //   sizeof(shfi48),
         //   SHGFI_ICON
         //   | SHGFI_LARGEICON);

         //   bool b16 = false;

         //   bool b48 = false;

         //   if (shfi16.hIcon != nullptr || shfi48.hIcon != nullptr)
         //   {

         //      if (reserve_image(imagekey, iImage))
         //      {

         //         add_icon_set(&shfi16, &shfi48, crBk, b16, b48, iImage);

         //         if (!b16 && shfi16.hIcon != nullptr)
         //         {

         //            ::DestroyIcon(shfi16.hIcon);

         //         }

         //         if (!b48 && shfi48.hIcon != nullptr)
         //         {

         //            ::DestroyIcon(shfi48.hIcon);

         //         }


         //      }

         //   }

         //}

         imagekey.set_extension(pathTarget);

         imagekey.m_strPath.Empty();

         imagekey.m_iIcon = 0;

         return get_image_by_file_extension(oswindow, imagekey);

      }


      i32 windows::get_image_by_file_extension(oswindow oswindow, image_key & imagekey)
      {

         i32 iImage;

         if (reserve_image(imagekey, iImage))
         {

            SHFILEINFOW shfi16 = {};

            SHFILEINFOW shfi48 = {};

            wstring wstrFilePath;

            if (imagekey.m_eattribute.has(file_attribute_directory))
            {

               SHGetFileInfoW(
               L"foo",
               FILE_ATTRIBUTE_DIRECTORY,
               &shfi16,
               sizeof(shfi16),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_SMALLICON);

               SHGetFileInfoW(
               L"foo",
               FILE_ATTRIBUTE_DIRECTORY,
               &shfi48,
               sizeof(shfi48),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_LARGEICON);

            }
            else
            {

               wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_strExtension);

               SHGetFileInfoW(
               wstrFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi16,
               sizeof(shfi16),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_SMALLICON);

               SHGetFileInfoW(
               wstrFilePath,
               FILE_ATTRIBUTE_NORMAL,
               &shfi48,
               sizeof(shfi48),
               SHGFI_USEFILEATTRIBUTES
               | SHGFI_ICON
               | SHGFI_LARGEICON);

            }

            bool b16 = false;

            bool b48 = false;

            add_icon_set(&shfi16, &shfi48, imagekey.m_cr, b16, b48, iImage);

            if (shfi16.hIcon != nullptr)
            {

               ::DestroyIcon(shfi16.hIcon);

            }

            if (shfi48.hIcon != nullptr)
            {

               ::DestroyIcon(shfi48.hIcon);

            }

         }

         return iImage;

      }


      //index windows::GetCSIDL(LPITEMIDLIST piidl)

      //{
      //   LPITEMIDLIST ppidl;

      //   i32 csidla[] =
      //   {
      //      CSIDL_DESKTOP,
      //      CSIDL_DRIVES,
      //      CSIDL_PERSONAL,
      //      CSIDL_NETHOOD,
      //      CSIDL_NETWORK,
      //      CSIDL_BITBUCKET,
      //      -1,
      //   };

      //   i32 * pcsidl = csidla;

      //   while (*pcsidl != -1)
      //   {
      //      if (SUCCEEDED(SHGetSpecialFolderLocation(
      //                    nullptr,
      //                    *pcsidl,
      //                    &ppidl)))
      //      {
      //         if (_017ItemIDListIsEqual(ppidl, piidl))

      //         {
      //            m_pmalloc->Free(ppidl);
      //            break;
      //         }
      //         m_pmalloc->Free(ppidl);
      //      }
      //      pcsidl++;
      //   }

      //   return *pcsidl;


      //}


      //index windows::GetCSIDLSort(index iCsidl)
      //{
      //   switch (iCsidl)
      //   {
      //   case CSIDL_DESKTOP:
      //      return 100;
      //   case CSIDL_PERSONAL:
      //      return 200;
      //   case CSIDL_DRIVES:
      //      return 300;
      //   case CSIDL_NETHOOD:
      //      return 1000;
      //   default:
      //      return 2000 + iCsidl;
      //   }

      //}


      //void windows::GetAscendants(LPITEMIDLIST piidl, array < LPITEMIDLIST, LPITEMIDLIST > & lpiidla)

      //{

      //   if (piidl == nullptr)

      //      return;

      //   for (;;)
      //   {
      //      piidl = _017ItemIDListGetFolderParent(lpiidl);

      //      if (piidl == nullptr)

      //         break;
      //      piidla.add(lpiidl);

      //   }

      //}


      //void windows::Free(array < LPITEMIDLIST, LPITEMIDLIST > & piidla)

      //{

      //   for (i32 i = 0; i < piidla.get_size(); i++)

      //   {

      //      m_pmalloc->Free(piidla[i]);


      //   }

      //   piidla.erase_all();


      //}


      e_folder windows::get_folder_type(::object * pobject, const ::string & pcsz)

      {

         return get_folder_type(pobject, ::str::international::utf8_to_unicode(pcsz));


      }


      e_folder windows::get_folder_type(::object * pobject, const unichar * pcszPath)

      {

         string strPath;

         ::str::international::unicode_to_utf8(strPath, pcszPath);


         if (         auto psystem = m_psystem;

         auto pacmedir = psystem->m_pacmedir;

pacmedir->is(strPath))
         {

            return folder_file_system;

         }
         else if (zip_context(this).is_unzippable(strPath))
         {

            return folder_zip;

         }
         else
         {

            return folder_none;

         }

      }


      i32 windows::impl_get_file_image(oswindow oswindow, const image_key & key)
      {

         return get_file_image(oswindow, key, nullptr, key.m_cr);

      }


      i32 windows::get_file_image(oswindow oswindow, image_key imagekey, const unichar * pcszExtra, color32_t crBk)

      {

         i32 iImage = 0x80000000;

         if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
         {

            if (reserve_image(imagekey, iImage))
            {

               ::file::path path = pcontext->m_papexcontext->dir().matter("cloud.ico");

               add_icon_path(path, crBk, iImage);

            }

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
         {

            if (reserve_image(imagekey, iImage))
            {

               ::file::path path = pcontext->m_papexcontext->dir().matter("remote.ico");

               add_icon_path(path, crBk, iImage);

            }

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
         {

            if (reserve_image(imagekey, iImage))
            {

               ::file::path path = pcontext->m_papexcontext->dir().matter("ftp.ico");

               add_icon_path(path, crBk, iImage);

            }

            return iImage;

         }

         if (::str::ends_ci(imagekey.m_strPath, ".aura"))
         {

            string str = pcontext->m_papexcontext->file().as_string(imagekey.m_strPath);

            if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
            {

               str.trim();


            }

            return iImage;

         }

         // Check for URL addresses like uifs://, http://, or ftp://
         // Except A: B: C: (Windows drive letters)
         // And then should find icon by extension if
         // it is a file or as folder otherwise.

         strsize iFind = imagekey.m_strPath.find_ci("://");

         strsize iFind2 = imagekey.m_strPath.find_ci(":");

         if (iFind >= 0 || iFind2 >= 2)
         {

            string strProtocol = imagekey.m_strPath.Left(maximum(iFind, iFind2));

            i32 i = 0;

            while (i < strProtocol.get_length() && ansi_char_is_alphanumeric(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.get_length())
            {

               // heuristically valid protocol
               return get_image_by_file_extension(oswindow, imagekey);

            }

            if (imagekey.m_eattribute.has(file_attribute_directory))
            {

               return get_image_by_file_extension(oswindow, imagekey);

            }

         }

         string strExtension;

         if (::str::ends_ci(imagekey.m_strPath, ".sln"))
         {

            output_debug_string("test");

         }

         string str(imagekey.m_strPath);

         if (str == "foo")
         {

            return get_image_by_file_extension(oswindow, imagekey);

         }

         if (::str::begins_eat(str, "foo."))
         {

            return get_image_by_file_extension(oswindow, imagekey);

         }

         ::file::path path = imagekey.m_strPath;

         ::file::path pathFolder = path.folder();

         itemidlist idlist;

         bool bParseError = false;

         try
         {

            idlist.parse(imagekey.m_strPath);

         }
         catch (...)
         {

            bParseError = true;

         }

         if (bParseError)
         {

            return get_image_by_file_extension(oswindow, imagekey);

         }


         itemidlist idlistAbsolute;

         idlistAbsolute = idlist - 1;

         itemidlist idlistChild;

         idlistChild = idlist.last();

         iImage = get_file_image(oswindow, imagekey, idlistAbsolute, idlistChild, pcszExtra, crBk);


         return iImage;

      }


      //i32 _017ItemIDListGetLen(LPITEMIDLIST piidl)

      //{
      //   if (piidl == nullptr)

      //      return 0;
      //   LPSHITEMID  pshiid = (LPSHITEMID)lpiidl;

      //   LPSHITEMID  pshiidLast = nullptr;

      //   USHORT cb;
      //   i32 iLen = 0;
      //   while (true)
      //   {
      //      cb = pshiid->cb;

      //      iLen += cb;
      //      if (cb == 0)
      //         break;
      //      pshiidLast = lpshiid;

      //      pshiid = (LPSHITEMID)(((byte *)lpshiid) + cb);


      //   }

      //   return iLen;

      //}


      void windows::initialize(::object * pobject)
      {

         if (m_bInitialized)
         {

            return ::success;

         }

         auto estatus = shell::initialize(pobject);

         if (!estatus)
         {

            return estatus;

         }

         return estatus;

      }





      int windows::add_icon_set(SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, color32_t crBk, bool & bUsed16, bool & bUsed48, int iImage)
      {

         synchronous_lock synchronouslock(mutex());

         auto iaSize = m_iaSize;

         synchronouslock.unlock();

         for (auto iSize : iaSize)
         {

            iImage = add_icon_info(iSize, pinfo16, pinfo48, crBk, bUsed16, bUsed48, iImage);

         }

         return iImage;

      }


      int windows::add_icon_path(::file::path path, color32_t crBk, int iImage)
      {

         synchronous_lock synchronouslock(mutex());

         auto iaSize = m_iaSize;

         synchronouslock.unlock();

         path = pcontext->m_papexcontext->defer_process_path(path);

         for (auto iSize : m_iaSize)
         {

            HICON hicon = (HICON)LoadImageW(nullptr, wstring(path), IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

            if (hicon == nullptr)
            {

               ::u32 dwLastError = ::GetLastError();

               output_debug_string("LastError = " + __string(dwLastError));

            }

            iImage = add_icon(iSize, hicon, crBk, iImage);

            ::DestroyIcon(hicon);

         }

         return iImage;

      }


      int windows::add_icon(int iSize, HICON hicon, color32_t crBk, int iImage)
      {

         synchronous_lock synchronouslock(m_pil[iSize]->mutex());

         synchronous_lock slHover(m_pilHover[iSize]->mutex());

         iImage = m_pil[iSize]->add_icon_os_data(hicon, iImage);

         iImage = add_hover_image(iSize, iImage, crBk);

         return iImage;

      }


      int windows::add_icon_info(int iSize, SHFILEINFOW * pinfo16, SHFILEINFOW * pinfo48, color32_t crBk, bool & bUsed16, bool & bUsed48, int iImage)
      {

         bool bUsed = false;

         SHFILEINFOW * pinfo;

         if (iSize <= 16)
         {

            pinfo = pinfo16 == nullptr ? pinfo48 : pinfo16;

            iImage = add_system_icon(iSize, m_pilSmall, pinfo, crBk, bUsed, iImage);

         }
         else if (iSize <= 32)
         {

            pinfo = pinfo48 == nullptr ? pinfo16 : pinfo48;

            iImage = add_system_icon(iSize, m_pilLarge, pinfo, crBk, bUsed, iImage);

         }
         else if (iSize <= 48)
         {

            pinfo = pinfo48 == nullptr ? pinfo16 : pinfo48;

            iImage = add_system_icon(iSize, m_pilExtraLarge, pinfo, crBk, bUsed, iImage);

         }
         else
         {

            pinfo = pinfo48 == nullptr ? pinfo16 : pinfo48;

            iImage = add_system_icon(iSize, m_pilJumbo, pinfo, crBk, bUsed, iImage);

         }

         if (bUsed)
         {

            if (pinfo16 == pinfo)
            {

               bUsed16 = true;

            }
            else
            {

               bUsed48 = true;

            }

         }

         return iImage;

      }


      int windows::add_system_icon(int iSize, IImageList * pil, SHFILEINFOW * pinfo, color32_t crBk, bool & bUsedImageList, int iImage)
      {

         if (pil != nullptr)
         {

            HICON hicon = nullptr;

            HRESULT hr = pil->GetIcon(pinfo->iIcon, ILD_TRANSPARENT, &hicon);

            if (hicon != nullptr)
            {

               iImage = add_icon(iSize, hicon, crBk, iImage);

               ::DestroyIcon(hicon);

            }
            else if (pinfo->hIcon == nullptr)
            {

            }
            else
            {

               iImage = add_icon(iSize, pinfo->hIcon, crBk, iImage);

               bUsedImageList = true;

            }

         }
         else if (pinfo->hIcon == nullptr)
         {

         }
         else
         {

            iImage = add_icon(iSize, pinfo->hIcon, crBk, iImage);

            bUsedImageList = true;

         }

         return iImage;

      }




      int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
      {

         synchronous_lock synchronouslock(m_pilHover[iSize]->mutex());

         if (crBk == 0)
         {

            return m_pilHover[iSize]->predicate_add_image([&](auto pimage)
            {

               psystem->imaging().color_blend(pimage, rgb(255, 255, 240), 64);

            }
            , m_pil[iSize], iImage, iImage);

         }
         else
         {

            iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);

            {

               ::image_pointer pimage(this);
               pimage->create({ iSize, iSize });
               pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
               pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

               m_pilHover[iSize]->draw(pimage->get_graphics(), iImage, nullptr, 0);
               m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
               m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
               m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            }

            {
               ::image_pointer d = m_pilHover[iSize]->m_pimage;
               size s = m_pil[iSize]->m_pimage->get_size();
               ::image_pointer pimage(this);
               pimage->create(d->size());
               pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
               pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
               pimage->get_graphics()->draw(nullptr, d->size(), d->get_graphics());
               pimage->get_graphics()->fill_solid_rect_dim(0, 0, d->size().cx, d->size().cy, argb(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
               m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
               m_pil[iSize]->m_pimage->g()->draw(d->rectangle(), pimage->get_graphics());
               m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

            }

            return iImage;

         }


      }


      void windows::set_image_ico(string strIconLocation, i32 & iImage, color32_t crBk)
      {

         ASSERT(strIconLocation.ends_ci(".ico"));

         image_key imagekeyIco;

         imagekeyIco.set_path(strIconLocation, false);

         imagekeyIco.m_iIcon = 0;

         if (reserve_image(imagekeyIco, iImage))
         {

            add_icon_path(strIconLocation, crBk, iImage);

         }

      }


      void windows::set_image_resource(string strIconLocation, i32 & iImage, const image_key & imagekey, color32_t crBk)
      {

         ASSERT(!strIconLocation.ends_ci(".ico"));

         image_key imagekeyIco;

         imagekeyIco.set_path(strIconLocation, false);

         imagekeyIco.m_iIcon = imagekey.m_iIcon;

         if (reserve_image(imagekeyIco, iImage))
         {

            synchronous_lock synchronouslock(mutex());

            auto iaSize = m_iaSize;

            synchronouslock.unlock();

            for (auto iSize : iaSize)
            {

               int iSizeOut = iSize;

               HICON hicon = (HICON)ExtractResourceIcon(strIconLocation, iSizeOut, iSizeOut, imagekey.m_iIcon);

               if (hicon == nullptr && imagekey.m_iIcon == 0)
               {

                  hicon = (HICON)ExtractResourceIcon(strIconLocation, iSizeOut, iSizeOut, 0x80000000);

               }

               add_icon(iSize, hicon, crBk, iImage);

               ::DestroyIcon(hicon);

            }

         }

      }


   } // namespace shell


} // namespace user



