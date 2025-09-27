// From github:/tristancalderbank/OpenGL-PBR-Renderer/HDRTexture.h by
// camilo on 2025-09-26 21:14 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu
{


   /**
    * A texture loaded from a .hdr file.
    */
   class HDRTexture :
      virtual public particle
   {
   public:


      unsigned int mId;


      HDRTexture();


      ~HDRTexture() override;


      virtual void initialize_HDRTexture(const std::string &path);


      //unsigned int getId();

   };


} // namespace gpu
