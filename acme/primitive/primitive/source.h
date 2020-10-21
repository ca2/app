#pragma once


class CLASS_DECL_ACME source :
   virtual public ::context_object
{
public:


   __pointer(::id_map < __pointer(::update) >)        m_pmap;

   static ::critical_section                          g_cs;
   // todo implement keyset 
   // a hashmap of just the key (but not a value)
   // like std::set?
   static isomap < source_pointer, source_pointer >   g_sourcekeyset;
   static bool                                        g_bDestroyAll;


   source();
   virtual ~source();


   static ::update_pointer fork_update(const ::id& id);

   ::update * update(const ::id& id);

   virtual void notify_update(const ::id& id);

   virtual void notify_update(const ::id& id, const ::action_context& actioncontext);

   virtual void apply_update(const ::id& id);

   virtual void apply_update(const ::id& id, const ::action_context & actioncontext);

   virtual void set_modified(const ::id& id);

   virtual void add_update(const ::id& id, ::matter * pmatter, bool bForkWhenNotify = false);

   virtual void remove_update(const ::id& id, ::matter* pmatter);

   static action_pointer fork_action(const ::id& id, ::matter * pmatter = nullptr);

   action_pointer action(const ::id& id, ::matter* pmatter = nullptr);


   virtual void finalize() override;

   //virtual void source_add(::matter* pmatter);
   //virtual void source_remove(::matter* pmatter);

   //void update_add(const ::id& id, ::matter* pmatter);
   //void update_remove(const ::id& id, ::matter* pmatter);


   void remove(::matter* pmatter);

   static void remove_from_any_source(::matter* pmatter);


   //static void __add(const ::id& id, ::matter* pmatter);

   //static void __remove(const ::id& id, ::matter* pmatter);

   static void __remove(::matter* pmatter);

   static void post_destroy_all();


};



inline ::action_pointer new_action(::update* pupdate) { return __new(::action(pupdate)); }


inline ::action_pointer new_action(::update* pupdate, ::matter * pmatter) { return __new(::action(pupdate, pmatter)); }



