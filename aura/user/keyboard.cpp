#include "framework.h"
#include "aura/user/_user.h"


//#if defined(LINUX) || defined(SOLARIS)
////#include "base/base/os/x11/x11_keyboard.h"
//string x11_keyboard_get_current_group_symbol();
//#elif defined(MACOS)
//string keyboard_input_source();
//#endif



namespace user
{

#ifdef LINUX


   CLASS_DECL_AURA ::user::enum_key keysym_to_userkey(const lparam & lparam);

#elif defined(MACOS)

   CLASS_DECL_AURA ::user::enum_key vkcode_to_userkey(wparam wparam);

#endif

   keyboard::keyboard()
   {



   }


   keyboard::~keyboard()
   {

   }


   ::e_status keyboard::initialize(::object * pobject)
   {

      auto estatus = ::object::initialize(pobject);

      if (!estatus)
      {

         return estatus;

      }

      auto psystem = m_psystem->m_paurasystem;

      SET_ENUM_TEXT(e_key_0);
      SET_ENUM_TEXT(e_key_1);
      SET_ENUM_TEXT(e_key_2);
      SET_ENUM_TEXT(e_key_3);
      SET_ENUM_TEXT(e_key_4);
      SET_ENUM_TEXT(e_key_5);
      SET_ENUM_TEXT(e_key_6);
      SET_ENUM_TEXT(e_key_7);
      SET_ENUM_TEXT(e_key_8);
      SET_ENUM_TEXT(e_key_9);
      SET_ENUM_TEXT(e_key_a);
      SET_ENUM_TEXT(e_key_b);
      SET_ENUM_TEXT(e_key_c);
      SET_ENUM_TEXT(e_key_d);
      SET_ENUM_TEXT(e_key_e);
      SET_ENUM_TEXT(e_key_f);
      SET_ENUM_TEXT(e_key_g);
      SET_ENUM_TEXT(e_key_h);
      SET_ENUM_TEXT(e_key_i);
      SET_ENUM_TEXT(e_key_j);
      SET_ENUM_TEXT(e_key_k);
      SET_ENUM_TEXT(e_key_l);
      SET_ENUM_TEXT(e_key_m);
      SET_ENUM_TEXT(e_key_n);
      SET_ENUM_TEXT(e_key_o);
      SET_ENUM_TEXT(e_key_p);
      SET_ENUM_TEXT(e_key_q);
      SET_ENUM_TEXT(e_key_r);
      SET_ENUM_TEXT(e_key_s);
      SET_ENUM_TEXT(e_key_t);
      SET_ENUM_TEXT(e_key_u);
      SET_ENUM_TEXT(e_key_v);
      SET_ENUM_TEXT(e_key_w);
      SET_ENUM_TEXT(e_key_x);
      SET_ENUM_TEXT(e_key_y);
      SET_ENUM_TEXT(e_key_z);
      SET_ENUM_TEXT(e_key_semicolon);
      SET_ENUM_TEXT(e_key_semicolon2);
      SET_ENUM_TEXT(e_key_comma);
      SET_ENUM_TEXT(e_key_dot);
      SET_ENUM_TEXT(e_key_shift);
      SET_ENUM_TEXT(e_key_left_shift);
      SET_ENUM_TEXT(e_key_right_shift);
      SET_ENUM_TEXT(e_key_control);
      SET_ENUM_TEXT(e_key_left_control);
      SET_ENUM_TEXT(e_key_right_control);
      SET_ENUM_TEXT(e_key_alt);
      SET_ENUM_TEXT(e_key_left_alt);
      SET_ENUM_TEXT(e_key_right_alt);
      SET_ENUM_TEXT(e_key_command);
      SET_ENUM_TEXT(e_key_left_command);
      SET_ENUM_TEXT(e_key_right_command);
      SET_ENUM_TEXT(e_key_left_button);
      SET_ENUM_TEXT(e_key_middle_button);
      SET_ENUM_TEXT(e_key_right_button);
      SET_ENUM_TEXT(e_key_back);
      SET_ENUM_TEXT(e_key_delete);
      SET_ENUM_TEXT(e_key_space);
      SET_ENUM_TEXT(e_key_right);
      SET_ENUM_TEXT(e_key_down);
      SET_ENUM_TEXT(e_key_left);
      SET_ENUM_TEXT(e_key_up);
      SET_ENUM_TEXT(e_key_prior);
      SET_ENUM_TEXT(e_key_next);
      SET_ENUM_TEXT(e_key_return);
      SET_ENUM_TEXT(e_key_home);
      SET_ENUM_TEXT(e_key_end);
      SET_ENUM_TEXT(e_key_tab);
      SET_ENUM_TEXT(e_key_capslock);
      SET_ENUM_TEXT(e_key_hyphen);
      SET_ENUM_TEXT(e_key_semicolon3);
      SET_ENUM_TEXT(e_key_slash2);
      SET_ENUM_TEXT(e_key_backslash2);
      SET_ENUM_TEXT(e_key_closebracket2);
      SET_ENUM_TEXT(e_key_openbracket2);
      SET_ENUM_TEXT(e_key_til2);
      SET_ENUM_TEXT(e_key_acute2);
      SET_ENUM_TEXT(e_key_equal);
      SET_ENUM_TEXT(e_key_escape);
      SET_ENUM_TEXT(e_key_apostrophe2);
      SET_ENUM_TEXT(e_key_numpad_0);
      SET_ENUM_TEXT(e_key_numpad_1);
      SET_ENUM_TEXT(e_key_numpad_2);
      SET_ENUM_TEXT(e_key_numpad_3);
      SET_ENUM_TEXT(e_key_numpad_4);
      SET_ENUM_TEXT(e_key_numpad_5);
      SET_ENUM_TEXT(e_key_numpad_6);
      SET_ENUM_TEXT(e_key_numpad_7);
      SET_ENUM_TEXT(e_key_numpad_8);
      SET_ENUM_TEXT(e_key_numpad_9);
      SET_ENUM_TEXT(e_key_print_screen);
      SET_ENUM_TEXT(e_key_f1);
      SET_ENUM_TEXT(e_key_f2);
      SET_ENUM_TEXT(e_key_f3);
      SET_ENUM_TEXT(e_key_f4);
      SET_ENUM_TEXT(e_key_f5);
      SET_ENUM_TEXT(e_key_f6);
      SET_ENUM_TEXT(e_key_f7);
      SET_ENUM_TEXT(e_key_f8);
      SET_ENUM_TEXT(e_key_f9);
      SET_ENUM_TEXT(e_key_f10);
      SET_ENUM_TEXT(e_key_f11);
      SET_ENUM_TEXT(e_key_f12);


      return ::success;

//      string strFile;
//
//#ifdef MACOS
//
//      strFile = pcontext->m_papexcontext->dir().matter("keyboard/windows/default.xml");
//
//#elif defined( LINUX)
//
//    return true;
//
//      strFile = pcontext->m_papexcontext->dir().matter("keyboard/linux/default.xml");
//
//#elif defined(__APPLE__)
//
//      strFile = pcontext->m_papexcontext->dir().matter("keyboard/macos/default.xml");
//
//#elif defined(ANDROID)
//
//      //strPath = pcontext->m_papexcontext->dir().matter("keyboard/android/default.xml");
//
//      strFile = pcontext->m_papexcontext->dir().matter("keyboard/windows/default.xml");
//
//#else
//
//#ifndef _UWP
//
//      WCHAR wsz[KL_NAMELENGTH];
//
//      ::u16 w;
//
//      if(GetKeyboardLayoutNameW(wsz))
//      {
//
//         if(wcslen(wsz) == 8)
//         {
//
//            index i = 0;
//
//            for(; i < 8; i++)
//            {
//               if(!::str::ch::is_digit(wsz[i]) && !(wsz[i] >= 'A' && wsz[i] <= 'F') && !(wsz[i] >= 'a' && wsz[i] <= 'f'))
//                  break;
//            }
//
//            if(i == 8)
//            {
//               string str(wstring(&wsz[4],4)); // least significant four digits
//
//               w = (::u16) ::hex::to_i64(str);
//
//            }
//
//         }
//         else
//         {
//
//            HKL hkl = GetKeyboardLayout(::GetCurrentThreadId());
//
//            w = HIWORD(hkl);
//
//            w &= 0x0fff;
//
//         }
//
//      }
//
//      string str = __str(w);
//
//      //strFile = pcontext->m_papexcontext->dir().matter("keyboard/windows/" + str + ".xml");
//
//      //if(pcontext->m_papexcontext->file().exists(strFile))
//      //{
//
//      //   if (load_os_layout(strFile))
//      //   {
//
//      //      return true;
//
//      //   }
//
//      //}
//
//#endif
//
//      strFile = pcontext->m_papexcontext->dir().matter("keyboard/windows/default.xml");
//
//#endif
//
//      if (!load_os_layout(strFile))
//      {
//
//         return false;
//
//      }
//
//      return estatus;

   }


