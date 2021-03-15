#include "framework.h"


namespace draw2d
{


   glyph::glyph()
   {

   }


   glyph::~glyph()
   {

   }


   glyph & glyph::operator = (const glyph & glyph)
   {

      m_ui = glyph.m_ui;

//#ifdef WINDOWS_DESKTOP
//
//      m_gm = glyph.m_gm;
//
//#endif

      m_pointsets.copy(glyph.m_pointsets);

      return *this;

   }


   bool glyph::operator <= (const glyph & glyph) const
   {

      return m_ui < glyph.m_ui;

   }


//#ifdef WINDOWS_DESKTOP
//
//   /****************************************************************************
//   *  FUNCTION   : IntFromFixed
//   *  RETURNS    : i32 value approximating the FIXED value.
//   ****************************************************************************/
//   i32 IntFromFixed(FIXED f)
//   {
//      if (f.fract >= 0x8000)
//         return(f.value + 1);
//      else
//         return(f.value);
//   }
//
//
//
//   /****************************************************************************
//   *  FUNCTION   : fxDiv2
//   *  RETURNS    : (val1 + val2)/2 for FIXED values
//   ****************************************************************************/
//   FIXED fxDiv2(FIXED fxVal1, FIXED fxVal2)
//   {
//      long l;
//
//      l = (*((long far *)&(fxVal1)) + *((long far *)&(fxVal2)))/2;
//      return(*(FIXED *)&l);
//   }
//
//   /****************************************************************************
//   *  FUNCTION   : MakeBezierFromLine
//   *
//   *  PURPOSE    : Converts a line define by two points to a four point_i32 Bezier
//   *               spline representation of the line in pPts.
//   *
//   *
//   *  RETURNS    : number of Bezier points placed into the pPts const point_i32 & array.
//   ****************************************************************************/
//   ::u32 MakeBezierFromLine( POINT_I32 *pPts, const point_i32 & startpt, const point_i32 & endpt )
//   {
//      ::u32 cTotal = 0;
//
//      // starting point_i32 of Bezier
//      pPts[cTotal] = startpt;
//      cTotal++;
//
//      // 1rst control, point == endpoint makes Bezier a line
//      pPts[cTotal].x = endpt.x;
//      pPts[cTotal].y = endpt.y;
//      cTotal++;
//
//      // 2nd control, point == startpoint makes Bezier a line
//      pPts[cTotal].x = startpt.x;
//      pPts[cTotal].y = startpt.y;
//      cTotal++;
//
//      // ending point_i32 of Bezier
//      pPts[cTotal] = endpt;
//      cTotal++;
//
//      return cTotal;
//   }
//
//   /****************************************************************************
//   *  FUNCTION   : MakeBezierFromQBSpline
//   *
//   *  PURPOSE    : Converts a quadratic spline in pSline to a four point_i32 Bezier
//   *               spline in pPts.
//   *
//   *
//   *  RETURNS    : number of Bezier points placed into the pPts const point_i32 & array.
//   ****************************************************************************/
//   ::u32 MakeBezierFromQBSpline( POINT_I32 *pPts, POINTFX *pSpline )
//   {
//      ::point_i32 point0;         // Quadratic on curve start point_i32
//      ::point_i32 point1;         // Quadratic control point_i32
//      ::point_i32 point2;         // Quadratic on curve end point_i32
//      ::u32 cTotal = 0;
//
//      // Convert the Quadratic points to integer
//      point0.x = IntFromFixed( pSpline[0].x );
//      point0.y = IntFromFixed( pSpline[0].y );
//      point1.x = IntFromFixed( pSpline[1].x );
//      point1.y = IntFromFixed( pSpline[1].y );
//      point2.x = IntFromFixed( pSpline[2].x );
//      point2.y = IntFromFixed( pSpline[2].y );
//
//      // conversion of a quadratic to a cubic
//
//      // Cubic point0 is the on curve start point_i32
//      pPts[cTotal] = point0;
//      cTotal++;
//
//      // Cubic point1 in terms of Quadratic point0 and point1
//      pPts[cTotal].x = point0.x + 2*(point1.x - point0.x)/3;
//      pPts[cTotal].y = point0.y + 2*(point1.y - point0.y)/3;
//      cTotal++;
//
//      // Cubic point2 in terms of Qudartic point1 and point2
//      pPts[cTotal].x = point1.x + 1*(point2.x - point1.x)/3;
//      pPts[cTotal].y = point1.y + 1*(point2.y - point1.y)/3;
//      cTotal++;
//
//      // Cubic P3 is the on curve end point_i32
//      pPts[cTotal] = point2;
//      cTotal++;
//
//      return cTotal;
//   }
//
//
//   /****************************************************************************
//   *  FUNCTION   : AppendPolyLineToBezier
//   *
//   *  PURPOSE    : Converts line segments into their Bezier point_i32
//   *               representation and appends them to a list of Bezier points.
//   *
//   *               WARNING - The array must have at least one valid
//   *               start point_i32 prior to the address of the matter passed.
//   *
//   *  RETURNS    : number of Bezier points added to the const point_i32 & array.
//   ****************************************************************************/
//   //::u32 AppendPolyLineToBezier( POINT_I32 * point, POINTFX start, LPTTPOLYCURVE pCurve )
//
//   ::u32 AppendPolyLineToBezier(
//   point_i32_array      &pointsset,
//   POINTFX         start,
//   LPTTPOLYCURVE   pCurve,
//
//   ::u32         cTotal )
//   {
//      i32     i;
//      //    ::u32    cTotal = 0;
//      ::point_i32   endpt;
//      ::point_i32   startpt;
//      ::point_i32   bezier[4];
//
//      endpt.x = IntFromFixed(start.x);
//      endpt.y = IntFromFixed(start.y);
//
//      //points.set_size(points.get_size() + pCurve->cpfx * 3);
//
//      for (i = 0; i < pCurve->cpfx; i++)
//
//      {
//         // define the line segment
//         startpt = endpt;
//         endpt.x = IntFromFixed(pCurve->apfx[i].x);
//
//         endpt.y = IntFromFixed(pCurve->apfx[i].y);
//
//
//         // convert a line to a bezier representation
//         MakeBezierFromLine( bezier, startpt, endpt );
//
//         // append the Bezier to the existing ones
//         // Point 0 is Point 3 of previous.
//         //      point_i32[cTotal++] = bezier[1];   // Point 1
//         //        point_i32[cTotal++] = bezier[2];   // Point 2
//         //      point_i32[cTotal++] = bezier[3];   // Point 3
//         pointsset.add(bezier[1]);
//         pointsset.add(bezier[2]);
//         pointsset.add(bezier[3]);
//
//
//      }
//
//      return cTotal;
//   }
//
//
//   /****************************************************************************
//   *  FUNCTION   : AppendQuadBSplineToBezier
//   *
//   *  PURPOSE    : Converts Quadratic spline segments into their Bezier point_i32
//   *               representation and appends them to a list of Bezier points.
//   *
//   *               WARNING - The array must have at least one valid
//   *               start point_i32 prior to the address of the matter passed.
//   *
//   *  RETURNS    : number of Bezier points added to the const point_i32 & array.
//   ****************************************************************************/
//   //::u32 AppendQuadBSplineToBezier( POINT_I32 * point, POINTFX start, LPTTPOLYCURVE pCurve )
//
//   ::u32 AppendQuadBSplineToBezier(
//   point_i32_array & pointset,
//   POINTFX start,
//   LPTTPOLYCURVE pCurve,
//
//   ::u32 cTotal )
//
//   {
//      ::u16                i;
//      //    ::u32                cTotal = 0;
//      POINTFX             spline[3];  // a Quadratic is defined by 3 points
//      ::point_i32               bezier[4];  // a Cubic by 4
//
//      // The initial A point_i32 is on the curve.
//      spline[0] = start;
//
//      for (i = 0; i < pCurve->cpfx;)
//
//      {
//         // The B point.
//         spline[1] = pCurve->apfx[i++];
//
//
//         // Calculate the C point.
//         if (i == (pCurve->cpfx - 1))
//
//         {
//            // The last C point_i32 is described explicitly
//            // i.e. it is on the curve.
//            spline[2] = pCurve->apfx[i++];
//
//         }
//         else
//         {
//            // C is midpoint between B and next B point_i32
//            // because that is the on curve point_i32 of
//            // a Quadratic B-Spline.
//            spline[2].x = fxDiv2(
//                          pCurve->apfx[i-1].x,
//
//                          pCurve->apfx[i].x
//
//                          );
//            spline[2].y = fxDiv2(
//                          pCurve->apfx[i-1].y,
//
//                          pCurve->apfx[i].y
//
//                          );
//         }
//
//         // convert the Q Spline to a Bezier
//         MakeBezierFromQBSpline( bezier, spline );
//
//         // append the Bezier to the existing ones
//         // Point 0 is Point 3 of previous.
//         //        point_i32[cTotal++] = bezier[1];   // Point 1
//         //      point_i32[cTotal++] = bezier[2];   // Point 2
//         //    point_i32[cTotal++] = bezier[3];   // Point 3
//         pointset.add(bezier[1]);
//         pointset.add(bezier[2]);
//         pointset.add(bezier[3]);
//
//         // New A point_i32 for next slice of spline is the
//         // on curve C point_i32 of this B-Spline
//         spline[0] = spline[2];
//      }
//
//      return cTotal;
//   }
//
//   /****************************************************************************
//   *  FUNCTION   : CloseContour
//   *
//   *  PURPOSE    : Adds a bezier line to close the circuit defined in point.
//   *
//   *
//   *  RETURNS    : number of points aded to the point_i32 const point_i32 & array.
//   ****************************************************************************/
//   //::u32 CloseContour( POINT_I32 * point, ::u32 cTotal )
//   ::u32 CloseContour(
//   point_i32_array & pointset,
//   ::u32 cTotal )
//   {
//      ::point_i32               endpt;
//      ::point_i32                 startpt;    // definition of a line
//      ::point_i32               bezier[4];
//
//      // connect the first and last points by a line segment
//      //startpt = point_i32[cTotal-1];
//      //endpt = point_i32[0];
//      startpt = pointset.last();
//      endpt = pointset.first();
//
//      //points.set_size(points.get_size() + 3);
//      // convert a line to a bezier representation
//      MakeBezierFromLine( bezier, startpt, endpt );
//
//      // append the Bezier to the existing ones
//      // Point 0 is Point 3 of previous.
//      //    point_i32[cTotal++] = bezier[1];   // Point 1
//      //  point_i32[cTotal++] = bezier[2];   // Point 2
//      //point_i32[cTotal++] = bezier[3];   // Point 3
//      pointset.add(bezier[1]);   // Point 1
//      pointset.add(bezier[2]);   // Point 2
//      pointset.add(bezier[3]);   // Point 3
//
//      //return 3;
//      return cTotal;
//   }
//
//
//   /****************************************************************************
//   *  FUNCTION   : DrawT2Outline
//   *
//   *  PURPOSE    : Decode the GGO_NATIVE outline, create a sequence of Beziers
//   *               for each contour, draw with poly_bezier.  color and relative
//   *               positioning provided by caller. The coordinates of hDC are
//   *               assumed to have MM_TEXT orientation.
//   *
//   *               The outline data is not scaled. To draw a glyph unhinted
//   *               the caller should create the font at its EMSquare size_i32
//   *               and retrieve the outline data. Then setup a mapping mode
//   *               prior to calling this function.
//   *
//   *  RETURNS    : none.
//   ****************************************************************************/
//   void glyph::Initialize(LPTTPOLYGONHEADER pHeader, u32 size, i32 iFontHiHeight)
//
//   {
//
//      ::u16                i;
//      ::u32                cTotal = 0; // Total points in a contour.
//      LPTTPOLYGONHEADER   pStart;    // the start of the buffer
//
//      LPTTPOLYCURVE       pCurve;    // the current curve of a contour
//
//      //  POINT_I32 *             point_i32;         // the bezier buffer
//      POINTFX             pointStart;    // The starting point_i32 of a curve
//      u32               dwMaxPts = size_i32/sizeof(POINTFX); // maximum possible pts.
//      u32               dwBuffSize;
//
//      dwBuffSize = dwMaxPts *     // Maximum possible # of contour points.
//                   sizeof(const point_i32 &) * // sizeof buffer matter
//                   3;             // Worst case multiplier of one additional point_i32
//      // of line expanding to three points of a bezier
//
//      pStart = pHeader;
//
//
//
//      // Loop until we have processed the entire buffer of contours.
//      // The buffer may contain one or more contours that begin with
//      // a TTPOLYGONHEADER. We have them all when we the end of the buffer.
//      //while ((u32)pHeader < (u32)(((char *)pStart) + size) && point != nullptr)
//
//      while ((uptr)pHeader < (uptr)(((char *)pStart) + size))
//
//      {
//         if (pHeader->dwType == TT_POLYGON_TYPE)
//
//            // draw each coutour, currently this is the only valid
//            // type of contour.
//         {
//            point_i32_array pointset;
//            //pPoints = new CPoints();
//            //         pPoints->m_lpPoints = point;
//
//            //point = (POINT_I32 *)malloc( dwBuffSize );
//            //         point = (POINT_I32 *) new byte(dwBuffSize);
//            // Convert the starting point. It is an on curve point.
//            // All other points are continuous from the "last"
//            // point_i32 of the contour. Thus the start point_i32 the next
//            // bezier is always point_i32[cTotal-1] - the last point_i32 of the
//            // previous bezier. See poly_bezier.
//            pointset.add(
//            IntFromFixed(pHeader->pfxStart.x),
//
//            IntFromFixed(pHeader->pfxStart.y));
//
//            cTotal = 1;
//            //cTotal = 1;
//            //point_i32[0].x = IntFromFixed(pHeader->pfxStart.x);
//
//            //point_i32[0].y = IntFromFixed(pHeader->pfxStart.y);
//
//
//            // get to first curve of contour -
//            // it starts at the next byte beyond header
//            pCurve = (LPTTPOLYCURVE) (pHeader + 1);
//
//
//            // Walk this contour and process each curve( or line ) segment
//            // and add it to the Beziers
//            while ((uptr)pCurve < (uptr)(((char *)pHeader) + pHeader->cb))
//
//            {
//               //**********************************************
//               // Format assumption:
//               //   The bytes immediately preceding a POLYCURVE
//               //   structure contain a valid POINTFX.
//               //
//               //   If this is first curve, this points to the
//               //      pfxStart of the POLYGONHEADER.
//               //   Otherwise, this points to the last point_i32 of
//               //      the previous POLYCURVE.
//               //
//               //   In either case, this is representative of the
//               //      previous curve's last point.
//               //**********************************************
//
//               pointStart = *(POINTFX *)((char *)pCurve - sizeof(POINTFX));
//
//               if (pCurve->wType == TT_PRIM_LINE)
//
//               {
//                  // convert the line segments to Bezier segments
//                  //cTotal += AppendPolyLineToBezier( &point[cTotal], pointStart, pCurve );
//
//                  cTotal = AppendPolyLineToBezier(pointset, pointStart, pCurve, cTotal );
//
//                  i = pCurve->cpfx;
//
//               }
//               else if (pCurve->wType == TT_PRIM_QSPLINE)
//
//               {
//                  // Decode each Quadratic B-Spline segment, convert to bezier,
//                  // and append to the Bezier segments
//                  //                    cTotal += AppendQuadBSplineToBezier( &point[cTotal], pointStart, pCurve );
//
//                  cTotal = AppendQuadBSplineToBezier(pointset, pointStart, pCurve, cTotal );
//
//                  i = pCurve->cpfx;
//
//               }
//               else
//                  // Oops! A POLYCURVE format we don't understand.
//                  ; // error, error, error
//
//               // Move on to next curve in the contour.
//               pCurve = (LPTTPOLYCURVE)&(pCurve->apfx[i]);
//
//            }
//
//            // add points to close the contour.
//            // All contours are implied closed by TrueType definition.
//            // Depending on the specific font and glyph being used, these
//            // may not always be needed.
//
//            //            if ( point_i32[cTotal-1].x != point_i32[0].x || point_i32[cTotal-1].y != point_i32[0].y )
//            if (pointset.last().x != pointset.first().x ||
//                  pointset.last().y != pointset.first().y)
//            {
//               //cTotal += CloseContour(point, cTotal );
//               cTotal = CloseContour(pointset, cTotal );
//            }
//
//            // flip coordinates to get glyph right side up (Windows coordinates)
//            // TT native coordiantes are zero originate at lower-left.
//            // Windows MM_TEXT are zero originate at upper-left.
//            for (i = 0; i < pointset.get_size(); i++)
//               pointset[i].y = iFontHiHeight - pointset[i].y;
//            //point_i32[i].y = 0 - point_i32[i].y;
//
//            // draw the contour
//
//            //poly_bezier( hDC, point, cTotal );
//            //pPoints->m_dwCount = cTotal;
//            m_pointsets.add(pointset);
//         }
//         else
//            // Bad, bail, must have a bogus buffer.
//            break; // error, error, error
//
//         // Move on to next Contour.
//         // Its header starts immediate after this contour
//         pHeader = (LPTTPOLYGONHEADER)(((char *)pHeader) + pHeader->cb);
//
//      }
//
//      // free( point_i32 );
//   }
//
//
//#endif
//

