// Created By Camilo 2020-12-27 21:59 BRT <3ThomasBS, Mummi and bilbo!!
// twitch streams... twitch chatting...


namespace user
{


   class CLASS_DECL_AURA call_message_handler_task :
      virtual public matter
   {
   public:


      __pointer(interaction)        m_pinteraction;
      ::atom                        m_atom;
      wparam                        m_wparam;
      lparam                        m_lparam;


      call_message_handler_task(interaction * pinteraction, const ::atom & atom, wparam wparam, lparam lparam);
      ~call_message_handler_task() override;


      void run() override;


   };


} // namespace user





