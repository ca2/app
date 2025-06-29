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

      bool m_bClosed;
      enum_state m_estate = e_state_none;

      ::pointer < ::gpu::render_target > m_pgpurendertarget;



      command_buffer();
      ~command_buffer() override;


      virtual void initialize_command_buffer(::gpu::render_target* pgpurendertarget);


      virtual void submit_command_buffer(::gpu::layer * pgpulayer);

      virtual void wait_commands_to_execute();

      virtual void reset();


   };


} // namespace gpu



