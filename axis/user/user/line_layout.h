#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_AXIS line_layout :
      virtual public ::user::interaction
   {
   public:

      enum_orientation m_eorientation = e_orientation_none;

      int m_iPadding = 2;


      line_layout();
      ~line_layout() override;


      virtual i64 increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {

         return ::object::increment_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }


      virtual i64 decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_PARAMETERS) override
      {

         return ::object::decrement_reference_count(OBJECT_REFERENCE_COUNT_DEBUG_ARGS);

      }

      
      void install_message_routing(::channel * pchannel) override;

      void handle(::topic * ptopic, ::context * pcontext) override;

      
      
      void on_perform_top_down_layout(::draw2d::graphics_pointer & pgraphics) override;

      bool on_perform_layout(::draw2d::graphics_pointer & pgraphics) override;
      
      
      DECLARE_MESSAGE_HANDLER(on_message_show_window);
      DECLARE_MESSAGE_HANDLER(on_message_create);
      DECLARE_MESSAGE_HANDLER(on_message_destroy);


      void _001OnNcClip(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnNcDraw(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnClip(::draw2d::graphics_pointer & pgraphics) override;
      void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;
      
      

   };


} // namespace user


