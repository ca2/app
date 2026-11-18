#include "../timed_keyboard_state.h"
#include <cassert>
#include <cmath>
#include <cstdio>
using keyboard = graphics3d::timed_keyboard_state<3>;
using namespace std::chrono_literals;
static bool near(double a, double b) { return std::abs(a - b) < 1e-9; }
int main()
{
 keyboard k;
 keyboard::time_point t{};
 // A complete 50 ms tap between 200 ms frames must survive exactly once.
 k.take(t);
 k.set(0,true,t+20ms); k.set(0,false,t+70ms);
 auto intervals=k.take(t+200ms);
 assert(intervals.size()==1 && intervals[0].pressed[0]);
 assert(near(intervals[0].seconds,.05));
 assert(near(intervals[0].seconds*7.,.35));
 assert(k.take(t+400ms).empty());
 // A repeat cannot restart a hold, nor charge idle time before the press.
 k.set(0,true,t+500ms); k.set(0,true,t+510ms);
 intervals=k.take(t+600ms);
 assert(intervals.size()==1 && near(intervals[0].seconds,.1));
 // Preserve simultaneous/opposing keys and speed modifiers as separate spans.
 k.set(1,true,t+620ms); k.set(2,true,t+640ms);
 k.set(0,false,t+660ms); k.set(1,false,t+680ms); k.set(2,false,t+700ms);
 intervals=k.take(t+800ms);
 assert(intervals.size()==5);
 for(const auto & span:intervals) assert(near(span.seconds,.02));
 assert(intervals[0].pressed[0] && !intervals[0].pressed[1]);
 assert(intervals[1].pressed[0] && intervals[1].pressed[1] && !intervals[1].pressed[2]);
 assert(intervals[2].pressed[0] && intervals[2].pressed[1] && intervals[2].pressed[2]);
 assert(!intervals[3].pressed[0] && intervals[3].pressed[1] && intervals[3].pressed[2]);
 assert(!intervals[4].pressed[0] && !intervals[4].pressed[1] && intervals[4].pressed[2]);
 // Focus loss discards stale pending movement and held keys.
 k.set(0,true,t+900ms); k.reset();
 assert(k.take(t+10s).empty());
 k.set(0,true,t+11s); k.set(0,false,t+11050ms);
 intervals=k.take(t+12s);
 assert(intervals.size()==1 && near(intervals[0].seconds,.05));
 // Step mode: one impulse per real press, then elapsed-time movement after
 // the hold delay. Rendering and OS repeat frequency cannot change distance.
 k.configure(5./60.,.25,2);
 k.set(0,true,t); k.set(0,true,t+10ms); k.set(0,false,t+50ms);
 intervals=k.take(t+200ms);
 assert(intervals.size()==1 && near(intervals[0].seconds,5./60.));
 assert(k.take(t+400ms).empty());
 k.set(0,true,t+1s);
 intervals=k.take(t+1100ms);
 assert(intervals.size()==1 && near(intervals[0].seconds,5./60.));
 assert(k.take(t+1250ms).empty());
 intervals=k.take(t+1300ms);
 assert(intervals.size()==1 && near(intervals[0].seconds,.05));
 k.set(0,false,t+1400ms);
 intervals=k.take(t+2s);
 assert(intervals.size()==1 && near(intervals[0].seconds,.1));
 auto heldDistance=[&](bool frequentFrames) {
  keyboard state;state.configure(5./60.,.25,2);
  double seconds=0.;state.set(0,true,t);
  if(frequentFrames) for(int ms=10;ms<500;ms+=10)
   for(auto span:state.take(t+std::chrono::milliseconds(ms)))seconds+=span.seconds;
  state.set(0,false,t+500ms);
  for(auto span:state.take(t+1s))seconds+=span.seconds;
  return seconds;
 };
 assert(near(heldDistance(true),5./60.+.25));
 assert(near(heldDistance(false),heldDistance(true)));
 // A modifier changes the continuous speed state without adding a tap.
 k.reset();k.set(0,true,t);k.take(t+100ms);
 k.set(2,true,t+200ms);k.set(2,false,t+300ms);k.set(0,false,t+350ms);
 intervals=k.take(t+1s);
 assert(intervals.size()==2 && near(intervals[0].seconds,.05) && near(intervals[1].seconds,.05));
 assert(intervals[0].pressed[2] && !intervals[1].pressed[2]);
 std::puts("Timed keyboard input passed: exact holds, step/delay mode, between-frame taps, repeat suppression, frame-rate independence, modifier spans and focus reset");
}
