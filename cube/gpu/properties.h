// Created by camilo on 2025-05-19 05:52 <3ThomasBorregaardSorensen!!
#pragma once


#include "cube/gpu/_.h"
#include <glm/glm.hpp>


namespace gpu
{


	class property
	{
	public:

		const char* m_pszName;
		::gpu::enum_type		m_etype;


		inline int get_size() const;

		inline int get_offset(const char* pszName) const;

	};


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

			auto iLenItem = ::gpu::get_type_size(p->m_etype);

			iLen += iLenItem;

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

			auto iLenItem = ::gpu::get_type_size(p->m_etype);

			iLen += iLenItem;

			p++;

		}


	}


	class properties
	{
	public:
		memory    m_memory;
		const ::gpu::property* m_pproperties;
		properties()
		{
			m_pproperties = nullptr;

		}
		properties(const ::gpu::properties & properties) :
			m_pproperties(properties.m_pproperties)
		{
			m_memory.copy(properties.m_memory);

		}
		properties(const ::gpu::property* pproperties)
		{
			set(pproperties);
		}
		void set(const ::gpu::property* pproperties)
		{
			m_pproperties = pproperties;
			m_memory.set_size(m_pproperties->get_size());

		}
		memsize size() const { return m_memory.size(); }
		unsigned char * data() const { return m_memory.data(); }
		void* plookup(const char* pszName){
			auto iOffset = m_pproperties->get_offset(pszName);
			return m_memory.data() + iOffset;
		}
		template < typename T>
		T& as(const char * pszName) { return *(T*)plookup(pszName); }
		float & as_float(const char* pszName){return as<float>(pszName);}
		int &as_int(const char* pszName)	{return as<int>(pszName);}
		glm::vec2& seq2(const char* pszName) { return as<glm::vec2>(pszName); }
		glm::vec3& seq3(const char* pszName) { return as<glm::vec3>(pszName); }
		glm::vec4 &seq4(const char* pszName){return as<glm::vec4>(pszName);}
		glm::mat2& mat2(const char* pszName) { return as<glm::mat2>(pszName); }
		glm::mat3& mat3(const char* pszName) { return as<glm::mat3>(pszName); }
		glm::mat4& mat4(const char* pszName){return as<glm::mat4>(pszName);}
		operator const ::gpu::property* ()
		{
			return m_pproperties;

		}
	};


} // namespace gpu



