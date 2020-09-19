#include "framework.h"
#include "core/user/user/_user.h"
#include "shell_linux.h"
#include "aura/node/linux/_linux.h"





const char * linux_g_direct_get_file_icon_path(const char * pszPath, int iSize);

string linux_get_file_icon_path(string strPath, int iSize)
{

   return ::str::from_strdup(linux_g_direct_get_file_icon_path(strPath, iSize));

}

const char * linux_g_direct_get_file_content_type(const char * pszFile);

string core_linux_get_file_content_type(string strPath)
{

   return ::str::from_strdup(linux_g_direct_get_file_content_type(strPath));

}





namespace linux
{


//   namespace shell
//   {


      shell::shell()
      {

         set_get_file_content_type_function(&core_linux_get_file_content_type);

         defer_create_mutex();
         //begin();

         //SHGetImageList(SHIL_SMALL, IID_IImageList, m_pilSmall);
         //SHGetImageList(SHIL_LARGE, IID_IImageList, m_pilLarge);
         //SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pilExtraLarge);
         //SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pilJumbo);
         /// SHGetMalloc(&m_pmalloc);

//         for (index i = 0; i < get_processor_count() * 2; i++)
//         {
//
//            m_threadaGetImage.add(fork([&]()
//            {
//
//               ::multithreading::set_priority(::priority_highest);
//
//               shell_run();
//
//            }));
//
//         }

      }


      shell::~shell()
      {

      }

//
//      void linux::initialize()
//      {
//
//
//      }

//      void linux::defer_start()
//      {
//
//
//      }

//      i32 linux::get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, COLORREF crBk)
//      {
//
//         return 0x80000000;
//
//      }




//      i32 linux::get_file_extension_image(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
//      {
//
//         i32 iImage;
//
//         wstring wstrFilePath;
//
////         imagekey.m_strPath = "foo";
//
//         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         {
//
//            sync_lock sl(mutex());
//
//            if (m_imagemap.lookup(imagekey, iImage))
//            {
//
//               return iImage;
//
//            }
//
//         }
//
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
////            wstrFilePath = wstring(L"foo.") + wstring(imagekey.m_pszExtension);
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
//         per_fork f(false);
//         if (pfork == nullptr)
//         {
//            f.init();
//            pfork = &f;
//
//         }
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
////         }         sync_lock sl(mutex());
////
////         m_imagemap.set_at(imagekey, iImage);
////
//         return iImage;
//
//      }





      //bool linux::get_icon(
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

      //   single_lock sl(mutex(), true);

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
      //      ASSERT(FALSE);
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

      //   CHAR szPath[_MAX_PATH * 10];
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
      //   UINT uiFlags = 0;

      //   SHFILEINFO shfi16;
      //   SHFILEINFO shfi48;

      //   ::linux::comptr< IExtractIcon > lpiextracticon;

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
      //         &uiFlags)))
      //      {
      //         strPath = szPath;
      //         if (strPath == "*")
      //         {
      //            strsize iFind = strFilePath.reverse_find('.');

      //            imagekey.m_iIcon = 0x80000000;
      //            imagekey.m_pszExtension = (char*)&strFilePath[iFind];
      //            imagekey.m_strPath = "";
      //         }
      //         else
      //         {
      //            imagekey.m_strPath = (char *)strPath.c_str();
      //            imagekey.m_iIcon = iIcon;
      //            imagekey.m_pszExtension = nullptr;
      //         }
      //      }
      //   }
      //   if (Context.dir().is(::str::international::unicode_to_utf8(szFilePath)))
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
      //         strPath = "foo." + string(imagekey.m_pszExtension);
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
      //         //LPTSTR lpsz = (LPTSTR) ::GlobalLock(hglobal);
      //         //strcpy(lpsz, strPath);
      //         try
      //         {
      //            if ((hrIconLocation == S_OK && !(uiFlags & GIL_NOTFILENAME))
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



      //i32 linux::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, COLORREF crBk)
      //{

      //   i32 iImage = get_image(pfork, oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra, crBk);

      //   _017ItemIDListFree(pfork, lpiidlChild);

      //   return iImage;

      //}





//      bool linux::get_icon( oswindow oswindow, const char * psz, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock sl(mutex(), true);
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
//      bool linux::get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock sl(mutex(), true);
//
//         wstring wstr;
//
////         ::linux::comptr < IShellFolder > lpsf = _017GetShellFolder(wstr, lpiidlAbsolute);
//         ::linux::comptr < IShellFolder > lpsf = _017GetShellFolder(lpiidlAbsolute);
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


      shell::e_folder shell::get_folder_type(::object * pobject, const char * lpcsz)
      {

         return get_folder_type(pobject, ::str::international::utf8_to_unicode(lpcsz));

      }


      shell::e_folder shell::get_folder_type(::object * pobject, const widechar * lpcszPath)
      {

         string strPath;

         ::str::international::unicode_to_utf8(strPath, lpcszPath);

         if (dir::is(strPath))
         {

            return folder_file_system;

         }
         else
         {

            return folder_none;

         }

      }


