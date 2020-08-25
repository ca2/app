#pragma once


namespace user
{


   class CLASS_DECL_AURA controller :
      virtual public channel
   {
   public:


      controller();
      virtual ~controller();


      virtual void dump(dump_context&) const override;
      virtual void assert_valid() const override;



   };


} // namespace user



