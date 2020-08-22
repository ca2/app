#pragma once


namespace aura
{

   template < class AXIS >
   class gudo:
      virtual public AXIS,
      virtual public object
   {
   public:


      string         m_strKey;
      bool           m_bAutoGudoSet;


      gudo(::object * pobject,const string & strKey,bool bInitialGudoGet = true);
      virtual ~gudo();

      virtual void gudo_get();
      virtual void gudo_set();

   };

   template < class AXIS >
   gudo < AXIS > ::gudo(::object * pobject,const string & strKey,bool bInitialGudoGet):
      ::object(pobject)
   {

      m_strKey = strKey;

      m_bAutoGudoSet = true;

      if(bInitialGudoGet)
      {

         gudo_get();

      }

   }

   template < class AXIS >
   gudo < AXIS > ::~gudo()
   {

      if(m_bAutoGudoSet)
      {

         gudo_set();

      }

   }


} // namespace aura
