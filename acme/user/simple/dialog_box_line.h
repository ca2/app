// Created by camilo on 2026-03-31 06:24 <3ThomasBorregaardSørensen!!
#pragma once



class CLASS_DECL_ACME simple_dialog_box_line :
   virtual public ::particle
{
public:


   ::string                      m_str;
   //double                      m_dFontSizeEm;
   //int                         m_iFontWeight;
   //::particle_pointer          m_pparticleFont;
   enum_simple_dialog_style      m_esimpledialogstyle;
   bool                          m_bSpacingLine;


   simple_dialog_box_line();
   ~simple_dialog_box_line() override;


   void initialize(::particle * pparticle) override;


   virtual void _001Parse(const ::scoped_string & scopedstr);


   virtual double get_font_size_em() const;
   virtual int get_font_weight() const;
   virtual int get_byte_text_color_strength() const;
   virtual bool is_spacing_line() const;
   virtual ::string get_line_height_text();

};



