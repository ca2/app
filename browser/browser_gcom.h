#pragma once


namespace browser
{


   class CLASS_DECL_APP_BROWSER gcom :
      virtual public impact_base,
      virtual public ::backview::user::impact
   {
   public:


      ::image_pointer        m_pimageBk;


      gcom(::layered * pobjectContext);
      virtual ~gcom();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual void install_message_routing(::channel * pchannel);

      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_subject(::promise::subject * psubject, ::promise::context * pcontext) override;

      ::user::document * get_document();

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

   };


} // namespace browser





















