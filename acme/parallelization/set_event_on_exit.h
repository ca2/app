//
//  multitasking_set_event_on_exit.h
//  acme
//
//
//


class CLASS_DECL_ACME set_event_on_exit
{
public:
   
   
   ::event * m_phappening;
   
   
   set_event_on_exit(::event & ev) { m_phappening = &ev; }
   ~set_event_on_exit() { if(m_phappening != nullptr) m_phappening->set_happening(); }
   
   
};



template < typename PRED >
class predicate_on_exit
{
public:
   
   
   PRED m_predicate;
   
   
   predicate_on_exit(PRED pred) : m_predicate(pred) { }
   ~predicate_on_exit() { m_predicate(); }
   
   
};



