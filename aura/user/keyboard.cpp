#include "framework.h"
#if !BROAD_PRECOMPILED_HEADER
#include "aura/user/_user.h"
#endif


#if defined(LINUX) || defined(SOLARIS)
//#include "base/base/os/x11/x11_keyboard.h"
string x11_keyboard_get_current_group_symbol();
#elif defined(MACOS)
string keyboard_input_source();
#endif



namespace user
{

#ifdef LINUX


   CLASS_DECL_AURA ::user::e_key keysym_to_userkey(const lparam & lparam);

#elif defined(MACOS)

   CLASS_DECL_AURA ::user::e_key vkcode_to_userkey(WPARAM wparam);

#endif

   keyboard::keyboard()
   {

      SET_ENUM_TEXT(key_0);
      SET_ENUM_TEXT(key_1);
      SET_ENUM_TEXT(key_2);
      SET_ENUM_TEXT(key_3);
      SET_ENUM_TEXT(key_4);
      SET_ENUM_TEXT(key_5);
      SET_ENUM_TEXT(key_6);
      SET_ENUM_TEXT(key_7);
      SET_ENUM_TEXT(key_8);
      SET_ENUM_TEXT(key_9);
      SET_ENUM_TEXT(key_a);
      SET_ENUM_TEXT(key_b);
      SET_ENUM_TEXT(key_c);
      SET_ENUM_TEXT(key_d);
      SET_ENUM_TEXT(key_e);
      SET_ENUM_TEXT(key_f);
      SET_ENUM_TEXT(key_g);
      SET_ENUM_TEXT(key_h);
      SET_ENUM_TEXT(key_i);
      SET_ENUM_TEXT(key_j);
      SET_ENUM_TEXT(key_k);
      SET_ENUM_TEXT(key_l);
      SET_ENUM_TEXT(key_m);
      SET_ENUM_TEXT(key_n);
      SET_ENUM_TEXT(key_o);
      SET_ENUM_TEXT(key_p);
      SET_ENUM_TEXT(key_q);
      SET_ENUM_TEXT(key_r);
      SET_ENUM_TEXT(key_s);
      SET_ENUM_TEXT(key_t);
      SET_ENUM_TEXT(key_u);
      SET_ENUM_TEXT(key_v);
      SET_ENUM_TEXT(key_w);
      SET_ENUM_TEXT(key_x);
      SET_ENUM_TEXT(key_y);
      SET_ENUM_TEXT(key_z);
      SET_ENUM_TEXT(key_semicolon);
      SET_ENUM_TEXT(key_semicolon2);
      SET_ENUM_TEXT(key_comma);
      SET_ENUM_TEXT(key_dot);
      SET_ENUM_TEXT(key_shift);
      SET_ENUM_TEXT(key_lshift);
      SET_ENUM_TEXT(key_rshift);
      SET_ENUM_TEXT(key_control);
      SET_ENUM_TEXT(key_lcontrol);
      SET_ENUM_TEXT(key_rcontrol);
      SET_ENUM_TEXT(key_alt);
      SET_ENUM_TEXT(key_lalt);
      SET_ENUM_TEXT(key_ralt);
      SET_ENUM_TEXT(key_command);
      SET_ENUM_TEXT(key_lcommand);
      SET_ENUM_TEXT(key_rcommand);
      SET_ENUM_TEXT(key_lbutton);
      SET_ENUM_TEXT(key_mbutton);
      SET_ENUM_TEXT(key_rbutton);
      SET_ENUM_TEXT(key_back);
      SET_ENUM_TEXT(key_delete);
      SET_ENUM_TEXT(key_space);
      SET_ENUM_TEXT(key_right);
      SET_ENUM_TEXT(key_down);
      SET_ENUM_TEXT(key_left);
      SET_ENUM_TEXT(key_up);
      SET_ENUM_TEXT(key_prior);
      SET_ENUM_TEXT(key_next);
      SET_ENUM_TEXT(key_return);
      SET_ENUM_TEXT(key_home);
      SET_ENUM_TEXT(key_end);
      SET_ENUM_TEXT(key_tab);
      SET_ENUM_TEXT(key_capslock);
      SET_ENUM_TEXT(key_hyphen);
      SET_ENUM_TEXT(key_semicolon3);
      SET_ENUM_TEXT(key_slash2);
      SET_ENUM_TEXT(key_backslash2);
      SET_ENUM_TEXT(key_closebracket2);
      SET_ENUM_TEXT(key_openbracket2);
      SET_ENUM_TEXT(key_til2);
      SET_ENUM_TEXT(key_acute2);
      SET_ENUM_TEXT(key_equal);
      SET_ENUM_TEXT(key_escape);
      SET_ENUM_TEXT(key_apostrophe2);
      SET_ENUM_TEXT(key_numpad_0);
      SET_ENUM_TEXT(key_numpad_1);
      SET_ENUM_TEXT(key_numpad_2);
      SET_ENUM_TEXT(key_numpad_3);
      SET_ENUM_TEXT(key_numpad_4);
      SET_ENUM_TEXT(key_numpad_5);
      SET_ENUM_TEXT(key_numpad_6);
      SET_ENUM_TEXT(key_numpad_7);
      SET_ENUM_TEXT(key_numpad_8);
      SET_ENUM_TEXT(key_numpad_9);
      SET_ENUM_TEXT(key_print_screen);
      SET_ENUM_TEXT(key_f1);
      SET_ENUM_TEXT(key_f2);
      SET_ENUM_TEXT(key_f3);
      SET_ENUM_TEXT(key_f4);
      SET_ENUM_TEXT(key_f5);
      SET_ENUM_TEXT(key_f6);
      SET_ENUM_TEXT(key_f7);
      SET_ENUM_TEXT(key_f8);
      SET_ENUM_TEXT(key_f9);
      SET_ENUM_TEXT(key_f10);
      SET_ENUM_TEXT(key_f11);
      SET_ENUM_TEXT(key_f12);

#ifdef WINDOWS
      for (char ch = 'A'; ch <= 'Z'; ch++)
      {
         m_mapKey[ch] = (::user::e_key) (key_a + (ch - 'A'));
      }
      for (char ch = '0'; ch <= '9'; ch++)
      {
         m_mapKey[ch] = (::user::e_key) (key_0 + (ch - '0'));
      }
      m_mapKey[VK_LEFT] = key_left;
      m_mapKey[VK_RIGHT] = key_right;
      m_mapKey[VK_UP] = key_up;
      m_mapKey[VK_DOWN] = key_down;
      m_mapKey[VK_DELETE] = key_delete;
      m_mapKey[VK_BACK] = key_back;
      m_mapKey[VK_RETURN] = key_return;
      m_mapKey[VK_SPACE] = key_space;
      m_mapKey[VK_HOME] = key_home;
      m_mapKey[VK_END] = key_end;
      m_mapKey[VK_PRIOR] = key_prior;
      m_mapKey[VK_NEXT] = key_next;
      m_mapKey[VK_TAB] = key_tab;
      m_mapKey[VK_ESCAPE] = key_escape;
      m_mapKey[VK_TAB] = key_tab;
      m_mapKey[VK_F1] = key_f1;
      m_mapKey[VK_F2] = key_f2;
      m_mapKey[VK_F3] = key_f3;
      m_mapKey[VK_F4] = key_f4;
      m_mapKey[VK_F5] = key_f5;
      m_mapKey[VK_F6] = key_f6;
      m_mapKey[VK_F7] = key_f7;
      m_mapKey[VK_F8] = key_f8;
      m_mapKey[VK_F9] = key_f9;
      m_mapKey[VK_F10] = key_f10;
      m_mapKey[VK_F11] = key_f11;
      m_mapKey[VK_F12] = key_f12;
      m_mapKey[VK_LSHIFT] = key_lshift;
      m_mapKey[VK_RSHIFT] = key_rshift;
      m_mapKey[VK_LCONTROL] = key_lcontrol;
      m_mapKey[VK_RCONTROL] = key_rcontrol;
      m_mapKey[VK_LMENU] = key_lalt;
      m_mapKey[VK_RMENU] = key_ralt;
#endif

   }


