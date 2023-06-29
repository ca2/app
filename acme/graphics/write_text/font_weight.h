// Created by camilo on 2023-06-28 19:47 <3ThomasBorregaardSorensen!!
#pragma once



namespace write_text
{ 


   class font_weight
   {
   public:


      enum_font_weight        m_efontweight;
      ::i16                   m_iFontWeight;


      font_weight() :
         m_efontweight(e_font_weight_normal),
         m_iFontWeight(-1)
      {


      }

      font_weight(enum_font_weight efontweight) : 
         m_efontweight(efontweight), 
         m_iFontWeight(-1)
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
         else if (iFontWeight <= 350)
         {

            return e_font_weight_light;

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
         else
         {

            return e_font_weight_heavy;

         }

      }




      constexpr operator enum_font_weight() const
      {

         if (m_iFontWeight <= 0)
         {

            return m_efontweight;

         }
         else if (m_iFontWeight <= 150)
         {

            return e_font_weight_thin;

         }
         else if (m_iFontWeight <= 250)
         {

            return e_font_weight_extra_light;

         }
         else if (m_iFontWeight <= 350)
         {

            return e_font_weight_light;

         }
         else if (m_iFontWeight <= 450)
         {

            return e_font_weight_normal;

         }
         else if (m_iFontWeight <= 550)
         {

            return e_font_weight_medium;

         }
         else if (m_iFontWeight <= 650)
         {

            return e_font_weight_semibold;

         }
         else if (m_iFontWeight <= 750)
         {

            return e_font_weight_bold;

         }
         else if (m_iFontWeight <= 850)
         {

            return e_font_weight_extra_bold;

         }
         else
         {

            return e_font_weight_heavy;

         }

      }

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
      void set_font_weight(INTEGRAL iFontWeight)
      {
      
         if (iFontWeight <= 0)
         {

            m_efontweight = e_font_weight_dont_care;

         }
         else if (iFontWeight == 100)
         {

            m_efontweight = e_font_weight_thin;

         }
         else if (iFontWeight == 200)
         {

            m_efontweight = e_font_weight_extra_light;

         }
         else if (iFontWeight == 300)
         {

            m_efontweight = e_font_weight_light;

         }
         else if (iFontWeight == 400)
         {

            m_efontweight = e_font_weight_normal;

         }
         else if (iFontWeight == 500)
         {

            m_efontweight = e_font_weight_medium;

         }
         else if (iFontWeight == 600)
         {

            m_efontweight = e_font_weight_semibold;

         }
         else if (iFontWeight == 700)
         {

            m_efontweight = e_font_weight_bold;

         }
         else if (iFontWeight == 800)
         {

            m_efontweight= e_font_weight_extra_bold;

         }
         else if (iFontWeight == 900)
         {

            m_efontweight = e_font_weight_heavy;

         }
         else
         {

            m_efontweight = e_font_weight_dont_care;

         }

         if(m_efontweight == e_font_weight_dont_care)
         {

            m_iFontWeight = iFontWeight;

         }
         else
         {

            m_iFontWeight = -1;

         }

      }

      font_weight & operator = (enum_font_weight efontweight)
      {

         m_efontweight = efontweight;
         m_iFontWeight = -1;

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