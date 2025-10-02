// From github:/tristancalderbank/OpenGL-PBR-Renderer/hdri_cube.h by
// camilo on 2025-09-26 19:54 <3ThomasBorregaardSorensen!!
#pragma once
// Maybe graphics3d::skybox can be used (it has cube mode and texture (that can be hdr))

 // #include <vector>
 // #include <string>
 // #include <iostream>
 //
 // //#include "stb_image/stb_image.h"
 //
 // #include "gpu/cube.h"
 // #include "gpu/hdr_texture.h"
 // #include "bred/gpu/shader.h"
 //

 #include  "bred/graphics3d/renderable.h"


 namespace gpu
 {


    namespace ibl
    {

       /**
        * A unit cube model textured with an equirectangular HDR image.
        */
       class CLASS_DECL_GPU hdri_cube
          :
          virtual public ::graphics3d::renderable
       {
       public:


          ::pointer<::gpu::cube> m_pcube;
          //::pointer < ::gpu::hdr_texture >  m_phdrtexture;

          //A texture loaded from a .hdr file.
          ::pointer < ::gpu::texture >  m_ptextureHdr;

          hdri_cube();


          ~hdri_cube() override;


          void draw(::gpu::command_buffer *pcommandbuffer) override;


          virtual void initialize_hdri_cube_with_hdr_on_memory(::gpu::renderer * pgpurenderer, const ::block & block);

       };


    } // namespace ibl


 } // namespace gpu
