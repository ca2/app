////////////////////////////////////////////////////////////////////////////
// other global state
class push_routing_frame
{
protected:
   frame_window* pOldRoutingFrame;
   _WINDOWS_DEFINITION_THREAD_STATE* pThreadState;
   push_routing_frame* pOldPushRoutingFrame;

public:
   explicit push_routing_frame(frame_window* pNewRoutingFrame)
   {
      pThreadState = ::windows_definition::GetThreadState();
      pOldPushRoutingFrame = pThreadState->m_pPushRoutingFrame;
      pOldRoutingFrame = pThreadState->m_pRoutingFrame;
      pThreadState->m_pRoutingFrame = pNewRoutingFrame;
      pThreadState->m_pPushRoutingFrame = this;
   }
   ~push_routing_frame()
   {
      if (pThreadState != nullptr)
      {
         ASSERT( pThreadState->m_pPushRoutingFrame == this );
         pThreadState->m_pRoutingFrame = pOldRoutingFrame;
         pThreadState->m_pPushRoutingFrame = pOldPushRoutingFrame;
      }
   }
   void pop()
   {
      ENSURE( pThreadState != nullptr );
      ASSERT( pThreadState->m_pPushRoutingFrame == this );
      pThreadState->m_pRoutingFrame = pOldRoutingFrame;
      pThreadState->m_pPushRoutingFrame = pOldPushRoutingFrame;
      pThreadState = nullptr;
   }
};
