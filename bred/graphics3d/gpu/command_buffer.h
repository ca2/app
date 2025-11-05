// From gpu_directx12::commandbuffer by
// camilo on 2025-06-26 03:46 <3ThomasBorregaardSørensen!!
// Created by camilo on 2025-06-23 00:14 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED command_buffer :
      virtual public ::particle
   {
   public:


      enum enum_state
      {
         e_state_none,
         e_state_recording,
         e_state_submitted,
      };

      bool                                m_bClosed;
      enum_state                          m_estate = e_state_none;
      enum_command_buffer                 m_ecommandbuffer;
      ::pointer < ::gpu::render_target >  m_pgpurendertarget;
      ::pointer < ::gpu::queue >          m_pgpuqueue;
      bool                                m_bLoadingCommandBuffer;
      ::collection::index                 m_iFrameIndex;
      ::string                            m_strAnnotation;
      ::pointer_array < ::particle >      m_particleaHold;
      ::graphics3d::render_system *       m_prendersystem = nullptr;


      command_buffer();
      ~command_buffer() override;


      virtual void initialize_command_buffer(::gpu::render_target* pgpurendertarget, ::gpu::queue * pqueue, enum_command_buffer ecommandbuffer);

      virtual void begin_command_buffer(bool bOneTime);

      virtual void submit_command_buffer(::gpu::layer * pgpulayer);

      virtual void wait_commands_to_execute();

      virtual void set_viewport(const ::int_rectangle& rectangle);

      virtual void set_scissor(const ::int_rectangle& rectangle);

      virtual void reset();

      //virtual void set_primitive_topology_triangle_strip();

      virtual void draw(int a);

      virtual void draw_vertexes(int iVertexCount);
      virtual void draw_indexes(int iIndexCount);


      virtual void draw(::gpu::pixmap * ppixmap);

      virtual void set_render_target();


   };


   struct CLASS_DECL_BRED scoped_command_buffer
   {

      ::pointer < ::gpu::command_buffer > m_pcommandbufferOut;
      ::pointer < ::gpu::command_buffer > m_pcommandbufferIn;

      scoped_command_buffer(::gpu::command_buffer* pcommandbufferIn);
      ~scoped_command_buffer();

   };


   CLASS_DECL_BRED ::gpu::command_buffer *current_command_buffer();


} // namespace gpu



