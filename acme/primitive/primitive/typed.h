// From acme/include/_.h 2022-11-09 00:22 <3ThomasBorregaardSørensen!!
#pragma once


template<class TYPE>
inline auto& __typed(TYPE& t) { return t; }


template<class POINTER_TYPE>
inline auto& __typed(POINTER_TYPE* p) { return *p; }


template<class POINTER_POINTER_TYPE>
inline auto& __typed(POINTER_POINTER_TYPE** p) { return **p; }


template<class TYPE>
inline auto& __typed_defer_new(TYPE& t) { return t; }


template<class POINTER_TYPE>
inline auto& __typed_defer_new(POINTER_TYPE*& p)
{
   if (!p) { p = memory_new POINTER_TYPE; }
   return *p;
}


template<class POINTER_POINTER_TYPE>
inline auto& __typed_defer_new(POINTER_POINTER_TYPE** p)
{
   if (!*p) { *p = memory_new POINTER_POINTER_TYPE; }
   return **p;
}



template < typename TYPE >
inline void __dynamic_cast(TYPE*& ptarget, const TYPE* psource)
{

   ptarget = (TYPE*)psource;

}


template<typename TARGET, typename SOURCE>
inline void __dynamic_cast(TARGET*& ptarget, const SOURCE* psource)
{

   ptarget = dynamic_cast <TARGET*> ((SOURCE*)psource);

}



