#pragma once


namespace user
{


   class CLASS_DECL_AURA progress :
      virtual public ::user::interaction
   {
   public:


      scalar_base * m_pscalar;

      double         m_dRate;



      progress();
      virtual ~progress();


      void assert_valid() const override;
      void dump(dump_context & dumpcontext) const override;

      void install_message_routing(::channel * pchannel) override;


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics) override;


   };



} // namespace user




