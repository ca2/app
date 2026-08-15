// Created by camilo on 2026-07-28 01:07 <3ThomasBorregaardSørensen!! Mummi!! Bilbo!!
#include "platform.h"
#include "fence.h"
#include "texture.h"
#include "texture_synchronization.h"


namespace gpu
{


   texture_synchronization::texture_synchronization() {}


   texture_synchronization::~texture_synchronization() {}


   ::gpu::fence *texture_synchronization::in_flight_fence()
   {

      if (!m_pgpufenceInFlight)
      {

         //::cast<::gpu_vulkan::context> pcontext = m_ptexture->m_pgpucontext;
         auto pcontext = m_ptexture->m_pgpucontext;

         constructø(m_pgpufenceInFlight);

         m_pgpufenceInFlight->initialize_gpu_fence(pcontext->m_pgpudevice, true);

         // return m_pgpufenceInFlight;

         // VkFenceCreateInfo fenceInfo = {};
         // fenceInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
         // fenceInfo.flags = VK_FENCE_CREATE_SIGNALED_BIT;

         // if (vkCreateFence(pcontext->logicalDevice(), &fenceInfo, nullptr, &m_vkfenceInFlight2) != VK_SUCCESS)
         //{

         //   throw ::exception(error_failed, "failed to create fence!");
         //}
      }

      // return m_vkfenceInFlight2;

      return m_pgpufenceInFlight;
   }


} // namespace gpu