   bool keyboard::load_os_layout(const ::file::path & pszPath)
   {

      //i32 iCode;

      //i32 iScan;

      //::user::enum_key ekey;

      //::type typeinfoKey = __type(::user::enum_key);

      auto pcontext = get_context();

      string str = pcontext->m_papexcontext->file().as_string(pszPath);


      output_debug_string(pszPath);

      output_debug_string(str);

      if(str.is_empty())
      {
         TRACE("unable to load os keyboard on_layout");
         //if(is_debugger_attached())
         //{

         //   message_box(nullptr,"keyboard default.xml is empty?!?!?!?!");

         //}
         return false;
      }

      __throw(todo, "xml");

      //::xml::document doc;

      //if(!doc.load(str))
      //{
      //   TRACE("unable to load os keyboard on_layout");
      //   //if(is_debugger_attached())
      //   //{

      //   //   message_box(nullptr,"keyboard default.xml syntax is incorrect?!?!?!?!");

      //   //}
      //   return false;
      //}

      //for(i32 i = 0; i < doc.root()->get_children_count(); i++)
      //{

      //   __pointer(::xml::node) pnode = doc.root()->child_at(i);

      //   if(pnode->get_name().compare_ci("item") == 0)
      //   {

      //      string strCode    = pnode->attribute("code");

      //      string strScan    = pnode->attribute("scan");

      //      string strExt    = pnode->attribute("ext");

      //      string strValue   = pnode->attribute("value");

      //      text_enum(ekey, strValue);

      //      if(strCode.has_char())
      //      {

      //         iCode    = atoi(strCode);

      //         m_mapKey.set_at(iCode,ekey);

      //      }

      //      if(strScan.has_char())
      //      {

      //         iScan    = atoi(strScan);

      //         if(strExt == "1")
      //         {

      //            m_mapExt.set_at(iScan,ekey);

      //         }
      //         else
      //         {

      //            m_mapScan.set_at(iScan,ekey);

      //         }

      //      }



      //   }

      //}

      //if((m_mapKey.get_count() + m_mapExt.get_count() + m_mapScan.get_count()) <= 0)
      //{

      //   if(is_debugger_attached())
      //   {

      //      message_box("keyboard default.xml has no keyboard entries?!?!?!?!");

      //   }

      //}

      return true;

   }


