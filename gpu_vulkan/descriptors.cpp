#include "framework.h"
#include "descriptors.h"

// std
#include <cassert>
#include <stdexcept>


namespace gpu_vulkan
{


   // *************** Descriptor Set Layout Builder *********************

   set_descriptor_layout::Builder & set_descriptor_layout::Builder::addBinding(
       uint32_t binding,
       VkDescriptorType descriptorType,
       VkShaderStageFlags stageFlags,
       uint32_t count) {
      assert(bindings.count(binding) == 0 && "Binding already in use");
      VkDescriptorSetLayoutBinding layoutBinding{};
      layoutBinding.binding = binding;
      layoutBinding.descriptorType = descriptorType;
      layoutBinding.descriptorCount = count;
      layoutBinding.stageFlags = stageFlags;
      bindings[binding] = layoutBinding;
      return *this;
   }

   ::pointer<set_descriptor_layout> set_descriptor_layout::Builder::build() const
   {
      auto pvkcdevice = this->m_pcontext.m_p;
      __refdbg_this(pvkcdevice);
      return __allocate set_descriptor_layout(m_pcontext, bindings);
   }

   // *************** Descriptor Set Layout *********************

   set_descriptor_layout::set_descriptor_layout(
       context * pvkcdevice, std::unordered_map<uint32_t, VkDescriptorSetLayoutBinding> bindings)
      : m_pcontext{ pvkcdevice }, bindings{ bindings } {
      ::array<VkDescriptorSetLayoutBinding> setLayoutBindings{};
      for (auto kv : bindings) {
         setLayoutBindings.push_back(kv.second);
      }

      VkDescriptorSetLayoutCreateInfo descriptorSetLayoutInfo{};
      descriptorSetLayoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
      descriptorSetLayoutInfo.bindingCount = static_cast<uint32_t>(setLayoutBindings.size());
      descriptorSetLayoutInfo.pBindings = setLayoutBindings.data();

      if (vkCreateDescriptorSetLayout(
         m_pcontext->logicalDevice(),
         &descriptorSetLayoutInfo,
         nullptr,
         &descriptorSetLayout) != VK_SUCCESS) {
         throw std::runtime_error("failed to create descriptor set layout!");
      }
   }

   set_descriptor_layout::~set_descriptor_layout() {
      if (descriptorSetLayout != VK_NULL_HANDLE) {
         vkDestroyDescriptorSetLayout(m_pcontext->logicalDevice(), descriptorSetLayout, nullptr);
         descriptorSetLayout = VK_NULL_HANDLE;
      }
   }

   // *************** Descriptor Pool Builder *********************

   descriptor_pool::Builder & descriptor_pool::Builder::addPoolSize(
       VkDescriptorType descriptorType, uint32_t count) {
      poolSizes.push_back({ descriptorType, count });
      return *this;
   }

   descriptor_pool::Builder & descriptor_pool::Builder::setPoolFlags(
       VkDescriptorPoolCreateFlags flags) {
      poolFlags = flags;
      return *this;
   }
   descriptor_pool::Builder & descriptor_pool::Builder::setMaxSets(uint32_t count) {
      maxSets = count;
      return *this;
   }

   ::pointer <descriptor_pool> descriptor_pool::Builder::build() const {
      return __allocate descriptor_pool(m_pcontext, maxSets, poolFlags, poolSizes);
   }

   // *************** Descriptor Pool *********************

   descriptor_pool::descriptor_pool(
       context * pvkcdevice,
       uint32_t maxSets,
       VkDescriptorPoolCreateFlags poolFlags,
       const ::array<VkDescriptorPoolSize> & poolSizes)
      : m_pcontext{ pvkcdevice } {
      VkDescriptorPoolCreateInfo descriptorPoolInfo{};
      descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
      descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(poolSizes.size());
      descriptorPoolInfo.pPoolSizes = poolSizes.data();
      descriptorPoolInfo.maxSets = maxSets;
      descriptorPoolInfo.flags = poolFlags;

      if (vkCreateDescriptorPool(m_pcontext->logicalDevice(), &descriptorPoolInfo, nullptr, &descriptorPool) !=
          VK_SUCCESS) {
         throw std::runtime_error("failed to create descriptor pool!");
      }
   }

