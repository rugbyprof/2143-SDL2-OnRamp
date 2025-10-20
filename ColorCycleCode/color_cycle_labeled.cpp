// =============================================================
// color_cycle_labeled.cpp - SDL2 Draw Order Visualization (with text)
// =============================================================
// Compile (macOS example):
// g++ color_cycle_labeled.cpp -o colorlabel \
//     -I/opt/homebrew/include/SDL2 -I/opt/homebrew/include/SDL2_ttf \
//     -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
// =============================================================

#include <SDL.h>
#include <SDL_ttf.h>

#include <cmath>
#include <string>

// Small helper to draw a single line of text
void drawText(SDL_Renderer* renderer, TTF_Font* font,
              const std::string& msg, int x, int y, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font, msg.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_Rect     rect = {x, y, surface->w, surface->h};
    SDL_FreeSurface(surface);
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_DestroyTexture(texture);
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();  // 🔹 initialize font subsystem

    SDL_Window*   window = SDL_CreateWindow("SDL2 Color Cycle Demo (Labeled)",
                                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Load a system font (you can use any TTF file you have)
    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 24);
    if (!font) font = TTF_OpenFont("DejaVuSans.ttf", 24);  // fallback for Linux

    bool      running = true;
    SDL_Event e;
    int       frame = 0;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        // ------------------------------
        // 1️⃣ BACKGROUND
        // ------------------------------
        int r = (int)(std::sin(frame * 0.02) * 127 + 128);
        int g = (int)(std::sin(frame * 0.03) * 127 + 128);
        int b = (int)(std::sin(frame * 0.04) * 127 + 128);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);
        drawText(renderer, font, "BACKGROUND", 20, 20, {255, 255, 255, 255});

        // ------------------------------
        // 2️⃣ GRID
        // ------------------------------
        SDL_SetRenderDrawColor(renderer, 255 - r, 255 - g, 255 - b, 255);
        for (int x = 0; x < 800; x += 40)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);
        for (int y = 0; y < 600; y += 40)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);
        drawText(renderer, font, "GRID", 20, 60, {255, 255, 0, 255});

        // ------------------------------
        // 3️⃣ SHAPE
        // ------------------------------
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_Rect rect = {350, 250, 100, 100};
        SDL_RenderFillRect(renderer, &rect);
        drawText(renderer, font, "SHAPE", 20, 100, {255, 128, 128, 255});

        // ------------------------------
        // Present to screen
        // ------------------------------
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
        frame++;
    }

    // Cleanup
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_Quit();
    return 0;
}