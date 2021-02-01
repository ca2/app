#pragma once


class CLASS_DECL_CORE xfplayer_view_linea :
   virtual public ::object
{
public:


   XfplayerViewLineSelection        m_selection;
   ::user::interaction *            m_pinteraction;
   index                            m_iFirstVisible;
   index                            m_iLastVisible;

   HAVE_ARRAY_OF(line, m_linea, xfplayer_view_line);


   xfplayer_view_linea();


   void set_blend(double dBlend);
   index FindLine(xfplayer_view_line * pline);
   void SetRenderWindow(::user::interaction_impl * pwindow);
   void SetEffect(i32 iEffect);
   void set_user_interaction(__pointer(::user::interaction) pinteraction);
   void Prepare(xfplayer_view_line * pViewLine);

   void Prepare();

   index GetFirstVisibleLineIndex();
   index GetLastVisibleLineIndex();
   void OnChildSetVisible(xfplayer_view_line * pViewLine, bool bVisible);


   

   user::enum_line_hit hit_test(const point_i32 &pointCursor, strsize &iLine, strsize &iChar);

   void install_message_routing(::channel * pchannel);

   virtual ~xfplayer_view_linea();

   DECL_GEN_SIGNAL(OnMouseMove);
   DECL_GEN_SIGNAL(OnLButtonDown);
   DECL_GEN_SIGNAL(OnLButtonUp);
   virtual void _001OnTimer(::timer * ptimer);
   DECL_GEN_SIGNAL(OnSetCursor);

   XfplayerViewLineSelection & GetSelection();

   void get_sel_text(string & strSelText, const char * pszLineSeparator = "\r\n");
   string get_sel_text(const char * pszLineSeparator = "\r\n");

   void get_text(string & strSelText, const char * pszLineSeparator = "\r\n");
   string get_text(const char * pszLineSeparator = "\r\n");

};



