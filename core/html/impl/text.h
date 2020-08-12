#pragma once


namespace html
{


   namespace impl
   {


      class text :
         virtual public elemental
      {
      public:


         __pointer(::user::plain_edit)        m_pedit;

         array < ::sizef >             m_sizea;
         string_array                       m_straLines;
         string_array                       m_straWordSpace;
         bool                          m_bLink;
         string                        m_strLink;
         bool                          m_bOnAfterChangeText;


         text();

         DECL_GEN_SIGNAL(OnLButtonDown);
         DECL_GEN_SIGNAL(OnMouseMove);
         DECL_GEN_SIGNAL(OnLButtonUp);


         virtual void _001OnGetText();


         virtual void _001OnDraw(html_data * pdocument);
         virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);
         void implement_phase1(html_data * pdocument, ::html::elemental * pelemental);
         void layout_phase0(html_data * pdata);
         bool layout_phase1(html_data * pdata);
         void layout_phase3(html_data * pdata);

         virtual void delete_implementation(html_data * pdocument);

         virtual bool get_color(COLORREF & cr);
         virtual bool has_link();
         virtual string link();

         virtual i32 hit_test(html_data * pdocument, const ::pointf & point);

         virtual strsize char_hit_test(::draw2d::graphics_pointer & pgraphics, i32 x, i32 y);

         virtual float get_first_line_height();
         virtual float get_last_line_height();

         virtual void _001OnAfterChangeText(const ::action_context & action_context);


      };


   } // namespace impl


} // namespace html




