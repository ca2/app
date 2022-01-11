// Created By Camilo 2020-12-27 21:59 BRT <3ThomasBS, Mummi and bilbo!!
// twitch streams... twitch chatting...


namespace user
{


   class CLASS_DECL_AURA call_message_handler_task :
      virtual public matter
   {
   public:


      __pointer(interaction)        m_pinteraction;
      ::id                          m_id;
      wparam                        m_wparam;
      lparam                        m_lparam;


      call_message_handler_task(interaction * pinteraction, const ::id & id, wparam wparam, lparam lparam);
      virtual ~call_message_handler_task();


      virtual void run();


   };


} // namespace user





