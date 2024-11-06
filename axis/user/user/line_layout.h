#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_AXIS line_layout :
      virtual public ::user::interaction
   {
   public:

      enum enum_align_relative
      {
         e_align_relative_none = 0,
         e_align_relative_near = 1,
         e_align_relative_middle = 2,
         e_align_relative_far = 4,
         e_align_relative_base_bottom_line = 8,
      };

      enum_orientation        m_eorientation = e_orientation_none;
      enum_align_relative     m_ealignrelativeOrthogonal;

      int m_iPadding = 2;


      line_layout();
      ~line_layout() override;


      virtual huge_integer increment_reference_count() override
      {

         return ::object::increment_reference_count();

      }


      virtual huge_integer decrement_reference_count() override
      {

         return ::object::decrement_reference_count();

      }

      virtual void create_line_layout(::user::interaction* puserinteractionParent, enum_orientation eorientation);
      
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



