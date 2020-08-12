#pragma once


namespace html
{


   namespace impl
   {


      class image : public elemental
      {
      public:
      
         
         image_pointer     m_pimage;
         ::rect            m_rect;


         void _001OnDraw(html_data * pdocument);
         void implement_phase1(html_data * pdocument, ::html::elemental * pelemental);
         bool layout_phase1(html_data * pdocument);
         void layout_phase3(html_data * pdocument);

      };


   } // namespace impl


} // namespace html




