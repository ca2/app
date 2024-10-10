// Reinserted on 2022-11-12 02:45 <3ThomasBorregaardSorensen!!
#pragma once


#include "acme/prototype/collection/map.h"
#include "acme/prototype/collection/procedure_array.h"


class CLASS_DECL_ACME object_meta
{
public:


   string                              m_strTopicText;
   ::procedure_map                     m_mapRoutine;


   object_meta() { }
   ~object_meta();


   inline void set_topic_text(const ::string & strTopicText) { m_strTopicText = strTopicText; }

   inline const char * topic_text() const { return m_strTopicText.c_str(); }

   //void destroy(::object* pReferer);


   //::collection::index task_add(::object * pReferer, ::task* ptask);
   //void task_erase(::object* pReferer, ::task* ptask);
   //void task_erase_all(::object* pReferer);


};



