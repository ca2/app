//
//  user_shell_macos.cpp
//  aura
//
//  Created by Camilo Sasuke Tsumanuma on 30/12/16.
//  Copyright © 2016 ca2 Desenvolvimento de Sofware Ltda. All rights reserved.
//

#include "framework.h"
//
//#include "apex/compress/zip/context.h"
//
//#include "shell_macos.h"
//
//bool macos_get_file_image(::image * pimage, const ::string & psz);
//
//
//namespace macos
//{
//
//
//   shell::shell()
//   {
//
//      defer_create_mutex();
//
//   }
//   
//
//   shell::~shell()
//   {
//
//   }
//
//
//   i32 shell::get_image_by_extension(image_key & key, color32_t crBk)
//   {
//
//      return 0x80000000;
//
//   }
//
//
//
//   i32 shell::get_foo_image(image_key imagekey, color32_t crBk)
//   {
//
//      i32 iImage = -1;
//
//      m_imagemap.set_at(imagekey, iImage);
//
//      return iImage;
//
//   }
//
//
//   shell::e_folder shell::get_folder_type(::object * pobject, const ::string & lpcszPath)
//   {
//
//      string strPath(lpcszPath);
//
//      if (         auto psystem = m_psystem;
//
//         auto pacmedir = psystem->m_pacmedir;
//
//pacmedir->is(strPath))
//      {
//         return folder_file_system;
//      }
//      else
//      {
//         
//         ::zip_context context(this);
//      
//         if (context.is_unzippable(strPath))
//         {
//            
//            return folder_zip;
//      
//         }
//         else
//         {
//
//            return folder_none;
//      
//         }
//
//      }
//
//   }
//
//
//   i32 shell::get_image(image_key imagekey, const unichar * lpcszExtra, color32_t crBk)
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
//         m_imagemap.set_at(imagekey, iImage);
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
//         m_imagemap.set_at(imagekey, iImage);
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
//         m_imagemap.set_at(imagekey, iImage);
//
//         return iImage;
//
//      }
//
//      if (::str::ends_ci(imagekey.m_strPath, ".aura"))
//      {
//         string str = pcontext->m_papexcontext->file().as_string(imagekey.m_strPath);
//         if (::str::begins_eat_ci(str, "ca2prompt\r\n"))
//         {
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
//         return iImage;
//      }
//      // try to find "uifs:// http:// ftp:// like addresses"
//      // then should show icon by extension or if is folder
//      strsize iFind = ::str::find_ci("://", imagekey.m_strPath);
//      strsize iFind2 = ::str::find_ci(":", imagekey.m_strPath);
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
//            return get_image_by_extension(imagekey, crBk);
//
//         }
//
//         if (imagekey.m_eattribute.has(file_attribute_directory))
//         {
//
//            return get_image_by_extension(imagekey, crBk);
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
//      auto pimage48 = create_image({48,  48});
//
//      pimage48->fill(0);
//
//      string strPath = imagekey.m_strPath;
//
//      if (macos_get_file_image(pimage48, strPath))
//      {
//         
//         auto pimage16 = create_image({16,  16});
//
//         pimage16->fill(0);
//
//         {
//            
//            synchronous_lock sl1(m_pilHover[16]->mutex());
//            
//            synchronous_lock sl2(m_pil[16]->mutex());
//            
//            if (macos_get_file_image(pimage16, strPath))
//            {
//               
//               iImage = m_pil[16]->add_image(pimage16, 0, 0);
//               
//               m_pilHover[16]->add_image(pimage16, 0, 0);
//
//            }
//            else
//            {
//
//               pimage16->get_graphics()->set_interpolation_mode(e_interpolation_mode_high_quality_bicubic);
//
//               pimage16->get_graphics()->StretchBlt(0, 0, 48, 48, pimage48->get_graphics(), 0, 0, pimage48->width(), pimage48->height());
//
//               iImage = m_pil[16]->add_image(pimage16, 0, 0);
//
//               m_pilHover[16]->add_image(pimage16, 0, 0);
//
//            }
//
//         }
//
//         synchronous_lock sl1(m_pilHover[48]->mutex());
//
//         synchronous_lock sl2(m_pil[48]->mutex());
//
//         iImage = m_pil[48]->add_image(pimage48, 0, 0);
//
//         m_pilHover[48]->add_image(pimage48, 0, 0);
//
//         if (crBk == 0)
//         {
//
//            psystem->imaging().color_blend(
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
//
//      //#endif
//
//      return iImage;
//
//   }
//
//
//   i32 shell::impl_get_file_image(const image_key & imagekey)
//   {
//
//      i32 iImage = 0x80000000;
//
//      image_key * pstore = new image_key(imagekey);
//
//      {
//
//         synchronous_lock synchronouslock(&m_mutexQueue);
//
//         m_keyptra.add(pstore);
//
//      }
//      
//      image_key i2(imagekey);
//
//      i2.set_path("foo");
//
//      iImage = get_foo_image(i2, i2.m_cr);
//
//      synchronous_lock synchronouslock(mutex());
//
//      m_imagemap.set_at(imagekey, iImage);
//
//      return iImage;
//
//   }
//
//
//   void shell::do_initialize()
//   {
//
//      on_update_sizes_interest();
//
//      fork([&]()
//      {
//
//         synchronous_lock synchronouslock(&m_mutexQueue);
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
//               int iImage = get_image(*pkey, nullptr, pkey->m_cr);
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
//      });
//
//
//   }
//
//
//} // namespace macos
//
//
//
//
//
//namespace core
//{
//
//
//   ::e_status user::create_user_shell()
//   {
//
//      ::e_status estatus = ::success;
//
//      if (!m_pshell)
//      {
//
//         estatus = __compose(m_pshell, __new(::macos::shell));
//
//         if (!estatus)
//         {
//
//            return estatus;
//
//         }
//
//      }
//
//      if (m_pshell)
//      {
//
//         return ::error_failed;
//
//      }
//
//      return ::success;
//
//   }
//
//
//} // namespace core
//
//
//
