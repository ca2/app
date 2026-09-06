#include <cassert>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>

static std::string read(const std::filesystem::path &path)
{
   std::ifstream stream(path);
   assert(stream);
   return {std::istreambuf_iterator<char>(stream), std::istreambuf_iterator<char>()};
}

int main()
{
   const auto app = std::filesystem::path(__FILE__).parent_path().parent_path().parent_path();
   const auto renderer = read(app / "bred/graphics3d/render_system/wavefront_obj_render_system.cpp");
   const auto mesh = read(app / "gpu_opengl/gltf/mesh.cpp");
   const auto constructor = renderer.find("wavefront_obj_render_system::wavefront_obj_render_system()");
   assert(constructor != std::string::npos);
   const auto constructorEnd = renderer.find('}', constructor);
   assert(renderer.substr(constructor, constructorEnd - constructor).find(
      "m_erendersystem = ::graphics3d::e_render_system_wavefront_obj;") != std::string::npos);
   const auto branch = mesh.find("if (erendersystem == ::graphics3d::e_render_system_wavefront_obj)");
   const auto skybox = mesh.find("else if (erendersystem == ::graphics3d::e_render_system_skybox_ibl)", branch);
   assert(branch != std::string::npos && skybox != std::string::npos);
   assert(mesh.substr(branch, skybox - branch).find("throw") == std::string::npos);
   assert(mesh.find("pcommandbuffer->draw(m_pmodelbuffer);", skybox) != std::string::npos);
}
