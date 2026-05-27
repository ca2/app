// Created by camilo on 2025-12-09 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{

   class texture_attributes
   {
   public:

      ::i32_rectangle      m_rectangleTarget;
      ::i32                  m_iBitsPerChannel = -1;
      ::i32                  m_iChannelCount = -1;
      ::i32                  m_iSrgb = -1;
      ::i32                  m_iFloat = -1;
      enum_texture         m_etexture = e_texture_none;
      ::i32                  m_iLayerCount = -1;
      ::i32                  m_iMipCount = -1;

      texture_attributes() = default;
      texture_attributes(const texture_attributes &texture_attributes) = default;
      texture_attributes(const ::i32_rectangle &rectangle, ::i32 iBitsPerChannel = 8, ::i32 iChannelCount = 4, ::i32 iSrgb= 0,::i32 iFloat = 0,
                 enum_texture etexture = e_texture_image, ::i32 iLayerCount = 1, ::i32 iMipCount = 1) :
          m_rectangleTarget(rectangle), m_iBitsPerChannel(iBitsPerChannel), m_iChannelCount(iChannelCount),
          m_iSrgb(iSrgb), m_iFloat(iFloat), m_etexture(etexture), m_iLayerCount(iLayerCount), m_iMipCount(iMipCount)
      {
      }


      void set_cubemap(::i32 iMipCount = 1)
      {

         m_etexture = e_texture_cube_map;
         m_iLayerCount = 6;
         m_iMipCount = iMipCount;

      }


      ::i32 maximum_mip_count() const
      {

         return (::i32) floor(log2(m_rectangleTarget.size().maximum())) + 1;

      }


      void set_cubemap_all_mips()
      {

         set_cubemap(maximum_mip_count());

      }


      bool operator==(const texture_attributes &texture_attributes) const = default;

      texture_attributes &operator=(const texture_attributes &texture_attributes) = default;

   };

   
} // namespace gpu



