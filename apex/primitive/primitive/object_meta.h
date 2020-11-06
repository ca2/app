#pragma once


class CLASS_DECL_APEX object_meta
{
public:


   string                              m_strTopicText;
   id_map < procedure_array >          m_mapProcedure;
   id_map < futurevar_array >          m_mapFuturevar;
   //__pointer_array(::task)           m_taska;


   object_meta() { }
   ~object_meta();


   inline void set_topic_text(const string & strTopicText) { m_strTopicText = strTopicText; }

   inline const char * topic_text() const { return m_strTopicText; }

   //void finalize(::object* pReferer);


   //::index task_add(::object * pReferer, ::task* ptask);
   //void task_remove(::object* pReferer, ::task* ptask);
   //void task_remove_all(::object* pReferer);


};



