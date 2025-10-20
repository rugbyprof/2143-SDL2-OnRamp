# 🧩 `08_Toggle_States_with_KeyPress.md`

### 🧩 Topic: Toggle States with a Key Press

Minimal snippet showing how to flip a boolean (like pause) without rapid repeat triggers.

**Essential Snippet**

```cpp
bool paused = false;

if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
    if (e.key.keysym.sym == SDLK_SPACE)
        paused = !paused;
}
```

**Concepts**

- `SDL_KEYDOWN` fires when a key is pressed _and_ repeats while held down.
- `e.key.repeat == 0` ensures your toggle triggers **only once per press**.
- `!paused` flips the boolean — true becomes false, false becomes true.
- This is how you safely toggle states like pause, fullscreen, or debug mode.

**Common Use**

```cpp
if (paused)
    std::cout << "Game paused.\n";
else
    std::cout << "Game resumed.\n";
```

**Teaches**

- How to debounce key input using the `repeat` flag.
- Logical state flipping (`flag = !flag`).
- Why the order of event handling matters — you can’t put this outside your event loop.
- Foundational control pattern for pause menus, visibility toggles, and more.

**Mini Challenge**

> Add this to your movement demo.  
> When paused, stop updating the rectangle’s position.  
> When unpaused, resume.  
> Bonus: draw “PAUSED” text or change the rectangle’s color to indicate state.
