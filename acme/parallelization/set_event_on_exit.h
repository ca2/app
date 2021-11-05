//
//  multithreading_set_event_on_exit.h
//  acme
//
//
//


class CLASS_DECL_ACME set_event_on_exit
{
public:
   
   
   ::event * m_pevent;
   
   
   set_event_on_exit(::event & ev) { m_pevent = &ev; }
   ~set_event_on_exit() { if(m_pevent != nullptr) m_pevent->set_event(); }
   
   
};



template < typename PRED >
class predicate_on_exit
{
public:
   
   
   PRED m_predicate;
   
   
   predicate_on_exit(PRED pred) : m_predicate(pred) { }
   ~predicate_on_exit() { m_predicate(); }
   
   
};



