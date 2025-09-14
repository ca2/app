#pragma once


template<typename TYPE, int t_iSize, enum_array t_earray, typename ARG_TYPE>
class block_array : 
   public ::array_range < TYPE, ARG_TYPE >
{
public:


   using ARRAY_RANGE = ::array_range < TYPE, ARG_TYPE >;
   using BASE_RANGE = ::array_range < TYPE, ARG_TYPE >;
   using RAW_BASE_ARRAY = block_array;
   using BASE_RAW_RANGE = ::range < TYPE * >;
   using BASE_TYPE = TYPE;

   TYPE m_ta[t_iSize];


   block_array() : ARRAY_RANGE (m_ta, m_ta){}
   ~block_array() {}

   TYPE *data() { return m_ta; }
   const TYPE *data() const { return m_ta; }

   ::collection::count storage_size() const { return t_iSize; }
//   ::collection::index get_upper_bound(::collection::index i = -1) const { return this->size() + i; }

     template<pointer_not_castable_to<TYPE *> P>
   ::collection::count allocate(::collection::count nNewSize, bool bShrink, bool bRaw, P &p)
   {
      TYPE t(p);
      return _allocate(nNewSize, bShrink, bRaw, &t);
   }
   template<pointer_castable_to<TYPE *> T>
   ::collection::count allocate(::collection::count nNewSize, bool bShrink, bool bRaw, T &t)
   {
      return _allocate(nNewSize, bShrink, bRaw, &t);
   }

   TYPE & add_new()
   {

      if (this->size() >= this->storage_size())
      {

         throw ::exception(error_wrong_state);

      }

      auto & t = m_ta[this->size()];

      this->m_end++;

      return t;

   }


   ::collection::index add(const TYPE & t)
   {

      if (this->size() >= this->storage_size())
      {

         throw ::exception(error_wrong_state);

      }

      auto i = this->size();

      m_ta[i] = t;

      this->m_end++;

      return i;

   }


   block_array &operator+=(const TYPE &t) 
   {
   
      add(t);

      return *this;
   
   }



   constexpr bool is_raw_array() const { return t_earray & e_array_raw; }

   /// @brief  attention, it doesn't actually destruct the object
   /// it just not regard it as part of the "filled" array...
   /// @param i 
   void erase_at(::collection::index iErase, ::collection::count countErase = 1)
   {

      if (iErase < 0)
      {

         throw ::exception(error_bad_argument);

      }
      else if (iErase >= this->size())
      {

         throw ::exception(error_wrong_state);

      }

      if (iErase + countErase > this->size())
      {

         countErase = this->size() - iErase;

      }

      if (countErase <= 0)
      {

         return;

      }

      if constexpr (t_earray & e_array_raw)
      {

         auto nTransferCount = this->size() - (iErase + countErase);

         auto i = iErase + countErase;

         ::safe_memory_transfer2(&m_ta[i - countErase], nTransferCount, &m_ta[i], nTransferCount);

      }
      else
      {

         for (auto i = iErase + 1; i < this->size(); i++)
         {

            m_ta[i - 1] = m_ta[i];

         }

      }

      this->m_end -= countErase;

   }

   void erase_first(::collection::count count = 1) { this->erase_at(0, count); 
   }

   void erase_last(::collection::count count = 1) 
   {
      this->erase_at(this->size() - count, count); 
   }



   ::collection::count _allocate(::collection::count nNewSize, bool bShrink, bool bRaw, const TYPE * type)
   {

      if (nNewSize >= this->storage_size())
      {

         throw ::exception(error_wrong_state);

      }

      return nNewSize;

   }

};
