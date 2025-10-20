# 🧩 `05_Keyboard_State_Array.md`

### 🧩 Topic: Keyboard State Array (Continuous Input)

Minimal snippet showing how to check which keys are currently held down each frame.

**Essential Snippet**

```cpp
const Uint8* state = SDL_GetKeyboardState(NULL);

if (state[SDL_SCANCODE_W]) { /* move up */ }
if (state[SDL_SCANCODE_S]) { /* move down */ }
if (state[SDL_SCANCODE_A]) { /* move left */ }
if (state[SDL_SCANCODE_D]) { /* move right */ }
```

**Concepts**

- `SDL_GetKeyboardState(NULL)` returns a pointer to an array representing the state of _every key_.
- Each entry is `1` if pressed or `0` if not.
- Keys are indexed by **scancodes** (physical key positions, not key labels).
- This method is perfect for _continuous_ input (e.g., movement while a key is held).

**Common Use**

```cpp
// Move a rectangle when keys are held
if (state[SDL_SCANCODE_W]) playerY -= speed;
if (state[SDL_SCANCODE_S]) playerY += speed;
if (state[SDL_SCANCODE_A]) playerX -= speed;
if (state[SDL_SCANCODE_D]) playerX += speed;
```

**Teaches**

- Continuous vs. discrete input handling.
- The relationship between `SDL_KEYDOWN`/`SDL_KEYUP` and the state array.
- Why real-time games typically read key states every frame.
- Scancodes stay consistent across keyboard layouts (unlike keycodes).

**Mini Challenge**

> Combine this with your frame-timed rectangle demo.  
> Make your rectangle move smoothly with `WASD`.  
> Add speed control (Shift = faster, Ctrl = slower).  
> Try printing key states to see when multiple keys are held at once.
