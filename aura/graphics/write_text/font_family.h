// Created by camilo on 2023-06-28 16:40 <3ThomasBorregaardSorensen!!
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA font_family :
      virtual public ::particle
   {
   public:


      enum_font         m_efont;
      ::string          m_strFamilyName;

   protected:
      font_family(enum_font efont);

      font_family(const ::scoped_string & scopedstrFamilyName);

      font_family(const font_family & fontfamily);

      friend class font_family_pointer;

   public:

      font_family();


      font_family & operator = (const ::scoped_string & scopedstrFamilyName);

      font_family & operator = (const font_family & fontfamily);


      ::string family_name(::particle * pparticle) const;


      ::particle_pointer clone() const override;


   };


   class CLASS_DECL_AURA font_family_pointer :
      public ::pointer < font_family >
   {
   public:

      font_family_pointer(enum_font efont = e_font_default);

      font_family_pointer(const ::scoped_string & scopedstrFamilyName);

      font_family_pointer(const ::string & strFamilyName) : font_family_pointer((const scoped_string &)strFamilyName) {}

      template < primitive_character CHARACTER >
      font_family_pointer(const CHARACTER * psz) : font_family_pointer((const scoped_string &)psz) {}

      font_family_pointer(const font_family & fontfamily);

      font_family_pointer(const ::particle_pointer & pparticle);


   };


} // namespace write_text



