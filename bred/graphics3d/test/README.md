# Event timing regression test

Run without a window system or GPU:

```sh
g++ -std=c++20 -Wall -Wextra -pedantic -pthread \
  source/app/bred/graphics3d/test/timed_keyboard_state.cpp \
  -o /tmp/ca2-timed-keyboard-test
/tmp/ca2-timed-keyboard-test
```

Checks a complete tap between frames, exact held duration, step/delay mode,
frame-rate independence, repeat suppression,
simultaneous keys and speed-modifier intervals, and focus reset. Movement uses
these event durations with the existing camera basis, normalization and speed;
it does not query operating-system keyboard state. `CA2_TRACE_INPUT=1` enables
Wayland event, focused-view delivery and camera interval diagnostics.

Camera defaults are a tap equivalent to 5 frames at a nominal 60 Hz, a 250 ms
hold delay, and the existing movement speed. After the delay, each key contributes
only its actual held duration. OS repeat messages do not add steps. Mouse look
and arrow behavior are unchanged.

Applications may call `configure_keyboard_input(tapSeconds, holdDelaySeconds)`.
The usual per-application file settings also accept:

- `camera_key_tap_ms.txt`: initial step expressed as equivalent movement time.
- `camera_key_hold_delay_ms.txt`: delay before continuous movement.
- `camera_move_speed.txt`: world units per second (scales taps and continuous movement).

A tap time of zero disables the initial step; a zero hold delay starts continuous
movement immediately. Setting both to zero selects direct held-time movement.
Invalid settings fall back to the defaults.
