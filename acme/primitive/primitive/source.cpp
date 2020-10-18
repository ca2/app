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


//void source::apply(const ::__id& id)
//{
//
//   auto ptask = get_update(id, this));
//
//   apply(paction);
//
//}


::update_pointer source::fork_update(const ::id& id)
{

   auto pupdate = __new(::update(id));

   return pupdate;

}


update * source::update(const ::id& id)
{

   sync_lock sl(mutex());

   if (!m_pmap)
   {

      m_pmap = __new(::id_map < __pointer(::update) >);

   }

   auto & pupdate = m_pmap->operator[](id);

   if (!pupdate)
   {

      pupdate = __new(::update(this, id));

      pupdate->defer_create_mutex();

      pupdate->m_iMillisSleep = os_get_system_update_poll_time(id);

   }

   return pupdate;

}


void source::apply_update(const ::id& id)
{

   update(id)->apply();

}


void source::apply_update(const ::id& id, const ::action_context& actioncontext)
{

   update(id)->apply(actioncontext);

}


void source::set_modified(const ::id& id)
{

   update(id)->set_modified();

}


void source::add_update(const ::id& id, ::matter * pmatter, bool bForkWhenNotify)
{

   update(id)->add(pmatter, bForkWhenNotify);

}


void source::remove_update(const ::id& id, ::matter* pmatter)
{

   update(id)->remove(pmatter);

}


action_pointer source::fork_action(const ::id& id, ::matter* pmatter)
{

   auto paction = __new(::action(id, pmatter));

   return paction;

}



action_pointer source::action(const ::id& id, ::matter* pmatter)
{

   auto pupdate = update(id);

   auto paction = ::new_action(pupdate, pmatter);

   return pupdate;

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


void source::__remove(::matter* pmatter)
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



