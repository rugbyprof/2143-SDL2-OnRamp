# 🧩 `03_Drawing_a_Rectangle.md`

````markdown
---
title: SDL2 - Drawing a Rectangle (Minimal Rendering)
description: Minimal snippet showing how to clear the screen, draw a rectangle, and display it.
tags: [SDL2, Rendering, Graphics, GameLoop]
---

### 🧩 Topic: Drawing a Rectangle (Minimal Rendering)

**Essential Snippet**

```cpp
// 1. Clear the screen with a background color
SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
SDL_RenderClear(renderer);

// 2. Define and draw a filled rectangle
SDL_Rect box{100, 100, 80, 80};
SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
SDL_RenderFillRect(renderer, &box);

// 3. Present the frame to the screen
SDL_RenderPresent(renderer);
```
````

**Concepts**

- `SDL_SetRenderDrawColor(renderer, r, g, b, a)` sets the active color for _future draw calls_.
- `SDL_RenderClear(renderer)` fills the entire window with the current color.
- `SDL_RenderFillRect()` draws a filled rectangle using the current draw color.
- `SDL_RenderPresent(renderer)` swaps the back buffer to the front — everything drawn becomes visible.

**Common Use**

```cpp
SDL_Rect player{playerX, playerY, width, height};
SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // green
SDL_RenderFillRect(renderer, &player);
```

**Teaches**

- The minimal rendering pipeline:
  1. Set background color →
  2. Draw shapes →
  3. Present frame.
- How drawing state works — colors persist until changed.
- That nothing appears onscreen until `SDL_RenderPresent()` is called.

**Student Prompt**

> Add this snippet inside your game loop after event handling.  
> Change the rectangle’s color, size, and position.  
> Then animate it by incrementing `x` or `y` each frame before drawing.
