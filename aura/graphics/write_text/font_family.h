// Created by camilo on 2023-06-28 16:40 <3ThomasBorregaardSorensen!!
#pragma once


namespace write_text
{


   class CLASS_DECL_AURA font_family :
      virtual public ::particle
      //, public ::allocator::accessor < font_family >
   {
   public:


      enum_font         m_efont;
      ::string          m_strFamilyName;
      ::string          m_strBranch;

   //protected:
      font_family(enum_font efont);

      template < prototype_character_range RANGE >
      font_family(const RANGE & rangeFamilyName)
      {

         m_efont = e_font_with_family_name;

         m_strFamilyName = rangeFamilyName;

      }

      template < prototype_character_range RANGE, prototype_character_range RANGE2 >
      font_family(const RANGE & rangeFamilyName, const RANGE2 & rangeBranch)
      {

         m_efont = e_font_with_family_name;

         m_strFamilyName = rangeFamilyName;

         m_strBranch = rangeBranch;

      }


      template < prototype_character CHARACTER >
      font_family(const CHARACTER * pszFamilyName)
      {

         m_efont = e_font_with_family_name;

         m_strFamilyName = pszFamilyName;

      }


      template < prototype_character CHARACTER, prototype_character CHARACTER2 >
      font_family(const CHARACTER * pszFamilyName, const CHARACTER2 * pszBranch)
      {

         m_efont = e_font_with_family_name;

         m_strFamilyName = pszFamilyName;

         m_strBranch = pszBranch;

      }

      font_family(const font_family & fontfamily);

      friend class ::allocator::accessor;

   public:

      font_family();


      font_family & operator = (const ::scoped_string & scopedstrFamilyName);

      font_family & operator = (const font_family & fontfamily);


      ::string family_name(::particle * pparticle) const;


      ::subparticle_pointer clone() override;


   };


   class CLASS_DECL_AURA font_family_pointer :
      public ::pointer < font_family >//,
      //public ::allocator::accessor < font_family >
   {
   public:


      font_family_pointer(enum_font efont = e_font_default);


      template < prototype_character_range RANGE >
      font_family_pointer(const RANGE & rangeFamilyName):
         ::pointer < font_family >(øallocate font_family(rangeFamilyName))
      {
      }

      template < prototype_character_range RANGE, prototype_character_range RANGE2 >
      font_family_pointer(const RANGE & rangeFamilyName, const RANGE2 & rangeBranch) :
         ::pointer < font_family >(øallocate font_family(rangeFamilyName, rangeBranch))
      {
      }


      template < prototype_character CHARACTER >
      font_family_pointer(const CHARACTER * pszFamilyName):
         ::pointer < font_family >(øallocate font_family(pszFamilyName))
      {

      }

      template < prototype_character CHARACTER, prototype_character CHARACTER2 >
      font_family_pointer(const CHARACTER * pszFamilyName, const CHARACTER2 * pszBranch) :
         ::pointer < font_family >(øallocate font_family(pszFamilyName, pszBranch))
      {

      }


      font_family_pointer(const font_family & fontfamily);

      font_family_pointer(const ::subparticle_pointer & pparticle);


   };


} // namespace write_text



