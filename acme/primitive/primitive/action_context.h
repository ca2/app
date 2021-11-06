#pragma once




class CLASS_DECL_ACME action_context :
   virtual public matter
{
public:


   bool                                   m_bRet : 1;
   e_source                               m_esource;
   __pointer_array(::matter)        m_objecta;
   __pointer(::acme::message)       m_pmessage;



   action_context() { }
   action_context(::enum_source esource) : m_esource(esource) {  }
   action_context(const action_context & action_context) : m_esource(action_context.m_esource), m_objecta(action_context.m_objecta) {}
   virtual ~action_context() {}


   inline void add(e_source esource) { m_esource.add(esource); }
   inline void add(const matter * pobject) { m_objecta.add((::matter *) pobject); }
   inline index find(const matter * pobject) const { return m_objecta.find_first(pobject); }
   inline bool contains(const matter * pobject) const { return m_objecta.contains(pobject); }

   inline bool is(e_source esource) const { return m_esource.has(esource); }
   inline bool is_user_source() const { return is(e_source_user); }
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


//CLASS_DECL_ACME e_source translation_source(e_source esource, e_context econtextDst, e_context econtextSrc);

//namespace source
//{
//
//   static inline action_context add(e_source esourceAdd, e_source esource) { action_context ctx(esource); return ctx + esourceAdd; }
//   static inline action_context erase(e_source esource, e_source esourceRemove) { action_context ctx(esource); return ctx - esourceRemove; }
//   static inline action_context add_erase(e_source esource, e_source esourceAdd, e_source esourceRemove) { action_context ctx(esource); return ctx + esourceAdd - esourceRemove; }
//   static inline action_context synchronization_object(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(::e_source_sync, esourceAdd, esourceRemove); }
//   static inline action_context sel(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(source_selection, esourceAdd, esourceRemove); }
//   static inline action_context user(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(::e_source_user, esourceAdd, esourceRemove); }
//   static inline action_context database(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(::e_source_database, esourceAdd, esourceRemove); }
//   static inline action_context system(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(source_system, esourceAdd, esourceRemove); }
//   static inline action_context data(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(source_data, esourceAdd, esourceRemove); }
//   static inline action_context op(e_source esourceAdd = source_none, e_source esourceRemove = source_none) { return add_erase(source_operator, esourceAdd, esourceRemove); }
//
//
//   static inline action_context add(action_context ctx, e_source esourceAdd) { return ctx + esourceAdd; }
//   static inline action_context erase(action_context ctx, e_source esourceRemove) { return ctx - esourceRemove; }
//   static inline action_context add_erase(action_context ctx, e_source esourceAdd, e_source esourceRemove) { return ctx + esourceAdd - esourceRemove; }
//   static inline action_context synchronization_object(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, ::e_source_sync, esourceRemove); }
//   static inline action_context sel(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, source_selection, esourceRemove); }
//   static inline action_context user(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, ::e_source_user, esourceRemove); }
//   static inline action_context database(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, ::e_source_database, esourceRemove); }
//   static inline action_context system(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, source_system, esourceRemove); }
//   static inline action_context data(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, source_data, esourceRemove); }
//   static inline action_context op(action_context ctx, e_source esourceRemove = source_none) { return add_erase(ctx, source_operator, esourceRemove); }
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
