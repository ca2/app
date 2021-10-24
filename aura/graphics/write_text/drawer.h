// Created by camilo on 2021-06-08 02:26 BRT <3ThomasBorregaardS�rensen__!!
#pragma once


namespace write_text
{

   class CLASS_DECL_AURA drawer :
      virtual public ::object
   {
   public:


      ::write_text::font_pointer                 m_pfont;
      ::write_text::font_pointer                 m_pfontDevice;


      drawer();
      ~drawer() override;


      virtual ::write_text::font* get_current_font();
      virtual ::e_status set(::write_text::font* pfont);


      virtual ::e_status draw(const ::write_text::text_out* ptextout);
      virtual ::e_status draw(const ::write_text::text_out_array& textouta);


      virtual ::size_f64 get_text_extent(const ::block& block);


      virtual ::write_text::text_metric get_text_metrics();
      virtual ::e_status get_text_metrics(::write_text::text_metric* pmetrics);


      virtual ::e_status TextOutRaw(double x, double y, const block& block);


      virtual ::e_status create_simple_multiline_layout(::write_text::text_out_array& textouta, const string& str, const ::rectangle_i32& rectangle, ::write_text::font* pfont, const ::e_align& ealign, enum_text_wrap etextwrap);
      virtual ::e_status split_text(string_array & stra, double w, enum_text_wrap etextwrap);
      virtual ::count _split_text(string_array & stra, ::index i, double w, enum_text_wrap etextwrap);
      virtual ::count _split_text_word(string_array & stra, ::index i, double w);
      virtual ::count _split_text_word_then_character(string_array & stra, ::index i, double w);
      virtual ::count _split_text_character(string_array & stra, ::index i, double w);





   };


} // namespace write_text



