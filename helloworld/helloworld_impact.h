#pragma once


namespace helloworld
{


   class CLASS_DECL_APP_HELLOWORLD impact :
      virtual public hellobase::impact,
      virtual public hellobase::impact_base
   {
   public:




      string                  m_strServer;
      ::image::image_pointer        m_pimageAi1;
      ::image::image_pointer        m_pimageAi2;

      string                  m_strImage;
      ::image::image_pointer        m_pimageColor;

      bool                    m_bOkPending;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;


      impact(::particle * pparticle);
      virtual ~impact();

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      virtual huge_integer increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual huge_integer decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

      void install_message_routing(::channel * pchannel) override;

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      void handle(::topic * ptopic, ::context * pcontext) override;

      ::user::document * get_document();



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual string get_helloworld();

      virtual string get_processed_helloworld();



      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace helloworld





















