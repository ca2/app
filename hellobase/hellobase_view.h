#pragma once


namespace hellobase
{


   class CLASS_DECL_APP_HELLO_BASE view :
      virtual public impact_base
   {
   public:




      string                  m_strServer;
      ::image_pointer        m_pimageAi1;
      ::image_pointer        m_pimageAi2;

      string                  m_strImage;
      ::image_pointer        m_pimageColor;

      bool                    m_bOkPending;


      bool                    m_bHelloLayoutOn001Layout;
      bool                    m_b001LayoutIgnoreEmpty;


      view(::object * pobject);
      virtual ~view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual i64 add_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS)
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }

      virtual void install_message_routing(::channel * pchannel);

      virtual void _006OnDraw(::draw2d::graphics_pointer & pgraphics);

      virtual void on_subject(::subject::subject * psubject, ::subject::context * pcontext) override;

      ::user::document * get_document();



      virtual void on_layout(::draw2d::graphics_pointer & pgraphics);

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(_001OnDestroy);

      virtual string get_hellobase();

      virtual string get_processed_hellobase();



      virtual void defer_check_on_draw_layout();
      virtual void on_draw_image_layer(::draw2d::graphics_pointer & pgraphics);

   };


} // namespace hellobase





















