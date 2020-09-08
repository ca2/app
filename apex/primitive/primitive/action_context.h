#pragma once




class CLASS_DECL_APEX action_context :
   virtual public context_object
{
public:


   esource                          m_esource;
   __pointer_array(::object)             m_objecta;


   action_context() { }
   action_context(e_source esource) : m_esource(esource) {  }
   action_context(const ::std::initializer_list < e_source > & esourcelist) : m_esource(esourcelist) {  }
   action_context(const esource & esource) : m_esource(esource) {  }
   action_context(const action_context & action_context) : m_esource(action_context.m_esource), m_objecta(action_context.m_objecta) {}
   ~action_context() {}


   inline void add(e_source esource) { m_esource.add(esource); }
   inline void add(const object * pobject) { m_objecta.add((::object *) pobject); }
   inline index find(const object * pobject) const { return m_objecta.find_first(pobject); }
   inline bool contains(const object * pobject) const { return m_objecta.contains(pobject); }

   inline bool is(e_source esource) const { return m_esource.has(esource); }
   inline bool is_user_source() const { return is(source_user); }
   inline bool has(e_source esource) const { return is(esource); }


   inline bool operator &(e_source esource) const { return has(esource); }

   inline ::action_context & operator |=(e_source esource) { add(esource); return *this; }
   inline ::action_context & operator +=(e_source esource) { add(esource); return *this; }


   action_context & operator = (const action_context & action_context)
   {
      if (this != &action_context)
      {
         m_esource = action_context.m_esource;
         m_objecta = action_context.m_objecta;
      }
      return *this;
   }

   IMPL_OPERATOR_PLUS(action_context);

};


//CLASS_DECL_APEX e_source translation_source(e_source esource, e_context econtextDst, e_context econtextSrc);

//namespace source
//{
//
//   static inline action_context add(e_source esourceAdd, e_source esource) { action_context ctx(esource); return ctx + esourceAdd; }
//   static inline action_context remove(e_source esource, e_source esourceRemove) { action_context ctx(esource); return ctx - esourceRemove; }
//   static inline action_context add_remove(e_source esource, e_source esourceAdd, e_source esourceRemove) { action_context ctx(esource); return ctx + esourceAdd - esourceRemove; }
//   static inline action_context sync(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_sync, esourceAdd, esourceRemove); }
//   static inline action_context sel(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_selection, esourceAdd, esourceRemove); }
//   static inline action_context user(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_user, esourceAdd, esourceRemove); }
//   static inline action_context database(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_database, esourceAdd, esourceRemove); }
//   static inline action_context system(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_system, esourceAdd, esourceRemove); }
//   static inline action_context data(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_data, esourceAdd, esourceRemove); }
//   static inline action_context op(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_remove(source_operator, esourceAdd, esourceRemove); }
//
//
//   static inline action_context add(action_context ctx, e_source esourceAdd) { return ctx + esourceAdd; }
//   static inline action_context remove(action_context ctx, e_source esourceRemove) { return ctx - esourceRemove; }
//   static inline action_context add_remove(action_context ctx, e_source esourceAdd, e_source esourceRemove) { return ctx + esourceAdd - esourceRemove; }
//   static inline action_context sync(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_sync, esourceRemove); }
//   static inline action_context sel(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_selection, esourceRemove); }
//   static inline action_context user(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_user, esourceRemove); }
//   static inline action_context database(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_database, esourceRemove); }
//   static inline action_context system(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_system, esourceRemove); }
//   static inline action_context data(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_data, esourceRemove); }
//   static inline action_context op(action_context ctx, e_source esourceRemove = source_none) { return add_remove(ctx, source_operator, esourceRemove); }
//
//
//
//   static inline action_context system_default(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return system(add(source_default, esourceAdd), esourceRemove); }
//   static inline action_context database_default(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return database(add(source_default, esourceAdd), esourceRemove); }
//   static inline action_context system_default(action_context ctx, e_source esourceRemove = source_none) { return system(add(ctx, source_default), esourceRemove); }
//   static inline action_context database_default(action_context ctx, e_source esourceRemove = source_none) { return database(add(ctx, source_default), esourceRemove); }
//
//}
//
//
