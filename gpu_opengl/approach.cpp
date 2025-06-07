#include "framework.h"
#include "approach.h"
#include "acme/filesystem/file/file.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/graphics/gpu/context.h"


//#if defined(FREEBSD) || defined(OPENBSD)
//#include <string.h>
//#endif


namespace gpu_opengl
{


   approach::approach()
   {

      m_bGpuLibraryInit = false;

#ifdef WINDOWS_DESKTOP

      m_atomClass = 0;

#endif

   }


   approach::~approach()
   {

   }


#ifdef WINDOWS_DESKTOP


   LRESULT CALLBACK Draw2OpenGLWndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
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
         wndclass.lpfnWndProc = &Draw2OpenGLWndProc;
         wndclass.hInstance = ::GetModuleHandleW(L"gpu_opengl.dll");
         wndclass.lpszClassName = L"draw2d_opengl_offscreen_buffer_window";

         m_atomClass = RegisterClassW(&wndclass);

         if (!m_atomClass)
         {

            throw ::exception(error_failed);

         }

      }

#endif

      //return estatus;

   }




   void approach::defer_init_gpu_library()
   {

      if (m_bGpuLibraryInit)
      {

         return;

      }

#if !defined(LINUX) && !defined(__APPLE__) && !defined(__BSD__)

      gladLoadGL();

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

      //unsigned int components = (fourCC == FOURCC_DXT1) ? 3 : 4;
      unsigned int format;
      switch (fourCC)
      {
      case FOURCC_DXT1:
         format = GL_COMPRESSED_RGBA_S3TC_DXT1_EXT;
         break;
      case FOURCC_DXT3:
         format = GL_COMPRESSED_RGBA_S3TC_DXT3_EXT;
         break;
      case FOURCC_DXT5:
         format = GL_COMPRESSED_RGBA_S3TC_DXT5_EXT;
         break;
      default:
         free(buffer);
         return {};
      }

      // Create one OpenGL texture
      GLuint textureID;
      glGenTextures(1, &textureID);

      // "Bind" the newly created texture : all future texture functions will modify this texture
      glBindTexture(GL_TEXTURE_2D, textureID);
      glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

      unsigned int blockSize = (format == GL_COMPRESSED_RGBA_S3TC_DXT1_EXT) ? 8 : 16;
      unsigned int offset = 0;

      /* load the mipmaps */
      for (unsigned int level = 0; level < mipMapCount && (width || height); ++level)
      {
         unsigned int size = ((width + 3) / 4) * ((height + 3) / 4) * blockSize;
         glCompressedTexImage2D(GL_TEXTURE_2D, level, format, width, height,
            0, size, buffer + offset);

         offset += size;
         width /= 2;
         height /= 2;

         // Deal with Non-Power-Of-Two textures. This code is not included in the webpage to reduce clutter.
         if (width < 1) width = 1;
         if (height < 1) height = 1;

      }

      free(buffer);

      gpu::payload payload;

      payload.m_iUniform = textureID;

      return payload;


   }


   ::file::path approach::shader_path(const ::file::path& pathShader)
   {

      if (pathShader.begins("matter://shaders/"))
      {

         auto pathFolder = pathShader.folder();

         return pathFolder / "opengl" / pathShader.name();

      }

      return pathShader;

   }





} // namespace gpu_opengl



