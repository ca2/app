//
// Created by camilo on 2024-09-26 17:52 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "button.h"
#include "console.h"
#include "dialog.h"
#include "operating_system/console.h"

#if defined(__BSD__) || defined(__APPLE__)
#include <stdio.h>
#endif

namespace micro
{


   console::console()
   {


   }

   console::~console()
   {


   }


   void console::create_console(::micro::dialog * pdialog)
   {

      m_pdialog = pdialog;

      ::collection::index i = 0;

      auto countButton = m_pdialog->micro_button_count();

      for (i = 0; i < countButton; i++)
      {

         auto pmicrobutton = m_pdialog->micro_button_at(i);

         char ch = pmicrobutton->m_chLetter;

         m_mapCharIndex[character_tolower(ch)] = i;

         if (i == m_pdialog->m_iDefaultButton)
         {

            m_cha1.insert_at(0, character_toupper(ch));

            m_stra.insert_at(0, pmicrobutton->m_strText);

         }
         else
         {

            m_cha1.add(character_tolower(ch));

            m_stra.add(pmicrobutton->m_strText);

         }

         i++;

      }

   }


   void console::_stdout_console()
   {

      ::collection::index iButton;

      while (true)
      {

         printf_out("%s", m_pdialog->get_title().c_str());

         ::string str;

         str = m_stra.implode(",");

         printf_out(" %s", str.c_str());

         printf_out(" (");

         printf_out("%c", m_cha1[0]);

         for (::collection::index i = 1; i < m_cha1.get_count(); i++)
         {

            printf_out("/%c", m_cha1[i]);

         }

         printf_out("):");

         char ch;

         auto iReturnCount = scanf("%c", &ch);

         if (iReturnCount >= 1)
         {

            ch = character_tolower(ch);

         }
         else
         {

            ch = '\0';

         }


         iButton = -1;

         if (m_mapCharIndex.lookup(ch, iButton))
         {

            break;

         }

      }

      if (iButton >= 0)
      {

         auto pmicrobutton = m_pdialog->micro_button_at(iButton);

         m_pdialog->on_click(pmicrobutton->m_edialogresult1, nullptr);

      }

   }

} // micro



