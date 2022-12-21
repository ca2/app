#include "framework.h"


char char_to_upper(int32_t ch);


int_bool MessageBoxAForConsole(oswindow interaction_impl, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, ::u32 uFlags);


//int_bool (* g_messageboxa)(oswindow interaction_impl, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, ::u32 uFlags) = MessageBoxAForConsole;



int_bool MessageBoxAForConsole(oswindow interaction_impl, const ::scoped_string & scopedstr, const ::scoped_string & scopedstrTitle, ::u32 uFlags)
{

   string strLine;


   strLine = "\n";

   if(strlen(pszTitle) > 0)
   {

      strLine += pszTitle;

      strLine += " : ";

   }

   strLine += psz;

   int iDefaultButton = e_dialog_result_ok;


   string str;

   if((uFlags & MB_YESNOCANCEL) == MB_YESNOCANCEL)
   {
      str += "y/n/c";
   }
   else if((uFlags & MB_YESNO) == MB_YESNO)
   {
      str += "y/n";
   }

   bool bDefault = false;

   if((uFlags & MB_DEFBUTTON1) == MB_DEFBUTTON1 && str.get_length() >= 1)
   {
      str.set_at(0, char_to_upper(str[0]));
      iDefaultButton = e_dialog_result_yes;
      bDefault = true;
   }
   else if((uFlags & MB_DEFBUTTON2) == MB_DEFBUTTON2 && str.get_length() >= 3)
   {
      str.set_at(2, char_to_upper(str[2]));
      iDefaultButton = e_dialog_result_no;
      bDefault = true;
   }
   else if((uFlags & MB_DEFBUTTON3) == MB_DEFBUTTON3 && str.get_length() >= 5)
   {
      str.set_at(4, char_to_upper(str[4]));
      iDefaultButton = e_dialog_result_cancel;
      bDefault = true;
   }

   if(str.has_char())
   {

      strLine += " : (" + str + ") ? ";

   }
   else
   {

      strLine += " : (OK) ";

   }

   int iRet = iDefaultButton;

   bool bAnswer = false;

repeat:

   if(uFlags & e_message_box_icon_exclamation || uFlags & e_message_box_icon_stop)
   {

      fputs(strLine, stderr);

   }
   else
   {

      fputs(strLine, stdout);

   }

   if((uFlags & MB_YESNOCANCEL) == MB_YESNOCANCEL)
   {

      int c = getc(stdin);

      switch(c)
      {
      case 'y':
      case 'Y':
         iRet = e_dialog_result_yes;
         bAnswer = true;
         break;
      case 'n':
      case 'N':
         iRet = e_dialog_result_no;
         bAnswer = true;
         break;
      case 'c':
      case 'C':
         iRet = e_dialog_result_cancel;
         bAnswer = true;
         break;
      default:
         bAnswer = bDefault;
         break;

      }

   }
   else if((uFlags & MB_YESNO) == MB_YESNO)
   {

      int c = getc(stdin);

      switch(c)
      {
      case 'y':
      case 'Y':
         iRet = e_dialog_result_yes;
         bAnswer = true;
         break;
      case 'n':
      case 'N':
         iRet = e_dialog_result_no;
         bAnswer = true;
         break;
      default:
         bAnswer = bDefault;
         break;
      }

   }
   else
   {

      getc(stdin);

   }


   if(!bAnswer)
      goto repeat;


   return iRet;

}

