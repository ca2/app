#pragma once


namespace aura
{


   class CLASS_DECL_AURA context_thread :
      virtual public ::thread,
      virtual public ::context
   {
   public:


      ::payload                                    m_varFile;
      __reference_array(::create)            m_createaPending;
      __reference_array(::create)            m_createaHistory;
      // current Topic Create
      __reference(::create)                  m_pcreate;
      /// accumulatted, reset, set, or clear as handler history passes
      //::payload                                    m_varFile;
      ///// accumulatted, reset, set, or clear as handler history passes
      //::payload                                    m_varQuery;


      context_thread();
      virtual ~context_thread();


      virtual void on_command_create(::create* pcreate);

      void add_create(::create* pcreate);

      create * get_create();

      bool contains(::create* pcreate) const;

      string command_line_text() const;

      virtual ::e_status destroy() override;


   };



} // namespace aura



