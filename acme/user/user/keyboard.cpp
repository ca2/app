// Created by camilo on 2023-05-19 07:30 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "keyboard.h"


namespace keyboard
{


   struct user_key_text
   {

      ::user::e_key        m_ekey;
      const char* m_psz;

   };


   static user_key_text s_userkeytextaModifiers[] =
   {


      {::user::e_key_control, "CONTROL+"},
      {::user::e_key_alt, "ALT+"},
      {::user::e_key_shift, "SHIFT+"},
      {::user::e_key_command, "COMMAND+"},


      {::user::e_key_none, nullptr}


   };


   struct user_key_user_key
   {

      ::user::e_key        m_ekey1;
      ::user::e_key        m_ekey2;

   };


   static user_key_user_key s_userkeyuserkeyModifiersGroups[] =
   {


      {::user::e_key_left_shift     , ::user::e_key_shift},
      {::user::e_key_right_shift    , ::user::e_key_shift},
      {::user::e_key_left_control   , ::user::e_key_control},
      {::user::e_key_right_control  , ::user::e_key_control},
      {::user::e_key_left_alt       , ::user::e_key_alt},
      {::user::e_key_right_alt      , ::user::e_key_alt},
      {::user::e_key_left_command   , ::user::e_key_control},
      {::user::e_key_right_control  , ::user::e_key_control},


      {::user::e_key_none           , ::user::e_key_none}


   };



   ::string key_string(::user::e_key ekey)
   {

      ::string res;

      //https://www.glfw.org/docs/latest/group__keys.html

      if (ekey.m_eenum >= ::user::e_key_f1 && ekey.m_eenum <= ::user::e_key_f24)
      {

         res.format("F%d", ekey.m_eenum - ::user::e_key_f1 + 1);

      }
      else if (ekey == ::user::e_key_space)
      {

         return " ";

      }
      else if (ekey >= ::user::e_key_0 && ekey <= ::user::e_key_9)
      {

         res.format("%c", ekey.m_eenum - ::user::e_key_0 + '0');

      }
      else if (ekey >= ::user::e_key_a && ekey <= ::user::e_key_z)
      {

         res.format("%c", ekey.m_eenum - ::user::e_key_a + 'A');

      }
      else if (ekey == ::user::e_key_plus_oem)
      {

         return "+";

      }
      else if (ekey == ::user::e_key_minus_oem)
      {

         return "-";

      }

      return res;

   }


   ::string key_string_with_no_modifier(::user::e_key ekey)
   {

      auto ekeyWithNoModifier = key_with_no_modifier(ekey);

      ::string strKeyWithNoModifier;

      //https://www.glfw.org/docs/latest/group__keys.html

      if (ekey.m_eenum >= ::user::e_key_f1 && ekey.m_eenum <= ::user::e_key_f24)
      {

         strKeyWithNoModifier.format("F%d", ekey.m_eenum - ::user::e_key_f1 + 1);

      }
      else if (ekey == ::user::e_key_space)
      {

         strKeyWithNoModifier = " ";

      }
      else if (ekey >= ::user::e_key_0 && ekey <= ::user::e_key_9)
      {

         strKeyWithNoModifier.format("%c", ekey.m_eenum - ::user::e_key_0 + '0');

      }
      else if (ekey >= ::user::e_key_a && ekey <= ::user::e_key_z)
      {

         strKeyWithNoModifier.format("%c", ekey.m_eenum - ::user::e_key_a + 'A');

      }
      else if (ekey == ::user::e_key_plus_oem)
      {

         strKeyWithNoModifier = "+";

      }
      else if (ekey == ::user::e_key_minus_oem)
      {

         strKeyWithNoModifier = "-";

      }

      return strKeyWithNoModifier;

   }


   ::string modifiers_groups_string(::user::e_key ekey)
   {

      ::string strModifiersGroups;

      auto puserkeytextModifiers = (user_key_text*)s_userkeytextaModifiers;

      while (puserkeytextModifiers->m_ekey)
      {

         if (ekey & puserkeytextModifiers->m_ekey)
         {

            strModifiersGroups += puserkeytextModifiers->m_psz;

         }

         puserkeytextModifiers++;

      }

      return strModifiersGroups;

   }


   CLASS_DECL_ACME::string key_string_with_modifiers_groups(::user::e_key ekey)
   {

      auto strModifiersGroups = modifiers_groups_string(ekey);

      auto strKeyWithNoModifier = key_string_with_no_modifier(ekey);

      return strModifiersGroups + strKeyWithNoModifier;

   }


