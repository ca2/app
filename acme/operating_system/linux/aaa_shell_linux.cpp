#include "framework.h"
#include "shell_linux.h"
#include "acme/node/linux/_linux.h"





const char * linux_g_direct_get_file_icon_path(const ::file::path & path, int iSize);

string linux_get_file_icon_path(string strPath, int iSize)
{

   return ::string_from_strdup(linux_g_direct_get_file_icon_path(strPath, iSize));

}

const char * linux_g_direct_get_file_content_type(const ::scoped_string & scopedstrFile);

string core_linux_get_file_content_type(string strPath)
{

   return ::string_from_strdup(linux_g_direct_get_file_content_type(strPath));

}





namespace linux
{


//   namespace shell
//   {


      shell::shell()
      {

         set_get_file_content_type_function(&core_linux_get_file_content_type);

         defer_create_synchronization();
         //begin();

         //SHGetImageList(SHIL_SMALL, IID_IImageList, m_pimagelistSmall);
         //SHGetImageList(SHIL_LARGE, IID_IImageList, m_pimagelistLarge);
         //SHGetImageList(SHIL_EXTRALARGE, IID_IImageList, m_pimagelistExtraLarge);
         //SHGetImageList(SHIL_JUMBO, IID_IImageList, m_pimagelistJumbo);
         /// SHGetMalloc(&m_pmalloc);

//         for (::collection::index i = 0; i < get_processor_count() * 2; i++)
//         {
//
//            m_threadaGetImage.add(fork([&]()
//            {
//
//               ::parallelization::set_priority(::e_priority_highest);
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

//      int linux::get_image_by_extension(per_fork * pfork, oswindow oswindow, image_key & key, color32_t crBk)
//      {
//
//         return I32_MINIMUM;
//
//      }




//      int linux::get_file_extension_image(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//      {
//
//         int iImage;
//
//         wstring wstrFilePath;
//
////         imagekey.m_strPath = "foo";
//
//         imagekey.m_strShellThemePrefix = (char *)m_strShellThemePrefix.c_str();
//
//         {
//
//            synchronous_lock synchronouslock(this->synchronization());
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
////         }         synchronous_lock synchronouslock(this->synchronization());
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

      //   single_lock synchronouslock(mutex(), true);

      //   if (lpsf == nullptr)
      //      return false;
      //   int iType;
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
      //   //   int iImage = I32_MINIMUM;

      //   HICON hicon16 = nullptr;
      //   HICON hicon48 = nullptr;
      //   HRESULT hrIconLocation;
      //   HRESULT hrExtract;
      //   image_key imagekey;


      //   string strPathEx(strFilePath);
      //   string strExtra;

      //   unicode_to_utf8(strExtra, lpcszExtra);

      //   if (strExtra.length() > 0)
      //   {
      //      strPathEx += ":" + strExtra;
      //   }



      //   int iIcon = I32_MINIMUM;
      //   unsigned int uFlags = 0;

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
      //         &uFlags)))
      //      {
      //         strPath = szPath;
      //         if (strPath == "*")
      //         {
      //            auto pFind = strFilePath.rear_find('.');

      //            imagekey.m_iIcon = I32_MINIMUM;
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
      //   if (pcontext->directory()->is(unicode_to_utf8(szFilePath)))
      //   {
      //      if (imagekey.m_iIcon == I32_MINIMUM)
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
      //         //HGLOBAL hglobal = ::GlobalAlloc(GPTR, strPath.length() + 1);
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



      //int linux::get_image(per_fork * pfork, oswindow oswindow, image_key imagekey, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, color32_t crBk)
      //{

      //   int iImage = get_image(pfork, oswindow, imagekey, lpiidlAbsolute, lpiidlChild, lpcszExtra, crBk);

      //   _017ItemIDListFree(pfork, lpiidlChild);

      //   return iImage;

      //}





//      bool linux::get_icon( oswindow oswindow, const ::scoped_string & scopedstr, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
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
//      bool linux::get_icon(per_fork * pfork, oswindow oswindow, LPITEMIDLIST lpiidlAbsolute, const unichar * lpcszExtra, e_icon eicon, HICON * phicon16, HICON * phicon48)
//      {
//
//         single_lock synchronouslock(mutex(), true);
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


      shell::e_folder shell::get_folder_type(::particle * pparticle, const char * lpcsz)
      {

         return get_folder_type(pparticle, utf8_to_unicode(lpcsz));

      }


      shell::e_folder shell::get_folder_type(::particle * pparticle, const ::wide_character * lpcszPath)
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

            return folder_none;

         }

      }


      void shell::on_update_sizes_interest()
      {

         synchronous_lock synchronouslock(this->synchronization());

         m_iaSize.erase_all();

         m_iaSize.add(16);

         m_iaSize.add(48);

         ::user::shell::shell::on_update_sizes_interest();

      }


      int shell::impl_get_file_image(const image_key & imagekeyParam)
      {

         image_key imagekey(imagekeyParam);

         int iImage = I32_MINIMUM;

         if (case_insensitive_string_begins(imagekey.m_strPath, "uifs:"))
         {

            ::file::path path = pcontext->directory()->matter("cloud.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock synchronouslock(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (case_insensitive_string_begins(imagekey.m_strPath, "fs:"))
         {

            ::file::path path = pcontext->directory()->matter("remote.ico");

            for (auto iSize : m_iaSize)
            {


//               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //             iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock synchronouslock(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }
         else if (case_insensitive_string_begins(imagekey.m_strPath, "ftp:"))
         {

            ::file::path path = pcontext->directory()->matter("ftp.ico");

            for (auto iSize : m_iaSize)
            {


               //HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);

               //iImage = add_icon(iSize, hicon, crBk);

            }

            single_lock synchronouslock(mutex(), true);

            m_imagemap.set_at(imagekey, iImage);

            return iImage;

         }





         if (case_insensitive_string_ends(imagekey.m_strPath, ".acme"))
         {
            string str = file()->as_string(imagekey.m_strPath);
            if (str.case_insensitive_begins_eat("ca2prompt\r\n"))
            {
               str.trim();
               /*HICON hicon16 = (HICON) ::LoadImage(nullptr, pcontext->directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
               HICON hicon48 = (HICON) ::LoadImage(nullptr, pcontext->directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
               synchronous_lock sl1(m_pil48Hover->mutex());
               synchronous_lock sl2(m_pil48->mutex());
               iImage = m_pil16->add_icon_os_data(hicon16);
               m_pil48Hover->add_icon_os_data(hicon48);

               if (crBk == 0)
               {
                  ::acmeacmesystem()->imaging().Createcolor_blend_ImageList(
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
         auto pFind = imagekey.m_strPath.case_insensitive_find("://");
         character_count iFind2 = imagekey.m_strPath.case_insensitive_find(":");
         if (::is_set(pFind) || iFind2 >= 2)
         {
            string strProtocol = string(imagekey.m_strPath).left(maximum(iFind, iFind2));
            int i = 0;

            while (i < strProtocol.length() && ansi_char_is_alnum(strProtocol[i]))
            {

               i++;

            }

            if (i > 0 && i == strProtocol.length())
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

         if (case_insensitive_string_ends(imagekey.m_strPath, ".sln"))
         {
            
            // informationf("test .sln");

         }


         string strIcon48;

         string strIcon16;

         if (case_insensitive_string_ends(imagekey.m_strPath, ".desktop"))
         {

            string str = file()->as_string(imagekey.m_strPath);

            string_array stra;

            stra.add_lines(str);

            stra.case_insensitive_filter_begins("icon=");

            if (stra.get_size() <= 0)
            {

               return -1;

            }

            string strIcon = stra[0];

            strIcon.case_insensitive_begins_eat("icon=");

            strIcon48 = strIcon;

            strIcon16 = strIcon;

         }
         else
         {

            strIcon48 = linux_get_file_icon_path(imagekey.m_strPath, 48);

            strIcon16 = linux_get_file_icon_path(imagekey.m_strPath, 16);

         }

         if (strIcon48.has_character())
         {

            ::image::image_pointer pimage1 = load_image(strIcon16);

            if (!::is_ok(pimage1))
            {

               return -1;

            }

            ::image::image_pointer pimage =  load_image(strIcon48);

            if (!::is_ok(pimage))
            {

               return -1;

            }

            ::image::image_pointer image16 = __create_image({16, 16});

            if (!::is_ok(image16))
            {

               return -1;

            }

            ::image::image_pointer image48 = __create_image({48, 48});

            if (!::is_ok(image48))
            {

               return -1;

            }

            pimage->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

            pimage->get_graphics()->StretchBlt(0, 0, 16, 16, pimage1->get_graphics(), 0, 0, pimage1->width(), pimage1->height());

            pimage->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);

            pimage->get_graphics()->StretchBlt(0, 0, 48, 48, pimage->get_graphics(), 0, 0, pimage->width(), pimage->height());

            synchronous_lock sl1(m_pimagelistHover[48]->synchronization());

            synchronous_lock sl2(m_pimagelist[48]->synchronization());

            iImage = m_pimagelist[16]->add_image(image16, 0, 0);

            m_pimagelistHover[48]->add_image(image48, 0, 0);

            if (imagekey.m_cr == 0)
            {

               ::acmeacmesystem()->imaging().color_blend(m_pimagelist[48], m_pimagelistHover[48], rgb(255, 255, 240), 64);

            }
            else
            {

               *m_pimagelist[48] = *m_pimagelistHover[48];

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
//         synchronous_lock synchronouslock(m_pmutexQueue);
//
//         while (task_get_run())
//         {
//
//            if(m_keyptra.is_empty())
//            {
//
//               synchronouslock.unlock();
//
//               sleep(100_ms);
//
//            }
//            else
//            {
//
//               image_key * pkey = m_keyptra.first();
//
//               m_keyptra.erase_at(0);
//
//               synchronouslock.unlock();
//
//               int iImage = get_image(&fork, pkey->m_oswindow, *pkey, nullptr, pkey->m_cr);
//
//               {
//
//                  synchronous_lock s(mutex());
//
//                  m_imagemap.set_at(*pkey, iImage);
//
//               }
//
//               delete pkey;
//
//            }
//
//            synchronouslock.lock();
//
//         }
//
//         return 0;
//
//      }
//


//      int linux::get_image(oswindow oswindow, const ::scoped_string & scopedstrPath, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
//      {
//
//         int iImage = I32_MINIMUM;
//
//         {
//            if (color32_byte_opacity(crBk) != 255)
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
//               synchronous_lock synchronouslock(this->synchronization());
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
//            image_key * pstore = aaa_primitive_new image_key(imagekey);
//
//            {
//
//               synchronous_lock synchronouslock(m_pmutexQueue);
//
//               m_keyptra.add(pstore);
//
//            }
//
//            imagekey.set_path("foo");
//
//            iImage = get_foo_image(nullptr, oswindow, imagekey, imagekey.m_cr);
//
//            synchronous_lock synchronouslock(this->synchronization());
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


      int shell::get_image_by_file_extension(image_key & imagekey)
      //int linux::get_image_foo(oswindow oswindow, const ::scoped_string & scopedstrExtension, e_file_attribute eattribute, e_icon eicon, color32_t crBk)
      {

         int iImage = I32_MINIMUM;

         {

            if (color32_byte_opacity(imagekey.m_cr) != 255)
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

               synchronous_lock synchronouslock(this->synchronization());

               if (m_imagemap.lookup(imagekey, iImage))
               {

                  return iImage;

               }

            }

            iImage = get_file_image(imagekey);

            synchronous_lock synchronouslock(this->synchronization());

            m_imagemap.set_at(imagekey, iImage);

         }

         return iImage;

      }


//      int shell::add_hover_image(int iSize, int iImage, color32_t crBk)
//      {
//
//         if (crBk == 0)
//         {
//
//            return m_pimagelistHover[iSize]->predicate_add_image([&](auto pimage)
//            {
//
//               ::acmeacmesystem()->imaging().color_blend(pimage, rgb(255, 255, 240), 64);
//
//            }
//            , m_pimagelist[iSize], iImage);
//
//         }
//         else
//         {
//
//            iImage = m_pimagelistHover[iSize]->add_image(m_pimagelist[iSize], iImage);
//
//            {
//
//               ::image::image_pointer pimage;
//               pimage = create_image({iSize,  iSize});
//               pimage->fill(255, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//               m_pimagelistHover[iSize]->draw(pimage->get_graphics(), iImage, ::int_point(), 0);
//               m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//               m_pimagelistHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
//               m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//
//            }
//
//            {
//               auto & d = m_pimagelistHover[iSize]->m_pimage;
//               size s = m_pimagelist[iSize]->m_pimage->get_size();
//               ::image::image_pointer pimage;
//               pimage = __create_image(d->size());
//               pimage->fill(255, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk));
//               pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
//               pimage->get_graphics()->draw(::int_point(), d->size(), d->get_graphics());
//               pimage->get_graphics()->fill_rectangle(rectangle(d->size()), argb(123, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk)));
//               m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
//               m_pimagelist[iSize]->m_pimage->g()->draw(::int_point(), d->size(), pimage->get_graphics());
//               m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
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







