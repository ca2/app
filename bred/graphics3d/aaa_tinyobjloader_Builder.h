// From V0idsEmbrace@Twich continuum project
// by camilo on 2025-05-17 02:40 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/model_buffer.h"


namespace graphics3d
{


   struct CLASS_DECL_BRED tinyobjloader_Builder : 
      public ::gpu::model_data<::graphics3d::Vertex>
   {

      void loadModel_001(::gpu::context* pgpucontext, const ::file::path& path, bool bCounterClockwise);
      void loadModel_002(::gpu::context *pgpucontext, const ::file::path &path, bool bCounterClockwise);
      void loadModel(::gpu::context *pgpucontext, const ::file::path &path, bool bCounterClockwise);
      bool LoadObjAndConvert( // float bmin[3], float bmax[3], //std::vector<DrawObject> *drawObjects,
                              //                                            std::vector<tinyobj::material_t> &materials,
                              //                                          std::map<std::string, GLuint> &textures,
         ::gpu::context *pgpucontext, 
         const ::file::path &path, bool bCounterClockwise);

   };


   void LoadObjAndConvert_recompute_normals();


}  // namespace graphics3d