      void shell::on_update_sizes_interest()
      {

         sync_lock sl(mutex());

         m_iaSize.remove_all();

         m_iaSize.add(16);

         m_iaSize.add(48);

         ::user::shell::shell::on_update_sizes_interest();

      }


      i32 shell::impl_get_file_image(const image_key & imagekeyParam)
      {

         image_key imagekey(imagekeyParam);

         i32 iImage = 0x80000000;

         if (::str::begins_ci(imagekey.m_strPath, "uifs:"))
         {

            ::file::path path = Context.dir().matter("cloud.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock sl(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "fs:"))
         {

            ::file::path path = Context.dir().matter("remote.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock sl(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (::str::begins_ci(imagekey.m_strPath, "ftp:"))
         {

            ::file::path path = Context.dir().matter("ftp.ico");

            for (auto iSize : m_iaSize)
            {


               //HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock sl(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }





         if (::str::ends_ci(imagekey.m_strPath, ".aura"))
         {
            string str = Context.file().as_string(imagekey.m_strPath);
            if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
            {
               str.trim();
               /*HICON hicon16 = (HICON) ::LoadImage(nullptr, Context.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
               HICON hicon48 = (HICON) ::LoadImage(nullptr, Context.dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
               sync_lock sl1(m_pil48Hover->mutex());
               sync_lock sl2(m_pil48->mutex());
               iImage = m_pil16->add_icon_os_data(hicon16);
               m_pil48Hover->add_icon_os_data(hicon48);

               if (crBk == 0)
               {
                  System.imaging().Createcolor_blend_ImageList(
                     m_pil48,
                     m_pil48Hover,
                     RGB(255, 255, 240),
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
         strsize iFind = imagekey.m_strPath.find_ci("://");
         strsize iFind2 = imagekey.m_strPath.find_ci(":");
         if (iFind >= 0 || iFind2 >= 2)
         {
            string strProtocol = string(imagekey.m_strPath).Left(max(iFind, iFind2));
            i32 i = 0;

            while (i < strProtocol.get_length() && ansi_char_is_alphanumeric(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.get_length())
            {

               // heuristically valid protocol
               return get_image_by_file_extension(imagekey);

            }

            if (imagekey.m_eattribute.has(file_attribute_directory))
            {

               return get_image_by_file_extension(imagekey);

            }

         }

         string strExtension;

         if (::str::ends_ci(imagekey.m_strPath, ".sln"))
         {

            // output_debug_string("test .sln");

         }


         string strIcon48;

         string strIcon16;

         if (::str::ends_ci(imagekey.m_strPath, ".desktop"))
         {

            string str = Context.file().as_string(imagekey.m_strPath);

            string_array stra;

            stra.add_lines(str);

            stra.filter_begins_ci("icon=");

            if (stra.get_size() <= 0)
            {

               return -1;

            }

            string strIcon = stra[0];

            ::str::begins_eat_ci(strIcon, "icon=");

            strIcon48 = strIcon;

            strIcon16 = strIcon;

         }
         else
         {

            strIcon48 = linux_get_file_icon_path(imagekey.m_strPath, 48);

            strIcon16 = linux_get_file_icon_path(imagekey.m_strPath, 16);

         }

         if (strIcon48.has_char())
         {

            ::image_pointer pimage1 = Application.image().load_image(strIcon16);

            if (!::is_ok(pimage1))
            {

               return -1;

            }

            ::image_pointer pimage = Application.image().load_image(strIcon48);

            if (!::is_ok(pimage))
            {

               return -1;

            }

            ::image_pointer image16 = create_image({16, 16});

            if (!::is_ok(image16))
            {

               return -1;

            }

            ::image_pointer image48 = create_image({48, 48});

            if (!::is_ok(image48))
            {

               return -1;

            }

            pimage->get_graphics()->SetStretchBltMode(HALFTONE);

            pimage->get_graphics()->StretchBlt(0, 0, 16, 16, pimage1->get_graphics(), 0, 0, pimage1->width(), pimage1->height());

            pimage->get_graphics()->SetStretchBltMode(HALFTONE);

            pimage->get_graphics()->StretchBlt(0, 0, 48, 48, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());

            sync_lock sl1(m_pilHover[48]->mutex());

            sync_lock sl2(m_pil[48]->mutex());

            iImage = m_pil[16]->add_image(image16, 0, 0);

            m_pilHover[48]->add_image(image48, 0, 0);

            if (imagekey.m_cr == 0)
            {

               System.imaging().color_blend(m_pil[48], m_pilHover[48], RGB(255, 255, 240), 64);

            }
            else
            {

               *m_pil[48] = *m_pilHover[48];

            }

            return iImage;

         }


         string str(imagekey.m_strPath);


         //iImage = GetImageByExtension(oswindow, imagekey.m_strPath, imagekey.m_eicon, imagekey.m_eattribute, crBk);

         return iImage;

      }



//      linux::per_fork::per_fork(bool bInit)
//      {
//         if (bInit)
//         {
//
//            init();
//
//         }
//
//      }
//
//
//      linux::per_fork::~per_fork()
//      {
//
//      }
//
//
//      void linux::per_fork::init()
//      {
//
//
//
//      }
//
//      int linux::shell_run()
//      {
//
//         per_fork fork;
//
//
//
//
//         sync_lock sl(&m_mutexQueue);
//
//         while (thread_get_run())
//         {
//
//            if(m_keyptra.is_empty())
//            {
//
//               sl.unlock();
//
//               Sleep(100);
//
//            }
//            else
//            {
//
//               image_key * pkey = m_keyptra.first();
//
//               m_keyptra.remove_at(0);
//
//               sl.unlock();
//
//               int iImage = get_image(&fork, pkey->m_oswindow, *pkey, nullptr, pkey->m_cr);
//
//               {
//
//                  sync_lock s(mutex());
//
//                  m_imagemap.set_at(*pkey, iImage);
//
//               }
//
//               delete pkey;
//
//            }
//
//            sl.lock();
//
//         }
//
//         return 0;
//
//      }
//


//      i32 linux::get_image(oswindow oswindow, const string & strPath, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
//      {
//
//         i32 iImage = 0x80000000;
//
//         {
//            if (colorref_get_a_value(crBk) != 255)
//            {
//
//               crBk = 0;
//
//            }
//
//
//
//            image_key imagekey;
//
//            imagekey.set_path(strPath);
//
//            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//            imagekey.m_eattribute = eattribute;
//
//            imagekey.m_eicon = eicon;
//
//            imagekey.m_iIcon = 0;
//
//            imagekey.m_oswindow = oswindow;
//
//            imagekey.m_cr = crBk;
//
//            {
//
//               sync_lock sl(mutex());
//
//               if (m_imagemap.lookup(imagekey, iImage))
//               {
//
//                  return iImage;
//
//               }
//
//            }
//
//            image_key * pstore = new image_key(imagekey);
//
//            {
//
//               sync_lock sl(&m_mutexQueue);
//
//               m_keyptra.add(pstore);
//
//            }
//
//            imagekey.set_path("foo");
//
//            iImage = get_foo_image(nullptr, oswindow, imagekey, imagekey.m_cr);
//
//            sync_lock sl(mutex());
//
//            m_imagemap.set_at(imagekey, iImage);
//
//         }
//
//         return iImage;
//
//
//      }
//
//


      i32 shell::get_image_by_file_extension(image_key & imagekey)
      //i32 linux::get_image_foo(oswindow oswindow, const string & strExtension, e_file_attribute eattribute, e_icon eicon, COLORREF crBk)
      {

         i32 iImage = 0x80000000;

         {

            if (colorref_get_a_value(imagekey.m_cr) != 255)
            {

               imagekey.m_cr = 0;

            }


            image_key imagekey;

            imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();

            imagekey.set_extension(imagekey.m_strPath);

            imagekey.m_strPath = "foo";

//            imagekey.m_eattribute = eattribute;

//            imagekey.m_eicon = eicon;

            imagekey.m_iIcon = 0;

            {

               sync_lock sl(mutex());

               if (m_imagemap.lookup(imagekey, iImage))
               {

                  return iImage;

               }

            }

            iImage = get_file_image(imagekey);

            sync_lock sl(mutex());

            m_imagemap.set_at(imagekey, iImage);

         }

         return iImage;

      }


//      int shell::add_hover_image(int iSize, int iImage, COLORREF crBk)
//      {
//
//         if (crBk == 0)
//         {
//
//            return m_pilHover[iSize]->pred_add_image([&](auto pimage)
//            {
//
//               System.imaging().color_blend(pimage, RGB(255, 255, 240), 64);
//
//            }
//            , m_pil[iSize], iImage);
//
//         }
//         else
//         {
//
//            iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);
//
//            {
//
//               ::image_pointer pimage;
//               pimage = create_image({iSize,  iSize});
//               pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//               m_pilHover[iSize]->draw(pimage->get_graphics(), iImage, ::point(), 0);
//               m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//               m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
//               m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            }
//
//            {
//               auto & d = m_pilHover[iSize]->m_pimage;
//               size s = m_pil[iSize]->m_pimage->get_size();
//               ::image_pointer pimage;
//               pimage = __create_image(d->size());
//               pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::alpha_mode_blend);
//               pimage->get_graphics()->draw(::point(), d->size(), d->get_graphics());
//               pimage->get_graphics()->fill_rect(rect(d->size()), ARGB(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
//               m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_set);
//               m_pil[iSize]->m_pimage->g()->draw(::point(), d->size(), pimage->get_graphics());
//               m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::alpha_mode_blend);
//
//            }
//
//            return iImage;
//
//         }
//
//      }

   //} // namespace shell


} // namespace user







namespace core
{


   ::estatus user::create_user_shell()
   {

      ::estatus estatus = ::success;

      if (!m_pshell)
      {

         estatus = __compose(m_pshell, __new(::linux::shell));

         if (!estatus)
         {

            return estatus;

         }

      }

      if (!m_pshell)
      {

         return ::error_failed;

      }

      return ::success;

   }


} // namespace core
