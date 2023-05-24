#pragma once


template < typename RECTANGLE_TYPE >
class rectangle_array_base :
   public array < RECTANGLE_TYPE >
{
public:


   using BASE_ARRAY_TYPE = array < RECTANGLE_TYPE >;
   using RECTANGLE_BASE_TYPE = typename RECTANGLE_TYPE;
   using UNIT_TYPE = typename RECTANGLE_TYPE::UNIT_TYPE;
   using POINT_TYPE = typename RECTANGLE_TYPE::POINT_TYPE;
   using SIZE_TYPE = typename RECTANGLE_TYPE::SIZE_TYPE;


   virtual ~rectangle_array_base();

   using array < RECTANGLE_TYPE >::add;
   void add(const RECTANGLE_TYPE & rectangle);
   void add(UNIT_TYPE left, UNIT_TYPE top, UNIT_TYPE right, UNIT_TYPE bottom);
   void add(const POINT_TYPE & point, const SIZE_TYPE & size);
   void add(const SIZE_TYPE & size);
   void intersect(const RECTANGLE_TYPE & rectangle);

   void add_dim(UNIT_TYPE x, UNIT_TYPE y, UNIT_TYPE cx, UNIT_TYPE cy);

   index max_normal_intersect_area(const RECTANGLE_TYPE & rectangle, const RECTANGLE_TYPE & rectangleModel);


   void get_box(RECTANGLE_BASE_TYPE * prectangle);

   RECTANGLE_TYPE union_rect();

   void offset(UNIT_TYPE cx, UNIT_TYPE cy);
   void offset(POINT_TYPE point);

   UNIT_TYPE total_area(::index iStart = 0, ::count c = -1) const
   { 
      
      UNIT_TYPE i = 0; 
      
      this->predicate_each([&i](auto& r)
         {

            i += r.area();

         }, iStart, c);
            
      return i; 

   }

   rectangle_array_base& operator = (const rectangle_array_base& array) { BASE_ARRAY_TYPE::operator=(array); return *this; }
   rectangle_array_base& operator = (rectangle_array_base&& array) { BASE_ARRAY_TYPE::operator=(::transfer(array)); return *this; }
   rectangle_array_base& operator = (std::initializer_list < RECTANGLE_TYPE > initializer_list) { BASE_ARRAY_TYPE ::operator=(initializer_list); return *this; }


};

template < typename RECTANGLE_TYPE >
inline void rectangle_array_base < RECTANGLE_TYPE >::offset(POINT_TYPE point)
{
   offset(point.x(), point.y());
}




template < typename RECTANGLE_TYPE >
rectangle_array_base < RECTANGLE_TYPE >::~rectangle_array_base()
{

}

template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::offset(UNIT_TYPE cx, UNIT_TYPE cy)
{

   for (i32 i = 0; i < this->get_size(); i++)
   {

      RECTANGLE_TYPE & rectangle = this->element_at(i);

      rectangle.left += cx;
      rectangle.top += cy;
      rectangle.right += cx;
      rectangle.bottom += cy;

   }

}


template < typename RECTANGLE_TYPE >
RECTANGLE_TYPE rectangle_array_base < RECTANGLE_TYPE >::union_rect()
{

   RECTANGLE_TYPE rectangleUnion(0, 0, 0, 0);

   for (i32 i = 0; i < this->get_size(); i++)
   {
      rectangleUnion.unite(rectangleUnion, this->element_at(i));
   }

   return rectangleUnion;

}


template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::get_box(RECTANGLE_BASE_TYPE * prectangle)

{

   *prectangle = union_rect();


}


template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::intersect(const RECTANGLE_TYPE & rectangle)
{

   for (index i = 0; i < this->get_size();)
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

template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::add(const RECTANGLE_TYPE & rectangle)
{
   array < RECTANGLE_TYPE >::add(rectangle);
}


template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::add(UNIT_TYPE left, UNIT_TYPE top, UNIT_TYPE right, UNIT_TYPE bottom)
{
   add(RECTANGLE_TYPE(left, top, right, bottom));
}


template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::add_dim(UNIT_TYPE x, UNIT_TYPE y, UNIT_TYPE cx, UNIT_TYPE cy)
{
   add(rectangle_i32_dimension(x, y, cx, cy));
}


template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::add(const POINT_TYPE & point, const SIZE_TYPE & size)
{
   add(RECTANGLE_TYPE(point, size));
}


template < typename RECTANGLE_TYPE >
void rectangle_array_base < RECTANGLE_TYPE >::add(const SIZE_TYPE & size)
{
   this->add(RECTANGLE_TYPE(size));
}


template < typename RECTANGLE_TYPE >
index rectangle_array_base < RECTANGLE_TYPE >::max_normal_intersect_area(const RECTANGLE_TYPE & rectangleParam, const RECTANGLE_TYPE & rectangleModel)
{

   index iFound = -1;
   RECTANGLE_TYPE rectangle;
   auto iModelArea = rectangleModel.width() * rectangleModel.height();
   decltype(iModelArea) iArea;
   decltype(iModelArea) iAreaMax = 0;

   if (iModelArea == 0)
      return -1;

   for (index i = 0; i < this->get_count(); i++)
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









