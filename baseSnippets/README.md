## 🧩 Baby Steps

# 🧱 **Stage 1: Create a Window (No Error Checking)**

This is the absolute bare minimum SDL2 program that shows a window.  
If this runs, you’ve successfully initialized SDL and your graphics system.

```cpp
// =============================================================
// 01_window.cpp - Minimal SDL2 Window
// =============================================================
// To compile (macOS example):
// g++ 01_window.cpp -o window -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
// =============================================================

#include <SDL.h>   // Include the SDL2 library header

int main() {
    SDL_Init(SDL_INIT_VIDEO);   // 1️⃣ Initialize the SDL video subsystem

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Window",          // 2️⃣ Title text for the window
        SDL_WINDOWPOS_CENTERED, // 3️⃣ X position on the screen
        SDL_WINDOWPOS_CENTERED, // 4️⃣ Y position on the screen
        800,                    // 5️⃣ Width of the window in pixels
        600,                    // 6️⃣ Height of the window in pixels
        0                       // 7️⃣ No flags (basic window)
    );

    SDL_Delay(2000);            // 8️⃣ Keep window open for 2 seconds
    SDL_Quit();                 // 9️⃣ Shut down SDL
    return 0;
}
```

🧠 **Concepts introduced:**

- `SDL_Init()` brings SDL online (video, audio, input, etc.)
- `SDL_CreateWindow()` is your OS-level window call.
- `SDL_Delay()` just pauses so you can see the result.
- `SDL_Quit()` cleans up after SDL.

---

# 🧮 **Stage 2: Draw a Grid**

Now that we can open a window, let’s **render** something!  
We add a `SDL_Renderer` and draw horizontal/vertical lines every few pixels.

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

---

# 🧰 **Stage 3: Add Minimal Error Checking**

Now we’ll add _just enough_ safety to avoid silent crashes,  
but keep it **readable** for students.

```cpp
// =============================================================
// 03_with_error_checking.cpp - Minimal Safety Checks
// =============================================================

#include <SDL.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL could not initialize! " << SDL_GetError() << "\n";
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("SDL2 Grid (Safe)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        800, 600, 0);

    if (!window) {
        std::cout << "Window creation failed: " << SDL_GetError() << "\n";
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        std::cout << "Renderer creation failed: " << SDL_GetError() << "\n";
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    int cellSize = 40;
    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);

        for (int x = 0; x < 800; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);
        for (int y = 0; y < 600; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);

        SDL_RenderPresent(renderer);
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
```

🧠 **Concepts introduced:**

- `SDL_GetError()` gives human-readable errors.
- Always check if `window` or `renderer` is `nullptr`.
- Clean shutdown: destroy what you create before quitting.

---

# 🧩 🗂️ Generated File Set

I can generate a ZIP bundle containing:

```
SDL2_Teaching/
├── 01-base_window.cpp
├── 02-draw_grid.cpp
├── 03-grid_w_error_check.cpp
└── 04-window_w_text.md
```

Each file builds independently with:

```bash
g++ 02_grid.cpp -o grid -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
./grid
```

---

Would you like me to generate that **ZIP** for download now?  
(It’ll include all three files, commented exactly like above — perfect for lecture handouts or in-class demos.)

You nailed it, Terry — **yes**, you’ll need an _additional_ SDL library to render text:

> ✅ **`SDL_ttf`** (the TrueType Font extension library for SDL2)

---

## 🧩 TL;DR

| Goal                       | Library Needed | Header        | Link Flag    |
| -------------------------- | -------------- | ------------- | ------------ |
| Draw shapes, lines, images | `SDL2`         | `<SDL.h>`     | `-lSDL2`     |
| Draw **text**              | `SDL2_ttf`     | `<SDL_ttf.h>` | `-lSDL2_ttf` |

---

## 🧠 Why You Need It

SDL by itself knows **nothing** about text.  
It can draw pixels, lines, rectangles — but not glyphs or fonts.

`SDL_ttf` is the **TrueType font** add-on that wraps FreeType2 to:

- Load `.ttf` or `.otf` font files
- Render characters or strings into SDL surfaces
- Convert them into SDL textures for display

---

## ⚙️ Installation (macOS / Linux)

### macOS (Homebrew)

```bash
brew install sdl2_ttf
```

### Ubuntu / Debian

```bash
sudo apt install libsdl2-ttf-dev
```

---

## 🧰 Compilation Example

```bash
g++ main.cpp -o text_demo -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
```

---

## ✨ Minimal Example: Displaying Text

This is the **shortest** working example showing text on screen.

```cpp
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();  // 🧠 Initialize SDL_ttf

    SDL_Window* window = SDL_CreateWindow("SDL2 Text Example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // 1️⃣ Load a font (adjust the path to your .ttf file)
    TTF_Font* font = TTF_OpenFont("/Library/Fonts/Arial.ttf", 48);

    // 2️⃣ Create a color (white)
    SDL_Color color = {255, 255, 255, 255};

    // 3️⃣ Render text to a *surface*
    SDL_Surface* surface = TTF_RenderText_Solid(font, "Hello, Graylian!", color);

    // 4️⃣ Convert surface to a *texture* for rendering
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

    // 5️⃣ Query texture size for placement
    int textW = 0, textH = 0;
    SDL_QueryTexture(texture, nullptr, nullptr, &textW, &textH);

    SDL_Rect dst = {100, 100, textW, textH};

    // 6️⃣ Draw it
    SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
    SDL_RenderPresent(renderer);

    SDL_Delay(3000);

    // 7️⃣ Cleanup
    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}
```

---

## 🧩 How It Works

| Step                             | Function                                       | Purpose |
| -------------------------------- | ---------------------------------------------- | ------- |
| `TTF_Init()`                     | Initializes SDL_ttf                            |
| `TTF_OpenFont("path.ttf", size)` | Loads a TrueType font                          |
| `TTF_RenderText_Solid()`         | Creates an SDL_Surface with your rendered text |
| `SDL_CreateTextureFromSurface()` | Converts that to a GPU texture                 |
| `SDL_RenderCopy()`               | Blits the text texture to your renderer        |
| `TTF_Quit()`                     | Shuts down SDL_ttf                             |

---

## 💡 Other Text Rendering Modes

| Function                   | Style                 | Notes                                                   |
| -------------------------- | --------------------- | ------------------------------------------------------- |
| `TTF_RenderText_Solid()`   | Fastest               | No blending, looks pixelated on transparent backgrounds |
| `TTF_RenderText_Blended()` | Best quality          | Uses anti-aliasing (slower but prettier)                |
| `TTF_RenderText_Shaded()`  | Adds background color | Good for highlighted text                               |

Example:

```cpp
SDL_Surface* surface = TTF_RenderText_Blended(font, "Smooth!", {255,255,255,255});
```

---

## 🧠 Teaching Progression Idea

You could create another **lesson chain** similar to your grid one:

| Stage | Lesson                     | Description                               |
| ----- | -------------------------- | ----------------------------------------- |
| 01    | Window only                | Same as before                            |
| 02    | Add SDL_ttf include & init | “What happens if we forget `TTF_Init()`?” |
| 03    | Render static text         | Use `TTF_RenderText                       |
