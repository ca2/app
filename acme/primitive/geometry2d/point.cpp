#include "framework.h"


//void point_i32::offset(i32 xOffset, i32 yOffset) noexcept
//{ x += xOffset; y += yOffset; }
//void point_i32::offset(const ::point_i32 & point) noexcept
//{ x += point.x; y += point.y; }
//void point_i32::offset(const ::size_i32 & size) noexcept
//{ x += size.cx; y += size.cy; }
//void point_i32::SetPoint(i32 X, i32 Y) noexcept
//{ x = X; y = Y; }
//bool point_i32::operator==(const ::point_i32 & point) const noexcept
//   { return (x == point.x && y == point.y); }
//bool point_i32::operator!=(const ::point_i32 & point) const noexcept
//   { return (x != point.x || y != point.y); }
//void point_i32::operator+=(const ::size_i32 & size) noexcept
//   { x += size.cx; y += size.cy; }
//void point_i32::operator-=(const ::size_i32 & size) noexcept
//   { x -= size.cx; y -= size.cy; }
//void point_i32::operator+=(const ::point_i32 & point) noexcept
//   { x += point.x; y += point.y; }
//void point_i32::operator-=(const ::point_i32 & point) noexcept
//   { x -= point.x; y -= point.y; }
//const ::point_i32 & point::operator+(const ::size_i32 & size) const noexcept
//{ return point(x + size.cx, y + size.cy); }
//const ::point_i32 & point::operator-(const ::size_i32 & size) const noexcept
//{ return point(x - size.cx, y - size.cy); }
//const ::point_i32 & point::operator-() const noexcept
//{ return point(-x, -y); }
//const ::point_i32 & point::operator+(const ::point_i32 & point) const noexcept
//{ return point(x +  point.x, y +  point.y); }
//size_i32 point_i32::operator-(const point_i32 &  point_i32) const noexcept
//{ return size_i32(x -  point.x, y -  point.y); }
//rectangle_i32 point_i32::operator+(const ::rectangle_i32 & rectangle) const noexcept

//{ return rectangle_i32(prectangle) + *this; }

//rectangle_i32 point_i32::operator-(const ::rectangle_i32 & rectangle) const noexcept

//{ return rectangle_i32(prectangle) - *this; }


//::u32 point_i32::u32() const noexcept
//{
//   return MAKELONG(x, y);
//}
//
//::u64 point_i32::u64() const noexcept
//{
//   return MAKELONG64(x, y);
//}
//
//::lparam point_i32::lparam() const noexcept
//
//{
//   return MAKELPARAM(x, y);
//}
//
//
//
//
//



