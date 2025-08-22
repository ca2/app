// graphics3d/include/IRenderSystem.h
#pragma once

namespace graphics3d
{

   class render_system :
      virtual public ::particle
   {
   public:


      ::pointer<::graphics3d::engine> m_pengine;


      ::pointer<::gpu::shader> m_pshader;


      render_system();


      ~render_system() override;


      virtual void on_prepare();


      virtual void on_update(IFrame *pframe);


      virtual void on_render(IFrame *pframe);


   };


} // namespace graphics3d
