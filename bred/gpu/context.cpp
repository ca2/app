#include "framework.h"
#include "binding.h"
#include "block.h"
#include "bred_approach.h"
#include "context.h"
#include "debug_scope.h"
#include "device.h"
#include "cpu_buffer.h"
#include "guard.h"
#include "input_layout.h"
#include "memory_buffer.h"
#include "model_buffer.h"
#include "queue.h"
#include "render.h"
#include "renderable.h"
#include "renderer.h"
#include "render_state.h"
#include "render_target.h"
#include "layer.h"
#include "swap_chain.h"
#include "texture.h"
#include "types.h"
#include "acme/exception/interface_only.h"
#include "acme/parallelization/synchronous_lock.h"
#include "aura/platform/application.h"
#include "aura/platform/system.h"
#include "aura/graphics/image/image.h"
#include "acme/filesystem/filesystem/file_context.h"
#include "aura/windowing/window.h"
#include "aura/graphics/image/context.h"

#include "acme/windowing/windowing.h"
#include "bred/gpu/command_buffer.h"
#include "bred/gpu/context_lock.h"
#include "bred/gpu/graphics.h"
#include "bred/platform/timer.h"
#include "bred/graphics3d/engine.h"
#include "bred/graphics3d/immersion_layer.h"
#include "bred/graphics3d/renderable.h"
#include "bred/graphics3d/scene_base.h"
#include "bred/graphics3d/types.h"
#include "ibl/_.h"


struct rgba_from_b_g_push_constants
{

   int mipLevel;
};


DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, rgba_from_b_g_push_constants);


namespace gpu
{

   interlocked_count g_iGpuContext;

   extern thread_local device *t_pgpudevice;

   context::context()
   {

      m_iGpuContext = ++g_iGpuContext;
      // m_pdraw2dgraphics = nullptr;

      m_eoutput = ::gpu::e_output_none;

      m_etype = e_type_undefined;

      m_escene = e_scene_none;

      m_bCreated = false;
   }


   context::~context() {}


   void context::draw() {}


   void context::prepare_for_gpu_read()
   {

      // swap_buffers();
   }


   //void context::start_drawing() {}


   void context::global_transform() {}


   void context::render() {}


   void context::set_bitmap_1(::image::image *pimage) {}


   // void context::swap_buffers()
   //{

   //   ::cast < swap_chain > pswapchain = m_pgpurenderer->m_pgpurendertarget;

   //   if (pswapchain)
   //   {

   //      pswapchain->present();

   //   }

   //}


   void context::create_window_buffer(::windowing::window *pwindow)
   {

      ::cast<device> pgpudevice = m_pgpudevice;

      if (::is_null(pgpudevice))
      {

         throw ::exception(error_null_pointer);
      }

      _create_window_buffer(pwindow);
   }


   void context::_create_window_buffer(::windowing::window *pwindow) {}


   void context::create_cpu_buffer(const ::int_size &size)
   {

      if (size.is_empty())
      {

         return;
      }

      _send(
         [this, size]()
         {
            ::cast<device> pgpudevice = m_pgpudevice;

            if (::is_null(pgpudevice))
            {

               throw ::exception(error_null_pointer);
            }

            ødefer_construct(m_pcpubuffer);

            m_pcpubuffer->initialize_cpu_buffer(this);

            m_pcpubuffer->set_size(size);

            _create_cpu_buffer(size);

            m_bCreated = true;
         });
   }


   void context::defer_create_window_context(::acme::windowing::window *pwindow)
   {

      //send(
        // [this, pwindow]()
         //{
            _defer_create_window_context(pwindow);

      auto pswapchain = get_swap_chain();

      if (!pswapchain->m_bSwapChainInitialized)
      {

         pswapchain->initialize_swap_chain_window(this, pwindow);

      }


      _create_cpu_buffer(pwindow->get_window_rectangle().size());

            m_bCreated = true;
         //});
   }


   void context::_create_cpu_buffer(const ::int_size &size) {}


   void context::_defer_create_window_context(::acme::windowing::window *pwindow) {}


   void context::resize_cpu_buffer(const ::int_size &size)
   {

      send(
         [this, size]()
         {
            if (!m_pcpubuffer)
            {

               return create_cpu_buffer(size);
            }

            _synchronous_lock synchronouslock(m_pcpubuffer->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

            m_pcpubuffer->set_size(size);
         });
   }


   void context::_send(const ::procedure & procedure)
   {

      ::procedure procedureForward = [this, procedure]()
      {

         //_synchronous_lock(this->synchronization());

         //defer_make_current();

         procedure();

      };

      // rear_guard rearguard(this);

      if (procedure.timeout().is_set())
      {

         procedureForward.set_timeout(procedure.timeout());

      }

      if (m_eoutput == e_output_swap_chain)
      {

         m_pacmewindowingwindowWindowSurface->_user_send(procedure);

      }
      else
      {

         ::thread::_send(procedureForward);

      }

   }


   // void context::_post(const ::procedure& procedure)
   //{

   //   //throw ::error_not_supported;

   //   ////auto procedureForward = [this, procedure]()
   //   ////   {

   //   ////      _synchronous_lock(this->synchronization());

   //   ////      procedure();


   //   ////   };

   //   ::thread::_post(procedureForward);

   //}


   ::gpu::texture *context::current_target_texture(::gpu::frame *pgpuframe)
   {

      if (m_pgpucompositor)
      {

         auto ptexture = m_pgpucompositor->current_target_texture(pgpuframe);

         if (ptexture)
         {

            return ptexture;
         }
      }

      return m_pgpurenderer->current_render_target_texture(pgpuframe);
   }


   void context::construct(::pointer<::gpu::shader> &pgpushader)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      try
      {

         if (::is_set(pgpushader))
         {

            pgpushader->m_timeRetire.Now();

            m_shaderaRetire.add(pgpushader);
         }
      }
      catch (...)
      {
      }

      øconstruct(pgpushader);
   }


