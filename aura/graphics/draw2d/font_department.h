#pragma once


class CXfplayerSong;


namespace draw2d
{

   class font;

}


typedef __pointer_array(draw2d::font) draw2d_font_spa;


class CLASS_DECL_AURA font_department :
   virtual public ::apex::department
{
public:


   __pointer(::draw2d::font_enumeration)   m_pfontenumeration;

   //::draw2d::font_pointer                m_fontCaption;
   //::draw2d::font_pointer                m_fontMenu;
   //::draw2d::font_pointer                m_fontStandard;
   //::draw2d::font_pointer                m_font;
   //::draw2d::font_pointer                m_fontListCtrl;
   //::draw2d::font_pointer                m_fontMeshCtrl;
   //::draw2d::font_pointer                m_fontGridCtrl;
   //__pointer(draw2d::font)                 m_lpSongLabelFont;
   //__pointer(draw2d::font)                 m_lpSongListFont;
   //__pointer(draw2d::font)                 m_pfontLyric;
   //__pointer(draw2d::font)                 m_pfontLyricCompact;
   //__pointer(draw2d::font)                 m_pxffontMidiTrackName;
   //draw2d_font_spa              m_pTitleFonts;
   //draw2d_font_spa              m_pSubTitleFonts;
   //draw2d_font_spa              m_pH3TitleFonts;
   bool                             m_bInitialized;
   //bool                             m_bLyric;


   //::draw2d::font * GetListCtrlFont();
   //::draw2d::font * GetMeshCtrlFont();
   //::draw2d::font * GetGridCtrlFont();
   //::draw2d::font * GetCaptionFont();
   //::draw2d::font * GetStandartFont();
   //draw2d::font * GetSongListFont();
   //draw2d::font * GetSongLabelFont();
   //draw2d::font * GetTitleFont();
   //draw2d::font * GetSubTitleFont();
   //draw2d::font * GetH3TitleFont();
   //draw2d::font * GetMidiTrackNameFont();
   //::draw2d::font * GetMenuFont();
   //draw2d::font * GetLyricViewFont();
   //draw2d::font * GetLyricViewCompactFont();
   //draw2d_font_spa & GetTitleFonts();
   //draw2d_font_spa & GetSubTitleFonts();
   //draw2d_font_spa & GetH3TitleFonts();

   //void CreateLyricViewFonts();
   //void DestroyLyricViewFonts();


   font_department();
   virtual ~font_department();


   virtual ::e_status initialize(::layered * pobjectContext);
   virtual void finalize();


   virtual bool is_initialized();
   virtual void defer_create_font_enumeration(::promise::subject * psubject);


};

