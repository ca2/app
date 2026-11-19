// Created by camilo on 2025-06-11 01:08 <3ThomasBorregaardSørensen!!
#include "platform.h"
#include "_gpu_opengl.h"
#include "command_buffer.h"
#include "context.h"
#include "device.h"
#include "input_layout.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "acme/prototype/geometry2d/matrix.h"
#include "acme/prototype/prototype/call.h"
#include "acme/parallelization/critical_section.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/render_target.h"
#include "bred/gpu/renderer.h"
#include "bred/gpu/types.h"
#include "bred/graphics3d/types.h"
#include <atomic>
#include <chrono>


namespace gpu_opengl
{

   namespace
   {
      struct pending_context_handle
      {
         enum_handle m_ehandle;
         GLuint m_handle;
         GLsync m_sync = nullptr;
      };
      ::critical_section g_csHandleDeletion;
      ::map<void *, ::array<pending_context_handle>> g_mapPendingHandles;

      ::std::atomic<long long> g_cTextureObjectsLive{0};
      ::std::atomic<long long> g_cTexturesCreated{0};
      ::std::atomic<long long> g_cTexturesDeleted{0};
      ::std::atomic<long long> g_cFbosCreated{0};
      ::std::atomic<long long> g_cFbosDeleted{0};
      ::std::atomic<long long> g_cVaosCreated{0};
      ::std::atomic<long long> g_cVaosDeleted{0};
      ::std::atomic<long long> g_cVbosCreated{0};
      ::std::atomic<long long> g_cVbosDeleted{0};
      ::std::atomic<long long> g_cSyncsCreated{0};
      ::std::atomic<long long> g_cSyncsDeleted{0};
      ::std::atomic<long long> g_cDroppedNullContextDeletes{0};
      ::std::atomic<long long> g_cLastTraceNs{0};
   }

