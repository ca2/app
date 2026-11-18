# Composed auto-hide controller

`user::auto_hide` is a `matter`, not an interaction or a window base class.
Any interaction can hold a `pointer<user::auto_hide>`, initialize it with its
context, and call `attach(this)`. The owner forwards its timer callbacks to
`operator()` and mouse movement/leave to the corresponding controller methods.
It calls `detach()` before destruction. The controller uses the owner's window,
coordinates, redraw requests and timer; it does not create another window.

## Full-screen frame coordination

`experience::frame_window::full_screen_auto_hide()` lazily creates a frame-owned
controller with a one-pixel reveal edge. The frame forwards mouse movement before
routing to children, preserving brief y=0 hits. A 100 ms live-cursor poll handles
stationary hover and the two-second hide delay. The control box registers with the
frame directly, so a pane impact is not required. Its normal right-hand geometry
is retained. No separate control-box hover timer decides full-screen visibility.

Hello Multiverse's pane uses `set_auto_hide_controller()` to join this controller;
its top editors register with that same controller. The strip and editors remain
overlays and do not shrink the rendered content.

`add_auto_hide_interaction(interaction, height = -1)` registers a subscriber.
Subscribers receive `auto_hide_visibility` through `handle()`, with Boolean
`coordinated` and `visible` payloads. They apply visibility to their chrome or
holder and request layout/redraw when it changes. Do not forward this notification
back to the controller. A tab's whole client remains visible while its strip hides.

While revealed, visible subscribers' screen rectangles keep the group open.
A nonnegative registration height limits that region to a strip at the top of
the interaction; the pane registers only its tab height, not its full content.
Hidden subscribers never extend the reveal region. Leaving all registered regions
starts the shared two-second delay; returning cancels it.

The owner and subscriber registrations are non-owning. Subscribers unregister in
their destruction path. Notifications retain a temporary snapshot and invoke
callbacks outside the registration lock. A subscriber may retain the controller
without retaining the owner. `detach()` stops polling and clears the owner, so
remaining subscriber references cannot access a destroyed frame.

Tabs without a frame coordinator retain a local composed controller and their
existing full-screen/transparent-frame visibility behavior. Theme callers read
state through the tab's `m_pAutoHide` member.

## Overlay placement relationships

`set_overlay_after(editor, pane)` declares that the editor's top edge follows
that pane's registered strip. `overlay_top(editor, parent, layout)` resolves the
strip's bottom edge into the editor holder parent's coordinates. The registered
strip height is used, rather than the pane's full client height. Removing a
subscriber also clears placement relationships that refer to it.

Hello Multiverse declares its editor after its pane's tabs. The tabs occupy the
first row at the top edge; the editor occupies the next row beneath them. Both
overlay the full-size scene. The editor applies this placement when revealed and
when its split parent lays out, so a holder previously placed while hidden does
not retain y=0 on reveal. The control box keeps its separate frame geometry.

The frame starts or updates polling during its own layout, independently of hidden
chrome children. Registration also refreshes polling for an already full-screen
owner. The frame overrides the existing `on_window_mouse_move` owner hook, which runs
before child routing and mouse capture. It passes the recorded event position to
`auto_hide_on_mouse_move`, which immediately reveals hidden subscribers and requests
a redraw. Non-client moves use the screen position recorded in LPARAM as well.
Polling remains a fallback and manages the shared keep-open/hide delay. Repeated
edge events do not repeatedly request layout after the group is already visible.

## Reveal latency diagnostic

With FPS_DEBUG enabled, the first tab draw intersecting the tab strip after a
hidden-to-visible transition emits one FPS auto-hide line. It identifies event
versus poll/layout detection and measures reveal-to-tab-draw with steady_clock.
This measures CPU rendering completion of the tabs, not native presentation or
RDP delivery, and starts when the application handles the reveal rather than
when the physical mouse moved. Rebuild dependent berg consumers together after
changes to the composed controller layout.

## Keep-open bounds

A frame owner contributes only the reveal edge; its full client never keeps the
group open. Hello Multiverse's editor registers its normal editor height, and
registered strip limits are clipped to the interaction's own rectangle. Updating
an existing strip height during tab layout does not recalculate or rebroadcast
visibility. New subscribers still receive the current coordinated state.

## Native presentation latency

FPS auto-hide present reports the first successful native commit of a buffer
whose tab drawing was stamped with the pending reveal. The id matches the
CPU tab-draw diagnostic. The event timestamp starts at entry to the controller's
mouse-move handler, before reveal checks; it excludes input travel and OS message
queue time before that handler. Poll/layout reveals are identified separately.

The render buffer owns per-frame timestamps, cleared at its next layout pass.
The shared reveal remains pending across skipped frames and native failures;
hiding, detaching, or a new reveal cancels the old pending measurement. Successful
completion is reported once. Each native failure reports result=failed and the
Windows error without marking the reveal presented.

Stages are event_to_tab, remaining_render (through rendering before buffer swap),
pacing (buffer swap, presentation scheduling, and locks before backend entry),
present_prepare (including bitmap mapping/copy and preparation before main_send),
owner_wait (synchronous dispatch to the HWND thread), owner_prepare (geometry
checks and configuration), and native_commit (UpdateLayeredWindow plus GdiFlush,
or ReactOS opaque BitBlt plus flush/ReleaseDC). event_to_present is the sum of
these stages through the native boundary. It does not confirm compositor scanout
or RDP client display. No DwmFlush or blocking synchronization is added.

The overlay trace applies to the layered-window software presentation path used
by Hello Multiverse, plus its existing ReactOS opaque fallback. GPU swap-chain
and optional diagnostic DIB presentation paths are not instrumented. Generation
and timing work are guarded by FPS_DEBUG; shared class layouts remain consistent
with it disabled. Rebuild aura, berg, aura_windows, windowing_win32 and dependent
modules together because the render buffer and controller gain appended members.

### Frame and layout split

The successful overlay frame also records draw_frame entry, layout-stage entry,
and layout-stage completion. event_phase identifies whether reveal arrived
before_frame, during frame_setup, layout, or drawing of that responding frame.

event_to_frame_start, frame_setup_after_event, layout_after_event, and
layout_to_tab partition event_to_tab. Work before the reveal is excluded from
these four intervals. layout_total reports the complete layout-stage duration;
frame_age_at_event reports how long the frame had already been running if the
event arrived mid-frame. These two context values are not additional stages.

Frame setup includes buffer/graphics lock waits and target preparation before
frame_layout_stage. layout_to_tab includes drawing before and through the tabs.
The frame is the actual successfully presented overlay frame, so a skipped
intermediate frame does not masquerade as a successful response. All timestamps
remain guarded by FPS_DEBUG and follow the existing steady-clock time base.

## Visibility task ownership

Visibility calculations, reveal transitions, timer start/stop, and the hide
countdown execute on the owner's user task. Calls from graphics/layout or timer
threads post one coalesced request using ca2 user_post and synchronization.
Off-task mouse events preserve their original controller-entry timestamp when
posted. Timer callbacks do not stop timers based on state read before the posted
calculation has run. This prevents competing calculations from resetting the
countdown or cancelling its polling timer.

FPS auto-hide state logs transitions and, while visible, at most once every two
seconds. The reason identifies edge, subscriber, visibility_policy, hide_delay,
or hidden, with cursor position, the matched keep-open interaction/rectangle,
and whether a countdown is active. These lines diagnose a persistent keep-open
condition separately from presentation latency; no visibility policy is inferred
from timing diagnostics.
