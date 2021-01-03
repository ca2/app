//
// Created by camilo.  <3Thomas Borregaard Soerensen!!
#include "framework.h"


string windows_font_name(enum_font efont)
{

   switch (efont)
   {
      case e_font_sans:
         return "FreeSans";
      case e_font_serif:
         return "FreeSerif";
      case e_font_sans_ui:
         return "FreeSans";
      case e_font_serif_ui:
         return "FreeSerif";
      case e_font_sans_ex:
         return "Liberation Sans";
      case e_font_serif_ex:
         return "Liberation Serif";
      case e_font_sans_fx:
         return "Ubuntu";
      case e_font_serif_fx:
         return "Bitstream Charter";
      case e_font_monospace:
         return "Ubuntu Mono";
      default:
         return "sans-serif";
   }

}


string ubuntu_font_name(enum_font efont)
{

   switch (efont)
   {
      case e_font_sans:
         return "FreeSans";
      case e_font_serif:
         return "FreeSerif";
      case e_font_sans_ui:
         return "FreeSans";
      case e_font_serif_ui:
         return "FreeSerif";
      case e_font_sans_ex:
         return "Liberation Sans";
      case e_font_serif_ex:
         return "Liberation Serif";
      case e_font_sans_fx:
         return "Ubuntu";
      case e_font_serif_fx:
         return "Bitstream Charter";
      case e_font_monospace:
         return "Ubuntu Mono";
      default:
         return "sans-serif";
   }

}


string linux_font_name(enum_linux_distribution elinuxdistribution, enum_font efont)
{

   switch(elinuxdistribution)
   {

      case e_linux_distribution_ubuntu:
      {

         return ubuntu_font_name(efont);

      }
      default:
      {

         return "sans-serif";

      }

   }

}


string os_font_name(enum_font efont)
{

#ifdef WINDOWS_DESKTOP

   return windows_font_name(efont);

#elif defined(LINUX)

   auto elinuxdistribution = System.get_linux_distribution();

   return linux_font_name(elinuxdistribution, efont);

#else

   return "sans-serif";

#endif

}


string os_font_name(enum_operating_system eoperatingsystem, int iVariant, enum_font efont)
{

   switch (eoperatingsystem)
   {
      case e_operating_system_windows:
      {

         return windows_font_name(efont);

      }
      case e_operating_system_linux:
      {

         auto elinuxdistribution = (::enum_linux_distribution) iVariant;

         return linux_font_name(elinuxdistribution, efont);

      }
      default:
      {

         return "sans-serif";

      }

   }

}