   void context::manage_retired_objects()
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      for (::collection::index i = 0; i < m_shaderaRetire.size();)
      {

         auto &pshader = m_shaderaRetire[i];

         if (pshader->m_timeRetire.elapsed() > 15_s)
         {

            ::release(pshader);

            m_shaderaRetire.erase_at(i);
         }
         else
         {

            i++;
         }
      }
   }


   void context::start_debug_happening(::gpu::command_buffer *pgpucommandbuffer,
                                       const ::scoped_string &scopedstrDebugHappening)
   {
   }


   void context::end_debug_happening(::gpu::command_buffer *pgpucommandbuffer) {}
   
   void context::on_cube_map_face_image(::image::image * pimage)
   {


   }

   ::gpu::texture *context::texture(const ::file::path &path)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto &ptexture = m_texturemap[path];

      if (!ptexture)
      {

         load_texture(ptexture, path, false);
      }

      return ptexture;
   }


   ::pointer<::gpu::texture> context::create_empty_texture()
   {

      auto ptextureEmpty = øcreate<::gpu::texture>();

      ::int_rectangle rectangleSize(API_CHANGED_ARGUMENT, 1, 1);

      ::gpu::texture_attributes textureattributes(rectangleSize);

      ::gpu::texture_flags textureflags;

      textureflags.m_bShaderResource = true;

      ptextureEmpty->initialize_texture(m_pgpurenderer, textureattributes, textureflags);

      return ptextureEmpty;

   }


   void context::load_texture(::pointer<::gpu::texture> &ptexture, const ::file::path &path, bool bIsSrgb)
   {

      if (ødefer_construct(ptexture))
      {

         ptexture->initialize_texture_from_file_path(m_pgpurenderer, path, bIsSrgb);

      }

   }


   ::gpu::texture *context::generic_texture(const ::file::path &path, bool bSrgb)
   {

      _synchronous_lock synchronouslock(this->synchronization(), DEFAULT_SYNCHRONOUS_LOCK_SUFFIX);

      auto pnode = m_texturemapGeneric.find(path);

      if (!pnode)
      {

         pnode = m_texturemapGeneric.get(path);

         try
         {

            load_generic_texture(pnode->element2(), path, bSrgb);

         }
         catch (...)
         {

            pnode->element2() = nullptr;
         }
      }

      return pnode->element2();
   }


   void context::load_generic_texture(::pointer<::gpu::texture> &ptexture, const ::file::path &path,
                                      bool bSrgb)
   {

      throw interface_only();

      // if (ødefer_construct(ptexture))
      // {
      //
      //    ptexture->initialize_image_texture(m_pgpurenderer, path);
      //
      // }
   }


   void context::load_ktx_texture_from_file_path(::gpu::texture * ptexture, const ::file::path & pathImage)
   {



   }


   void context::load_ktx_texture_from_memory(::gpu::texture * ptexture, const void * data, memsize size)
   {



   }


   void context::layout_input_layout_properties(::gpu::properties *pproperties)
   {

      layout_properties_default(*pproperties);

      // auto &properties = *pproperties;

      // auto pproperty = properties.m_pproperties;

      //::collection::index i = 0;

      // int iSizeWithSamplers = 0;

      // int iSizeWithoutSamplers = 0;

      // while (pproperty->m_pszName)
      //{

      //   int iItemSize = pproperty->get_item_size(true);

      //   int iSize = iItemSize;

      //   //if (pproperty->m_etype == ::gpu::e_type_seq3)
      //   //{

      //   //   if (iSizeWithSamplers % 16 != 0)
      //   //   {

      //   //      iSizeWithSamplers += 16 - iSizeWithSamplers % 16;
      //   //   }

      //   //   // iSize = 16;
      //   //}

      //   ::gpu::property_data data;

      //   data.m_iOffset = iSizeWithSamplers;

      //   properties.m_propertydataa.set_at_grow(i, data);

      //   i++;

      //   iSizeWithSamplers += iSize;

      //   ::string strName(pproperty->m_pszName);

      //   if (!strName.begins("sampler:"))
      //   {

      //      iSizeWithoutSamplers = iSizeWithSamplers;
      //   }

      //   pproperty++;
      //}

      // properties.m_memory.set_size(iSizeWithSamplers);
      // properties.m_blockWithoutSamplers = properties.m_memory(0, iSizeWithoutSamplers);
      // properties.m_blockWithSamplers = properties.m_memory;
   }


   void context::layout_global_ubo(::gpu::properties * pproperties)
   {

      layout_properties_default(*pproperties);
      
   }


   void context::layout_properties_default(::gpu::properties &properties)
   {

      auto pproperty = properties.m_pproperties;

      ::collection::index i = 0;

      int iSizeWithSamplers = 0;

      int iSizeWithoutSamplers = 0;

      while (pproperty->m_pszName)
      {

         int iItemSize = pproperty->get_item_size(true);

         int iSize = iItemSize;

         // if (pproperty->m_etype == ::gpu::e_type_seq3)
         //{

         //   if (iSizeWithSamplers % 16 != 0)
         //   {

         //      iSizeWithSamplers += 16 - iSizeWithSamplers % 16;
         //   }

         //   // iSize = 16;
         //}

         ::gpu::property_data data;

         data.m_iOffset = iSizeWithSamplers;

         properties.m_propertydataa.set_at_grow(i, data);

         i++;

         iSizeWithSamplers += iSize;

         ::string strName(pproperty->m_pszName);

         if (!strName.begins("sampler:"))
         {

            iSizeWithoutSamplers = iSizeWithSamplers;
         }

         pproperty++;
      }


      properties.memory().set_size(iSizeWithSamplers);
      properties.m_blockWithoutSamplers = properties.memory()(0, iSizeWithoutSamplers);
      properties.m_blockWithSamplers = properties.memory();
   }


   void context::layout_push_constants(::gpu::properties &properties, bool bGlobalUbo)
   {

      layout_properties_default(properties);
   }


   void context::_layout_std140_or_std430(::gpu::properties &properties, enum_layout elayout)
   {

      auto pproperty = properties.m_pproperties;

      ::collection::index i = 0;

      int iSizeWithSamplers = 0;

      int iSizeWithoutSamplers = 0;

      while (pproperty->m_pszName)
      {

         int iItemSize = pproperty->get_item_size(true);

         int iSize = iItemSize;

         if (pproperty->m_etype == ::gpu::e_type_array)
         {

            if (iSizeWithSamplers % 16 != 0)
            {

               iSizeWithSamplers += 16 - iSizeWithSamplers % 16;

            }

            //for (int i = 0; i < pproperty->m_iArraySize; i++)
            //{

               
               //_layout_std140_or_std430(*pproperty->m_pproperties, elayout)

            //}



         }
         else if (iItemSize == 4)
         {

            if (iSizeWithSamplers % 4 != 0)
            {

               iSizeWithSamplers += 4 - iSizeWithSamplers % 4;
            }
         }
         else if (iItemSize == 8)
         {

            if (iSizeWithSamplers % 8 != 0)
            {

               iSizeWithSamplers += 8 - iSizeWithSamplers % 8;
            }
         }
         else if (iItemSize == 12)
         {

            if (iSizeWithSamplers % 16 != 0)
            {

               iSizeWithSamplers += 16 - iSizeWithSamplers % 16;
            }

            if (elayout == ::gpu::e_layout_std140) // layout 140
            {

               iSize = 16;
            }
         }
         else
         {

            if (iSizeWithSamplers % 16 != 0)
            {

               iSizeWithSamplers += 16 - iSizeWithSamplers % 16;
            }

            // iSize = 16;
         }


         ::gpu::property_data data;

         data.m_iOffset = iSizeWithSamplers;
         data.m_iItemSize = iItemSize;

         properties.m_propertydataa.set_at_grow(i, data);

         i++;

         iSizeWithSamplers += iSize;

         ::string strName(pproperty->m_pszName);

         if (!strName.begins("sampler:"))
         {

            iSizeWithoutSamplers = iSizeWithSamplers;
         }

         pproperty++;
      }

      properties.memory().set_size(iSizeWithSamplers);
      properties.m_blockWithoutSamplers = properties.memory()(0, iSizeWithoutSamplers);
      properties.m_blockWithSamplers = properties.memory();
   }


   void context::_layout_hlsl(::gpu::properties & properties)
   {

   auto pproperty = properties.m_pproperties;

   ::collection::index i = 0;

   memsize iSizeWithSamplers = 0;

   memsize iSizeWithoutSamplers = 0;

   while (pproperty->m_pszName)
   {

      ::collection::count iItemSize;

      if (pproperty->m_etype == ::gpu::e_type_array)
      {
         ::gpu::properties propertiesNested;

         propertiesNested.m_pproperties = pproperty->m_pproperties;

         //layout_push_constants(propertiesNested, bGlobalUbo);
         _layout_hlsl(propertiesNested);

         iItemSize = propertiesNested.m_blockWithoutSamplers.size();
         iItemSize *= pproperty->m_iArraySize;
      }
      else
      {
         iItemSize = ::gpu::get_type_size(pproperty->m_etype);
      }

      auto iSize = iItemSize;

      if (iItemSize == 4)
      {

         /*if (iSizeWithSamplers % 16 != 0)
         {

            iSizeWithSamplers += 16 - iSizeWithSamplers % 16;
         }*/

         // iSize = (iSize + 15) & ~15;


         ::gpu::property_data data;

         data.m_iOffset = iSizeWithSamplers;

         properties.m_propertydataa.set_at_grow(i, data);

         i++;

         iSizeWithSamplers += 4;

         //if (!pproperty[1].m_pszName)
         //{
         //   break;
         //}
         //if (pproperty[1].m_etype != ::gpu::e_type_array && ::gpu::get_type_size(pproperty[1].m_etype) != 4)
         //{
         //   goto iteration1;
         //}

         //pproperty++;

         ////         ::gpu::property_data data;

         //data.m_iOffset = iSizeWithSamplers;

         //properties.m_propertydataa.set_at_grow(i, data);

         //i++;

         //iSizeWithSamplers += 4;

         //if (!pproperty[1].m_pszName)
         //{
         //   break;
         //}
         //if (pproperty[1].m_etype != ::gpu::e_type_array && ::gpu::get_type_size(pproperty[1].m_etype) != 4)
         //{
         //   goto iteration1;
         //}

         //pproperty++;

         ////::gpu::property_data data;

         //data.m_iOffset = iSizeWithSamplers;

         //properties.m_propertydataa.set_at_grow(i, data);

         //i++;

         //iSizeWithSamplers += 4;

         //if (!pproperty[1].m_pszName)
         //{
         //   break;
         //}
         //if (pproperty[1].m_etype != ::gpu::e_type_array && ::gpu::get_type_size(pproperty[1].m_etype) != 4)
         //{
         //   goto iteration1;
         //}

         //pproperty++;

         ////::gpu::property_data data;

         //data.m_iOffset = iSizeWithSamplers;

         //properties.m_propertydataa.set_at_grow(i, data);

         //i++;

         //iSizeWithSamplers += 4;
      }
      else if (iItemSize == 8)
      {

         if (iSizeWithSamplers % 8 != 0)
         {
            iSizeWithSamplers += 8 - iSizeWithSamplers % 8;
         }

         ::gpu::property_data data;

         data.m_iOffset = iSizeWithSamplers;

         properties.m_propertydataa.set_at_grow(i, data);

         i++;

         iSizeWithSamplers += 8;

         //if (!pproperty[1].m_pszName)
         //{
         //   break;
         //}
         //if (pproperty[1].m_etype != ::gpu::e_type_array && ::gpu::get_type_size(pproperty[1].m_etype) != 8)
         //{
         //   goto iteration1;
         //}

         //pproperty++;

         ////::gpu::property_data data;

         //data.m_iOffset = iSizeWithSamplers;

         //properties.m_propertydataa.set_at_grow(i, data);

         //i++;

         //iSizeWithSamplers += 8;
      }
      else if (iItemSize == 12)
      {

         if (iSizeWithSamplers % 16 > 4)
         {
            
            iSizeWithSamplers += 16 - iSizeWithSamplers % 16;

         }

         ::gpu::property_data data;

         data.m_iOffset = iSizeWithSamplers;

         properties.m_propertydataa.set_at_grow(i, data);

         i++;

         iSizeWithSamplers += 12;

         // if (!pproperty[1].m_pszName)
         //{
         //    break;
         // }
         // if (pproperty[1].m_etype != ::gpu::e_type_array && ::gpu::get_type_size(pproperty[1].m_etype) != 8)
         //{
         //    goto iteration1;
         // }

         // pproperty++;

         ////::gpu::property_data data;

         // data.m_iOffset = iSizeWithSamplers;

         // properties.m_propertydataa.set_at_grow(i, data);

         // i++;

         // iSizeWithSamplers += 8;
      }
      else
      {

         if (iSizeWithSamplers % 16 != 0)
         {

            iSizeWithSamplers += 16 - iSizeWithSamplers % 16;
         }

         iSize = (iSize + 15) & ~15;


         ::gpu::property_data data;

         data.m_iOffset = iSizeWithSamplers;

         properties.m_propertydataa.set_at_grow(i, data);

         i++;

         iSizeWithSamplers += iSize;
      }

      ::string strName(pproperty->m_pszName);

      if (!strName.begins("sampler:"))
      {

         iSizeWithoutSamplers = iSizeWithSamplers;
      }

      pproperty++;
   }

   iSizeWithSamplers = (iSizeWithSamplers + 15) & ~15;
   iSizeWithoutSamplers = (iSizeWithoutSamplers + 15) & ~15;

   properties.memory().set_size(iSizeWithSamplers);
   properties.m_blockWithoutSamplers = properties.memory()(0, iSizeWithoutSamplers);
   properties.m_blockWithSamplers = properties.memory();


}

   //
   // void context::defer_make_current()
   // {
   //
   //
   // }

   ::floating_matrix4 context::defer_transpose(const ::floating_matrix4 & m)
   {

      return m;

   }


   ::floating_matrix4 context::defer_clip_remap_projection(const ::floating_matrix4 & m)
   { return m;

   }


   ::floating_matrix4 context::defer_remap_impact_matrix(const ::floating_matrix4 &m) {
   
      return m;
   
   }



   ::pointer < ::gpu::command_buffer >context::beginSingleTimeCommands(::gpu::queue * pqueue, ::gpu::enum_command_buffer ecommandbuffer)
   {

      ::pointer < command_buffer > pcommandbuffer;

      ødefer_construct(pcommandbuffer);

      pcommandbuffer->initialize_command_buffer(m_pgpurenderer->render_target(), 
         pqueue,
         ecommandbuffer);

      pcommandbuffer->begin_command_buffer(true);

      pcommandbuffer->m_iCommandBufferFrameIndex = 0;

      return pcommandbuffer;

   }


   void context::endSingleTimeCommands(::gpu::command_buffer *pcommandbuffer)
   {

      pcommandbuffer->submit_command_buffer(nullptr);

      pcommandbuffer->wait_commands_to_execute();

   }


   //::pointer<::graphics3d::renderable> context::load_wavefront_obj_renderable(const ::gpu::renderable_t & model)
   //{
   //   // // 1) cache check
   //   // if (auto it = m_mapObjectModel.find(name); it != m_mapObjectModel.end())
   //   //    return it->element2();

   //   // 2) load

   //   ASSERT(model.m_erenderabletype == ::gpu::e_renderable_type_wavefront_obj);

   //   auto prenderable = _load_wavefront_obj_renderable(model);

   //   
   //   // // 3) cache & return
   //   // m_mapObjectModel[name] = model;
   //   return prenderable;

   //}


   //::pointer<::graphics3d::renderable> context::_load_wavefront_obj_renderable(const ::gpu::renderable_t & model)
   //{

   //   auto prenderable = m_pengine->_load_wavefront_obj_renderable(model);

   //   return prenderable;

   //}


   //::pointer<::graphics3d::renderable> context::load_model(const ::gpu::renderable_t & model)
   //{
   //   //ASSERT(model.m_erenderabletype == ::gpu::e_renderable_type_gltf);
   //   auto prenderable = _load_model(model);
   //   return prenderable;

   //   // //if (auto it = m_mapGltfModel.find(name); it != m_mapGltfModel.end())
   //   //   // return it->element2();
   //   //
   //   // auto model = øcreate_pointer<gltf::Model>();
   //   //
   //   // model->loadFromFile(filepath, &m_pgpudevice, m_pgpudevice->graphicsQueue(), gltfFlags, scale);
   //   //
   //   // //m_mapGltfModel[name] = model;
   //   // return model;

   //}


