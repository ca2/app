#include "framework.h"
#include "context_win32.h"
#include "approach.h"
#include "cpu_buffer.h"
#include "physical_device.h"
#include "aura/graphics/gpu/approach.h"
#include "aura/graphics/image/image.h"
#include "acme/platform/application.h"
#include "aura/platform/system.h"
#include "windowing_win32/window.h"
//xxxopengl>>>>vulkan #include "glad_wgl.h"


using namespace vulkan;


namespace gpu_vulkan
{


   ::pointer < ::gpu::context > allocate_system_context(::particle * pparticle)
   {

      return pparticle->__create_new <context_win32>();

   }


   context_win32::context_win32()
   {

      m_bMesa = false;

      m_emode = e_mode_system;

      m_estatus = error_not_initialized;

      m_physicaldevicefeaturesCreate = {};
      m_physicaldevicefeaturesEnabled = {};
      m_device = VK_NULL_HANDLE;
      m_commandpool = VK_NULL_HANDLE;

   }


   context_win32::~context_win32()
   {

   }


   bool context_win32::is_mesa()
   {

      return m_bMesa;

   }

   
   void context_win32::_create_offscreen_window(const ::int_size & size)
   {
      //if (::IsWindow(m_hwnd))
      //{

      //   if (!::SetWindowPos(m_hwnd,
      //      nullptr, 0, 0,
      //      size.cx()
      //      , size.cy(), SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE
      //      | SWP_NOCOPYBITS | SWP_NOSENDCHANGING
      //      | SWP_NOREPOSITION | SWP_NOREDRAW))
      //   {

      //      information() << "SetWindowPos Failed";

      //   }


      //   //return m_hwnd;

      //}
      //else
      //{

      //   LPCTSTR lpClassName = L"draw2d_vulkan_offscreen_buffer_window";
      //   LPCTSTR lpWindowName = L"draw2d_vulkan_offscreen_buffer_window";
      //   //unsigned int dwStyle = WS_CAPTION | WS_POPUPWINDOW; // | WS_VISIBLE
      //   unsigned int dwExStyle = 0;
      //   unsigned int dwStyle = WS_OVERLAPPEDWINDOW;
      //   dwStyle |= WS_POPUP;
      //   //dwStyle |= WS_VISIBLE;
      //   //dwStyle |= WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
      //   dwStyle &= ~WS_CAPTION;
      //   //dwStyle = 0;
      //   dwStyle &= ~WS_THICKFRAME;
      //   dwStyle &= ~WS_BORDER;
      //   int x = 0;
      //   int y = 0;
      //   int nWidth = size.cx();
      //   int nHeight = size.cy();
      //   HWND hWndParent = nullptr;
      //   HMENU hMenu = nullptr;
      //   HINSTANCE hInstance = ::GetModuleHandleW(L"gpu_vulkan.dll");
      //   LPVOID lpParam = nullptr;

      //   m_hwnd = CreateWindowExW(dwExStyle, lpClassName, lpWindowName, dwStyle, x, y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);

      //   if (!m_hwnd)
      //   {

      //      informationf("MS GDI - CreateWindow failed");

      //      informationf("last-error code: %d\n", GetLastError());

      //      throw ::exception(error_failed);

      //   }

      //   //return m_hwnd;

      //}


   }


