#pragma once



template < typename POINTER_TYPE >
class cotaskptr
{
public:


   POINTER_TYPE   m_p;

   cotaskptr()
   {

      m_p = nullptr;

   }


   virtual ~cotaskptr()
   {

      free();

   }

   void alloc(SIZE_T size)
   {

      if (m_p != nullptr)
      {

         m_p = CoTaskMemRealloc(m_p, size);

      }
      else
      {

         m_p = CoTaskMemAlloc(size);

      }

   }

   bool is_null() const
   {

      return m_p == nullptr;

   }

   bool is_set() const
   {

      return m_p != nullptr;

   }

   virtual void free()
   {

      if (m_p != nullptr)
      {

         ::CoTaskMemFree(m_p);

         m_p = nullptr;

      }

   }


   operator POINTER_TYPE()
   {

      return m_p;

   }

   operator const POINTER_TYPE() const
   {

      return m_p;

   }


   POINTER_TYPE operator ->()
   {

      return m_p;

   }


   const POINTER_TYPE operator ->() const
   {

      return m_p;

   }

   POINTER_TYPE * operator &()
   {

      free();

      return &m_p;

   }

   const POINTER_TYPE * operator &() const
   {

      return &m_p;

   }


};


template < typename POINTER_TYPE >
class sec_cotaskptr :
   virtual public cotaskptr < POINTER_TYPE >
{
public:


   ::u32         m_size;


   sec_cotaskptr()
   {

      m_size = 0;
      m_p = nullptr;

   }


   virtual ~sec_cotaskptr()
   {

      free();

   }

   using cotaskptr::alloc;
   void alloc()
   {

      alloc(m_size);

   }

   virtual void free() override
   {

      if (m_p != nullptr)
      {

         if (m_size > 0)
         {

            SecureZeroMemory(m_p, m_size);

            m_size = 0;

         }

         cotaskptr::free();

      }

   }


};


#define cotaskp(POINTER_TYPE) cotaskptr < POINTER_TYPE >



template < typename POINTER_TYPE >
inline auto as_string(const cotaskptr < POINTER_TYPE > & ptr)
{

   return as_string((const POINTER_TYPE)ptr);

}



namespace str
{


   inline ansi_string & assign(ansi_string & ansistrDst, const cotaskptr < PWSTR > & pwidesz)
   {

      ansistrDst.assign(pwidesz.operator const PWSTR());

      return ansistrDst;

   }


   inline wide_string & assign(wide_string & widestrDst, const cotaskptr < PSTR > & pansisz)
   {

      widestrDst.assign(pansisz.operator const PSTR());

      return widestrDst;

   }


   inline ansi_string & assign(ansi_string & ansistrDst, const cotaskptr < PSTR > & pansisz)
   {

      ansistrDst.assign(pansisz.operator const PSTR());

      return ansistrDst;

   }


   inline wide_string & assign(wide_string & widestrDst, const cotaskptr < PWSTR > & pwidesz)
   {

      widestrDst.assign(pwidesz.operator const PWSTR());

      return widestrDst;

   }


} // namespace str



