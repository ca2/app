#pragma once


namespace userex
{


   class progress_view;


   class CLASS_DECL_CORE progress_control :
      virtual public ::progress_control
   {
   public:


      ::user::document *    m_pdocument;
      progress_view *       m_pview;


      progress_control();
      virtual ~progress_control();

#ifdef DEBUG
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override;
#endif


      void create_progress();
      void set_progress_title(const char * pszTitle);
      virtual void close_progress() override;


      virtual void redraw() override;

      virtual void defer_show(::user::interaction * puiParent, const char* pszTitle, ::count iStepCount = 0);


   };


   class CLASS_DECL_CORE progress_view :
      virtual public user::impact,
      virtual public double_scalar
   {
   public:

      
      
      ::progress_control *          m_pprogresscontrol;

      __pointer(::user::progress)   m_pprogress;

      ::rect                        m_rectStatus;


      progress_view();
      virtual ~progress_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
#ifdef DEBUG
      virtual i64 add_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::add_ref(OBJ_REF_DBG_ARGS);
      }
      virtual i64 dec_ref(OBJ_REF_DBG_PARAMS) override
      {
         return ::object::dec_ref(OBJ_REF_DBG_ARGS);
      }
#endif
      virtual void install_message_routing(::channel * pchannel) override;

      virtual void on_apply(::action * paction) override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnTimer(::timer* ptimer) override;

   };


} // namespace tranquillum

