#pragma once


#include "interaction.h"
#include "acme/primitive/mathematics/scalar.h"


namespace user
{


   class CLASS_DECL_AURA progress :
      virtual public ::user::interaction
   {
   public:


      scalar         m_scalar;

      double         m_dRate;



      progress();
      ~progress() override;


//      // void assert_ok() const override;
//      // void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };



} // namespace user




