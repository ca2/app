// From gpu_directx12/input_layout.cpp by
// camilo on 2025-06-29 08:46 <3ThomasBorregaardSørensen!!
// From gpu_directx11/input_layout.cpp by
// camilo on 2025-06-29 06:06 <3ThomasBorregaardSørensen!!
// From gpu_vulkan/input_layout.cpp by camilo on 2025-06-29 03:55 <3ThomasBorregaardSørensen!!
#include "framework.h"
#include "input_layout.h"


namespace gpu_opengl
{

	input_layout::input_layout()
	{



	}


	input_layout::~input_layout()
	{


	}


   void input_layout::__do_opengl_vao_vbo_and_ebo_input_layout(GLuint gluVAO, GLuint gluVBO, GLuint gluEBO)
	{

		//glBindVertexArray(gluVAO);
		//GLCheckError("");

		//glBindBuffer(GL_ARRAY_BUFFER, gluVBO);
		//GLCheckError("");

		//for(int i = 0; i < m)
		//// vertex positions
		//glEnableVertexAttribArray(0);
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::Vertex), (void*)offsetof(::gpu::Vertex, position));
		//// vertex color
		//glEnableVertexAttribArray(1);
		//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::Vertex), (void*)offsetof(::gpu::Vertex, color));
		//// vertex normals
		//glEnableVertexAttribArray(2);
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(::gpu::Vertex), (void*)offsetof(::gpu::Vertex, normal));
		//// vertex texture coords
		//glEnableVertexAttribArray(3);
		//glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(::gpu::Vertex), (void*)offsetof(::gpu::Vertex, uv));

      int sizeVertex = this->size();

		auto countInputLayout = this->count();

      if (countInputLayout > 0)
      {

         int iOffset = 0;

         for (::collection::index iInputLayout = 0; iInputLayout < countInputLayout; iInputLayout++)
         {

            auto pproperty = this->m_pproperties + iInputLayout;

            auto name = pproperty->m_pszName;
            auto etype = pproperty->m_etype;
				auto size = ::gpu::get_type_size(etype);
				auto countTypeUnit = ::gpu::get_type_unit_count(etype);
				auto opengltypeTypeUnit = ::opengl::get_gpu_type_unit_opengl_type(etype);
            
				glEnableVertexAttribArray((GLuint)iInputLayout);
				GLCheckError("");

            glVertexAttribPointer(
					(GLuint)iInputLayout, 
					countTypeUnit,
					opengltypeTypeUnit, 
					GL_FALSE,
               sizeVertex, 
					(void*)iOffset);
				GLCheckError("");


				iOffset += size;

         }
    
      }

		//if (gluEBO)
		//{
			//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, gluEBO);
			//GLCheckError("");
		//}

		//glBindBuffer(GL_ARRAY_BUFFER, 0);
		//GLCheckError("");

		//glBindVertexArray(0);
		//GLCheckError("");

	}


} // namespace gpu_opengl