   void context_win32::_create_context_win32()
   {

      ::cast < approach > papproach = system()->get_gpu();

      if (!papproach)
      {

         throw ::exception(error_failed);

      }

      auto pphysicaldevice = papproach->m_pphysicaldevice;

      assert(pphysicaldevice && pphysicaldevice->m_physicaldevice);
      //this->m_physicaldevice = physicalDevice;

      auto physicaldevice = pphysicaldevice->m_physicaldevice;

      // Get list of supported extensions
      uint32_t extCount = 0;
      vkEnumerateDeviceExtensionProperties(physicaldevice, nullptr, &extCount, nullptr);
      if (extCount > 0)
      {
         ::array<VkExtensionProperties> extensions(extCount);
         if (vkEnumerateDeviceExtensionProperties(physicaldevice, nullptr, &extCount, extensions.data()) == VK_SUCCESS)
         {
            for (auto & ext : extensions)
            {
               m_straSupportedExtensions.add(ext.extensionName);
            }
         }
      }

      // Derived examples can enable extensions based on the list of supported extensions read from the physical device
      //getEnabledExtensions();

      bool useSwapChain = m_papplication->m_bUseDraw2dProtoWindow;

      VkResult result = createLogicalDevice(
         m_physicaldevicefeaturesCreate,
         papproach->m_pszaEnabledDeviceExtensions,
         papproach->m_pDeviceCreatepNextChain,
         useSwapChain);

      if (result != VK_SUCCESS)
      {

         exitFatal("Could not create Vulkan device: \n" + ::errorString(result) + " VkResult=" + ::as_string(result), result);

         throw ::exception(error_failed);

      }

      //device = vulkanDevice->logicalDevice;

   }


   void context_win32::on_create_context()
   {

      _create_context_win32();

      ::cast < approach > papproach = system()->get_gpu();

      if (!papproach)
      {

         throw ::exception(error_failed);

      }



   }


   VkResult context_win32::createLogicalDevice(
   VkPhysicalDeviceFeatures enabledFeatures,
   ::array<const char *> enabledExtensions,
   void * pNextChain,
   bool useSwapChain,
   VkQueueFlags requestedQueueTypes)
   {

      ::cast < approach > papproach = ::system()->get_gpu();

      ::cast < physical_device > pphysicaldevice = papproach->m_pphysicaldevice;

      // Desired queues need to be requested upon logical device creation
      // Due to differing queue family configurations of Vulkan implementations this can be a bit tricky, especially if the application
      // requests different queue types

      ::array<VkDeviceQueueCreateInfo> queueCreateInfos{};

      // Get queue family indices for the requested queue family types
      // Note that the indices may overlap depending on the implementation

      const float defaultQueuePriority(0.0f);

      // Graphics queue
      if (requestedQueueTypes & VK_QUEUE_GRAPHICS_BIT)
      {
         m_queuefamilyindices.graphics = pphysicaldevice->getQueueFamilyIndex(VK_QUEUE_GRAPHICS_BIT);
         VkDeviceQueueCreateInfo queueInfo{};
         queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
         queueInfo.queueFamilyIndex = m_queuefamilyindices.graphics;
         queueInfo.queueCount = 1;
         queueInfo.pQueuePriorities = &defaultQueuePriority;
         queueCreateInfos.add(queueInfo);
      }
      else
      {
         m_queuefamilyindices.graphics = 0;
      }

      // Dedicated compute queue
      if (requestedQueueTypes & VK_QUEUE_COMPUTE_BIT)
      {
         m_queuefamilyindices.compute = pphysicaldevice->getQueueFamilyIndex(VK_QUEUE_COMPUTE_BIT);
         if (m_queuefamilyindices.compute != m_queuefamilyindices.graphics)
         {
            // If compute family index differs, we need an additional queue create info for the compute queue
            VkDeviceQueueCreateInfo queueInfo{};
            queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueInfo.queueFamilyIndex = m_queuefamilyindices.compute;
            queueInfo.queueCount = 1;
            queueInfo.pQueuePriorities = &defaultQueuePriority;
            queueCreateInfos.add(queueInfo);
         }
      }
      else
      {
         // Else we use the same queue
         m_queuefamilyindices.compute = m_queuefamilyindices.graphics;
      }

      // Dedicated transfer queue
      if (requestedQueueTypes & VK_QUEUE_TRANSFER_BIT)
      {
         m_queuefamilyindices.transfer = pphysicaldevice->getQueueFamilyIndex(VK_QUEUE_TRANSFER_BIT);
         if ((m_queuefamilyindices.transfer != m_queuefamilyindices.graphics)
            && (m_queuefamilyindices.transfer != m_queuefamilyindices.compute))
         {
            // If transfer family index differs, we need an additional queue create info for the transfer queue
            VkDeviceQueueCreateInfo queueInfo{};
            queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueInfo.queueFamilyIndex = m_queuefamilyindices.transfer;
            queueInfo.queueCount = 1;
            queueInfo.pQueuePriorities = &defaultQueuePriority;
            queueCreateInfos.add(queueInfo);
         }
      }
      else
      {
         // Else we use the same queue
         m_queuefamilyindices.transfer = m_queuefamilyindices.graphics;
      }

      // Create the logical device representation
      ::array<const char *> deviceExtensions(enabledExtensions);
      if (useSwapChain)
      {
         
         // If the device will be used for presenting to a display via a swapchain we need to request the swapchain extension
         deviceExtensions.add(VK_KHR_SWAPCHAIN_EXTENSION_NAME);

      }

      VkDeviceCreateInfo deviceCreateInfo = {};
      deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
      deviceCreateInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());;
      deviceCreateInfo.pQueueCreateInfos = queueCreateInfos.data();
      deviceCreateInfo.pEnabledFeatures = &enabledFeatures;

