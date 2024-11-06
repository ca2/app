// Merged from scroll_state by camilo on 
// 2023-10-22 11:37 <3ThomasBorregaardSorensen!!
#pragma once


namespace user
{


   class scroll_bar;


   class CLASS_DECL_AURA scroll_state
   {
   public:


      //int          m_iPage;
      //int          m_iLine;
      //int          m_iWheel;
      //int            m_iWidth;
      //bool           m_bHasScroll;
      //bool           m_bScrollEnable;
      ////bool           m_bShowScroll;

      ::f64          m_dMinimum;
      ::f64          m_dMaximum;

      ///// @brief  if m_iPage is zero, 
      ///// units in this struct_data are expressed in pixels.
      //int            m_iPage;
      ::f64          m_dPosition;
      ::f64          m_dTrackingPosition;
      //bool           m_bHasScroll;
      //bool           m_bScrollEnable;


      ::f64          m_dPage;
      ::f64          m_dLine;
      ::f64          m_dWheel;
      ::f64          m_dThickness;
      bool           m_bHasScroll;
      bool           m_bScrollEnable;


      inline bool scroll_visible() const
      {

         return m_bHasScroll && m_bScrollEnable;

      }


      inline ::f64 dimension() const
      {

         return m_dMaximum - m_dMinimum;

      }


      inline void set_dimension(::f64 dDimension)
      {

         m_dMaximum = dDimension + m_dMinimum;

      }


      inline ::f64 range() const
      {

         return m_dMaximum - m_dMinimum - m_dPage;

      }


   };

   class CLASS_DECL_AURA scroll_layout :
      virtual public ::particle
   {
   public:

      scroll_state               m_scrollstatea[::user::e_layout_maximum_count];

   };

  
} // namespace user



