#pragma once


template < typename ARRAY >
class array_union
{

public:

   using BASE_TYPE = typename ARRAY::BASE_TYPE;

   ::array < ARRAY * >    m_2a;

   void add_array(ARRAY & a)
   {

      m_2a.add(&a);

   }

   const BASE_TYPE & operator[](::index i)
   {

      for (::index i = 0; i < m_2a.size(); i++)
      {

         if (i < m_2a[i]->size())
         {

            return m_2a[i]->element_at(i);

         }

         i -= m_2a[i]->size();

      }

      throw ::exception(error_index_out_of_bounds, "get_line with argument >= line_count");

      return {};

   }


   ::count size() const
   {

      ::count c = 0;

      for (::index i = 0; i < m_2a.size(); i++)
      {

         c += m_2a[i]->size();

      }

      return c;

   }
   ::count get_upper_bound(::index i = -1) const { return size() + i; }

};


