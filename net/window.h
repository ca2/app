#pragma once


namespace app_net
{


   /*class value
   {
   public :

      string m_str;

   };

   template < typename VALUE >
   class node
   {
   public:

      node* m_pprevious;
      node* m_pnext;
      VALUE m_value;


   };*/

   class CLASS_DECL_APP_APP_APP window :
      virtual public ::user::main_window
   {
   public:


      string                        m_strUrl;
      double                        m_dBreathPeriod;
      class ::time                    m_timeStart;
      double                        m_dPhaseShift;
      ::write_text::font_pointer    m_pfont;
      string                        m_strGet;
      bool                          m_bGettingUrl;
      class ::time                    m_timeStartGettingUrl;


      window();



      virtual void on_create_user_interaction() override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001DrawItem(::draw2d::graphics_pointer& pgraphics, ::item * pitem, const ::user::e_state & estate) override;


      virtual void start_getting_url();

      virtual bool on_click(::item *pitem) override;


   };


} // namespace app_net



