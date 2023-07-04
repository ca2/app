// Created by camilo on 2023-06-28 19:47 <3ThomasBorregaardSorensen!!
#pragma once


namespace write_text
{ 


   class font_weight
   {
   protected:


      enum_font_weight        m_efontweight;
      /// m_iFontWeight maybe "fraction" of a font weight
      ::i16                   m_iFontWeight;


   public:


      font_weight() :
         m_efontweight(e_font_weight_normal),
         m_iFontWeight(e_font_weight_normal)
      {


      }


      font_weight(enum_font_weight efontweight) : 
         m_efontweight(efontweight), 
         m_iFontWeight(efontweight)
      {

      }


      font_weight(int iFontWeight)
      {

         set_font_weight(iFontWeight);

      }


      constexpr static enum_font_weight sink(int iFontWeight) 
      {

         if (iFontWeight <= 0)
         {

            return e_font_weight_dont_care;

         }
         else if (iFontWeight <= 150)
         {

            return e_font_weight_thin;

         }
         else if (iFontWeight <= 250)
         {

            return e_font_weight_extra_light;

         }
         else if (iFontWeight <= 325)
         {

            return e_font_weight_light;

         }
         else if (iFontWeight <= 375)
         {

            return e_font_weight_semi_light;

         }
         else if (iFontWeight <= 450)
         {

            return e_font_weight_normal;

         }
         else if (iFontWeight <= 550)
         {

            return e_font_weight_medium;

         }
         else if (iFontWeight <= 650)
         {

            return e_font_weight_semibold;

         }
         else if (iFontWeight <= 750)
         {

            return e_font_weight_bold;

         }
         else if (iFontWeight <= 850)
         {

            return e_font_weight_extra_bold;

         }
         else if (iFontWeight <= 925)
         {

            return e_font_weight_heavy;

         }
         else
         {

            return e_font_weight_ultra_black;

         }

      }


      constexpr enum_font_weight efontweight() const { return m_efontweight; }
      constexpr ::i32 i32() const { return m_iFontWeight; }


      constexpr operator enum_font_weight() const { return efontweight(); }
      constexpr operator ::i32() const { return i32(); }


      constexpr ::std::weak_ordering operator <=>(const enum_font_weight efontweight) const
      {

         if (m_iFontWeight > 0)
         {

            return sink(m_iFontWeight) <=> efontweight;

         }
         else
         {

            return m_efontweight <=> efontweight;

         }

      }


      template < primitive_integral INTEGRAL >
      constexpr ::std::strong_ordering operator <=>(const INTEGRAL iFontWeight) const
      {

         return m_iFontWeight <=> iFontWeight;

      }


      template < primitive_integral INTEGRAL >
      void set_font_weight(INTEGRAL iFontWeight)
      {
      
         m_efontweight = sink(iFontWeight);
         m_iFontWeight = maximum(minimum(I16_MAXIMUM, iFontWeight), -1);

      }


      font_weight & operator = (enum_font_weight efontweight)
      {

         m_efontweight = efontweight;
         m_iFontWeight = efontweight;

         return *this;

      }


      template < primitive_integral INTEGRAL >
      font_weight & operator = (INTEGRAL iFontWeight)
      {

         set_font_weight(iFontWeight);

         return *this;

      }

   };


} // namespace write_text



