#pragma once



//
//#define IMPLEMENT_CONST_STRING_PTR(stringype, value, name) const const_fixed_string<stringype, sizeof(value)/sizeof(stringype::char)> _init##name ={    {nullptr,      sizeof(value)/sizeof(stringype::char)-1,    sizeof(value)/sizeof(stringype::char)-1,    -1},         value   };   const stringype::char* const _value##name = _init##name.m_achData;   extern const stringype* const name = CONST_STRING_PTR(stringype, name);
//#define DECLARE_CONST_STRING_PTR(stringype, name) extern const stringype* const name;
//#define CONST_STRING_PTR(stringype, name) reinterpret_cast<const stringype* const>(&_value##name)

//
//template < typename TYPE_CHAR >
//class char_traits
//{
//public:
//
//};


