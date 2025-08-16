#pragma once


#include "acme/prototype/mathematics/mathematics.h"
#include "bred/graphics3d/model.h"


namespace graphics3d
{



   class shape_factory
   {
   public:

      const static inline auto π = ::mathematics::mathematics::πf();

      struct Vertex
      {

         ::glm::vec3    m_position;
         ::glm::vec3    m_color;
         ::glm::vec2    m_uv;

         /*Vertex() {}

         Vertex(
            const ::glm::vec3& position,
            const ::glm::vec3& color,
            const ::glm::vec3& uv
         ) :
            m_position(position),
            m_color(color),
            m_uv(uv)
         {}*/

      };

      using shape = ::graphics3d::model_data < Vertex >;
      //struct shape {
      //   ::array<float> vertices;  // Positions, colors, texture coordinates, and normals
      //   ::array<unsigned int> indices;
      //};

      // Generate a graphics3d with position, color, texture coordinates, and normals
      static shape create_cube(float size) 
      {
         shape shape;

         float halfSize = size / 2.0f;

         // Vertices for a graphics3d
         shape.m_vertices ={
            // Front face
            {{ -halfSize, -halfSize,  halfSize}, { -0.5f, -0.5f,  0.5f},  { 0.0f, 0.0f}},   // bottom-left (red)
            {{ halfSize, -halfSize,  halfSize},   {0.5f, -0.5f,  0.5f},   {1.0f, 0.0f}},   // bottom-right (green)
            {{ halfSize,  halfSize,  halfSize},   { 0.5f,  0.5f,  0.5f},   {1.0f, 1.0f}},   // top-right (blue)
            {{-halfSize,  halfSize,  halfSize},   {-0.5f,  0.5f,  0.5f},   {0.0f, 1.0f}},   // top-left (yellow)

            // Back face
            {{-halfSize, -halfSize, -halfSize},   {1.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},   // bottom-left (purple)
            {{ halfSize, -halfSize, -halfSize},    {0.0f, 1.0f, 1.0f},  { 1.0f, 0.0f}},   // bottom-right (cyan)
            {{ halfSize,  halfSize, -halfSize},    {1.0f, 1.0f, 1.0f},   {1.0f, 1.0f}},   // top-right (white)
            {{-halfSize,  halfSize, -halfSize},    {0.5f, 0.5f, 0.5f},   {0.0f, 1.0f}},   // top-left (gray)

            // Left face
            {{-halfSize, -halfSize, -halfSize},    {0.5f, 0.0f, 0.5f}, {0.0f, 0.0f}},   // bottom-left (pink)
            {{-halfSize, -halfSize,  halfSize},    {0.0f, 0.5f, 0.5f},   {1.0f, 0.0f}},   // bottom-right (light blue)
            {{-halfSize,  halfSize,  halfSize},    {0.5f, 1.0f, 0.0f},   {1.0f, 1.0f}},   // top-right (orange)
            {{-halfSize,  halfSize, -halfSize},    {1.0f, 0.5f, 0.0f},   {0.0f, 1.0f}},   // top-left (dark yellow)

            // Right face
            {{ halfSize, -halfSize, -halfSize},    {1.0f, 0.0f, 0.5f},   {0.0f, 0.0f}},   // bottom-left (purple)
            {{ halfSize, -halfSize,  halfSize},    {0.0f, 0.5f, 1.0f},   {1.0f, 0.0f}},   // bottom-right (light blue)
            {{ halfSize,  halfSize,  halfSize},    {1.0f, 0.5f, 0.0f},   {1.0f, 1.0f}},   // top-right (orange)
            {{ halfSize,  halfSize, -halfSize},    {0.5f, 1.0f, 1.0f},   {0.0f, 1.0f}},   // top-left (light green)

             // Top face
             {{-halfSize,  halfSize, -halfSize},    {0.5f, 0.0f, 0.0f},   {0.0f, 0.0f}},   // bottom-left (dark red)
             {{-halfSize,  halfSize,  halfSize},    {0.0f, 0.5f, 0.0f},   {1.0f, 0.0f}},   // bottom-right (light green)
             {{ halfSize,  halfSize,  halfSize},    {0.0f, 0.0f, 0.5f},   {1.0f, 1.0f}},   // top-right (dark blue)
             {{ halfSize,  halfSize, -halfSize},    {1.0f, 0.5f, 0.5f},   {0.0f, 1.0f}},   // top-left (light pink)

              // Bottom face
              {{-halfSize, -halfSize, -halfSize},    {0.5f, 0.0f, 0.5f},   {0.0f, 1.0f}},   // bottom-left (dark purple)
              {{-halfSize, -halfSize,  halfSize},    {0.5f, 0.5f, 0.0f},   {1.0f, 1.0f}},   // bottom-right (light yellow)
              {{ halfSize, -halfSize,  halfSize},    {0.0f, 1.0f, 0.5f},   {1.0f, 0.0f}},   // top-right (light pink)
              {{halfSize, -halfSize, -halfSize},    {0.0f, 0.0f, 1.0f},   {0.0f, 0.0f}},   // top-left (dark blue)
         };


         // Indices for the graphics3d (two triangles per face)
         shape.m_indices = {
            // Front face
            0, 1, 2,  2, 3, 0,

            // Back face
            4, 5, 6,  6, 7, 4,

            // Left face
            8, 9, 10, 10, 11, 8,

            // Right face
            12, 13, 14, 14, 15, 12,

            // Top face
            16, 17, 18, 18, 19, 16,

            // Bottom face
            20, 21, 22, 22, 23, 20,
         };

         return shape;

      }


      // Generate a plane (XZ plane by default) with position, texture coords, and normals
      static shape create_plane(float width, float depth) {
         shape shape;

         float halfWidth = width / 2.0f;
         float halfDepth = depth / 2.0f;

         // Vertices for a plane
         shape.m_vertices = {
            // Position               // Color           // texture coords 
            {{ -halfWidth, 0.0f, -halfDepth}, { 1.0f, 0.0f, 0.0f},  {0.0f, 0.0f}},
           { { halfWidth, 0.0f, -halfDepth},  {0.0f, 1.0f, 0.0f},  {1.0f, 0.0f}},
           { { halfWidth, 0.0f,  halfDepth}, { 0.0f, 0.0f, 1.0f},  {1.0f, 1.0f}},
           { {-halfWidth, 0.0f,  halfDepth}, { 1.0f, 1.0f, 0.0f},  {0.0f, 1.0f}},
         };

         // Indices for a plane (two triangles)
         shape.m_indices = {
             0, 1, 2, 2, 3, 0
         };

         return shape;
      }

      // Generate a wall (XY plane by default) with position, texture coords, and normals
      static shape create_wall(float width, float height) {
         shape shape;

         float halfWidth = width / 2.0f;
         float halfHeight = height / 2.0f;

         // Vertices for a wall
         shape.m_vertices ={
            // Position               // Color           // texture coords 
            {{ -halfWidth, -halfHeight, 0.0f},  {-0.5f, -0.5f,  0.5f},   {0.0f, 0.0f}},   // bottom-left (red)
            {{ halfWidth, -halfHeight, 0.0f},   {0.5f, -0.5f,  0.5f},   {1.0f, 0.0f}},   // bottom-right (green)
            {{ halfWidth,  halfHeight, 0.0f},   { 0.5f,  0.5f,  0.5f},   {1.0f, 1.0f}},   // top-right (blue)
            {{-halfWidth,  halfHeight, 0.0f},   {-0.5f,  0.5f,  0.5f},   {0.0f, 1.0f}},   // top-left (yellow)
         };


         // Indices for a wall (two triangles)
         shape.m_indices ={
             0, 1, 2, 2, 3, 0
         };

         return shape;
      }

      static shape create_sphere(float radius, unsigned int sectorCount, unsigned int stackCount) {
         shape shape;

         float xy;                               // vertex position
         float lengthInv = 1.0f / radius;     // normal
         //float s, t;                                      // texture coordinates

         float sectorStep = 2 * π / sectorCount;
         float stackStep = π / stackCount;
         float sectorAngle, stackAngle;
         Vertex vertex;

         for (unsigned int i = 0; i <= stackCount; ++i) {
            stackAngle = π / 2 - i * stackStep;        // from pi/2 to -pi/2
            xy = radius * cosf(stackAngle);              // r * cos(u)
            vertex.m_position.z = radius * sinf(stackAngle);               // r * sin(u)

            // add (sectorCount+1) vertices per stack
            // the first and last vertices have same position and normal, but different tex coords
            for (unsigned int j = 0; j <= sectorCount; ++j) {
               sectorAngle = j * sectorStep;           // from 0 to 2pi

               // vertex position (x, y, z)
               vertex.m_position.x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
               vertex.m_position.y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)

               // normalized vertex normal (nx, ny, nz)
               vertex.m_color.x = vertex.m_position.x * lengthInv;
               vertex.m_color.y = vertex.m_position.y * lengthInv;
               vertex.m_color.z = vertex.m_position.z * lengthInv;

               // vertex tex coord (s, t) range between [0, 1]
               vertex.m_uv.x = (float)j / sectorCount;
               vertex.m_uv.y = (float)i / stackCount;

               shape.m_vertices.add(vertex);

            }
         }

         // Indices
         unsigned int k1, k2;
         for (unsigned int i = 0; i < stackCount; ++i) {
            k1 = i * (sectorCount + 1);     // beginning of current stack
            k2 = k1 + sectorCount + 1;      // beginning of next stack

            for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2) {
               if (i != 0) {
                  // triangle 1
                  shape.m_indices.add(k1);
                  shape.m_indices.add(k2);
                  shape.m_indices.add(k1 + 1);
               }

               if (i != (stackCount - 1)) {
                  // triangle 2
                  shape.m_indices.add(k1 + 1);
                  shape.m_indices.add(k2);
                  shape.m_indices.add(k2 + 1);
               }
            }
         }

         return shape;
      }

      //// Generate a ray with a specified length
      //static shape CreateRay(float length) {
      //   shape shape;

      //   // Define vertices for the ray (start at origin, end at specified length)
      //   shape.vertices = {
      //       0.0f, 0.0f, 0.0f,  // Ray start
      //       0.0f, 0.0f, length, // Ray end
      //   };

      //   // Define indices for the ray (one line)
      //   shape.indices = {
      //       0, 1,
      //   };

      //   return shape;
      //}

   };


} // namespace graphics3d


BEGIN_GPU_PROPERTIES(::graphics3d::shape_factory::Vertex)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("color", ::gpu::e_type_seq3)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()




