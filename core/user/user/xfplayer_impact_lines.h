#pragma once


class CLASS_DECL_CORE xfplayer_impact_linea :
   virtual public ::object
{
public:


   ::pointer<xfplayer_impact_line_selection>   m_pselection;
   ::user::interaction *                        m_puserinteraction;
   index                                        m_iFirstVisible;
   index                                        m_iLastVisible;


   HAVE_ARRAY_OF(line, m_linea, xfplayer_impact_line);


   xfplayer_impact_linea(::user::interaction * puserinteraction);


   void set_blend(double dBlend);
   index FindLine(xfplayer_impact_line * pline);
   //void SetRenderWindow(::user::interaction_impl * pwindow);
   void SetEffect(i32 iEffect);
   //void set_user_interaction(::pointer<::user::interaction>pinteraction);
   void Prepare(xfplayer_impact_line * pImpactLine);

   void Prepare();

   index GetFirstVisibleLineIndex();
   index GetLastVisibleLineIndex();
   void OnChildSetVisible(xfplayer_impact_line * pImpactLine, bool bVisible);


   user::enum_line_hit hit_test(const point_i32 &pointCursor, strsize &iLine, strsize &iChar);

   void install_message_routing(::channel * pchannel);

   virtual ~xfplayer_impact_linea();

   DECLARE_MESSAGE_HANDLER(OnMouseMove);
   DECLARE_MESSAGE_HANDLER(OnLButtonDown);
   DECLARE_MESSAGE_HANDLER(OnLButtonUp);
   virtual void _001OnTimer(::timer * ptimer);
   DECLARE_MESSAGE_HANDLER(OnSetCursor);

   xfplayer_impact_line_selection & GetSelection();

   void get_sel_text(string & strSelText, const ::string & pszLineSeparator = "\r\n");
   string get_sel_text(const ::string & pszLineSeparator = "\r\n");

   void get_text(string & strSelText, const ::string & pszLineSeparator = "\r\n");
   string get_text(const ::string & pszLineSeparator = "\r\n");

};



