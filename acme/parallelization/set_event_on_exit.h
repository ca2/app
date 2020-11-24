//
//  multithreading_set_event_on_exit.h
//  acme
//
//
//


class CLASS_DECL_ACME set_event_on_exit
{
public:
   
   
   event * m_pevent;
   
   
   set_event_on_exit(event & ev) { m_pevent = &ev; }
   ~set_event_on_exit() { if(m_pevent != nullptr) m_pevent->set_event(); }
   
   
};



template < typename PRED >
class  λon_exit
{
public:
   
   
   PRED m_pred;
   
   
   λon_exit(PRED pred) : m_pred(pred) { }
   ~λon_exit() { m_pred(); }
   
   
};



