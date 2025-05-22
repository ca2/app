#include "framework.h"
#include "approach.h"
#include "context.h"
#include "debug.h"
#include "physical_device.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/gpu/context.h"
#include "acme/platform/application.h"


//#if defined(FREEBSD) || defined(OPENBSD)
//#include <string.h>
//#endif
using namespace vulkan;

namespace gpu_vulkan
{


#ifdef WINDOWS_DESKTOP

   ::pointer <::gpu::context > allocate_system_context(::particle * pparticle);

#elif defined(__APPLE__)

#if 1

   ::pointer <::gpu::context > allocate_fbo_context(::particle * pparticle);

#else

   ::pointer <::gpu::context > allocate_cgl_context(::particle * pparticle);

#endif

#else

   ::pointer <::gpu::context > allocate_egl_context(::particle * pparticle);

   //::pointer <::gpu::context > allocate_glx_context(::particle * pparticle);

#endif


   approach::approach()
   {

      m_bGpuLibraryInit = false;

#ifdef WINDOWS_DESKTOP

      m_atomClass = 0;

#endif

      m_vkinstance = VK_NULL_HANDLE;
      //m_physicaldevice = VK_NULL_HANDLE;
      //m_physicaldeviceproperties = {};
      //m_physicaldevicefeatures = {};
      //m_physicaldevicememoryproperties = {};
      //m_physicaldevicefeaturesEnabled = {};
      m_vkdevice = VK_NULL_HANDLE;
      m_vkqueue = VK_NULL_HANDLE;
      m_formatDepth = VK_FORMAT_UNDEFINED;
      m_vkcommandpool = VK_NULL_HANDLE;
      m_pipelinestageflagsSubmit = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
      m_submitinfo = {};
      m_vkrenderpass = VK_NULL_HANDLE;
      m_uCurrentBuffer = 0;
      m_descriptorpool = {};
      m_vkpipelinecache = {};
      m_bRequiresStencil = false;

   }


   approach::~approach()
   {

   }


#ifdef WINDOWS_DESKTOP


   LRESULT CALLBACK Draw2VulkanWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
   {

      return DefWindowProc(hwnd, message, wparam, lparam);

   }


#endif // WINDOWS_DESKTOP


   void approach::initialize(::particle * pparticle)
   {

      //::e_status estatus =
      
      ::object::initialize(pparticle);

      //if (!estatus)
      //{

      //   return estatus;

      //}

#ifdef WINDOWS_DESKTOP

      if (!m_atomClass)
      {

         WNDCLASSW wndclass = {};

         wndclass.style = CS_OWNDC;
         wndclass.lpfnWndProc = &Draw2VulkanWndProc;
         wndclass.hInstance = ::GetModuleHandleW(L"gpu_vulkan.dll");
         wndclass.lpszClassName = L"draw2d_vulkan_offscreen_buffer_window";

         m_atomClass = RegisterClassW(&wndclass);

         if (!m_atomClass)
         {

            throw ::exception(error_failed);

         }

      }

#endif

      initialize_gpu_approach();

      //return estatus;

   }