   //class keyboard_layout & keyboard::on_layout()
   //{
   //
   //   return *m_playout;

   //}


   //void keyboard::process_escape(__pointer(::xml::node) pnode, property_set & set)
   //{
   //   m_playout->process_escape(pnode, set);
   //}

//   bool keyboard::load_layout(const char * pszPath, const ::action_context & context)
//   {
//
//      auto playout = __new(::user::keyboard_layout);
//
//      string strPath;
//      if(pszPath == nullptr)
//      {
//         strPath = get_current_system_layout();
//      }
//      else
//      {
//         strPath = pszPath;
//      }
//      if(initialize(playout, strPath))
//      {
//         TRACE("setting keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//         if(playout->load(playout->m_strPath))
//         {
//            m_playout = playout;
//// xxx            papplication->simpledb().on_set_keyboard_layout(playout->m_strPath, context);
//            TRACE("successfully set keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//            return true;
//         }
//         else
//         {
//            playout->release();
//            TRACE("failed to load keyboard on_layout : %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//         }
//      }
//      else
//      {
//         TRACE("failed to set keyboard on_layout path=%s", pszPath);
//      }
//      return false;
//   }

   //string keyboard::process_key(key * pkey)
   //{

   //   //if(m_playout == nullptr)
   //   //{

   //   //   return string((char)(pkey->m_nChar & 0xff));

   //   //}

