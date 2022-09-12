#include "framework.h"
#include "margin.h"


namespace user
{


   margin_base::margin_base()
   {

      m_rectangleMargin.left    = 0;
      m_rectangleMargin.top     = 0;
      m_rectangleMargin.right   = 0;
      m_rectangleMargin.bottom  = 0;

   }


   margin_base::~margin_base()
   {

   }


   void margin_base::get_margin_rect(RECTANGLE_I32 * prectMargin)

   {

      *prectMargin = m_rectangleMargin;


   }


} // namespace user



