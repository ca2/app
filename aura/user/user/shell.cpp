#include "framework.h"
//#include "aura/operating_system.h"
//#include "aura/user/_user.h"
#include "aura/user/user/shell.h"
//#include "acme/compress/zip/_.h"
//#include "acme/compress/gz.h"
#include "acme/primitive/primitive/atomic.h"
#include "acme/filesystem/filesystem/acme_directory.h"
#include "acme/filesystem/filesystem/acme_file.h"
#include "acme/filesystem/filesystem/acme_path.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/context_image.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/image/icon.h"


#if defined(RASPBIAN)
#define OPERATING_SYSTEM_NAMESPACE linux
#endif


namespace user
{


   shell::image_key::image_key()
   {

      m_iIcon = 0x80000000;

   }


   shell::image_key::image_key(const image_key & key)
   {

      m_strPath = key.m_strPath;
      m_iIcon = key.m_iIcon;
      m_eattribute = key.m_eattribute;
      m_eicon = key.m_eicon;
      m_strExtension = key.m_strExtension;
      m_strShellThemePrefix = key.m_strShellThemePrefix;

   }


   shell::image_key::image_key(const ::string & strPath, const ::string & strShellThemePrefix, enum_file_attribute eattribute, enum_icon eicon)
   {

      m_strPath = strPath;

      m_strShellThemePrefix = strShellThemePrefix;

      m_eattribute = eattribute;

      m_eicon = eicon;

      m_iIcon = 0;

   }


   shell::image_key::~image_key()
   {


   }


   void shell::image_key::set_path(const ::string & strPath, bool bSetExtension)
   {

      m_strPath = strPath;

      if (bSetExtension)
      {

         set_extension(strPath);

      }
      else
      {

         m_strExtension.Empty();

      }

   }


   void shell::image_key::set_extension(const ::string & strPath)
   {

      strsize iFind1 = strPath.rfind('/');

      strsize iFind2 = strPath.rfind('\\');

      strsize iFind = maximum(iFind1, iFind2) + 1;

      strsize iDot = strPath.find('.', iFind);

      if (iDot < 0)
      {

         m_strExtension.Empty();

      }
      else
      {

         m_strExtension = strPath.Mid(iDot + 1);

      }

   }


   shell::shell()
   {

      m_bAddDefaultIcons = false;
      m_bRequireHighQualityThumbnail = false;
      m_bPendingUpdate = false;
      m_bMax = false;
      m_iActiveThreadCount = 0;
      m_iMaxThreadCount = 1;

      m_pevNewImageKey = __new(manual_reset_event);

      m_pevNewImageKey->m_eobject += e_object_alertable_wait;

      m_iaSize.add(16);
      m_iaSize.add(24);
      m_iaSize.add(32);
      m_iaSize.add(48);
      m_iaSize.add(256);

      m_imagemap.InitHashTable(16383);

   }


   shell::~shell()
   {

   }


   void shell::initialize(::object * pobject)
   {

      if (m_bInitialized)
      {

         //return ::success;

         return;

      }

      //auto estatus = 
      
      ::object::initialize(pobject);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      synchronous_lock synchronouslock(mutex());

      branch();

      do_initialize();

      m_bPendingUpdate = true;

      m_bInitialized = true;

      //return success;

   }



   bool shell::reserve_image(_get_file_image_ & getfileimage)
   {

      synchronous_lock synchronouslock(mutex());

      if (contains_image(getfileimage.m_imagekey, getfileimage.m_iImage))
      {

         return false;

      }

      getfileimage.m_iImage = _reserve_image(getfileimage.m_imagekey);

      return true;

   }


   int shell::_reserve_image(const image_key & key)
   {

      synchronous_lock synchronouslock(mutex());

      int iImage = -1;

      for (auto iSize : m_iaSize)
      {

         iImage = m_pil[iSize]->reserve_image(iImage);

         iImage = m_pilHover[iSize]->reserve_image(iImage);

      }

      m_imagemap.set_at(key, iImage);

      return iImage;

   }


