#include "framework.h"
#include "user.h"
//#include "key.h"
#include "interaction.h"
#include "acme/constant/user_key.h"
#include "acme/parallelization/synchronous_lock.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "acme/user/user/key.h"
#include "aura/windowing/windowing.h"
#include "aura/windowing/keyboard.h"
#include "aura/platform/system.h"
#include "aura/platform/session.h"


//#if defined(LINUX) || defined(SOLARIS)
////#include "base/base/os/x11/x11_keyboard.h"
//string x11_keyboard_get_current_group_symbol();
//#elif defined(MACOS)
//string keyboard_input_source();
//#endif



namespace user
{

#ifdef LINUX


   //CLASS_DECL_AURA ::user::enum_key keysym_to_userkey(const lparam & lparam);

#elif defined(MACOS)

   CLASS_DECL_AURA ::user::enum_key vkcode_to_userkey(wparam wparam);

#endif

   keyboard::keyboard()
   {

      defer_create_synchronization();

   }


   keyboard::~keyboard()
   {

   }


   void keyboard::initialize(::particle * pparticle)
   {

      // auto estatus =
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

      auto psystem = system();

//      SET_ENUM_TEXT(e_key_0);
//      SET_ENUM_TEXT(e_key_1);
//      SET_ENUM_TEXT(e_key_2);
//      SET_ENUM_TEXT(e_key_3);
//      SET_ENUM_TEXT(e_key_4);
//      SET_ENUM_TEXT(e_key_5);
//      SET_ENUM_TEXT(e_key_6);
//      SET_ENUM_TEXT(e_key_7);
//      SET_ENUM_TEXT(e_key_8);
//      SET_ENUM_TEXT(e_key_9);
//      SET_ENUM_TEXT(e_key_a);
//      SET_ENUM_TEXT(e_key_b);
//      SET_ENUM_TEXT(e_key_c);
//      SET_ENUM_TEXT(e_key_d);
//      SET_ENUM_TEXT(e_key_e);
//      SET_ENUM_TEXT(e_key_f);
//      SET_ENUM_TEXT(e_key_g);
//      SET_ENUM_TEXT(e_key_h);
//      SET_ENUM_TEXT(e_key_i);
//      SET_ENUM_TEXT(e_key_j);
//      SET_ENUM_TEXT(e_key_k);
//      SET_ENUM_TEXT(e_key_l);
//      SET_ENUM_TEXT(e_key_m);
//      SET_ENUM_TEXT(e_key_n);
//      SET_ENUM_TEXT(e_key_o);
//      SET_ENUM_TEXT(e_key_p);
//      SET_ENUM_TEXT(e_key_q);
//      SET_ENUM_TEXT(e_key_r);
//      SET_ENUM_TEXT(e_key_s);
//      SET_ENUM_TEXT(e_key_t);
//      SET_ENUM_TEXT(e_key_u);
//      SET_ENUM_TEXT(e_key_v);
//      SET_ENUM_TEXT(e_key_w);
//      SET_ENUM_TEXT(e_key_x);
//      SET_ENUM_TEXT(e_key_y);
//      SET_ENUM_TEXT(e_key_z);
//      SET_ENUM_TEXT(e_key_semicolon);
//      SET_ENUM_TEXT(e_key_semicolon2);
//      SET_ENUM_TEXT(e_key_comma);
//      SET_ENUM_TEXT(e_key_dot);
//      SET_ENUM_TEXT(e_key_shift);
//      SET_ENUM_TEXT(e_key_left_shift);
//      SET_ENUM_TEXT(e_key_right_shift);
//      SET_ENUM_TEXT(e_key_control);
//      SET_ENUM_TEXT(e_key_left_control);
//      SET_ENUM_TEXT(e_key_right_control);
//      SET_ENUM_TEXT(e_key_alt);
//      SET_ENUM_TEXT(e_key_left_alt);
//      SET_ENUM_TEXT(e_key_right_alt);
//      SET_ENUM_TEXT(e_key_command);
//      SET_ENUM_TEXT(e_key_left_command);
//      SET_ENUM_TEXT(e_key_right_command);
//      SET_ENUM_TEXT(e_key_left_button);
//      SET_ENUM_TEXT(e_key_middle_button);
//      SET_ENUM_TEXT(e_key_right_button);
//      SET_ENUM_TEXT(e_key_back);
//      SET_ENUM_TEXT(e_key_delete);
//      SET_ENUM_TEXT(e_key_space);
//      SET_ENUM_TEXT(e_key_right);
//      SET_ENUM_TEXT(e_key_down);
//      SET_ENUM_TEXT(e_key_left);
//      SET_ENUM_TEXT(e_key_up);
//      SET_ENUM_TEXT(e_key_prior);
//      SET_ENUM_TEXT(e_key_next);
//      SET_ENUM_TEXT(e_key_return);
//      SET_ENUM_TEXT(e_key_home);
//      SET_ENUM_TEXT(e_key_end);
//      SET_ENUM_TEXT(e_key_tab);
//      SET_ENUM_TEXT(e_key_capslock);
//      SET_ENUM_TEXT(e_key_hyphen);
//      SET_ENUM_TEXT(e_key_semicolon3);
//      SET_ENUM_TEXT(e_key_slash2);
//      SET_ENUM_TEXT(e_key_backslash2);
//      SET_ENUM_TEXT(e_key_closebracket2);
//      SET_ENUM_TEXT(e_key_openbracket2);
//      SET_ENUM_TEXT(e_key_til2);
//      SET_ENUM_TEXT(e_key_acute2);
//      SET_ENUM_TEXT(e_key_equal);
//      SET_ENUM_TEXT(e_key_escape);
//      SET_ENUM_TEXT(e_key_apostrophe2);
//      SET_ENUM_TEXT(e_key_numpad_0);
//      SET_ENUM_TEXT(e_key_numpad_1);
//      SET_ENUM_TEXT(e_key_numpad_2);
//      SET_ENUM_TEXT(e_key_numpad_3);
//      SET_ENUM_TEXT(e_key_numpad_4);
//      SET_ENUM_TEXT(e_key_numpad_5);
//      SET_ENUM_TEXT(e_key_numpad_6);
//      SET_ENUM_TEXT(e_key_numpad_7);
//      SET_ENUM_TEXT(e_key_numpad_8);
//      SET_ENUM_TEXT(e_key_numpad_9);
//      SET_ENUM_TEXT(e_key_print_screen);
//      SET_ENUM_TEXT(e_key_f1);
//      SET_ENUM_TEXT(e_key_f2);
//      SET_ENUM_TEXT(e_key_f3);
//      SET_ENUM_TEXT(e_key_f4);
//      SET_ENUM_TEXT(e_key_f5);
//      SET_ENUM_TEXT(e_key_f6);
//      SET_ENUM_TEXT(e_key_f7);
//      SET_ENUM_TEXT(e_key_f8);
//      SET_ENUM_TEXT(e_key_f9);
//      SET_ENUM_TEXT(e_key_f10);
//      SET_ENUM_TEXT(e_key_f11);
//      SET_ENUM_TEXT(e_key_f12);

      //return ::success;

//      string strFile;
//
//#ifdef MACOS
//
//      strFile = directory()->matter("keyboard/windows/default.xml");
//
//#elif defined( LINUX)
//
//    return true;
//
//      strFile = directory()->matter("keyboard/linux/default.xml");
//
//#elif defined(__APPLE__)
//
//      strFile = directory()->matter("keyboard/macos/default.xml");
//
//#elif defined(__ANDROID__)
//
//      //strPath = directory()->matter("keyboard/android/default.xml");
//
//      strFile = directory()->matter("keyboard/windows/default.xml");
//
//#else
//
//#ifndef UNIVERSAL_WINDOWS
//
//      WCHAR wsz[KL_NAMELENGTH];
//
//      unsigned short w;
//
//      if(GetKeyboardLayoutNameW(wsz))
//      {
//
//         if(wcslen(wsz) == 8)
//         {
//
//            ::collection::index i = 0;
//
//            for(; i < 8; i++)
//            {
//               if(!unicode_is_digit(wsz[i]) && !(wsz[i] >= 'A' && wsz[i] <= 'F') && !(wsz[i] >= 'a' && wsz[i] <= 'f'))
//                  break;
//            }
//
//            if(i == 8)
//            {
//               string str(wstring(&wsz[4],4)); // least significant four digits
//
//               w = (unsigned short) ::hex::to_long_long(str);
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
//      string str = as_string(w);
//
//      //strFile = directory()->matter("keyboard/windows/" + str + ".xml");
//
//      //if(file()->exists(strFile))
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
//      strFile = directory()->matter("keyboard/windows/default.xml");
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


   ::user::enum_key keyboard::wparam_to_userkey(wparam wparam)
   {
      
      auto pwindowing = system()->windowing();
      
      auto pkeyboard = pwindowing->keyboard();
      
      return pkeyboard->wparam_to_userkey(wparam);
      
      
   }


   bool keyboard::load_os_layout(const ::file::path & path)
   {

      synchronous_lock synchronouslock(this->synchronization());

      //int iCode;

      //int iScan;

      //::user::enum_key ekey;

      //::type typeinfoKey = ::type < ::user::enum_key >();

      // auto pcontext = get_context();

      string str = file()->as_string(path);


      informationf(path);

      informationf(str);

      if(str.is_empty())
      {

         information() << "unable to load os keyboard on_layout";
         
         //if(is_debugger_attached())
         //{

         //   message_box(nullptr,"keyboard default.xml is empty?!?!?!?!");

         //}
         return false;
      }

      throw ::exception(todo, "xml");

      //::xml::document doc;

      //if(!doc.load(str))
      //{
      //   informationf("unable to load os keyboard on_layout");
      //   //if(is_debugger_attached())
      //   //{

      //   //   message_box(nullptr,"keyboard default.xml syntax is incorrect?!?!?!?!");

      //   //}
      //   return false;
      //}

      //for(int i = 0; i < doc.root()->get_children_count(); i++)
      //{

      //   ::pointer<::xml::node>pnode = doc.root()->child_at(i);

      //   if(pnode->get_name().case_insensitive_order("item") == 0)
      //   {

      //      string strCode    = pnode->attribute("code");

      //      string strScan    = pnode->attribute("scan");

      //      string strExt    = pnode->attribute("ext");

      //      string strValue   = pnode->attribute("value");

      //      text_enum(ekey, strValue);

      //      if(strCode.has_character())
      //      {

      //         iCode    = atoi(strCode);

      //         m_mapKey.set_at(iCode,ekey);

      //      }

      //      if(strScan.has_character())
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

      //      output_error_message("keyboard default.xml has no keyboard entries?!?!?!?!");

      //   }

      //}

      return true;

   }


   //class keyboard_layout & keyboard::on_layout()
   //{
   //
   //   return *m_playout;

   //}


   //void keyboard::process_escape(::pointer<::xml::node>pnode, ::property_set & set)
   //{
   //   m_playout->process_escape(pnode, set);
   //}

//   bool keyboard::load_layout(const ::scoped_string & scopedstrPath, const ::action_context & context)
//   {
//
//      auto playout = __allocate ::user::keyboard_layout();
//
//      string strPath;
//      if(scopedstrPath == nullptr)
//      {
//         strPath = get_current_system_layout();
//      }
//      else
//      {
//         strPath = pszPath;
//      }
//      if(initialize(playout, strPath))
//      {
//         informationf("setting keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//         if(playout->load(playout->m_strPath))
//         {
//            m_playout = playout;
//// xxx            papp->simpledb().on_set_keyboard_layout(playout->m_strPath, context);
//            informationf("successfully set keyboard on_layout to %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//            return true;
//         }
//         else
//         {
//            playout->release();
//            informationf("failed to load keyboard on_layout : %s (path=%s)", playout->m_strName.c_str(), playout->m_strPath.c_str());
//         }
//      }
//      else
//      {
//         informationf("failed to set keyboard on_layout path=%s", pszPath);
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
   //      pkey->m_iCode |= I32_MINIMUM;
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
   //      iCode |= I32_MINIMUM;
   //   }
   //   if(psession->is_key_pressed(::user::e_key_right_alt))
   //   {
   //      iCode |= 0x40000000;
   //   }

   //   return m_playout->process_key(iCode);

   //}

   //string keyboard::process_char(const ::scoped_string & scopedstrKey)
   //{
   //   if(m_playout == nullptr)
   //   {
   //      return pszKey;
   //   }
   //   return m_playout->process_char(scopedstrKey);
   //}

   //string keyboard::process_escape(const ::scoped_string & scopedstrEscape)
   //{
   //   if(m_playout == nullptr)
   //   {
   //      return pszEscape;
   //   }
   //   return m_playout->process_char(scopedstrEscape);
   //}


//   string keyboard::get_current_system_layout()
//   {
//
//      keyboard_layout_ida layoutida;
//
//      ::file::path_array patha;
//
//      directory()->matter_ls_file("keyboard layout", patha);
//
//      for(int i = 0; i < patha.get_count(); i++)
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
//      string strOverride = file_system()->as_string(         auto psystem = system();

//         auto pdirectorysystem = psystem->m_pdirectorysystem;
//
//pdirectorysystem->system() / "config\\system\\keyboard_layout.txt");
//
//      if(strOverride.has_character())
//      {
//
//         string strTest;
//
//         string strPath = directory()->matter("keyboard layout/" + strOverride + ".xml");
//
//         strTest = file()->as_string(strPath);
//
//         if(strTest.has_character())
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
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_hkla.contains(hkl))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//      hkl = (HKL) (((uptr) hkl) & 0xffff);
//      for(int i = 0; i < layoutida.get_count(); i++)
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
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_countrycode.case_insensitive_contains(strSymbol))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#elif defined(MACOS)
//
//      string strSymbol = keyboard_input_source();
//
//      for(int i = 0; i < layoutida.get_count(); i++)
//      {
//         if(layoutida[i].m_keylayout.has_character() && strSymbol.contains(layoutida[i].m_keylayout))
//         {
//            return layoutida[i].m_strPath;
//         }
//      }
//
//#else
//
//      {
//
//         string strPath = directory()->matter("keyboard layout/br_abnt2.xml");
//
//         if(file()->exists(strPath))
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
//      string strPath = directory()->matter("keyboard layout/en_us_international.xml");
//
//      if(file()->exists(strPath))
//      {
//
//         return strPath;
//
//      }
//
//      return "";
//
//   }


//   bool keyboard::initialize(keyboard_layout_id * playoutid, const ::scoped_string & scopedstrPath)
//   {
//
//      if(!file()->exists(scopedstrPath))
//         return false;
//
//      string str = file()->as_string(scopedstrPath);
//
//      if(str.is_empty())
//         return false;
//
//      throw ::exception(todo("xml"));
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
////      for(int i = 0; i < straHkl.get_count(); i++)
////      {
////         string strHkl = straHkl[i];
////         HKL hkl;
////         strHkl.trim();
////         if(strHkl.case_insensitive_begins_eat("0x"))
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
////      //throw ::exception(todo);
////
////#endif
////
////      if(playoutid->m_strName.is_empty())
////         return false;
//
//      return true;
//
//   }



   void keyboard::translate_os_key_message(key * pkey)
   {

      synchronous_lock synchronouslock(this->synchronization());

      if(pkey->m_ekey == ::user::e_key_refer_to_text_member
         && pkey->m_strText.has_character())
      {

         return;

      }


   }


} // namespace user


