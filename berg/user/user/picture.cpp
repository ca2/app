#include "framework.h"
#include "acme/handler/item.h"
#include "aura/platform/context.h"
#include <math.h>
#include "acme/prototype/geometry2d/matrix.h"
#include "aura/graphics/image/context.h"
#include "aura/graphics/image/image.h"
#include "aura/graphics/image/drawing.h"
#include "picture.h"
#include "acme/prototype/geometry2d/_binary_stream.h"
#include "acme/prototype/collection/_array_binary_stream.h"
//#include "acme/_finish.h"


property & operator << (property & property, const ::double_rectangle & rectangle)
{

   property["left"] = rectangle.left();
   property["top"] = rectangle.top();
   property["right"] = rectangle.right();
   property["bottom"] = rectangle.bottom();

   return property;

}

property & operator >> (property & property, ::double_rectangle & rectangle)
{

   rectangle.left() = property["left"].as_double();
   rectangle.top() = property["top"].as_double();
   rectangle.right() = property["right"].as_double();
   rectangle.bottom() = property["bottom"].as_double();

   return property;

}



namespace user
{


   picture::picture()
   {

      set_flag(e_flag_default_io_exchange);

      reset_cursor_rect();

   }


   //picture::picture()
   //{

   //   m_eobject += object_default_io_exchange;

   //   reset_cursor_rect();

   //}


   picture::~picture()
   {

      enable_picture(false);

   }


   bool picture::is_picture_enabled() const
   {

      return m_ppictureimpl;

   }


   picture::picture_impl::picture_impl()
   {

      set_flag(e_flag_default_io_exchange);

      m_dZoom = 1.0;
      m_pointDrag2.x() = 0.0;
      m_pointDrag2.y() = 0.0;


      m_bOutline = false;
      m_iOutlineWidth = 7;
      m_hlsOutline.m_dH = 0.0;
      m_hlsOutline.m_dL = 0.0;
      m_hlsOutline.m_dS = 0.0;

      m_bGlowDropShadow = false;
      m_iGlowDropShadowOffset = 12;
      m_iGlowDropShadowBlur = 4;
      m_hlsGlowDropShadow.m_dH = 0.0;
      m_hlsGlowDropShadow.m_dL = 0.0;
      m_hlsGlowDropShadow.m_dS = 0.0;

      m_iBlur = 0;
      m_bGrayscale = false;
      m_bInvert = false;
      m_iOpacity = 100;
      m_iSaturation = 100;

   }


   void picture::picture_impl::read_from_stream(::binary_stream & binarystream)
   {

      binarystream >> m_rectangle;
      binarystream >> m_dRotate;

   }
   
   
   void picture::picture_impl::write_to_stream(::binary_stream & binarystream)
   {

      binarystream << m_rectangle;
      binarystream << m_dRotate;

   }



   bool picture::enable_picture(bool bEnable)
   {

      if (bEnable)
      {

         ødefer_construct_new(m_ppictureimpl);

      }
      else
      {

         m_ppictureimpl.release();

      }

      return is_equivalent(bEnable, m_ppictureimpl);

   }


   ::item_pointer picture::parent_client_on_hit_test(const ::int_point &point, ::user::e_zorder ezorder)
   {

      ASSERT(is_picture_enabled());

      //_rtransform_point(point);

      if (m_ppictureimpl->m_rectangle.contains(point))
      {

         return stock_item(e_element_client);

      }

      auto pitemNone = stock_item(e_element_none);

      return pitemNone;

   }


//   double_point picture::_transform(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      _transform_point(point);
//
//      return point;
//
//   }


//   double_point picture::_transform_drawing(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      _transform_point_drawing(point);
//
//      return point;
//
//   }


   void picture::_transform_sequence(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectangle.center());

      m.transform(sequence);

   }


   void picture::_transform_sequence_drawing(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangleDrawing.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectangleDrawing.center());

      m.transform(sequence);

   }


//   double_point picture::_rtransform(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      _rtransform_point(point);
//
//      return point;
//
//   }


//   double_point picture::_rtransform_drawing(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      _rtransform_point_drawing(point);
//
//      return point;
//
//   }


   void picture::_rtransform_sequence(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectangle.center());

      m.transform(sequence);

   }


   void picture::_rtransform_sequence_drawing(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangleDrawing.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      m.translate(m_ppictureimpl->m_rectangleDrawing.center());

      m.transform(sequence);

   }


