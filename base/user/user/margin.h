#pragma once


#include "aura/user/user/interaction.h"


namespace user
{


   class CLASS_DECL_BASE margin_base:
      virtual public ::user::interaction
   {
   public:


      ::int_rectangle      m_rectangleMargin;


      margin_base();
      virtual ~margin_base();


      virtual void get_margin_rect(::int_rectangle * prectMargin) override;



   };


   template < class BASE >
   class margin:
      virtual public margin_base,
      virtual public BASE
   {
   public:

      margin()
      {
      }

      virtual ~margin()
      {
      }

      virtual void install_message_routing(::channel * pchannel) override
      {

         ::user::margin_base::install_message_routing(pchannel);
         BASE::install_message_routing(pchannel);

      }

//      void screen_to_client(::int_rectangle * prectangle)

      //    {

      //     BASE::screen_to_client(prectangle);


      /*prectangle->left()   -= m_rectangleMargin.left();

      prectangle->right()  -= m_rectangleMargin.left();

      prectangle->top()    -= m_rectangleMargin.top();

      prectangle->bottom() -= m_rectangleMargin.top();*/


      // }

      virtual ::double_point get_context_offset(::user::enum_layout elayout = ::user::e_layout_sketch) override
      {

         auto pointOffset = BASE::get_context_offset(elayout);

         pointOffset += m_rectangleMargin.top_left();

         return pointOffset;

      }


      //void set_context_offset(::draw2d::graphics_pointer & pgraphics, int x,int y) override
      //{

      //   BASE::set_context_offset(pgraphics, x - m_rectangleMargin.left(), y - m_rectangleMargin.top());

      //}

      
      void set_context_offset(const ::double_point & point, ::user::enum_layout elayout = e_layout_sketch) override
      {

         BASE::set_context_offset(point - m_rectangleMargin.top_left(), elayout);

      }

      virtual ::double_size get_total_size(::user::enum_layout elayout = ::user::e_layout_sketch) override
      {

         auto s = BASE::get_total_size();

         return decltype(s)(s.cx() + m_rectangleMargin.left() + m_rectangleMargin.right(),s.cy() + m_rectangleMargin.top() + m_rectangleMargin.bottom());

      }

   };

} // namespace user



