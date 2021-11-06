#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO draw2d  :
      virtual public ::draw2d::draw2d
   {
   public:




      draw2d();
      virtual ~draw2d();


      virtual ::e_status initialize(::object * pobject) override;

      virtual ::e_status process_init() override;

      virtual ::e_status init() override;
      virtual ::e_status init1() override;

      virtual ::e_status term() override;

      virtual ::e_status destroy() override;


   };


} // namespace draw2d


