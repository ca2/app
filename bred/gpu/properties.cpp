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


	void properties_reference::_set_mat4(const ::floating_matrix4 & floating_matrix4)
	{

		t_pgpudevice->set_mat4(m_blockWithSamplers.data(), floating_matrix4);

	}
		
	
	void properties_reference::_set_vec4(const ::floating_sequence4& floating_sequence4)
	{

		*((::floating_sequence4 *)m_blockWithSamplers.data()) = floating_sequence4;

	}

	void properties_reference::_set_int(const int& i)
	{

		*((int *)m_blockWithSamplers.data()) = i;

	}


} // namespace gpu



