#include "framework.h"


::critical_section source::g_cs;
::isomap < source_pointer, source_pointer > source::g_sourcekeyset;
bool source::g_bDestroyAll = false;


source::source()
{

}


source::~source()
{


}


::manager_pointer source::fork_update(const ::id& id)
{

   auto pupdate = ＿＿new(::manager(id));

   return pupdate;

}


manager * source::update(const ::id& id)
{

   sync_lock sl(mutex());

   if (!m_pmap)
   {

      m_pmap = ＿＿new(::id_map < ＿＿pointer(::manager) >);

   }

   auto & pupdate = m_pmap->operator[](id);

   if (!pupdate)
   {

      pupdate = ＿＿new(::manager(this, id));

      pupdate->defer_create_mutex();

      pupdate->m_iMillisSleep = os_get_system_update_poll_time(id);

   }

   if (is_null(&pupdate))
   {

      output_debug_string("teste");

   }

   return pupdate;

}

void source::notify_update(const ::id& id)
{

   update(id)->notify();

}


void source::notify_update(const ::id& id, const ::action_context& actioncontext)
{

   update(id)->notify(actioncontext);

}


void source::apply_update(const ::id& id)
{

   update(id)->process();

}


void source::apply_update(const ::id& id, const ::action_context& actioncontext)
{

   update(id)->process(actioncontext);

}


void source::apply_update(const ::id& id, const ::var& var)
{

   update(id)->process(var);

}


void source::set_modified(const ::id& id)
{

   auto pupdate = update(id);

   if (::is_set(pupdate))
   {

      pupdate->set_modified();

   }

}


void source::add_update(const ::id& id, ::matter * pmatter, bool bForkWhenNotify)
{

   auto pupdate = update(id);

   if (::is_set(pupdate))
   {

      pupdate->add(pmatter, bForkWhenNotify);

   }

}


void source::remove_update(const ::id& id, ::matter* pmatter)
{

   update(id)->remove(pmatter);

}


action_pointer source::fork_action(const ::id& id, ::matter* pmatter)
{

   auto paction = ＿＿new(::subject(id, pmatter));

   return paction;

}


action_pointer source::action(const ::id& id, ::matter* pmatter)
{

   auto pupdate = update(id);

   auto paction = ::new_action(pupdate, pmatter);

   return paction;

}


void source::finalize()
{

   context_object::finalize();

   m_pmap.release();

}


void source::remove(::matter* pmatter)
{

   sync_lock sl(mutex());

   for (auto& pupdate : m_pmap->values())
   {

      pupdate->remove(pmatter);

   }

}


void source::＿＿remove(::matter* pmatter)
{

   cslock sl(&g_cs);

   for (auto& psource : g_sourcekeyset.values())
   {

      psource->remove(pmatter);

   }

}


void source::post_destroy_all()
{

   g_bDestroyAll = true;

}



