#pragma once


#include <utility>

template <typename TO, typename FROM>
concept dynamically_castable =
   requires
{
   dynamic_cast<TO>(std::declval<FROM>());
};


template < typename TYPE >
class auto_pointer
{
public:


   using element_type = TYPE;
   using pointer = TYPE *;


   TYPE * m_p;
   bool m_bOwn;


   constexpr auto_pointer() noexcept
   {
      m_p = nullptr;
      m_bOwn = false;
   }


   constexpr auto_pointer(::std::nullptr_t) noexcept
   {
      m_p = nullptr;
      m_bOwn = false;

   }


   explicit auto_pointer(pointer p)
   {

      m_p = p;
      m_bOwn = false;

   }


   template < typename TYPE2 >
   auto_pointer(const transfer_pointer < TYPE2 > & p)
   {

      if constexpr (dynamically_castable<TYPE, TYPE2>)
      {

         m_p = dynamic_cast <TYPE>(p.m_p);
         if (!m_p && p.m_p)
         {

            throw ::exception(error_wrong_type);

         }
      }
      else
      {
         /// non cast on purpose, meant to permit only same type cast or cast to base class pointer.
         m_p = p.m_p;
      }
      m_bOwn = true;

   }


   auto_pointer(transfer_t, pointer p)
   {

      m_p = p;
      m_bOwn = true;

   }


   auto_pointer(const auto_pointer & p) noexcept
   {

      m_p = p.m_p;
      m_bOwn = false;

   }
   auto_pointer(auto_pointer && p) noexcept
   {
      m_p = p.m_p;
      p.m_p = nullptr;
      m_bOwn = p.m_bOwn;
      p.m_bOwn = false;


   }


   ~auto_pointer()
   {

      destroy();

   }

   void destroy()
   {

      if (m_bOwn)
      {

         m_bOwn = false;

         auto p = m_p;

         m_p = nullptr;

         if (p)
         {

            delete p;

         }

      }

   }


   template < typename TYPE2 >
   auto_pointer & operator =(const transfer_pointer < TYPE2 > & p)
   {

      destroy();

      if constexpr (dynamically_castable<TYPE, TYPE2>)
      {

         m_p = dynamic_cast <TYPE>(p.m_p);
         if (!m_p && p.m_p)
         {

            throw ::exception(error_wrong_type);

         }
      }
      else
      {
         /// non cast on purpose, meant to permit only same type or cast to base class pointer.
         m_p = p.m_p;
      }
      m_bOwn = true;

      return *this;

   }



   auto_pointer & operator =(const auto_pointer & p) noexcept
   {

      if (this != &p)
      {

         destroy();

         m_p = p.m_p;
         m_bOwn = false;

      }

      return *this;


   }


   auto_pointer & operator =(auto_pointer && p) noexcept
   {

      if (this != &p)
      {
         destroy();

         m_p = p.m_p;
         m_bOwn = p.m_bOwn;

         p.m_p = nullptr;
         p.m_bOwn = false;

      }

      return *this;

   }




   auto_pointer & operator =(::std::nullptr_t) noexcept
   {

      destroy();
      return *this;

   }


   [[nodiscard]] explicit operator bool() const noexcept
   {

      return static_cast < bool >(m_p);

   }


   [[nodiscard]] operator TYPE *() const noexcept
   {

      return m_p;

   }


   [[nodiscard]] TYPE * operator ->() const noexcept
   {

      return m_p;

   }



};



template < typename TYPE >
inline auto_pointer <TYPE > as_auto_pointer(TYPE * p)
{

   return { transfer_t{}, p };

}



template <typename TYPE, typename... ARGUMENTS>
[[nodiscard]]
inline auto_pointer<TYPE> create_auto_pointerø(ARGUMENTS &&... arguments)
{

   return { transfer_t{}, new TYPE(::std::forward<ARGUMENTS>(arguments)...) };
}