   //   pkey->m_iCode = (int)(pkey->m_ekey);

   //   if(psession->is_key_pressed(::user::e_key_shift))
   //   {
   //      pkey->m_iCode |= 0x80000000;
   //   }
   //   if(psession->is_key_pressed(::user::e_key_right_alt))
   //   {
   //      pkey->m_iCode |= 0x40000000;
   //   }



   //   //return m_playout->process_key(pkey);

   //}

   //string keyboard::process_key(::user::enum_key ekey)
   //{

   //   if(m_playout == nullptr)
   //   {

   //      return string((char) ekey);

   //   }

   //   int iCode = (int) (ekey);

   //   if(psession->is_key_pressed(::user::e_key_shift))
   //   {
   //      iCode |= 0x80000000;
   //   }
   //   if(psession->is_key_pressed(::user::e_key_right_alt))
   //   {
   //      iCode |= 0x40000000;
   //   }

   //   return m_playout->process_key(iCode);

   //}

   //string keyboard::process_char(const char * pszKey)
   //{
   //   if(m_playout == nullptr)
   //   {
   //      return pszKey;
   //   }
   //   return m_playout->process_char(pszKey);
   //}

   //string keyboard::process_escape(const char * pszEscape)
   //{
   //   if(m_playout == nullptr)
   //   {
   //      return pszEscape;
   //   }
   //   return m_playout->process_char(pszEscape);
   //}


//   string keyboard::get_current_system_layout()
//   {
//
//      keyboard_layout_ida layoutida;
//
//      ::file::patha patha;
//
//      pcontext->m_papexcontext->dir().matter_ls_file("keyboard layout", patha);
//
//      for(i32 i = 0; i < patha.get_count(); i++)
//      {
//
//         keyboard_layout_id layoutid;
//
//         ::file::path path = patha[i];
//
//         if(initialize(&layoutid, path))
//         {
//
//            layoutida.add(layoutid);
//
//         }
//
//      }
//
//      ::sort::quick_sort(layoutida, true);
//
//#ifdef WINDOWS_DESKTOP
//
//
//      string strOverride = file_as_string(pacmedir->system() / "config\\system\\keyboard_layout.txt");
//
//      if(strOverride.has_char())
//      {
//
//         string strTest;
//
//         string strPath = pcontext->m_papexcontext->dir().matter("keyboard layout/" + strOverride + ".xml");
//
//         strTest = pcontext->m_papexcontext->file().as_string(strPath);
//
//         if(strTest.has_char())
//         {
//
//            return strPath;
//
//         }
//
//      }
//
//      wchar_t szLayoutName[KL_NAMELENGTH];
//
//      ::GetKeyboardLayoutNameW(szLayoutName);
//
//      HKL hkl = ::GetKeyboardLayout(0);
//
//      for(i32 i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_hkla.contains(hkl))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//      hkl = (HKL) (((uptr) hkl) & 0xffff);
//      for(i32 i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_hkla.contains(hkl))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#elif defined(LINUX) || defined(SOLARIS)
//
//      string strSymbol = x11_keyboard_get_current_group_symbol();
//
//      for(i32 i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_countrycode.contains_ci(strSymbol))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#elif defined(MACOS)
//
//      string strSymbol = keyboard_input_source();
//
//      for(i32 i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_keylayout.has_char() && strSymbol.contains(layoutida[i].m_keylayout))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#else
//
//      {
//
//         string strPath = pcontext->m_papexcontext->dir().matter("keyboard layout/br_abnt2.xml");
//
//         if(pcontext->m_papexcontext->file().exists(strPath))
//         {
//
//            return strPath;
//
//         }
//
//         return strPath;
//
//      }
//
//#endif
//
//      string strPath = pcontext->m_papexcontext->dir().matter("keyboard layout/en_us_international.xml");
//
//      if(pcontext->m_papexcontext->file().exists(strPath))
//      {
//
//         return strPath;
//
//      }
//
//      return "";
//
//   }


//   bool keyboard::initialize(keyboard_layout_id * playoutid, const char * pszPath)
//   {
//
//      if(!pcontext->m_papexcontext->file().exists(pszPath))
//         return false;
//
//      string str = pcontext->m_papexcontext->file().as_string(pszPath);
//
//      if(str.is_empty())
//         return false;
//
//      __throw(todo("xml"));
//
////      ::xml::document doc;
////
////      if(!doc.load(str))
////         return false;
////
////      playoutid->m_strPath = pszPath;
////
////      playoutid->m_strName = doc.root()->attribute("name");
////
////      playoutid->m_countrycode = doc.root()->attribute("cc");
////
////      playoutid->m_keylayout = doc.root()->attribute("kl");
////
////      string_array straHkl;
////
////      straHkl.explode(";", doc.root()->attribute("hkla"));
////
////#ifdef WINDOWS_DESKTOP
////
////      for(i32 i = 0; i < straHkl.get_count(); i++)
////      {
////         string strHkl = straHkl[i];
////         HKL hkl;
////         strHkl.trim();
////         if(::str::begins_eat_ci(strHkl, "0x"))
////         {
////            hkl = (HKL) ::hex::to_uptr(strHkl);
////         }
////         else
////         {
////            hkl = (HKL) ansi_to_uptr(strHkl);
////         }
////         playoutid->m_hkla.add(hkl);
////      }
////
////#else
////
////      //__throw(todo);
////
////#endif
////
////      if(playoutid->m_strName.is_empty())
////         return false;
//
//      return true;
//
//   }