   ::user::e_key string_key_modifiers_groups(::string& strWillKeyWithNoModifiers)
   {

      ::user::e_key ekeyModifiers = ::user::e_key_none;

      auto puserkeytextModifiers = (user_key_text*)s_userkeytextaModifiers;

      while (puserkeytextModifiers->m_ekey != ::user::e_key_none)
      {

         if (strWillKeyWithNoModifiers.contains_erase(puserkeytextModifiers->m_psz))
         {

            ekeyModifiers |= puserkeytextModifiers->m_ekey;

         }

         puserkeytextModifiers++;

      }

      return ekeyModifiers;

   }


   ::user::e_key string_key(const ::scoped_string& scopedstrWithNoModifiers, ::user::e_key ekeyModifiers)
   {

      auto ekeyWithNoModifiers = string_key_with_no_modifier(scopedstrWithNoModifiers);

      return ekeyWithNoModifiers | ekeyModifiers;

   }


   ::user::e_key string_key(const ::scoped_string& scopedstr)
   {

      ::string strWillKeyWithNoModifiers(scopedstr);

      auto ekeyModifiers = string_key_modifiers_groups(strWillKeyWithNoModifiers);

      auto ekeyWithNoModifiers = string_key_with_no_modifier(strWillKeyWithNoModifiers);

      return ekeyWithNoModifiers | ekeyModifiers;

   }


   ::user::e_key string_key_with_no_modifier(const ::scoped_string& scopedstrKeyWithNoModifier)
   {

      ::string strKeyWithNoModifier(scopedstrKeyWithNoModifier);

      //https://www.glfw.org/docs/latest/group__keys.html

      if (strKeyWithNoModifier.begins_eat("F"))
      {

         int iF = atoi(strKeyWithNoModifier);

         if (iF < 1 || iF > 24)
         {

            return ::user::e_key_none;

         }

         return (::user::enum_key) (::user::e_key_f1 + (iF - 1));

      }
      else if (strKeyWithNoModifier == " ")
      {

         return ::user::e_key_space;

      }
      else if (strKeyWithNoModifier.length() == 1)
      {

         auto ch = strKeyWithNoModifier[0];

         if (ch >= '0' && ch <= '9')
         {

            return (::user::enum_key)(::user::e_key_0 + (ch - '0'));

         }
         else if (ch >= 'a' && ch <= 'z')
         {

            return (::user::enum_key)(::user::e_key_a + (ch - 'a'));

         }
         else if (ch >= 'A' && ch <= 'Z')
         {

            return (::user::enum_key)(::user::e_key_a + (ch - 'A'));

         }
         else if (ch == '+')
         {

            return ::user::e_key_plus;

         }
         else if (ch == '-')
         {

            return ::user::e_key_minus;

         }

      }

      return ::user::e_key_none;

   }


   bool is_equivalent_using_modifiers_groups(::user::e_key ekey1, ::user::e_key ekey2)
   {

      auto ekeyWithNoModifier1 = key_with_no_modifier(ekey1);

      auto ekeyWithNoModifier2 = key_with_no_modifier(ekey2);

      if (ekeyWithNoModifier1 != ekeyWithNoModifier2)
      {

         return false;

      }

      auto ekeyModifiersGroups1 = modifiers_groups(ekey1);

      auto ekeyModifiersGroups2 = modifiers_groups(ekey2);

      if (ekeyModifiersGroups1 != ekeyModifiersGroups2)
      {

         return false;

      }

      return true;

   }


   ::user::e_key modifiers_groups(::user::e_key ekey)
   {

      ::user::e_key ekeyModifiers = ::user::e_key_none;

      auto puserkeyuserkeyModifiersGroups = (user_key_user_key*)s_userkeyuserkeyModifiersGroups;

      while (puserkeyuserkeyModifiersGroups->m_ekey1 != ::user::e_key_none)
      {

         if (ekey & puserkeyuserkeyModifiersGroups->m_ekey1)
         {

            ekeyModifiers |= puserkeyuserkeyModifiersGroups->m_ekey2;

         }

         puserkeyuserkeyModifiersGroups++;

      }

      return ekeyModifiers;

   }


   CLASS_DECL_ACME::user::e_key key_with_no_modifier(::user::e_key ekey)
   {

      return ekey & ::user::e_key_with_no_modifier_mask;

   }


} // namespace shortcut







