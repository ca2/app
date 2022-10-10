#pragma once


#include "element.h"


namespace html
{


   namespace impl
   {


      class CLASS_DECL_AXIS input_button : public element
      {
      public:

         
         i32 m_iFont;
         ::pointer<::user::button>m_pbutton;


         input_button();
         virtual ~input_button();


         void _001OnDraw(html_data * pdocument);


         virtual void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         virtual bool layout_phase1(html_data * pdocument);
         virtual void layout_phase3(html_data * pdocument);
         void on_change_layout(html_data * pdocument);


      };


   } // namespace impl


} // namespace html













