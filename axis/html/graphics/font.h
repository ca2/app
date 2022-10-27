#pragma once


namespace html
{


   class CLASS_DECL_AXIS font :
      virtual public ::object
   {
   public:
      
      
      index                         m_iIndex;
      string                        m_strFamily;
      string                        m_strWeight;
      string                        m_strSize;
      string                        m_strTextDecoration;
      ::write_text::font_pointer    m_pfont;


      font();
      font(const class font & font);
      
      
      bool create(::particle * pparticle);


      bool operator == (const font & font) const;


   };


} // namespace html







