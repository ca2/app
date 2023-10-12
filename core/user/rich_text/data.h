#pragma once


#include "acme/primitive/data/data.h"
#include "span.h"
#include "format_host.h"


namespace user
{


   namespace rich_text
   {


      class edit_impl;


      class CLASS_DECL_CORE data :
         virtual public ::data::data,
         virtual public ::user::rich_text::format_host
      {
      public:


         //::draw2d::graphics_pointer                   m_pgraphics;

         //::rectangle_f64                            m_rectangle;
         
         // storage data
         pointer_array < span >                       m_spana;
         //pointer< pointer_array < format > >          m_pformata;

         ::pointer<format>                            m_pformatCurrent;

         


         data();
         ~data() override;


         void initialize_data(::data::data_container_base * pdocument) override;
         void destroy() override;

         virtual void __initialize(::pointer<::user::rich_text::format>& pformat);


         //virtual ::user::rich_text::edit * get_rich_text_edit();

         // if span has alignment set, it generates memory_new line
         //::pointer<span>create_span(::e_align ealignNewLine = e_align_none);
         ::pointer<span>create_span();

         virtual ::pointer<span> add_span(::e_align ealignEndOfLine, bool bEndOfLine);
         //virtual ::pointer<span> add_start_of_line_span(::e_align ealignNewLine, bool bEndOfLine);
         //virtual ::pointer<span> add_span();
         //virtual ::pointer<span> add_end_of_line_span();

         ::pointer<span>add_span(const span & span);

         //index fork_format(index iFormat);

         //virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);



         string get_full_text();


         virtual void _001SetFontFormat(::strsize iSelBeg, ::strsize iEnd, const format * pformat, const e_attribute & eattribute);

         virtual void _001Delete(strsize i1, strsize i2);
         virtual strsize _001InsertText(strsize i1, strsize i2, const ::string & psz, format * pformatParam = nullptr);

         virtual void _001GetText(string & str) const;

         virtual void optimize_data();


         virtual strsize _001GetTextLength() const;

         //void write(::binary_stream & stream) const override;
         //void read(::binary_stream & stream) override;
         bool on_new_data();
         bool on_open_data(const ::payload & payloadFile);
         bool on_save_data(::file::file * pfile);

      };


      inline void span::set_new_format(){ m_pformat = m_pdata->add_format(); }

   } // namespace rich_text


} // namespace user



