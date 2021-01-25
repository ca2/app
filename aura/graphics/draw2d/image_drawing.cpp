// Created by CamiloSasukeThomasBorregaardSoerensen 2021-01-23 04:40
// This is how things starts happening, promise of Life, in a virgin Temple...
// to be or not to be, or will it be or won't, that is the question....
#include "framework.h"


image_drawing::~image_drawing()
{


}


bool image_drawing_options::get_color_matrix(color_matrix & colormatrix) const
{

   if (m_pcolorfilter.is_null())
   {

      return false;

   }


   if(!m_pcolorfilter->get_color_matrix(colormatrix))
   {

      return false;

   }

   return true;

}



