#pragma once


//namespace promise
//{
//

//   template < typename RESULT >
//   process < RESULT > ::process()
//   {
//
//      m_pevent = nullptr;
//
//   }
//
//
//   template < typename RESULT >
//   void process < RESULT > ::set_result(const RESULT &  result, const void & estatus)
//   {
//
//      critical_section_lock lock(get_process_critical_section());
//
//      m_statusresult.m_estatus = estatus;
//
//      m_statusresult.m_result = result;
//
//   }
//
//
//   template < typename RESULT >
//   void process < RESULT > ::set_status(const void & estatus)
//   {
//
//      critical_section_lock lock(get_process_critical_section());
//
//      m_statusresult.m_estatus = estatus;
//
//   }
//
//
//   template < typename RESULT >
//   status < RESULT > & process < RESULT > ::get_result(const ::duration& duration)
//   {
//
//      critical_section_lock lock(get_process_critical_section());
//
//      if (m_statusresult.m_estatus == error_not_initialized)
//      {
//
//         m_pevent = new manual_reset_event();
//
//         if (!m_pevent->wait(duration).succeeded())
//         {
//
//            return error_timeout;
//
//         }
//
//      }
//
//      return m_statusresult;
//
//   }
//
//   //inline void operator()(const ::payload& payload) const;
//
//   //inline bool should_run_async() const;
//
//
//} // namespace promise
//


