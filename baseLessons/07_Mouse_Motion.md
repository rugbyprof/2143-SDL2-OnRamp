# 🧩 `07_Mouse_Motion.md`

### 🧩 Topic: Mouse Motion (Continuous Movement)

Minimal snippet showing how to track mouse position and respond to movement events.

**Essential Snippet**

```cpp
if (e.type == SDL_MOUSEMOTION) {
    int x = e.motion.x;
    int y = e.motion.y;
    // use (x, y) to move or track something
}
```

**Concepts**

- `SDL_MOUSEMOTION` is fired whenever the mouse moves within the window.
- `e.motion.x` and `e.motion.y` give the **absolute** position of the cursor.
- `e.motion.xrel` and `e.motion.yrel` give **relative movement** since the last event.
- These values are refreshed constantly — often dozens of times per frame if you move fast.

**Common Use**

```cpp
SDL_Rect cursor{e.motion.x - 10, e.motion.y - 10, 20, 20};
SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
SDL_RenderFillRect(renderer, &cursor);
```

**Teaches**

- How to capture real-time movement.
- The difference between absolute and relative motion.
- How to make an object “follow” the cursor.
- That SDL only reports motion while inside the window (unless you grab the mouse).

**Mini Challenge**

> Draw a rectangle that follows your mouse.  
> Make it change color when a mouse button is held (`SDL_MOUSEBUTTONDOWN` / `UP`).  
> Bonus: draw a trail by _not_ clearing the screen each frame.  
> Super bonus: use `xrel` / `yrel` to measure speed and adjust color intensity.
