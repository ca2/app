// Created by camilo on 2025-05-19 05:52 <3ThomasBorregaardSorensen!!
#pragma once


#include "bred/gpu/_.h"
#include <glm/glm.hpp>

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

		const char* m_pszName = nullptr;
		::gpu::enum_type		m_etype =::gpu::e_type_none;
		const property* m_pproperties = nullptr;
		int m_iArraySize = 0;
		int m_iCachedSize = -1;
		int m_iCachedOffset = -1;

		property() {}
		property(const char* pszName, ::gpu::enum_type etype) :
			m_pszName(pszName), m_etype(etype)
		{


		}

		property(const char* pszName, const property * pproperty, int iSize = 1);
		property(const property& property):
			m_pszName(property.m_pszName),
			m_etype(property.m_etype),
			m_pproperties(property.m_pproperties),
			m_iArraySize(property.m_iArraySize),
			m_iCachedSize(property.m_iCachedSize),
			m_iCachedOffset(property.m_iCachedOffset)
		{
		}


		inline const property* find(const char* pszName) const;

		inline int get_size() const;

		inline ::collection::count count() const;

		inline int get_offset(const char* pszName) const;

		inline int get_item_size() const
		{
			if (m_etype == e_type_properties_array)
			{

				return m_pproperties->get_size() * m_iArraySize;
			}
			else
			{
				return ::gpu::get_type_size(m_etype);
			}
		}

	};


	inline const property* property::find(const char* pszName) const
	{

		auto p = this;

		int iLen = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				return nullptr;

			}

			auto iLenItem = p->get_item_size();

			if (p->m_iCachedOffset < 0)
			{

				((property*)p)->m_iCachedOffset = iLen;

			}

			if (p->m_iCachedSize < 0)
			{

				((property*)p)->m_iCachedSize = iLenItem;

			}

			if (!strcmp(p->m_pszName, pszName))
			{

				return p;

			}

			iLen += iLenItem;

			p++;

		}

	}


	inline int property::get_size() const
	{
		auto p = this;
		int iLen = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				return iLen;

			}

			auto iLenItem = p->get_item_size();

			iLen += iLenItem;

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


	inline int property::get_offset(const char* pszName) const
	{
		auto p = this;
		int iLen = 0;

		while (true)
		{

			if (::is_null(p->m_pszName))
			{

				throw ::exception(error_not_found);

			}

			if (!::strcmp(p->m_pszName, pszName))
			{

				return iLen;

			}

			auto iLenItem = p->get_item_size();

			iLen += iLenItem;

			p++;

		}


	}


	class properties_reference;

	class properties_interface
	{
	public:
		
		::block    m_block;
		
		const ::gpu::property* m_pproperties;

		properties_interface()
		{

			m_pproperties = nullptr;

		}

		properties_interface(const ::gpu::properties_interface& properties) :
			m_pproperties(properties.m_pproperties)
		{
			m_block = properties.m_block;

		}
		properties_interface(const ::gpu::property* pproperties)
		{
			set(pproperties);
		}
		properties_interface(const ::gpu::property* pproperties, const ::block & block):
			m_block(block)
		{
			set(pproperties);
		}
		void set(const ::gpu::property* pproperties)
		{
			m_pproperties = pproperties;

		}
		memsize size() const { return m_block.size(); }
		::collection::count count() const { return ::is_null(m_pproperties) ? 0:m_pproperties->count(); }
		unsigned char* data() const { return m_block.data(); }
		void* plookup(const char* pszName) {
			auto iOffset = m_pproperties->get_offset(pszName);
			return m_block.data() + iOffset;
		}
		template < typename T>
		T& as(const char* pszName) { return *(T*)plookup(pszName); }
		float& as_float(const char* pszName) { return as<float>(pszName); }
		int& as_int(const char* pszName) { return as<int>(pszName); }
		glm::vec2& seq2(const char* pszName) { return as<glm::vec2>(pszName); }
		glm::vec3& seq3(const char* pszName) { return as<glm::vec3>(pszName); }
		glm::vec4& seq4(const char* pszName) { return as<glm::vec4>(pszName); }
		glm::mat2& mat2(const char* pszName) { return as<glm::mat2>(pszName); }
		glm::mat3& mat3(const char* pszName) { return as<glm::mat3>(pszName); }
		glm::mat4& mat4(const char* pszName) { return as<glm::mat4>(pszName); }
		operator const ::gpu::property* ()
		{
			return m_pproperties;

		}

		properties_interface array_item(const char* pszArrayName, int iItem)
		{

			auto pproperty = m_pproperties->find(pszArrayName);

			if (::is_null(pproperty))
			{

				throw ::exception(error_not_found);

			}

			return { pproperty->m_pproperties,
				m_block(pproperty->m_iCachedOffset,
					pproperty->m_iCachedSize) };

		}

		properties_reference operator[](const char* pszName);
		properties_reference operator[](::collection::index i);

	};

	class CLASS_DECL_BRED properties_reference :
		public properties_interface
	{
	public:
		
		
		properties_reference(const property* pproperty, const ::block& block)
		{
			m_block = block;
			m_pproperties = pproperty;

			//m_propertya.add(*pproperty);
			//m_propertya.add({ nullptr, ::gpu::e_type_none });
			//m_pproperties = m_propertya.data();

		}

		void _set_mat4(const ::glm::mat4& mat4);
		void _set_vec4(const ::glm::vec4& vec4);
		void _set_int(const int& i);
		
		template < typename TYPE >
		properties_reference& operator=(const TYPE& mat4) requires
			(::std::is_same_v<TYPE, ::glm::mat4 >)
		{

			if (m_pproperties->m_etype != ::gpu::e_type_mat4)
			{

				throw ::exception(error_bad_data_format);

			}
			_set_mat4(mat4);
			

			return *this;

		}
		template < typename TYPE >
		properties_reference& operator=(const TYPE& vec4)requires
		(::std::is_same_v<TYPE, ::glm::vec4 >)
		{
			if (m_pproperties->m_etype != ::gpu::e_type_seq4)
			{

				throw ::exception(error_bad_data_format);

			}

			_set_vec4(vec4);

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
		public properties_interface
	{
	public:
		::memory m_memory;


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
			m_memory.set_size(m_pproperties->get_size());
			m_block.begin() = m_memory.data();
			m_block.end() = m_memory.end();

		}

		
		template < typename TYPE >
		void set()
		{

			this->set_properties(::gpu_properties<TYPE>());

		}


	};


	inline property::property(const char* pszName,  const property * pproperty, int iSize):
		m_pszName(pszName), 
		m_etype(::gpu::e_type_properties_array),
		m_pproperties(pproperty),
		m_iArraySize(iSize)
	{


	}
	inline properties_reference properties_interface::operator[](const char* pszName)
	{


		auto pproperty = m_pproperties->find(pszName);

		return { pproperty,
			m_block(pproperty->m_iCachedOffset,
				pproperty->m_iCachedSize) };
	}

	inline properties_reference properties_interface::operator[](::collection::index i)
	{

		if (m_pproperties->m_etype != ::gpu::e_type_properties_array)
		{

			throw ::exception(error_wrong_state);

		}
		if (i < 0 || i >= m_pproperties->m_iArraySize)
		{

			throw ::exception(error_index_out_of_bounds);

		}

		auto pproperty = m_pproperties;

		int iSize = pproperty->m_pproperties->get_size();
		int iOffset = iSize * (int) i;

		return { pproperty->m_pproperties, m_block(iOffset, iSize) };


	}


} // namespace gpu




#define BEGIN_GPU_PROPERTIES(type) \
	template < >	\
   inline ::gpu::property * gpu_properties<type>() \
   { \
      static ::gpu::property s_pproperty[]= {

#define GPU_PROPERTY(...) {__VA_ARGS__},

#define END_GPU_PROPERTIES() \
   {  } \
   }; \
   return { s_pproperty };  \
} 
 




