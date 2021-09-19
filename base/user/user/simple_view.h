#pragma once


namespace user
{


   class CLASS_DECL_BASE simple_view :
      virtual public ::user::impact
   {
   public:

      

      class text
      {
      public:


         string               m_strText;
         ::write_text::font_pointer    m_font;
         point_i32                m_point;
         ::color::color              m_color;


      };


      array < text >       m_texta;


      simple_view();
      virtual ~simple_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };



} // namespace user




