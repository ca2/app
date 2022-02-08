#pragma once


namespace async
{

   struct callback
   {
   };




   struct CLASS_DECL_AURA token
   {
      token *     m_ptoken;
      uptr    m_uiToken;
      token()
      {
         m_ptoken = nullptr;
         m_uiToken = 0;
      }
      token(const token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
      }
      void set_token(uptr uiTokenValue)
      {
         if(m_ptoken != nullptr)
         {
            m_ptoken->set_token(uiTokenValue);
         }
         else
         {
            m_uiToken = uiTokenValue;
         }
      }

      uptr get_token()
      {
         if(m_ptoken != nullptr)
         {
            return m_ptoken->get_token();
         }
         else
         {
            return m_uiToken;
         }
      }
      token & operator = (const token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
         return *this;
      }

      static token none()
      {
         token t;
         t.m_ptoken = (token *) -1;
         t.m_uiToken = (uptr) -1;
         return t;
      }

      bool is_null()
      {
         return m_ptoken == (token *) -1;
      }

      bool is_set()
      {
         return !is_null();
      }

   };

   struct CLASS_DECL_AURA registration_token : public token
   {

   };


   struct CLASS_DECL_AURA cancellation_token : public token
   {
      callback *   m_pcallback;
      void(callback ::*m_pfnCancel)();

      cancellation_token()
      {
         m_pcallback = nullptr;
         m_pfnCancel = nullptr;
      }

      cancellation_token(const token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
      }

      cancellation_token(const cancellation_token & token)
      {
         m_ptoken = (struct token *) &token;
         m_uiToken = token.m_uiToken;
         m_pcallback = token.m_pcallback;
         m_pfnCancel = token.m_pfnCancel;
      }

      void cancel()
      {
         set_token(1);
      }

      cancellation_token & operator = (const cancellation_token & token)
      {
         m_ptoken = (struct cancellation_token *) &token;
         m_uiToken = token.m_uiToken;
         m_pcallback = token.m_pcallback;
         m_pfnCancel = token.m_pfnCancel;
         return *this;
      }


      template < class T >
      registration_token register_callback(T * point, void(T::*pfnCancel)())
      {
         m_pcallback = (callback *) point;
         m_pfnCancel = (void(callback ::*)()) pfnCancel;
         registration_token t;
         t.m_ptoken = m_ptoken;
         t.m_uiToken = m_uiToken;
         return t;
      }

      void deregister_callback(registration_token t)
      {
         if(t.m_ptoken == this)
         {
            m_pcallback = nullptr;
            m_pfnCancel = nullptr;
         }
      }

   };


   enum enum_state
   {

      e_state_error,
      e_state_run,
      e_state_cancel,
      e_state_complete

   };


   template < class T >
   class task_completion_event;


   template < class T >
   class CLASS_DECL_AURA task :
      public ::thread
   {
   public:


      class completion_callback;


      typedef void (completion_callback :: *LPFN_COMPLETION_CALLBACK)(task < T > & task, const ::e_status & estatus);


      T *                              m_presult;
      completion_callback *            m_pcompletioncallback;
      LPFN_COMPLETION_CALLBACK         m_pfncompletioncallback;
      enum_state                       m_estate;
      task_completion_event < T > *    m_pev;
      cancellation_token               m_cancellationtoken;


      inline task(task_completion_event < T > & ev, cancellation_token token)
      {

         m_presult                  = nullptr;
         m_pcompletioncallback      = nullptr;
         m_pfncompletioncallback    = nullptr;
         m_estatus                  = e_state_complete;
         m_pev                      = &ev;
         m_cancellationtoken        = token;
      }

      virtual ~task()
      {

         close();

      }


      template < class COMPLETION_CALLBACK >
      void set_completion_callback(COMPLETION_CALLBACK * pobject, void (COMPLETION_CALLBACK :: *pfncompletioncallback)(task < T > & task, const ::e_status & estatus))
      {

         m_pcompletioncallback      = static_cast < completion_callback * > (pobject);

         m_pfncompletioncallback    = static_cast < completion_callback * > (pfncompletioncallback);

      }



      virtual void cancel()
      {

         defer_call_completion(e_state_cancel);

      }

      void  defer_call_completion(const ::e_status & estatus)
      {

         m_estatus = estatus;

         if(m_pcompletioncallback == nullptr)
            return error_failed;

         if(m_pfncompletioncallback == nullptr)
            return error_failed;

         (m_pcompletioncallback->*m_pfncompletioncallback)(*this, m_estatus);

      }

      virtual void  run() override
      {

         return defer_call_completion(e_state_complete);

      }

      virtual T * wait(u32 dwMillis = U32_INFINITE_TIMEOUT)
      {

         ::get_task()->wait(::duration(dwMillis));

         return m_presult;

      }

      virtual void close()
      {

         if(m_presult != nullptr)
         {

            destroy_result();

            m_presult = nullptr;

         }

      }

      virtual void destroy_result()
      {

         if(m_presult == nullptr)
            return;

         delete m_presult;

      }

   };



   inline void cancel_current_task()
   {

      throw ::exception(::exception("cancel_current_task"));

   }


   template < typename T >
   class task_completion_event
   {
   public:
      event m_event;
      bool set(T r )
      {
         m_event.set_event();
         return true;
      }
   };

   template < >
   class task_completion_event < void >
   {
   public:
      event m_event;
      bool set()
      {
         m_event.set_event();
         return true;
      }
   };

   template < class T >
   inline task < T > * create_task(task_completion_event < T > & ev, cancellation_token token = token::none())
   {
      return new task < T > (ev, token);
   }

} // namespace async



template < typename T >
class waiter_for_async_task
{
public:

   T *                                                m_presult;
   async::task < T > *                                m_pobjectTask;


   waiter_for_async_task(::async::task < T > * pobjectTask)
   {

      m_pobjectTask = pobjectTask;

   }


   virtual ~waiter_for_async_task()
   {

   }


   T * wait(u32 dwMillis = U32_INFINITE_TIMEOUT)
   {

      m_presult = m_pobjectTask->wait(dwMillis);

      return m_presult;

   }

};




template < typename T >
inline  T * wait(::async::task < T > * pobjectTask, u32 dwMillis = U32_INFINITE_TIMEOUT)
{

   return waiter_for_async_task < T > (pobjectTask).wait(dwMillis);

}


