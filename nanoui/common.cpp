/*
    nanoui/nanoui.cpp -- Basic initialization and utility routines

    NanoGUI was developed by Wenzel Jakob <wenzel.jakob@epfl.ch>.
    The pwidget drawing code is based on the NanoVG demo application
    by Mikko Mononen.

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE.txt file.
*/
#include "framework.h"
#include "Object.h"
#include "acme/platform/application.h"
#include "acme/filesystem/filesystem/directory_context.h"
#include "acme/filesystem/filesystem/listing.h"
#include "apex/platform/context.h"
#include "aura/graphics/image/context.h"
#include "nano2d/context.h"



void CLASS_DECL_NANOUI file_dialog_from_platform(
   void * poswindow,
   const ::array<::pair<::string, ::string>> & filetypes,
   const ::function < void(const ::string_array & ) > & function,
   bool save, 
   bool multiple);


//::object * get_nano2d_object(::nano2d::context * pcontext);




//#include <nanoui/opengl.h>
//#include <nanoui/metal.h>
//#include <map>
//#include <thread>
//#include <chrono>
//#include <mutex>
//#include <iostream>

#if !defined(_WIN32)
#  include <locale.h>
#  include <signal.h>
#  include <dirent.h>
#endif

#if defined(EMSCRIPTEN)
#  include <emscripten/emscripten.h>
#endif


