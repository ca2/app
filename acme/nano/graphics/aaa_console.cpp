//
// Created by camilo on 2024-09-26 17:52 <3ThomasBorregaardSorensen!!
//
#include "framework.h"
#include "button.h"
#include "console.h"
#include "interchange.h"
#include "operating_system/console.h"



namespace nano {
namespace user {



   console::console()
   {


   }

   console::~console()
   {


   }


   void console::create_console(::nano::user::interchange * pinterchange)
   {

      m_pinterchange =  pinterchange;

      ::collection::index i = 0;

      for (auto & pnanobutton : m_pinterchange->m_nanobuttona)
      {

         char ch = pnanobutton->m_chLetter;

         m_mapCharIndex[character_tolower(ch)] = i;

         if (i == m_pinterchange->m_iDefaultButton)
         {

            m_cha1.insert_at(0, character_toupper(ch));

            m_stra.insert_at(0, pnanobutton->m_strText);

         }
         else
         {

            m_cha1.add(character_tolower(ch));

            m_stra.add(pnanobutton->m_strText);

         }

         i++;

      }

   }


   void console::_stdout_console()
   {

      ::collection::index iButton;

      while (true)
      {

         printf("%s", m_pinterchange->m_strTitle.c_str());

         ::string str;

         str = m_stra.implode(",");

         printf(" %s", str.c_str());

         printf(" (");

         printf("%c", m_cha1[0]);

         for (::collection::index i = 1; i < m_cha1.get_count(); i++)
         {

            printf("/%c", m_cha1[i]);

         }

         printf("):");

         char ch;

         auto iReturnCount = scanf("%c", &ch);

         if(iReturnCount >= 1)
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

         auto pnanobutton = m_pinterchange->m_nanobuttona[iButton];

         m_pinterchange->on_click(pnanobutton->m_edialogresult1, nullptr);

      }

   }


} // user
} // nano