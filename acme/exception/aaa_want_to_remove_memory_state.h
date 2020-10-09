#pragma once



//
//
//// Memory state for snapshots/leak detection
//struct CLASS_DECL_ACME memory_state :
//   public MEMORY_STATE
//{
//// Attributes
//   enum blockUsage
//   {
//      freeBlock,    // memory not used
//      objectBlock,  // contains a element derived class element
//      bitBlock,     // contains ::operator new data
//      crtBlock,
//      ignoredBlock,
//      nBlockUseMax  // total number of usages
//   };
//
//
//   memory_state();
//
//// Operations
//   void Checkpoint();  // fill with current state
//   bool Difference(const memory_state& oldState,
//               const memory_state& newState);  // fill with difference
//   void update_data();
//
//   void dumpStatistics() const;
//   void dumpAllObjectsSince() const;
//
//};
//
//
