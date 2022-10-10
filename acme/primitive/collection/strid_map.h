#pragma once


//template < class VALUE, typename ARG_VALUE = typename argument_of < VALUE >::type  >
//using strid_map = id_map < VALUE,ARG_VALUE > ;

template < class T >
class CLASS_DECL_ACME string_to_pointer :
   public string_to_ptr
{
public:


   class pair
   {
   public:

      template < typename TYPE > inline pair(TYPE *);

      const string first;

      T * second;

   };


   bool lookup(string key, T * & rValue) const
   {
      return string_to_ptr::lookup(key, rValue);
   }
   const pair *plookup(string key) const
   {
      return reinterpret_cast < const string_to_pointer::pair * > (string_to_ptr::plookup(key));
   }
   pair *plookup(string key)
   {
      return reinterpret_cast < string_to_pointer::pair * > (string_to_ptr::plookup(key));
   }


   T ** pget(string key)
   {
      
      return (T**) string_to_ptr::pget(key);

   }


   T * get(string key)
   {

      T ** p = (T **) string_to_ptr::pget(key);

      if (p == nullptr)
      {

         return nullptr;

      }
      else
      {

         return (T *)*p;

      }

   }


   // Operations
   // lookup and add if not there
   T * & operator[](string key)
   {
      return (T * &) string_to_ptr::operator[](key);
   }


//   pair * get_start()
//   {
//      return (pair *) string_to_ptr::get_start();
//   }
//
//   pair * get_next(pair * & rPpair)
//   {
//      return (pair *) string_to_ptr::get_next((string_to_ptr::pair * &) rPpair);
//   }

};



#define stridsp(ca) strid_map < ::pointer<ca >>

