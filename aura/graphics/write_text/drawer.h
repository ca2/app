// Created by camilo on 2021-06-08 02:26 BRT <3ThomasBorregaardSørensen__!!
#pragma once


#include "acme/primitive/geometry2d/_geometry2d.h"
////#include "acme/primitive/primitive/object.h"


namespace write_text
{


   class text_out;
   class text_out_array;
   class text_metric;


   class CLASS_DECL_AURA drawer :
      virtual public ::object
   {
   public:


      ::write_text::font_pointer                 m_pfont;
      ::write_text::font_pointer                 m_pfontDevice;


      drawer();
      ~drawer() override;


      virtual ::write_text::font* get_current_font();
      virtual void set(::write_text::font* pfont);


      virtual void draw(const ::write_text::text_out* ptextout);
      virtual void draw(const ::write_text::text_out_array& textouta);


      virtual ::size_f64 get_text_extent(const ::scoped_string & scopedstr);


      virtual ::write_text::text_metric get_text_metrics();
      virtual void get_text_metrics(::write_text::text_metric* pmetrics);


      virtual void TextOutRaw(double x, double y, const ::scoped_string & scopedstr);


      virtual void create_simple_multiline_layout(::write_text::text_out_array& textouta, const string& str, const ::rectangle_i32& rectangle, ::write_text::font* pfont, const ::e_align& ealign, enum_text_wrap etextwrap);
      virtual void split_text(string_array & stra, double w, enum_text_wrap etextwrap);
      virtual ::count _split_text(string_array & stra, ::index i, double w, enum_text_wrap etextwrap);
      virtual ::count _split_text_word(string_array & stra, ::index i, double w);
      virtual ::count _split_text_word_then_character(string_array & stra, ::index i, double w);
      virtual ::count _split_text_character(string_array & stra, ::index i, double w);





   };


} // namespace write_text



