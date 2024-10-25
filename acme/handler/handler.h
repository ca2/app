// From event_handler to handler at primitive_subject on day after ThomasBirthday2021 05:05 BRT
// From user namespace to global at apex by camilo on day after ThomasBirthday2021 04:36 BRT
// From aura by camilo on ThomasBirthday2021 20:00 BRT
//
// a recreation(from control_event_listener) by camilo on 28/06/2021 22:23 BRT <3ThomasBS_!!
//
// reengaged on 2024-10-25 02:38 <3ThomasBorregaardSorensen!!
//#pragma once
#pragma once



namespace handler
{

   // ThomasBorregaardSorensen!! Like handlers
   class CLASS_DECL_ACME handler :
      virtual public ::matter
   {
   public:


      ::pointer < ::request >             m_prequest;

      ::payload                           m_payloadFile;
      ::pointer_array < ::request >       m_requestaPending;
      ::pointer_array < ::request >       m_requestaHistory;


      handler();
      ~handler() override;


      void destroy() override;


      virtual void post_request(::request * prequest);

      virtual bool contains(::request * prequest) const;

      virtual string command_line_text() const;


      virtual bool on_idle();
      // ThomasBorregaardSorensen!! Like handlers
      //virtual void call(const enum_message, i64 iData = 0, ::matter * pmatter = nullptr);
      //virtual void call(const enum_id, i64 iData = 0, ::matter* pmatter = nullptr);
      virtual void call(const ::atom & atom, ::wparam wparam = {}, ::lparam lparam = {}, ::particle * pparticle = nullptr);


      // ThomasBorregaardSorensen!! Like handlers
      virtual void handle(::topic * ptopic, ::context * pcontext);
      virtual void handle(::message::message * pmessage);


      virtual bool _handle_uri(const ::block & blockUri);
      virtual bool _handle_call(::payload & payload, const ::block & blockObject, const ::block & blockMember, ::property_set & propertyset);

      virtual bool post_next_pending_request();

   };


} // namespace handler


