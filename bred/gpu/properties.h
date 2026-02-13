// Created by camilo on 2025-05-19 05:52 <3ThomasBorregaardSorensen!!
#pragma once


//#include "bred/gpu/_.h"
//


class memory_composite :
   virtual public ::particle
{
public:

   ::pointer < ::memory > m_pmemory;


   memory_composite()
   {

   }

   ~memory_composite() override
   {

   }


   ::memory & memory()
   {

      if (!m_pmemory)
      {

         øconstruct(m_pmemory);

      }

      return * m_pmemory;

   }


   ::memory & memory() const
   {

      return ((memory_composite *)this)->memory();

   }



};

template < typename TYPE >
inline ::gpu::property* gpu_properties()
{

	throw ::error_interface_only;

	return nullptr;

}


namespace gpu
{

	CLASS_DECL_BRED::gpu::device* thread_gpu_device();
	class property
	{
	public:

		const_char_pointer m_pszName = nullptr;
		::gpu::enum_type		m_etype =::gpu::e_type_none;
		const property* m_pproperties = nullptr;
		int m_iArraySize = 0;
		int m_iCachedSizeWithSamplers = -1;
      int m_iCachedSizeWithoutSamplers = -1;
		int m_iCachedOffset = -1;

		property() {}
        property(nullptr_t) {}
		property(const_char_pointer pszName, ::gpu::enum_type etype) :
			m_pszName(pszName), m_etype(etype)
		{


		}

		property(const_char_pointer pszName, const property * pproperty, int iSize = 1);
      property(const property &property) :
         m_pszName(property.m_pszName), 
         m_etype(property.m_etype),
         m_pproperties(property.m_pproperties),
         m_iArraySize(property.m_iArraySize), 
         m_iCachedSizeWithSamplers(property.m_iCachedSizeWithSamplers),
         m_iCachedSizeWithoutSamplers(property.m_iCachedSizeWithoutSamplers),
         m_iCachedOffset(property.m_iCachedOffset)
		{
		}


		inline const property* find(const_char_pointer pszName) const;

		inline int get_size(bool bWithSamplers) const;

		inline ::collection::count count() const;

		inline int get_offset(const_char_pointer pszName) const;

      inline int find_index(const_char_pointer pszName) const;

		inline int get_item_size(bool bWithSamplers) const
		{
			if (m_etype == e_type_array)
			{

				return m_pproperties->get_size(bWithSamplers) * m_iArraySize;
			}
			else
			{
				return ::gpu::get_type_size(m_etype);
			}
		}

	};


	inline const property* property::find(const_char_pointer pszName) const
	{

		auto p = this;

		int iLen = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				return nullptr;

			}

         ::string strName(p->m_pszName);

         strName.begins_eat("sampler:");

         auto iLenItem = p->get_item_size(true);

			if (p->m_iCachedOffset < 0)
			{

				((property*)p)->m_iCachedOffset = iLen;

			}

			if (p->m_iCachedSizeWithSamplers < 0)
			{

				((property*)p)->m_iCachedSizeWithSamplers = iLenItem;

			}

			if (strName == pszName)
			{

				return p;

			}

			iLen += iLenItem;

