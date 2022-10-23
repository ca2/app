//
// Created by camilo.  <3Thomas Borregaard Soerensen!!
#include "framework.h"
#include "acme/primitive/string/string.h"


string windows_font_name(enum_font efont)
{


//#define FONT_SANS "Lucida Sans Unicode"
//#define FONT_SERIF "Times New Roman"
//#define FONT_MONO "Courier New"
//#define FONT_SANS_EX "Geneva"
//#define FONT_SERIF_EX "Palatino Linotype"
//#define FONT_SANS_FX "Tahoma"
//#define FONT_SERIF_FX "Georgia"

   switch (efont)
   {
      case e_font_sans:
         return "Lucida Sans Unicode";
      case e_font_serif:
         return "Times New Roman";
      case e_font_sans_ui:
         return "Segoe UI";
         //return "Times New Roman";
      case e_font_serif_ui:
         return "Georgia";
      case e_font_sans_ex:
         return "Geneva";
      case e_font_serif_ex:
         return "Palatino Linotype";
      case e_font_sans_fx:
         return "Tahoma";
      case e_font_serif_fx:
         return "Georgia";
      case e_font_monospace:
         return "Courier New";
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