      // If a pNext(Chain) has been passed, we need to add it to the device creation info
      VkPhysicalDeviceFeatures2 physicalDeviceFeatures2{};
      if (pNextChain) {
         physicalDeviceFeatures2.sType = VK_STRUCTURE_TYPE_PHYSICAL_DEVICE_FEATURES_2;
         physicalDeviceFeatures2.features = enabledFeatures;
         physicalDeviceFeatures2.pNext = pNextChain;
         deviceCreateInfo.pEnabledFeatures = nullptr;
         deviceCreateInfo.pNext = &physicalDeviceFeatures2;
      }

#if (defined(VK_USE_PLATFORM_IOS_MVK) || defined(VK_USE_PLATFORM_MACOS_MVK) || defined(VK_USE_PLATFORM_METAL_EXT)) && defined(VK_KHR_portability_subset)
      // SRS - When running on iOS/macOS with MoltenVK and VK_KHR_portability_subset is defined and supported by the device, enable the extension
      if (extensionSupported(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME))
      {
         deviceExtensions.push_back(VK_KHR_PORTABILITY_SUBSET_EXTENSION_NAME);
      }
#endif

      if (deviceExtensions.size() > 0)
      {
         for (const char * enabledExtension : deviceExtensions)
         {
            if (!isExtensionSupported(enabledExtension)) {
               information() << "Enabled device extension \"" << enabledExtension << "\" is not present at device level\n";
            }
         }

         deviceCreateInfo.enabledExtensionCount = (uint32_t)deviceExtensions.size();
         deviceCreateInfo.ppEnabledExtensionNames = deviceExtensions.data();
      }

      this->m_physicaldevicefeaturesEnabled = enabledFeatures;

      auto physicaldevice = pphysicaldevice->m_physicaldevice;

      VkResult result = vkCreateDevice(physicaldevice, &deviceCreateInfo, nullptr, &m_device);
      if (result != VK_SUCCESS)
      {
         return result;
      }

      // Create a default command pool for graphics command buffers
      m_commandpool = createCommandPool(m_queuefamilyindices.graphics);

