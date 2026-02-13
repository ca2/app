// Created by camilo on 2025-12-09 <3ThomasBorregaardSørensen!!
#pragma once


namespace gpu
{


   class texture_flags
   {
   public:

      bool m_bWithDepth;
      bool m_bRenderTarget;
      bool m_bShaderResource;
      bool m_bTransferSource;
      bool m_bTransferTarget;
      bool m_bCpuRead;

      texture_flags(const texture_flags &flags) = default;
      texture_flags(bool bWithDepth = false, bool bRenderTarget = false, bool bShaderResource = false,
            bool bTransferSource = false, bool bTransferTarget = false, bool bCpuRead = false) :
          m_bWithDepth(bWithDepth), m_bRenderTarget(bRenderTarget), m_bShaderResource(bShaderResource),
          m_bTransferSource(bTransferSource), m_bTransferTarget(bTransferTarget), m_bCpuRead(bCpuRead)
      {
      }

      bool operator==(const texture_flags &flags) const = default;

      texture_flags &operator=(const texture_flags &flags) = default;
   };



} // namespace gpu