   keyboard::~keyboard()
   {

   }


   ::e_status keyboard::initialize(::layered * pobjectContext)
   {

      auto estatus = ::object::initialize(pobjectContext);

      if (!estatus)
      {

         return estatus;

      }

      return ::success;

//      string strFile;
//
//#ifdef MACOS
//
//      strFile = Context.dir().matter("keyboard/windows/default.xml");
//
//#elif defined( LINUX)
//
//    return true;
//
//      strFile = Context.dir().matter("keyboard/linux/default.xml");
//
//#elif defined(__APPLE__)
//
//      strFile = Context.dir().matter("keyboard/macos/default.xml");
//
//#elif defined(ANDROID)
//
//      //strPath = Context.dir().matter("keyboard/android/default.xml");
//
//      strFile = Context.dir().matter("keyboard/windows/default.xml");
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
//      //strFile = Context.dir().matter("keyboard/windows/" + str + ".xml");
//
//      //if(Context.file().exists(strFile))
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
//      strFile = Context.dir().matter("keyboard/windows/default.xml");
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

      //::user::e_key ekey;

      //::type typeinfoKey = __type(::user::e_key);

      string str = Context.file().as_string(pszPath);


      output_debug_string(pszPath);

      output_debug_string(str);

      if(str.is_empty())
      {
         TRACE("unable to load os keyboard on_layout");
         //if(is_debugger_attached())
         //{

         //   Application.message_box(nullptr,"keyboard default.xml is empty?!?!?!?!");

         //}
         return false;
      }

      __throw(todo("xml"));

      //::xml::document doc;

      //if(!doc.load(str))
      //{
      //   TRACE("unable to load os keyboard on_layout");
      //   //if(is_debugger_attached())
      //   //{

      //   //   Application.message_box(nullptr,"keyboard default.xml syntax is incorrect?!?!?!?!");

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

      //      Application.message_box("keyboard default.xml has no keyboard entries?!?!?!?!");

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
//// xxx            Application.simpledb().on_set_keyboard_layout(playout->m_strPath, context);
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

   //   if(psession->is_key_pressed(::user::key_shift))
   //   {
   //      pkey->m_iCode |= 0x80000000;
   //   }
   //   if(psession->is_key_pressed(::user::key_ralt))
   //   {
   //      pkey->m_iCode |= 0x40000000;
   //   }



   //   //return m_playout->process_key(pkey);

   //}

   //string keyboard::process_key(::user::e_key ekey)
   //{

   //   if(m_playout == nullptr)
   //   {

   //      return string((char) ekey);

   //   }

   //   int iCode = (int) (ekey);

   //   if(psession->is_key_pressed(::user::key_shift))
   //   {
   //      iCode |= 0x80000000;
   //   }
   //   if(psession->is_key_pressed(::user::key_ralt))
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
//      Context.dir().matter_ls_file("keyboard layout", patha);
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
//      string strOverride = file_as_string(::dir::system() / "config\\system\\keyboard_layout.txt");
//
//      if(strOverride.has_char())
//      {
//
//         string strTest;
//
//         string strPath = Context.dir().matter("keyboard layout/" + strOverride + ".xml");
//
//         strTest = Context.file().as_string(strPath);
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
//         string strPath = Context.dir().matter("keyboard layout/br_abnt2.xml");
//
//         if(Context.file().exists(strPath))
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
//      string strPath = Context.dir().matter("keyboard layout/en_us_international.xml");
//
//      if(Context.file().exists(strPath))
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
//      if(!Context.file().exists(pszPath))
//         return false;
//
//      string str = Context.file().as_string(pszPath);
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
////      //__throw(todo());
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

      sync_lock sl(mutex());

      m_iSoftwareKeyboardEventId++;

      index iEventId = m_iSoftwareKeyboardEventId;

      m_pprimitiveSoftwareKeyboard = pprimitive;

      fork([=]
         {

            sleep(400_ms);

            sync_lock sl(mutex());

            if (iEventId == m_iSoftwareKeyboardEventId)
            {

               ASSERT(pprimitive == m_pprimitiveSoftwareKeyboard);

               sl.unlock();

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

      sync_lock sl(mutex());

      m_iSoftwareKeyboardEventId++;

      index iEventId = m_iSoftwareKeyboardEventId;

      m_pprimitiveSoftwareKeyboard = nullptr;

      fork([=]
         {

            sleep(400_ms);

            sync_lock sl(mutex());

            if (iEventId == m_iSoftwareKeyboardEventId)
            {

               sl.unlock();

               m_pprimitiveSoftwareKeyboard->hide_software_keyboard(pprimitive);

            }

         });

      return ::success;

   }




   void keyboard::translate_os_key_message(key * pkey)
   {

      if(pkey->m_ekey == ::user::key_refer_to_text_member
         && pkey->m_strText.has_char())
      {

         return;

      }

   #if defined(MACOS)

      auto ekey = ::user::vkcode_to_userkey(pkey->m_wparam);

      if(ekey != ::user::key_none)
      {

          pkey->m_ekey = ekey;

          return;

      }

   #elif !defined(LINUX)


   #else

     auto ekey = keysym_to_userkey(pkey->m_lparam);

     if(ekey != ::user::key_none)
     {

         pkey->m_ekey = ekey;

         return;

     }

   #endif


#if defined(WINDOWS_DESKTOP) || defined(MACOS)

      if(pkey->m_bExt)
      {

         pkey->m_ekey = m_mapExt[(i32)pkey->m_nScanCode];

         if(pkey->m_ekey != ::user::key_none)
            return;

      }

      pkey->m_ekey = m_mapScan[(i32)pkey->m_nScanCode];

      if(pkey->m_ekey != ::user::key_none)
         return;

#endif

      if(pkey->m_ekey == ::user::key_none)
      {

         pkey->m_ekey = m_mapKey[(i32) pkey->m_iVirtualKey];

      }

   }


} // namespace user


