#include <cassert>
#include <fstream>
#include <iterator>
#include <string>


namespace
{


   std::string read_file(const char * pszPath)
   {

      std::ifstream stream(pszPath, std::ios::binary);

      return {
         std::istreambuf_iterator<char>(stream),
         std::istreambuf_iterator<char>()};

   }


   std::string section(
      const std::string & source,
      const std::string & beginMarker,
      const std::string & endMarker)
   {

      const auto begin = source.find(beginMarker);
      const auto end = source.find(endMarker, begin);

      assert(begin != std::string::npos);
      assert(end != std::string::npos);
      assert(begin < end);

      return source.substr(begin, end - begin);

   }


} // namespace


int main()
{

   const auto baseHeader = read_file("bred/gpu/texture.h");
   const auto renderTarget = read_file("bred/gpu/render_target.cpp");
   const auto glHeader = read_file("gpu_opengl/texture.h");
   const auto textureSource = read_file("gpu_opengl/texture.cpp");
   const auto contextSource = read_file("gpu_opengl/context.cpp");
   const auto shaderSource = read_file("gpu_opengl/shader.cpp");

   assert(baseHeader.find("::i32 m_iSampleCount = 1;") !=
      std::string::npos);
   assert(glHeader.find("::i32 effective_sample_count() const") !=
      std::string::npos);
   assert(glHeader.find("void invalidate_framebuffer_attachments()") !=
      std::string::npos);
   assert(glHeader.find("GLenum m_gluAllocatedType = 0;") !=
      std::string::npos);
   assert(glHeader.find("::i32_size m_sizeAllocated{-1, -1};") !=
      std::string::npos);
   assert(glHeader.find("::i32 m_iAllocatedSampleCount = 0;") !=
      std::string::npos);
   assert(renderTarget.find("m_gpu.m_iSampleCount") != std::string::npos);
   assert(renderTarget.find("ptexture->m_iSampleCount !=") !=
      std::string::npos);
   assert(textureSource.find(
      "glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, m_iSampleCount") !=
      std::string::npos);
   assert(textureSource.find(
      "glRenderbufferStorageMultisample(GL_RENDERBUFFER, m_iSampleCount") !=
      std::string::npos);
   assert(textureSource.find(
      "glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4") ==
      std::string::npos);
   assert(textureSource.find(
      "glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4") ==
      std::string::npos);
   assert(textureSource.find(
      "if (m_gluTextureID && bAllocationChanged)") !=
      std::string::npos);
   assert(textureSource.find("GL_MAX_SAMPLES") != std::string::npos);
   assert(textureSource.find("GL_MAX_COLOR_TEXTURE_SAMPLES") !=
      std::string::npos);

   const auto copy = section(
      contextSource,
      "void context::copy(::gpu::texture *ptextureTarget",
      "//   void context::_create_offscreen_window");
   assert(copy.find("glGenFramebuffers(1, &uReadFramebuffer)") !=
      std::string::npos);
   assert(copy.find("glGenFramebuffers(1, &uDrawFramebuffer)") !=
      std::string::npos);
   assert(copy.find("GL_READ_FRAMEBUFFER, GL_COLOR_ATTACHMENT0") !=
      std::string::npos);
   assert(copy.find("GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0") !=
      std::string::npos);
   assert(copy.find("glCheckFramebufferStatus(GL_READ_FRAMEBUFFER)") !=
      std::string::npos);
   assert(copy.find("glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER)") !=
      std::string::npos);
   assert(copy.find("GL_READ_FRAMEBUFFER_BINDING") != std::string::npos);
   assert(copy.find("GL_DRAW_FRAMEBUFFER_BINDING") != std::string::npos);
   assert(copy.find("GL_READ_BUFFER") != std::string::npos);
   assert(copy.find("GL_DRAW_BUFFER") != std::string::npos);
   assert(copy.find("GL_COLOR_BUFFER_BIT, GL_NEAREST") !=
      std::string::npos);
   assert(copy.find("sizeSrc != sizeDst") != std::string::npos);
   assert(copy.find("iDestinationSampleCount != 1") !=
      std::string::npos);
   assert(copy.find("ptextureSrc->frame_buffer_object()") ==
      std::string::npos);
   assert(copy.find("ptextureDst->frame_buffer_object()") ==
      std::string::npos);
   assert(contextSource.find(
      "glBindFramebuffer(GL_READ_FRAMEBUFFER, m_iReadFramebuffer)") !=
      std::string::npos);
   assert(contextSource.find(
      "glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_iDrawFramebuffer)") !=
      std::string::npos);
   assert(contextSource.find(
      "glDeleteFramebuffers(1, &m_uReadFramebuffer)") !=
      std::string::npos);
   assert(contextSource.find(
      "glDeleteFramebuffers(1, &m_uDrawFramebuffer)") !=
      std::string::npos);

   assert(glHeader.find(
      "::pointer < ::gpu_opengl::texture > m_ptextureResolved;") !=
      std::string::npos);
   assert(glHeader.find("texture * resolved_texture();") !=
      std::string::npos);

   const auto resolveTexture = section(
      textureSource,
      "texture * texture::resolved_texture()",
      "void texture::create_depth_resources()");
   assert(resolveTexture.find("if (m_iSampleCount <= 1)") !=
      std::string::npos);
   assert(resolveTexture.find("m_ptextureResolved") != std::string::npos);
   assert(resolveTexture.find("m_bMultisample = false;") !=
      std::string::npos);
   assert(resolveTexture.find("m_iSampleCount = 1;") !=
      std::string::npos);
   assert(resolveTexture.find("m_ptextureResolved == this") !=
      std::string::npos);
   assert(resolveTexture.find("textureflags.m_bWithDepth = false;") !=
      std::string::npos);
   assert(resolveTexture.find("textureflags.m_bRenderTarget = true;") !=
      std::string::npos);
   assert(resolveTexture.find("textureflags.m_bShaderResource = true;") !=
      std::string::npos);
   assert(resolveTexture.find("textureflags.m_bTransferSource = true;") !=
      std::string::npos);
   assert(resolveTexture.find("textureflags.m_bTransferTarget = true;") !=
      std::string::npos);
   assert(resolveTexture.find(
      "pcontext->copy(m_ptextureResolved, this, nullptr)") !=
      std::string::npos);

   const auto bindSource = section(
      shaderSource,
      "void shader::bind_source(::gpu::command_buffer",
      "void shader::bind_source2(");
   const auto bindSource2 = section(
      shaderSource,
      "void shader::bind_source2(",
      "//   void shader::setBool");
   const auto bindSlotSet = section(
      shaderSource,
      "void shader::bind_slot_set(",
      "void shader::program_compile_errors(");
   assert(bindSource.find("ptexture = ptexture->resolved_texture();") !=
      std::string::npos);
   assert(bindSource2.find("ptexture = ptexture->resolved_texture();") !=
      std::string::npos);
   assert(bindSlotSet.find("ptexture = ptexture->resolved_texture();") !=
      std::string::npos);
   assert(bindSource.find("bindingslot.m_ptexture = pgputexture;") !=
      std::string::npos);
   assert(bindSource.find("GL_TEXTURE_2D_MULTISAMPLE") !=
      std::string::npos);
   assert(bindSource2.find("GL_TEXTURE_2D_MULTISAMPLE") !=
      std::string::npos);
   assert(bindSlotSet.find("GL_TEXTURE_2D_MULTISAMPLE") !=
      std::string::npos);

   return 0;

}
