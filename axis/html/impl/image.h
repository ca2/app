#pragma once


#include "element.h"


namespace html
{


   namespace impl
   {


      class image : public element
      {
      public:
      
         
         ::image::image_pointer     m_pimage;
         ::int_rectangle            m_rectangle;


         void _001OnDraw(html_data * pdocument);
         void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         bool layout_phase1(html_data * pdocument);
         void layout_phase3(html_data * pdocument);

      };


   } // namespace impl


} // namespace html




