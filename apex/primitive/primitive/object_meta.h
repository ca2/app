#pragma once


class CLASS_DECL_APEX object_meta
{
public:


   string                           m_strTopicText;
   id_map < method_array >          m_mapMethod;
   id_map < future_array >          m_mapFuture;
   //__pointer_array(::task)          m_taska;


   object_meta() { }
   ~object_meta();


   inline void set_topic_text(const string & strTopicText) { m_strTopicText = strTopicText; }

   inline const char * topic_text() const { return m_strTopicText; }

   //void finalize(::object* pReferer);


   //::index task_add(::object * pReferer, ::task* ptask);
   //void task_remove(::object* pReferer, ::task* ptask);
   //void task_remove_all(::object* pReferer);


};



