#pragma once


namespace gpu
{


   class CLASS_DECL_AURA buffer :
      virtual public ::object
   {
   public:


      ::image_pointer         m_pimage;


      buffer();
      ~buffer() override;

      virtual void gpu_read();
      virtual void gpu_write();
      

   };


} // namespace gpu



