// Simple-polygon triangulation feeding the shared GPU brush fill pipeline.
#pragma once
#include <algorithm>
#include <cmath>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace gpu::brush_fill_geometry
{
struct point { double x, y; };
inline double cross(point a, point b, point c)
{ return (b.x-a.x)*(c.y-a.y) - (b.y-a.y)*(c.x-a.x); }
inline std::vector<point> triangulate(std::vector<point> points)
{
   for (auto p : points)
      if (!std::isfinite(p.x) || !std::isfinite(p.y))
         throw std::invalid_argument("Non-finite polygon coordinate");
   points.erase(std::unique(points.begin(), points.end(), [](point a, point b)
      { return a.x == b.x && a.y == b.y; }), points.end());
   if (points.size() > 1 && points.front().x == points.back().x && points.front().y == points.back().y)
      points.pop_back();
   if (points.size() < 3) return {};
   double area = 0.0;
   for (size_t i=1; i+1<points.size(); ++i) area += cross(points[0], points[i], points[i+1]);
   if (area == 0.0)
   {
      bool collinear = true;
      for (auto p : points) collinear = collinear && cross(points[0], points[1], p) == 0.0;
      if (collinear) return {};
   }
   auto on_segment = [](point a, point b, point p)
   {
      return cross(a,b,p) == 0.0 && p.x >= std::min(a.x,b.x) && p.x <= std::max(a.x,b.x)
         && p.y >= std::min(a.y,b.y) && p.y <= std::max(a.y,b.y);
   };
   for (size_t i=0; i<points.size(); ++i)
      for (size_t j=i+1; j<points.size(); ++j)
      {
         if (j == i+1 || (i == 0 && j+1 == points.size())) continue;
         auto a=points[i], b=points[(i+1)%points.size()], c=points[j], d=points[(j+1)%points.size()];
         auto ab_c=cross(a,b,c), ab_d=cross(a,b,d), cd_a=cross(c,d,a), cd_b=cross(c,d,b);
         if (((ab_c>0 && ab_d<0) || (ab_c<0 && ab_d>0))
            && ((cd_a>0 && cd_b<0) || (cd_a<0 && cd_b>0)))
            throw std::invalid_argument("Intersecting polygon edges");
         if (on_segment(a,b,c) || on_segment(a,b,d) || on_segment(c,d,a) || on_segment(c,d,b))
            throw std::invalid_argument("Touching polygon edges");
      }
   if (area == 0.0) throw std::invalid_argument("Zero-area polygon with intersecting edges");
   const double sign = area > 0.0 ? 1.0 : -1.0;
   std::vector<size_t> indices(points.size());
   std::iota(indices.begin(), indices.end(), 0);
   std::vector<point> triangles;
   while (indices.size() > 2)
   {
      bool removed = false;
      for (size_t i=0; i<indices.size(); ++i)
      {
         auto a=points[indices[(i+indices.size()-1)%indices.size()]];
         auto b=points[indices[i]];
         auto c=points[indices[(i+1)%indices.size()]];
         const double turn = sign*cross(a,b,c);
         if (turn < 0.0) continue;
         if (turn == 0.0)
         {
            indices.erase(indices.begin()+i); removed=true; break;
         }
         bool contains = false;
         for (auto index : indices)
         {
            auto p=points[index];
            if ((p.x==a.x && p.y==a.y) || (p.x==b.x && p.y==b.y) || (p.x==c.x && p.y==c.y)) continue;
            if (sign*cross(a,b,p)>=0.0 && sign*cross(b,c,p)>=0.0 && sign*cross(c,a,p)>=0.0)
            { contains=true; break; }
         }
         if (contains) continue;
         triangles.insert(triangles.end(), {a,b,c});
         indices.erase(indices.begin()+i); removed=true; break;
      }
      if (!removed) throw std::invalid_argument("Expected a simple polygon without intersecting edges");
   }
   return triangles;
}
// A single simple line contour, matching the tab paths. Figure endings are
// optional for filling; triangulate supplies the closing edge in either case.
// Reject additional contours rather than painting holes/overlaps incorrectly.
class linear_path
{
public:
   void begin_figure() { end_figure(); }
   void end_figure() { if (!m_points.empty()) m_ended = true; }

   void add_line(point a, point b)
   {
      if (m_points.empty())
         m_points.push_back(a);
      else if (m_ended || m_points.back().x != a.x || m_points.back().y != a.y)
         throw std::domain_error("GPU line path fills currently require one connected contour");
      m_points.push_back(b);
   }

   std::vector<point> triangles() const { return triangulate(m_points); }

private:
   std::vector<point> m_points;
   bool m_ended = false;
};
} // namespace gpu::brush_fill_geometry
