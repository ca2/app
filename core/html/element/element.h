#pragma once


#include "core/html/impl/_.h"

namespace css
{

   enum enum_color
   {

      color_text,
      color_background,

   };

}


namespace html
{


   class CLASS_DECL_CORE element :
      virtual public ::user::primitive,
      virtual public ::user::text
   {
   public:


      // always present property?! "text"
      property_set               m_propertyset;
      __pointer(impl::element)   m_pimpl;
      element *                  m_pparent;
      base *                     m_pbase;
      html_data *                m_pdata;

      __pointer(::html::style)   m_pstyle;
      __pointer_array(element)   m_elementalptra;

      e_tag                      m_etag;
      string                     m_strBody;
      id                         m_idTagName;
      bool                       m_bParent;
      bool                       m_bTagVisible;
      string                     m_strClass;
      string                     m_strInlineStyle;


      element();
      virtual ~element();


      virtual ::e_status initialize_html_elemental(html_data * pdata, element * pparent = nullptr);


      virtual ::e_status initialize_html_element(html_data* phtmldata);



      virtual void _001SetText(const string & str, const ::action_context & action_context) override;

      DECLARE_MESSAGE_HANDLER(OnLButtonDown);
      DECLARE_MESSAGE_HANDLER(OnMouseMove);
      DECLARE_MESSAGE_HANDLER(OnLButtonUp);


      virtual void delete_implementation(html_data * phtmldata);

      void destroy(html_data * phtmldata);

      //virtual void nextstyle(::user::style_context * pcontext) override;


      element * get_element_by_name(id id);
      element * get_element_by_id(id id);

      virtual element * hit_test(html_data * phtmldata, const ::point_f32 & point);
      virtual element * bound_hit_test(html_data * phtmldata, const ::point_f32 & point);
      virtual element * bound_hit_test(html_data * phtmldata, const ::point_f32 & point, double & dMin);


      virtual void implement(html_data * phtmldata);
      virtual void on_layout(html_data * phtmldata);

      virtual void _001OnDraw(html_data * phtmldata);
      virtual void load(html_data * phtmldata, base * pusermessage);

      //virtual bool get_color(color32_t & cr, ::user::e_color ecolor, ::user::style_context * pcontext) override;
      //virtual bool get_font(::write_text::font_pointer & spfont, ::user::e_font efont, ::user::style_context * pcontext) override;

      virtual ::color::color get_color(::user::style * pstyle, ::css::enum_color ecolor);
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
      virtual bool parse(html_data * phtmldata, const char * & psz);
      virtual void parse_attributes(html_data * phtmldata, const char * & psz);


   };


} // namespace html





