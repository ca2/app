#pragma once



class CLASS_DECL_ACME action :
   virtual public context_object
{
public:


   __pointer(::update)           m_pupdate;
   __pointer(::change)           m_pchange;
   __pointer(::matter)           m_pmatter;
   __pointer(::layered)          m_pobjectTopic;
   ::action_context              m_actioncontext;
   __pointer(::layered)          m_psender;
   __pointer(::layered)          m_puserinteraction; // user::interaction
   __pointer(::layered)          m_pcontrolevent; // user::control_event
   __pointer(::file::item)       m_pfileitem;
   ::var                         m_var;
   bool                          m_bRet;
   ::user::e_key                 m_ekey;


   action();
   action(const ::id & id, ::matter* pmatter = nullptr);
   action(const ::id& id, const ::action_context& actioncontext);
   action(::update * pupdate, const ::action_context& actioncontext);
   action(::update * pupdate, ::matter * pmatter = nullptr);
   action(::update * pupdate, ::change * pchange, ::matter* pmatter);
   virtual ~action();


   void action_common_construct();



   virtual ::estatus start_task();

   void reset_update(const ::id& id);


   virtual ::estatus on_task() override;


   operator action* () { return this; }
   operator const action* () const { return this; }

   inline bool is_up_to_date() const;

   virtual void set_up_to_date();

   inline ::id& id() { return m_id; }
   inline const ::id& id() const { return m_id; }


};