   void approach::initialize_gpu_approach()
   {

         // Instead of checking for the command line switch, validation can be forced via a define
#if defined(_VALIDATION)
         this->settings.validation = true;
#endif

         // Create the instance
         VkResult result = createInstance();
         if (result != VK_SUCCESS) {
            auto str = "Could not create Vulkan instance : \n" + errorString(result);
            throw ::exception(error_failed);
         }

#if defined(VK_USE_PLATFORM_ANDROID_KHR)
         vks::android::loadVulkanFunctions(instance);
#endif

         // If requested, we enable the default validation layers for debugging
         if (settings.validation)
         {
            
            debug::setupDebugging(m_vkinstance);

         }

         // Physical device
         uint32_t gpuCount = 0;
         // Get number of available physical devices
         VK_CHECK_RESULT(vkEnumeratePhysicalDevices(m_vkinstance, &gpuCount, nullptr));
         if (gpuCount == 0) {
            exitFatal("No device with Vulkan support found", -1);
            throw ::exception(error_failed);
         }
         // Enumerate devices
         ::array<VkPhysicalDevice> physicalDevices;
         
         physicalDevices.set_size(gpuCount);
         result = vkEnumeratePhysicalDevices(m_vkinstance, &gpuCount, physicalDevices.data());
         if (result != VK_SUCCESS) {
            exitFatal("Could not enumerate physical devices : \n" + errorString(result), result);
            throw ::exception(error_failed);
         }

         // GPU selection

         // Select physical device to be used for the Vulkan example
         // Defaults to the first device unless specified by command line
         uint32_t selectedDevice = 0;

//#if !defined(VK_USE_PLATFORM_ANDROID_KHR)
//         // GPU selection via command line argument
//         if (commandLineParser.isSet("gpuselection")) {
//            uint32_t index = commandLineParser.getValueAsInt("gpuselection", 0);
//            if (index > gpuCount - 1) {
//               std::cerr << "Selected device index " << index << " is out of range, reverting to device 0 (use -listgpus to show available Vulkan devices)" << "\n";
//            }
//            else {
//               selectedDevice = index;
//            }
//         }
//         if (commandLineParser.isSet("gpulist")) {
//            std::cout << "Available Vulkan devices" << "\n";
//            for (uint32_t i = 0; i < gpuCount; i++) {
//               VkPhysicalDeviceProperties deviceProperties;
//               vkGetPhysicalDeviceProperties(physicalDevices[i], &deviceProperties);
//               std::cout << "Device [" << i << "] : " << deviceProperties.deviceName << std::endl;
//               std::cout << " Type: " << physicalDeviceTypeString(deviceProperties.deviceType) << "\n";
//               std::cout << " API: " << (deviceProperties.apiVersion >> 22) << "." << ((deviceProperties.apiVersion >> 12) & 0x3ff) << "." << (deviceProperties.apiVersion & 0xfff) << "\n";
//            }
//         }
//#endif

         auto physicaldevice = physicalDevices[selectedDevice];

         auto pphysicaldevice = __create_new < physical_device >();

         pphysicaldevice->_initialize_physical_device(this, physicaldevice);

         m_pphysicaldevice = pphysicaldevice;

         //m_physicaldevice = physicalDevices[selectedDevice];

         //// Store properties (including limits), features and memory properties of the physical device (so that examples can check against them)
         //vkGetPhysicalDeviceProperties(m_physicaldevice, &m_physicaldeviceproperties);
         //vkGetPhysicalDeviceFeatures(m_physicaldevice, &m_physicaldevicefeatures);
         //vkGetPhysicalDeviceMemoryProperties(m_physicaldevice, &m_physicaldevicememoryproperties);

         // Derived examples can override this to set actual features (based on above readings) to enable for logical device creation
         getEnabledFeatures();

         //// Vulkan device creation
         //// This is handled by a separate class that gets a logical device representation
         //// and encapsulates functions related to a device
         //m_pdevice = new vks::VulkanDevice(physicalDevice);

         //// Derived examples can enable extensions based on the list of supported extensions read from the physical device
         //getEnabledExtensions();

         //result = vulkanDevice->createLogicalDevice(enabledFeatures, enabledDeviceExtensions, deviceCreatepNextChain);
         //if (result != VK_SUCCESS) {
         //   exitFatal("Could not create Vulkan device: \n" + errorString(result), result);
         //   throw ::exception(error_failed);
         //}
         //device = vulkanDevice->logicalDevice;

         //// Get a graphics queue from the device
         //vkGetDeviceQueue(device, vulkanDevice->queueFamilyIndices.graphics, 0, &queue);

         //// Find a suitable depth and/or stencil format
         //VkBool32 validFormat{ false };
         //// Samples that make use of stencil will require a depth + stencil format, so we select from a different list
         //if (requiresStencil) {
         //   validFormat = getSupportedDepthStencilFormat(physicalDevice, &depthFormat);
         //}
         //else {
         //   validFormat = getSupportedDepthFormat(physicalDevice, &depthFormat);
         //}
         //assert(validFormat);

         //swapChain.setContext(instance, physicalDevice, device);

         //// Create synchronization objects
         //VkSemaphoreCreateInfo semaphoreCreateInfo = vks::initializers::semaphoreCreateInfo();
         //// Create a semaphore used to synchronize image presentation
         //// Ensures that the image is displayed before we start submitting new commands to the queue
         //VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &semaphores.presentComplete));
         //// Create a semaphore used to synchronize command submission
         //// Ensures that the image is not presented until all commands have been submitted and executed
         //VK_CHECK_RESULT(vkCreateSemaphore(device, &semaphoreCreateInfo, nullptr, &semaphores.renderComplete));

         //// Set up submit info structure
         //// Semaphores will stay the same during application lifetime
         //// Command buffer submission info is set by each example
         //submitInfo = vks::initializers::submitInfo();
         //submitInfo.pWaitDstStageMask = &submitPipelineStages;
         //submitInfo.waitSemaphoreCount = 1;
         //submitInfo.pWaitSemaphores = &semaphores.presentComplete;
         //submitInfo.signalSemaphoreCount = 1;
         //submitInfo.pSignalSemaphores = &semaphores.renderComplete;

   }


