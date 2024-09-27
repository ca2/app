#pragma once


template < typename ARRAY >
class array_union_base
{

public:

   using BASE_TYPE = typename ARRAY::BASE_TYPE;

   ::array < ARRAY * >    m_2a;

   void add_array(ARRAY & a)
   {

      m_2a.add(&a);

   }

   const BASE_TYPE & operator[](::collection::index iIndex)
   {
      
      ::collection::index iArray = 0;

      for (; iArray < m_2a.size(); iArray++)
      {

         if (iIndex < m_2a[iArray]->size())
         {

            return m_2a[iArray]->element_at(iIndex);

         }

         iIndex -= m_2a[iArray]->size();

      }

      throw ::exception(error_index_out_of_bounds, "get_line with argument >= line_count");

      return m_2a[iArray]->element_at(0);

   }


   ::collection::count size() const
   {

      ::collection::count c = 0;

      for (::collection::index iArray = 0; iArray < m_2a.size(); iArray++)
      {

         c += m_2a[iArray]->size();

      }

      return c;

   }
   

};

template < typename ARRAY >
class array_traits :
   public ARRAY
{
public:


   ::collection::count get_upper_bound(::collection::index i = -1) const { return this->size() + i; }
   bool has_elements(::collection::count cMinimum = 1) const { return this->size() > cMinimum; }
   bool has_element() const { return this->has_elements(); }

};


template < typename ARRAY >
using array_union = array_traits < array_union_base < ARRAY > >;
