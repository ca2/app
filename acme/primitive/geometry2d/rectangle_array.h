#pragma once


template < typename RECT_TYPE >
class rect_array_base :
   public array < RECT_TYPE >
{
public:


   using RECT_BASE_TYPE = typename RECT_TYPE::RECT_BASE_TYPE;
   using UNIT_TYPE = typename RECT_TYPE::UNIT_TYPE;
   using POINT_TYPE = typename RECT_TYPE::POINT_TYPE;
   using SIZE_TYPE = typename RECT_TYPE::SIZE_TYPE;


   virtual ~rect_array_base();

   using array < RECT_TYPE >::add;
   void add(const RECT_TYPE & rectangle);
   void add(UNIT_TYPE left, UNIT_TYPE top, UNIT_TYPE right, UNIT_TYPE bottom);
   void add(const POINT_TYPE & point, const SIZE_TYPE & size);
   void add(const SIZE_TYPE & size);
   void intersect(const RECT_TYPE & rectangle);

   void add_dim(UNIT_TYPE x, UNIT_TYPE y, UNIT_TYPE cx, UNIT_TYPE cy);

   index max_normal_intersect_area(const RECT_TYPE & rectangle, const RECT_TYPE & rectModel);


   void get_box(RECT_BASE_TYPE * prectangle);

   RECT_TYPE union_rect();

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

};

template < typename RECT_TYPE >
inline void rect_array_base < RECT_TYPE >::offset(POINT_TYPE point)
{
   offset(point.x, point.y);
}




template < typename RECT_TYPE >
rect_array_base < RECT_TYPE >::~rect_array_base()
{

}

template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::offset(UNIT_TYPE cx, UNIT_TYPE cy)
{

   for (i32 i = 0; i < this->get_size(); i++)
   {

      RECT_TYPE & rectangle = this->element_at(i);

      rectangle.left += cx;
      rectangle.top += cy;
      rectangle.right += cx;
      rectangle.bottom += cy;

   }

}


template < typename RECT_TYPE >
RECT_TYPE rect_array_base < RECT_TYPE >::union_rect()
{

   RECT_TYPE rectUnion(0, 0, 0, 0);

   for (i32 i = 0; i < this->get_size(); i++)
   {
      rectUnion.unite(rectUnion, this->element_at(i));
   }

   return rectUnion;

}


template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::get_box(RECT_BASE_TYPE * prectangle)

{

   *prectangle = union_rect();


}


template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::intersect(const RECT_TYPE & rectangle)
{

   for (index i = 0; i < this->get_size();)
   {
      this->element_at(i).intersect(this->element_at(i), rectangle);
      if (this->element_at(i).is_null())
      {
         this->remove_at(i);
      }
      else
      {
         i++;
      }
   }

}

template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::add(const RECT_TYPE & rectangle)
{
   array < RECT_TYPE >::add(rectangle);
}


template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::add(UNIT_TYPE left, UNIT_TYPE top, UNIT_TYPE right, UNIT_TYPE bottom)
{
   add(RECT_TYPE(left, top, right, bottom));
}


template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::add_dim(UNIT_TYPE x, UNIT_TYPE y, UNIT_TYPE cx, UNIT_TYPE cy)
{
   add(rect_dim(x, y, cx, cy));
}


template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::add(const POINT_TYPE & point, const SIZE_TYPE & size)
{
   add(RECT_TYPE(point, size));
}


template < typename RECT_TYPE >
void rect_array_base < RECT_TYPE >::add(const SIZE_TYPE & size)
{
   this->add(RECT_TYPE(size));
}


template < typename RECT_TYPE >
index rect_array_base < RECT_TYPE >::max_normal_intersect_area(const RECT_TYPE & rectParam, const RECT_TYPE & rectModel)
{

   index iFound = -1;
   RECT_TYPE rectangle;
   auto iModelArea = rectModel.width() * rectModel.height();
   decltype(iModelArea) iArea;
   decltype(iModelArea) iAreaMax = 0;

   if (iModelArea == 0)
      return -1;

   for (index i = 0; i < this->get_count(); i++)
   {

      if (rectangle.intersect(&rectParam, this->element_at(i)))
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





using rect_array = rect_array_base < rectangle_i32 >;
using rect64_array = rect_array_base < rectangle_i64 >;
using rectd_array = rect_array_base < rectangle_f64 >;