   descriptor_pool::~descriptor_pool() {
      if (descriptorPool != VK_NULL_HANDLE) {
         vkDestroyDescriptorPool(m_pcontext->logicalDevice(), descriptorPool, nullptr);
         descriptorPool = VK_NULL_HANDLE;
      }
   }

   bool descriptor_pool::allocateDescriptor(
       const VkDescriptorSetLayout descriptorSetLayout, VkDescriptorSet & descriptor) const {
      VkDescriptorSetAllocateInfo allocInfo{};
      allocInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
      allocInfo.descriptorPool = descriptorPool;
      allocInfo.pSetLayouts = &descriptorSetLayout;
      allocInfo.descriptorSetCount = 1;

      // Might want to create a "DescriptorPoolManager" class that handles this case, and builds
      // a new pool whenever an old pool fills up. But this is beyond our current scope
      if (vkAllocateDescriptorSets(m_pcontext->logicalDevice(), &allocInfo, &descriptor) != VK_SUCCESS) {
         return false;
      }
      return true;
   }

   void descriptor_pool::freeDescriptors(::array<VkDescriptorSet> & descriptors) const {
      vkFreeDescriptorSets(
          m_pcontext->logicalDevice(),
          descriptorPool,
          static_cast<uint32_t>(descriptors.size()),
          descriptors.data());
   }

   void descriptor_pool::resetPool() {
      vkResetDescriptorPool(m_pcontext->logicalDevice(), descriptorPool, 0);
   }

   // *************** Descriptor Writer *********************

   descriptor_writer::descriptor_writer(set_descriptor_layout & setLayout, descriptor_pool & pool)
      : setLayout{ setLayout }, pool{ pool } {
   }

   descriptor_writer & descriptor_writer::writeBuffer(
       uint32_t binding, VkDescriptorBufferInfo * bufferInfo) {
      assert(setLayout.bindings.count(binding) == 1 && "Layout does not contain specified binding");

      auto & bindingDescription = setLayout.bindings[binding];

      assert(
          bindingDescription.descriptorCount == 1 &&
          "Binding single descriptor info, but binding expects multiple");

      VkWriteDescriptorSet write{};
      write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      write.descriptorType = bindingDescription.descriptorType;
      write.dstBinding = binding;
      write.pBufferInfo = bufferInfo;
      write.descriptorCount = 1;

      writes.push_back(write);
      return *this;
   }

   descriptor_writer & descriptor_writer::writeImage(
       uint32_t binding, VkDescriptorImageInfo * imageInfo) {
      assert(setLayout.bindings.count(binding) == 1 && "Layout does not contain specified binding");

      auto & bindingDescription = setLayout.bindings[binding];

      assert(
          bindingDescription.descriptorCount == 1 &&
          "Binding single descriptor info, but binding expects multiple");

      VkWriteDescriptorSet write{};
      write.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
      write.descriptorType = bindingDescription.descriptorType;
      write.dstBinding = binding;
      write.pImageInfo = imageInfo;
      write.descriptorCount = 1;

      writes.push_back(write);
      return *this;
   }

   bool descriptor_writer::build(VkDescriptorSet & set) {
      bool success = pool.allocateDescriptor(setLayout.getDescriptorSetLayout(), set);
      if (!success) {
         return false;
      }
      overwrite(set);
      return true;
   }

   void descriptor_writer::overwrite(VkDescriptorSet & set) {
      for (auto & write : writes) {
         write.dstSet = set;
      }
      vkUpdateDescriptorSets(pool.m_pcontext->logicalDevice(), writes.size(), writes.data(), 0, nullptr);
   }


} // namespace gpu_vulkan



