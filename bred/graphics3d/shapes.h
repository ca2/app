#pragma once


#include "bred/graphics3d/model.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#include <vector>
#include <glm/glm.hpp>
#include <cmath>
#include <vector>
#include <glm/glm.hpp>

namespace graphics3d
{


   class shape_factory
   {
   public:


      struct Vertex
      {
         ::glm::vec3 m_position;
         ::glm::vec3 m_color;
         ::glm::vec3 m_uv;

      };

      using shape_data = ::graphics3d::model_data < Vertex >;
      //struct ShapeData {
      //   ::array<float> vertexes;  // Positions, colors, texture coordinates, and normals
      //   ::array<unsigned int> indexes;
      //};

      // Generate a graphics3d with position, color, texture coordinates, and normals
      static shape_data CreateCube(float size) {
         shape_data shape;

         float halfSize = size / 2.0f;

         // Vertices for a graphics3d
         shape.vertexes = {
            // Front face
            -halfSize, -halfSize,  halfSize,  -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   // bottom-left (red)
             halfSize, -halfSize,  halfSize,   0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   // bottom-right (green)
             halfSize,  halfSize,  halfSize,    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   // top-right (blue)
            -halfSize,  halfSize,  halfSize,   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   // top-left (yellow)

            // Back face
            -halfSize, -halfSize, -halfSize,   1.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom-left (purple)
             halfSize, -halfSize, -halfSize,    0.0f, 1.0f, 1.0f,   1.0f, 0.0f,   // bottom-right (cyan)
             halfSize,  halfSize, -halfSize,    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,   // top-right (white)
            -halfSize,  halfSize, -halfSize,    0.5f, 0.5f, 0.5f,   0.0f, 1.0f,   // top-left (gray)

            // Left face
            -halfSize, -halfSize, -halfSize,    0.5f, 0.0f, 0.5f,   0.0f, 0.0f,   // bottom-left (pink)
            -halfSize, -halfSize,  halfSize,    0.0f, 0.5f, 0.5f,   1.0f, 0.0f,   // bottom-right (light blue)
            -halfSize,  halfSize,  halfSize,    0.5f, 1.0f, 0.0f,   1.0f, 1.0f,   // top-right (orange)
            -halfSize,  halfSize, -halfSize,    1.0f, 0.5f, 0.0f,   0.0f, 1.0f,   // top-left (dark yellow)

            // Right face
             halfSize, -halfSize, -halfSize,    1.0f, 0.0f, 0.5f,   0.0f, 0.0f,   // bottom-left (purple)
             halfSize, -halfSize,  halfSize,    0.0f, 0.5f, 1.0f,   1.0f, 0.0f,   // bottom-right (light blue)
             halfSize,  halfSize,  halfSize,    1.0f, 0.5f, 0.0f,   1.0f, 1.0f,   // top-right (orange)
             halfSize,  halfSize, -halfSize,    0.5f, 1.0f, 1.0f,   0.0f, 1.0f,   // top-left (light green)

             // Top face
             -halfSize,  halfSize, -halfSize,    0.5f, 0.0f, 0.0f,   0.0f, 0.0f,   // bottom-left (dark red)
             -halfSize,  halfSize,  halfSize,    0.0f, 0.5f, 0.0f,   1.0f, 0.0f,   // bottom-right (light green)
              halfSize,  halfSize,  halfSize,    0.0f, 0.0f, 0.5f,   1.0f, 1.0f,   // top-right (dark blue)
              halfSize,  halfSize, -halfSize,    1.0f, 0.5f, 0.5f,   0.0f, 1.0f,   // top-left (light pink)

              // Bottom face
              -halfSize, -halfSize, -halfSize,    0.5f, 0.0f, 0.5f,   0.0f, 1.0f,   // bottom-left (dark purple)
              -halfSize, -halfSize,  halfSize,    0.5f, 0.5f, 0.0f,   1.0f, 1.0f,   // bottom-right (light yellow)
               halfSize, -halfSize,  halfSize,    0.0f, 1.0f, 0.5f,   1.0f, 0.0f,   // top-right (light pink)
               halfSize, -halfSize, -halfSize,    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // top-left (dark blue)
         };


         // Indices for the graphics3d (two triangles per face)
         shape.indexes = {
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
      static shape_data CreatePlane(float width, float depth) {
         shape_data shape;

         float halfWidth = width / 2.0f;
         float halfDepth = depth / 2.0f;

         // Vertices for a plane
         shape.vertexes = {
            // Position               // Color           // texture coords 
            -halfWidth, 0.0f, -halfDepth,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,
             halfWidth, 0.0f, -halfDepth,  0.0f, 1.0f, 0.0f,  1.0f, 0.0f,
             halfWidth, 0.0f,  halfDepth,  0.0f, 0.0f, 1.0f,  1.0f, 1.0f,
            -halfWidth, 0.0f,  halfDepth,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
         };

         // Indices for a plane (two triangles)
         shape.indexes = {
             0, 1, 2, 2, 3, 0
         };

         return shape;
      }

      // Generate a wall (XY plane by default) with position, texture coords, and normals
      static shape_data CreateWall(float width, float height) {
         shape_data shape;

         float halfWidth = width / 2.0f;
         float halfHeight = height / 2.0f;

         // Vertices for a wall
         shape.vertexes = {
            // Position               // Color           // texture coords 
            -halfWidth, -halfHeight, 0.0f,  -0.5f, -0.5f,  0.5f,   0.0f, 0.0f,   // bottom-left (red)
             halfWidth, -halfHeight, 0.0f,   0.5f, -0.5f,  0.5f,   1.0f, 0.0f,   // bottom-right (green)
             halfWidth,  halfHeight, 0.0f,    0.5f,  0.5f,  0.5f,   1.0f, 1.0f,   // top-right (blue)
            -halfWidth,  halfHeight, 0.0f,   -0.5f,  0.5f,  0.5f,   0.0f, 1.0f,   // top-left (yellow)
         };


         // Indices for a wall (two triangles)
         shape.indexes = {
             0, 1, 2, 2, 3, 0
         };

         return shape;
      }

      static shape_data CreateSphere(float radius, unsigned int sectorCount, unsigned int stackCount) {
         shape_data shape;

         float x, y, z, xy;                               // vertex position
         float nx, ny, nz, lengthInv = 1.0f / radius;     // normal
         float s, t;                                      // texture coordinates

         float sectorStep = 2 * M_PI / sectorCount;
         float stackStep = M_PI / stackCount;
         float sectorAngle, stackAngle;

         for (unsigned int i = 0; i <= stackCount; ++i) {
            stackAngle = M_PI / 2 - i * stackStep;        // from pi/2 to -pi/2
            xy = radius * cosf(stackAngle);              // r * cos(u)
            z = radius * sinf(stackAngle);               // r * sin(u)

            // add (sectorCount+1) vertexes per stack
            // the first and last vertexes have same position and normal, but different tex coords
            for (unsigned int j = 0; j <= sectorCount; ++j) {
               sectorAngle = j * sectorStep;           // from 0 to 2pi

               // vertex position (x, y, z)
               x = xy * cosf(sectorAngle);             // r * cos(u) * cos(v)
               y = xy * sinf(sectorAngle);             // r * cos(u) * sin(v)
               shape.vertexes.push_back(x);
               shape.vertexes.push_back(y);
               shape.vertexes.push_back(z);

               // normalized vertex normal (nx, ny, nz)
               nx = x * lengthInv;
               ny = y * lengthInv;
               nz = z * lengthInv;
               shape.vertexes.push_back(nx);
               shape.vertexes.push_back(ny);
               shape.vertexes.push_back(nz);

               // vertex tex coord (s, t) range between [0, 1]
               s = (float)j / sectorCount;
               t = (float)i / stackCount;
               shape.vertexes.push_back(s);
               shape.vertexes.push_back(t);
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
                  shape.indexes.push_back(k1);
                  shape.indexes.push_back(k2);
                  shape.indexes.push_back(k1 + 1);
               }

               if (i != (stackCount - 1)) {
                  // triangle 2
                  shape.indexes.push_back(k1 + 1);
                  shape.indexes.push_back(k2);
                  shape.indexes.push_back(k2 + 1);
               }
            }
         }

         return shape;
      }

      // Generate a ray with a specified length
      static shape_data CreateRay(float length) {
         shape_data shape;

         // Define vertexes for the ray (start at origin, end at specified length)
         shape.vertexes = {
             0.0f, 0.0f, 0.0f,  // Ray start
             0.0f, 0.0f, length, // Ray end
         };

         // Define indexes for the ray (one line)
         shape.indexes = {
             0, 1,
         };

         return shape;
      }

   };


} // namespace graphics3d_opengl




