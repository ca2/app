// Created by camilo on 2025-06-05 01:53 <3ThomasBorregaardSørensen!!
#pragma once


namespace draw2d_gpu
{


   class CLASS_DECL_BRED end_draw :
      virtual public particle
   {
   public:


      end_draw();
      ~end_draw() override;


      virtual void initialize_end_draw(::gpu::graphics* pdraw2dgraphics);


      virtual void endDraw(::user::interaction* puserinteraction, ::gpu::renderer* prendererSrc);


   };


} // namespace draw2d_gpu



