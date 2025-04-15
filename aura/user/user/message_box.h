// now based on a ::acme::user::message_box based on ::reified<::message_box> by
//    camilo on 2024-10-09 09:00 <3ThomasBorregaardSorensen!!
//
// Created by camilo on 29/01/2021.  02:05 BRT <3ThomasBS_!!
//
#pragma once


#include "acme/user/user/message_box.h"
#include "interaction.h"


namespace user
{



   class CLASS_DECL_AURA message_box :
      virtual public ::user::interaction,
      virtual public ::acme::user::message_box
   {
   public:


      bool                                            m_bFirstLayoutDone;


      //pointer< ::future < enum_dialog_result > >    m_pprocess;
      bool                                            m_bOsUserThemeColorModified;
      bool                                            m_bInvalidated;
      string_array                                    m_stra;
      //string                                          m_strTitle;
      string                                          m_strFontName;

      //Window                                        m_window;
      ::int_point                                     m_point;
      ::int_size                                      m_size;

      int                                             m_iLineHeight;
      int                                             m_iTextAscent;

      ::pointer<button>                              m_pbuttonClose;
      pointer_array < button >                         m_buttona;

      int                                             m_iButtonTop;
      int                                             m_iButtonHeight;
      int                                             m_iButtonWidth;

      ::pointer<still>                               m_pstill;

      //XftFont *                                     m_pfont;
      //XftDraw *                                     m_pdraw;
      //XFontSet                                      m_fs;
      //char **                                       m_listMissingCharset;
      //GC                                            m_gcText;
      //GC                                            m_gcTextHover;
      //GC                                            m_gcBar;
      //::color::color                                m_colorButton;
      //::color::color                                m_colorButtonHover;
      //::color::color                                m_colorButtonPress;
      //::color::color                                m_colorBorder;
      //::color::color                                m_colorBorderHover;
      //::color::color                                m_colorBorderPress;
      //::color::color                                m_colorBorderHover1;
      //::color::color                                m_colorBorderHover2;
      //::color::color                                m_colorBorderHover3;

      //Colormap                                      m_colormap;
      //int                                           m_iScreen;
      //Visual *                                      m_pvisual;
      int                                             m_iMarginTop;
      int                                             m_iMarginLeft;
      int                                             m_iMarginRight;
      int                                             m_iMarginBottom;
      int                                             m_iLineSpacing;
      int                                             m_iButtonHSpacing;
      int                                             m_iButtonHPadding;
      int                                             m_iButtonVPadding;
      int                                             m_iMidSpacing;

      //::color::color                                m_colorBack;
      //::color::color                                m_colorFace;
      //::color::color                                m_colorFore;

      //::color::color                                m_colorFaceHover;
      //::color::color                                m_colorFacePress;

      int                                             m_iResult;


      //message_box(const ::string & strMessage, const ::string & strTitle, const ::e_message_box & emessagebox);
      message_box();
      ~message_box() override;


      // message_box_interface
      //::pointer < ::subparticle > show(::user::interaction * puserinteraction, const string & strMessage, const string & strTitle, const ::e_message_box & emessagebox) override;
      void on_realize(::message_box * pmessagebox) override;
      void add_button(const ::scoped_string & scopedstrTitle, enum_dialog_result edialogresult, char chLetter) override;

      void destroy() override;

      void install_message_routing(::channel * pchannel) override;


      long long increment_reference_count() override;
      long long decrement_reference_count() override;
      long long release() override;


      void common_construct();


      DECLARE_MESSAGE_HANDLER(on_message_create);



   protected:
      void do_show();
   public:

      //GC create_gc();

      virtual void invalidate();

      //virtual void on_idle() override;

      //void on_expose(Display * pdisplay);

      //void call_expose(Display * pdisplay);

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void do_layout();

      //void on_colors(Display * pdisplay);

      //void on_alloc_colors(Display * pdisplay);

      //void on_free_colors(Display * pdisplay);

      //virtual bool process_event(Display * pdisplay, XEvent & e, XGenericEventCookie * cookie) override;

      //void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      

      void on_show();

      bool on_click(int iResult);

      virtual void close_window();


      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;



   };


} // namespace user



//
//namespace user
//{
//
//
//   class CLASS_DECL_AURA message_box :
//      virtual public ::matter
//   {
//   public:
//
//
//      string                  m_strText;
//      string                  m_strTitle;
//      ::e_message_box         m_emessagebox;
//
//
//      message_box(const string &strText, const string &strTitle, const ::e_message_box &emessagebox);
//      virtual ~message_box();
//
//
//      virtual ::payload realize() override;
//
//
//   };
//
//
//} // namespace user
//
//
////CLASS_DECL_AURA void auto pmessagebox = __initialize_new ::message_box(const ::string & pszMessage, const ::string & pszTitle = nullptr, const ::e_message_box & emessagebox = e_message_box_ok, const future & process = ::future());

//pmessagebox->sync();
//
//
//
