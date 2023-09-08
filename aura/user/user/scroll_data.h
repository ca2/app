#pragma once





namespace user
{


   class scroll_bar;


   class CLASS_DECL_AURA scroll_data :
      virtual public ::particle
   {
   public:


      ::i32          m_iPage;
      ::i32          m_iLine;
      ::i32          m_iWheel;
      i32            m_iWidth;
      bool           m_bHasScroll;
      bool           m_bScrollEnable;
      //bool           m_bShowScroll;


      inline bool scroll_visible() const
      {

         return m_bHasScroll && m_bScrollEnable;

      }


   };

  
} // namespace user



