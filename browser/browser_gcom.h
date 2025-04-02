#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER gcom :
      virtual public impact_base,
      virtual public ::backimpact::user::impact
   {
   public:


      ::image::image_pointer        m_pimageBk;


      gcom(::particle * pparticle);
      virtual ~gcom();


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;


      void install_message_routing(::channel * pchannel) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      void handle(::topic * ptopic, ::handler_context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual long long increment_reference_count()
      {
         return ::object::increment_reference_count();
      }
      virtual long long decrement_reference_count()
      {
         return ::object::decrement_reference_count();
      }

   };


} // namespace browser





















