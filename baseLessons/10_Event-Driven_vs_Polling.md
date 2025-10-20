# 🧩 `10_Event_Driven_vs_Polling.md`

### 🧩 Topic: Event-Driven vs Polling Comparison

Minimal snippet showing the difference between waiting for and polling events.

**Essential Snippet**

```cpp
// Blocking: waits until something happens
SDL_WaitEvent(&e);

// Non-blocking: checks if something happened, keeps going if not
while (SDL_PollEvent(&e)) {
    // handle event
}
```

**Concepts**

- `SDL_WaitEvent()` **blocks** the program until an event occurs.
  - Great for apps that should sleep when idle (like GUIs or menus).
- `SDL_PollEvent()` **non-blocking** — it checks and immediately returns.
  - Perfect for real-time programs that must keep running even without input (like games).
- The game loop typically uses `SDL_PollEvent()` because it must update every frame regardless of input.

**Common Use**

```cpp
// Typical game loop pattern
while (running) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) running = false;
    }

    update();
    render();
}
```

**Teaches**

- The philosophical difference between _event-driven_ (reactive) and _loop-driven_ (active) systems.
- Why games “poll” — they can’t afford to stop updating physics, animations, or timers.
- That GUI programs, however, often wait for events to save resources.
- The idea that your loop defines the rhythm of your program — your “heartbeat.”

**Mini Challenge**

> Modify your existing game loop to use `SDL_WaitEvent()` instead of `SDL_PollEvent()`.  
> What happens to your animation or moving shapes?  
> Then switch back to `SDL_PollEvent()` and notice the difference.  
> (Bonus: discuss which approach you’d use for a _paint program_ vs a _platformer game_.)
