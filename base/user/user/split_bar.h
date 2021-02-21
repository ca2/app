#pragma once


namespace user
{

   class split_layout;

   class CLASS_DECL_BASE split_bar :
      public ::user::interaction
   {
   public:

      


      index                         m_iIndex;
      split_layout *                m_pparent;
      u32                           m_dwPosition;
      double                        m_dRate;
      double                        m_dMinimumRate;
      double                        m_dMaximumRate;
      u32                           m_dwMaxPosition;



      split_bar();
      virtual ~split_bar();


      void install_message_routing(::channel * pchannel);


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


      //using ::user::interaction::create_interaction;
      //virtual bool create_child(split_layout * psplitlayoutParent);
      virtual bool pre_create_window(::user::system * pusersystem);


      DECL_GEN_SIGNAL(on_message_left_button_down);
      DECL_GEN_SIGNAL(on_message_left_button_up);
      DECL_GEN_SIGNAL(_001OnMouseMove);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace user


