#pragma once


class CLASS_DECL_APEX object_meta
{
public:


   string                           m_strTopicText;
   id_map < array < method > >      m_methodmap;
   id_map < array < future > >      m_futuremap;


   object_meta() { }
   ~object_meta();


   inline void set_topic_text(const string & strTopicText) { m_strTopicText = strTopicText; }

   inline const char * topic_text() const { return m_strTopicText; }


};