			p++;

		}

	}


	inline int property::get_size(bool bWithSamplers) const
	{
		auto p = this;
		int iLen = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				return iLen;

			}

         ::string strName(p->m_pszName);

         bool bSampler = strName.begins("sampler:");

			auto iLenItem = p->get_item_size(bWithSamplers);

         if (bWithSamplers || !bSampler)
         {

            iLen += iLenItem;

         }

			p++;

		}

	}


	inline ::collection::count property::count() const
	{
		
		auto p = this;

		::collection::count count = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				return count;

			}

			count++;

			p++;

		}

	}


	inline int property::get_offset(const_char_pointer pszName) const
	{
		auto p = this;
		int iLen = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				throw ::exception(error_not_found);

			}

         ::string strName(p->m_pszName);

         strName.begins_eat("sampler:");

			if (strName == pszName)
			{

				return iLen;

			}

			auto iLenItem = p->get_item_size(true);

			iLen += iLenItem;

			p++;

		}


	}

	inline int property::find_index(const_char_pointer pszName) const
   {
      auto p = this;
      int iLen = 0;
      int iIndex = 0;

      while (true)
      {

         if (::is_null(p->m_pszName))
         {

            return iIndex;
         }

         ::string strName(p->m_pszName);

         strName.begins_eat("sampler:");

         if (strName == pszName)
         {

            return iIndex;
         }

         auto iLenItem = p->get_item_size(true);

         iLen += iLenItem;

         p++;
         iIndex++;
      }

      
   }

   class property_data
   {
   public:


      memsize m_iOffset;
      memsize m_iItemSize;


   };


	class properties_reference;

	class properties_interface
	{
	public:
		
		::block     m_blockWithSamplers;
      ::block     m_blockWithoutSamplers;
		
		const ::gpu::property* m_pproperties;

      ::array_base<property_data> m_propertydataa;

		properties_interface()
		{

			m_pproperties = nullptr;

		}

		properties_interface(const ::gpu::properties_interface& properties) :
			m_pproperties(properties.m_pproperties)
		{
			m_blockWithSamplers = properties.m_blockWithSamplers;
         m_blockWithoutSamplers = properties.m_blockWithoutSamplers;

		}
		properties_interface(const ::gpu::property* pproperties)
		{
			set(pproperties);
		}
      properties_interface(const ::gpu::property *pproperties, const ::block &blockWithSamplers, const ::block &blockWithoutSamplers) :			m_blockWithSamplers(blockWithSamplers), m_blockWithoutSamplers(blockWithoutSamplers)
		{
			set(pproperties);
		}
		void set(const ::gpu::property* pproperties)
		{
			m_pproperties = pproperties;

		}
		memsize size(bool bWithSamplers) const { return bWithSamplers? m_blockWithSamplers.size():m_blockWithoutSamplers.size(); }
		::collection::count count() const { return ::is_null(m_pproperties) ? 0:m_pproperties->count(); }
      unsigned char *data(bool bWithSamplers) const { return bWithSamplers ? m_blockWithSamplers.data():m_blockWithoutSamplers.data(); }
		void* find(const_char_pointer pszName, bool bWithSamplers = true) {
         auto iIndex = m_pproperties->find_index(pszName);
         if (iIndex < 0)
         {
            throw ::exception(error_not_found);

         }
         if (iIndex >= m_propertydataa.count())
         {
            throw ::exception(error_wrong_state);

         }
         auto iOffset = m_propertydataa[iIndex].m_iOffset;
         if (bWithSamplers)
            return m_blockWithSamplers.data() + iOffset;
         else
            return m_blockWithoutSamplers.data() + iOffset;
		}
      memsize find_size(const_char_pointer pszName)
      {
         auto iIndex = m_pproperties->find_index(pszName);
         if (iIndex < 0)
         {
            throw ::exception(error_not_found);
         }
         if (iIndex >= m_propertydataa.count())
         {
            throw ::exception(error_wrong_state);
         }
         auto iSize = m_propertydataa[iIndex].m_iItemSize;
         return iSize;
      }
      bool contains(const_char_pointer pszName) const
      {
         if (::is_null(m_pproperties))
            return false;
         return ::is_set(m_pproperties->find(pszName));
      }
      template<typename T>
		T& as(const_char_pointer pszName) { return *(T*)find(pszName); }
		float& as_float(const_char_pointer pszName) { return as<float>(pszName); }
		int& as_int(const_char_pointer pszName) { return as<int>(pszName); }
		floating_sequence2& seq2(const_char_pointer pszName) { return as<floating_sequence2>(pszName); }
		floating_sequence3& seq3(const_char_pointer pszName) { return as<floating_sequence3>(pszName); }
		floating_sequence4& seq4(const_char_pointer pszName) { return as<floating_sequence4>(pszName); }
		floating_matrix2& mat2(const_char_pointer pszName) { return as<floating_matrix2>(pszName); }
		floating_matrix3& mat3(const_char_pointer pszName) { return as<floating_matrix3>(pszName); }
		floating_matrix4& mat4(const_char_pointer pszName) { return as<floating_matrix4>(pszName); }
		operator const ::gpu::property* ()
		{
			return m_pproperties;

		}

		properties_interface array_item(const_char_pointer pszArrayName, int iItem)
		{

			auto pproperty = m_pproperties->find(pszArrayName);

			if (::is_null(pproperty))
			{

				throw ::exception(error_not_found);

			}

			return { pproperty->m_pproperties,
				m_blockWithSamplers(pproperty->m_iCachedOffset, pproperty->m_iCachedSizeWithSamplers),
                 m_blockWithoutSamplers(pproperty->m_iCachedOffset, pproperty->m_iCachedSizeWithoutSamplers)};

		}

		properties_reference operator[](const_char_pointer pszName);
		properties_reference operator[](::collection::index i);

	};

	class CLASS_DECL_BRED properties_reference :
		public properties_interface
	{
	public:
		
		
		properties_reference(const property *pproperty, const ::block &blockWithSamplers,
                           const ::block &blockWithoutSamplers)
		{
			m_blockWithSamplers = blockWithSamplers;
         m_blockWithoutSamplers = blockWithoutSamplers;
         
			m_pproperties = pproperty;

			//m_propertya.add(*pproperty);
			//m_propertya.add({ nullptr, ::gpu::e_type_none });
			//m_pproperties = m_propertya.data();

		}

		void _set_matrix4(const ::floating_matrix4& matrix4);
		void _set_sequence4(const ::floating_sequence4& sequence4);
      void _set_sequence3(const ::floating_sequence3 & sequence3);
		void _set_int(const int& i);
		
		template < typename TYPE >
		properties_reference& operator=(const TYPE& matrix4) requires
			(::std::is_same_v<TYPE, ::floating_matrix4 >)
		{

			if (m_pproperties->m_etype != ::gpu::e_type_mat4)
			{

				throw ::exception(error_bad_data_format);

			}
			_set_matrix4(matrix4);
			
			return *this;

		}
		template < typename TYPE >
		properties_reference& operator=(const TYPE& sequence4)requires
		(::std::is_same_v<TYPE, ::floating_sequence4 >)
		{
			if (m_pproperties->m_etype != ::gpu::e_type_seq4)
			{

				throw ::exception(error_bad_data_format);

			}

			_set_sequence4(sequence4);

			return *this;

		}
      template<typename TYPE>
      properties_reference &operator=(const TYPE &sequence3)
         requires(::std::is_same_v<TYPE, ::floating_sequence3>)
      {
         if (m_pproperties->m_etype != ::gpu::e_type_seq3)
         {

            throw ::exception(error_bad_data_format);
         }

         _set_sequence3(sequence3);

         return *this;
      }


		template < typename TYPE >
		properties_reference& operator=(const TYPE& i)requires
			(::std::is_same_v<TYPE, int >)
		{
			if (m_pproperties->m_etype != ::gpu::e_type_int)
			{

				throw ::exception(error_bad_data_format);

			}

			_set_int(i);

			return *this;

		}
		

		
	};

	class properties :
		public properties_interface,
      virtual public memory_composite
	{
	public:


		properties()
		{

		}
		properties(const ::gpu::property* pproperties)
		{
			set_properties(pproperties);
		}

		void set_properties(const ::gpu::property* pproperties)
		{
			properties_interface::set(pproperties);

		   auto & memory = this->memory();
			memory.set_size(m_pproperties->get_size(true));
			m_blockWithSamplers.begin() = memory.data();
         m_blockWithSamplers.end() = memory.end();
         m_blockWithoutSamplers.begin() = memory.data();
         m_blockWithoutSamplers.end() = m_blockWithoutSamplers.begin() + m_pproperties->get_size(false);

		}



      ::block block_with_samplers() { return m_blockWithSamplers; }
      ::block block_without_samplers() { return m_blockWithoutSamplers; }
		
		template < typename TYPE >
		void set()
		{

			this->set_properties(::gpu_properties<TYPE>());

		}


	};


	inline property::property(const_char_pointer pszName,  const property * pproperty, int iSize):
		m_pszName(pszName), 
		m_etype(::gpu::e_type_array),
		m_pproperties(pproperty),
		m_iArraySize(iSize)
	{


	}
	
   
   inline properties_reference properties_interface::operator[](const_char_pointer pszName)
	{


		auto pproperty = m_pproperties->find(pszName);

      if (m_propertydataa.has_element())
      {
         return {pproperty,
            {find(pszName, true), find_size(pszName)},
            {find(pszName, false), find_size(pszName)}
         };
      }
      else
      {


            return {pproperty,

                 m_blockWithSamplers(pproperty->m_iCachedOffset, pproperty->m_iCachedSizeWithSamplers),
                 m_blockWithoutSamplers(pproperty->m_iCachedOffset, pproperty->m_iCachedSizeWithoutSamplers)};


      }
	}

	inline properties_reference properties_interface::operator[](::collection::index i)
	{

		if (m_pproperties->m_etype != ::gpu::e_type_array)
		{

			throw ::exception(error_wrong_state);

		}
		if (i < 0 || i >= m_pproperties->m_iArraySize)
		{

			throw ::exception(error_index_out_of_bounds);

		}

		auto pproperty = m_pproperties;

		int iSizeWithSamplers = pproperty->m_pproperties->get_size(true);
      int iOffset = iSizeWithSamplers * (int)i;

		return { pproperty->m_pproperties, 
         m_blockWithSamplers(iOffset, iSizeWithSamplers),
              m_blockWithoutSamplers(iOffset, iSizeWithSamplers)};


	}


} // namespace gpu


#define DECLARE_GPU_PROPERTIES(rooting, type)                                                                                     \
template<>                                                 \
rooting ::gpu::property *gpu_properties<type>();


#define BEGIN_GPU_PROPERTIES(type) \
	template < >	\
   CLASS_DECL_EXPORT ::gpu::property * gpu_properties<type>() \
   { \
      static ::gpu::property s_pproperty[]= {

#define GPU_PROPERTY(...) {__VA_ARGS__},

#define END_GPU_PROPERTIES() \
   nullptr \
   }; \
   return s_pproperty;  \
} 
 




DECLARE_GPU_PROPERTIES(CLASS_DECL_BRED, ::floating_sequence3)





