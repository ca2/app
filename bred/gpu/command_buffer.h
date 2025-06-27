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

      bool m_bClosed;


      command_buffer();
      ~command_buffer() override;


      virtual void submit_command_buffer();

      virtual void wait_commands_to_execute();

      virtual void reset();


   };


} // namespace gpu



