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

#include "bred/graphics3d/scene_object.h"


namespace graphics3d
{

	//
	//
	// struct CLASS_DECL_BRED PointLightComponent
	// {
	// 	float lightIntensity = 1.0f;
	// };

	//
	// class CLASS_DECL_BRED scene_object :
	// 	virtual public ::graphics3d::scene_objects
	// {
	// public:
	//
	//
	// 	using Vertex = ::graphics3d::Vertex;
	//
	// 	::string m_strPath;
	//
	// 	//::collection::index m_iId;
	//
	// 	//::graphics3d::transform m_transform;
	//
	// 	//floating_sequence3 m_color;
	//
	// 	//::graphics3d::model<Vertex> m_pmodel;
	//
	// 	//using map_base = index_map_base < ::pointer < scene_object > >;
	//
	// 	//static interlocked_long_long s_interlockedll;
	//
	//
	// 	scene_object() :
	// 		m_iId{ s_interlockedll++ }
	// 	{
	//
	// 	}
	//
	// 	scene_object& translate(const floating_sequence3& locationOffset)
	// 	{
	//
	// 		m_transform.translation += locationOffset;
	//
	// 		return *this;
	//
	// 	}
	//
	// 	scene_object& scale(const floating_sequence3& poleScaling)
	// 	{
	//
	// 		m_transform.scale *= poleScaling;
	//
	// 		return *this;
	//
	// 	}
	// };

	//
	// class CLASS_DECL_BRED point_light :
	// 	virtual public scene_object
	// {
	// public:
	//
	//
	// 	//
	// 	//    struct point_light_component
	// 	//    {
	// 	//
	// 	        float m_fLightIntensity = 1.0f;
	// 	//
	// 	//    };
	// 	//
	//
	// 	point_light(float intensity = 10.f, float radius = 0.1f, floating_sequence3 color = floating_sequence3(1.f));
	// 	~point_light() override;
	//
	// };


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