// Created by camilo on 2025-06-02 21:35 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "device.h"
#include "properties.h"


namespace gpu
{


	extern thread_local device* t_pgpudevice;


	CLASS_DECL_BRED::gpu::device* thread_gpu_device()
	{

		return t_pgpudevice;

	}


	void properties_reference::_set_mat4(const ::glm::mat4 & mat4)
	{

		t_pgpudevice->set_mat4(m_blockWithSamplers.data(), mat4);

	}
		
	
	void properties_reference::_set_vec4(const ::glm::vec4& vec4)
	{

		*((::glm::vec4 *)m_blockWithSamplers.data()) = vec4;

	}

	void properties_reference::_set_int(const int& i)
	{

		*((int *)m_blockWithSamplers.data()) = i;

	}


} // namespace gpu