   void approach::getEnabledFeatures()
   {



   }


   VkResult approach::createInstance()
   {
      
      ::array<const char *> instanceExtensions;
      
      if (m_papplication->m_bUseDraw2dProtoWindow)
      {

         instanceExtensions.add(VK_KHR_SURFACE_EXTENSION_NAME);

         // Enable surface extensions depending on os
#if defined(_WIN32)
         instanceExtensions.add(VK_KHR_WIN32_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_ANDROID_KHR)
         instanceExtensions.add(VK_KHR_ANDROID_SURFACE_EXTENSION_NAME);
#elif defined(_DIRECT2DISPLAY)
         instanceExtensions.add(VK_KHR_DISPLAY_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_DIRECTFB_EXT)
         instanceExtensions.add(VK_EXT_DIRECTFB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_WAYLAND_KHR)
         instanceExtensions.add(VK_KHR_WAYLAND_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_XCB_KHR)
         instanceExtensions.add(VK_KHR_XCB_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_IOS_MVK)
         instanceExtensions.add(VK_MVK_IOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_MACOS_MVK)
         instanceExtensions.add(VK_MVK_MACOS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_METAL_EXT)
         instanceExtensions.add(VK_EXT_METAL_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_HEADLESS_EXT)
         instanceExtensions.add(VK_EXT_HEADLESS_SURFACE_EXTENSION_NAME);
#elif defined(VK_USE_PLATFORM_SCREEN_QNX)
         instanceExtensions.add(VK_QNX_SCREEN_SURFACE_EXTENSION_NAME);
#endif

      }

      // Get extensions supported by the instance and store for later use
      uint32_t extCount = 0;
      vkEnumerateInstanceExtensionProperties(nullptr, &extCount, nullptr);
      if (extCount > 0)
      {
         ::array<VkExtensionProperties> extensions(extCount);
         if (vkEnumerateInstanceExtensionProperties(nullptr, &extCount, extensions.data()) == VK_SUCCESS)
         {
            for (VkExtensionProperties & extension : extensions)
            {
               m_straSupportedInstanceExtensions.add(extension.extensionName);
            }
         }
      }

#if (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT))
      // SRS - When running on iOS/macOS with MoltenVK, enable VK_KHR_get_physical_device_properties2 if not already enabled by the example (required by VK_KHR_portability_subset)
      if (std::find(enabledInstanceExtensions.begin(), enabledInstanceExtensions.end(), VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME) == enabledInstanceExtensions.end())
      {
         enabledInstanceExtensions.add(VK_KHR_GET_PHYSICAL_DEVICE_PROPERTIES_2_EXTENSION_NAME);
      }

#endif

      // Enabled requested instance extensions
      //if (m_pszaEnabledDeviceExtensions.has_element())
      //{
         for (const char * enabledExtension : m_pszaEnabledDeviceExtensions)
         {
            // Output message if requested extension is not available
            if (!m_straSupportedInstanceExtensions.contains(enabledExtension))
            {
               warning() << "Enabled instance extension \"" << enabledExtension << "\" is not present at instance level";
            }
            instanceExtensions.add(enabledExtension);
         }
      //}

      VkApplicationInfo appInfo{};
      appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
      appInfo.pApplicationName = m_strName;
      appInfo.pEngineName = m_strName;
      appInfo.apiVersion = m_uApiVersion;

      VkInstanceCreateInfo instanceCreateInfo{};
      instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
      instanceCreateInfo.pApplicationInfo = &appInfo;

      VkDebugUtilsMessengerCreateInfoEXT debugUtilsMessengerCI{};
      if (settings.validation) 
      {
         debug::setupDebugingMessengerCreateInfo(debugUtilsMessengerCI);
         debugUtilsMessengerCI.pNext = instanceCreateInfo.pNext;
         instanceCreateInfo.pNext = &debugUtilsMessengerCI;
      }

#if (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT)) && defined(VK_KHR_portability_enumeration)
      // SRS - When running on iOS/macOS with MoltenVK and VK_KHR_portability_enumeration is defined and supported by the instance, enable the extension and the flag
      if (std::find(supportedInstanceExtensions.begin(), supportedInstanceExtensions.end(), VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME) != supportedInstanceExtensions.end())
      {
         instanceExtensions.add(VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME);
         instanceCreateInfo.flags |= VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
      }
#endif

      // Enable the debug utils extension if available (e.g. when debugging tools are present)
      if (settings.validation || m_straSupportedInstanceExtensions.contains(VK_EXT_DEBUG_UTILS_EXTENSION_NAME))
      {
         instanceExtensions.add(VK_EXT_DEBUG_UTILS_EXTENSION_NAME);
      }

      if (!instanceExtensions.empty()) {
         instanceCreateInfo.enabledExtensionCount = (uint32_t)instanceExtensions.size();
         instanceCreateInfo.ppEnabledExtensionNames = instanceExtensions.data();
      }

      // The VK_LAYER_KHRONOS_validation contains all current validation functionality.
      // Note that on Android this layer requires at least NDK r20
      const char * validationLayerName = "VK_LAYER_KHRONOS_validation";
      if (settings.validation) {
         // Check if this layer is available at instance level
         uint32_t instanceLayerCount;
         vkEnumerateInstanceLayerProperties(&instanceLayerCount, nullptr);
         ::array<VkLayerProperties> instanceLayerProperties(instanceLayerCount);
         vkEnumerateInstanceLayerProperties(&instanceLayerCount, instanceLayerProperties.data());
         bool validationLayerPresent = false;
         for (VkLayerProperties & layer : instanceLayerProperties) {
            if (strcmp(layer.layerName, validationLayerName) == 0) {
               validationLayerPresent = true;
               break;
            }
         }
         if (validationLayerPresent) {
            instanceCreateInfo.ppEnabledLayerNames = &validationLayerName;
            instanceCreateInfo.enabledLayerCount = 1;
         }
         else {
            warning() << "Validation layer VK_LAYER_KHRONOS_validation not present, validation is disabled";
         }
      }

      // If layer settings are defined, then activate the sample's required layer settings during instance creation.
      // Layer settings are typically used to activate specific features of a layer, such as the Validation Layer's
      // printf feature, or to configure specific capabilities of drivers such as MoltenVK on macOS and/or iOS.
      VkLayerSettingsCreateInfoEXT layerSettingsCreateInfo{ VK_STRUCTURE_TYPE_LAYER_SETTINGS_CREATE_INFO_EXT };
      if (m_layersettingsEnabled.has_element()) 
      {
         layerSettingsCreateInfo.settingCount = static_cast<uint32_t>(m_layersettingsEnabled.size());
         layerSettingsCreateInfo.pSettings = m_layersettingsEnabled.data();
         layerSettingsCreateInfo.pNext = instanceCreateInfo.pNext;
         instanceCreateInfo.pNext = &layerSettingsCreateInfo;
      }

      VkResult result = vkCreateInstance(&instanceCreateInfo, nullptr, &m_vkinstance);

      // If the debug utils extension is present we set up debug functions, so samples can label objects for debugging
      if (m_straSupportedInstanceExtensions.contains(VK_EXT_DEBUG_UTILS_EXTENSION_NAME)) 
      {
         debugutils::setup(m_vkinstance);
      }

      return result;

   }


