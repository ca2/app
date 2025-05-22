/*
 * vulkan examples debug wrapper
 *
 * copyright (c) 2016-2023 by sascha willems - www.saschawillems.de
 *
 * this code is licensed under the mit license (mit) (http://opensource.org/licenses/mit)
 */
#include "framework.h"
#include "debug.h"
 //#include <iostream>

namespace vulkan
{

   namespace debug
   {


      PFN_vkCreateDebugUtilsMessengerEXT vkCreateDebugUtilsMessengerEXT;
      PFN_vkDestroyDebugUtilsMessengerEXT vkDestroyDebugUtilsMessengerEXT;
      VkDebugUtilsMessengerEXT debugUtilsMessenger;

      VKAPI_ATTR VkBool32 VKAPI_CALL debugUtilsMessageCallback(
         VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
         VkDebugUtilsMessageTypeFlagsEXT messageType,
         const VkDebugUtilsMessengerCallbackDataEXT * pCallbackData,
         void * pUserData)
      {
         // Select prefix depending on flags passed to the callback
         ::string prefix;

         if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_VERBOSE_BIT_EXT) {
            prefix = "VERBOSE: ";
#if defined(_WIN32)
            prefix = "\033[32m" + prefix + "\033[0m";
#endif
         }
         else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_INFO_BIT_EXT) {
            prefix = "INFO: ";
#if defined(_WIN32)
            prefix = "\033[36m" + prefix + "\033[0m";
#endif
         }
         else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT) {
            prefix = "WARNING: ";
#if defined(_WIN32)
            prefix = "\033[33m" + prefix + "\033[0m";
#endif
         }
         else if (messageSeverity & VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            prefix = "ERROR: ";
#if defined(_WIN32)
            prefix = "\033[31m" + prefix + "\033[0m";
#endif
         }


         // Display message to default output (console/logcat)
         ::string debugMessage;
         if (pCallbackData->pMessageIdName) {
            debugMessage << prefix << "[" << pCallbackData->messageIdNumber << "][" << pCallbackData->pMessageIdName << "] : " << pCallbackData->pMessage;
         }
         else {
            debugMessage << prefix << "[" << pCallbackData->messageIdNumber << "] : " << pCallbackData->pMessage;
         }

#if defined(__ANDROID__)
         if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            LOGE("%s", debugMessage.str().c_str());
         }
         else {
            LOGD("%s", debugMessage.str().c_str());
         }
#else
         if (messageSeverity >= VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT) {
            warning() << debugMessage;
         }
         else {
            information() << debugMessage;
         }
         fflush(stdout);
#endif


         // The return value of this callback controls whether the Vulkan call that caused the validation message will be aborted or not
         // We return VK_FALSE as we DON'T want Vulkan calls that cause a validation message to abort
         // If you instead want to have calls abort, pass in VK_TRUE and the function will return VK_ERROR_VALIDATION_FAILED_EXT
         return VK_FALSE;
      }

      void setupDebugingMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT & debugUtilsMessengerCI)
      {
         debugUtilsMessengerCI.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
         debugUtilsMessengerCI.messageSeverity = VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
         debugUtilsMessengerCI.messageType = VK_DEBUG_UTILS_MESSAGE_TYPE_GENERAL_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT;
         debugUtilsMessengerCI.pfnUserCallback = debugUtilsMessageCallback;
      }

      void setupDebugging(VkInstance instance)
      {
         vkCreateDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkCreateDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT"));
         vkDestroyDebugUtilsMessengerEXT = reinterpret_cast<PFN_vkDestroyDebugUtilsMessengerEXT>(vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT"));

         VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCI{};
         setupDebugingMessengerCreateInfo(debugUtilsMessengerCI);
         VkResult result = vkCreateDebugUtilsMessengerEXT(instance, &debugUtilsMessengerCI, nullptr, &debugUtilsMessenger);
         assert(result == VK_SUCCESS);
      }

      void freeDebugCallback(VkInstance instance)
      {
         if (debugUtilsMessenger != VK_NULL_HANDLE)
         {
            vkDestroyDebugUtilsMessengerEXT(instance, debugUtilsMessenger, nullptr);
         }
      }
   }

   namespace debugutils
   {
      PFN_vkCmdBeginDebugUtilsLabelEXT vkCmdBeginDebugUtilsLabelEXT{ nullptr };
      PFN_vkCmdEndDebugUtilsLabelEXT vkCmdEndDebugUtilsLabelEXT{ nullptr };
      PFN_vkCmdInsertDebugUtilsLabelEXT vkCmdInsertDebugUtilsLabelEXT{ nullptr };

      void setup(VkInstance instance)
      {
         vkCmdBeginDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdBeginDebugUtilsLabelEXT>(vkGetInstanceProcAddr(instance, "vkCmdBeginDebugUtilsLabelEXT"));
         vkCmdEndDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdEndDebugUtilsLabelEXT>(vkGetInstanceProcAddr(instance, "vkCmdEndDebugUtilsLabelEXT"));
         vkCmdInsertDebugUtilsLabelEXT = reinterpret_cast<PFN_vkCmdInsertDebugUtilsLabelEXT>(vkGetInstanceProcAddr(instance, "vkCmdInsertDebugUtilsLabelEXT"));
      }

      void cmdBeginLabel(VkCommandBuffer cmdbuffer, ::string caption, glm::vec4 color)
      {
         if (!vkCmdBeginDebugUtilsLabelEXT) {
            return;
         }
         VkDebugUtilsLabelEXT labelInfo{};
         labelInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_LABEL_EXT;
         labelInfo.pLabelName = caption.c_str();
         memcpy(labelInfo.color, &color[0], sizeof(float) * 4);
         vkCmdBeginDebugUtilsLabelEXT(cmdbuffer, &labelInfo);
      }

      void cmdEndLabel(VkCommandBuffer cmdbuffer)
      {
         if (!vkCmdEndDebugUtilsLabelEXT) {
            return;
         }
         vkCmdEndDebugUtilsLabelEXT(cmdbuffer);
      }

   } // namespace debug


} // namespace vulkan



