// Created by camilo on 2025-12-09 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{

   class texture_attributes
   {
   public:

      ::int_rectangle      m_rectangleTarget;
      int                  m_iBitsPerChannel = -1;
      int                  m_iChannelCount = -1;
      int                  m_iSrgb = -1;
      int                  m_iFloat = -1;
      enum_texture         m_etexture = e_texture_none;
      int                  m_iLayerCount = -1;
      int                  m_iMipCount = -1;

      texture_attributes() = default;
      texture_attributes(const texture_attributes &texture_attributes) = default;
      texture_attributes(const ::int_rectangle &rectangle, int iBitsPerChannel = 8, int iChannelCount = 4, int iSrgb= 0,int iFloat = 0,
                 enum_texture etexture = e_texture_image, int iLayerCount = 1, int iMipCount = 1) :
          m_rectangleTarget(rectangle), m_iBitsPerChannel(iBitsPerChannel), m_iChannelCount(iChannelCount),
          m_iSrgb(iSrgb), m_iFloat(iFloat), m_etexture(etexture), m_iLayerCount(iLayerCount), m_iMipCount(iMipCount)
      {
      }


      void set_cubemap(int iMipCount = 1)
      {

         m_etexture = e_texture_cube_map;
         m_iLayerCount = 6;
         m_iMipCount = iMipCount;

      }


      int maximum_mip_count() const
      {

         return floor(log2(m_rectangleTarget.size().maximum())) + 1;

      }


      void set_cubemap_all_mips()
      {

         set_cubemap(maximum_mip_count());

      }


      bool operator==(const texture_attributes &texture_attributes) const = default;

      texture_attributes &operator=(const texture_attributes &texture_attributes) = default;

   };

   
} // namespace gpu



