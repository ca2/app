#pragma once


class CLASS_DECL_APEX object_meta
{
public:


   string                              m_strTopicText;
   atom_map < ::procedure_array >   m_mapRoutine;
   //atom_map < future_array >   m_mapProcess;
   //pointer_array < ::task >           m_taska;


   object_meta() { }
   ~object_meta();


   inline void set_topic_text(const ::string & strTopicText) { m_strTopicText = strTopicText; }

   inline const char * topic_text() const { return m_strTopicText; }

   //void destroy(::object* pReferer);


   //::index task_add(::object * pReferer, ::task* ptask);
   //void task_erase(::object* pReferer, ::task* ptask);
   //void task_erase_all(::object* pReferer);


};



