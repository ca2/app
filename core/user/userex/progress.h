#pragma once


#include "base/user/user/impact.h"
#include "apex/progress/real.h"


namespace userex
{


   class progress_impact;


   class CLASS_DECL_CORE progress_control :
      virtual public ::progress::real
   {
   public:


      ::user::document *    m_pdocument;
      progress_impact *       m_pimpact;


      progress_control();
      ~progress_control() override;

#ifdef _DEBUG
      huge_integer decrement_reference_count() override;
#endif


      void create_progress();
      void set_progress_title(const ::string & pszTitle);
      void close_progress() override;


      void redraw() override;

      virtual void defer_show(::user::interaction * puiParent, const ::string & pszTitle, ::collection::count iStepCount = 0);


   };


   class CLASS_DECL_CORE progress_impact :
      virtual public user::impact,
      virtual public scalar
   {
   public:

      
      
      ::pointer<::progress::real>       m_pprogressreal;

      ::pointer<::user::progress>  m_pprogress;

      ::int_rectangle                        m_rectangleStatus;


      progress_impact();
      ~progress_impact() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;
#ifdef _DEBUG
      virtual huge_integer increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      virtual huge_integer decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }
#endif
      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      virtual void on_layout(::draw2d::graphics_pointer & pgraphics) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;

      virtual void _001OnTimer(::timer* ptimer) override;

   };


} // namespace tranquillum

