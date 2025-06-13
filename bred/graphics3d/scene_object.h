// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 03:54 <3ThomasBorregaardSorensen!!
#pragma once

#include "bred/graphics3d/model.h"
#include "bred/graphics3d/types.h"
#include "acme/prototype/collection/map.h"

// libs
#include <glm/gtc/matrix_transform.hpp>

// std
#include <memory>
#include <unordered_map>


namespace graphics3d
{



	struct CLASS_DECL_BRED PointLightComponent
	{
		float lightIntensity = 1.0f;
	};


	class CLASS_DECL_BRED scene_object :
		virtual public ::particle
	{
	public:

		::string m_strPath;

		::collection::index m_iId;

		TransformComponent m_transform;

		glm::vec3 m_color;

		::pointer<model> m_pmodel;

		using map = index_map < ::pointer < scene_object > >;

		static interlocked_long_long s_interlockedll;


		scene_object() :
			m_iId{ s_interlockedll++ }
		{

		}

		scene_object& translate(const glm::vec3& locationOffset)
		{

			m_transform.translation += locationOffset;

			return *this;

		}

		scene_object& scale(const glm::vec3& poleScaling)
		{

			m_transform.scale *= poleScaling;

			return *this;

		}
	};


	class CLASS_DECL_BRED point_light :
		virtual public scene_object
	{
	public:


		PointLightComponent	m_pointlightcomponent;


		point_light(float intensity = 10.f, float radius = 0.1f, glm::vec3 color = glm::vec3(1.f));
		~point_light() override;

	};


} // namespace graphics3d






//
//struct alignas(16) PointLight {
//	DirectX::XMFLOAT4 position;
//	DirectX::XMFLOAT4 color;
//};
//
//struct alignas(16) GlobalUbo {
//	DirectX::XMMATRIX projection;
//	DirectX::XMMATRIX view;
//	DirectX::XMMATRIX invView;
//	DirectX::XMFLOAT4 ambientLightColor;
//	PointLight pointLights[10];
//	int numLights;
//	int padding1;
//	int padding2;
//	int padding3;
//};
//
//struct alignas(16) ObjectMatrices {
//	DirectX::XMMATRIX modelMatrix;
//	DirectX::XMMATRIX normalMatrix;
//};