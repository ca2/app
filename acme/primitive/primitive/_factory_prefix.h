#pragma once


//
//
// Compose, Construct, Create, Refer and Add_Reference
//
// __create        // return __pointer(BASE_TYPE)          // _id atom   // _new TYPE
// __compose       // __composite(BASE_TYPE) &             // _id atom   // _new TYPE  // SOURCE &&
// __construct     // __pointer(BASE_TYPE) &               // _id atom   // _new TYPE  // SOURCE &&
// __refer         // __reference(BASE_TYPE) & SOURCE &&
// add_reference   // SOURCE &&
//
//
// Short explanation at ca2 framework action_context
//
// create : land memory_new independent matter (::pointer smart pointer)
// compose : ownership, acquisition, parenthood, containment, attach, be responsible for (::ownership member)
// construct : memory_new on place, build on place (::pointer smart pointer)
// refer : member-reserved reference (::composite)
// add_reference : just a reference (matter)
//
//

//template < typename BASE_TYPE >
//inline __pointer(BASE_TYPE) __create();
//
//template < typename BASE_TYPE >
//inline __pointer(BASE_TYPE) __id_create(const ::atom & atom);
//
//template < typename TYPE >
//inline __pointer(TYPE) __create_new();
//
//template < typename TYPE >
//inline __pointer(TYPE) __create_new(const TYPE & t);



//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const __pointer(SOURCE) & psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const ::atom & atom);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const ::type & type);
//
//// template < typename OBJECT, typename TYPE >
//// inline void __raw_compose_new(OBJECT && pobject, __composite(TYPE) & pownership);
//
//// template < typename OBJECT, typename TYPE >
//// inline void __compose_new(OBJECT && pobject, __composite(TYPE) & pownership);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const __pointer(SOURCE) & psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __defer_id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const ::atom & atom);
//
//// //template < typename OBJECT, typename BASE_TYPE >
//// //inline void __defer_id_compose(OBJECT && pobject, __composite(BASE_TYPE) & pownership, const ::type & type);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __defer_compose_new(OBJECT && pobject, __composite(BASE_TYPE) & pownership);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const __pointer(SOURCE) & psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __refer(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const __pointer(SOURCE) & psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_refer(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __id_compose(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const ::atom & atom);
//
////template < typename OBJECT, typename BASE_TYPE >
////inline void __id_compose(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite, const ::type & type);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __compose_new(OBJECT && pobject, __reference(BASE_TYPE) & pcomposite);
//
//template < typename BASE_TYPE >
//inline void __construct(__pointer(BASE_TYPE) & pusermessage);
//
//template < typename BASE_TYPE >
//inline void __defer_construct(__pointer(BASE_TYPE) & pusermessage);
//
//template < typename BASE_TYPE >
//inline void __id_construct(__pointer(BASE_TYPE) & pusermessage, const ::atom & atom);
//
//template < typename BASE_TYPE >
//inline void __defer_id_construct(__pointer(BASE_TYPE) & pusermessage, const ::atom & atom);
//
//template < typename TYPE >
//inline void __construct_new(__pointer(TYPE) & ptype);
//
//template < typename TYPE >
//inline void __defer_construct_new(__pointer(TYPE) & ptype);
//
//
//
