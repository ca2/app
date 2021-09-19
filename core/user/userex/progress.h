#pragma once


namespace userex
{


   class progress_view;


   class CLASS_DECL_CORE progress_control :
      virtual public ::progress::real
   {
   public:


      ::user::document *    m_pdocument;
      progress_view *       m_pimpact;


      progress_control();
      virtual ~progress_control();

#ifdef _DEBUG
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override;
#endif


      void create_progress();
      void set_progress_title(const ::string & pszTitle);
      virtual void close_progress() override;


      virtual void redraw() override;

      virtual void defer_show(::user::interaction * puiParent, const ::string & pszTitle, ::count iStepCount = 0);


   };


   class CLASS_DECL_CORE progress_view :
      virtual public user::impact,
      virtual public double_scalar
   {
   public:

      
      
      __pointer(::progress::real)        m_pprogressreal;

      __pointer(::user::progress)   m_pprogress;

      ::rectangle_i32                        m_rectStatus;


      progress_view();
      virtual ~progress_view();


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;
#ifdef _DEBUG
      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {
         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);
      }
#endif
      virtual void install_message_routing(::channel * pchannel) override;

      virtual void handle(::subject * psubject, ::context * pcontext) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnTimer(::timer* ptimer) override;

   };


} // namespace tranquillum

