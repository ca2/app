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


	void properties_reference::_set_matrix4(const ::floating_matrix4 & matrix4)
	{

		t_pgpudevice->set_matrix4(m_blockWithSamplers.data(), matrix4);

	}
		
	
	void properties_reference::_set_sequence4(const ::floating_sequence4& sequence4)
	{

		*((::floating_sequence4 *)m_blockWithSamplers.data()) = sequence4;

	}


   void properties_reference::_set_sequence3(const ::floating_sequence3 &sequence3)
   {

      *((::floating_sequence3 *)m_blockWithSamplers.data()) = sequence3;

   }

   
   void properties_reference::_set_int(const int& i)
	{

		*((int *)m_blockWithSamplers.data()) = i;

	}


} // namespace gpu