//   double_point picture::drag_transform(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      drag_transform_point(point);
//
//      return point;
//
//   }


//   double_point picture::drag_transform_drawing(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      drag_transform_point_drawing(point);
//
//      return point;
//
//   }


   void picture::drag_transform_sequence(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.scale(m_ppictureimpl->m_dZoom, m_ppictureimpl->m_dZoom);

      m.translate(m_ppictureimpl->m_rectangle.center());

      m.transform(sequence);

   }


   void picture::drag_transform_sequence_drawing(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangleDrawing.center());

      m.rotate(m_ppictureimpl->m_dRotate);

      m.scale(m_ppictureimpl->m_dZoom, m_ppictureimpl->m_dZoom);

      m.translate(m_ppictureimpl->m_rectangleDrawing.center());

      m.transform(sequence);

   }


//   double_point picture::drag_rtransform(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      drag_rtransform_point(point);
//
//      return point;
//
//   }
//
//
//   double_point picture::drag_rtransform_drawing(const double_point & pointParam) const
//   {
//
//      double_point point(pointParam);
//
//      drag_rtransform_point_drawing(point);
//
//      return point;
//
//   }


   void picture::drag_rtransform_sequence(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangle.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      double dZoom = m_ppictureimpl->m_dZoom;

      m.scale(1.0 / dZoom, 1.0 / dZoom);

      m.transform(sequence);

   }



   void picture::set_drag_point(const ::double_point & point)
   {

      auto size = get_size();

      m_ppictureimpl->m_pointDrag2.x() = point.x() * size.cx()/m_ppictureimpl->m_rectangle.width();

      m_ppictureimpl->m_pointDrag2.y() = point.y() * size.cy() / m_ppictureimpl->m_rectangle.height();

   }

   ::double_point picture::get_drag_point()
   {

      ::double_point point;

      auto size = get_size();

      point.x() = m_ppictureimpl->m_pointDrag2.x() *m_ppictureimpl->m_rectangle.width() / size.cx();

      point.y() = m_ppictureimpl->m_pointDrag2.y() *m_ppictureimpl->m_rectangle.height() / size.cy();

      return point;

   }


   void picture::drag_rtransform_sequence_drawing(sequence2_double & sequence) const
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      ::geometry2d::matrix m;

      m.translate(-m_ppictureimpl->m_rectangleDrawing.center());

      m.rotate(-m_ppictureimpl->m_dRotate);

      m.scale(1.0 / m_ppictureimpl->m_dZoom, 1.0 / m_ppictureimpl->m_dZoom);

      //m.translate(m_ppictureimpl->m_rectangleDrawing.center());

      m.transform(sequence);

   }


   void picture::update_placement()
   {

   }


   void picture::update_drawing_rect(::double_size sizePage, ::double_size sizeClient)
   {

      ASSERT(is_picture_enabled());

      if (sizeClient.area() <= 0)
      {

         m_ppictureimpl->m_rectangleDrawing = m_ppictureimpl->m_rectangle;

      }
      else
      {

         m_ppictureimpl->m_rectangleDrawing.left() = m_ppictureimpl->m_rectangle.left() * sizePage.cx() / sizeClient.cx();
         m_ppictureimpl->m_rectangleDrawing.right() = m_ppictureimpl->m_rectangle.right() * sizePage.cx() / sizeClient.cx();
         m_ppictureimpl->m_rectangleDrawing.top() = m_ppictureimpl->m_rectangle.top() * sizePage.cy() / sizeClient.cy();
         m_ppictureimpl->m_rectangleDrawing.bottom() = m_ppictureimpl->m_rectangle.bottom() * sizePage.cy() / sizeClient.cy();

      }

   }


   void picture::update_screen_rect(::double_size sizePage, ::double_size sizeClient)
   {

      ASSERT(is_picture_enabled());

      if (sizePage.area() <= 0)
      {

         m_ppictureimpl->m_rectangle = m_ppictureimpl->m_rectangleDrawing;

      }
      else
      {

         m_ppictureimpl->m_rectangle.left() = m_ppictureimpl->m_rectangleDrawing.left() * sizeClient.cx() / sizePage.cx();
         m_ppictureimpl->m_rectangle.right() = m_ppictureimpl->m_rectangleDrawing.right() * sizeClient.cx() / sizePage.cx();
         m_ppictureimpl->m_rectangle.top() = m_ppictureimpl->m_rectangleDrawing.top() * sizeClient.cy() / sizePage.cy();
         m_ppictureimpl->m_rectangle.bottom() = m_ppictureimpl->m_rectangleDrawing.bottom() * sizeClient.cy() / sizePage.cy();

      }

   }

   void picture::update_region()
   {

      if (m_ppictureimpl->m_rectangleRegion == m_ppictureimpl->m_rectangle
            && m_ppictureimpl->m_rectangleRegionDrawing == m_ppictureimpl->m_rectangleDrawing)
      {

         return;

      }



      ASSERT(is_picture_enabled());

      m_ppictureimpl->m_polygonDrawing.set_size(4);

      m_ppictureimpl->m_polygonDrawing[0] = _transform_drawing(m_ppictureimpl->m_rectangleDrawing.top_left());
      m_ppictureimpl->m_polygonDrawing[1] = _transform_drawing(m_ppictureimpl->m_rectangleDrawing.top_right());
      m_ppictureimpl->m_polygonDrawing[2] = _transform_drawing(m_ppictureimpl->m_rectangleDrawing.bottom_right());
      m_ppictureimpl->m_polygonDrawing[3] = _transform_drawing(m_ppictureimpl->m_rectangleDrawing.bottom_left());

      m_ppictureimpl->m_polygonDrawing.m_bDirty = true;

      m_ppictureimpl->m_polygon.set_size(4);

      m_ppictureimpl->m_polygon[0] = _transform(m_ppictureimpl->m_rectangle.top_left());
      m_ppictureimpl->m_polygon[1] = _transform(m_ppictureimpl->m_rectangle.top_right());
      m_ppictureimpl->m_polygon[2] = _transform(m_ppictureimpl->m_rectangle.bottom_right());
      m_ppictureimpl->m_polygon[3] = _transform(m_ppictureimpl->m_rectangle.bottom_left());

      m_ppictureimpl->m_polygon.m_bDirty = true;

      m_ppictureimpl->m_rectangleRegion = m_ppictureimpl->m_rectangle;
      m_ppictureimpl->m_rectangleRegionDrawing = m_ppictureimpl->m_rectangleDrawing;

   }


   ::draw2d::region_pointer picture::get_region() const
   {

      if (m_ppictureimpl->m_region.is_null())
      {

         ((picture*)this)->update_region();

      }

      return m_ppictureimpl->m_region;

   }


   bool picture::intersects(const ::double_rectangle & rectangleParam) const
   {

      double_rectangle rectangle(rectangleParam);

      double_polygon int_polygon;

      int_polygon.set_size(4);

      int_polygon[0] = rectangle.top_left();
      int_polygon[1] = rectangle.top_right();
      int_polygon[2] = rectangle.bottom_right();
      int_polygon[3] = rectangle.bottom_left();

      int_polygon.m_bDirty = false;

      int_polygon.m_bDirtyBoundingRect = false;

      int_polygon.m_rectangleBounding = rectangle;

      if (m_ppictureimpl->m_polygon.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return int_polygon.overlaps(m_ppictureimpl->m_polygon);

   }


   double_rectangle picture::drawing_bounds() const
   {

      double_rectangle rectangle(0.0, 0.0, 0.0, 0.0);

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      if (m_ppictureimpl->m_polygonDrawing.get_size() > 0)
      {

         rectangle.left() = rectangle.right() = m_ppictureimpl->m_polygonDrawing[0].x();

         rectangle.top() = rectangle.bottom() = m_ppictureimpl->m_polygonDrawing[0].y();

         for (::collection::index i = 1; i < m_ppictureimpl->m_polygonDrawing.get_size(); i++)
         {

            if (m_ppictureimpl->m_polygonDrawing[i].x() < rectangle.left())
            {

               rectangle.left() = m_ppictureimpl->m_polygonDrawing[i].x();

            }
            else if (m_ppictureimpl->m_polygonDrawing[i].x() > rectangle.right())
            {

               rectangle.right() = m_ppictureimpl->m_polygonDrawing[i].x();

            }

            if (m_ppictureimpl->m_polygonDrawing[i].y() < rectangle.top())
            {

               rectangle.top() = m_ppictureimpl->m_polygonDrawing[i].y();

            }
            else if (m_ppictureimpl->m_polygonDrawing[i].y() > rectangle.bottom())
            {

               rectangle.bottom() = m_ppictureimpl->m_polygonDrawing[i].y();

            }

         }

      }

      return rectangle;

   }


   double_point_array_base & picture::drawing_polygon() const
   {

      double_rectangle rectangle(0.0, 0.0, 0.0, 0.0);

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return m_ppictureimpl->m_polygonDrawing;

   }


   bool picture::intersects_drawing(const double_polygon & int_polygon) const
   {

      ASSERT(is_picture_enabled());

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return int_polygon.overlaps( m_ppictureimpl->m_polygonDrawing);

   }


   bool picture::intersects_drawing(const ::double_rectangle & rectangleParam) const
   {

      ASSERT(is_picture_enabled());

      double_polygon polygon;

      polygon = rectangleParam;

      if (m_ppictureimpl->m_polygonDrawing.get_size() <= 0)
      {

         ((picture*)this)->update_region();

      }

      return polygon.overlaps(m_ppictureimpl->m_polygonDrawing);

   }


   bool picture::is_valid()
   {

      return true;

   }


   ::double_size picture::get_size()
   {

      return ::double_size(128, 128);

   }


   ::double_size picture::get_request_size()
   {

      return get_size();

   }


   bool picture::set_text_editable(bool bEditable)
   {

      return false;

   }


   bool picture::is_text_editable()
   {

      return false;

   }


   bool picture::is_text_editor()
   {

      return false;

   }


   void picture::reset_cursor_rect()
   {

      if (m_ppictureimpl == nullptr)
      {

         return;

      }

      m_ppictureimpl->m_rectangleCursor.set(0, 0, -1, -1);

   }


   bool picture::is_dragging()
   {

      if (!is_valid())
      {

         return false;

      }

      if (!m_ppictureimpl->m_bDrag)
      {

         return false;

      }

      return true;

   }


   //int picture::on_hit_test_cursor(double_point point)
   //{

   //   if (!is_valid())
   //   {

   //      return -1;

   //   }

   //   _rtransform_point(point);

   //   if(m_ppictureimpl->m_rectangle.contains(point))
   //   {

   //      return 0;

   //   }

   //   return -1;

   //}


   ::image::image_pointer picture::defer_draw_drop_shadow_phase1(int_rectangle & rectangleDropShadow, ::image::fastblur & blurDropShadow, ::image::image_pointer & pimageDropShadow, ::image::image_pointer pimage)
   {

      if (m_ppictureimpl->m_bGlowDropShadow)
      {

         double dBlur = (double)m_ppictureimpl->m_iGlowDropShadowBlur * (double)pimage->width() / (double)rectangleDropShadow.width();

         int iBlur = (int) ceil(dBlur);

         ::int_rectangle rectangleDib(pimage->get_size());

         int iShift = iBlur * 2;

         rectangleDib.inflate(iShift, iShift);

         pimageDropShadow = image()->create_image(rectangleDib.size());

         if (pimageDropShadow)
         {

            rectangleDropShadow.inflate(m_ppictureimpl->m_iGlowDropShadowBlur, m_ppictureimpl->m_iGlowDropShadowBlur);

            pimageDropShadow->clear(color::transparent);

            ::image::image_source imagesource(pimage);

            ::image::image_drawing_options imagedrawingoptions(pimage->rectangle({ iShift, iShift }));

            ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

            pimageDropShadow->g()->draw(imagedrawing);

            pimageDropShadow->multiply_rgb_by_source_alpha(m_ppictureimpl->m_hlsGlowDropShadow);
            
            blurDropShadow.initialize(pimageDropShadow->size(), iBlur);

            blurDropShadow.blur(pimageDropShadow);

         }

      }

      return pimage;

   }


   void picture::defer_draw_drop_shadow_phase2(::draw2d::graphics_pointer & pgraphics, const int_rectangle & rectangle, ::image::fastblur & pblurDropShadow, ::image::image_pointer & pimageDropShadow)
   {

      if (m_ppictureimpl->m_bGlowDropShadow)
      {

         ::int_rectangle rectangleDropShadow(rectangle);

         rectangleDropShadow.offset(m_ppictureimpl->m_iGlowDropShadowOffset, m_ppictureimpl->m_iGlowDropShadowOffset);

         ::image::image_source imagesource(pimageDropShadow);

         ::image::image_drawing_options imagedrawingoptions(rectangleDropShadow);

         ::image::image_drawing imagedrawing(imagedrawingoptions, imagesource);

         pgraphics->draw(imagedrawing);

      }

   }


   void picture::draw_impl(::draw2d::graphics_pointer & pgraphics)
   {


   }


   bool picture::is_picture_hover()
   {

      return false;

   }


   ::item_pointer picture::parent_client_hit_test(const ::int_point & point, ::user::e_zorder ezorder)
   {

      //item.m_pointScreen = point;

      //item.m_pointClient = _rtransform(item.m_pointScreen);

      //item.m_pointHitTest = item.m_pointClient;

      return parent_client_on_hit_test(point, ezorder);

   }



   ::double_rectangle picture::get_rect_for_picture2()
   {

      auto size = m_ppictureimpl->m_rectangleDrawing.size() / 2.0;

      auto pointDrag = get_drag_point();

      size = ::double_size(pointDrag.x() * m_ppictureimpl->m_rectangleDrawing.width(),
         pointDrag.y() * m_ppictureimpl->m_rectangleDrawing.height()) - size;

      double_rectangle rectangle(::double_point(size), ::double_size(m_ppictureimpl->m_rectangleDrawing.size()));

      return rectangle;

   }


   ::double_point picture::get_point_transform()
   {

      auto pointD = m_ppictureimpl->m_rectangleDrawing.center();

      return pointD;

      //      auto pointD = ::double_point(m_ppictureimpl->m_rectangleDrawing.size() / 2.0);

   }


   void picture::draw(::draw2d::graphics_pointer & pgraphics)
   {

      if (!_000OnBeforeDraw(pgraphics))
      {

         return;

      }

      ::draw2d::save_context savecontext(pgraphics);

      ::geometry2d::matrix mRot;

      ::double_rectangle rectangleClip(m_ppictureimpl->m_rectangleDrawing);

      ::double_polygon int_polygon;

      int_polygon.set_size(4);

      int_polygon[0] = _transform_drawing(rectangleClip.top_left());
      int_polygon[1] = _transform_drawing(rectangleClip.top_right());
      int_polygon[2] = _transform_drawing(rectangleClip.bottom_right());
      int_polygon[3] = _transform_drawing(rectangleClip.bottom_left());

      //pgraphics->intersect_clip(int_polygon);

      mRot.append(::geometry2d::matrix::rotation(m_ppictureimpl->m_dRotate));

      ::geometry2d::matrix mG;

      mG.scaling(pgraphics->get_scaling());

      pgraphics->prepend(mRot);

      pgraphics->prepend(::geometry2d::matrix::scaling(m_ppictureimpl->m_dZoom, m_ppictureimpl->m_dZoom));

      pgraphics->prepend(::geometry2d::matrix::translation(
         -m_ppictureimpl->m_rectangle.width() / 2,
         -m_ppictureimpl->m_rectangle.height() / 2));

      auto pointDrag = get_drag_point();

      pgraphics->prepend(::geometry2d::matrix::translation(
         pointDrag.x(),
         pointDrag.y()));

      ::geometry2d::matrix mTrans;

      auto pointD = get_point_transform();

      mG.transform(pointD);

      mTrans.append(::geometry2d::matrix::translation(pointD));

      pgraphics->append(mTrans);

      draw_impl(pgraphics);


   }




   void picture::move_to(double_point point, ::double_size sizePage, ::double_size sizeClient, const ::double_rectangle & rectangleMargin)
   {

      m_ppictureimpl->m_rectangle.move_to(point);

      update_region();

      m_ppictureimpl->m_rectangle._001Constrain(rectangleMargin, m_ppictureimpl->m_rectangleBounding);

      update_drawing_rect(sizePage, sizeClient);

      update_region();

      update_placement();

   }





   picture::picture_impl::~picture_impl()
   {


   }


   void picture::read_from_stream(::binary_stream & binarystream)
   {

      if (!is_picture_enabled())
      {

         enable_picture();

      }

      m_ppictureimpl->read_from_stream(binarystream);

   }


   void picture::write_to_stream(::binary_stream & binarystream)
   {

      m_ppictureimpl->write_to_stream(binarystream);

   }


} // namespace user


