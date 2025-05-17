PIXELFORMATDESCRIPTOR pfd =
{
   sizeof(PIXELFORMATDESCRIPTOR),
   1,
   PFD_DRAW_TO_WINDOW | PFD_SUPPORT_VULKAN | PFD_DOUBLEBUFFER,    //Flags
   PFD_TYPE_RGBA,        // The kind of framebuffer. RGBA or palette.
   32,                   // Colordepth of the framebuffer.
   0, 0, 0, 0, 0, 0,
   0,
   0,
   0,
   0, 0, 0, 0,
   24,                   // Number of bits for the depthbuffer
   8,                    // Number of bits for the stencilbuffer
   0,                    // Number of Aux buffers in the framebuffer.
   PFD_MAIN_PLANE,
   0,
   0, 0, 0
};

HDC ourWindowHandleToDeviceContext = GetDC(hWnd);

int  letWindowsChooseThisPixelFormat;
letWindowsChooseThisPixelFormat = ChoosePixelFormat(ourWindowHandleToDeviceContext, &pfd);
SetPixelFormat(ourWindowHandleToDeviceContext, letWindowsChooseThisPixelFormat, &pfd);

HGLRC ourVulkanRenderingContext = wglCreateContext(ourWindowHandleToDeviceContext);
wglMakeCurrent(ourWindowHandleToDeviceContext, ourVulkanRenderingContext);

MessageBoxA(0, (char*)vkGetString(VK_VERSION), "VULKAN VERSION", 0);

wglDeleteContext(ourVulkanRenderingContext);
PostQuitMessage(0);
