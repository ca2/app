#include "framework.h"


//void point::offset(i32 xOffset, i32 yOffset) noexcept
//{ x += xOffset; y += yOffset; }
//void point::offset(const ::point & point) noexcept
//{ x += point.x; y += point.y; }
//void point::offset(const ::size & size) noexcept
//{ x += size.cx; y += size.cy; }
//void point::SetPoint(i32 X, i32 Y) noexcept
//{ x = X; y = Y; }
//bool point::operator==(const ::point & point) const noexcept
//   { return (x == point.x && y == point.y); }
//bool point::operator!=(const ::point & point) const noexcept
//   { return (x != point.x || y != point.y); }
//void point::operator+=(const ::size & size) noexcept
//   { x += size.cx; y += size.cy; }
//void point::operator-=(const ::size & size) noexcept
//   { x -= size.cx; y -= size.cy; }
//void point::operator+=(const ::point & point) noexcept
//   { x += point.x; y += point.y; }
//void point::operator-=(const ::point & point) noexcept
//   { x -= point.x; y -= point.y; }
//const ::point & point::operator+(const ::size & size) const noexcept
//{ return point(x + size.cx, y + size.cy); }
//const ::point & point::operator-(const ::size & size) const noexcept
//{ return point(x - size.cx, y - size.cy); }
//const ::point & point::operator-() const noexcept
//{ return point(-x, -y); }
//const ::point & point::operator+(const ::point & point) const noexcept
//{ return point(x +  point.x, y +  point.y); }
//size point::operator-(const point &  point) const noexcept
//{ return size(x -  point.x, y -  point.y); }
//rect point::operator+(const ::rect & rect) const noexcept

//{ return rect(prect) + *this; }

//rect point::operator-(const ::rect & rect) const noexcept

//{ return rect(prect) - *this; }


//::u32 point::u32() const noexcept
//{
//   return MAKELONG(x, y);
//}
//
//::u64 point::u64() const noexcept
//{
//   return MAKELONG64(x, y);
//}
//
//::lparam point::lparam() const noexcept
//
//{
//   return MAKELPARAM(x, y);
//}
//
//
//
//
//



//void point64::offset(i64 xOffset, i64 yOffset) noexcept
//{ x += xOffset; y += yOffset; }
//void point64::offset(POINT64 point64) noexcept
//{ x += point64.x; y += point64.y; }
//void point64::offset(SIZE64 size64) noexcept
//{ x += size64.cx; y += size64.cy; }
//void point64::SetPoint(i64 X, i64 Y) noexcept
//{ x = X; y = Y; }
//bool point64::operator==(POINT64 point64) const noexcept
//{ return (x == point64.x && y == point64.y); }
//bool point64::operator!=(POINT64 point64) const noexcept
//{ return (x != point64.x || y != point64.y); }
//void point64::operator+=(SIZE64 size64) noexcept
//{ x += size64.cx; y += size64.cy; }
//void point64::operator-=(SIZE64 size64) noexcept
//{ x -= size64.cx; y -= size64.cy; }
//void point64::operator+=(POINT64 point64) noexcept
//{ x += point64.x; y += point64.y; }
//void point64::operator-=(POINT64 point64) noexcept
//{ x -= point64.x; y -= point64.y; }
//point64 point64::operator+(SIZE64 size64) const noexcept
//{ return point64(x + size64.cx, y + size64.cy); }
//point64 point64::operator-(SIZE64 size64) const noexcept
//{ return point64(x - size64.cx, y - size64.cy); }
//point64 point64::operator-() const noexcept
//{ return point64(-x, -y); }
//point64 point64::operator+(POINT64 point) const noexcept
//{ return point64(x + point.x, y + point.y); }
//size64 point64::operator-(POINT64 point) const noexcept
//{ return size64(x - point.x, y - point.y); }
//rect64 point64::operator+(const RECT64 * prect) const noexcept
//
//{ return rect64(prect) + *this; }
//
//rect64 point64::operator-(const RECT64 * prect) const noexcept
//
//{ return rect64(prect) - *this; }
//
//
//::u32 point64::u32() const noexcept
//{
//   return MAKELONG(x, y);
//}
//
//::u64 point64::u64() const noexcept
//{
//   return MAKELONG64(x, y);
//}
//
//LPARAM point64::lparam() const noexcept
//
//{
//   return MAKELPARAM(x, y);
//}










//void pointd::offset(double xOffset, double yOffset) noexcept
//{ x += xOffset; y += yOffset; }
//void pointd::offset(POINTD pointd) noexcept
//{ x += pointd.x; y += pointd.y; }
//void pointd::offset(SIZED size) noexcept
//{ x += size.cx; y += size.cy; }
//void pointd::SetPoint(double X, double Y) noexcept
//{ x = X; y = Y; }
//bool pointd::operator==(POINTD pointd) const noexcept
//{ return (x == pointd.x && y == pointd.y); }
//bool pointd::operator!=(POINTD pointd) const noexcept
//{ return (x != pointd.x || y != pointd.y); }
//void pointd::operator+=(SIZED size) noexcept
//{ x += size.cx; y += size.cy; }
//void pointd::operator-=(SIZED size) noexcept
//{ x -= size.cx; y -= size.cy; }
//void pointd::operator+=(POINTD pointd) noexcept
//{ x += pointd.x; y += pointd.y; }
//void pointd::operator-=(POINTD pointd) noexcept
//{ x -= pointd.x; y -= pointd.y; }
//pointd pointd::operator+(SIZED size) const noexcept
//{ return pointd(x + size.cx, y + size.cy); }
//pointd pointd::operator-(SIZED size) const noexcept
//{ return pointd(x - size.cx, y - size.cy); }
//pointd pointd::operator-() const noexcept
//{ return pointd(-x, -y); }
//pointd pointd::operator+(POINTD point) const noexcept
//{ return pointd(x +  point.x, y +  point.y); }
//sized pointd::operator-(POINTD  point) const noexcept
//{ return sized(x -  point.x, y -  point.y); }
//rectd pointd::operator+(const rectd & prect) const noexcept
//
//{ return rectd(prect) + *this; }
//
//rectd pointd::operator-(const rectd & prect) const noexcept
//
//{ return rectd(prect) - *this; }
//
//
//::u32 pointd::u32() const noexcept
//{
//   return MAKELONG((i32) x, (i32) y);
//}
//
//::u64 pointd::u64() const noexcept
//{
//   return MAKELONG64((i32) x, (i32) y);
//}
//
//LPARAM pointd::lparam() const noexcept
//
//{
//   return MAKELPARAM((i32) x, (i32) y);
//}
//
//
//

//locationd locationd::rotate(locationd point)
//{
//
//   locationd point1;
//   point1.x = x *cos(point.z) - y * sin(point.z) ;
//   point1.y = x *sin(point.z) + y * cos(point.z) ;
//   point1.z = z;
//
//   locationd point2;
//   point2.y = point1.y*cos(point.x) - point1.z * sin(point.x) ;
//   point2.z = point1.y *sin(point.x) + point1.z * cos(point.x) ;
//   point2.x = point1.x;
//
//   locationd p3;
//   p3.z = point2.z *cos(point.y) - point2.x * sin(point.y) ;
//   p3.x = point2.z *sin(point.y) + point2.x * cos(point.y) ;
//   p3.y = point2.y;
//
//   return p3;
//}


