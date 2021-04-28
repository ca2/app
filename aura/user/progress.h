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


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      void install_message_routing(::channel * pchannel);


      virtual void _001OnDraw(::draw2d::graphics_pointer & pgraphics);


   };



} // namespace user




