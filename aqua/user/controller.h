#pragma once


namespace user
{


   class CLASS_DECL_AQUA controller :
      virtual public channel,
      virtual public ::manager
   {
   public:


      controller();
      virtual ~controller();


      virtual void dump(dump_context&) const override;
      void assert_valid() const override;


      virtual ::user::interaction* impact_at(::index iImpact) const;
      virtual ::count impact_count() const;


   };


} // namespace user



