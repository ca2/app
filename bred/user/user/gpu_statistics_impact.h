// Created by camilo on 2026-09-05 03:22 <3ThomasBorregaardSørensen!! Mummi!! bilbo!!
#pragma once


#include "apex/platform/app_consumer.h"
#include "berg/user/user/show.h"
#include "bred/platform/application.h"
#include "bred/platform/fps_counter.h"


namespace user
{


   class CLASS_DECL_BRED gpu_statistics_impact :
      virtual public ::app_consumer < ::bred::application, ::user::show <::user::box> >
   {
   public:


      ::write_text::font_pointer       m_pfontThomasBS_;
      string                           m_strFont1;
      int                              m_iSequence;
      fps_counter                      m_fpscounter;


      gpu_statistics_impact();
      ~gpu_statistics_impact() override;


#ifdef _DEBUG

      virtual long long increment_reference_count() override;
      virtual long long decrement_reference_count() override;

#endif

      //::pointer < ::graphics3d::application > start_graphics3d_application() override;


      virtual void install_message_routing(::channel * psender) override;

      virtual void _001OnClip(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      virtual void _001OnDraw(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      void handle(::topic * ptopic, ::handler_context * phandlercontext) override;

      document * get_document();


      //s::block global_ubo_block() override;

      void on_layout(::draw2d::graphics_pointer & pdraw2dgraphics) override;

      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);

      bool on_click(::item * pitem, ::user::mouse * pmouse) override;


   };




} // namespace user