//void point_i64::offset(i64 xOffset, i64 yOffset) noexcept
//{ x += xOffset; y += yOffset; }
//void point_i64::offset(POINT_I64 point_i64) noexcept
//{ x += point_i64.x; y += point_i64.y; }
//void point_i64::offset(SIZE_I64 size_i64) noexcept
//{ x += size_i64.cx; y += size_i64.cy; }
//void point_i64::SetPoint(i64 X, i64 Y) noexcept
//{ x = X; y = Y; }
//bool point_i64::operator==(POINT_I64 point_i64) const noexcept
//{ return (x == point_i64.x && y == point_i64.y); }
//bool point_i64::operator!=(POINT_I64 point_i64) const noexcept
//{ return (x != point_i64.x || y != point_i64.y); }
//void point_i64::operator+=(SIZE_I64 size_i64) noexcept
//{ x += size_i64.cx; y += size_i64.cy; }
//void point_i64::operator-=(SIZE_I64 size_i64) noexcept
//{ x -= size_i64.cx; y -= size_i64.cy; }
//void point_i64::operator+=(POINT_I64 point_i64) noexcept
//{ x += point_i64.x; y += point_i64.y; }
//void point_i64::operator-=(POINT_I64 point_i64) noexcept
//{ x -= point_i64.x; y -= point_i64.y; }
//point_i64 point_i64::operator+(SIZE_I64 size_i64) const noexcept
//{ return point_i64(x + size_i64.cx, y + size_i64.cy); }
//point_i64 point_i64::operator-(SIZE_I64 size_i64) const noexcept
//{ return point_i64(x - size_i64.cx, y - size_i64.cy); }
//point_i64 point_i64::operator-() const noexcept
//{ return point_i64(-x, -y); }
//point_i64 point_i64::operator+(POINT_I64 point_i32) const noexcept
//{ return point_i64(x + point.x, y + point.y); }
//size_i64 point_i64::operator-(POINT_I64 point_i32) const noexcept
//{ return size_i64(x - point.x, y - point.y); }
//rectangle_i64 point_i64::operator+(const RECTANGLE_I64 * prectangle) const noexcept
//
//{ return rectangle_i64(prectangle) + *this; }
//
//rectangle_i64 point_i64::operator-(const RECTANGLE_I64 * prectangle) const noexcept
//
//{ return rectangle_i64(prectangle) - *this; }
//
//
//::u32 point_i64::u32() const noexcept
//{
//   return MAKELONG(x, y);
//}
//
//::u64 point_i64::u64() const noexcept
//{
//   return MAKELONG64(x, y);
//}
//
//LPARAM point_i64::lparam() const noexcept
//
//{
//   return MAKELPARAM(x, y);
//}










//void point_f64::offset(double xOffset, double yOffset) noexcept
//{ x += xOffset; y += yOffset; }
//void point_f64::offset(POINT_F64 point_f64) noexcept
//{ x += point_f64.x; y += point_f64.y; }
//void point_f64::offset(SIZE_F64 size_i32) noexcept
//{ x += size.cx; y += size.cy; }
//void point_f64::SetPoint(double X, double Y) noexcept
//{ x = X; y = Y; }
//bool point_f64::operator==(POINT_F64 point_f64) const noexcept
//{ return (x == point_f64.x && y == point_f64.y); }
//bool point_f64::operator!=(POINT_F64 point_f64) const noexcept
//{ return (x != point_f64.x || y != point_f64.y); }
//void point_f64::operator+=(SIZE_F64 size_i32) noexcept
//{ x += size.cx; y += size.cy; }
//void point_f64::operator-=(SIZE_F64 size_i32) noexcept
//{ x -= size.cx; y -= size.cy; }
//void point_f64::operator+=(POINT_F64 point_f64) noexcept
//{ x += point_f64.x; y += point_f64.y; }
//void point_f64::operator-=(POINT_F64 point_f64) noexcept
//{ x -= point_f64.x; y -= point_f64.y; }
//point_f64 point_f64::operator+(SIZE_F64 size_i32) const noexcept
//{ return point_f64(x + size.cx, y + size.cy); }
//point_f64 point_f64::operator-(SIZE_F64 size_i32) const noexcept
//{ return point_f64(x - size.cx, y - size.cy); }
//point_f64 point_f64::operator-() const noexcept
//{ return point_f64(-x, -y); }
//point_f64 point_f64::operator+(POINT_F64 point_i32) const noexcept
//{ return point_f64(x +  point.x, y +  point.y); }
//size_f64 point_f64::operator-(POINT_F64  point_i32) const noexcept
//{ return size_f64(x -  point.x, y -  point.y); }
//rectangle_f64 point_f64::operator+(const rectangle_f64 & prectangle) const noexcept
//
//{ return rectangle_f64(prectangle) + *this; }
//
//rectangle_f64 point_f64::operator-(const rectangle_f64 & prectangle) const noexcept
//
//{ return rectangle_f64(prectangle) - *this; }
//
//
//::u32 point_f64::u32() const noexcept
//{
//   return MAKELONG((i32) x, (i32) y);
//}
//
//::u64 point_f64::u64() const noexcept
//{
//   return MAKELONG64((i32) x, (i32) y);
//}
//
//LPARAM point_f64::lparam() const noexcept
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