namespace nanoui
{



//extern std::map<GLFWwindow *, Screen *> __nanoui_screens;

#if defined(__APPLE__)
extern void disable_saved_application_state_osx();
#endif

//void init() {
//#if !defined(_WIN32)
//   /* Avoid locale-related number parsing issues */
//   setlocale(LC_NUMERIC, "C");
//#endif
//
//#if defined(__APPLE__)
//   disable_saved_application_state_osx();
//   glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
//#endif
//
////   glfwSetErrorCallback(
////      [](int error, const char * descr) {
////         if (error == GLFW_NOT_INITIALIZED)
////            return; /* Ignore */
////         std::cerr << "GLFW error " << error << ": " << descr << std::endl;
////      }
////   );
////
////   if (!glfwInit())
////      throw std::runtime_error("Could not initialize GLFW!");
////
////#if defined(NANOUI_USE_METAL)
////   metal_init();
////#endif
////
////   glfwSetTime(0);
//}

//static bool mainloop_active = false;

#if defined(EMSCRIPTEN)
static double emscripten_last = 0;
static float emscripten_refresh = 0;
#endif

//::pointer < ::mutex > m_async_mutex;
//::array<::function<void()>> m_async_functions;

//void mainloop(float refresh) {
//   if (mainloop_active)
//      throw std::runtime_error("Main loop is already running!");
//
//   auto mainloop_iteration = []() {
//      int num_screens = 0;
//
//#if defined(EMSCRIPTEN)
//      double emscripten_now = glfwGetTime();
//      bool emscripten_redraw = false;
//      if (float((emscripten_now - emscripten_last) * 1000) > emscripten_refresh) {
//         emscripten_redraw = true;
//         emscripten_last = emscripten_now;
//      }
//#endif
//
//      /* Run async functions */ {
//         std::lock_guard<std::pointer < ::mutex >> guard(m_async_mutex);
//         for (auto & f : m_async_functions)
//            f();
//         m_async_functions.clear();
//      }
//
//      for (auto kv : __nanoui_screens) {
//         Screen * pscreen = kv.second;
//         if (!pscreen->visible()) {
//            continue;
//         }
//         else if (glfwWindowShouldClose(pscreen->glfw_window())) {
//            pscreen->set_visible(false);
//            continue;
//         }
//#if defined(EMSCRIPTEN)
//         if (emscripten_redraw || pscreen->tooltip_fade_in_progress())
//            pscreen->redraw();
//#endif
//         pscreen->draw_all();
//         num_screens++;
//      }
//
//      if (num_screens == 0) {
//         /* Give up if there was nothing to draw */
//         mainloop_active = false;
//         return;
//      }
//
//#if !defined(EMSCRIPTEN)
//      /* Wait for mouse/keyboard or empty refresh happenings */
//      glfwWaitEvents();
//#endif
//   };
//
//#if defined(EMSCRIPTEN)
//   emscripten_refresh = refresh;
//   /* The following will throw an exception and enter the main
//      loop within Emscripten. This means that none of the code below
//      (or in the caller, for that matter) will be executed */
//   emscripten_set_main_loop(mainloop_iteration, 0, 1);
//#endif
//
//   mainloop_active = true;
//
//   std::thread refresh_thread;
//   std::chrono::microseconds quantum;
//   size_t quantum_count = 1;
//   if (refresh >= 0) {
//      quantum = std::chrono::microseconds((huge_integer)(refresh * 1'000));
//      while (quantum.count() > 50'000) {
//         quantum /= 2;
//         quantum_count *= 2;
//      }
//   }
//   else {
//      quantum = std::chrono::microseconds(50'000);
//      quantum_count = std::numeric_limits<size_t>::max();
//   }
//
//   /* If there are no mouse/keyboard happenings, try to refresh the
//      view roughly every 50 ms (default); this is to support animations
//      such as progress bars while keeping the system load
//      reasonably low */
//   refresh_thread = std::thread(
//      [quantum, quantum_count]() {
//         while (true) {
//            for (size_t i = 0; i < quantum_count; ++i) {
//               if (!mainloop_active)
//                  return;
//               std::this_thread::sleep_for(quantum);
//               for (auto kv : __nanoui_screens) {
//                  if (kv.second->tooltip_fade_in_progress())
//                     kv.second->redraw();
//               }
//            }
//            for (auto kv : __nanoui_screens)
//               kv.second->redraw();
//         }
//      }
//   );
//
//   try {
//      while (mainloop_active)
//         mainloop_iteration();
//
//      /* Process happenings once more */
//      glfwPollEvents();
//   }
//   catch (const std::exception & e) {
//      std::cerr << "Caught exception in main loop: " << e.what() << std::endl;
//      leave();
//   }
//
//   refresh_thread.join();
//}

//void async(const ::function<void()> & func) {
//   std::lock_guard<std::pointer < ::mutex >> guard(m_async_mutex);
//   m_async_functions.add(func);
//}

//void leave() {
//   mainloop_active = false;
//}

//bool active() {
//   return mainloop_active;
//}

//::pair<bool, bool> test_10bit_edr_support() {
//#if defined(NANOUI_USE_METAL)
//   return metal_10bit_edr_support();
//#else
//   return { false, false };
//#endif
//}


//void shutdown() {
//   glfwTerminate();
//
//#if defined(NANOUI_USE_METAL)
//   metal_shutdown();
//#endif
//}

#if defined(__clang__)
#  define NANOUI_FALLTHROUGH [[clang::fallthrough]];
#elif defined(__GNUG__)
#  define NANOUI_FALLTHROUGH __attribute__ ((fallthrough));
#else
#  define NANOUI_FALLTHROUGH
#endif

::string get_utf8_character(uint32_t pwidgetChild) {
   char seq[8];
   int n = 0;
   if (pwidgetChild < 0x80) n = 1;
   else if (pwidgetChild < 0x800) n = 2;
   else if (pwidgetChild < 0x10000) n = 3;
   else if (pwidgetChild < 0x200000) n = 4;
   else if (pwidgetChild < 0x4000000) n = 5;
   else if (pwidgetChild <= I32_MAXIMUM) n = 6;
   seq[n] = '\0';
   switch (n) {
   case 6: seq[5] = 0x80 | (pwidgetChild & 0x3f); pwidgetChild = pwidgetChild >> 6; pwidgetChild |= 0x4000000; NANOUI_FALLTHROUGH
   case 5: seq[4] = 0x80 | (pwidgetChild & 0x3f); pwidgetChild = pwidgetChild >> 6; pwidgetChild |= 0x200000;  NANOUI_FALLTHROUGH
   case 4: seq[3] = 0x80 | (pwidgetChild & 0x3f); pwidgetChild = pwidgetChild >> 6; pwidgetChild |= 0x10000;   NANOUI_FALLTHROUGH
   case 3: seq[2] = 0x80 | (pwidgetChild & 0x3f); pwidgetChild = pwidgetChild >> 6; pwidgetChild |= 0x800;     NANOUI_FALLTHROUGH
   case 2: seq[1] = 0x80 | (pwidgetChild & 0x3f); pwidgetChild = pwidgetChild >> 6; pwidgetChild |= 0xc0;      NANOUI_FALLTHROUGH
   case 1: seq[0] = pwidgetChild;
   }
   return ::string(seq, seq + n);
}

int __nanoui_get_image(::nano2d::context * pcontext, const ::scoped_string & name, uint8_t * data, uint32_t size) {
   static string_map < int> icon_cache;
   auto it = icon_cache.plookup(name);
   if (it != icon_cache.end())
      return it->m_element2;
   int icon_id = pcontext->create_image_mem(0, data, size);
   if (icon_id == 0)
      throw std::runtime_error("Unable to load resource data.");
   icon_cache[name] = icon_id;
   return icon_id;
}





void CLASS_DECL_NANOUI load_image_directory(::nano2d::context * pcontext, ::array<::pair<int, ::string>> & images, const ::scoped_string & path)
{

//   ::array<::pair<int, ::string> > result;
//#if !defined(_WIN32)
//   DIR * dp = opendir(path.c_str());
//   if (!dp)
//      throw std::runtime_error("Could not open image directory!");
//   struct dirent * ep;
//   while ((ep = readdir(dp))) {
//      const char * fname = ep->d_name;
//#else

   auto pparticle = get_nano2d_object(pcontext);

   auto papexcontext = pparticle->m_papplication;

   ::file::listing listing;

   listing.set_file_listing(path.c_str());

   papexcontext->directory()->enumerate(listing);

   for (auto & path : listing)
   {

      int iImage = pcontext->create_image(path, 0);

      if (iImage >= 0)
      {
         
         string strTitle = path.title();

         images.add({ iImage, strTitle });

      }

   }


//   WIN32_FIND_DATA ffd;
//   ::string search_path = path + "/*.*";
//   HANDLE handle = FindFirstFileA(search_path.c_str(), &ffd);
//   if (handle == INVALID_HANDLE_VALUE)
//      throw std::runtime_error("Could not open image directory!");
//   do {
//      const char * fname = ffd.cFileName;
//#endif
//      if (strstr(fname, "png") == nullptr)
//         continue;
//      ::string full_name = path + "/" + ::string(fname);
//      int img = pcontext->create_imagefull_name.c_str(), 0);
//      if (img == 0)
//         throw std::runtime_error("Could not open image data!");
//      result.add(
//         std::make_pair(img, full_name.substr(0, full_name.length() - 4)));
//#if !defined(_WIN32)
//   }
//   closedir(dp);
//#else
//   } while (FindNextFileA(handle, &ffd) != 0);
//   FindClose(handle);
//#endif
   
}






//void Object::inc_ref(){
//   //m_ref_count++;
//   increment_reference_count();
//}
//
//void Object::dec_ref(bool dealloc)  {
//   if (dealloc)
//   {
//      release();
//
//   }
//   else
//   {
//
//      decrement_reference_count();
//
//   }
//   //--m_ref_count;
//   //if (m_ref_count == 0 && dealloc) {
//   //   delete this;
//   //}
//   //else if (m_ref_count < 0) {
//   //   fprintf(stderr, "Internal error: %p: object reference count < 0!\n", this);
//   //   abort();
//   //}
//}

Object::~Object() { }



::image::image_pointer ___load_image(::particle * pparticle, const ::file::path & path)
{

   return pparticle->image()->path_image(path);

}


void ___save_image(::particle * pparticle, const ::file::path & path, ::image::image *pimage)
{

   return pparticle->image()->save_image(path, pimage);

}




} // namespace nanoui







