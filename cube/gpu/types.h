// Created by camilo on 2025-05-22 09:30 PM <3ThomasBorregaardSoerensen!!
#pragma once


#include "acme/constant/gpu.h"


#define GLM_ENABLE_EXPERIMENTAL
#define GLM_FORCE_RADIANS	
#define GLM_FORCE_DEPTH_ZERO_TO_ONE
#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <functional>


#include "acme/graphics/image/image32.h"


namespace gpu
{



   struct start_context_t
   {

      ::particle* m_pparticle;
      ::gpu::device * m_pgpudevice;
      ::gpu::enum_output m_eoutput;
      ::windowing::window* m_pwindow;
      //::image32_callback m_callbackImage32CpuBuffer;
      //::image::target * m_pimagetarget;
      ::function< void(::image::target* ptarget) > m_callbackOnImagePixels;
      ::int_rectangle m_rectanglePlacement;


      start_context_t(::particle* pparticle, ::gpu::device* pgpudevice, const enum_output & eoutput, const ::int_rectangle rectanglePlacement):
         m_pparticle(pparticle),
         m_pgpudevice(pgpudevice),
         m_eoutput(eoutput),
         m_rectanglePlacement(rectanglePlacement),
         m_pwindow(nullptr)
      {


      }

      start_context_t(::particle* pparticle, ::gpu::device* pgpudevice, const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::int_rectangle rectanglePlacement) :
         m_pparticle(pparticle),
         m_pgpudevice(pgpudevice),
         m_eoutput(e_output_cpu_buffer),
         m_callbackOnImagePixels(callbackOnImagePixels),
         m_rectanglePlacement(rectanglePlacement),
         m_pwindow(nullptr)
      {

      }


      start_context_t(::particle* pparticle, ::gpu::device* pgpudevice, ::windowing::window* pwindow) :
         m_pparticle(pparticle),
         m_pgpudevice(pgpudevice),
         m_eoutput(e_output_swap_chain),
         m_pwindow(pwindow),
         m_rectanglePlacement{}
      {

      }

   };


   struct start_gpu_output_context_t :
      public start_context_t
   {

      start_gpu_output_context_t(::particle* pparticle, ::gpu::device* pgpudevice, const enum_output & eoutput, const ::int_rectangle rectanglePlacement) :
         start_context_t(pparticle, pgpudevice, eoutput, rectanglePlacement)
      {
      }

   };


   struct start_cpu_buffer_context_t :
      public start_context_t
   {

      start_cpu_buffer_context_t(::particle* pparticle, ::gpu::device* pgpudevice, const ::function< void(::image::target* ptarget) >& callbackOnImagePixels, const ::int_rectangle rectangleplacement) :
         start_context_t(pparticle, pgpudevice, callbackOnImagePixels, rectangleplacement)
      {
      }

   };


   struct start_swap_chain_context_t :
      public start_context_t
   {

      start_swap_chain_context_t(::particle * pparticle, ::gpu::device* pgpudevice, ::windowing::window* pwindow) :
         start_context_t(pparticle, pgpudevice, pwindow)
      {
      }

   };



	// from: https://stackoverflow.com/a/57595105
	template <typename T, typename... Rest>
	void hash_combine(::hash32& seed, const T& v, const Rest&... rest)
	{
		seed.m_u ^= ::hash32((::uptr)(size_t)::std::hash<T>{}(v)).m_u + 0x9e3779b9 + (seed.m_u << 6) + (seed.m_u >> 2);
		(hash_combine(seed, rest), ...);
	};


	struct Vertex
	{

		glm::vec3 position{};
		glm::vec3 color{};
		glm::vec3 normal{};
		glm::vec2 uv{};

		//static std::vector<VkVertexInputBindingDescription> getBindingDescriptions();
		//static std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions();

		bool operator==(const Vertex& other) const { return position == other.position && normal == other.normal && uv == other.uv; }

	};


} // namespace gpu


template < >
inline ::hash32 as_hash32<gpu::Vertex>(const ::gpu::Vertex& vertex)
{

	hash32 seed{};

	::gpu::hash_combine(seed, vertex.position, vertex.color, vertex.normal, vertex.uv);

	return seed;

}