   bool shell::contains_image(const image_key & imagekey, i32 & iImage)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_imagemap.lookup(imagekey, iImage))
      {

         return true;

      }

      return false;

   }


   void shell::add_size_interest(int_array iaSize)
   {

      synchronous_lock synchronouslock(mutex());

      auto cAddedCount = m_iaSize.add_unique(iaSize);

      if (cAddedCount > 0)
      {

         m_iaSize.sort();

         m_bPendingUpdate = true;

      }

   }


   void shell::set_size_interest(int_array iaSize)
   {

      synchronous_lock synchronouslock(mutex());

      iaSize.sort();

      if (m_iaSize != iaSize)
      {

         m_iaSize = iaSize;

         m_bPendingUpdate = true;

      }

   }


   bool shell::would_set_thumbnail_for(_get_file_image_ & getfileimage)
   {

      ::file::path pathFinal;

      pathFinal = final_path(getfileimage);

      if (pathFinal.ends_ci(".jpg")
         || pathFinal.ends_ci(".jpeg")
         || pathFinal.ends_ci(".png")
         || pathFinal.ends_ci(".gif")
         || pathFinal.ends_ci(".bmp")
         || pathFinal.ends_ci(".svg")
         )
      {

         return true;

      }

      return false;

   }


   bool shell::defer_set_thumbnail(_get_file_image_ & getfileimage)
   {

      auto pcontextimage = m_pcontext->context_image();

      auto pimageTemplate = pcontextimage->load_image(getfileimage.m_imagekey.m_strPath);

      if (::is_ok(pimageTemplate))
      {

         getfileimage.m_iImage = _reserve_image(getfileimage.m_imagekey);

         if (getfileimage.m_iImage >= 0)
         {

            for (auto & iSize : m_iaSize)
            {

//               double dSize = (double)iSize;
//
//               double dRateWidth = dSize / (double)pimageTemplate->width();
//
//               double dRateHeight = dSize / (double)pimageTemplate->height();
//
//               double dRateMinimum = minimum(dRateWidth, dRateHeight);
//
//               int cx = (int) maximum(1.0, dRateMinimum * (double)pimageTemplate->width());
//
//               int cy = (int) maximum(1.0, dRateMinimum * (double)pimageTemplate->height());
//
//               auto pimage = pimageTemplate->get_image(cx, cy);

               image_source imagesource(pimageTemplate);

               rectangle_f64 rectangle(::size_f64(iSize, iSize));

               image_drawing_options imagedrawingoptions(rectangle, e_placement_aspect_fit, {0.0, 0.0});

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               set_image(getfileimage.m_iImage, iSize, imagedrawing);

            }

            return true;

         }

      }

      return false;

   }

 
   void shell::on_update_sizes_interest()
   {

      synchronous_lock synchronouslock(mutex());

      m_imagemap.erase_all();

      m_iaSize.sort();

      if (m_iaSize.is_empty())
      {

         m_iaSize.add(48);

      }

      for (auto iSize : m_iaSize)
      {

         if (m_pil[iSize].is_null())
         {

            __refer(m_pil[iSize], __create_new < ::image_list >());
            m_pil[iSize]->create(iSize, iSize, 0, 10, 10);

         }
         else
         {

            m_pil[iSize]->erase_all();

         }

         if (m_pilHover[iSize].is_null())
         {

            __refer(m_pilHover[iSize], __create_new < ::image_list >());
            m_pilHover[iSize]->create(iSize, iSize, 0, 10, 10);

         }
         else
         {

            m_pilHover[iSize]->erase_all();

         }

      }

      m_bAddDefaultIcons = true;

      m_bPendingUpdate = false;

   }


   void shell::get_scheduled_image_key(image_key & imagekey)
   {


      while (task_get_run())
      {

         {

            m_pevNewImageKey->_wait(500_ms);

            synchronous_lock synchronouslock(mutex());

            if (m_imagekeySchedule.has_elements())
            {

               imagekey = m_imagekeySchedule[0];

               m_imagekeySchedule.erase_at(0);

               return;

            }
            else
            {

               m_pevNewImageKey->ResetEvent();

            }

         }

      }


   }


   void shell::on_add_default_file_image(_get_file_image_ & getfileimage)
   {

      create_file_icon_image("bookmark://", e_file_attribute_directory, e_icon_normal, "icon://quickaccess", getfileimage);

      create_file_icon_image("bookmark://", e_file_attribute_directory, e_icon_open, "icon://quickaccess", getfileimage);

      create_file_icon_image("dropbox://", e_file_attribute_directory, e_icon_normal, "icon://dropbox", getfileimage);

      create_file_icon_image("dropbox://", e_file_attribute_directory, e_icon_open, "icon://dropbox", getfileimage);

      create_file_icon_image("dropbox-app://", e_file_attribute_directory, e_icon_normal, "icon://dropbox", getfileimage);

      create_file_icon_image("dropbox-app://", e_file_attribute_directory, e_icon_open, "icon://dropbox", getfileimage);

   }


   void shell::do_initialize()
   {


   }


   shell::_get_file_image_ * shell::new_get_file_image()
   {

      return new _get_file_image_;

   }

   
   ::file::path & shell::processed_path(_get_file_image_ & getfileimage)
   {

      if (getfileimage.m_pathProcessed.is_empty())
      {

         ::file::path pathProcessed = m_pcontext->m_papexcontext->defer_process_path(getfileimage.m_imagekey.m_strPath);

         getfileimage.m_pathProcessed = pathProcessed;

      }

      return getfileimage.m_pathProcessed;

   }


   ::file::path & shell::final_path(_get_file_image_ & getfileimage)
   {

      if(getfileimage.m_pathFinal.is_empty())
      {
      
         processed_path(getfileimage);

         ::file::path pathFinal = m_psystem->m_pacmepath->_final(getfileimage.m_pathProcessed);
      
         getfileimage.m_pathFinal = pathFinal;

      }
      
      return getfileimage.m_pathFinal;
      
   }


   ::image_list * shell::GetImageList(int iSize)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bPendingUpdate)
      {

         on_update_sizes_interest();

      }

      index i = 0;

      for (; i < m_iaSize.get_size(); i++)
      {

         if (iSize <= m_iaSize[i])
         {

            break;

         }

      }

      if (i >= m_iaSize.get_size())
      {

         i = m_iaSize.get_upper_bound();

      }

      if (i < 0)
      {

         return nullptr;

      }

      return m_pil[m_iaSize[i]];

   }


   ::image_list * shell::GetImageListHover(int iSize)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bPendingUpdate)
      {

         on_update_sizes_interest();

      }

      index i = 0;

      for (; i < m_iaSize.get_size(); i++)
      {

         if (iSize <= m_iaSize[i])
         {

            break;

         }

      }

      if (i >= m_iaSize.get_size())
      {

         i = m_iaSize.get_upper_bound();

      }

      if (i < 0)
      {

         return nullptr;

      }

      return m_pilHover[m_iaSize[i]];

   }


   shell::enum_folder shell::get_folder_type(::object * pobject, const ::wstring & wstrPath)
   {

      string str(wstrPath);

      return get_folder_type(pobject, str);

   }


   shell::enum_folder shell::get_folder_type(::object * pobject, const ::string & strPath)
   {

      wstring wstr(strPath);

      return get_folder_type(pobject, wstr);

   }


   void shell::get_file_extension_image(_get_file_image_ & getfileimage)
   {

      getfileimage.m_imagekey.m_strPath = "foo";

      getfileimage.m_imagekey.m_strShellThemePrefix = m_strShellThemePrefix;

      getfileimage.m_imagekey.m_iIcon = 0;

      get_file_image(getfileimage.m_imagekey);

   }


   i32 shell::get_file_image(const ::file::path & path, const ::user::shell::enum_file_attribute & eattribute, ::user::shell::enum_icon eicon)
   {

      synchronous_lock synchronouslock(mutex());

      image_key imagekey(path, m_strShellThemePrefix, eattribute, eicon);

      return get_file_image(imagekey);

   }


   i32 shell::get_file_image(const image_key & imagekey)
   {

      synchronous_lock synchronouslock(mutex());

      if (m_bPendingUpdate)
      {

         on_update_sizes_interest();

      }

      i32 iImage;

      if (m_imagemap.lookup(imagekey, iImage))
      {

         if (iImage == 0x80000001)
         {

            iImage = 0x80000000;

         }

         return iImage;

      }

      image_key imagekeyStore(imagekey);

      m_imagemap.set_at(imagekeyStore, 0x80000001); // mark as "calculating image"

      return schedule_get_file_image(imagekey);

   }


   i32 shell::schedule_get_file_image(const image_key & imagekey)
   {

      {

         synchronous_lock synchronouslock(mutex());

         m_imagekeySchedule.add(imagekey);

         m_pevNewImageKey->SetEvent();

      }

      return 0x80000000;

   }


   void shell::warn_when_ok(const ::file::path & path, const ::user::interaction_array & userinteractionaInterested)
   {

      synchronous_lock synchronouslock(mutex());

      for(auto & puserinteraction : userinteractionaInterested.m_interactiona)
      {

         m_mapInterest[puserinteraction].add_unique(path);

      }

   }


   void shell::warn_ok(const ::file::path & path)
   {

      synchronous_lock synchronouslock(mutex());

      for(auto & pair : m_mapInterest)
      {

         if(pair.m_element2.erase(path) > 0)
         {

            pair.m_element1->set_need_redraw();

            pair.m_element1->post_redraw();

            if(pair.m_element2.is_empty())
            {

               m_mapInterest.erase_key(pair.m_element1);

            }

         }

      }

   }



   bool shell::get_image_by_file_extension(_get_file_image_ & getfileimage)
   {
      
      return false;

   }


   bool shell::_get_file_image(_get_file_image_ & getfileimage)
   {
      
//      ::file::path path = getfileimage.m_imagekey.m_strPath;
//
////         image_key imagekey(imagekeyParam);
////
////         i32 iImage = 0x80000000;
//
//      if (::str::begins_ci(getfileimage.m_imagekey.m_strPath, "uifs:"))
//      {
//
//         auto pcontext = m_pcontext;
//
//         ::file::path path = pcontext->m_papexcontext->dir().matter("cloud.ico");
//
////            for (auto iSize : m_iaSize)
////            {
////
////
//////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////               //             iImage = add_icon(iSize, hicon, crBk);
////
////            }
//
//         single_lock synchronouslock(mutex(), true);
//
//         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);
//
//         //return iImage;
//
//         return;
//
//      }
//      else if (::str::begins_ci(getfileimage.m_imagekey.m_strPath, "fs:"))
//      {
//
//         auto pcontext = m_pcontext;
//
//         ::file::path path = pcontext->m_papexcontext->dir().matter("remote.ico");
//
////            for (auto iSize : m_iaSize)
////            {
////
////
//////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////               //             iImage = add_icon(iSize, hicon, crBk);
////
////            }
//
//         single_lock synchronouslock(mutex(), true);
//
//         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);
//
//         //return iImage;
//
//         return;
//
//      }
//      else if (::str::begins_ci(getfileimage.m_imagekey.m_strPath, "ftp:"))
//      {
//
//         auto pcontext = m_pcontext;
//
//         ::file::path path = pcontext->m_papexcontext->dir().matter("ftp.ico");
//
////            for (auto iSize : m_iaSize)
////            {
////
////
////               //HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
////
////               //iImage = add_icon(iSize, hicon, crBk);
////
////            }
//
//         single_lock synchronouslock(mutex(), true);
//
//         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);
//
//         //return iImage;
//
//         return;
//
//      }
//
//      if (::str::ends_ci(getfileimage.m_imagekey.m_strPath, ".aura"))
//      {
//
//         auto pcontext = m_pcontext;
//
//         string str = pcontext->m_papexcontext->file().as_string(getfileimage.m_imagekey.m_strPath);
//
//         if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
//         {
//
//            str.trim();
//            /*HICON hicon16 = (HICON) ::LoadImage(nullptr, pcontext->m_papexcontext->dir().matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
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
//         //return iImage;
//
//         return true;
//
//      }
//
//      // try to find "uifs:// http:// ftp:// like addresses"
//      // then should show icon by extension or if is folder
//
//      string strPath = getfileimage.m_imagekey.m_strPath;
//
//      string strRealPath = m_pcontext->m_papexcontext->defer_process_path(strPath);
//
//      string strFinalPath = m_psystem->m_pacmepath->_final(strRealPath);
//
//      if(strFinalPath.is_empty())
//      {
//
//         string strProtocol = m_psystem->m_purldepartment->get_protocol(path);
//
//         string strRoot = m_psystem->m_purldepartment->get_root(path);
//
//         if (strProtocol.has_char() && strRoot.has_char())
//         {
//
//            if(get_image_by_file_extension(getfileimage))
//            {
//
//               return true;
//
//            }
//
//         }
//
//      }
//
//      if(defer_set_thumbnail(getfileimage))
//      {
//
//         return true;
//
//      }
//
//      string strExtension;
//
//      if (::str::ends_ci(getfileimage.m_imagekey.m_strPath, ".sln"))
//      {
//
//         // output_debug_string("test .sln");
//
//      }
//
//      return false;

      
      string strPath = getfileimage.m_imagekey.m_strPath;

//         image_key imagekey(imagekeyParam);
//
//         i32 iImage = 0x80000000;

      if (::str::begins_ci(strPath, "uifs:"))
      {

         auto pcontext = m_pcontext;

         ::file::path path = pcontext->m_papexcontext->dir().matter("cloud.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               //             iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(mutex(), true);

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

         //return iImage;

         return true;

      }
      else if (::str::begins_ci(strPath, "fs:"))
      {

         auto pcontext = m_pcontext;

         ::file::path path = pcontext->m_papexcontext->dir().matter("remote.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               //             iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(mutex(), true);

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

         //return iImage;

         return true;

      }
      else if (::str::begins_ci(strPath, "ftp:"))
      {

         auto pcontext = m_pcontext;

         ::file::path path = pcontext->m_papexcontext->dir().matter("ftp.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
//               //HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               //iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(mutex(), true);

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

         //return iImage;

         return true;

      }

      if (::str::ends_ci(strPath, ".aura"))
      {

         auto pcontext = m_pcontext;

         string str = pcontext->m_papexcontext->file().as_string(strPath);

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
         //return iImage;

         return true;

      }

      // try to find "uifs:// http:// ftp:// like addresses"
      // then should show icon by extension or if is folder

      auto & pathFinal = final_path(getfileimage);

      if(pathFinal.is_empty())
      {

         string strProtocol = m_psystem->m_purldepartment->get_protocol(strPath);

         string strRoot = m_psystem->m_purldepartment->get_root(strPath);

         if (strProtocol.has_char() && strRoot.has_char())
         {

            if(get_image_by_file_extension(getfileimage))
            {
            
               return true;
               
            }

         }

      }

      if (would_set_thumbnail_for(getfileimage))
      {

         if (defer_set_thumbnail(getfileimage))
         {

            return true;

         }

      }
      
      if(m_bGetFileImageByIconPath)
      {
      
         if(defer_get_file_image_by_icon_path(getfileimage))
         {
            
            return true;
         
         }
         
      }
      
      bool bGetFileImageByFileTypeImage = m_bGetFileImageByFileTypeImage;

      if(bGetFileImageByFileTypeImage)
      {
         
         if(m_bGetFileImageByFileImage)
         {
            
            auto pacmepath = m_psystem->m_pacmepath;
         
            if(pacmepath->has_custom_icon(strPath))
            {
               
               bGetFileImageByFileTypeImage = false;
               
            }
               
         }

         if(bGetFileImageByFileTypeImage)
         {
      
            if(defer_get_file_image_by_file_type_image(getfileimage))
            {
               
               return true;
            
            }
            
         }
         
      }

      if(m_bGetFileImageByFileImage)
      {
      
         if(defer_get_file_image_by_file_image(getfileimage))
         {
            
            return true;
         
         }
         
      }
      
      return false;

   }


   bool shell::defer_get_file_image_by_icon_path(_get_file_image_ & getfileimage)
   {

      string strExtension;

      string strIcon48;

      string strIcon16;

      if (::str::ends_ci(getfileimage.m_imagekey.m_strPath, ".desktop"))
      {

         auto pcontext = m_pcontext;

         string str = pcontext->m_papexcontext->file().as_string(getfileimage.m_imagekey.m_strPath);

         string_array stra;

         stra.add_lines(str);

         stra.filter_begins_ci("icon=");

         if (stra.get_size() <= 0)
         {

            getfileimage.m_iImage = -1;

            return false;

         }

         string strIcon = stra[0];

         ::str::begins_eat_ci(strIcon, "icon=");

         strIcon48 = strIcon;

         strIcon16 = strIcon;

      }
      else
      {

         auto psystem = m_psystem->m_paurasystem;

         auto pnode = psystem->node();
         
         auto pathFinal = final_path(getfileimage);
         
         strIcon48 = pnode->get_file_icon_path(pathFinal, 48);

         strIcon16 = pnode->get_file_icon_path(pathFinal, 16);

      }

      if (strIcon16.has_char() || strIcon48.has_char())
      {

         if(strIcon16.has_char())
         {

            getfileimage.m_imagekey.m_strPath = strIcon16;

            getfileimage.m_imagekey.m_strExtension = "";

            getfileimage.m_imagekey.m_eicon = e_icon_normal;

            if(!reserve_image(getfileimage))
            {

               return false;

            }

         }
         else if(strIcon48.has_char())
         {

            getfileimage.m_imagekey.m_strPath = strIcon48;

            getfileimage.m_imagekey.m_strExtension = "";

            getfileimage.m_imagekey.m_eicon = e_icon_normal;

            if(!reserve_image(getfileimage))
            {

               return false;

            }

         }

         if(strIcon16.is_empty())
         {

            strIcon16 = strIcon48;

         }
         else if(strIcon48.is_empty())
         {

            strIcon48 = strIcon16;

         }

         ::image_pointer pimage1 = m_pcontext->m_pcontextimage->load_image(strIcon16);

         if (!::is_ok(pimage1))
         {

            return false;

         }

         auto pcontext = m_pcontext;

         auto pcontextimage = pcontext->context_image();

         ::image_pointer pimage = pcontextimage->load_image(strIcon48);

         if (!::is_ok(pimage))
         {

            return false;

         }

         ::image_pointer image16;

         if(pimage1->get_size() == ::size_i32(16, 16))
         {

            image16 = pimage1;

         }
         else
         {

            image16 = m_pcontext->context_image()->create_image({16, 16});

            if (!::is_ok(image16))
            {

               return false;

            }

            image16->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            image_source imagesource(pimage1, pimage1->rectangle());

            rectangle_f64 rectangle(::size_i32(16, 16));

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            image16->get_graphics()->draw(imagedrawing);

         }

         ::image_pointer image48;

         if(pimage->get_size() == ::size_i32(48, 48))
         {

            image48 = pimage;

         }
         else
         {

            image48 = m_pcontext->context_image()->create_image({48, 48});

            if (!::is_ok(image48))
            {

               return false;

            }

            image48->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            image_source imagesource(pimage, pimage->rectangle());

            rectangle_f64 rectangle(::size_i32(48, 48));

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            image48->get_graphics()->draw(imagedrawing);

         }

         {

            synchronous_lock sl1(m_pil[16]->mutex());

            image_source imagesource(pimage1, pimage1->rectangle());

            rectangle_f64 rectangle(::size_i32(16, 16));

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pil[16]->set(getfileimage.m_iImage, imagedrawing);

         }

         {

            synchronous_lock sl2(m_pil[48]->mutex());

            image_source imagesource(image48, image48->rectangle());

            rectangle_f64 rectangle(::size_i32(48, 48));

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pil[48]->set(getfileimage.m_iImage, imagedrawing);

         }

         {

            synchronous_lock sl1(m_pilHover[16]->mutex());

            image_source imagesource(image16, image16->rectangle());

            rectangle_f64 rectangle(::size_i32(16, 16));

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pil[16]->set(getfileimage.m_iImage, imagedrawing);

            m_pilHover[16]->color_blend(m_pil[16], rgb(255, 255, 240), 64);

         }

         {

            synchronous_lock sl1(m_pilHover[48]->mutex());

            image_source imagesource(image48, image48->rectangle());

            rectangle_f64 rectangle(::size_i32(48, 48));

            image_drawing_options imagedrawingoptions(rectangle);

            image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pil[48]->set(getfileimage.m_iImage, imagedrawing);

            m_pilHover[48]->color_blend(m_pil[48], rgb(255, 255, 240), 64);

         }

         return true;

         
      }

      return false;
      
   }


   bool shell::defer_get_file_image_by_file_type_image(_get_file_image_ & getfileimage)
   {
   
      auto psystem = m_psystem->m_paurasystem;
      
      auto pnode = psystem->node();
      
      auto pathFinal = final_path(getfileimage);
      
      string strTypeIdentifier = pnode->get_file_type_identifier(pathFinal);
      
      if(strTypeIdentifier.is_empty())
      {
         
         return false;
         
      }
      
      string strPath = getfileimage.m_imagekey.m_strPath;
      
      getfileimage.m_imagekey.m_strPath.Empty();
      
      getfileimage.m_imagekey.m_strExtension = strTypeIdentifier;
      
      if(!reserve_image(getfileimage))
      {
         
         // File Type Image already set
         
         return true;
         
      }
      
      image_pointer pimageFirst;
      
      auto iaSize = m_iaSize;
      
      iaSize.sort(false);

      for(int & iSize : iaSize)
      {
         
         auto pimage = pnode->get_file_image_by_type_identifier(iSize, strTypeIdentifier);
         
         if(!::is_ok(pimage))
         {
         
            if(!::is_ok(pimageFirst))
            {
               
               getfileimage.m_imagekey.m_strPath = strPath;
               
               getfileimage.m_imagekey.m_strExtension.Empty();
               
               return false;
            
            }
            
            pimage = pimageFirst;

         }
         else if(::is_null(pimageFirst))
         {
            
            pimageFirst = pimage;
            
         }

         image_source imagesource(pimage);

         set_image(getfileimage.m_iImage, iSize, imagesource);

      }

      return true;

//      if(strUniversalTypeIdentifier.has_char())
//      {
//
//         string strPathOld = getfileimage.m_imagekey.m_strPath;
//
//         getfileimage.m_imagekey.m_strPath.Empty();
//
//         getfileimage.m_imagekey.m_strExtension = strUniversalTypeIdentifier;
//
//         if(!reserve_image(getfileimage))
//         {
//
//            // Image already set for this file type.
//
//            return true;
//
//         }
//
//         ::image_pointer pimage;
//
//         pimage.create();
//
//         pimage->create({ 48, 48});
//
//         if (macos_get_file_image_by_type_identifier(pimage, strUniversalTypeIdentifier))
//         {
//
//            if (::is_ok(pimage))
//            {
//
//               image_source imagesource(pimage);
//
//               for(int & iSize : m_iaSize)
//               {
//
//                  set_image(getfileimage.m_iImage, iSize, imagesource);
//
//               }
//
//               return true;
//
//            }
//
//         }
//
//         getfileimage.m_imagekey.m_strPath = strPathOld;
//
//      }
//
//      return false;

   }


   bool shell::defer_get_file_image_by_file_image(_get_file_image_ & getfileimage)
   {
      
      auto psystem = m_psystem->m_paurasystem;
      
      auto pnode = psystem->node();
      
      auto pcontext = m_pcontext->m_papexcontext;
      
      string strPath = pcontext->defer_process_path(getfileimage.m_imagekey.m_strPath);
      
      image_pointer pimageFirst;
      
      auto iaSize = m_iaSize;
      
      iaSize.sort(false);
      
      for(int & iSize : iaSize)
      {
         
         auto pimage = pnode->get_file_image(iSize, strPath);
         
         if(!::is_ok(pimage))
         {
         
            if(!::is_ok(pimageFirst))
            {
          
               return false;
            
            }
            
            pimage = pimageFirst;
            
         }
         else if(::is_null(pimageFirst))
         {
            
            getfileimage.m_iImage = _reserve_image(getfileimage.m_imagekey);
          
            pimageFirst = pimage;
            
         }

         image_source imagesource(pimage);

         set_image(getfileimage.m_iImage, iSize, imagesource);

      }

      return true;
         
   }
      

   void shell::run()
   {

      auto_pointer < _get_file_image_ > pgetfileimage(new_get_file_image());

      while (task_get_run())
      {
         
         get_scheduled_image_key(pgetfileimage->m_imagekey);

         if (!task_get_run())
         {

            break;

         }

         if (m_bAddDefaultIcons)
         {

            m_bAddDefaultIcons = false;

            on_add_default_file_image(*pgetfileimage);

         }

         try
         {

            pgetfileimage->m_pathProcessed.Empty();
            
            pgetfileimage->m_pathFinal.Empty();

            auto strPath = pgetfileimage->m_imagekey.m_strPath;

            auto eicon = pgetfileimage->m_imagekey.m_eicon;

            _get_file_image(*pgetfileimage);

            pgetfileimage->m_imagekey.m_strPath = strPath;

            pgetfileimage->m_imagekey.m_strExtension.Empty();

            pgetfileimage->m_imagekey.m_iIcon = 0;

            pgetfileimage->m_imagekey.m_eicon = eicon;

            synchronous_lock synchronouslock(mutex());

            if (pgetfileimage->m_iImage & 0x80000000)
            {

               m_imagemap.erase_key(pgetfileimage->m_imagekey);

            }
            else
            {

               m_imagemap.set_at(pgetfileimage->m_imagekey, pgetfileimage->m_iImage);

               warn_ok(pgetfileimage->m_imagekey.m_strPath);

            }

         }
         catch (...)
         {

         }

      }

      //return ::success;

   }


   void shell::set_icon(int iImage, const ::file::path & pathIcon)
   {

      synchronous_lock synchronouslock(mutex());

      auto iaSize = m_iaSize;

      synchronouslock.unlock();

      ::file::path path = m_pcontext->m_papexcontext->defer_process_path(pathIcon);

      auto pwindowingicon = __create < windowing::icon >();

      pwindowingicon->load_file(path);

      auto pdraw2dicon = __create < draw2d::icon >();

      pdraw2dicon->initialize_with_windowing_icon(pwindowingicon);

      for (auto iSize : m_iaSize)
      {

         auto pcontext = m_pcontext->m_pauracontext;

         auto pcontextimage = pcontext->context_image();

         auto pimage = pdraw2dicon->image_source_image(::size_f64(iSize, iSize));

         if (::is_null(pimage))
         {

            output_debug_string("error loading image: \"" + path + "\"\n");

         }

         image_source imagesource(pimage);

         rectangle_f64 rectangle(::size_f64(iSize, iSize));

         image_drawing_options imagedrawingoptions(rectangle);

         image_drawing imagedrawing(imagedrawingoptions, imagesource);

         set_image(iImage, iSize, imagedrawing);

      }

   }

   
//   void shell::set_image(int iImage, int iSize, ::image * pimage)
//   {
//
//      synchronous_lock synchronouslock(m_pil[iSize]->mutex());
//
//      synchronous_lock slHover(m_pilHover[iSize]->mutex());
//
//      m_pil[iSize]->set(iImage, pimage);
//
//      auto pimageHover = m_pil[iSize]->get_image(iImage);
//
//      pimageHover->g()->fill_rectangle(pimage->rectangle(), ::color::color(255, 255, 240, 64));
//
//      m_pilHover[iSize]->set(iImage, pimageHover);
//
//   }


   void shell::set_image(int iImage, int iSize, image_drawing imagedrawing)
   {

      synchronous_lock synchronouslock(m_pil[iSize]->mutex());

      synchronous_lock slHover(m_pilHover[iSize]->mutex());

      m_pil[iSize]->set(iImage, imagedrawing);

      auto pimageHover = m_pil[iSize]->get_image(iImage);

      pimageHover->g()->fill_rectangle(pimageHover->rectangle(), ::color::color(255, 255, 240, 64));

      m_pilHover[iSize]->set(iImage, imagedrawing);

   }


   i32 shell::create_file_icon_image(const ::string & strPath, enum_file_attribute eattribute, enum_icon eicon, const string & strIcon, _get_file_image_ & getfileimage)
   {

      int iReturn = -1;

      auto pcontext = m_pcontext->m_papexcontext;

      auto pathFinal = pcontext->defer_process_path(strPath);

      if (pathFinal != strPath)
      {

         iReturn = _create_file_icon_image(pathFinal, eattribute, eicon, strIcon, getfileimage);

      }

      iReturn = _create_file_icon_image(strPath, eattribute, eicon, strIcon, getfileimage);

      return iReturn;

   }


   i32 shell::_create_file_icon_image(const ::string & strPath, enum_file_attribute eattribute, enum_icon eicon, const string & strIconParam, _get_file_image_ & getfileimage)
   {

      getfileimage.m_imagekey.m_strPath = strPath;
      getfileimage.m_imagekey.m_strShellThemePrefix = m_strShellThemePrefix;
      getfileimage.m_imagekey.m_eattribute = eattribute;
      getfileimage.m_imagekey.m_eicon = eicon;

      if (!reserve_image(getfileimage))
      {

         return getfileimage.m_iImage;

      }

      string strIcon(strIconParam);

      ::file::path pathIcon;

      m_imagemap[getfileimage.m_imagekey] = getfileimage.m_iImage;

      if (strIcon.begins_eat_ci("icon://"))
      {

         auto pcontext = m_pcontext->m_papexcontext;

         auto pcontextimage = pcontext->context_image();

         ::file::path pathFolder = m_psystem->m_pacmedirectory->ca2roaming() / "matter/icon";

         __pointer(::image) pimage;

         int_array iaSizeFallback;

         iaSizeFallback.add(1024);
         iaSizeFallback.add(512);
         iaSizeFallback.add(256);
         iaSizeFallback.add(128);
         iaSizeFallback.add(64);
         iaSizeFallback.add(48);
         iaSizeFallback.add(32);
         iaSizeFallback.add(24);
         iaSizeFallback.add(16);

         for (int & iSize : m_iaSize)
         {

            string strSize;

            strSize.format("%d", iSize);

            ::file::path pathImage = pathFolder / strSize / (strIcon + ".png");

            pimage = nullptr;

            if (m_psystem->m_pacmefile->exists(pathImage))
            {

               pimage = pcontextimage->get_image(pathImage);

            }

            if (!::is_ok(pimage))
            {

               for (int & iSizeFallback : iaSizeFallback)
               {

                  if (iSizeFallback != iSize)
                  {

                     strSize.format("%d", iSizeFallback);

                     pathImage = pathFolder / strSize / (strIcon + ".png");

                     if (m_psystem->m_pacmefile->exists(pathImage))
                     {

                        pimage = pcontextimage->get_image(pathImage);

                        if (::is_ok(pimage))
                        {

                           break;

                        }

                     }

                  }

               }

            }

            if (::is_ok(pimage))
            {

               image_source imagesource(pimage);

               rectangle_f64 rectangle(::size_f64(iSize, iSize));

               image_drawing_options imagedrawingoptions(rectangle);

               image_drawing imagedrawing(imagedrawingoptions, imagesource);

               set_image(getfileimage.m_iImage, iSize, imagedrawing);

            }

         }

         //return iImage;
         return getfileimage.m_iImage;

         //auto & dir = pcontext->dir();

         //pathIcon = pathFolder / "ico" / (strIcon + ".ico");

      }
      else
      {

         pathIcon = strIcon;

      }

      set_icon(getfileimage.m_iImage, pathIcon);

      return getfileimage.m_iImage;

   }



   //int shell::add_hover_image(int iSize, int iImage, ::color::color crBk)
   //{

   //   synchronous_lock synchronouslock(m_pilHover[iSize]->mutex());

   //   if (crBk == 0)
   //   {

   //      return m_pilHover[iSize]->predicate_add_image([&](auto pimage)
   //         {

   //            psystem->imaging().color_blend(pimage, rgb(255, 255, 240), 64);

   //         }
   //      , m_pil[iSize], iImage, iImage);

   //   }
   //   else
   //   {

   //      iImage = m_pilHover[iSize]->add_image(m_pil[iSize], iImage);

   //      {

   //         ::image_pointer pimage(this);
   //         pimage->create({ iSize, iSize });
   //         pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         m_pilHover[iSize]->draw(pimage->get_graphics(), iImage, nullptr, 0);
   //         m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         m_pilHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
   //         m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      {
   //         ::image_pointer d = m_pilHover[iSize]->m_pimage;
   //         size_i32 s = m_pil[iSize]->m_pimage->get_size();
   //         ::image_pointer pimage(this);
   //         pimage->create(d->size());
   //         pimage->fill(255, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk));
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //         pimage->get_graphics()->draw(nullptr, d->size(), d->get_graphics());
   //         pimage->get_graphics()->fill_solid_rect_dim(0, 0, d->size().cx, d->size().cy, argb(123, colorref_get_r_value(crBk), colorref_get_g_value(crBk), colorref_get_b_value(crBk)));
   //         m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         m_pil[iSize]->m_pimage->g()->draw(d->rectangle(), pimage->get_graphics());
   //         m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      return iImage;

   //   }


   //}

   //int shell::add_hover_image(int iSize, int iImage, const ::color::color& colorBackground)
   //{

   //   synchronous_lock synchronouslock(m_pilHover[iSize]->mutex());

   //   if (colorBackground.is_transparent())
   //   {

   //      auto pimage = m_pil[iSize]->get_image(iImage);
   //      
   //      pimage->g()->fill_rectangle(pimage->rectangle(), ::color::color(255, 255, 240, 64));

   //      m_pilHover[iSize]->add_image(pimage, 0, 0, iImage);

   //      return iImage;

   //   }
   //   else
   //   {

   //      auto pimage = m_pil[iSize]->get_image(iImage);

   //      iImage = m_pilHover[iSize]->add_image(pimage, 0, 0,  iImage);

   //      {

   //         ::image_pointer pimage(this);

   //         pimage->create({ iSize, iSize });

   //         pimage->fill(255, colorBackground.red, colorBackground.green, colorBackground.blue);

   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

   //         m_pilHover[iSize]->draw(pgraphics, iImage, nullptr, 0);

   //         m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //         auto rectangleDraw = ::rectangle_f64(::point_f64(iImage * 48, 0), ::size_f64(48, 48));

   //         m_pilHover[iSize]->m_pimage->g()->draw(rectangleDraw, pimage->get_graphics());

   //         m_pilHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      {

   //         ::image_pointer d = m_pilHover[iSize]->m_pimage;

   //         ::image_pointer pimage(this);

   //         pimage->create(d->size());

   //         pimage->fill(255, colorBackground.red, colorBackground.green, colorBackground.blue);
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //         pimage->get_graphics()->stretch(d->size(), d);
   //         pimage->get_graphics()->fill_rectangle(d->size(), argb(123, colorBackground.red, colorBackground.green, colorBackground.blue));
   //         m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         m_pil[iSize]->m_pimage->g()->draw(d->rectangle(), pimage->get_graphics());
   //         m_pil[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      return iImage;

   //   }

   //}


   //void shell::thread::destroy()
   //{

   //   return ::thread::destroy();

   //}


   void shell::destroy()
   {

      ::task::destroy();

      //task_erase_all();

      //return ::success;

   }



} // namespace user


//#ifdef WINDOWS_DESKTOP
//#include "aura/user/user/shell_windows.h"
//#elif defined(MACOS)
//#include "aura/user/user/shell_macos.h"
//#elif defined(APPLE_IOS)
//#include "aura/user/user/shell_ios.h"
//#elif defined(LINUX)
//#include "aura/user/user/shell_linux.h"
//#elif defined(ANDROID)
//#include "aura/user/user/shell_android.h"
//#elif defined(_UWP)
//#include "aura/user/user/shell_uwp.h"
//#else
//#error "Implement here"
//#endif





