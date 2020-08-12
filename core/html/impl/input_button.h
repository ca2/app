#pragma once


namespace html
{


   namespace impl
   {


      class CLASS_DECL_CORE input_button : public elemental
      {
      public:

         
         i32 m_iFont;
         __composite(::user::button) m_pbutton;


         input_button();
         virtual ~input_button();


         void _001OnDraw(html_data * pdocument);


         virtual void implement_phase1(html_data * pdocument, ::html::elemental * pelemental);
         virtual bool layout_phase1(html_data * pdocument);
         virtual void layout_phase3(html_data * pdocument);
         void on_change_layout(html_data * pdocument);


      };


   } // namespace impl


} // namespace html













