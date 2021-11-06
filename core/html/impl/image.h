#pragma once


namespace html
{


   namespace impl
   {


      class image : public element
      {
      public:
      
         
         image_pointer     m_pimage;
         ::rectangle_i32            m_rectangle;


         void _001OnDraw(html_data * pdocument);
         void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         bool layout_phase1(html_data * pdocument);
         void layout_phase3(html_data * pdocument);

      };


   } // namespace impl


} // namespace html




