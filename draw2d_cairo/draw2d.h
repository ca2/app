#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO draw2d  :
      virtual public ::draw2d::draw2d
   {
   public:




      draw2d();
      virtual ~draw2d();


      virtual void initialize(::object * pobject) override;

      virtual void process_init() override;

      virtual void init() override;
      virtual void init1() override;

      virtual void term() override;

      virtual void destroy() override;


   };


} // namespace draw2d