//    ::pointer<::graphics3d::renderable> context::_load_model(const ::gpu::renderable_t & model)
//    {
//
// return {};
//
//    }


   void context::set_viewport(::gpu::command_buffer * pgpucommandbuffer, const ::int_rectangle & rectangle)
   {

      pgpucommandbuffer->set_viewport(rectangle);

   }


   void context::set_scissor(::gpu::command_buffer *pgpucommandbuffer, const ::int_rectangle &rectangle)
   {

      pgpucommandbuffer->set_scissor(rectangle);

   }


   floating_matrix4 context::ortho(float left, float right, float bottom, float top, float zNear,
                           float zFar)
   {

      throw ::interface_only();

      return {1.0f};

   }


   //floating_matrix4 context::rotateFromAxes(const ::floating_sequence3 & right, const ::floating_sequence3 & up,
   //                                        const ::floating_sequence3 & forward) // OpenGL forward = -f
   //{

   //   return {1.0f};
   //}


   //floating_matrix4 context::lookAt(const float_sequence3 & eye, const float_sequence3 & center,

   //                         const float_sequence3 & up)
   //{


   //   return {1.0f};
   //       }



   ::gpu::command_buffer* context::defer_get_upload_command_buffer()
   {

      if (!m_pcommandbufferUpload)
      {

         m_pcommandbufferUpload = beginSingleTimeCommands(m_pgpudevice->transfer_queue());

      }

      return m_pcommandbufferUpload;

   }


   void context::defer_end_upload_command_buffer()
   {

      if (m_pcommandbufferUpload)
      {

         endSingleTimeCommands(m_pcommandbufferUpload);

         m_pcommandbufferUpload.release();

      }

   }


   void context::begin_render(::gpu::command_buffer * pgpucommandbuffer,::gpu::texture * pgputexture)
   {


   }


   void context::end_render(::gpu::command_buffer * pgpucommandbuffer)
   {


   }



   floating_sequence3 context::front(const ::graphics3d::floating_rotation & rotation)
   {

      throw ::interface_only();
      //sequence_type<FLOATING, 3> front() const
      //{

      //   floating_sequence3 front(m_anglePitch.cos() * m_angleYaw.cos(), m_anglePitch.sin(),
      //                            m_anglePitch.cos() * m_angleYaw.sin());

      //   front.normalize();

      //   return front;
      //}


      return {};

   }


   void context::_context_lock()
   {


   }


   void context::_context_unlock()
   {



   }


   bool context::defer_bind2(::gpu::command_buffer *pgpucommandbuffer, ::gpu::shader *pgpushader,
                             ::gpu::texture *pgputexture)
   {

      auto iFrameIndex = pgpucommandbuffer->m_iCommandBufferFrameIndex;
      if (pgpushader == m_pshaderBound
         && pgpushader->m_iFrameBound ==
         iFrameIndex)
      {

         pgpushader->on_bind_already_bound(pgpucommandbuffer, pgputexture);

         return false;

      }

      //auto pgpucommandbuffer = ::gpu::current_command_buffer();

      if (m_pshaderBound && m_pshaderBound != pgpushader)
      {

         end_debug_happening(pgpucommandbuffer);

         m_pshaderBound->unbind(pgpucommandbuffer);

      }

      start_debug_happening(pgpucommandbuffer, "shader changing");

      //auto ptexture = m_pgpurenderer->m_pgpurendertarget->current_texture(::gpu::current_frame());

      pgpushader->bind(pgpucommandbuffer, pgputexture);

      m_pshaderBound = pgpushader;

      return true;

   }


   bool context::defer_bind3(::gpu::command_buffer *pgpucommandbuffer, ::gpu::shader *pgpushader)
   {

      if (pgpushader == m_pshaderBound)
      {


         return false;
      }

      // auto pgpucommandbuffer = ::gpu::current_command_buffer();

      if (m_pshaderBound)
      {

         end_debug_happening(pgpucommandbuffer);

         m_pshaderBound->unbind(pgpucommandbuffer);
      }

      start_debug_happening(pgpucommandbuffer, "shader changing");

      auto ptexture = pgpucommandbuffer->m_pgpurendertarget->current_texture(::gpu::current_frame());

      pgpushader->bind(pgpucommandbuffer, ptexture);

      m_pshaderBound = pgpushader;

      return true;

   }


   void context::defer_unbind(::gpu::shader* pgpushader)
   {


   }


   void context::defer_unbind_shader()
   {

      if (m_pshaderBound)
      {

         auto pshaderBound = m_pshaderBound;

         m_pshaderBound.release();

         pshaderBound->unbind(::gpu::current_command_buffer());

         end_debug_happening(::gpu::current_command_buffer());

      }

   }


   //bool context::defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, memsize size, memory_buffer::enum_type etype)
   //{

   //   if (ødefer_construct(pmemorybuffer))
   //   {

   //      pmemorybuffer->initialize_memory_buffer_with_conext(this, size, etype);

   //      return true;

   //   }

   //   return false;

   //}


   //bool context::defer_construct_new(::pointer < ::gpu::memory_buffer >& pmemorybuffer, const ::block& block, memory_buffer::enum_type etype)
   //{

   //   if (defer_construct_new(pmemorybuffer, block.size(), etype))
   //   {

   //      pmemorybuffer->assign(block.data(), block.size());

   //      return true;

   //   }

   //   return false;

   //}


   void context::create_window_context(::gpu::device* pgpudevice, ::acme::windowing::window* pacmewindowingwindow)
   {

      if (m_etype != e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      m_escene = e_scene_2d;

      m_pacmewindowingwindowWindowSurface = pacmewindowingwindow;

      if (m_htask.is_null())
      {

         branch_synchronously();

         m_pgpudevice = pgpudevice;

         // rear_guard guard(this);

         _send(
            [this, pacmewindowingwindow]()
            {

               auto eoutput = ::gpu::e_output_swap_chain;

               auto pwindowWindow = (::acme::windowing::window *)pacmewindowingwindow;

               auto rectangleWindow = pwindowWindow->get_window_rectangle();

               auto size = rectangleWindow.size();

               initialize_gpu_context(m_pgpudevice, eoutput, pacmewindowingwindow, size);

               if (m_papplication->m_gpu.m_bUseSwapChainWindow)
               {

                  auto pcontextMain = m_pgpudevice->main_context();

                  if (pcontextMain != this)
                  {

                     throw ::exception(error_wrong_state);

                  }

                  auto pswapchain = pcontextMain->get_swap_chain();

                  if (!pswapchain->m_bSwapChainInitialized)
                  {

                     pswapchain->initialize_swap_chain_window(pcontextMain, pacmewindowingwindow);
                  }
               }
            });
      }

   }


   void context::create_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::gpu::enum_scene& escene, const ::int_size& size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      m_eoutput = eoutput;

      m_escene = escene;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      //rear_guard guard(this);

      _send([this, pgpudevice, eoutput, size]()
         {

            initialize_gpu_context(pgpudevice, eoutput, nullptr, size);

         });

   }


   void context::create_draw2d_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, const ::int_size& size)
   {

      if (::is_null(pgpudevice))
      {

         throw ::exception(error_bad_argument);

      }

      if (::is_null(pgpudevice->m_pwindow))
      {

         throw ::exception(error_wrong_state);

      }

      if (!pgpudevice->_is_ok())
      {

         throw ::exception(error_wrong_state);

      }

      m_etype = e_type_draw2d;

      m_escene = e_scene_2d;

      branch_synchronously();

      m_pgpudevice = pgpudevice;

      //rear_guard guard(this);

      m_bD3D11On12Shared = true;

      _send([this, pgpudevice, eoutput, size]()
         {

            initialize_gpu_context(pgpudevice, eoutput, nullptr, size);

         });

   }


   //void context::create_draw2d_window_context(::gpu::device* pgpudevice, const ::gpu::enum_output & eoutput,  ::windowing::window* pwindow)
   //{

   //   m_etype = e_type_draw2d;

   //   branch_synchronously();

   //   m_pgpudevice = pgpudevice;

   //   rear_guard guard(this);

   //   _send([this, pgpudevice, eoutput, pwindow]()
   //      {

   //         initialize_gpu_context(pgpudevice, eoutput, pwindow, {});

   //      });

   //}


   //void context::create_draw2d_off_screen_context(::gpu::device* pgpudevice, const ::gpu::enum_output & eoutput, const::int_size& size)
   //{

   //   m_etype = e_type_draw2d;

   //   branch_synchronously();

   //   m_pgpudevice = pgpudevice;

   //   rear_guard guard(this);

   //   _send([this]()
   //      {

   //         initialize_gpu_context(startcontext);

   //      });

   //}


   //void context::start_gpu_context(const start_context_t& startcontext)
   //{

   //   branch_synchronously();

   //   m_pgpudevice = startcontext.m_pgpudevice;

   //   rear_guard guard(this);

   //   _send([this, &startcontext]()
   //      {

   //         initialize_gpu_context(startcontext);

   //      });

   //}


   void context::initialize_gpu_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::acme::windowing::window* pwindow, const ::int_size& size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_bad_argument);

      }

      if (m_etype == e_type_window)
      {

//         task_set_name("gctx::window");

      }
      else if (m_etype == e_type_graphics3d)
      {

         ASSERT(is_current_task());

         task_set_name("gctx::3d");

      }
      else if (m_etype == e_type_draw2d)
      {

         ASSERT(is_current_task());

         task_set_name("gctx::draw2d");

      }
      else if (m_etype == e_type_generic)
      {

         ASSERT(is_current_task());

         task_set_name("gctx::generic");

      }
      else
      {

         ASSERT(is_current_task());

         task_set_name("gctx::unknown");

      }

      m_pgpudevice = pgpudevice;

      t_pgpudevice = m_pgpudevice;

      m_eoutput = eoutput;

      m_rectangle.top_left() = { 0, 0 };

      m_rectangle.set_size(size);

      on_create_context(pgpudevice, eoutput, pwindow, size);

   }


   void context::on_create_context(::gpu::device* pgpudevice, const ::gpu::enum_output& eoutput, ::acme::windowing::window* pwindow, const ::int_size& size)
   {

      if (size.is_empty())
      {

         throw ::exception(error_wrong_state);

      }

      if (eoutput == ::gpu::e_output_cpu_buffer)
      {

         //if (startcontext.m_callbackImage32CpuBuffer
         //   && !startcontext.m_rectanglePlacement.is_empty())
         //{

         //   ASSERT(startcontext.m_callbackImage32CpuBuffer);
         //   ASSERT(!startcontext.m_rectanglePlacement.is_empty());

         create_cpu_buffer(size);

         //}

      }
      else if (eoutput == ::gpu::e_output_swap_chain)
      {

         defer_create_window_context(pwindow);

      }
      else
      {

         auto r = ::int_rectangle(::int_point{}, size);
         //
         //       ::gpu::rear_guard guard(this);

         send([this, r]()
         {

            _create_cpu_buffer(r.size());

            //::gpu::context_guard guard(this);

         });

      }

   }


   void context::engine_on_frame_context_initialization()
   {



   }


   void context::on_before_initialize_scene()
   {

      onBeforePreloadGlobalAssets();

   }


   void context::onBeforePreloadGlobalAssets()
   {


   }


   //bool context::task_iteration()
   //{

   //   if (!::thread::task_iteration())
   //   {

   //      return false;

   //   }

   //   for (auto prender : m_rendera)
   //   {

   //      if (!prender->render_step())
   //      {

   //         return false;

   //      }

   //   }

   //   return true;

   //}


   void context::lock_context()
   {

      //return ::success;

   }


   void context::unlock_context()
   {

      //return ::success;

   }


   ::gpu::enum_output context::get_eoutput()
   {

      return m_eoutput;

   }


   ::pointer<::gpu::input_layout> context::input_layout(const ::gpu::property *pproperties)
   {

      auto pinputlayout = øcreate<::gpu::input_layout>();

      pinputlayout->initialize_input_layout(this, pproperties);

      return pinputlayout;

   }


   ::gpu::cpu_buffer* context::get_cpu_buffer()
   {

      if (!m_pcpubuffer)
      {

         create_cpu_buffer(m_rectangle.size());

      }

      return m_pcpubuffer;

   }


   //void context::make_current()
   //{

   //   m_pgpudevice->make_current(this);

   //}


   //void context::release_current()
   //{

   //   m_pgpudevice->release_current(this);

   //}


   void context::destroy_cpu_buffer()
   {

      //return ::success_none;

   }


   //void context::set_topic_texture(int iIndex)
   //{

   //   m_iTopicTexture = iIndex;

   //}


   void context::set_cull_face(::gpu::enum_cull_mode ecullmode)
   {

      m_ecullmode = ecullmode;

   }


   ::int_rectangle context::rectangle()
   {

      return m_rectangle;

   }


   void context::set_placement(const ::int_rectangle& rectanglePlacement)
   {

      m_rectangle = rectanglePlacement;

      //get_renderer()->on_context_resize();

   }


   void context::on_resize(const ::int_size& size)
   {

      m_rectangle.top_left() = { 0, 0 };

      m_rectangle.set_size(size);

      if (m_pgpurenderer)
      {

         m_pgpurenderer->on_resize(size);

      }

      if (m_pgpucompositor)
      {

         m_pgpucompositor->on_gpu_context_placement_change(size, m_pgpudevice->m_pwindow);

      }

   }


   void context::assert_there_is_current_context()
   {



   }


   void context::do_on_context(const ::procedure& procedure)
   {

      ///context_guard contextguard(this);

      procedure();

   }


   void context::send_on_context(const ::procedure& procedureParam)
   {

      //::gpu::rear_guard rear_guard(this);

      ::procedure procedure = procedureParam;

      procedure.set_timeout(5_min);

      _send([this, procedure]()
         {

            do_on_context(procedure);

         });

   }


   ////void context::gpu_debug_message(const ::scoped_string& scopedstrMessage)
   //void context::gpu_debug_message(const ::scoped_string& scopedstrMessage)
   //{

   //   //{

   //   //   ::string strMessage(scopedstrMessage);

   //   //   glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
   //   //      GL_DEBUG_TYPE_MARKER,
   //   //      0,
   //   //      GL_DEBUG_SEVERITY_NOTIFICATION,
   //   //      -1,
   //   //      strMessage);

   //   //}

   //}


   ::pointer < ::gpu::pixmap > context::create_gpu_pixmap(const ::int_size& size)
   {

      ::pointer < ::gpu::pixmap > ppixmap;

      if (m_textureaAtlas.is_empty()
         || (!(ppixmap = m_textureaAtlas.last()->create_gpu_pixmap(size))))
      {

         auto ptextureNewAtlas = øcreate<::gpu::texture >();

         ::gpu::texture_attributes textureattributes(::int_rectangle{API_CHANGED_ARGUMENT, 4096, 4096}); 

         ::gpu::texture_flags textureflags;

         textureflags.m_bTransferTarget = true;

         ptextureNewAtlas->initialize_texture(m_pgpurenderer, textureattributes, textureflags);

         m_textureaAtlas.add(ptextureNewAtlas);

         ppixmap = m_textureaAtlas.last()->create_gpu_pixmap(size);

         if (!ppixmap)
         {

            throw ::exception(error_failed);

         }

      }

      return ppixmap;

   }


   ::gpu::swap_chain* context::get_swap_chain()
   {

      if (m_etype != e_type_window)
      {

         //throw ::exception(error_failed);

         return m_pgpudevice->m_pgpucontextMain->get_swap_chain();

//         return nullptr;

      }

      if (!m_pgpuswapchain)
      {

         ødefer_construct(m_pgpuswapchain);

         ///m_pswapchain->initialize_gpu_swap_chain(this, m_pwindow);

      }

      return m_pgpuswapchain;

   }





   void context::top_send_on_context(::gpu::context* pcontextInnerStart, bool bForDrawing, const ::procedure& procedure)
   {

      auto etype = this->m_etype;

      auto eoutput = this->m_eoutput;

      auto rectangleContext = this->rectangle();

      if (m_etype != e_type_window)
      {

         throw ::exception(error_wrong_state);

      }

      if (!bForDrawing)
      {

         m_pgpudevice->on_new_frame();

         //auto pgpudevice = m_papplication->get_gpu_approach()->get_gpu_device();

         m_pgpudevice->start_stacking_layers();

      }

      ::procedure procedureOnContext = [this, pcontextInnerStart, bForDrawing, procedure]()
         {

            auto pgpurenderer = get_gpu_renderer();

            pgpurenderer->do_on_frame(bForDrawing, [this, pcontextInnerStart, bForDrawing, procedure](::gpu::frame* pgpuframe)
               {

                  if (bForDrawing)
                  {

                     pcontextInnerStart->send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
                        {

                           //if (bForDrawing)
                           {

                              auto prenderer = pcontextInnerStart->get_gpu_renderer();

                              prenderer->defer_update_renderer();

                              auto λ = [procedure](::gpu::frame* pgpuframe)
                                 {

                                    procedure();

                                 };

                              prenderer->do_on_frame(bForDrawing, λ);

                           }
                           //else
                           //{

                           //   procedure();

                           //}

                        });

                     if (bForDrawing)
                     {
                        //while (!m_pgpudevice->m_playera || 
                        //   m_pgpudevice->m_playera->count() < 3)
                        //{

                        //   preempt(10_ms);

                        //}

                        auto playera = m_pgpudevice->m_playera;

                        if (playera)
                        {
                           auto prendererBackBuffer = get_gpu_renderer();

                           auto prendertargetBackBuffer = prendererBackBuffer->render_target();

                           auto iFrameIndex = prendertargetBackBuffer->get_frame_index();

                           auto ptextureBackBuffer = prendertargetBackBuffer->current_texture(pgpuframe);

                           merge_layers(ptextureBackBuffer, m_pgpudevice->m_playera);

                           ::cast < swap_chain > pswapchain = get_swap_chain();

                           if (!pswapchain->m_bSwapChainInitialized)
                           {

                              pswapchain->initialize_gpu_swap_chain(prendererBackBuffer);

                           }

                           ::cast < gpu::render_target > pgpurendertarget = pswapchain;

                           if (pgpurendertarget)
                           {

                              if (!pgpurendertarget->m_pgpurenderer)
                              {

                                 pgpurendertarget->initialize_render_target(
                                 m_pgpurenderer,
                                    m_rectangle.size(), 
                                    nullptr);
                                 
                              }

                           }

                           for (auto player : *playera)
                           {

                              if (player->getCurrentCommandBuffer4())
                              {

                                 player->getCurrentCommandBuffer4()->wait_commands_to_execute();

                              }

                           }

                           pswapchain->m_pwindowSwapChain->_main_send([pswapchain, ptextureBackBuffer]()
                           // system()->acme_windowing()
                           // ->_main_send([pswapchain, ptextureBackBuffer]()
                           {

                              pswapchain->present(ptextureBackBuffer);

                           });

                        }

                     }

                  }
                  else
                  {

                     pcontextInnerStart->send_on_context([this, pcontextInnerStart, bForDrawing, procedure]()
                        {

                           //if (bForDrawing)
                           {

                              auto prenderer = pcontextInnerStart->get_gpu_renderer();

                              prenderer->defer_update_renderer();

                              auto λ = [procedure](::gpu::frame* pgpuframe)
                                 {

                                    procedure();

                                 };

                              prenderer->do_on_frame(bForDrawing, λ);

                           }
                           //else
                           //{

                           //   procedure();

                           //}

                        });

                  }

               });

         };


         if (procedure.timeout().is_set())
         {

            procedureOnContext.set_timeout(procedure.timeout());

         }

         send_on_context(procedureOnContext);

         if (bForDrawing)
         {

            m_pgpudevice->on_end_frame();

         }




   }


   bool context::create_offscreen_graphics_for_swap_chain_blitting(::gpu::graphics* pgraphics, const ::int_size& size)
   {

      return false;

   }


   ::gpu::renderer* context::get_gpu_renderer()
   {

      if (!m_pgpurenderer)
      {

         øconstruct(m_pgpurenderer);

         m_pgpurenderer->initialize_gpu_renderer(this);

         m_pgpurenderer->defer_update_renderer();

      }

      return m_pgpurenderer;

   }


   //::gpu::renderer* context::back_buffer_gpu_renderer()
   //{

   //   if (!m_pgpurendererBackBuffer)
   //   {

   //      øconstruct(m_pgpurendererBackBuffer);

   //      m_pgpurendererBackBuffer->initialize_gpu_renderer(this);

   //      //m_pgpurendererBackBuffer->m_pgpurendertarget->m_iFrameCountRequest = 1;

   //      m_pgpurendererBackBuffer->m_prenderstate->m_estate = ::gpu::e_state_single_frame;

   //      m_pgpurendererBackBuffer->defer_update_renderer();

   //   }

   //   return m_pgpurenderer;

   //}


   //::gpu::renderer* context::draw2d_renderer()
   //{

   //   if (!m_pgpucontextDraw2d->m_pgpurenderer)
   //   {

   //      ::gpu::enum_scene escene = m_escene;

   //      øconstruct(m_pgpucontextDraw2d->m_pgpurenderer);

   //      auto eoutputDraw2d = m_papplication->m_gpu.m_eoutputDraw2d;

   //      m_pgpucontextDraw2d->m_pgpurenderer->initialize_renderer(this, eoutputDraw2d, escene);

   //      m_pgpucontextDraw2d->m_pgpurenderer->set_single_frame();

   //      m_pgpucontextDraw2d->m_pgpurenderer->defer_update_renderer();

   //   }

   //   return m_pgpucontextDraw2d->m_pgpurenderer;

   //}


   //::gpu::renderer* context::graphics3d_renderer()
   //{

   //   if (!m_pgpurendererEngine)
   //   {

   //      ::gpu::enum_scene escene = m_escene;

   //      øconstruct(m_pgpurendererEngine);

   //      auto eoutputEngine = m_papplication->m_gpu.m_eoutputEngine;

   //      m_pgpurendererEngine->initialize_renderer(this, eoutputEngine, escene);

   //      //m_pgpurendererEngine->set_single_frame();

   //      m_pgpurendererEngine->m_iFrameCount2 = ::gpu::render_target::MAX_FRAMES_IN_FLIGHT;

   //      m_pgpurendererEngine->defer_update_renderer();

   //   }

   //   return m_pgpurendererEngine;

   //}


   //::gpu::renderer* context::new_draw2d_renderer()
   //{

   //   ::pointer < ::gpu::renderer > pgpurendererDraw2d;

   //   ::gpu::enum_scene escene = m_escene;

   //   øconstruct(pgpurendererDraw2d);

   //   //auto eoutputDraw2d = m_papplication->m_gpu.m_eoutputDraw2d;

   //   auto eoutputDraw2d = ::gpu::e_output_gpu_buffer;

   //   pgpurendererDraw2d->initialize_renderer(this, eoutputDraw2d, escene);

   //   m_gpurendereraDraw2d.add(pgpurendererDraw2d);

   //   return pgpurendererDraw2d;

   //}



   string context::_001GetIntroProjection()
   {

      string strVersion = get_shader_version_text();


      string strProjection =
         "layout(floating_sequence3 = 0) in floating_sequence3 aPos;\n"
         "layout(floating_sequence3 = 1) in floating_sequence3 aColor;\n"
         "/* out floating_sequence3 ourColor; */\n"
         "out floating_sequence3 ourPosition;\n"
         "\n"
         "void main()\n"
         "{\n"
         "   gl_Position = floating_sequence4(aPos, 1.0);\n"
         "   /* ourColor = aColor;*/\n"
         "   ourPosition = aPos;\n"
         "}\n";

      return strProjection;
   }


   string context::_001GetIntroFragment()
   {

      string strVersion = get_shader_version_text();

      string strFragment =
         "uniform floating_sequence2 resolution;\n"
         "uniform float time;\n"
         "uniform floating_sequence2 mouse;\n"
         "uniform sampler2D backbuffer;\n"
         "\n"
         "void main(void) {\n"
         "floating_sequence2 uv = (gl_FragCoord.xy * 2.0 - resolution.xy) / minimum(resolution.x, resolution.y);\n"
         "\n"
         "gl_FragColor = floating_sequence4(uv, uv/2.0);\n"
         "}\n";

      return strFragment;

   }


   bool context::is_mesa()
   {

      return false;

   }


   string context::load_fragment(const ::scoped_string & scopedstrPath, enum_shader_source& eshadersource)
   {

      ::file::path path(scopedstrPath);

      string strFragment = file()->as_string(path);

      string strExtension = path.all_extensions();

      string strVersion = get_shader_version_text();

      if (strExtension.case_insensitive_begins("shadertoy"))
      {

         eshadersource = e_shader_source_shadertoy;

         strFragment =
            //"#" + strVersion + "\n"
            //"\n"
            //"precision highp float;\n"
            "\n"
            "uniform floating_sequence2 iResolution;\n"
            "uniform float iTime;\n"
            "uniform floating_sequence2 iMouse;\n"
            "uniform sampler2D backbuffer;\n"
            "\n"
            "\n"
            + strFragment;


         strFragment +=
            "\n\n"
            "void main(void)\n"
            "{\n"
            "   mainImage(gl_FragColor, gl_FragCoord.xy);\n"
            "}\n";

      }
      else
      {

         strFragment =
            //            "#" + strVersion + "\n"
            //            "\n"
            +strFragment;

         eshadersource = e_shader_source_neort;

      }

      return strFragment;

   }


   string context::get_shader_version_text()
   {

      return "version 330 core";

   }


   void context::set_matrix_uniform(const ::gpu::payload& payloadMatrix)
   {

      throw interface_only();

   }


   void context::translate_shader(string& strFragment)
   {

      string_array_base stra;

      stra.add_lines(strFragment);

      auto iFind = stra.case_insensitive_find_first_begins("#version ");

      if (found(iFind))
      {

         stra[iFind] = get_shader_version_text();

      }
      else
      {

         stra.insert_at(0, get_shader_version_text());

      }

      _translate_shader(stra);

      strFragment = stra.implode("\n");

   }


   void context::_translate_shader(string_array_base& stra)
   {

   }


   image_data context::image32(const ::payload& payloadFile)
   {

      auto pimage = image()->get_image(payloadFile, { .sync = true, .cache = false });

      class image_data image32;

      image32.m_memory.set_size(pimage->area() * 4);

      {


         auto p = image32.m_memory.data();

         for (auto y = 0; y < pimage->height(); y++)
         {

            auto psource = pimage->line_data(pimage->height() - y - 1);
            for (auto x = 0; x < pimage->width(); x++)
            {

               *p++ = psource->byte_red(pimage->color_indexes());
               *p++ = psource->byte_green(pimage->color_indexes());
               *p++ = psource->byte_blue(pimage->color_indexes());
               *p++ = psource->byte_opacity(pimage->color_indexes());

               psource++;

            }

         }

      }

      image32.m_iWidth = pimage->width();
      image32.m_iHeight = pimage->height();

      return ::transfer(image32);


   }


   image_data context::image24(const ::payload& payloadFile)
   {

      auto pimage = image()->get_image(payloadFile, { .sync = true, .cache = false });

      class image_data image24;

      image24.m_memory.set_size(pimage->area() * 3);

      {


         auto p = image24.m_memory.data();

         for (auto y = 0; y < pimage->height(); y++)
         {

            auto psource = pimage->line_data(pimage->height() - y - 1);
            for (auto x = 0; x < pimage->width(); x++)
            {

               *p++ = psource->byte_red(pimage->color_indexes());
               *p++ = psource->byte_green(pimage->color_indexes());
               *p++ = psource->byte_blue(pimage->color_indexes());

               psource++;

            }

         }

      }

      image24.m_iWidth = pimage->width();
      image24.m_iHeight = pimage->height();

      return ::transfer(image24);

   }


   void context::clear(::gpu::texture * pgputexture, const ::color::color& color)
   {


   }

   
   ::gpu::binding_set *context::global_ubo1_binding_set()
   {

      if (!m_pbindingsetGlobalUbo1)
      {

         øconstruct(m_pbindingsetGlobalUbo1);

         auto pbindingGlobalUbo = m_pbindingsetGlobalUbo1->binding(0);

         pbindingGlobalUbo->m_ebinding = ::gpu::e_binding_global_ubo1;

         pbindingGlobalUbo->m_strUniform = "GlobalUbo";

         pbindingGlobalUbo->m_iBindingPoint2 = 0;

      }

      return m_pbindingsetGlobalUbo1;
   }


   ::gpu::binding_set *context::ibl1_binding_set()
   {

      if (!m_pbindingsetIbl1)
      {

         øconstruct(m_pbindingsetIbl1);

         auto pbindingIrradiance = m_pbindingsetIbl1->binding(0);
         pbindingIrradiance->m_ebinding = ::gpu::e_binding_cube_sampler;
         pbindingIrradiance->m_strUniform = "diffuseIrradianceMap";
         pbindingIrradiance->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_DIFFUSE_IRRADIANCE_MAP;

         auto pbindingPrefiltered = m_pbindingsetIbl1->binding(1);
         pbindingPrefiltered->m_strUniform = "prefilteredEnvMap";
         pbindingPrefiltered->m_ebinding = ::gpu::e_binding_cube_sampler;
         pbindingPrefiltered->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_PREFILTERED_ENV_MAP;

         auto pbindingBrdf = m_pbindingsetIbl1->binding(2);
         pbindingBrdf->m_strUniform = "brdfConvolutionMap";
         pbindingBrdf->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingBrdf->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_BRDF_CONVOLUTION_MAP;

      }

      return m_pbindingsetIbl1;
   }


   ::gpu::binding_set *context::gltf_pbr_binding_set()
   {

      if (!m_pbindingsetGltfPbr)
      {

         øconstruct(m_pbindingsetGltfPbr);

         auto pbindingAlbedo = m_pbindingsetGltfPbr->binding(0);
         pbindingAlbedo->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingAlbedo->m_strUniform = "textureAlbedo";
         pbindingAlbedo->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_ALBEDO;

         auto pbindingNormal = m_pbindingsetGltfPbr->binding(1);
         pbindingNormal->m_strUniform = "textureNormal";
         pbindingNormal->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingNormal->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_NORMAL;

         auto pbindingMetallicRoughness = m_pbindingsetGltfPbr->binding(2);
         pbindingMetallicRoughness->m_strUniform = "textureMetallicRoughness";
         pbindingMetallicRoughness->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingMetallicRoughness->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_METALLIC_ROUGHNESS;

         auto pbindingAmbientOcclusion = m_pbindingsetGltfPbr->binding(3);
         pbindingAmbientOcclusion->m_strUniform = "textureAmbientOcclusion";
         pbindingAmbientOcclusion->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingAmbientOcclusion->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_AMBIENT_OCCLUSION;

         auto pbindingEmissive = m_pbindingsetGltfPbr->binding(4);
         pbindingEmissive->m_strUniform = "textureEmissive";
         pbindingEmissive->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingEmissive->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_EMISSIVE;
      }

      return m_pbindingsetGltfPbr;
   }


   ::gpu::binding_set *context::scene_gltf_pbr_binding_set()
   {

      if (!m_pbindingsetSceneGltfPbr)
      {

         øconstruct(m_pbindingsetSceneGltfPbr);

         auto pbindingAlbedo = m_pbindingsetSceneGltfPbr->binding(0);
         pbindingAlbedo->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingAlbedo->m_strUniform = "textureAlbedo";
         pbindingAlbedo->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_ALBEDO;

         auto pbindingNormal = m_pbindingsetSceneGltfPbr->binding(1);
         pbindingNormal->m_strUniform = "textureNormal";
         pbindingNormal->m_ebinding = ::gpu::e_binding_sampler2d;
         pbindingNormal->m_iTextureUnit = ::gpu::ibl::TEXTURE_UNIT_NORMAL;
      }

      return m_pbindingsetSceneGltfPbr;
   }


   //::gpu::block *context::global_ubo1_block(::gpu::context *pgpucontext)
   //{

   //   if (!m_pblockGlobalUbo)
   //   {

   //      create_global_ubo(pgpucontext);
   //   }

   //   return m_pblockGlobalUbo;
   //}

   void context::update_global_ubo1(::gpu::block * pblockGlobalUbo1)
   {

      pblockGlobalUbo1->update_frame(m_pgpurenderer);

   }


   ::pointer < ::gpu::block > context::create_global_ubo1(const ::gpu::property * ppropertyProperties)
   {

      auto pblock = øcreate<::gpu::block>();

      pblock->set_properties(ppropertyProperties);

      layout_global_ubo(pblock);

      pblock->create_gpu_block(this);

      return pblock;

   }


   void context::update_current_scene()
   {

      auto pscene = m_pengine->m_pimmersionlayer->m_pscene;

      if (pscene->global_ubo1(this)->size(true) > 0)
      {

         pscene->on_update(this);

         update_global_ubo1(pscene->global_ubo1(this));

      }

   }


   //void context::copy(::gpu::texture* ptexture)
   //{

   //   throw ::interface_only();

   //}


   void context::copy(::gpu::texture* ptextureTarget, ::gpu::texture* ptextureSource)
   {

      throw ::interface_only();

   }


   void context::merge_layers(::gpu::texture* ptextureTarget, ::pointer_array < ::gpu::layer >* playera)
   {

      {

          int iLayer = 0;

         for (auto player: *playera)
         {

            if (iLayer == 2)
            {
               // information("What happened to the 3D Layer?");
            }


            //::cast<::gpu_opengl::texture> ptextureSrc = player->texture();

            auto ptextureSrc = player->texture();

            ptextureSrc->wait_fence();

            // m_pshaderBlend3->bind_source(nullptr, ptextureSrc, 0);
            iLayer++;
         }


      }

      ::gpu::context_lock contextlock(this);

      if (!m_pmodelbufferDummy)
      {

         ødefer_construct(m_pmodelbufferDummy);

         m_pmodelbufferDummy->initialize_dummy_model(m_pgpurenderer, 3);

         //m_pmodelbufferDummy->m_iVertexCount = 3;

      }

      {

         if (!m_pshaderBlend3)
         {

            const char full_screen_triangle_vertex_shader[] = R"vert(
#version 330 core

out vec2 uv;

void main() {
    const vec2 pos[3] = vec2[](
        vec2(-1.0, -1.0),
        vec2(-1.0,  3.0),
        vec2( 3.0, -1.0)
    );

    const vec2 tex[3] = vec2[](
        vec2(0.0, 0.0),
        vec2(0.0, 2.0),
        vec2(2.0, 0.0)
    );

    gl_Position = vec4(pos[gl_VertexID], 0.0, 1.0);
    uv = tex[gl_VertexID];
}
)vert";

            const char full_screen_triangle_fragment_shader[] = R"frag(
#version 330 core

uniform sampler2D uTexture;

in vec2 uv;
out vec4 outColor;

void main() {
    vec4 color = texture(uTexture, uv);
    outColor = color;
}
)frag";

            ødefer_construct(m_pshaderBlend3);

            m_pshaderBlend3->m_bEnableBlend = true;
            //m_pshaderBlend3->m_bindingSampler.set();
            m_pshaderBlend3->m_bDisableDepthTest = true;

            auto pbindingSampler = m_pshaderBlend3->binding();
            pbindingSampler->m_ebinding = ::gpu::e_binding_sampler2d;
            pbindingSampler->m_iTextureUnit = 0;
            //m_pshaderBlend3->m_bT
            //m_pshaderBlend3->m_pgpurenderer = this;
            //m_pshaderBlend3->m_setbindingSampler = 0;
            // Image Blend descriptors
            //if (!m_psetdescriptorlayoutImageBlend)

            //m_pshaderBlend3->m_bClearColor = true;
            //m_pshaderBlend3->m_colorClear = ::color::transparent;

            //m_pshaderBlend3->m_bClearColor = false;
            //m_pshaderBlend3->m_colorClear = ::color::transparent;

            m_pshaderBlend3->initialize_shader_with_block(
               m_pgpurenderer,
               ::as_block(full_screen_triangle_vertex_shader),
               ::as_block(full_screen_triangle_fragment_shader),
               {},
               //{},
               //{},
               // this means the vertex input layout will be null/empty
               // the full screen shader is embed in the shader code
               ::gpu::shader::e_flag_clear_default_bindings_and_attributes_descriptions

               );

         }


         //if (!m_pd3d11blendstateBlend3)
         //{

         //   D3D12_BLEND_DESC blendDesc = { 0 };
         //   blendDesc.RenderTarget[0].BlendEnable = TRUE;
         //   blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_ONE;              // Premultiplied alpha
         //   blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;   // Use inverse of alpha
         //   blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;

         //   blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;         // Alpha blending (optional)
         //   blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_INV_SRC_ALPHA;
         //   blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;

         //   blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

         //   ::cast < ::gpu_directx11::device > pgpudevice = m_pgpudevice;

         //   HRESULT hr = pgpudevice->m_pd3d12device->CreateBlendState(&blendDesc, &m_pd3d11blendstateBlend3);
         //   ::defer_throw_hresult(hr);

         //}

         ::cast<renderer> prenderer = m_pgpurenderer;

         ::cast<::gpu::command_buffer> pcommandbuffer = prenderer->getCurrentCommandBuffer2(
            ::gpu::current_frame());

         //auto vkcommandbuffer = pcommandbuffer->m_vkcommandbuffer;

         ::cast<::gpu::texture> ptextureDst = ptextureTarget;

         // int iH = ptextureDst->m_pgpurenderer->m_pgpucontext->m_rectangle.height();
         //
         // ptextureDst->bind_render_target();
         //
         // {
         //
         //    //GLint objName = 0;
         //    //glGetFramebufferAttachmentParameteriv(target, GL_COLOR_ATTACHMENT0,
         //    //   GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &objName);
         //
         //    GLint drawFbo = 0;
         //    glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);
         //
         //    GLint readFbo = 0;
         //    glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFbo);
         //
         //    ::string strMessage;
         //
         //    strMessage.formatf("ø clear drawFbo=%d readFbo=%d tex=%d", drawFbo, readFbo, ptextureDst->m_gluTextureID);
         //
         //    glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
         //                         GL_DEBUG_TYPE_MARKER,
         //                         0,
         //                         GL_DEBUG_SEVERITY_NOTIFICATION,
         //                         -1,
         //                         strMessage);
         //
         // }

         // glClearColor(0.f, 0.f, 0.f, 0.f);
         // GLCheckError("glClearColor");
         // glClearDepth(1.0f);
         // GLCheckError("glClearDepth");
         // glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
         // GLCheckError("glClear");



         if (1)
         {

            int iLayer = 0;

            pcommandbuffer.m_p->begin_render(m_pshaderBlend3.m_p, ptextureDst.m_p);

            this->clear(ptextureDst, ::color::transparent);

            //m_pshaderBlend3, ptextureDst, ptextureSrc);

            for (auto player: *playera)
            {

               if (iLayer == 2)
               {
                  //information("What happened to the 3D Layer?");
               }


                  //::cast<::gpu_opengl::texture> ptextureSrc = player->texture();

                  //ptextureSrc->wait_fence();

                  //::cast<::gpu_opengl::texture> ptextureSrc = player->texture();

                  auto ptextureSrc = player->texture();

                  m_pshaderBlend3->bind_source(nullptr, ptextureSrc, 0);

                  //ptextureSrc->_new_state(
                  //   pcommandbuffer,
                  //   0,
                  //   VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL,
                  //   VK_PIPELINE_STAGE_FRAGMENT_SHADER_BIT
                  //);

                  auto r = ptextureSrc->rectangle();

                  int h = r.height();

                  int iH = ptextureDst->height();

                  r.top = iH - r.bottom;

                  r.bottom = r.top + h;

                  pcommandbuffer->set_viewport(r);

                  pcommandbuffer->set_scissor(r);

                  //m_pmodelbufferDummy->bind(pcommandbuffer);


                  {

                     //GLint objName = 0;
                     //glGetFramebufferAttachmentParameteriv(target, GL_COLOR_ATTACHMENT0,
                     //   GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME, &objName);

                     // GLint drawFbo = 0;
                     // glGetIntegerv(GL_DRAW_FRAMEBUFFER_BINDING, &drawFbo);
                     //
                     // GLint readFbo = 0;
                     // glGetIntegerv(GL_READ_FRAMEBUFFER_BINDING, &readFbo);
                     //
                     // ::string strMessage;
                     //
                     // strMessage.formatf("ø merge%d drawFbo=%d readFbo=%d texDst=%d", iLayer, drawFbo, readFbo,
                     //                    ptextureDst->m_gluTextureID);
                     //
                     // glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
                     //                      GL_DEBUG_TYPE_MARKER,
                     //                      0,
                     //                      GL_DEBUG_SEVERITY_NOTIFICATION,
                     //                      -1,
                     //                      strMessage);

                  }

                  {

                     // GLint activeTex = -1;
                     //
                     // glGetIntegerv(GL_TEXTURE_BINDING_2D, &activeTex); // query the bound texture for target
                     //
                     // auto samplerTex = ptextureSrc->m_gluTextureID;
                     //
                     // ::string strMessage;
                     //
                     // strMessage.formatf("ø merge%d activeTex=%d samplerTex=%d", iLayer, activeTex, samplerTex);
                     //
                     // glDebugMessageInsert(GL_DEBUG_SOURCE_APPLICATION,
                     //                      GL_DEBUG_TYPE_MARKER,
                     //                      0,
                     //                      GL_DEBUG_SEVERITY_NOTIFICATION,
                     //                      -1,
                     //                      strMessage);

                  }

                  pcommandbuffer->draw(m_pmodelbufferDummy);

                  m_pmodelbufferDummy->unbind(pcommandbuffer);

                  //ID3D11SamplerState* samplerstatea[] =
                  //{ ptexture->m_psamplerstate };
                  //ID3D11ShaderResourceView* sharedresourceviewa[] =
                  //{ ptexture->m_pshaderresourceview };

                  // 1. Define viewport and scissor rectangle
                  //D3D12_VIEWPORT viewport = {};
                  //viewport.TopLeftX = ptextureSrc->m_rectangleTarget.left;
                  //viewport.TopLeftY = ptextureSrc->m_rectangleTarget.top;
                  //viewport.Width = static_cast<float>(ptextureSrc->m_rectangleTarget.width());
                  //viewport.Height = static_cast<float>(ptextureSrc->m_rectangleTarget.height());
                  //viewport.MinDepth = 0.0f;
                  //viewport.MaxDepth = 1.0f;

                  //D3D12_RECT scissorRect = {};
                  //scissorRect.left = ptextureSrc->m_rectangleTarget.left;
                  //scissorRect.top = ptextureSrc->m_rectangleTarget.top;
                  //scissorRect.right = ptextureSrc->m_rectangleTarget.right;
                  //scissorRect.bottom = ptextureSrc->m_rectangleTarget.bottom;


                  ////// 4. Set the viewport and scissor
                  //pcommandlist->RSSetViewports(1, &viewport);
                  //pcommandlist->RSSetScissorRects(1, &scissorRect);
                  //D3D11_VIEWPORT vp = {};
                  //vp.TopLeftX = ptexture->rectangle().left;
                  //vp.TopLeftY = ptexture->rectangle().top;
                  //vp.Width = static_cast<float>(ptexture->rectangle().width());
                  //vp.Height = static_cast<float>(ptexture->rectangle().height());
                  //vp.MinDepth = 0.0f;
                  //vp.MaxDepth = 1.0f;
                  //m_pcontext->RSSetViewports(1, &vp);

                  //m_pcontext->PSSetSamplers(0, 1, samplerstatea);
                  //m_pcontext->PSSetShaderResources(0, 1, sharedresourceviewa);


                  //pcommandlist->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
                  //vkCmdDraw(vkcommandbuffer, 3, 1, 0, 0);
               //}
               iLayer++;
               //if (iLayer >= 3)
               //{
               //   break;

               //}
            }
            pcommandbuffer->end_render();
            //m_pshaderBlend3->unbind(pcommandbuffer);
         }
         //}


         ////::cast <texture > ptextureDst = ptextureTarget;
         //{
         //
         //   float clearColor2[4] = { 0.95f * 0.5f, 0.75f * 0.5f, 0.95f * 0.5f, 0.5f }; // Clear to transparent
         //
         //   D3D12_RECT r[1];
         //
         //   r[0].left = 100;
         //   r[0].top = 200;
         //   r[0].right = 200;
         //   r[0].bottom = 300;
         //
         //   pcommandlist->ClearRenderTargetView(
         //      ptextureDst->m_pheapRenderTargetView->GetCPUDescriptorHandleForHeapStart(),
         //      clearColor2,
         //      1, r);

         //}


      }


      //::gpu::context::merge_layers(ptextureTarget, playera);

      ////::gpu::context_lock contextlock(this);

      ////::cast < texture > ptextureDst = ptextureTarget;

      //////if()

      //////GLuint framebuffer;
      //////glGenFramebuffers(1, &framebuffer);
      //////GLCheckError("glGenFramebuffers");
      //////glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer);
      //////GLCheckError("glBindFramebuffer");

      //////auto gluTextureID = ptextureDst->m_gluTextureID;

      //////// Bind the destination texture (textures[textureSrc]) as the framebuffer color attachment
      //////glFramebufferTexture2D(
      //////   GL_DRAW_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D,
      //////   gluTextureID,
      //////   0);
      //////GLCheckError("glFramebufferTexture2D");

      //////if (glCheckFramebufferStatus(GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
      //////   printf("Framebuffer not complete!\n");
      //////   glDeleteFramebuffers(1, &framebuffer);
      //////   return;
      //////}

      //////glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
      ////////glClearColor(0.5f * 0.5f, 0.75f * 0.5f, 0.95f * 0.5f, 0.5f);
      //////glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      ////glFlush();

      ////::cast < renderer > prenderer = m_pgpurenderer;

      ////for (auto& player : *playera)
      ////{

      ////   if (player.is_null())
      ////   {

      ////      continue;

      ////   }

      ////   prenderer->__blend(ptextureTarget, player->texture());

      ////}

      ////glBindFramebuffer(GL_FRAMEBUFFER, 0); // Return to default framebuffer
      ////GLCheckError("glBindFramebuffer");

      ////glDeleteFramebuffers(1, &framebuffer);
      ////GLCheckError("glDeleteFramebuffers");


   }


   void context::on_start_layer(::gpu::layer* player)
   {


   }


   void context::on_end_layer(::gpu::layer* player)
   {

      //::gpu::context_lock contextlock(this);

      defer_unbind_shader();

      if (m_pgpucompositor)
      {

         m_pgpucompositor->on_end_layer(player);

      }

      //auto ptextureTarget = player->texture();

      //auto ptextureSource = current_target_texture(player->m_pgpuframe);

      ////auto ptextureSource = m_pgpurendertarget->current_texture();

      //copy(ptextureTarget, ptextureSource);


   }



   void context::on_create_texture(::gpu::texture* ptexture)
   {


   }


   //void context::on_take_snapshot(layer* player)
   //{


   //}


   void context::on_begin_draw_attach(::gpu::graphics* pgpugraphics)
   {

      draw2d_on_begin_draw(pgpugraphics);

   }

   void context::on_end_draw_detach(::gpu::graphics* pgpugraphics)
   {

      draw2d_on_end_draw(pgpugraphics);

   }


   void context::draw2d_on_begin_draw(::gpu::graphics* pgpugraphics)
   {

      //if (pgpugraphics->m_egraphics == e_graphics_draw)
      //{

      //   pgpugraphics->start_gpu_layer();

      //   //auto pgpurendererDraw2d = get_gpu_renderer();

      //   //if (pgpurendererDraw2d->m_pgpurendertarget)
      //   //{

      //   //   pgpurendererDraw2d->m_pgpurendertarget->on_before_begin_draw_frame(pgpugraphics);

      //   //}

      //   //pgpurendererDraw2d->m_pgpucontext->get_gpu_renderer()->start_frame();

      //   //pgpurendererDraw2d->m_pgpucontext->m_pgpudevice->start_stacking_layers();

      //   //pgpurendererDraw2d->start_layer(rectangle);


      //}

   }


   void context::frame_prefix()
   {


   }


   void context::frame_suffix()
   {


   }





   void context::draw2d_on_end_draw(::gpu::graphics* pgpugraphics)
   {

      //if (pgpugraphics->m_egraphics == e_graphics_draw)
      //{

      //   auto pgpurendererDraw2d = m_pgpurenderer;

      //   pgpurendererDraw2d->end_layer();

      //   //pgpurendererDraw2d->m_pgpucontext->get_gpu_renderer()->end_frame();

      //   //if (pgpurendererDraw2d->m_pgpurendertarget)
      //   //{

      //   //   pgpurendererDraw2d->m_pgpurendertarget->on_after_end_draw_frame(pgpugraphics);

      //   //}

      //}

   }


   void context::__bind_draw2d_compositor(::gpu::compositor* pgpucompositor, ::gpu::layer* player)
   {


   }


   void context::__defer_soft_unbind_draw2d_compositor(::gpu::compositor* pgpucompositor, ::gpu::layer* player)
   {


   }


   ::memory context::rectangle_shader_vert()
   {

      return {};

   }


   ::memory context::rectangle_shader_frag()
   {

      return {};

   }



   ::memory context::white_to_color_sampler_vert()
   {

      return {};

   }


   //void context::white_to_color_sampler_shader_setup(gpu::shader* pshader)
   //{


   //}


   ::memory context::white_to_color_sampler_frag()
   {

      return {};

   }


   // bool context::is_global_ubo_ok()
   // {
   //
   //    return true;
   //
   // }


   void context::initialize_rectangle_shader(::gpu::shader* pshader)
   {

      //auto pcontext = gpu_context();
      //::cast < ::gpu_vulkan::device > pgpudevice = pgpucontext->m_pgpudevice;
      pshader->initialize_shader_with_block(
         m_pgpurenderer,
         rectangle_shader_vert(),
         //as_memory_block(g_uaAccumulationFragmentShader),
         rectangle_shader_frag(),
         //{},
         //{},
         this->input_layout < ::graphics3d::sequence2_color>()
      );

   }


   ::gpu::model_buffer* context::sequence2_uv_fullscreen_quad_model_buffer(::gpu::frame* pgpuframe)
   {

      if (!m_pmodelbufferFullscreenQuad)
      {

         ødefer_construct(m_pmodelbufferFullscreenQuad);

         m_pmodelbufferFullscreenQuad->sequence2_uv_create_fullscreen_quad(pgpuframe);

      }

      return m_pmodelbufferFullscreenQuad;

   }


   //render_target* context::draw2d_render_target()
   //{

   //   return nullptr;

   //}


   //render_target* context::graphics3d_render_target()
   //{

   //   return nullptr;

   //}


   ::pointer<::graphics3d::renderable> context::load_model(const ::gpu::renderable_t & model)
   {

      ::pointer<::graphics3d::renderable> prenderable;

      try
      {

         prenderable = _load_model(model);

         // if (model.m_erenderabletype == ::gpu::e_renderable_type_wavefront_obj)
         // {
         //
         //    prenderable = load_wavefront_obj_renderable(model);
         //
         //    // information("[asset_manager] Successfully loaded OBJ model '{}' from '{}'",
         //    //    model.m_strName,
         //    //    model.m_path);
         //
         // }
         // else if (model.m_erenderabletype == ::gpu::e_renderable_type_gltf)
         // {
         //
         //    //uint32_t flags = entry.get("flags", 0); // Optional flags
         //    //float scale = entry.get("scale", 1.0f); // Optional scale
         //    prenderable = load_gltf_model(model);
         //
         //    //name, path, flags, scale);
         //    // if (entry.get("usage", "") == "skybox" || name == "cube")
         //    // {
         //    //    m_pmodelSkybox = pmodel;
         //    // }
         //
         //    //information("[asset_manager] Successfully loaded glTF model '{}' from '{}'",
         //      // loadmodel.m_strName,
         //       //loadmodel.m_path);
         //
         // }
         // else
         // {
         //
         //    warningf("[context::load_model] Unknown model type '%s' for asset '%s'",
         //       model.m_strRenderableType1.c_str(),
         //       model.m_strName.c_str());
         //
         // }

      }
      catch (const ::exception &e)
      {

         errorf("[asset_manager] Failed to load model '%s': %s", model.m_strName.c_str(), e.get_message().c_str());

      }

      //prenderable->set_emodel(loadmodel.m_emodel);

      //prenderable->set_model_usage(loadmodel.m_emodelusage);

      //
      // if (loadmodel.m_emodelusage == gpu::e_model_usage_default)
      // {
      //
      //    m_prenderableSkybox = prenderable;
      //
      // }

      return prenderable;

   }


   ::pointer<::graphics3d::renderable> context::_load_model(const ::gpu::renderable_t & renderable)
   {

      return {};

   }


   ::pointer<::gpu::texture> context::load_cube_map(
      const ::scoped_string & scopedstrName,
      const ::file::path & path, 
      bool b32)
   {

return {};

   }


   ::pointer<::gpu::texture> context::load_sandbox_texture(const ::scoped_string & scopedstrName,
                                                    const ::file::path & path,
                                                    const ::scoped_string & scopedstrImageFormat)
   {

      return {};

   }

   
   ::pointer<::gpu::texture> context::cubemap_from_hdr(const ::file::path & path)
   {

      return {};

   }


   // ::pointer < ::graphics3d::renderable> context::create_tinyobj_renderable(const ::file::path& path)
   // {
   //
   //    auto pmodel = m_pengine->create_tinyobjloader_model(path);
   //
   //    return pmodel;
   //
   // }

   ::memory context::rgba_from_b_g_vert_memory()
   {

      return {};

   }
   ::memory context::rgba_from_b_g_frag_memory()
   {

      return {};

   }


   ::pointer<::gpu::texture> context::rgba_from_b_g(::gpu::texture *pgputextureMetallic,
                                                    ::gpu::texture *pgputextureRoughness)
   {




      if (!m_pgpushaderRgbaFromB_G)
      {


         auto pshaderRgbaFromB_G = øcreate<::gpu::shader>();

         // m_pshaderBlendRectangle->m_bDisableDepthTest = true;
         pshaderRgbaFromB_G->m_bDisableDepthTest = true;
         // m_pshaderRectangle->m_iColorAttachmentCount = 2;
         pshaderRgbaFromB_G->m_bEnableBlend = false;
         // m_pshaderRectangle->m_bAccumulationEnable = true;


         auto pbindingset = pshaderRgbaFromB_G->binding_set(0);

         auto pbindingMetallic = pbindingset->binding(0);
         pbindingMetallic->m_strUniform = "metallicTex";
         pbindingMetallic->m_ebinding = ::gpu::e_binding_sampler2d;
         auto pbindingRoughness = pbindingset->binding(1);
         pbindingRoughness->m_strUniform = "roughnessTex";
         pbindingRoughness->m_ebinding = ::gpu::e_binding_sampler2d;

         auto pcontext = this;

         pshaderRgbaFromB_G->m_propertiesPushShared.set_properties(::gpu_properties<::rgba_from_b_g_push_constants>());

         pcontext->layout_push_constants(pshaderRgbaFromB_G->m_propertiesPushShared, false);

         //::cast < ::gpu_vulkan::device > pgpudevice = pgpucontext->m_pgpudevice;
         pshaderRgbaFromB_G->initialize_shader_with_block(
            pcontext->m_pgpurenderer, 
            rgba_from_b_g_vert_memory(),
            rgba_from_b_g_frag_memory(),
            pcontext->input_layout<::graphics3d::sequence2_color>());
         m_pgpushaderRgbaFromB_G = pshaderRgbaFromB_G;

      }

      ::gpu::binding_set *pbindingset = m_pgpushaderRgbaFromB_G->binding_set(0);
      ::gpu::binding *pbindingMetallic = m_pgpushaderRgbaFromB_G->binding(0, 0);
      ::gpu::binding *pbindingRoughness = m_pgpushaderRgbaFromB_G->binding(0, 1);

      int w1 = pgputextureMetallic->width();
      int h1 = pgputextureMetallic->height();
      int w2 = pgputextureRoughness->width();
      int h2 = pgputextureRoughness->height();
      ASSERT(w1 == w2 && h1 == h2);

      auto pgputextureMetallicRoughness = øcreate<::gpu::texture>();
      ::int_rectangle r(0, 0, w1, h1);
      ::gpu::texture_attributes textureattributes(r);
      textureattributes.m_iBitsPerChannel = 8;
      textureattributes.m_iChannelCount = 1;
      textureattributes.m_etexture = ::gpu::e_texture_image;
      textureattributes.m_iSrgb = 0;
      textureattributes.m_iFloat = 0;
      textureattributes.m_iLayerCount = 1;
      textureattributes.m_iMipCount= maximum(pgputextureMetallic->m_textureattributes.m_iMipCount,
         pgputextureRoughness->m_textureattributes.m_iMipCount);
      ::gpu::texture_flags textureflags;
      textureflags.m_bRenderTarget = true;
      textureflags.m_bShaderResource = true;
      pgputextureMetallicRoughness->initialize_texture(m_pgpurenderer, textureattributes, textureflags);

                     ::bred::Timer timer;



              auto pgpucommandbuffer = this->beginSingleTimeCommands(m_pgpudevice->graphics_queue());
                     pgputextureMetallicRoughness->set_current_mip(-1);
              pgputextureMetallicRoughness->set_current_layer(0);
                     pgputextureMetallicRoughness->set_state(pgpucommandbuffer,
                                                             ::gpu::e_texture_state_color_attachment);

      ::string strDebugScopeCompute;

      strDebugScopeCompute.format("gpu::context::rgba_from_b_g");

      auto pbindingslotMetallic = m_pgpushaderRgbaFromB_G->binding_slot(0, 0, pbindingMetallic);
      auto pbindingslotRoughness = m_pgpushaderRgbaFromB_G->binding_slot(0, 1, pbindingRoughness);

      pbindingslotMetallic->m_ptexture = pgputextureMetallic;
      pbindingslotRoughness->m_ptexture = pgputextureRoughness;

      pgputextureMetallic->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);
      pgputextureRoughness->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);

      auto pbindingslotset = m_pgpushaderRgbaFromB_G->binding_slot_set(0, pbindingset);

      for (int iMip = 0; iMip < textureattributes.m_iMipCount; iMip++)
      {
         pgputextureMetallicRoughness->set_current_mip(iMip);
         pgputextureMetallicRoughness->set_current_layer(0);

         pgpucommandbuffer->begin_render(m_pgpushaderRgbaFromB_G, pgputextureMetallicRoughness);


         m_pgpushaderRgbaFromB_G->set_int("mipLevel", iMip);

         int_rectangle r;
         r.left = 0;
         r.top = 0;
         r.set_width(pgputextureMetallicRoughness->mip_width());
         r.set_height(pgputextureMetallicRoughness->mip_height());

         pgpucommandbuffer->set_viewport(r);
         m_pgpushaderRgbaFromB_G->push_properties(pgpucommandbuffer);

         pgpucommandbuffer->bind_slot_set(0, pbindingslotset);

         pgpucommandbuffer->draw_vertexes(3);
         pgpucommandbuffer->end_render();
      }

      timer.logDifference("Rendered rgba_from_b_g");
      pgputextureMetallicRoughness->set_current_mip(-1);
      pgputextureMetallicRoughness->set_state(pgpucommandbuffer, ::gpu::e_texture_state_shader_read);
      pgputextureMetallicRoughness->set_ok_flag();

      this->endSingleTimeCommands(pgpucommandbuffer);


      return pgputextureMetallicRoughness;

   }



} // namespace gpu


BEGIN_GPU_PROPERTIES(rgba_from_b_g_push_constants)
GPU_PROPERTY("mipLevel", ::gpu::e_type_int)
END_GPU_PROPERTIES()



