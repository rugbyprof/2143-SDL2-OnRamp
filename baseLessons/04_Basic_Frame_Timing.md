# 🧩 `04_Basic_Frame_Timing.md`

### 🧩 Topic: Basic Frame Timing (Limiting FPS)

Minimal snippet showing how to keep a consistent frame rate (around 60 FPS).

**Essential Snippet**

```cpp
Uint32 frameStart = SDL_GetTicks();
// ... update logic and drawing go here ...
Uint32 frameTime = SDL_GetTicks() - frameStart;
if (frameTime < 16) SDL_Delay(16 - frameTime);
```

**Concepts**

- `SDL_GetTicks()` returns the number of milliseconds since SDL was initialized.
- Capturing a timestamp at the start and end of the frame lets you measure frame duration.
- `SDL_Delay(ms)` pauses the program for the specified milliseconds (roughly).
- `16 ms ≈ 60 FPS` → because 1000ms / 60 ≈ 16.6.

**Common Use**

```cpp
while (running) {
    Uint32 start = SDL_GetTicks();

    handleInput();
    updateGame();
    renderScene();

    Uint32 elapsed = SDL_GetTicks() - start;
    if (elapsed < 16) SDL_Delay(16 - elapsed);
}
```

**Teaches**

- Why games need **consistent timing** for movement and animation.
- How to limit framerate to avoid CPU burnout.
- That real-time loops run as fast as your computer unless throttled.
- The start of separating **game time** from **real time** — a foundational concept.

**Mini Challenge**

> Add this snippet to your rectangle demo.
> Print the measured `frameTime` each frame to the console.
> Try increasing and decreasing the delay to see how motion smoothness changes.
> (Bonus: calculate the actual FPS using `1000 / frameTime`.)
