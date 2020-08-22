#pragma once


template < class TYPE, class ARG_TYPE, class T >
class map_to_smart_pointer :
   public map < TYPE, ARG_TYPE, pointer < T >, const pointer < T > & >
{
public:


   map_to_smart_pointer(::object * pobject = nullptr) :
      ::object(pobject),
      map < TYPE, ARG_TYPE, pointer < T >, const pointer < T > & > (pobject)
   {
   }



   virtual ~map_to_smart_pointer()
   {
   }


} ;

template < class T >
class string_to_smart_pointer :
   public string_map < pointer < T >, const pointer < T > & >
{
public:


   string_to_smart_pointer()
   {

   }


   virtual ~string_to_smart_pointer()
   {
   }


} ;

template < class T >
class int_to_smart_pointer:
   public int_ptr_map < pointer < T >,const pointer < T > & >
{
public:


   int_to_smart_pointer(::object * pobject = nullptr, ::count nBlockSize = 10):
      ::object(pobject),
      int_ptr_map < pointer < T >,const pointer < T > & >(pobject,nBlockSize)
   {

   }


   virtual ~int_to_smart_pointer()
   {
   }


} ;


#define mapsp(TYPE, ARG_TYPE, SPTYPE) map_to_smart_pointer < TYPE, ARG_TYPE, SPTYPE >
#define strsp(SPTYPE) string_to_smart_pointer < SPTYPE >
#define isp(SPTYPE) int_to_smart_pointer < SPTYPE >
#define idsp(SPTYPE) mapsp(id, id, SPTYPE)






