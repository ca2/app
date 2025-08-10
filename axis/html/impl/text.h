#pragma once


#include "element.h"


namespace html
{


   namespace impl
   {


      class text :
         virtual public element
      {
      public:


         ::pointer<::user::plain_edit>       m_pedit;

         array < ::float_size >             m_sizea;
         string_array_base                       m_straLines;
         string_array_base                       m_straWordSpace;
         bool                          m_bLink;
         string                        m_strLink;
         bool                          m_bOnAfterChangeText;


         text();

         DECLARE_MESSAGE_HANDLER(OnLButtonDown);
         DECLARE_MESSAGE_HANDLER(OnMouseMove);
         DECLARE_MESSAGE_HANDLER(OnLButtonUp);


         virtual void _001OnGetText();


         virtual void _001OnDraw(html_data * pdocument);
         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
         void implement_phase1(html_data * pdocument, ::html::element* pelemental);
         void layout_phase0(html_data * pdata);
         bool layout_phase1(html_data * pdata);
         void layout_phase3(html_data * pdata);

         virtual void delete_implementation(html_data * pdocument);

         virtual bool get_color(::color::color & color32);
         virtual bool has_link();
         virtual string link();

         virtual int hit_test(html_data * pdocument, const ::float_point & point);

         virtual character_count char_hit_test(::draw2d::graphics_pointer & pgraphics, int x, int y);

         virtual float get_first_line_height();
         virtual float get_last_line_height();

         virtual void _001OnAfterChangeText(const ::action_context & action_context);


      };


   } // namespace impl


} // namespace html




