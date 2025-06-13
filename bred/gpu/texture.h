// Created by camilo on 2025-06-12 21:04 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class CLASS_DECL_BRED texture :
      virtual public ::particle 
   {
   public:


      ::int_size m_size;


      texture();
      ~texture() override;

      
      virtual void initialize_gpu_texture(const ::int_size& size);


   };


} // namespace gpu



