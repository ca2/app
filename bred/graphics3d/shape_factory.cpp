// Created by camilo on 2025-08-23 21:23 <3ThomasBorregaardSorensen!!
#include "framework.h"
#include "shape_factory.h"


BEGIN_GPU_PROPERTIES(::graphics3d::shape_factory::Vertex)
GPU_PROPERTY("position", ::gpu::e_type_seq3)
GPU_PROPERTY("normal", ::gpu::e_type_seq3)
GPU_PROPERTY("uv", ::gpu::e_type_seq2)
END_GPU_PROPERTIES()


namespace graphics3d
{


   shape_factory::shape_factory()
   {


   }


   shape_factory ::~shape_factory()
   {


   }


      // Generate a graphics3d with position, color, texture coordinates, and normals
   ::pointer < ::graphics3d::renderable > shape_factory::create_cube_001(::gpu::context * pgpucontext, float size)
   {
      shape shape;

      float halfSize = size / 2.0f;

     shape.m_vertexes = {
         // Front face  (normal =  0, 0,  1)
         {{-halfSize, -halfSize, halfSize}, {0.0f, 0.0f, 1.0f}, {0.0f, 0.0f}}, // bottom-left
         {{halfSize, -halfSize, halfSize}, {0.0f, 0.0f, 1.0f}, {1.0f, 0.0f}}, // bottom-right
         {{halfSize, halfSize, halfSize}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}}, // top-right
         {{-halfSize, halfSize, halfSize}, {0.0f, 0.0f, 1.0f}, {0.0f, 1.0f}}, // top-left

         // Back face   (normal =  0, 0, -1)
         {{-halfSize, -halfSize, -halfSize}, {0.0f, 0.0f, -1.0f}, {0.0f, 0.0f}}, // bottom-left
         {{halfSize, -halfSize, -halfSize}, {0.0f, 0.0f, -1.0f}, {1.0f, 0.0f}}, // bottom-right
         {{halfSize, halfSize, -halfSize}, {0.0f, 0.0f, -1.0f}, {1.0f, 1.0f}}, // top-right
         {{-halfSize, halfSize, -halfSize}, {0.0f, 0.0f, -1.0f}, {0.0f, 1.0f}}, // top-left

         // Left face   (normal = -1, 0,  0)
         {{-halfSize, -halfSize, -halfSize}, {-1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // bottom-left
         {{-halfSize, -halfSize, halfSize}, {-1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // bottom-right
         {{-halfSize, halfSize, halfSize}, {-1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // top-right
         {{-halfSize, halfSize, -halfSize}, {-1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // top-left

         // Right face  (normal =  1, 0,  0)
         {{halfSize, -halfSize, -halfSize}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}}, // bottom-left
         {{halfSize, -halfSize, halfSize}, {1.0f, 0.0f, 0.0f}, {1.0f, 0.0f}}, // bottom-right
         {{halfSize, halfSize, halfSize}, {1.0f, 0.0f, 0.0f}, {1.0f, 1.0f}}, // top-right
         {{halfSize, halfSize, -halfSize}, {1.0f, 0.0f, 0.0f}, {0.0f, 1.0f}}, // top-left

         // Top face    (normal =  0, 1,  0)
         {{-halfSize, halfSize, -halfSize}, {0.0f, 1.0f, 0.0f}, {0.0f, 0.0f}}, // bottom-left
         {{-halfSize, halfSize, halfSize}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}}, // bottom-right
         {{halfSize, halfSize, halfSize}, {0.0f, 1.0f, 0.0f}, {1.0f, 1.0f}}, // top-right
         {{halfSize, halfSize, -halfSize}, {0.0f, 1.0f, 0.0f}, {0.0f, 1.0f}}, // top-left

         // Bottom face (normal =  0,-1,  0)
         {{-halfSize, -halfSize, -halfSize}, {0.0f, -1.0f, 0.0f}, {0.0f, 1.0f}}, // bottom-left
         {{-halfSize, -halfSize, halfSize}, {0.0f, -1.0f, 0.0f}, {1.0f, 1.0f}}, // bottom-right
         {{halfSize, -halfSize, halfSize}, {0.0f, -1.0f, 0.0f}, {1.0f, 0.0f}}, // top-right
         {{halfSize, -halfSize, -halfSize}, {0.0f, -1.0f, 0.0f}, {0.0f, 0.0f}}, // top-left
      };


      // Indices for the graphics3d (two triangles per face)
      shape.m_indexes = {
         // Front face
         0,
         1,
         2,
         2,
         3,
         0,

         // Back face
         4,
         5,
         6,
         6,
         7,
         4,

         // Left face
         8,
         9,
         10,
         10,
         11,
         8,

         // Right face
         12,
         13,
         14,
         14,
         15,
         12,

         // Top face
         16,
         17,
         18,
         18,
         19,
         16,

         // Bottom face
         20,
         21,
         22,
         22,
         23,
         20,
      };

      return create_renderable_from_shape(pgpucontext, shape);

   }


   ::pointer<::graphics3d::renderable> shape_factory::create_cube_002(::gpu::context *pgpucontext, float size)
   {
      shape shape;
      float s = size * 0.5f;

      shape.m_vertexes = {

         // +X face (right)
         {{s, -s, -s}, {1, 0, 0}, {0, 0}},
         {{s, -s, s}, {1, 0, 0}, {1, 0}},
         {{s, s, s}, {1, 0, 0}, {1, 1}},
         {{s, s, -s}, {1, 0, 0}, {0, 1}},

         // -X face (left)
         {{-s, -s, s}, {-1, 0, 0}, {0, 0}},
         {{-s, -s, -s}, {-1, 0, 0}, {1, 0}},
         {{-s, s, -s}, {-1, 0, 0}, {1, 1}},
         {{-s, s, s}, {-1, 0, 0}, {0, 1}},

         // +Y face (top)
         {{-s, s, -s}, {0, 1, 0}, {0, 0}},
         {{s, s, -s}, {0, 1, 0}, {1, 0}},
         {{s, s, s}, {0, 1, 0}, {1, 1}},
         {{-s, s, s}, {0, 1, 0}, {0, 1}},

         // -Y face (bottom)
         {{-s, -s, s}, {0, -1, 0}, {0, 0}},
         {{s, -s, s}, {0, -1, 0}, {1, 0}},
         {{s, -s, -s}, {0, -1, 0}, {1, 1}},
         {{-s, -s, -s}, {0, -1, 0}, {0, 1}},

         // +Z face (front)
         {{-s, -s, s}, {0, 0, 1}, {0, 0}},
         {{-s, s, s}, {0, 0, 1}, {0, 1}},
         {{s, s, s}, {0, 0, 1}, {1, 1}},
         {{s, -s, s}, {0, 0, 1}, {1, 0}},

         // -Z face (back)
         {{s, -s, -s}, {0, 0, -1}, {0, 0}},
         {{s, s, -s}, {0, 0, -1}, {0, 1}},
         {{-s, s, -s}, {0, 0, -1}, {1, 1}},
         {{-s, -s, -s}, {0, 0, -1}, {1, 0}},
      };

      // 6 faces × 2 triangles per face
      shape.m_indexes = {
         0,  1,  2,  2,  3,  0, // +X
         4,  5,  6,  6,  7,  4, // -X
         8,  9,  10, 10, 11, 8, // +Y
         12, 13, 14, 14, 15, 12, // -Y
         16, 17, 18, 18, 19, 16, // +Z
         20, 21, 22, 22, 23, 20 // -Z
      };

      return create_renderable_from_shape(pgpucontext, shape);
   }


   // Generate a plane (XZ plane by default) with position, texture coords, and normals
   ::pointer < ::graphics3d::renderable > shape_factory::create_plane(::gpu::context * pgpucontext, float width, float depth)
   {
      shape shape;

      float halfWidth = width / 2.0f;
      float halfDepth = depth / 2.0f;

      // Vertices for a plane
      shape.m_vertexes = {
         // Position               // Color           // texture coords
         {{-halfWidth, 0.0f, -halfDepth}, {1.0f, 0.0f, 0.0f}, {0.0f, 0.0f}},
         {{halfWidth, 0.0f, -halfDepth}, {0.0f, 1.0f, 0.0f}, {1.0f, 0.0f}},
         {{halfWidth, 0.0f, halfDepth}, {0.0f, 0.0f, 1.0f}, {1.0f, 1.0f}},
         {{-halfWidth, 0.0f, halfDepth}, {1.0f, 1.0f, 0.0f}, {0.0f, 1.0f}},
      };

      // Indices for a plane (two triangles)
      shape.m_indexes = {0, 1, 2, 2, 3, 0};

      return create_renderable_from_shape(pgpucontext, shape);

   }

   // Generate a wall (XY plane by default) with position, texture coords, and normals
   ::pointer < ::graphics3d::renderable > shape_factory::create_wall(::gpu::context * pgpucontext, float width, float height)
   {
      shape shape;

      float halfWidth = width / 2.0f;
      float halfHeight = height / 2.0f;

      // Vertices for a wall
      shape.m_vertexes = {
         // Position               // Color           // texture coords
         {{-halfWidth, -halfHeight, 0.0f}, {-0.5f, -0.5f, 0.5f}, {0.0f, 0.0f}}, // bottom-left (red)
         {{halfWidth, -halfHeight, 0.0f}, {0.5f, -0.5f, 0.5f}, {1.0f, 0.0f}}, // bottom-right (green)
         {{halfWidth, halfHeight, 0.0f}, {0.5f, 0.5f, 0.5f}, {1.0f, 1.0f}}, // top-right (blue)
         {{-halfWidth, halfHeight, 0.0f}, {-0.5f, 0.5f, 0.5f}, {0.0f, 1.0f}}, // top-left (yellow)
      };

      // Indices for a wall (two triangles)
      shape.m_indexes = {0, 1, 2, 2, 3, 0};

      return create_renderable_from_shape(pgpucontext, shape);

   }

   ::pointer<::graphics3d::renderable> shape_factory::create_sphere(::gpu::context *pgpucontext, float radius,
                                                                          unsigned int sectorCount,
                                                                  unsigned int stackCount)
   {
      shape shape;

      float xy; // vertex position
      float lengthInv = 1.0f / radius; // normal
      // float s, t;                                      // texture coordinates

      float sectorStep = 2 * π / sectorCount;
      float stackStep = π / stackCount;
      float sectorAngle, stackAngle;
      Vertex vertex;

      for (unsigned int i = 0; i <= stackCount; ++i)
      {
         stackAngle = π / 2 - i * stackStep; // from pi/2 to -pi/2
         xy = radius * cosf(stackAngle); // r * cos(u)
         vertex.m_position.z = radius * sinf(stackAngle); // r * sin(u)

         // add (sectorCount+1) vertexes per stack
         // the first and last vertexes have same position and normal, but different tex coords
         for (unsigned int j = 0; j <= sectorCount; ++j)
         {
            sectorAngle = j * sectorStep; // from 0 to 2pi

            // vertex position (x, y, z)
            vertex.m_position.x = xy * cosf(sectorAngle); // r * cos(u) * cos(v)
            vertex.m_position.y = xy * sinf(sectorAngle); // r * cos(u) * sin(v)

            // normalized vertex normal (nx, ny, nz)
            vertex.m_normal.x = vertex.m_position.x * lengthInv;
            vertex.m_normal.y = vertex.m_position.y * lengthInv;
            vertex.m_normal.z = vertex.m_position.z * lengthInv;

            // vertex tex coord (s, t) range between [0, 1]
            vertex.m_uv.x = (float)j / sectorCount;
            vertex.m_uv.y = (float)i / stackCount;

            shape.m_vertexes.add(vertex);
         }
      }

      // Indices
      unsigned int k1, k2;
      for (unsigned int i = 0; i < stackCount; ++i)
      {
         k1 = i * (sectorCount + 1); // beginning of current stack
         k2 = k1 + sectorCount + 1; // beginning of next stack

         for (unsigned int j = 0; j < sectorCount; ++j, ++k1, ++k2)
         {
            if (i != 0)
            {
               // triangle 1
               shape.m_indexes.add(k1);
               shape.m_indexes.add(k2);
               shape.m_indexes.add(k1 + 1);
            }

            if (i != (stackCount - 1))
            {
               // triangle 2
               shape.m_indexes.add(k1 + 1);
               shape.m_indexes.add(k2);
               shape.m_indexes.add(k2 + 1);
            }
         }
      }

            return create_renderable_from_shape(pgpucontext, shape);


   }

   ////// Generate a ray with a specified length
   //::pointer < ::graphics3d::scene_renderable > shape_factory::CreateRay(float length)
   //{
   //    shape shape;

   //   // Define vertexes for the ray (start at origin, end at specified length)
   //   shape.vertexes = {
   //       {0.0f, 0.0f, 0.0f}, // Ray start
   //       0.0f, 0.0f, length, // Ray end
   //   };

   //   // Define indexes for the ray (one line)
   //   shape.m_indexes = {
   //       0, 1,
   //   };

   //   return shape;
   //}



} // namespace graphics3d


