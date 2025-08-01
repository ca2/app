#include "framework.h"
#include "interaction_array.h"
#include "interaction.h"
#include "acme/parallelization/manual_reset_happening.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/filesystem/filesystem/directory_system.h"
#include "acme/filesystem/filesystem/file_system.h"
#include "acme/filesystem/filesystem/path_system.h"
#include "acme/platform/application.h"
#include "acme/prototype/prototype/atomic.h"
#include "acme/prototype/collection/_sort.h"
#include "acme/prototype/prototype/url.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/image/list.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/draw2d/graphics.h"
#include "aura/graphics/draw2d/lock.h"
#include "aura/graphics/image/icon.h"
#include "aura/graphics/image/drawing.h"
#include "aura/platform/node.h"
#include "aura/user/user/shell.h"
#include "aura/windowing/icon.h"


#include "acme/prototype/collection/_array.h"

#if defined(RASPBERRYPIOS)
#define OPERATING_SYSTEM_NAMESPACE linux
#endif


namespace user
{


   shell::image_key::image_key()
   {

      m_iIcon = I32_MINIMUM;

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


   shell::image_key::image_key(const ::scoped_string & scopedstrPath, const ::scoped_string & scopedstrShellThemePrefix, enum_file_attribute eattribute, enum_icon eicon)
   {

      m_strPath = scopedstrPath;

      m_strShellThemePrefix = scopedstrShellThemePrefix;

      m_eattribute = eattribute;

      m_eicon = eicon;

      m_iIcon = 0;

   }


   shell::image_key::~image_key()
   {


   }


   void shell::image_key::set_path(const ::scoped_string & scopedstrPath, bool bSetExtension)
   {

      m_strPath = scopedstrPath;

      if (bSetExtension)
      {

         set_extension(scopedstrPath);

      }
      else
      {

         m_strExtension.empty();

      }

   }


   void shell::image_key::set_extension(const ::scoped_string & scopedstrPath)
   {

      character_count iFind1 = scopedstrPath.rear_find_index('/');

      character_count iFind2 = scopedstrPath.rear_find_index('\\');

      auto iFind = maximum(iFind1, iFind2) + 1;

      character_count iDot = scopedstrPath.find_index('.', iFind);

      if (iDot < 0)
      {

         m_strExtension.empty();

      }
      else
      {

         m_strExtension = scopedstrPath.substr(iDot + 1);

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

      m_pevNewImageKey = __allocate manual_reset_happening();

      m_pevNewImageKey->m_eflagElement += e_flag_alertable_wait;

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


   void shell::initialize(::particle * pparticle)
   {

      if (m_bInitialized)
      {

         //return ::success;

         return;

      }

      //auto estatus = 
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      branch_synchronously();

      //synchronous_lock synchronouslock(this->synchronization());

      //return success;

   }


   // ::aura::application * shell::get_app()
   // {
   //
   //    return m_papplication ? m_papplication->m_papplication : nullptr;
   //
   // }
   //
   //
   // ::aura::session *shell:: get_session()
   // {
   //
   //    return m_papplication ? m_papplication->m_psession : nullptr;
   //
   // }


   //::aura::system * shellacmesystem()
   //{

   //   return system() ? system() : nullptr;

   //}


   bool shell::reserve_image(_get_file_image_ & getfileimage)
   {

      ::draw2d::lock lock(this);

      _synchronous_lock synchronouslock(this->synchronization());

      if (contains_image(getfileimage.m_imagekey, getfileimage.m_iImage))
      {

         return false;

      }

      getfileimage.m_iImage = _reserve_image(getfileimage.m_imagekey);

      return true;

   }


   int shell::_reserve_image(const image_key & key)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      int iImage = -1;

      for (auto iSize : m_iaSize)
      {

         iImage = m_pimagelist[iSize]->reserve_image(iImage);

         iImage = m_pimagelistHover[iSize]->reserve_image(iImage);

      }

      m_imagemap.set_at(key, iImage);

      return iImage;

   }


   bool shell::contains_image(const image_key & imagekey, int & iImage)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_imagemap.lookup(imagekey, iImage))
      {

         return true;

      }

      return false;

   }


   void shell::add_size_interest(::int_array iaSize)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto cAddedCount = m_iaSize.append_unique(iaSize);

