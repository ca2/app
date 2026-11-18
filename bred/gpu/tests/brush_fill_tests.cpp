#include "../brush_fill_geometry.h"
#include "../brush_fill_shader_source.h"
#include <cassert>
#include <filesystem>
#include <fstream>
#include <limits>

using namespace gpu::brush_fill_geometry;
static double area(const std::vector<point> & triangles)
{
   double result=0;
   for (size_t i=0;i<triangles.size();i+=3) result+=std::abs(cross(triangles[i],triangles[i+1],triangles[i+2]))/2;
   return result;
}
int main(int argc, char ** argv)
{
   // Production contexts return this source directly, without a version preamble.
   for (bool fragment : {false, true})
      for (bool pattern : {false, true})
         assert(gpu::brush_fill_source::source(false,fragment,pattern).rfind("#version 330 core\n",0)==0);
   std::vector<point> concave{{0,0},{4,0},{4,1},{1,1},{1,4},{0,4}};
   assert(std::abs(area(triangulate(concave))-7.0)<1e-12);
   std::reverse(concave.begin(),concave.end());
   assert(std::abs(area(triangulate(concave))-7.0)<1e-12);
   assert(area(triangulate({{0,0},{2,0},{2,0},{2,1},{0,1},{0,0}}))==2);
   assert(area(triangulate({{0,0},{1,0},{2,0},{2,2},{0,2}}))==4);
   assert(triangulate({{0,0},{1,0},{2,0},{3,0}}).empty());
   for (auto & p : concave) { p.x*=1e-6; p.y*=1e-6; }
   assert(std::abs(area(triangulate(concave))-7e-12)<1e-24);
   bool failed=false;
   try { triangulate({{0,0},{2,2},{0,2},{2,0}}); } catch(const std::invalid_argument &) { failed=true; }
   assert(failed);
   failed=false;
   try { triangulate({{0,0},{1,0},{0,std::numeric_limits<double>::infinity()}}); }
   catch(const std::invalid_argument &) { failed=true; }
   assert(failed);
   // Selected tabs omit close_figure; hover tabs close the same contour.
   // Both must cover the same shape, including its sloped top-right corner.
   linear_path tab;
   tab.begin_figure();
   tab.add_line({8,48},{8,8});
   tab.add_line({8,8},{44,8});
   tab.add_line({44,8},{56,20});
   tab.add_line({56,20},{55,48});
   auto tabTriangles = tab.triangles();
   assert(std::abs(area(tabTriangles)-1834.0)<1e-12);
   tab.end_figure();
   assert(area(tab.triangles())==area(tabTriangles));
   linear_path reverseTab;
   reverseTab.add_line({55,48},{56,20});
   reverseTab.add_line({56,20},{44,8});
   reverseTab.add_line({44,8},{8,8});
   reverseTab.add_line({8,8},{8,48});
   reverseTab.add_line({8,48},{55,48});
   assert(area(reverseTab.triangles())==area(tabTriangles));
   linear_path concavePath;
   concavePath.add_line({0,0},{4,0});
   concavePath.add_line({4,0},{4,1});
   concavePath.add_line({4,1},{1,1});
   concavePath.add_line({1,1},{1,4});
   concavePath.add_line({1,4},{0,4});
   assert(area(concavePath.triangles())==7);
   assert(linear_path().triangles().empty());
   linear_path degeneratePath;
   degeneratePath.add_line({0,0},{0,0});
   degeneratePath.add_line({0,0},{1,0});
   degeneratePath.add_line({1,0},{2,0});
   assert(degeneratePath.triangles().empty());
   failed=false;
   try { tab.begin_figure(); tab.add_line({12,12},{12,16}); }
   catch(const std::domain_error &) { failed=true; }
   assert(failed); // Do not paint a second contour as a solid hole or overdraw it.
   linear_path disconnected;
   disconnected.add_line({0,0},{1,0});
   failed=false;
   try { disconnected.add_line({2,0},{2,1}); }
   catch(const std::domain_error &) { failed=true; }
   assert(failed);
   if (argc>1)
   {
      std::filesystem::path output(argv[1]);
      std::filesystem::create_directories(output);
      std::ofstream tabFile(output/"tab_triangles.txt");
      for (auto p : tabTriangles) tabFile << p.x << ' ' << p.y << '\n';
      for (int backend=0;backend<3;++backend)
         for (int pattern=0;pattern<2;++pattern)
            for (int fragment=0;fragment<2;++fragment)
            {
               auto name=std::string(backend==0?"gl":backend==1?"vk":"hlsl")+(pattern?"_pattern":"_plain")+(fragment?".frag":".vert");
               std::ofstream file(output/name);
               file<<gpu::brush_fill_source::source(backend==2,fragment!=0,pattern!=0,backend==1);
            }
   }
}
