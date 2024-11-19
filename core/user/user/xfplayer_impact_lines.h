#pragma once


class CLASS_DECL_CORE xfplayer_impact_linea :
   virtual public ::object
{
public:


   ::pointer<xfplayer_impact_line_selection>   m_pselection;
   ::user::interaction *                        m_puserinteraction;
   ::collection::index                                        m_iFirstVisible;
   ::collection::index                                        m_iLastVisible;


   HAVE_ARRAY_OF(line, m_linea, xfplayer_impact_line);


   xfplayer_impact_linea(::user::interaction * puserinteraction);


   void set_blend(double dBlend);
   ::collection::index FindLine(xfplayer_impact_line * pline);
   //void SetRenderWindow(::windowing::window * pwindow);
   void SetEffect(int iEffect);
   //void set_user_interaction(::pointer<::user::interaction>pinteraction);
   void Prepare(xfplayer_impact_line * pImpactLine);

   void Prepare();

   ::collection::index GetFirstVisibleLineIndex();
   ::collection::index GetLastVisibleLineIndex();
   void OnChildSetVisible(xfplayer_impact_line * pImpactLine, bool bVisible);


   user::enum_line_hit hit_test(const int_point &pointCursor, character_count &iLine, character_count &iChar);

   void install_message_routing(::channel * pchannel);

   virtual ~xfplayer_impact_linea();

   DECLARE_MESSAGE_HANDLER(OnMouseMove);
   DECLARE_MESSAGE_HANDLER(OnLButtonDown);
   DECLARE_MESSAGE_HANDLER(OnLButtonUp);
   virtual void on_timer(::timer * ptimer);
   DECLARE_MESSAGE_HANDLER(OnSetCursor);

   xfplayer_impact_line_selection & GetSelection();

   void get_sel_text(string & strSelText, const ::string & pszLineSeparator = "\r\n");
   string get_sel_text(const ::string & pszLineSeparator = "\r\n");

   void get_text(string & strSelText, const ::string & pszLineSeparator = "\r\n");
   string get_text(const ::string & pszLineSeparator = "\r\n");

};