      if (cAddedCount > 0)
      {

         ::sort::QuickSortAsc(m_iaSize);

         m_bPendingUpdate = true;

      }

   }


   void shell::set_size_interest(::int_array iaSize)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      ::sort::QuickSortAsc(iaSize);

      if (::acme::array::is_different(m_iaSize, iaSize))
      {

         m_iaSize = iaSize;

         m_bPendingUpdate = true;

      }

   }


   bool shell::would_set_thumbnail_for(_get_file_image_ & getfileimage)
   {

      ::file::path pathFinal;

      pathFinal = final_path(getfileimage);

      auto strFinalExtension = pathFinal.final_extension();

      if (strFinalExtension.case_insensitive_equals("jpg")
         || strFinalExtension.case_insensitive_equals("jpeg")
         || strFinalExtension.case_insensitive_equals("png")
         || strFinalExtension.case_insensitive_equals("gif")
         || strFinalExtension.case_insensitive_equals("bmp")
         || strFinalExtension.case_insensitive_equals("svg")
         || strFinalExtension.case_insensitive_equals("webp")
         )
      {

         return true;

      }

      return false;

   }


   bool shell::defer_set_thumbnail(_get_file_image_ & getfileimage)
   {

      auto pimagecontext = image();

      auto pimageTemplate = image()->load_image(getfileimage.m_imagekey.m_strPath);

      if (pimageTemplate.ok())
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

               ::image::image_source imagesource(pimageTemplate);

               double_rectangle rectangle(::double_size(iSize, iSize));

               ::image::image_drawing_options imagedrawingoptions(rectangle, ::image::e_placement_aspect_fit, {0.0, 0.0});

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

               set_image(getfileimage.m_iImage, iSize, imagedrawing);

            }

            return true;

         }

      }

      return false;

   }

 
   void shell::on_update_sizes_interest()
   {

      _synchronous_lock synchronouslock(this->synchronization());

      m_imagemap.erase_all();

      ::sort::QuickSortAsc(m_iaSize);

      if (m_iaSize.is_empty())
      {

         m_iaSize.add(48);

      }

      for (auto iSize : m_iaSize)
      {

         if (m_pimagelist[iSize].is_null())
         {

            m_pimagelist[iSize] = __create_new < ::image::image_list >();
            m_pimagelist[iSize]->create(iSize, iSize, 0, 10, 10);

         }
         else
         {

            m_pimagelist[iSize]->erase_all();

         }

         if (m_pimagelistHover[iSize].is_null())
         {

            m_pimagelistHover[iSize] = __create_new < ::image::image_list >();

            m_pimagelistHover[iSize]->create(iSize, iSize, 0, 10, 10);

         }
         else
         {

            m_pimagelistHover[iSize]->erase_all();

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

            m_pevNewImageKey->wait(500_ms);

            _synchronous_lock synchronouslock(this->synchronization());

            if (m_imagekeySchedule.has_elements())
            {

               imagekey = m_imagekeySchedule[0];

               m_imagekeySchedule.erase_at(0);

               return;

            }
            else
            {

               m_pevNewImageKey->reset_happening();

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

      return __raw_new _get_file_image_();

   }

   
   ::file::path & shell::processed_path(_get_file_image_ & getfileimage)
   {

      if (getfileimage.m_pathProcessed.is_empty())
      {

         ::file::path pathProcessed = m_papplication->defer_process_matter_path(getfileimage.m_imagekey.m_strPath);

         getfileimage.m_pathProcessed = pathProcessed;

      }

      return getfileimage.m_pathProcessed;

   }


   ::file::path & shell::final_path(_get_file_image_ & getfileimage)
   {

      if(getfileimage.m_pathFinal.is_empty())
      {
      
         processed_path(getfileimage);

         auto pathFinal = path_system()->safe_get_real_path(getfileimage.m_pathProcessed);
      
         getfileimage.m_pathFinal = pathFinal;

      }
      
      return getfileimage.m_pathFinal;
      
   }


   ::image::image_list * shell::GetImageList(int iSize)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_bPendingUpdate)
      {

         on_update_sizes_interest();

      }

      ::collection::index i = 0;

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

      return m_pimagelist[m_iaSize[i]];

   }


   ::image::image_list * shell::GetImageListHover(int iSize)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_bPendingUpdate)
      {

         on_update_sizes_interest();

      }

      ::collection::index i = 0;

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

      return m_pimagelistHover[m_iaSize[i]];

   }


   // shell::enum_folder shell::get_folder_type(::particle * pparticle, const ::wstring & wstrPath)
   // {
   //
   //    string str(wstrPath);
   //
   //    return get_folder_type(pparticle, str);
   //
   // }


   shell::enum_folder shell::get_folder_type(::particle * pparticle, const ::scoped_string & scopedstrPath)
   {

      wstring wstr(scopedstrPath);

      return get_folder_type(pparticle, wstr);

   }


   void shell::get_file_extension_image(_get_file_image_ & getfileimage)
   {

      getfileimage.m_imagekey.m_strPath = "foo";

      getfileimage.m_imagekey.m_strShellThemePrefix = m_strShellThemePrefix;

      getfileimage.m_imagekey.m_iIcon = 0;

      get_file_image(getfileimage.m_imagekey);

   }


   int shell::get_file_image(const ::file::path & path, const ::user::shell::enum_file_attribute & eattribute, ::user::shell::enum_icon eicon)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      image_key imagekey(path, m_strShellThemePrefix, eattribute, eicon);

      return get_file_image(imagekey);

   }


   int shell::get_file_image(const image_key & imagekey)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      if (m_bPendingUpdate)
      {

         on_update_sizes_interest();

      }

      int iImage;

      if (m_imagemap.lookup(imagekey, iImage))
      {

         if (iImage == 0x80000001)
         {

            iImage = I32_MINIMUM;

         }

         return iImage;

      }

      image_key imagekeyStore(imagekey);

      m_imagemap.set_at(imagekeyStore, 0x80000001); // mark as "calculating image"

      return schedule_get_file_image(imagekey);

   }


   int shell::schedule_get_file_image(const image_key & imagekey)
   {

      {

         _synchronous_lock synchronouslock(this->synchronization());

         m_imagekeySchedule.add(imagekey);

         m_pevNewImageKey->set_happening();

      }

      return I32_MINIMUM;

   }


   void shell::warn_when_ok(const ::file::path & path, const ::user::interaction_array & userinteractionaInterested)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      for(auto & puserinteraction : userinteractionaInterested.m_interactiona)
      {

         m_mapInterest[puserinteraction].add_unique(path);

      }

   }


   void shell::warn_ok(const ::file::path & path)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      bool bErasedAnyAtForLoop;

      do
      {

         bErasedAnyAtForLoop = false;

         for (auto & pair : m_mapInterest)
         {

            if (pair.m_element2.erase(path) > 0)
            {

               pair.m_element1->set_need_redraw();

               pair.m_element1->post_redraw();

               if (pair.m_element2.is_empty())
               {

                  m_mapInterest.erase_item(pair.m_element1);

                  bErasedAnyAtForLoop = true;

                  break;

               }

            }

         }

      } while (bErasedAnyAtForLoop);

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
////         int iImage = I32_MINIMUM;
//
//      if (case_insensitive_string_begins(getfileimage.m_imagekey.m_strPath, "uifs:"))
//      {
//
//         auto pcontext = m_papplication;
//
//         ::file::path path = directory()->matter("cloud.ico");
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
//      else if (case_insensitive_string_begins(getfileimage.m_imagekey.m_strPath, "fs:"))
//      {
//
//         auto pcontext = m_papplication;
//
//         ::file::path path = directory()->matter("remote.ico");
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
//      else if (case_insensitive_string_begins(getfileimage.m_imagekey.m_strPath, "ftp:"))
//      {
//
//         auto pcontext = m_papplication;
//
//         ::file::path path = directory()->matter("ftp.ico");
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
//      if (case_insensitive_string_ends(getfileimage.m_imagekey.m_strPath, ".aura"))
//      {
//
//         auto pcontext = m_papplication;
//
//         string str = file()->as_string(getfileimage.m_imagekey.m_strPath);
//
//         if (str.case_insensitive_begins_eat("ca2prompt\r\n"))
//         {
//
//            str.trim();
//            /*HICON hicon16 = (HICON) ::LoadImage(nullptr, directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
//            HICON hicon48 = (HICON) ::LoadImage(nullptr, directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
//            _synchronous_lock sl1(m_pil48Hover->synchronization());
//            _synchronous_lock sl2(m_pil48->synchronization());
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
//      string strRealPath = m_papplication->defer_process_matter_path(strPath);
//
//      string strFinalPath = path_system()->_final(strRealPath);
//
//      if(strFinalPath.is_empty())
//      {
//
//         string strProtocol = url()->get_protocol(path);
//
//         string strRoot = url()->get_root(path);
//
//         if (strProtocol.has_character() && strRoot.has_character())
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
//      if (case_insensitive_string_ends(getfileimage.m_imagekey.m_strPath, ".sln"))
//      {
//
//         // informationf("test .sln");
//
//      }
//
//      return false;

      
      string strPath = getfileimage.m_imagekey.m_strPath;

