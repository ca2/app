#include "framework.h"
#include "color_filter.h"


bool color_filter::get_matrix(color_matrix & colormatrix) const
{

   if (is_opacity_filter())
   {

      colormatrix = color_matrix();

      colormatrix.opacity(opacity());

      return true;

   }

   if (m_pcolormatrix)
   {

      colormatrix = *m_pcolormatrix;

      return true;

   }

   return false;

}
