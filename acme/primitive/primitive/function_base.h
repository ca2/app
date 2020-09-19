#pragma once


class CLASS_DECL_ACME function_base
{
public:


   ::id                       m_id;
   __pointer(generic)         m_pobjectTask;


   function_base(const ::id & id = ::id(), ::generic * p = nullptr) : m_id(id), m_pobjectTask(p) {}
   function_base(const ::function_base& functionbase) : m_id(functionbase.m_id), m_pobjectTask(functionbase.m_pobjectTask) { }


};