   ::pointer < ::gpu::context > approach::create_context(::particle * pparticle)
   {

      ::pointer < ::gpu_vulkan::context > pgpucontext;

#ifdef WINDOWS_DESKTOP

      pgpucontext = allocate_system_context(pparticle);

#elif defined(__APPLE__)
      
#if 1

      pgpucontext = allocate_fbo_context(pparticle);
      
#else
      
      pgpucontext = allocate_cgl_context(pparticle);
      
#endif

#elif defined(__ANDROID__)

      pgpucontext = allocate_egl_context(pparticle);

#else

      string strWaylandDisplay(getenv("WAYLAND_DISPLAY"));

      if(strWaylandDisplay.has_character())
      {

         pgpucontext = allocate_egl_context(pparticle);

      }
      // else
      // {
      //
      //    pgpucontext = allocate_glx_context(pparticle);
      //
      // }

#endif

      if(!pgpucontext)
      {

         return nullptr;

      }

      pgpucontext->m_pphysicaldevice = m_pphysicaldevice;

      pgpucontext->create_context();

      return pgpucontext;

   }


   void approach::defer_init_gpu_library()
   {

      if (m_bGpuLibraryInit)
      {

         return;

      }

#if !defined(LINUX) && !defined(__APPLE__) && !defined(__BSD__)

      //gladLoadGL();

      m_bGpuLibraryInit = true;

#endif

//      if (!m_bGlewInit)
//      {
//         
//#if !defined(__APPLE__) && !defined(__ANDROID__)
//
//         glewExperimental = GL_TRUE;
//
//         GLenum err = glewInit();
//
//         if (err != GLEW_OK)
//         {
//
//            const ::ansi_character * pszErrorString = (const char *) glewGetErrorString(err);
//
//            //throw ::exception(error_resource);
//            // Problem: glewInit failed, something is seriously wrong.
//            informationf("glewInit failed: %s (%d)\n", pszErrorString, err);
//
//            throw ::exception(error_failed);
//
//         }
//         
//#endif
//
//         m_bGlewInit = true;

//      }

      //return ::success;

   }


#define FOURCC_DXT1 0x31545844 // Equivalent to "DXT1" in ASCII
#define FOURCC_DXT3 0x33545844 // Equivalent to "DXT3" in ASCII
#define FOURCC_DXT5 0x35545844 // Equivalent to "DXT5" in ASCII

