#pragma once


template < typename POINTER_ARRAY_PROCESS, typename TYPE >
class pointer_array_process :
   public POINTER_ARRAY_PROCESS
{
public:

   using POINTER_ARRAY_PROCESS_BASE_TYPE = typename POINTER_ARRAY_PROCESS::BASE_TYPE;

   //using POINTER_ARRAY_PROCESS::POINTER_ARRAY_PROCESS;
   using BASE_ARRAY = POINTER_ARRAY_PROCESS;

   //using ref_iterator = typename POINTER_ARRAY_PROCESS::ref_iterator;
   //using const_ref_iterator = typename POINTER_ARRAY_PROCESS::const_ref_iterator;


   pointer_array_process() { }
   pointer_array_process(const pointer_array_process & array) : BASE_ARRAY(array) { }
   pointer_array_process(pointer_array_process && array) noexcept : BASE_ARRAY(::transfer(array)) { }

   //inline auto ptra(index iStart = 0, index iEnd = -1) { return ARRAY_BASE::values(iStart, iEnd); }

   //inline auto ptra(index iStart = 0, index iEnd = -1) const { return ARRAY_BASE::values(iStart, iEnd); }

   //inline auto values(index iStart = 0, index iEnd = -1) { return ref_iterator(iStart, iEnd, this); }

   //inline auto values(index iStart = 0, index iEnd = -1) const { return const_ref_iterator(iStart, iEnd, this); }

   //inline auto begin() { return ref_iterator(0, m_nSize, this); }

   //inline auto end() { return ref_iterator(m_nSize, m_nSize, this); }

   //inline auto begin() const { return const_ref_iterator(0, m_nSize, this); }

   //inline auto end() const { return const_ref_iterator(m_nSize, m_nSize, this); }

   //ref_iterator ref_it(::index iStart) { return ref_iterator(iStart, this); }
   //ref_iterator ref_it(::index iStart, ::count cCount) { return ref_iterator(iStart + (cCount < 0 ? this->get_count() + cCount + 1 : cCount), this); }

   //ref_iterator_range refa(::index iStart = 0, ::count cCount = -1) { return ref_iterator(ref_it(iStart), ref_it(iStart, cCount)); }

   template < typename REF >
   inline bool contains_ref(const REF & ref)
   {

      for (auto & p : *this)
      {

         if (*p == ref)
         {

            return true;

         }

      }

      return false;

   }


   POINTER_ARRAY_PROCESS_BASE_TYPE pop()
   {

      if (this->is_empty())
      {

         return nullptr;

      }

      return POINTER_ARRAY_PROCESS::pop();

   }

   TYPE& first_ref(::index n = 0) const
   {

      return *this->first(n);

   }


   TYPE& first_ref(::index n = 0)
   {

      return *this->first(n);

   }



   TYPE& last_ref(::index n = -1) const
   {

      return *this->last(n);

   }


   TYPE& last_ref(::index n = -1)
   {

      return *this->last(n);

   }




};



