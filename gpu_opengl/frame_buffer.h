// Created by camilo on 2025-05-24 20:56 <3ThomasBorregaardSorensen!!
#pragma once


namespace gpu_opengl
{


	class CLASS_DECL_GPU_OPENGL frame_buffer :
		virtual public ::particle
	{
	public:


		GLuint m_fbo;
		GLuint m_tex;
		GLuint m_rbo;
		::int_size m_size;
		bool m_bWithDepthBuffer;


		frame_buffer();
		~frame_buffer() override;


		void create(const ::int_size& size, bool bWithDepthBuffer = false);

		void destroy();
		void bind();
		void unbind();

	};



} // namespace gpu_opengl