   ::e_status keyboard::show_software_keyboard(::user::primitive* pprimitive, string str, strsize iBeg, strsize iEnd)
   {

      synchronous_lock synchronouslock(mutex());

      m_iSoftwareKeyboardEventId++;

      index iEventId = m_iSoftwareKeyboardEventId;

      m_pprimitiveSoftwareKeyboard = pprimitive;

      fork([=,this]
         {

            sleep(400_ms);

            synchronous_lock synchronouslock(mutex());

            if (iEventId == m_iSoftwareKeyboardEventId)
            {

               ASSERT(pprimitive == m_pprimitiveSoftwareKeyboard);

               synchronouslock.unlock();

               m_pprimitiveSoftwareKeyboard->show_software_keyboard(pprimitive, str, iBeg, iEnd);

            }

         });

      return ::success;

   }


   ::e_status keyboard::hide_software_keyboard(::user::primitive * pprimitive)
   {

      if (!::is_null(pprimitive) && pprimitive != m_pprimitiveSoftwareKeyboard)
      {

         return error_invalid_argument;

      }

      synchronous_lock synchronouslock(mutex());

      m_iSoftwareKeyboardEventId++;

      index iEventId = m_iSoftwareKeyboardEventId;

      m_pprimitiveSoftwareKeyboard = nullptr;

      fork([this,iEventId,pprimitive]
         {

            sleep(400_ms);

            synchronous_lock synchronouslock(mutex());

            if (iEventId == m_iSoftwareKeyboardEventId)
            {

               synchronouslock.unlock();

               m_pprimitiveSoftwareKeyboard->hide_software_keyboard(pprimitive);

            }

         });

      return ::success;

   }



   void keyboard::translate_os_key_message(key * pkey)
   {

      if(pkey->m_ekey == ::user::e_key_refer_to_text_member
         && pkey->m_strText.has_char())
      {

         return;

      }

   #if defined(MACOS)

      auto ekey = ::user::vkcode_to_userkey(pkey->m_wparam);

      if(ekey != ::user::e_key_none)
      {

          pkey->m_ekey = ekey;

          return;

      }

   #elif !defined(LINUX)


   #else
//
//     auto ekey = keysym_to_userkey(pkey->m_lparam);
//
//     if(ekey != ::user::e_key_none)
//     {
//
//         pkey->m_ekey = ekey;
//
//         return;
//
//     }

   #endif


#if defined(WINDOWS_DESKTOP) || defined(MACOS)

      if(pkey->m_bExt)
      {

         pkey->m_ekey = m_mapExt[(i32)pkey->m_nScanCode];

         if(pkey->m_ekey != ::user::e_key_none)
            return;

      }

      pkey->m_ekey = m_mapScan[(i32)pkey->m_nScanCode];

      if(pkey->m_ekey != ::user::e_key_none)
         return;

#endif

      if(pkey->m_ekey == ::user::e_key_none)
      {

         pkey->m_ekey = m_mapKey[(i32) pkey->m_iVirtualKey];

      }

   }


} // namespace user


