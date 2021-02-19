#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_AURA draw2d  :
      virtual public ::draw2d::draw2d
   {
   public:




      draw2d();
      virtual ~draw2d();


      virtual ::e_status initialize(::layered * pobjectContext) override;

      virtual ::e_status process_init() override;

      virtual ::e_status init() override;
      virtual ::e_status init1() override;

      virtual void term() override;

      virtual void finalize() override;


   };


} // namespace draw2d


