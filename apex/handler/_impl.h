#pragma once


//namespace promise
//{
//

//   template < typename RESULT >
//   process < RESULT > ::process()
//   {
//
//      m_phappening = nullptr;
//
//   }
//
//
//   template < typename RESULT >
//   void process < RESULT > ::set_result(const RESULT &  result, const ::e_status & estatus)
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
//   void process < RESULT > ::set_status(const ::e_status & estatus)
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
//   status < RESULT > & process < RESULT > ::get_result(const class ::time& time)
//   {
//
//      critical_section_lock lock(get_process_critical_section());
//
//      if (m_statusresult.m_estatus == error_not_initialized)
//      {
//
//         m_phappening = ___new manual_reset_happening();
//
//         if (!m_phappening->wait(time).succeeded())
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


