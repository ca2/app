#pragma once


namespace user
{


   class CLASS_DECL_BASE simple_impact :
      virtual public ::user::impact
   {
   public:

      

      class text
      {
      public:


         string               m_strText;
         ::write_text::font_pointer    m_pfont;
         point_i32                m_point;
         ::color::color              m_color;


      };


      array < text >       m_texta;


      simple_impact();
      virtual ~simple_impact();


      void assert_ok() const override;
      void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::topic * ptopic, ::context * pcontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };



} // namespace user




