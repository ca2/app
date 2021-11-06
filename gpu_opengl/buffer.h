#pragma once


namespace opengl
{


   class CLASS_DECL_GPU_OPENGL buffer :
      virtual public ::gpu::buffer
   {
   public:

      

      buffer();
      virtual ~buffer();

      virtual void gpu_read() override;
      virtual void gpu_write() override;
      


   };


} // namespace opengl



