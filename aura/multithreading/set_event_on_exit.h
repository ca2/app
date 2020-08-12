//
//  multithreading_set_event_on_exit.h
//  aura
//
//
//


class CLASS_DECL_AURA set_event_on_exit
{
public:
   
   
   event * m_pevent;
   
   
   set_event_on_exit(event & ev) { m_pevent = &ev; }
   ~set_event_on_exit() { if(m_pevent != nullptr) m_pevent->set_event(); }
   
   
};



template < typename PRED >
class  pred_on_exit
{
public:
   
   
   PRED m_pred;
   
   
   pred_on_exit(PRED pred) : m_pred(pred) { }
   ~pred_on_exit() { m_pred(); }
   
   
};



