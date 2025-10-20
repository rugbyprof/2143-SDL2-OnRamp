# 🧱 Create a Window(No Error Checking)

- This is the absolute bare minimum SDL2 program that shows a window.
- If this runs, you’ve successfully initialized SDL and your graphics system.

## # 🛠 Compilation Command

```bash
g++ 01_window.cpp -o window -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
```

```cpp
// =============================================================
// 01_window.cpp - Minimal SDL2 Window
// =============================================================
// To compile (macOS example):
// g++ 01_window.cpp -o window -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
// =============================================================

#include <SDL.h>  // Include the SDL2 library header

                                                                                         int main() {
    SDL_Init(SDL_INIT_VIDEO);  // 1️⃣ Initialize the SDL video subsystem

    SDL_Window* window = SDL_CreateWindow(
        "SDL2 Window",           // 2️⃣ Title text for the window
        SDL_WINDOWPOS_CENTERED,  // 3️⃣ X position on the screen
        SDL_WINDOWPOS_CENTERED,  // 4️⃣ Y position on the screen
        800,                     // 5️⃣ Width of the window in pixels
        600,                     // 6️⃣ Height of the window in pixels
        0                        // 7️⃣ No flags (basic window)
    );

    SDL_Delay(2000);  // 8️⃣ Keep window open for 2 seconds
    SDL_Quit();       // 9️⃣ Shut down SDL
    return 0;
}
```

## 🧠 Concepts introduced :

- `SDL_Init()` brings SDL online(video, audio, input, etc.)
- `SDL_CreateWindow()` is your OS - level window call.
- `SDL_Delay()` just pauses so you can see the result.
- `SDL_Quit()` cleans up after SDL.
