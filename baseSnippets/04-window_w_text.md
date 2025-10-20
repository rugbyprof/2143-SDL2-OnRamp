# Writing Text to Windows

Most everything can be handled by the SDL2 library, except fonts. This is nothing new. It's a little like the unicode vs ascii or utf-8 issues. Fonts just make things a little wierd. If you look below, like I said SDL2 for shapes, lines, images but for `text` we need `SDL2_ttf`.

## 🧩 Requirements

| Goal                       | Library Needed | Header        | Link Flag    |
| -------------------------- | -------------- | ------------- | ------------ |
| Draw shapes, lines, images | `SDL2`         | `<SDL.h>`     | `-lSDL2`     |
| Draw **text**              | `SDL2_ttf`     | `<SDL_ttf.h>` | `-lSDL2_ttf` |

---

## 🧠 Why You Need It

- SDL by itself knows **nothing** about text.
- It can draw pixels, lines, rectangles — but not glyphs or fonts.

- `SDL_ttf` is the **TrueType font** add-on that wraps FreeType2 to:
  - Load `.ttf` or `.otf` font files
  - Render characters or strings into SDL surfaces
  - Convert them into SDL textures for display

---

## ⚙️ Installation (macOS / Linux)

### macOS (Homebrew)

```bash
brew install sdl2_ttf
```

### Ubuntu / Debian (WSL)

```bash
sudo apt install libsdl2-ttf-dev
```

---

## 🧰 Compilation Example

It's the same as before but we add the -lSDL2_ttf to tell the compiler about our new library we need.

```bash
g++ main.cpp -o text_demo -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
```

---

## ✨ Minimal Example: Displaying Text

This is the **shortest** working example showing text on screen ... and it's not short 🤷‍♂️.

```cpp
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();  // 🧠 Initialize SDL_ttf

    // Create a window instance to work with
    SDL_Window* window = SDL_CreateWindow("SDL2 Text Example",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);

    // Create a "renderer" tied to rendering to our `window`
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
