#include "framework.h"
//#include "aura/operating_system.h"
#include "aura/user/_user.h"
#include "aura/user/shell.h"
#include "acme/compress/zip/_.h"
#include "acme/compress/gz.h"
#include "acme/primitive/primitive/atomic.h"
#include "acme/filesystem/filesystem/acme_dir.h"

#if defined(RASPBIAN)
#define PLATFORM_NAMESPACE linux
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


   ::e_status shell::initialize(::object * pobject)
   {

      if (m_bInitialized)
      {

         return ::success;

      }

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      synchronous_lock synchronouslock(mutex());

      branch();

      do_initialize();

      m_bPendingUpdate = true;
      //on_update_sizes_interest();

      m_bInitialized = true;

      return success;

   }


   //void shell::add_thread()
   //{

   //   synchronous_lock synchronouslock(mutex());

   //   auto pthread = __new(thread(this));

   //   add_composite(pthread);

   //}


   //shell::thread::thread(shell * pshell)
   //{

   //   initialize(pshell);

   //   __refer(m_pshell, pshell);

   //   branch();

   //}


   //shell::thread::~thread()
   //{

   //}


   /*::e_status shell::thread::init_thread()
   {

      m_bSimpleMessageLoop = false;

      if (!::thread::init_thread())
      {

         return false;

      }

#ifdef WINDOWS
      defer_co_initialize_ex(false);
#endif

      return true;

   }*/

   bool shell::reserve_image(const image_key & imagekey, i32 & iImage)
   {

      synchronous_lock synchronouslock(mutex());

      if (contains_image(imagekey, iImage))
      {

         return false;

      }

      iImage = _reserve_image(imagekey);

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


   bool shell::defer_set_thumbnail(_get_file_image_ & getfileimage)
   {

      auto psystem = m_psystem->m_paurasystem;

      auto pcontextimage = psystem->context_image();

      auto pimageTemplate = pcontextimage->load_image(getfileimage.m_imagekey.m_strPath);

      if (::is_ok(pimageTemplate))
      {

         getfileimage.m_iImage = _reserve_image(getfileimage.m_imagekey);

         if (getfileimage.m_iImage >= 0)
         {

            for (auto & iSize : m_iaSize)
            {

               double dSize = (double)iSize;

               double dRateWidth = dSize / (double)pimageTemplate->width();

               double dRateHeight = dSize / (double)pimageTemplate->height();

               double dRateMinimum = minimum(dRateWidth, dRateHeight);

               int cx = (int) maximum(1.0, dRateMinimum * (double)pimageTemplate->width());

               int cy = (int) maximum(1.0, dRateMinimum * (double)pimageTemplate->height());

               auto pimage = pimageTemplate->get_image(cx, cy);

               set_image(getfileimage.m_iImage, iSize, pimage);

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

            m_pil[iSize] = __create_new < ::image_list >();
            m_pil[iSize]->create(iSize, iSize, 0, 10, 10);

         }
         else
         {

            m_pil[iSize]->erase_all();

         }

         if (m_pilHover[iSize].is_null())
         {

            m_pilHover[iSize] = __create_new < ::image_list >();
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

            m_pevNewImageKey->wait();

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


   }


   void shell::do_initialize()
   {


   }


   shell::_get_file_image_ * shell::new_get_file_image()
   {

      return new _get_file_image_;

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


   i32 shell::get_file_image(const ::file::path & path, ::user::shell::enum_file_attribute & eattribute, ::user::shell::enum_icon eicon)
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


   void shell::_get_file_image(_get_file_image_ & getfileimage)
   {

   }


   ::e_status shell::run()
   {

      auto_pointer < _get_file_image_ > pgetfileimage(new_get_file_image());

      while (task_get_run())
      {

//         image_key imagekey;

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

            auto strPath = pgetfileimage->m_imagekey.m_strPath;

            _get_file_image(*pgetfileimage);

            pgetfileimage->m_imagekey.m_strPath = strPath;

            pgetfileimage->m_imagekey.m_strExtension.Empty();

            pgetfileimage->m_imagekey.m_iIcon = 0;

            synchronous_lock synchronouslock(mutex());

            if (pgetfileimage->m_iImage & 0x80000000)
            {

               m_imagemap.erase_key(pgetfileimage->m_imagekey);

            }
            else
            {

               m_imagemap.set_at(pgetfileimage->m_imagekey, pgetfileimage->m_iImage);

            }

         }
         catch (...)
         {

         }

      }

      return ::success;

   }


   void shell::set_icon(const ::file::path & pathIcon, _get_file_image_ & getfileimage)
   {

      synchronous_lock synchronouslock(mutex());

      auto iaSize = m_iaSize;

      synchronouslock.unlock();

      ::file::path path = m_pcontext->m_papexcontext->defer_process_path(pathIcon);

      for (auto iSize : m_iaSize)
      {

         auto pcontext = m_pcontext->m_pauracontext;

         auto pcontextimage = pcontext->context_image();

         auto pimage = pcontextimage->get_image(path);

         if (::is_null(pimage))
         {

            output_debug_string("error loading image: \"" + path + "\"\n");

         }

         set_image(getfileimage.m_iImage, iSize, pimage);

      }

   }

   
   void shell::set_image(int iImage, int iSize, ::image * pimage)
   {

      synchronous_lock synchronouslock(m_pil[iSize]->mutex());

      synchronous_lock slHover(m_pilHover[iSize]->mutex());

      m_pil[iSize]->set(iImage, pimage);

      auto pimageHover = m_pil[iSize]->get_image(iImage);

      pimageHover->g()->fill_rectangle(pimage->rectangle(), ::color::color(255, 255, 240, 64));

      m_pilHover[iSize]->set(iImage, pimageHover);

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

      // auto_pointer < _get_file_image_ > pgetfileimage(new_get_file_image());

      getfileimage.m_imagekey.m_strPath = strPath;
      getfileimage.m_imagekey.m_strShellThemePrefix = m_strShellThemePrefix;
      getfileimage.m_imagekey.m_eattribute = eattribute;
      getfileimage.m_imagekey.m_eicon = eicon;

      if (!reserve_image(getfileimage.m_imagekey, getfileimage.m_iImage))
      {

         return -1;

      }

      string strIcon(strIconParam);

      ::file::path pathIcon;

      m_imagemap[getfileimage.m_imagekey] = getfileimage.m_iImage;

      if (strIcon.begins_eat_ci("icon://"))
      {

         auto pcontext = m_pcontext->m_papexcontext;

         auto pcontextimage = pcontext->context_image();

         ::file::path pathFolder = m_psystem->m_pacmedir->ca2roaming() / "matter/icon";

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

            strSize.Format("%d", iSize);

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

                     strSize.Format("%d", iSizeFallback);

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

               pimage = pimage->get_image(iSize, iSize);

               set_image(getfileimage.m_iImage, iSize, pimage);

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

      set_icon(pathIcon, getfileimage);

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

   //         auto rectDraw = ::rectangle_f64(::point_f64(iImage * 48, 0), ::size_f64(48, 48));

   //         m_pilHover[iSize]->m_pimage->g()->draw(rectDraw, pimage->get_graphics());

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


   //::e_status shell::thread::destroy()
   //{

   //   return ::thread::destroy();

   //}


   ::e_status shell::destroy()
   {

      ::task::destroy();

      //task_erase_all();

      return ::success;

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





