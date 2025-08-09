#pragma once


#include "rectangle.h"


template < primitive_number NUMBER >
class rectangle_base_array :
public ::array < ::rectangle_type < NUMBER > >
{
public:


   //using BASE_ARRAY_TYPE = array < ::rectangle_type < NUMBER > >;
   //using RECTANGLE_BASE_TYPE = ::rectangle_type < NUMBER >;
   //using UNIT_TYPE = typename ::rectangle_type < NUMBER >::UNIT_TYPE;
   using UNIT_TYPE = NUMBER;
   //using POINT_TYPE = typename ::rectangle_type < NUMBER >::POINT_TYPE;
   //using SIZE_TYPE = typename ::rectangle_type < NUMBER >::SIZE_TYPE;

   
   using array < ::rectangle_type < NUMBER > >::array;
   rectangle_base_array(const rectangle_base_array & a) noexcept : array < ::rectangle_type < NUMBER > > (a) { }
   rectangle_base_array(rectangle_base_array && a) noexcept : array < ::rectangle_type < NUMBER > >(::transfer(a)) { }

   
   virtual ~rectangle_base_array();

   using array < ::rectangle_type < NUMBER > >::add;
   void add(const ::rectangle_type < NUMBER > & rectangle);
   void add(UNIT_TYPE left, UNIT_TYPE top, UNIT_TYPE right, UNIT_TYPE bottom);
   void add(const ::point_type < NUMBER > & point, const ::size_type < NUMBER > & size);
   void add(const ::size_type < NUMBER > & size);
   void add_if_none_contains(const ::rectangle_type < NUMBER > & rectangle)
   {
      if (!this->any_contains(rectangle)) add(rectangle);
   }
   template < primitive_container CONTAINER >
   void append_if_none_contains(const CONTAINER & container)
   {
      for (auto & r : container) add_if_none_contains(r);
   }
   void intersect(const ::rectangle_type < NUMBER > & rectangle);
   bool any_contains(const ::rectangle_type < NUMBER > & rectangle) const
   {
      for (auto & r : *this) if (r.contains(rectangle)) return true;
      return false;
   }

   void add_dim(UNIT_TYPE x, UNIT_TYPE y, UNIT_TYPE cx, UNIT_TYPE cy);

   ::collection::index max_normal_intersect_area(const ::rectangle_type < NUMBER > & rectangle, const ::rectangle_type < NUMBER > & rectangleModel);


   void get_box(::rectangle_type < NUMBER > * prectangle);
   

   ::rectangle_type < NUMBER > union_rect();

   void offset(UNIT_TYPE cx, UNIT_TYPE cy);
   void offset(::point_type < NUMBER > point);

   UNIT_TYPE total_area(::collection::index iStart = 0, ::collection::count c = -1) const
   { 
      
      UNIT_TYPE i = 0; 
      
      this->predicate_each([&i](auto& r)
         {

            i += r.area();

         }, iStart, c);
            
      return i; 

   }

   rectangle_base_array& operator = (const rectangle_base_array& array) { ::array < ::rectangle_type < NUMBER > >::operator=(array); return *this; }
   rectangle_base_array& operator = (rectangle_base_array&& array) { ::array < ::rectangle_type < NUMBER > >::operator=(::transfer(array)); return *this; }
   rectangle_base_array& operator = (std::initializer_list < ::rectangle_type < NUMBER > > initializer_list) { ::array < ::rectangle_type < NUMBER > > ::operator=(initializer_list); return *this; }


};

template < primitive_number NUMBER >
inline void rectangle_base_array < NUMBER >::offset(::point_type < NUMBER > point)
{
   offset(point.x(), point.y());
}




template < primitive_number NUMBER >
rectangle_base_array < NUMBER >::~rectangle_base_array()
{

}

template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::offset(UNIT_TYPE cx, UNIT_TYPE cy)
{

   for (int i = 0; i < this->get_size(); i++)
   {

      ::rectangle_type < NUMBER > & rectangle = this->element_at(i);

      rectangle.left() += cx;
      rectangle.top() += cy;
      rectangle.right() += cx;
      rectangle.bottom() += cy;

   }

}


template < primitive_number NUMBER >
::rectangle_type < NUMBER > rectangle_base_array < NUMBER >::union_rect()
{
   
   if(this->is_empty())
   {
      
      return {};
      
   }

   ::rectangle_type < NUMBER > rectangleUnion(0, 0, 0, 0);

   rectangleUnion = this->first();

   for (int i = 1; i < this->get_size(); i++)
   {
      
      rectangleUnion.unite(rectangleUnion, this->element_at(i));
      //this->element_at(i).expand_bounding_box(rectangleUnion.top_left(), rectangleUnion.bottom_right());
   }

   return rectangleUnion;

}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::get_box(::rectangle_type < NUMBER > * prectangle)

{

   *prectangle = union_rect();


}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::intersect(const ::rectangle_type < NUMBER > & rectangle)
{

   for (::collection::index i = 0; i < this->get_size();)
   {
      
      this->element_at(i).intersect(this->element_at(i), rectangle);
      
      if (this->element_at(i).is_null())
      {
         
         this->erase_at(i);
         
      }
      else
      {
         
         i++;
         
      }
      
   }

}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::add(const ::rectangle_type < NUMBER > & rectangle)
{
   array < ::rectangle_type < NUMBER > >::add(rectangle);
}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::add(UNIT_TYPE left, UNIT_TYPE top, UNIT_TYPE right, UNIT_TYPE bottom)
{
   add(::rectangle_type < NUMBER >(left, top, right, bottom));
}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::add_dim(UNIT_TYPE x, UNIT_TYPE y, UNIT_TYPE cx, UNIT_TYPE cy)
{
   add(int_rectangle_dimension(x, y, cx, cy));
}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::add(const ::point_type < NUMBER > & point, const ::size_type < NUMBER > & size)
{
   add(::rectangle_type < NUMBER >(point, size));
}


template < primitive_number NUMBER >
void rectangle_base_array < NUMBER >::add(const ::size_type < NUMBER > & size)
{
   this->add(::rectangle_type < NUMBER >(size));
}


template < primitive_number NUMBER >
::collection::index rectangle_base_array < NUMBER >::max_normal_intersect_area(const ::rectangle_type < NUMBER > & rectangleParam, const ::rectangle_type < NUMBER > & rectangleModel)
{

   ::collection::index iFound = -1;
   ::rectangle_type < NUMBER > rectangle;
   auto iModelArea = rectangleModel.width() * rectangleModel.height();
   decltype(iModelArea) iArea;
   decltype(iModelArea) iAreaMax = 0;

   if (iModelArea == 0)
      return -1;

   for (::collection::index i = 0; i < this->get_count(); i++)
   {

      if (rectangle.intersect(&rectangleParam, this->element_at(i)))
      {

         iArea = rectangle.area() * iModelArea / this->element_at(i).area();

         if (iArea > iAreaMax)
         {

            iFound = i;

            iAreaMax = iArea;

         }


      }

   }

   return iFound;

}


CLASS_DECL_ACME int_rectangle_array get_top_left_oriented_damaged_areas_by_resizing(const ::int_rectangle & rectangleNew, const ::int_rectangle & rectangleOld, bool bOnlyGrowing = true);



