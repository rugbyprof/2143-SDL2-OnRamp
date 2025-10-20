# 🧩 `06_Random_Colors_and_Shapes.md`

### 🧩 Topic: Random Colors and Shapes

Minimal snippet showing how to use random values for color and shape properties.

**Essential Snippet**

```cpp
int r = rand() % 256;
int g = rand() % 256;
int b = rand() % 256;

SDL_SetRenderDrawColor(renderer, r, g, b, 255);
SDL_RenderFillRect(renderer, &rect);
```

**Concepts**

- RGB color channels each range from 0–255.
- `rand() % 256` picks a random value in that range.
- Calling this each frame or for each shape gives dynamic, colorful visuals.
- You can also randomize size or position using the same pattern.

**Common Use**

```cpp
SDL_Rect rect;
rect.x = rand() % 800;
rect.y = rand() % 600;
rect.w = 20 + rand() % 80;
rect.h = 20 + rand() % 80;

int r = rand() % 256, g = rand() % 256, b = rand() % 256;
SDL_SetRenderDrawColor(renderer, r, g, b, 255);
SDL_RenderFillRect(renderer, &rect);
```

**Teaches**

- The structure of an `SDL_Rect`.
- How color is defined in SDL’s RGBA format.
- The power of randomness for testing, prototyping, and visual feedback.
- A playful way to reinforce frame loops (random every frame = chaotic animation).

**Mini Challenge**

> Create a “rainbow fireworks” screen:  
> Each frame, draw 10 rectangles at random positions and colors.  
> Bonus: clear the screen only every few frames to create trails.  
> Super bonus: seed the random number generator (`srand(SDL_GetTicks());`) to change the pattern each run.
