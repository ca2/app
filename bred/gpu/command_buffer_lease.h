// Created by camilo on 2026-09-01 01:12 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#pragma once


namespace gpu
{

   class CLASS_DECL_BRED command_buffer_lease
   {
   protected:

      friend class gpu::context;
      ::pointer<::gpu::command_buffer> m_pgpucommandbuffer;
      command_buffer_lease(::pointer<::gpu::command_buffer> pgpucommandbuffer);
   public:


      command_buffer_lease(command_buffer_lease && commandbufferlease);
      command_buffer_lease(const command_buffer_lease&)= delete;
      ~command_buffer_lease() noexcept;
      //void initialize_command_buffer_lease(::gpu::context * pgpucontext, ::gpu::command_buffer * pgpucmdbuffer);  

      /// Submit the recorded command buffer and consume this lease.
      ///
      /// This must be called explicitly after recording has completed
      /// successfully. If submission throws, the lease is still consumed and
      /// its destructor will not attempt a second submission.
      void commit();

      /// Discard the recorded command buffer without submitting it.
      ///
      /// Destruction has the same behavior, which makes exception unwinding
      /// safe: a partially recorded command buffer is never submitted.
      void cancel() noexcept;

      bool is_pending() const { return m_pgpucommandbuffer.is_set(); }

      ::gpu::command_buffer * operator->() { return m_pgpucommandbuffer; }

      operator ::gpu::command_buffer * () { return m_pgpucommandbuffer; }

   };


} // namespace gpu
