#pragma once


#include "bred/sandbox/model.h"
#include "bred/sandbox/entity.h"
#include "bred/sandbox/game_object.h"
#include "SceneFoundry/sandbox_renderer/object_model.h"
#include <glm/gtc/matrix_transform.hpp>

// std
//#include <memory>
//#include <unordered_map>
//////#include <stdexcept>
//
// namespace sandbox_game
// {
//
//
//    class game_object :
//    virtual public ::sandbox::IGameObject
//    {
//    public:
//
//
//       //::sandbox::TransformComponent m_transform;
//       //::pointer<::sandbox::IModel> m_pmodel;
//       glm::vec3 m_color{};
//       bool m_bIsOBJ{ false };
// //      ::sandbox::point_light_component m_pointlight;
//
//       ::string m_cubemapTextureName;
//       long long m_llId;
//       bool m_bIsSkybox = false;
//
//
//
//       game_object();
//       // sandbox_game_object() = default;
//       // sandbox_game_object(const sandbox_game_object&) = delete;
//       // sandbox_game_object& operator=(const sandbox_game_object&) = delete;
//       // sandbox_game_object(sandbox_game_object&&) = default;
//       // sandbox_game_object& operator=(sandbox_game_object&&) = default;
//
//
//       void initialize_game_object(long long llId);
//
//       long long getId() override;
//
//       glm::vec3 color() override;
//
//       // const ::sandbox::point_light_component * getPointLight() const override {
//       //    return &m_pointlight;
//       // }
//
//       ::sandbox::TransformComponent& transform() override;
//
//       ::sandbox::IModel * model() override;
//
//       void set_model(::sandbox::IModel * pmodel) override;
//
//
//
//    };
//
//
// } // namespace sandbox_game
//
//
