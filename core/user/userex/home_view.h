#pragma once


namespace userex
{


   class CLASS_DECL_CORE home_view :
      virtual public ::user::impact
   {
   public:


      class CLASS_DECL_CORE item
      {

      public: 

         string            m_strName;
         ::file::path      m_path;

      };


      home_view();
      virtual ~home_view();


      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;

      virtual void install_message_routing(::channel * pchannel) override;

      virtual void update(::update * pupdate) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnShowWindow);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      virtual void on_mouse(const ::point & point);
      virtual void rebuild_luminance();

//      virtual color get_color();
//      virtual void set_color(color color);

   };


} // namespace userex




