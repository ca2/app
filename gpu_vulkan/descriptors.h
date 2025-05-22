#pragma once


#include "context.h"
#include "acme/prototype/collection/map.h"

//// std
//#include <memory>
//#include <unordered_map>
//#include <vector>


namespace gpu_vulkan
{


   class CLASS_DECL_GPU_VULKAN set_descriptor_layout :
      virtual public ::particle
   {
   public:
      class Builder
      {
      public:
         Builder(context * pvkcDevice) : m_pcontext{ pvkcDevice } {}

         Builder & addBinding(
             uint32_t binding,
             VkDescriptorType descriptorType,
             VkShaderStageFlags stageFlags,
             uint32_t count = 1);
         ::pointer<set_descriptor_layout> build() const;

      private:
         ::pointer < context > m_pcontext;
         ::map < unsigned int, VkDescriptorSetLayoutBinding> bindings{};
      };

      set_descriptor_layout(
          context * pvkcdevice, ::map<unsigned int, VkDescriptorSetLayoutBinding> bindings);
      ~set_descriptor_layout();

      VkDescriptorSetLayout getDescriptorSetLayout() const { return descriptorSetLayout; }

      ::pointer < context > m_pcontext;
      VkDescriptorSetLayout descriptorSetLayout;
      ::map<unsigned int, VkDescriptorSetLayoutBinding> bindings;

   };


   class CLASS_DECL_GPU_VULKAN descriptor_pool :
      virtual public ::particle
   {
   public:


      class Builder :
         virtual public ::particle
      {
      public:

         //Builder(context& m_pcontext) : m_pcontext{ m_pcontext } {}
         Builder() {}
         void initialize_builder(::gpu::context * pcontext)
         {
            m_pcontext = pcontext;

         }
         Builder & addPoolSize(VkDescriptorType descriptorType, uint32_t count);
         Builder & setPoolFlags(VkDescriptorPoolCreateFlags flags);
         Builder & setMaxSets(uint32_t count);
         ::pointer<descriptor_pool> build() const;

      private:
         ::pointer < context > m_pcontext;
         ::array<VkDescriptorPoolSize> poolSizes{};
         uint32_t maxSets = 1000;
         VkDescriptorPoolCreateFlags poolFlags = 0;
      };

      descriptor_pool(
          context * pvkcdevice,
          uint32_t maxSets,
          VkDescriptorPoolCreateFlags poolFlags,
          const ::array<VkDescriptorPoolSize> & poolSizes);
      ~descriptor_pool();
      descriptor_pool(const descriptor_pool &) = delete;
      descriptor_pool & operator=(const descriptor_pool &) = delete;

      bool allocateDescriptor(
          const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet & descriptor) const;

      void freeDescriptors(::array<VkDescriptorSet> & descriptors) const;

      void resetPool();

      ::pointer < context > m_pcontext;
      VkDescriptorPool descriptorPool;

   };


   class CLASS_DECL_GPU_VULKAN descriptor_writer
   {
   public:
      descriptor_writer(set_descriptor_layout & setLayout, descriptor_pool & pool);

      descriptor_writer & writeBuffer(uint32_t binding, VkDescriptorBufferInfo * bufferInfo);
      descriptor_writer & writeImage(uint32_t binding, VkDescriptorImageInfo * imageInfo);

      bool build(VkDescriptorSet & set);
      void overwrite(VkDescriptorSet & set);

      set_descriptor_layout & setLayout;
      descriptor_pool & pool;
      ::array<VkWriteDescriptorSet> writes;
   };


} // namespace graphics3d_vulkan



