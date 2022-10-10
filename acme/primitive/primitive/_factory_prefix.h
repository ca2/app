#pragma once


//
//
// Compose, Construct, Create, Refer and Add_Reference
//
// __create        // return ::pointer<BASE_TYPE>         // _id atom   // _new TYPE
// __construct       // ::pointer<BASE_TYPE>&             // _id atom   // _new TYPE  // SOURCE &&
// __construct     // ::pointer<BASE_TYPE>&               // _id atom   // _new TYPE  // SOURCE &&
// __refer         // ::pointer<BASE_TYPE>& SOURCE &&
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
//inline ::pointer<BASE_TYPE>__create();
//
//template < typename BASE_TYPE >
//inline ::pointer<BASE_TYPE>__id_create(const ::atom & atom);
//
//template < typename TYPE >
//inline ::pointer<TYPE>__create_new();
//
//template < typename TYPE >
//inline ::pointer<TYPE>__create_new(const TYPE & t);



//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::pointer<SOURCE> psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::atom & atom);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::type & type);
//
//// template < typename OBJECT, typename TYPE >
//// inline void __raw_construct_new(OBJECT && pobject, ::pointer<TYPE>& pownership);
//
//// template < typename OBJECT, typename TYPE >
//// inline void __construct_new(OBJECT && pobject, ::pointer<TYPE>& pownership);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::pointer<SOURCE> psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __defer_id_compose(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::atom & atom);
//
//// //template < typename OBJECT, typename BASE_TYPE >
//// //inline void __defer_id_compose(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership, const ::type & type);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __defer_construct_new(OBJECT && pobject, ::pointer<BASE_TYPE>& pownership);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __refer(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const SOURCE * psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::pointer<SOURCE> psource);
//
//// template < typename OBJECT, typename BASE_TYPE, typename SOURCE >
//// inline void __defer_refer(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::member < SOURCE > & psource);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::atom & atom);
//
////template < typename OBJECT, typename BASE_TYPE >
////inline void __id_construct(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite, const ::type & type);
//
//// template < typename OBJECT, typename BASE_TYPE >
//// inline void __construct_new(OBJECT && pobject, ::pointer<BASE_TYPE>& pcomposite);
//
//template < typename BASE_TYPE >
//inline void __construct(::pointer<BASE_TYPE>& pusermessage);
//
//template < typename BASE_TYPE >
//inline void __defer_construct(::pointer<BASE_TYPE>& pusermessage);
//
//template < typename BASE_TYPE >
//inline void __id_construct(::pointer<BASE_TYPE>& pusermessage, const ::atom & atom);
//
//template < typename BASE_TYPE >
//inline void __defer_id_construct(::pointer<BASE_TYPE>& pusermessage, const ::atom & atom);
//
//template < typename TYPE >
//inline void __construct_new(::pointer<TYPE>& ptype);
//
//template < typename TYPE >
//inline void __defer_construct_new(::pointer<TYPE>& ptype);
//
//
//
