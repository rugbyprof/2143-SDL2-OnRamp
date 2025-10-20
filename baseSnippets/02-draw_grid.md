# 🧮 **Stage 2: Draw a Grid**

Did anyone run the **base window** code, it ran, but the window never appeared? I would like to discuss that in class.

Next Streps:

- Now that we can open a window, let’s **render** something!
- We add a `SDL_Renderer` and draw horizontal/vertical lines every few pixels.

> Note: I wanted to print some text on the window initially because I assumed it was easy. Well it's easier to draw a grid then print a word 😳.

```cpp
// =============================================================
// 02_grid.cpp - Draw a Grid
// =============================================================
// g++ 02_grid.cpp -o grid -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
// =============================================================

#include <SDL.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 Grid",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    int cellSize = 40;   // Distance between grid lines

    bool running = true;
    SDL_Event event;

    while (running) {
        // 1️⃣ Poll for events (keyboard, mouse, quit)
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // 2️⃣ Clear the screen with dark gray
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // 3️⃣ Set color for grid lines (light gray)
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

        // 4️⃣ Draw vertical lines
        for (int x = 0; x < 800; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);

        // 5️⃣ Draw horizontal lines
        for (int y = 0; y < 600; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);

        // 6️⃣ Display everything
        SDL_RenderPresent(renderer);
    }

    SDL_Quit();
    return 0;
}
```

🧠 **Concepts introduced:**

- `SDL_Renderer` handles drawing commands.
- `SDL_SetRenderDrawColor` sets the brush color.
- `SDL_RenderDrawLine` is the simplest draw function.
- `SDL_RenderPresent` swaps the off-screen buffer to the display.
- `SDL_PollEvent` checks for “Quit” events (X button).