      return result;

   }


   /**
   * Create a command pool for allocation command buffers from
   *
   * @param queueFamilyIndex Family index of the queue to create the command pool for
   * @param createFlags (Optional) Command pool creation flags (Defaults to VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT)
   *
   * @note Command buffers allocated from the created pool can only be submitted to a queue with the same family index
   *
   * @return A handle to the created command buffer
   */
   VkCommandPool context_win32::createCommandPool(uint32_t queueFamilyIndex, VkCommandPoolCreateFlags createFlags)
   {
      VkCommandPoolCreateInfo cmdPoolInfo = {};
      cmdPoolInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
      cmdPoolInfo.queueFamilyIndex = queueFamilyIndex;
      cmdPoolInfo.flags = createFlags;
      VkCommandPool cmdPool;
      VK_CHECK_RESULT(vkCreateCommandPool(m_device, &cmdPoolInfo, nullptr, &cmdPool));
      return cmdPool;
   }


   /**
   * Check if an extension is supported by the (physical device)
   *
   * @param extension Name of the extension to check
   *
   * @return True if the extension is supported (present in the list read at device creation time)
   */
   bool context_win32::isExtensionSupported(const ::scoped_string & scopedstrExtension)
   {

      return m_straSupportedExtensions.contains(scopedstrExtension);

   }


   //void context_win32::_create_window_buffer()
   //{

   //   if (!m_hdc || !m_hrc)
   //   {

   //      auto psystem = system();

   //      auto pgpu = psystem->get_gpu();

   //      ::pointer < ::vulkan::vulkan > pvulkan = pgpu;

   //      if (!pvulkan->m_atomClass)
   //      {

   //         informationf("MS GDI - RegisterClass failed");

   //         informationf("last-error code: %d\n", GetLastError());

   //         throw ::exception(error_failed);

   //      }

   //      // create WGL context, make current

   //      //xxxopengl>>>>vulkan PIXELFORMATDESCRIPTOR pixformat;

   //      int chosenformat;

   //      HDC hdc = GetDC(m_hwnd);

   //      if (!hdc)
   //      {

   //         informationf("MS GDI - GetDC failed");

   //         informationf("last-error code: %d\n", GetLastError());

   //         throw ::exception(error_failed);

   //      }

   //      ////xxxopengl>>>>vulkan  zero(pixformat);
   //      //pixformat.nSize = sizeof(pixformat);
   //      //pixformat.nVersion = 1;
   //      //pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_VULKAN | PFD_DOUBLEBUFFER;
   //      //pixformat.iPixelType = PFD_TYPE_RGBA;
   //      //pixformat.cColorBits = 32;
   //      //pixformat.cRedShift = 16;
   //      //pixformat.cGreenShift = 8;
   //      //pixformat.cBlueShift = 0;
   //      //pixformat.cAlphaShift = 24;
   //      //pixformat.cAlphaBits = 8;
   //      //pixformat.cDepthBits = 24;
   //      //pixformat.cStencilBits = 8;

   //      //xxxopengl>>>>vulkan chosenformat = ChoosePixelFormat(hdc, &pixformat);

   //      //if (chosenformat == 0)
   //      //{

   //      //   informationf("MS GDI - ChoosePixelFormat failed");

   //      //   informationf("last-error code: %d\n", GetLastError());

   //      //   ReleaseDC(m_hwnd, hdc);

   //      //   throw ::exception(error_failed);

   //      //}

   //      //bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

   //      //if (!spfok)
   //      //{

   //      //   informationf("MS GDI - SetPixelFormat failed");

   //      //   informationf("last-error code: %d\n", GetLastError());

   //      //   ReleaseDC(m_hwnd, hdc);

   //      //   throw ::exception(error_failed);

   //      //}

   //      //HGLRC hglrc = wglCreateContext(hdc);

   //      //if (!hglrc)
   //      //{

   //      //   informationf("MS WGL - wglCreateContext failed");

   //      //   informationf("last-error code: %d\n", GetLastError());

   //      //   ReleaseDC(m_hwnd, hdc);

   //      //   throw ::exception(error_failed);

   //      //}

   //      //bool bMakeCurrentOk = wglMakeCurrent(hdc, hglrc);

   //      //if (!bMakeCurrentOk)
   //      //{

   //      //   informationf("MS WGL - wglMakeCurrent failed");

   //      //   informationf("last-error code: %d\n", GetLastError());

   //      //   ReleaseDC(m_hwnd, hdc);

   //      //   throw ::exception(error_failed);

   //      //}


   //      pvulkan->defer_init_gpu_library();

   //      //auto pszVersion = (const char *)glGetString(GL_VERSION);
   //      ////::e_status estatus = 

   //      //::string strVersion(pszVersion);

   //      //if (strVersion.case_insensitive_contains("mesa"))
   //      //{

   //      //   m_bMesa = true;

   //      //}

   //      ////if (!estatus)
   //      ////{

   //      ////   ReleaseDC(window, hdc);

   //      ////   return estatus;

   //      ////}

   //      m_hwnd = m_hwnd;
   //      m_hdc = hdc;
   //      //xxxopengl>>>>vulkan m_hrc = hglrc;

   //   }

   //   RECT rectClient;

   //   ::GetClientRect(m_hwnd, &rectClient);

   //   m_size = { rectClient.right - rectClient.left,
   //      rectClient.bottom - rectClient.top };

   //   m_itaskGpu = ::current_itask();

   //   m_estatus = ::success;

   //   set_ok_flag();
   //   
   //}


   void context_win32::_create_window_context(::windowing::window * pwindowParam)
   {

   //   ::cast < ::windowing_win32::window > pwindow = pwindowParam;

   //   if (!m_hdc || !m_hrc)
   //   {

   //      auto psystem = system();

   //      auto pgpu = psystem->get_gpu();

   //      ::pointer < ::vulkan::vulkan > pvulkan = pgpu;

   //      //if (!pvulkan->m_atomClass)
   //      //{

   //      //   informationf("MS GDI - RegisterClass failed");

   //      //   informationf("last-error code: %d\n", GetLastError());

   //      //   throw ::exception(error_failed);

   //      //}

   //      if (!m_hwnd)
   //      {

   //         auto hwnd = pwindow->m_hwnd;


   //         m_hwnd = hwnd;


   //         //// create WGL context, make current

   //         //PIXELFORMATDESCRIPTOR pixformat;

   //         //int chosenformat;

   //         HDC hdc = GetDC(m_hwnd);

   //         //if (!hdc)
   //         //{

   //         //   informationf("MS GDI - GetDC failed");

   //         //   informationf("last-error code: %d\n", GetLastError());

   //         //   throw ::exception(error_failed);

   //         //}

   //         //zero(pixformat);
   //         //pixformat.nSize = sizeof(pixformat);
   //         //pixformat.nVersion = 1;
   //         //pixformat.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_VULKAN | PFD_DOUBLEBUFFER;
   //         //pixformat.iPixelType = PFD_TYPE_RGBA;
   //         //pixformat.cColorBits = 32;
   //         //pixformat.cRedShift = 16;
   //         //pixformat.cGreenShift = 8;
   //         //pixformat.cBlueShift = 0;
   //         //pixformat.cAlphaShift = 24;
   //         //pixformat.cAlphaBits = 8;
   //         //pixformat.cDepthBits = 24;
   //         //pixformat.cStencilBits = 8;

   //         //chosenformat = ChoosePixelFormat(hdc, &pixformat);

   //         //if (chosenformat == 0)
   //         //{

   //         //   informationf("MS GDI - ChoosePixelFormat failed");

   //         //   informationf("last-error code: %d\n", GetLastError());

   //         //   ReleaseDC(m_hwnd, hdc);

   //         //   throw ::exception(error_failed);

   //         //}

   //         //bool spfok = SetPixelFormat(hdc, chosenformat, &pixformat);

   //         //if (!spfok)
   //         //{

   //         //   informationf("MS GDI - SetPixelFormat failed");

   //         //   informationf("last-error code: %d\n", GetLastError());

   //         //   ReleaseDC(m_hwnd, hdc);

   //         //   throw ::exception(error_failed);

   //         //}

   ////         auto hglrc = wglCreateContext(hdc);

   ////         pwindow->m_hglrcProto = hglrc;

   //////         int context_attribs[] = {
   //////WGL_CONTEXT_MAJOR_VERSION_ARB, 2,
   //////WGL_CONTEXT_MINOR_VERSION_ARB, 1,
   //////0, 0
   //////         };
   //////         auto hglrc = wglCreateContextAttribsARB(hdc, NULL, context_attribs);
   //////         if (!hglrc) {
   //////            //ReleaseDC(hWnd, hDC);
   //////            //DestroyWindow(hWnd);

   //////            throw ::exception(error_failed);
   //////         }
   //////         //ReleaseDC(hWnd, hDC);

   ////         if (!pwindow->m_hglrcProto)
   ////         {

   ////            informationf("MS WGL - wglCreateContext failed");

   ////            informationf("last-error code: %d\n", GetLastError());

   ////            ReleaseDC(m_hwnd, hdc);

   ////            throw ::exception(error_failed);

   ////         }

   ////         bool bMakeCurrentOk = wglMakeCurrent(hdc, pwindow->m_hglrcProto);

   ////         if (!bMakeCurrentOk)
   ////         {

   ////            informationf("MS WGL - wglMakeCurrent failed");

   ////            informationf("last-error code: %d\n", GetLastError());

   ////            ReleaseDC(m_hwnd, hdc);

   ////            throw ::exception(error_failed);

   ////         }


   ////         pvulkan->defer_init_gpu_library();

   //         //auto pszVersion = (const char *)glGetString(GL_VERSION);
   //         ////::e_status estatus = 

   //         //::string strVersion(pszVersion);

   //         //if (strVersion.case_insensitive_contains("mesa"))
   //         //{

   //         //   m_bMesa = true;

   //         //}

   //         ////if (!estatus)
   //         ////{

   //         ////   ReleaseDC(window, hdc);

   //         ////   return estatus;

   //         ////}

   //         m_hwnd = m_hwnd;
   //         m_hdc = hdc;
   //         m_hrc = pwindow->m_hglrcProto;

   //      }

   //   }

   //   RECT rectClient;

   //   ::GetClientRect(m_hwnd, &rectClient);

   //   ::int_size sizeNew = { rectClient.right - rectClient.left,
   //rectClient.bottom - rectClient.top };
   //   
   //   if (m_size != sizeNew)
   //   {
   //      m_size = sizeNew;


   //      //HDC pdcDIB;                      // контекст устройства в памяти
   //      //HBITMAP hbmpDIB;                 // и его текущий битмапvoid *pBitsDIB(NULL);            // содержимое битмапаint cxDIB(200); int cyDIB(300);  // его размеры (например для окна 200х300)
   //      //auto &BIH=pwindow->m_bitmapinfoheaderProto;            // и заголовок// …// создаем DIB section// создаем структуру BITMAPINFOHEADER, описывающую наш DIBint iSize = sizeof(BITMAPINFOHEADER);  // размер
   //      //memset(&BIH, 0, sizeof(pwindow->m_bitmapinfoheaderProto));

   //      //BIH.biSize = sizeof(pwindow->m_bitmapinfoheaderProto);        // размер структуры
   //      //BIH.biWidth = m_size.cx();       // геометрия
   //      //BIH.biHeight = m_size.cy();      // битмапа
   //      //BIH.biPlanes = 1;          // один план
   //      //BIH.biBitCount = 32;       // 24 bits per pixel
   //      //BIH.biCompression = BI_RGB;// без сжатия// создаем новый DC в памяти
   //      ////pdcDIB = CreateCompatibleDC(NULL);
   //      ////void * pBits = nullptr;
   //      //// создаем DIB-секцию
   //      //pwindow->m_hbitmapProto = CreateDIBSection(
   //      //  m_hdc,                  // контекст устройства
   //      //  (BITMAPINFO *)&BIH,       // информация о битмапе
   //      //  DIB_RGB_COLORS,          // параметры цвета
   //      //  &pwindow->m_pbitsProto,               // местоположение буфера (память выделяет система)
   //      //  NULL,                    // не привязываемся к отображаемым в память файлам
   //      //  0);

   //      //// выберем новый битмап (DIB section) для контекста устройства в памяти
   //      //SelectObject(m_hdc, pwindow->m_hbitmapProto);
   //      //pwindow->m_hdcProto = m_hdc;
   //   }

   //   m_itaskGpu = ::current_itask();

   //   m_estatus = ::success;

   //   set_ok_flag();

   }


   void context_win32::_create_offscreen_buffer(const ::int_size& size)
   {

      _create_offscreen_window(size);
      
      //_create_window_buffer();

      m_itaskGpu = ::current_itask();

   }


   void context_win32::defer_create_window_context(::windowing::window * pwindow)
   {

      //if (m_hrc)
      //{

      //   return;

      //}

      //::vulkan::context::defer_create_window_context(pwindow);

   }


   void context_win32::_defer_create_window_context(::windowing::window * pwindow)
   {

      _create_window_context(pwindow);

   }


   void context_win32::resize_offscreen_buffer(const ::int_size& sizeParam)
   {

       if (m_papplication->m_bUseDraw2dProtoWindow)
       {

           return;

       }

      auto size(sizeParam);

      send([this, size]()
         {
            //if (!m_pcpubuffer)

            create_offscreen_buffer(size);


      ///m_pcpubuffer->m_pixmap.create(m_pcpubuffer->m_memory, size);

//#ifdef WINDOWS_DESKTOP
//
//      ::SetWindowPos(m_hwnd, 0, 0, 0, size.cx(), size.cy(), SWP_NOZORDER | SWP_NOMOVE | SWP_HIDEWINDOW);
//
//#else

//      destroy_offscreen_buffer();
//
//      if(!create_offscreen_buffer(size))
//      {
//
//         return error_failed;
//
//      }

//#endif

      make_current();

      //glViewport(0, 0, size.cx(), size.cy());
      //glMatrixMode(GL_PROJECTION);
      //glLoadIdentity();
      //glOrtho(0, size.cx(), 0, size.cy(), -10, 10);
      //glMatrixMode(GL_MODELVIEW);
      //glutPostRedisplay();

      //return ::success;
            });


   }


   void context_win32::make_current()
   {

      ASSERT(m_itaskGpu == ::current_itask());

      ::e_status estatus = ::success;

      //bool bMakeCurrentOk = wglMakeCurrent(m_hdc, m_hrc);

      //if (!bMakeCurrentOk)
      //{

      //   informationf("MS WGL - wglMakeCurrent failed");

      //   informationf("last-error code: %d\n", GetLastError());

      //   throw ::exception(error_failed);

      //}

      //return estatus;

   }


   void context_win32::destroy_offscreen_buffer()
   {

      //ASSERT(m_itaskGpu == ::current_itask());

      //::e_status estatus = ::success;

      //if (m_hrc == NULL && m_hdc == NULL && m_hwnd == NULL)
      //{

      //   return;

      //}

      ////wglMakeCurrent(nullptr, nullptr);
      ////wglDeleteContext(m_hrc);
      //::ReleaseDC(m_hwnd, m_hdc);
      //::DestroyWindow(m_hwnd);
      //m_size.set(0, 0);
      //m_hrc = NULL;
      //m_hwnd = NULL;
      //m_hdc = NULL;

      ////return estatus;

   }

   void context_win32::render()
   {

      ::gpu_vulkan::context::render();

      

   }


   void context_win32::swap_buffers()
   {

      //SwapBuffers(m_hdc);

   }


   string context_win32::get_shader_version_text()
   {

      return "#version 330 core";

   }


   void context_win32::_translate_shader(string_array& stra)
   {

      context::_translate_shader(stra);

      character_count iFindPrecision = stra.case_insensitive_find_first_begins("precision ");

      if (iFindPrecision >= 0)
      {

         stra[iFindPrecision] = "precision highp float;";

      }
      else
      {

         stra.insert_at(1, "precision highp float;");

         iFindPrecision = 1;

      }

   }




} // namespace gpu_vulkan



