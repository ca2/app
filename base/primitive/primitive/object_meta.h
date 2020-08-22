#pragma once


class CLASS_DECL_AURA object_meta
{
public:


   string                           m_strTopicText;
   id_map < array < procedure > >   m_proceduremap;
   id_map < array < callback > >    m_callbackmap;


   object_meta() { }
   ~object_meta();


   inline void set_topic_text(const string & strTopicText) { m_strTopicText = strTopicText; }

   inline const char * topic_text() const { return m_strTopicText; }


};