   void glyph::clear()
   {

      //   m_lpBodyData = nullptr;
      //   m_lpOutlineData  = nullptr;

//#ifdef WINDOWS_DESKTOP
//
//      __memset(&m_gm, 0, sizeof(m_gm));
//
//#else
//
//      __throw(todo);
//
//#endif


   }


   void glyph::GetGlyphRect(i32 x, i32 y, RECTANGLE_I32 * prectangle)

   {

//#ifdef WINDOWS_DESKTOP
//
//      prectangle->left      = x - m_gm.gmptGlyphOrigin.x;
//
//      prectangle->top       = y - m_gm.gmptGlyphOrigin.y;
//
//      prectangle->right     = x + m_gm.gmBlackBoxX;
//
//      prectangle->bottom    = y + m_gm.gmBlackBoxY;
//
//
//#else
//
//      __throw(todo);
//
//#endif


   }


   void glyph::DrawGlyph(::draw2d::graphics_pointer & pgraphics, bool bFill, double dRateX, POINT_I32 * ppointOffset)

   {

      UNREFERENCED_PARAMETER(pgraphics);
      UNREFERENCED_PARAMETER(bFill);
      UNREFERENCED_PARAMETER(dRateX);
      UNREFERENCED_PARAMETER(ppointOffset);


      //psystem->draw2d()->api().draw_and_fill_beziers(pgraphics, &m_pointsets, dRateX, ppointOffset);


   }


} // namespace draw2d


