//
// Created by camilo on 26/11/2020. CamiloSasukeThomasBorregaardSorensen
//
#include "framework.h"
#include "os_theme_colors.h"


//namespace user
//{


   bool os_theme_colors::is_ok() const
   {

      if(m_colorBack == m_colorFore)
      {

         return false;

      }

      if(m_colorFore == m_colorFace)
      {

         return false;

      }

      return true;

   }


//   void os_set_theme_colors(os_theme_colors * pthemecolors)
//   {
//
//      g_pthemecolors = pthemecolors;
//
//   }


//   void os_term_theme_colors()
//   {
//
//      if(g_pthemecolors)
//      {
//
//         del_os_theme_colors(g_pthemecolors);
//
//         g_pthemecolors = nullptr;
//
//      }
//
//   }
//
//
//
//} // namespace user
//

//os_theme_colors * new_os_theme_colors()
//{
//
//   return new os_theme_colors();
//
//}
//
//
//void del_os_theme_colors(os_theme_colors * pthemecolors)
//{
//
//   delete pthemecolors;
//
//}



