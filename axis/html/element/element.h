#pragma once


#include "axis/html/impl/_.h"
#include "apex/user/user/interaction_base.h"


namespace css
{

   enum enum_plain_color
   {

      color_text,
      color_background,

   };

}


namespace html
{


   class CLASS_DECL_AXIS element :
      virtual public ::object
      //virtual public ::user::interaction_base,
      //virtual public ::user::text
   {
   public:


      // always present property?! "text"
      ::property_set             m_propertyset;
      ::pointer<impl::element>   m_pimpl;
      element *                  m_pparent;
      ::html::base *             m_phtmlbase;
      html_data *                m_pdata;

      ::pointer<::html::style>  m_pstyle;
      pointer_array < element >   m_elementalptra;

      e_tag                      m_etag;
      string                     m_strBody;
      atom                         m_atomTagName;
      bool                       m_bParent;
      bool                       m_bTagVisible;
      string                     m_strClass;
      string                     m_strInlineStyle;


      element();
      virtual ~element();


      virtual void initialize_html_elemental(html_data * pdata, element * pparent = nullptr);


      virtual void initialize_html_element(html_data* phtmldata);



      virtual void set_text(const ::scoped_string & scopedstr);

      DECLARE_MESSAGE_HANDLER(OnLButtonDown);
      DECLARE_MESSAGE_HANDLER(OnMouseMove);
      DECLARE_MESSAGE_HANDLER(OnLButtonUp);


      virtual void delete_implementation(html_data * phtmldata);

      void destroy(html_data * phtmldata);

      //virtual void nextstyle(::user::style_context * pcontext) override;


      element * get_element_by_name(atom atom);
      element * get_element_by_id(atom atom);

      virtual element * hit_test(html_data * phtmldata, const ::float_point & point);
      virtual element * bound_hit_test(html_data * phtmldata, const ::float_point & point);
      virtual element * bound_hit_test(html_data * phtmldata, const ::float_point & point, double & dMin);


      virtual void implement(html_data * phtmldata);
      virtual void on_layout(html_data * phtmldata);

      virtual void _001OnDraw(html_data * phtmldata);
      virtual void load(html_data * phtmldata, ::html::base * phtmlbase);

      //virtual bool get_color(::color::color & color32, ::user::e_color ecolor, ::user::style_context * pcontext) override;
      //virtual bool get_font(::write_text::font_pointer & spfont, ::user::e_font efont, ::user::style_context * pcontext) override;

      virtual ::color::color get_color(::user::style * pstyle, ::css::enum_plain_color ecolor);
      virtual ::write_text::font_pointer get_font();

      tag * get_tag();


      virtual void implement_phase1(html_data * phtmldata);
      virtual void implement_phase2(html_data * phtmldata);

      virtual void layout_phase0(html_data * pdata); // cx minimum/maximum
      virtual void layout_phase1(html_data * pdata); // cxy
      virtual void layout_phase2(html_data * pdata); // adjust
      virtual void layout_phase3(html_data * pdata); // final on_layout

      virtual void get_html(html_data * pdata, string & str);


   protected:
      virtual bool parse(html_data * phtmldata, ::ansi_range & range);
      virtual void parse_attributes(html_data * phtmldata, ::ansi_range & range);


   };


} // namespace html





