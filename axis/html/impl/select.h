#pragma once


#include "element.h"


namespace html
{


   namespace impl
   {


      class CLASS_DECL_AXIS select : public element
      {
      public:


         int                    m_iFont;
         ::pointer<::user::combo_box>    m_pcombo;


         select();
         virtual ~select();
         
         
         void _001OnDraw(html_data * pdocument);
         virtual void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         
         
         virtual bool layout_phase1(html_data * pdocument);
         virtual void layout_phase3(html_data * pdocument);

         
         virtual void layout_phase1_end(html_data * pdata);
         virtual void layout_phase3_end(html_data * pdata);


         void on_change_layout(html_data * pdocument);

         //void set_pos(html_data * pdocument,float x,float y,float cx,float cy);

      };


   } // namespace impl


} // namespace html