   void trace_opengl_resource_created(enum_handle ehandle)
   {
      if (ehandle == e_handle_texture)
         g_cTexturesCreated.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_fbo)
         g_cFbosCreated.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_buffer)
         g_cVaosCreated.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_vertex_buffer)
         g_cVbosCreated.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_sync)
         g_cSyncsCreated.fetch_add(1, ::std::memory_order_relaxed);
   }

   void trace_opengl_resource_deleted(enum_handle ehandle)
   {
      if (ehandle == e_handle_texture)
         g_cTexturesDeleted.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_fbo)
         g_cFbosDeleted.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_buffer)
         g_cVaosDeleted.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_vertex_buffer)
         g_cVbosDeleted.fetch_add(1, ::std::memory_order_relaxed);
      else if (ehandle == e_handle_sync)
         g_cSyncsDeleted.fetch_add(1, ::std::memory_order_relaxed);
   }

   void trace_opengl_texture_object_delta(int iDelta)
   {
      g_cTextureObjectsLive.fetch_add(iDelta, ::std::memory_order_relaxed);
   }

   void trace_opengl_resource_stats_if_due()
   {
      auto nowNs = ::std::chrono::duration_cast<::std::chrono::nanoseconds>(
         ::std::chrono::steady_clock::now().time_since_epoch()).count();
      auto lastNs = g_cLastTraceNs.load(::std::memory_order_relaxed);
      if (nowNs - lastNs < 1000000000LL)
      {
         return;
      }
      if (!g_cLastTraceNs.compare_exchange_strong(lastNs, nowNs, ::std::memory_order_relaxed))
      {
         return;
      }

      ::collection::count cPendingContexts = 0;
      ::collection::count cPendingHandles = 0;
      {
         ::critical_section_lock lock(&g_csHandleDeletion);
         cPendingContexts = g_mapPendingHandles.size();
         for (auto & pair : g_mapPendingHandles)
         {
            cPendingHandles += pair.element2().size();
         }
      }

      ::string strTrace;
      strTrace.formatf(
         "[gpu_opengl_mem] tex_obj_live=%lld gl_tex=%lld/%lld gl_fbo=%lld/%lld gl_vao=%lld/%lld gl_vbo=%lld/%lld gl_sync=%lld/%lld pending=%lld(ctx=%lld) null_ctx_drop=%lld",
         g_cTextureObjectsLive.load(::std::memory_order_relaxed),
         g_cTexturesCreated.load(::std::memory_order_relaxed),
         g_cTexturesDeleted.load(::std::memory_order_relaxed),
         g_cFbosCreated.load(::std::memory_order_relaxed),
         g_cFbosDeleted.load(::std::memory_order_relaxed),
         g_cVaosCreated.load(::std::memory_order_relaxed),
         g_cVaosDeleted.load(::std::memory_order_relaxed),
         g_cVbosCreated.load(::std::memory_order_relaxed),
         g_cVbosDeleted.load(::std::memory_order_relaxed),
         g_cSyncsCreated.load(::std::memory_order_relaxed),
         g_cSyncsDeleted.load(::std::memory_order_relaxed),
         (long long)cPendingHandles,
         (long long)cPendingContexts,
         g_cDroppedNullContextDeletes.load(::std::memory_order_relaxed));
      ::information(strTrace);
   }

   void defer_delete_context_handle(void * pNativeContext, enum_handle ehandle, GLuint handle)
   {
      if (!handle) return;
      if (!pNativeContext)
      {
         g_cDroppedNullContextDeletes.fetch_add(1, ::std::memory_order_relaxed);
         return;
      }
      ::critical_section_lock lock(&g_csHandleDeletion);
      g_mapPendingHandles[pNativeContext].add({ehandle, handle});
   }

   void defer_delete_context_sync(void * pNativeContext, GLsync sync)
   {
      if (!sync) return;
      if (!pNativeContext)
      {
         g_cDroppedNullContextDeletes.fetch_add(1, ::std::memory_order_relaxed);
         return;
      }
      ::critical_section_lock lock(&g_csHandleDeletion);
      g_mapPendingHandles[pNativeContext].add({e_handle_sync, 0, sync});
   }

   void delete_pending_context_handles(void * pNativeContext)
   {
      if (!pNativeContext) return;
      ::critical_section_lock lock(&g_csHandleDeletion);
      auto p = g_mapPendingHandles.find(pNativeContext);
      if (!p) return;
      for (auto & object : p->payload())
      {
         if (object.m_ehandle == e_handle_buffer)
         {
            glDeleteVertexArrays(1, &object.m_handle);
            trace_opengl_resource_deleted(e_handle_buffer);
         }
         else if (object.m_ehandle == e_handle_fbo)
         {
            glDeleteFramebuffers(1, &object.m_handle);
            trace_opengl_resource_deleted(e_handle_fbo);
         }
         else if (object.m_ehandle == e_handle_texture)
         {
            glDeleteTextures(1, &object.m_handle);
            trace_opengl_resource_deleted(e_handle_texture);
         }
         else if (object.m_ehandle == e_handle_renderbuffer)
         {
            glDeleteRenderbuffers(1, &object.m_handle);
         }
         else if (object.m_ehandle == e_handle_vertex_buffer)
         {
            glDeleteBuffers(1, &object.m_handle);
            trace_opengl_resource_deleted(e_handle_vertex_buffer);
         }
         else if (object.m_ehandle == e_handle_sync)
         {
            glDeleteSync(object.m_sync);
            trace_opengl_resource_deleted(e_handle_sync);
         }
         else if (object.m_ehandle == e_handle_program)
         {
            glDeleteProgram(object.m_handle);
         }
      }
      g_mapPendingHandles.erase(pNativeContext);
   }

   void discard_pending_context_handles(void * pNativeContext)
   {
      ::critical_section_lock lock(&g_csHandleDeletion);
      g_mapPendingHandles.erase(pNativeContext);
   }


   model_buffer::model_buffer()
   {

      //m_gluVao = 0;

   }


   model_buffer::~model_buffer()
   {
      for (auto & pair : m_mapContextHandleObject)
      {
         defer_delete_context_handle(pair.element1(), e_handle_buffer, pair.element2().m_handle);
      }
   }


   void model_buffer::initialize_dummy_model(::gpu::context* pgpucontext, ::i32 iVertexCount)
   {

      ::gpu::model_buffer::initialize_dummy_model(pgpucontext, iVertexCount);

   }


   void model_buffer::on_initialize_gpu_context_object()
   {

      ::gpu::model_buffer::on_initialize_gpu_context_object();

   }


   void model_buffer::_defer_apply_input_layout(base_context_handle::object & object)
   {

      ::cast < input_layout > pinputlayout = m_pinputlayout;

      if(::is_set(pinputlayout))
      {
         
         //m_pinputlayout = pgpuinputlayout;
         
         ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;
         
         ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;
         
         if (pbufferVertex)
         {
            
            ::cast < input_layout > pinputlayout = m_pinputlayout;
            
            pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
                                                                   object.m_handle,
                                                                   pbufferVertex->m_gluVbo,
                                                                   pbufferIndex ? pbufferIndex->m_gluVbo : 0
                                                                   );
            
            object.m_bBound = true;
            
         }
         
      }

   }


   void model_buffer::bind2(::gpu::command_buffer* pgpucommandbuffer)
   {
      
      auto gluVertexArrayObject = vertex_array_object();
      
      if(gluVertexArrayObject <= 0)
      {
         
         ::string strMessage;
         
         strMessage = "model_buffer::bind2 VAO is null";
         
         warning(strMessage);
         
         throw ::exception(error_wrong_state, strMessage);
         
      }

      glBindVertexArray(gluVertexArrayObject);
      ::opengl::check_error("");

               ::gpu::enum_model emodel = ::gpu::e_model_none;

      if (m_prenderableParent)
      {

         if (m_prenderableParent->m_prenderableParent)
         {

            emodel = m_prenderableParent->m_prenderableParent->m_egpumodel;
         }
      }

      if (emodel == ::gpu::e_model_wavefront_for_texture)
      {

         GLint enabled = 0;
         GLint size = 0;
         GLint type = 0;
         GLint normalized = 0;
         GLint stride = 0;
         GLint bufferBinding = 0;
         GLint divisor = 0;
         void *offset = nullptr;

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &enabled);

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_SIZE, &size);

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_TYPE, &type);

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_NORMALIZED, &normalized);

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_STRIDE, &stride);

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_BUFFER_BINDING, &bufferBinding);

         glGetVertexAttribiv(1, GL_VERTEX_ATTRIB_ARRAY_DIVISOR, &divisor);

         glGetVertexAttribPointerv(1, GL_VERTEX_ATTRIB_ARRAY_POINTER, &offset);

         informationf("UV attrib: enabled=%d size=%d type=0x%x normalized=%d "
                      "stride=%d buffer=%d offset=%zu divisor=%d",
                      enabled, size, type, normalized, stride, bufferBinding, reinterpret_cast<size_t>(offset),
                      divisor);

         information("");

      }



   }


   GLuint model_buffer::vertex_array_object()
   {
 
      auto & object = context_handle_object();
      
      auto & gluVertexArrayObject = object.m_handle;
      
      if(gluVertexArrayObject == 0)
      {
         glGenVertexArrays(1, &gluVertexArrayObject);
         ::opengl::check_error("");
         trace_opengl_resource_created(e_handle_buffer);
         
         if(gluVertexArrayObject == 74)
         {
            
            information("gluVertexArrayObject == 74");
         
         }
         
         //glBindVertexArray(vertexarrayobject.m_gluVertexArrayObject);
         //::opengl::check_error("");
         
   //      ::cast < memory_buffer > pbufferVertex = m_pbufferVertex;
   //
   //      ::cast < memory_buffer > pbufferIndex = m_pbufferIndex;
   //
   //      if(::is_set(pbufferVertex))
   //      {
   //
   //         ::cast < input_layout > pinputlayout = m_pinputlayout;
   //
   //         pinputlayout->__do_opengl_vao_vbo_and_ebo_input_layout(
   //                                                gluVertexArrayObject,
   //                                                                pbufferVertex->m_gluVbo,
   //                                                                pbufferIndex ? pbufferIndex->m_gluVbo : 0
   //                                                                );
   //
   //      }
         
         //glBindVertexArray(0);
         //::opengl::check_error("");
      }
      
      if(m_pinputlayout && !object.m_bBound)
      {
         
         _defer_apply_input_layout(object);
        
      }
      
      return gluVertexArrayObject;

   }


   void model_buffer::draw2(::gpu::command_buffer* pgpucommandbuffer)
   {

      GLenum mode = GL_TRIANGLES;

      auto pshaderBound = pgpucommandbuffer->m_pgpurendertarget->m_pgpurenderer->m_pgpucontext->m_pshaderBound;

      if (pshaderBound)
      {

         auto etopology = pshaderBound->m_etopology;

         mode = ::opengl::as_gl_draw_mode(etopology);

      }



      if (m_pbufferVertex)
      {

         if (m_pbufferIndex)
         {

            GLenum etype;

            if (m_pmodeldatabase2->index_type_size() == 1)
            {

               etype = GL_UNSIGNED_BYTE;

            }
            else if (m_pmodeldatabase2->index_type_size() == 2)
            {

               etype = GL_UNSIGNED_SHORT;

            }
            else
            {

               etype = GL_UNSIGNED_INT;

            }
            
            auto iIndexCount = m_pmodeldatabase2->index_count();
            
            glDrawElements(mode, (::i32) iIndexCount, etype, 0);
            ::opengl::check_error("");

         }
         else
         {
            
            auto iVertexCount = m_pmodeldatabase2->vertex_count();

            glDrawArrays(mode, 0, (::i32) iVertexCount);
            ::opengl::check_error("");

         }

      }
      else
      {
         
         auto iVertexCount = m_pmodeldatabase2->vertex_count();

         glDrawArrays(mode, 0, (::i32) iVertexCount);
         ::opengl::check_error("");

      }

   }


   void model_buffer::draw_lines(::gpu::command_buffer* pgpucommandbuffer)
   {

      if (m_pbufferVertex)
      {

         //if (m_pbufferIndex)
         //{

         //   GLenum etype;

         //   if (m_iSizeIndex == 1)
         //   {

         //      etype = GL_UNSIGNED_BYTE;

         //   }
         //   else if (m_iSizeIndex == 2)
         //   {

         //      etype = GL_UNSIGNED_SHORT;

         //   }
         //   else
         //   {

         //      etype = GL_UNSIGNED_INT;

         //   }

         //   glDrawElements(GL_TRIANGLES, m_iIndexCount, etype, 0);
         //   ::opengl::check_error("");

         //}
         //else
         {

            glDrawArrays(GL_LINES, 0, (::i32) m_pmodeldatabase2->vertex_count());
            ::opengl::check_error("");

         }

      }
      else
      {

         glDrawArrays(GL_LINES, 0, (::i32) m_pmodeldatabase2->vertex_count());
         ::opengl::check_error("");

      }

   }


   void model_buffer::unbind(::gpu::command_buffer* pgpucommandbuffer)
   {

//      if (m_pbufferVertex)
//      {
//
//         if (m_pbufferIndex)
//         {
//
//            m_pbufferIndex->unbind();
//
//         }
//
//         m_pbufferVertex->unbind();
//
//      }

      glBindVertexArray(0);
      ::opengl::check_error("");

   }


} // namespace gpu_opengl



