#pragma once


#include "bred/graphics3d/model.h"
#include "bred/graphics3d/entity.h"
#include "bred/graphics3d/game_object.h"
//#include "SceneFoundry/graphics3d/object_model.h"
//#include <glm/gtc/matrix_transform.hpp>

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
//    virtual public ::graphics3d::IGameObject
//    {
//    public:
//
//
//       //::graphics3d::transform m_transform;
//       //::pointer<::graphics3d::IModel> m_pmodel;
//       floating_sequence3 m_color{};
//       bool m_bIsOBJ{ false };
// //      ::graphics3d::point_light_component m_pointlight;
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
//       floating_sequence3 color() override;
//
//       // const ::graphics3d::point_light_component * getPointLight() const override {
//       //    return &m_pointlight;
//       // }
//
//       ::graphics3d::transform& transform() override;
//
//       ::graphics3d::IModel * model() override;
//
//       void set_model(::graphics3d::IModel * pmodel) override;
//
//
//
//    };
//
//
// } // namespace sandbox_game
//
//
