#pragma once


namespace user
{


   class CLASS_DECL_AURA simple_view :
      virtual public ::user::impact
   {
   public:

      

      class text
      {
      public:


         string               m_strText;
         ::draw2d::font_pointer    m_font;
         point                m_point;
         ::color              m_color;


      };


      array < text >       m_texta;


      simple_view();
      virtual ~simple_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;

      virtual void update(::update * pupdate) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };



} // namespace user




