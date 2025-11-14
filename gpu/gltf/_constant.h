// From github:/tristancalderbank/OpenGL-PBR-Renderer/constant.h by
// camilo on 2025-09-26 18:28 <3ThomasBorregaardSorensen!!

#pragma once

//#include <glm/glm.hpp>


namespace gpu
{

    namespace gltf
    {
    const auto PI = atan(1)*4;

    const auto mIndentity4 = ::floating_matrix4(1.0f);
    const auto origin = floating_sequence3(0.0f, 0.0f, 0.0f);
    const auto unitX = floating_sequence3(1.0f, 0.0f, 0.0f);
    const auto unitY = floating_sequence3(0.0f, 1.0f, 0.0f);
    const auto unitZ = floating_sequence3(0.0f, 0.0f, 1.0f);

    // colors
    const auto colorWhite = floating_sequence3(1.0, 1.0, 1.0);
    const auto colorRed = floating_sequence3(1.0, 0.0, 0.0);
} // namespace gltf



} // namespace gpu



