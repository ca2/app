#pragma once


#include "aura/user/user/box.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/immersion_layer.h"
#include "bred/graphics3d/key_map.h"
#include "bred/graphics3d/types.h"
#include "apex/platform/app_consumer.h"
#include "apex/platform/application.h"


namespace user
{

  

   class CLASS_DECL_BRED graphics3d :
      virtual public ::app_consumer < ::aura::application, ::user::box>
   {
   public:

      //memory m_memory;
      //int m_i;

      ::graphics3d::enum_mouse                  m_emouse;
      ::graphics3d::enum_keyboard               m_ekeyboard;
      //bool                                      m_bAbsoluteMousePosition;

      ::pointer < ::graphics3d::engine >			m_pengine;

      ::pointer < ::graphics3d::key_map >			m_pkeymap;
      //::task_pointer                            m_ptaskEngine;
      //::pointer < ::image::target >             m_pimagetarget;

      //bool		m_bShouldClose;
      int		m_iWidth;
      int		m_iHeight;
      bool		m_bFrameBufferResized;




      graphics3d();
      ~graphics3d() override;

//      // void assert_ok() const override;
//      // void dump(dump_context & dumpgpucontext) const override;
      //::int_size size() override;

      //virtual ::block global_ubo_block();

      void install_message_routing(::channel * pchannel) override;


      virtual void on_mouse_move(const int_point& point);
      virtual void on_mouse_out();

      virtual ::user::enum_key_state get_key_state(::user::e_key ekey) ;
      void _001OnNcClip(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;


      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnNcPostDraw(::draw2d::graphics_pointer & pgraphics) override;


      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      //::user::document * get_document();



      //virtual ::pointer < ::graphics3d::application > start_graphics3d_application();


      void on_layout(::draw2d::graphics_pointer & pgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);
      DECLARE_MESSAGE_HANDLER(on_message_key_down);
      DECLARE_MESSAGE_HANDLER(on_message_key_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_move);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_down);
      DECLARE_MESSAGE_HANDLER(on_message_left_button_up);
      DECLARE_MESSAGE_HANDLER(on_message_mouse_leave);

      void on_timer(::timer * ptimer) override;

      //void reset_mouse_last_position();


      long long increment_reference_count() override
      {
         return ::object::increment_reference_count();
      }
      long long decrement_reference_count() override
      {
         return ::object::decrement_reference_count();
      }
      bool keyboard_focus_is_focusable() override;


      //virtual bool is_absolute_mouse_position();

      //virtual bool shouldClose();
      //virtual ::int_size size();
      virtual bool wasWindowResized();
      virtual void resetWindowResizedFlag();
//
  //    virtual ::user::enum_key_state get_key_state(::user::e_key ekey);

      //virtual void initWindow();


      virtual void defer_initialize_engine(const ::int_rectangle & rectangle);

      virtual ::pointer < ::prodevian::immersion > create_immersion();

      virtual void on_load_engine();




      virtual ::pointer < ::graphics3d::key_map > get_default_key_map();
      virtual float getAspectRatio();

      virtual void prepare_mouse_input();
      virtual void process_mouse_input();

      virtual void process_keyboard_input();


   };


} // namespace graphics3d