//         image_key imagekey(imagekeyParam);
//
//         int iImage = I32_MINIMUM;

      if (strPath.case_insensitive_begins("uifs:"))
      {

            ::file::path path = directory()->matter("cloud.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               //             iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(synchronization(), true);

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

         //return iImage;

         return true;

      }
      else if (strPath.case_insensitive_begins("fs:"))
      {

            ::file::path path = directory()->matter("remote.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
////               HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               //             iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(synchronization(), true);

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

         //return iImage;

         return true;

      }
      else if (strPath.case_insensitive_begins("ftp:"))
      {

            ::file::path path = directory()->matter("ftp.ico");

//            for (auto iSize : m_iaSize)
//            {
//
//
//               //HICON hicon = (HICON)LoadImage(nullptr, path, IMAGE_ICON, iSize, iSize, LR_LOADFROMFILE);
//
//               //iImage = add_icon(iSize, hicon, crBk);
//
//            }

         single_lock synchronouslock(synchronization(), true);

         m_imagemap.set_at(getfileimage.m_imagekey, getfileimage.m_iImage);

         //return iImage;

         return true;

      }

      if (strPath.case_insensitive_ends(".aura"))
      {

            string str = file()->as_string(strPath);

         if (str.case_insensitive_begins_eat("ca2prompt\r\n"))
         {

            str.trim();
            /*HICON hicon16 = (HICON) ::LoadImage(nullptr, directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 16, 16, LR_LOADFROMFILE);
            HICON hicon48 = (HICON) ::LoadImage(nullptr, directory()->matter(str + "/mainframe/icon.ico"), IMAGE_ICON, 48, 48, LR_LOADFROMFILE);
            _synchronous_lock sl1(m_pil48Hover->synchronization());
            _synchronous_lock sl2(m_pil48->synchronization());
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

         ::url::url url(strPath);

         string strProtocol = url.connect().protocol();

         string strRoot = url.connect().host();

         if (strProtocol.has_character() && strRoot.has_character())
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
            
            auto pacmepath = path_system();
         
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

      if (getfileimage.m_imagekey.m_strPath.case_insensitive_ends(".desktop"))
      {

            string str = file()->as_string(getfileimage.m_imagekey.m_strPath);

         string_array stra;

         stra.add_lines(str);

         stra.case_insensitive_filter_begins("icon=");

         if (stra.get_size() <= 0)
         {

            getfileimage.m_iImage = -1;

            return false;

         }

         string strIcon = stra[0];

         strIcon.case_insensitive_begins_eat("icon=");

         strIcon48 = strIcon;

         strIcon16 = strIcon;

      }
      else
      {

         auto psystem = system();

         auto pnode = psystem->node();
         
         auto pathFinal = final_path(getfileimage);
         
         strIcon48 = pnode->get_file_icon_path(pathFinal, 48);

         strIcon16 = pnode->get_file_icon_path(pathFinal, 16);

      }

      if (strIcon16.has_character() || strIcon48.has_character())
      {

         if(strIcon16.has_character())
         {

            getfileimage.m_imagekey.m_strPath = strIcon16;

            getfileimage.m_imagekey.m_strExtension = "";

            getfileimage.m_imagekey.m_eicon = e_icon_normal;

            if(!reserve_image(getfileimage))
            {

               return false;

            }

         }
         else if(strIcon48.has_character())
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

         ::image::image_pointer pimage1 = m_papplication->m_pimagecontext->load_image(strIcon16);

         if (pimage1.nok())
         {

            return false;

         }

         ::image::image_pointer pimage = image()->load_image(strIcon48);

         if (pimage.nok())
         {

            return false;

         }

         ::image::image_pointer image16;

         if(pimage1->get_size() == ::int_size(16, 16))
         {

            image16 = pimage1;

         }
         else
         {

            image16 = image()->create_image({16, 16});

            if (image16.nok())
            {

               return false;

            }

            image16->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            ::image::image_source imagesource(pimage1, pimage1->rectangle());

            double_rectangle rectangle(::int_size(16, 16));

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            image16->get_graphics()->draw(imagedrawing);

         }

         ::image::image_pointer image48;

         if(pimage->get_size() == ::int_size(48, 48))
         {

            image48 = pimage;

         }
         else
         {

            image48 = image()->create_image({48, 48});

            if (image48.nok())
            {

               return false;

            }

            image48->get_graphics()->set_interpolation_mode(::draw2d::e_interpolation_mode_high_quality_bicubic);

            ::image::image_source imagesource(pimage, pimage->rectangle());

            double_rectangle rectangle(::int_size(48, 48));

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            image48->get_graphics()->draw(imagedrawing);

         }

         {

            _synchronous_lock sl1(m_pimagelist[16]->synchronization());

            ::image::image_source imagesource(pimage1, pimage1->rectangle());

            double_rectangle rectangle(::int_size(16, 16));

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pimagelist[16]->set(getfileimage.m_iImage, imagedrawing);

         }

         {

            _synchronous_lock sl2(m_pimagelist[48]->synchronization());

            ::image::image_source imagesource(image48, image48->rectangle());

            double_rectangle rectangle(::int_size(48, 48));

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pimagelist[48]->set(getfileimage.m_iImage, imagedrawing);

         }

         {

            _synchronous_lock sl1(m_pimagelistHover[16]->synchronization());

            ::image::image_source imagesource(image16, image16->rectangle());

            double_rectangle rectangle(::int_size(16, 16));

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pimagelist[16]->set(getfileimage.m_iImage, imagedrawing);

            m_pimagelistHover[16]->color_blend(m_pimagelist[16], rgb(255, 255, 240), 64);

         }

         {

            _synchronous_lock sl1(m_pimagelistHover[48]->synchronization());

            ::image::image_source imagesource(image48, image48->rectangle());

            double_rectangle rectangle(::int_size(48, 48));

            ::image::image_drawing_options imagedrawingoptions(rectangle);

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            getfileimage.m_iImage = m_pimagelist[48]->set(getfileimage.m_iImage, imagedrawing);

            m_pimagelistHover[48]->color_blend(m_pimagelist[48], rgb(255, 255, 240), 64);

         }

         return true;

         
      }

      return false;
      
   }


   bool shell::defer_get_file_image_by_file_type_image(_get_file_image_ & getfileimage)
   {
   
      auto pnode = node();
      
      auto pathFinal = final_path(getfileimage);
      
      string strTypeIdentifier = pnode->get_file_type_identifier(pathFinal);
      
      if(strTypeIdentifier.is_empty())
      {
         
         return false;
         
      }
      
      string strPath = getfileimage.m_imagekey.m_strPath;
      
      getfileimage.m_imagekey.m_strPath.empty();
      
      getfileimage.m_imagekey.m_strExtension = strTypeIdentifier;
      
      if(!reserve_image(getfileimage))
      {
         
         // File Type Image already set
         
         return true;
         
      }
      
      ::image::image_pointer pimageFirst;
      
      auto iaSize = m_iaSize;
      
      ::sort::QuickSortDesc(iaSize);

      for(int & iSize : iaSize)
      {
         
         auto pimage = pnode->get_file_image_by_type_identifier(iSize, strTypeIdentifier);
         
         if(pimage.nok())
         {
         
            if(pimageFirst.nok())
            {
               
               getfileimage.m_imagekey.m_strPath = strPath;
               
               getfileimage.m_imagekey.m_strExtension.empty();
               
               return false;
            
            }
            
            pimage = pimageFirst;

         }
         else if(::is_null(pimageFirst))
         {
            
            pimageFirst = pimage;
            
         }

         ::image::image_source imagesource(pimage);

         set_image(getfileimage.m_iImage, iSize, imagesource);

      }

      return true;

//      if(strUniversalTypeIdentifier.has_character())
//      {
//
//         string strPathOld = getfileimage.m_imagekey.m_strPath;
//
//         getfileimage.m_imagekey.m_strPath.empty();
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
//         ::image::image_pointer pimage;
//
//         pimage.create();
//
//         pimage->create({ 48, 48});
//
//         if (macos_get_file_image_by_type_identifier(pimage, strUniversalTypeIdentifier))
//         {
//
//            if (pimage.ok())
//            {
//
//               ::image::image_source imagesource(pimage);
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
      
      auto psystem = system();
      
      auto pnode = psystem->node();
      
      auto pcontext = m_papplication;
      
      string strPath = pcontext->defer_process_path(getfileimage.m_imagekey.m_strPath);
      
      ::image::image_pointer pimageFirst;
      
      auto iaSize = m_iaSize;
      
      ::sort::QuickSortDesc(iaSize);
      
      for(int & iSize : iaSize)
      {
         
         auto pimage = pnode->get_file_image(iSize, strPath);
         
         if(pimage.nok())
         {
         
            if(pimageFirst.nok())
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

         ::image::image_source imagesource(pimage);

         set_image(getfileimage.m_iImage, iSize, imagesource);

      }

      return true;
         
   }


   void shell::init_task()
   {

      m_pgetfileimage = new_get_file_image();

      do_initialize();

      m_bPendingUpdate = true;

      m_bInitialized = true;

   }
      

   void shell::run()
   {

      while (task_get_run())
      {

         if (m_bAddDefaultIcons)
         {

            m_bAddDefaultIcons = false;

            on_add_default_file_image(*m_pgetfileimage);

         }

         get_scheduled_image_key(m_pgetfileimage->m_imagekey);

         if (!task_get_run())
         {

            break;

         }

         try
         {

            m_pgetfileimage->m_pathProcessed.empty();
            
            m_pgetfileimage->m_pathFinal.empty();

            auto strPath = m_pgetfileimage->m_imagekey.m_strPath;

            auto eicon = m_pgetfileimage->m_imagekey.m_eicon;

            _get_file_image(*m_pgetfileimage);

            m_pgetfileimage->m_imagekey.m_strPath = strPath;

            m_pgetfileimage->m_imagekey.m_strExtension.empty();

            m_pgetfileimage->m_imagekey.m_iIcon = 0;

            m_pgetfileimage->m_imagekey.m_eicon = eicon;

            _synchronous_lock synchronouslock(this->synchronization());

            if (m_pgetfileimage->m_iImage & I32_MINIMUM)
            {

               m_imagemap.erase_item(m_pgetfileimage->m_imagekey);

            }
            else
            {

               auto & iImage = m_imagemap[m_pgetfileimage->m_imagekey];

               if (iImage <= 0)
               {

                  iImage = m_pgetfileimage->m_iImage;

               }

               warn_ok(m_pgetfileimage->m_imagekey.m_strPath);

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

      _synchronous_lock synchronouslock(this->synchronization());

      auto iaSize = m_iaSize;

      synchronouslock.unlock();

      ::file::path path = m_papplication->defer_process_matter_path(pathIcon);

      auto pwindowingicon = __øcreate < windowing::icon >();

      pwindowingicon->load_file(path);

      auto pdraw2dicon = __øcreate < ::image::icon >();

      pdraw2dicon->initialize_with_windowing_icon(pwindowingicon);

      for (auto iSize : m_iaSize)
      {

         auto pimage = pdraw2dicon->image_source_image(::double_size(iSize, iSize));

         if (::is_null(pimage))
         {

            information("error loading image: \"" + path + "\"\n");

         }

         ::image::image_source imagesource(pimage);

         double_rectangle rectangle(::double_size(iSize, iSize));

         ::image::image_drawing_options imagedrawingoptions(rectangle);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         set_image(iImage, iSize, imagedrawing);

      }

   }

   
//   void shell::set_image(int iImage, int iSize, ::image::image *pimage)
//   {
//
//      _synchronous_lock synchronouslock(m_pimagelist[iSize]->synchronization());
//
//      _synchronous_lock slHover(m_pimagelistHover[iSize]->synchronization());
//
//      m_pimagelist[iSize]->set(iImage, pimage);
//
//      auto pimageHover = m_pimagelist[iSize]->get_image(iImage);
//
//      pimageHover->g()->fill_rectangle(pimage->rectangle(), ::rgba(255, 255, 240, 64));
//
//      m_pimagelistHover[iSize]->set(iImage, pimageHover);
//
//   }


   void shell::set_image(int iImage, int iSize, ::image::image_drawing imagedrawing)
   {

      _synchronous_lock synchronouslock(this->synchronization());

      auto pimagelist = m_pimagelist[iSize];

      auto pimagelistHover = m_pimagelistHover[iSize];

      synchronouslock.unlock();

      _synchronous_lock sl(pimagelist->synchronization());

      _synchronous_lock slHover(pimagelistHover->synchronization());

      pimagelist->set(iImage, imagedrawing);

      auto pimageHover = pimagelist->get_image(iImage);

      pimageHover->g()->fill_rectangle(pimageHover->rectangle(), ::rgba(255, 255, 240, 64));

      pimagelistHover->set(iImage, imagedrawing);

   }


   int shell::create_file_icon_image(const ::scoped_string & scopedstrPath, enum_file_attribute eattribute, enum_icon eicon, const ::scoped_string & scopedstrIcon, _get_file_image_ & getfileimage)
   {

      int iReturn = -1;

      auto pcontext = m_papplication;

      auto pathFinal = pcontext->defer_process_path(scopedstrPath);

      if (pathFinal != scopedstrPath)
      {

         iReturn = _create_file_icon_image(pathFinal, eattribute, eicon, scopedstrIcon, getfileimage);

      }

      iReturn = _create_file_icon_image(scopedstrPath, eattribute, eicon, scopedstrIcon, getfileimage);

      return iReturn;

   }


   int shell::_create_file_icon_image(const ::scoped_string & scopedstrPath, enum_file_attribute eattribute, enum_icon eicon, const ::scoped_string & scopedstrIconParam, _get_file_image_ & getfileimage)
   {

      getfileimage.m_imagekey.set_path(scopedstrIconParam, false);
      getfileimage.m_imagekey.m_strShellThemePrefix = m_strShellThemePrefix;
      getfileimage.m_imagekey.m_eattribute = eattribute;
      getfileimage.m_imagekey.m_eicon = eicon;

      bool bReserved = reserve_image(getfileimage);

      getfileimage.m_imagekey.set_path(scopedstrPath, false);

      auto & iImage = m_imagemap[getfileimage.m_imagekey];

      iImage = getfileimage.m_iImage;

      if(!bReserved)
      {
      
         return getfileimage.m_iImage;

      }

      string strIcon(scopedstrIconParam);

      ::file::path pathIcon;

      //m_imagemap[getfileimage.m_imagekey] = getfileimage.m_iImage;

      if (strIcon.case_insensitive_begins_eat("icon://"))
      {

         ::file::path pathFolder = directory_system()->ca2roaming() / "matter/icon";

         //::file::path pathIco = pathFolder / "ico" / (strIcon + ".ico");

         //if (file_system()->exists(pathIco))
         //{

         //   set_image_ico()

         //   return getfileimage.m_iImage;

         //}


         ::pointer<::image::image>pimage;

         ::int_array iaSizeFallback;

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

            strSize.formatf("%d", iSize);

            ::file::path pathImage = pathFolder / strSize / (strIcon + ".png");

            pimage = nullptr;

            if (file_system()->exists(pathImage))
            {

               pimage = image()->get_image(pathImage);

            }

            if (pimage.nok())
            {

               for (int & iSizeFallback : iaSizeFallback)
               {

                  if (iSizeFallback != iSize)
                  {

                     strSize.formatf("%d", iSizeFallback);

                     pathImage = pathFolder / strSize / (strIcon + ".png");

                     if (file_system()->exists(pathImage))
                     {

                        pimage = image()->get_image(pathImage);

                        if (pimage.ok())
                        {

                           break;

                        }

                     }

                  }

               }

            }

            if (pimage.ok())
            {

               ::image::image_source imagesource(pimage);

               double_rectangle rectangle(::double_size(iSize, iSize));

               ::image::image_drawing_options imagedrawingoptions(rectangle);

               ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

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

   //   _synchronous_lock synchronouslock(m_pimagelistHover[iSize]->synchronization());

   //   if (crBk == 0)
   //   {

   //      return m_pimagelistHover[iSize]->predicate_add_image([&](auto pimage)
   //         {

   //            psystem->imaging().color_blend(pimage, rgb(255, 255, 240), 64);

   //         }
   //      , m_pimagelist[iSize], iImage, iImage);

   //   }
   //   else
   //   {

   //      iImage = m_pimagelistHover[iSize]->add_image(m_pimagelist[iSize], iImage);

   //      {

   //         ::image::image_pointer pimage(this);
   //         pimage->create({ iSize, iSize });
   //         pimage->fill(255, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk));
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         m_pimagelistHover[iSize]->draw(pimage->get_graphics(), iImage, nullptr, 0);
   //         m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         m_pimagelistHover[iSize]->m_pimage->g()->BitBlt(iImage * 48, 0, 48, 48, pimage->get_graphics());
   //         m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      {
   //         ::image::image_pointer d = m_pimagelistHover[iSize]->m_pimage;
   //         int_size s = m_pimagelist[iSize]->m_pimage->get_size();
   //         ::image::image_pointer pimage(this);
   //         pimage->create(d->size());
   //         pimage->fill(255, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk));
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //         pimage->get_graphics()->draw(nullptr, d->size(), d->get_graphics());
   //         pimage->get_graphics()->fill_solid_rect_dim(0, 0, d->size().cx(), d->size().cy(), argb(123, color32_byte_red(crBk), color32_byte_green(crBk), color32_byte_blue(crBk)));
   //         m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         m_pimagelist[iSize]->m_pimage->g()->draw(d->rectangle(), pimage->get_graphics());
   //         m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      return iImage;

   //   }


   //}

   //int shell::add_hover_image(int iSize, int iImage, const ::color::color& colorBackground)
   //{

   //   _synchronous_lock synchronouslock(m_pimagelistHover[iSize]->synchronization());

   //   if (colorBackground.is_transparent())
   //   {

   //      auto pimage = m_pimagelist[iSize]->get_image(iImage);
   //      
   //      pimage->g()->fill_rectangle(pimage->rectangle(), ::rgba(255, 255, 240, 64));

   //      m_pimagelistHover[iSize]->add_image(pimage, 0, 0, iImage);

   //      return iImage;

   //   }
   //   else
   //   {

   //      auto pimage = m_pimagelist[iSize]->get_image(iImage);

   //      iImage = m_pimagelistHover[iSize]->add_image(pimage, 0, 0,  iImage);

   //      {

   //         ::image::image_pointer pimage(this);

   //         pimage->create({ iSize, iSize });

   //         pimage->fill(255, colorBackground.red, colorBackground.green, colorBackground.blue);

   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //         ::draw2d::graphics_pointer pgraphics = pimage->get_graphics();

   //         m_pimagelistHover[iSize]->draw(pgraphics, iImage, nullptr, 0);

   //         m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);

   //         auto rectangleDraw = ::double_rectangle(::double_point(iImage * 48, 0), ::double_size(48, 48));

   //         m_pimagelistHover[iSize]->m_pimage->g()->draw(rectangleDraw, pimage->get_graphics());

   //         m_pimagelistHover[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

   //      }

   //      {

   //         ::image::image_pointer d = m_pimagelistHover[iSize]->m_pimage;

   //         ::image::image_pointer pimage(this);

   //         pimage->create(d->size());

   //         pimage->fill(255, colorBackground.red, colorBackground.green, colorBackground.blue);
   //         pimage->get_graphics()->set_alpha_mode(::draw2d::e_alpha_mode_blend);
   //         pimage->get_graphics()->stretch(d->size(), d);
   //         pimage->get_graphics()->fill_rectangle(d->size(), argb(123, colorBackground.red, colorBackground.green, colorBackground.blue));
   //         m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_set);
   //         m_pimagelist[iSize]->m_pimage->g()->draw(d->rectangle(), pimage->get_graphics());
   //         m_pimagelist[iSize]->m_pimage->g()->set_alpha_mode(::draw2d::e_alpha_mode_blend);

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

      if(m_pimagelist.size()>0)
      {
         for(auto &pimagelist : m_pimagelist.payloads())
         {
            pimagelist.defer_destroy();
         }
      }
      if(m_pimagelistHover.size()>0)
      {
         for(auto &pimagelist : m_pimagelistHover.payloads())
         {
            pimagelist.defer_destroy();
         }
      }
      m_pimagelist.clear();
      m_pimagelistHover.clear();


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
//#elif defined(__ANDROID__)
//#include "aura/user/user/shell_android.h"
//#elif defined(UNIVERSAL_WINDOWS)
//#include "aura/user/user/shell_uwp.h"
//#else
//#error "Implement here"
//#endif





