#pragma once

enum e_new_array
{
   new_array,

};

template < typename T >
class auto_pointer
{
public:

   T * m_p;
   bool m_bArray;

   auto_pointer()
   {

      m_p = nullptr;
      m_bArray = false;

   }

   auto_pointer(e_new_array, ::count c)
   {
      m_bArray = true;
      m_p = new T[(size_t) c];

   }

   auto_pointer(e_new_array, T * p)
   {
      m_bArray = true;
      m_p = p;

   }


   template < typename TYPE >
   auto_pointer(TYPE * p, ::count c)
   {
      
      m_bArray = true;

      m_p = new T[(size_t)c];

      for (index i = 0; i < c; i++)
      {
         
         ::copy(&m_p[(size_t)i], &p[(size_t) i]);

      }

   }


   template < typename TYPE, typename COPY >
   auto_pointer(TYPE* p, ::count c, COPY copy)
   {

      m_bArray = true;

      m_p = new T[(size_t)c];

      for (index i = 0; i < c; i++)
      {

         copy(&m_p[(size_t)i], &p[(size_t)i]);

      }

   }


   auto_pointer(T * point)
   {

      m_p = point;
      m_bArray = false;

   }


   auto_pointer(const auto_pointer & op)
   {

      m_p = op.m_p;
      m_bArray = op.m_bArray;

   }


   auto_pointer(auto_pointer && op)
   {

      m_p = op.m_p;
      m_bArray = op.m_bArray;
      op.m_p = nullptr;
      

   }


   ~auto_pointer()
   {

      destroy();

   }


   void destroy()
   {

      if (m_bArray)
      {

         delete[] m_p;

         m_p = NULL;

      }
      else
      {

         ::acme::del(m_p);

      }

   }


   T * detach()
   {

      T * point = m_p;

      m_p = nullptr;

      return point;

   }


   T * release()
   {

      return detach();

   }


   T * get()
   {

      return m_p;

   }


   T * get() const
   {

      return m_p;

   }

   operator T *()
   {

      return m_p;

   }


   operator T *() const
   {

      return m_p;

   }


   T & operator *()
   {

      return*m_p;

   }


   const T & operator *() const
   {

      return*m_p;

   }

   void reset(T * point)
   {

      if (point == m_p)
      {

         return;

      }

      destroy();

      m_p = point;

   }


   auto_pointer & operator = (T * point)
   {

      reset(point);

      return *this;

   }

   auto_pointer & operator = (const auto_pointer & op)
   {

      reset(op.m_p);

      return *this;

   }


   auto_pointer & operator = (auto_pointer && op)
   {

      if (op.m_p == m_p)
      {

         return *this;

      }

      destroy();

      m_p = op.m_p;

      op.m_p = nullptr;

      return *this;

   }


   T * operator ->()
   {

      return m_p;

   }


   const T * operator ->() const
   {

      return m_p;

   }

   template < typename TYPE >
   bool is()
   {

      return dynamic_cast < TYPE * > ((T *) this);

   }

};

// Remember you always can restore with #define ap(x) __AP(x),
// or #undef ap and use more verbore __AP,
// or even you may #undef both and use explicit ::auto_pointer < x >!
#define __AP(x) ::auto_pointer < x >
#define ap(x) __AP(x)


template <typename T>
inline auto __auto(T* p)
{
   return auto_pointer < T >(p);
}


