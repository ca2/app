// Created by camilo on 2025-07-25 ~05:00 <3ThomasBorregaardSørensen!!
#pragma once


namespace draw2d
{

   template < primitive_array POINT_ARRAY, primitive_point POINT, primitive_point POINT2 >
   void make_line_triangles_cap_butt_square(
      POINT_ARRAY& pointa,
      POINT p1, POINT p2, POINT2 thickness)
   {

      float dx = (float) (p2.x - p1.x);
      float dy = (float) (p2.y - p1.y);
      float len = sqrtf(dx * dx + dy * dy);
      if (len == 0.0f) len = 1.0f;
      dx /= len;
      dy /= len;

      // Extend the line endpoints by half thickness (square caps)
      float capx = (float) (thickness.x * 0.5f);
      float capy = (float) (thickness.y * 0.5f);
      p1.x -= dx * capx;
      p1.y -= dy * capy;
      p2.x += dx * capx;
      p2.y += dy * capy;

      // Perpendicular offset
      float px = (float)( - dy * thickness.x * 0.5f);
      float py = (float) ( dx * thickness.y * 0.5f);

      // Rectangle corners (with extended ends)
      double_point v0 = { p1.x + px, p1.y + py };
      double_point v1 = { p1.x - px, p1.y - py };
      double_point v2 = { p2.x + px, p2.y + py };
      double_point v3 = { p2.x - px, p2.y - py };

      // Two triangles (6 vertexes)
      pointa.add({ v0.x, v0.y });
      pointa.add({ v1.x, v1.y });
      pointa.add({ v2.x, v2.y });
      pointa.add({ v2.x, v2.y });
      pointa.add({ v1.x, v1.y });
      pointa.add({ v3.x, v3.y });

   }


   template < primitive_array POINT_ARRAY, primitive_array POINT_ARRAY1,
   primitive_point POINT >
   void make_draw_rectangle(
      POINT_ARRAY & pointa,
      const POINT_ARRAY1& pointa1,
      POINT thickness)
   {
      // Rectangle corners
      //::double_point p0 = { x,     y };          // bottom-left
      //::double_point p1 = { x + w,   y };          // bottom-right
      //::double_point p2 = { x + w,   y + h };          // top-right
      //::double_point p3 = { x,     y + h };          // top-left

      // Each side will have 6 vertexes (2 triangles), 12 floats
      // Total = 4 sides * 12 floats = 48 floats
      //float* v = out_vertexes;

      // Bottom edge
      make_line_triangles_cap_butt_square(
         pointa,
         ::double_point{ pointa1[0].x + thickness.x, pointa1[0].y},
         ::double_point{ pointa1[1].x - thickness.y, pointa1[1].y},
         thickness);

      // Right edge
      make_line_triangles_cap_butt_square(
         pointa,
         ::double_point{ pointa1[1].x, pointa1[1].y },
         ::double_point{ pointa1[2].x, pointa1[2].y },
         thickness);

      // Top edge
      make_line_triangles_cap_butt_square(
         pointa,
         ::double_point{ pointa1[2].x - thickness.x, pointa1[2].y},
         ::double_point{ pointa1[3].x + thickness.y, pointa1[3].y},
         thickness);

      // Left edge
      make_line_triangles_cap_butt_square(
         pointa,
         ::double_point{ pointa1[3].x, pointa1[3].y },
         ::double_point{ pointa1[0].x, pointa1[0].y },
         thickness);

   }


} // namespace draw2d


