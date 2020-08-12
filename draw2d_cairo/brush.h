#pragma once


namespace draw2d_cairo
{


   class CLASS_DECL_DRAW2D_CAIRO brush :
      virtual public ::draw2d::brush
   {
   public:



      brush();
      virtual ~brush();


      virtual bool create(::draw2d::graphics * pgraphics);
      virtual void destroy();


      virtual void dump(dump_context & dumpcontext) const;


   };


} // namespace draw2d_cairo

