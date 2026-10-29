#include "acme_windowing_wayland/native/runtime.h"
#include <EGL/egl.h>
#include <EGL/eglext.h>
#include <GL/gl.h>
#include <wayland-egl.h>
#include <chrono>
#include <cstdio>
#include <thread>
int main() {
 ca2_wayland::runtime native;
 auto w=native.create_window(360,240,"ca2 native Wayland EGL test","ca2.native.egl.test",{});
 for(int i=0;i<100 && !w->configured();++i) std::this_thread::sleep_for(std::chrono::milliseconds(20));
 if(!w->configured()) return 1;
 EGLDisplay d=eglGetPlatformDisplay(EGL_PLATFORM_WAYLAND_KHR,native.display(),nullptr);
 EGLint major=0,minor=0;
 if(!eglInitialize(d,&major,&minor)||!eglBindAPI(EGL_OPENGL_API)) return 2;
 EGLint attributes[]={EGL_SURFACE_TYPE,EGL_WINDOW_BIT,EGL_RENDERABLE_TYPE,EGL_OPENGL_BIT,EGL_RED_SIZE,8,EGL_GREEN_SIZE,8,EGL_BLUE_SIZE,8,EGL_ALPHA_SIZE,8,EGL_DEPTH_SIZE,24,EGL_STENCIL_SIZE,8,EGL_NONE};
 EGLConfig config=nullptr; EGLint count=0;
 if(!eglChooseConfig(d,attributes,&config,1,&count)||count!=1)return 3;
 EGLint bits=0;eglGetConfigAttrib(d,config,EGL_SURFACE_TYPE,&bits);std::printf("Wayland EGL surface bits: 0x%x (pbuffer=%d)\n",bits, bool(bits&EGL_PBUFFER_BIT));
 w->acquire_external_presentation();
 auto window=wl_egl_window_create(w->surface(),360,240);
 auto surface=eglCreateWindowSurface(d,config,(EGLNativeWindowType)window,nullptr);
 EGLint contextAttributes[]={EGL_CONTEXT_MAJOR_VERSION,4,EGL_CONTEXT_MINOR_VERSION,3,EGL_CONTEXT_OPENGL_PROFILE_MASK,EGL_CONTEXT_OPENGL_CORE_PROFILE_BIT,EGL_NONE};
 auto context=eglCreateContext(d,config,EGL_NO_CONTEXT,contextAttributes);
 if(surface==EGL_NO_SURFACE||context==EGL_NO_CONTEXT||!eglMakeCurrent(d,surface,surface,context))return 4;
 for(int i=0;i<5;++i){glClearColor(float(i)/5,0.2,0.6,1);glClear(GL_COLOR_BUFFER_BIT);if(!eglSwapBuffers(d,surface))return 5;std::this_thread::sleep_for(std::chrono::milliseconds(100));}
 w->hide();
 if(w->configured()) return 6;
 w->show();
 if(!w->configured()) return 7;
 glClearColor(0.1,0.7,0.4,1);glClear(GL_COLOR_BUFFER_BIT);
 if(!eglSwapBuffers(d,surface))return 8;
 native.send([]{});
 if(!native.connected()) return 9;
 eglMakeCurrent(d,EGL_NO_SURFACE,EGL_NO_SURFACE,EGL_NO_CONTEXT);eglDestroyContext(d,context);eglDestroySurface(d,surface);wl_egl_window_destroy(window);eglTerminate(d);w->release_external_presentation();w.reset();
 std::puts("Native Wayland EGL smoke passed: OpenGL 4.3 context, five swaps and EGL hide/show remapping");
}
