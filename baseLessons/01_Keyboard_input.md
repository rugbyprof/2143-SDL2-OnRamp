-# 🧩 `01_Keyboard_Input_Basics.md`

Minimum code necessary to grab keyboard input.

### 🧩 Topic: Keyboard Input (Press + Release)

**Essential Snippet**

```cpp
SDL_Event e;
while (SDL_PollEvent(&e)) {
    if (e.type == SDL_KEYDOWN) {
        // e.key.keysym.sym gives which key was pressed
    }
    if (e.type == SDL_KEYUP) {
        // e.key.keysym.sym again, but for key release
    }
}
```



**Concepts**

- `SDL_KEYDOWN` fires once when a key is pressed.
- `SDL_KEYUP` fires once when a key is released.
- `e.key.keysym.sym` holds the SDL key code (`SDLK_w`, `SDLK_a`, etc.).
- `SDL_GetKeyName(e.key.keysym.sym)` returns a printable name (`"W"`, `"Space"`, etc.).
- You can add `if (e.key.repeat == 0)` to ignore repeated “key held” events.

**Common Use**

```cpp
if (e.key.keysym.sym == SDLK_ESCAPE)
    running = false;  // quit game

if (e.key.keysym.sym == SDLK_SPACE)
    paused = !paused; // toggle pause state
```

**Teaches**

- Discrete keyboard events (press/release).
- Mapping keys to actions.
- The difference between a single press vs. a held key.

**Mini Challenge**

> Expand this snippet into a small test:  
> Print `"Key pressed: X"` and `"Key released: X"` to the console.  
> Add a quit key (ESC) and a pause toggle (SPACE).

```

```