   int approach::fread(void* data, int c, int s, ::file::file* pfile)
   {

      return (int) (pfile->read(data,s * c) / c);

   }


   ::gpu::payload approach::load_dds(const ::scoped_string & scopedstrImagePath) 
   {

      auto fp = file()->get_reader(scopedstrImagePath);

      unsigned char header[124];

      //FILE * fp;

      ///* try to open the file */
      //fp = fopen(strImagePath, "rb");
      //if (fp == NULL) {
      //   printf("%s could not be opened. Are you in the right directory ? Don't forget to read the FAQ !\n", strImagePath.c_str()); getchar();
      //   return 0;
      //}

      /* verify the type of file */
      char filecode[4];
      fread(filecode, 1, 4, fp);
      if (::string(filecode, 4).case_insensitive_order("DDS ") != 0) {
         //fclose(fp);
         return {};
      }

      /* get the surface desc */
      fread(&header, 124, 1, fp);

      unsigned int height = *(unsigned int *)&(header[8]);
      unsigned int width = *(unsigned int *)&(header[12]);
      unsigned int linearSize = *(unsigned int *)&(header[16]);
      unsigned int mipMapCount = *(unsigned int *)&(header[24]);
      unsigned int fourCC = *(unsigned int *)&(header[80]);


      unsigned char * buffer;
      unsigned int bufsize;
      /* how big is it going to be including all mipmaps? */
      bufsize = mipMapCount > 1 ? linearSize * 2 : linearSize;
      buffer = (unsigned char *)malloc(bufsize * sizeof(unsigned char));
      fread(buffer, 1, bufsize, fp);
      /* close the file pointer */
      //fclose(fp);



      ////unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
      //unsigned int format;
      //switch (fourCC)
      //{
      //case FOURCC_DXT1:
      //   format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
      //   break;
      //case FOURCC_DXT3:
      //   format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
      //   break;
      //case FOURCC_DXT5:
      //   format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
      //   break;
      //default:
      //   free(buffer);
      //   return 0;
      //}

      //// Create one Vulkan texture
      //GLuint textureID;
      //glGenTextures(1, &textureID);

      //// "Bind" the newly created texture : all future texture functions will modify this texture
      //glBindTexture(GL_TEXTURE_2D, textureID);
      //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      //unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
      //unsigned int offset = 0;

      ///* load the mipmaps */
      //for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
      //{
      //   unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
      //   glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
      //      0, size, buffer + offset);

      //   offset += size;
      //   width /= 2;
      //   height /= 2;

      //   // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
      //   if (width < 1) width = 1;
      //   if (height < 1) height = 1;

      //}

      //free(buffer);

      //return textureID;

      return {};


   }


} // namespace gpu_vulkan



