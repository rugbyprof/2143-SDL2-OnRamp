// =============================================================
// color_cycle_demo.cpp - SDL2 Draw Order Visualization
// =============================================================
// Compile (macOS example):
// g++ color_cycle_demo.cpp -o colorcycle -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2
// =============================================================

#include <SDL.h>

#include <cmath>

void moveRectangle(SDL_Rect& rect, int& dx, int& dy, int screenW = 800, int screenH = 600) {
    if (rect.x < 0 || rect.x + rect.w > screenW)
        dx *= -1;
    if (rect.y < 0 || rect.y + rect.h > screenH)
        dy *= -1;

    rect.x += dx;
    rect.y += dy;
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SDL2 Color Cycle Demo",
                                          SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                          800, 600, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool      running = true;
    SDL_Event e;
    int       frame = 0;

    SDL_Rect rect = {350, 250, 100, 100};
    int      dx = 2;
    int      dy = 2;

    while (running) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
        }

        // Rectangles coords
        int rectX = 350;
        int rectY = 250;
        int rectW = 100;
        int rectH = 100;

        // 1️⃣ Set BACKGROUND color (slowly changing)
        int r = (int)(std::sin(frame * 0.02) * 127 + 128);
        int g = (int)(std::sin(frame * 0.03) * 127 + 128);
        int b = (int)(std::sin(frame * 0.04) * 127 + 128);
        SDL_SetRenderDrawColor(renderer, r, g, b, 255);
        SDL_RenderClear(renderer);

        // 2️⃣ Set GRID color (based on frame)
        SDL_SetRenderDrawColor(renderer, 255 - r, 255 - g, 255 - b, 255);
        for (int x = 0; x < 800; x += 40)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);
        for (int y = 0; y < 600; y += 40)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);

        // 3️⃣ Set SHAPE color (notice we change it again!)
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);

        SDL_RenderFillRect(renderer, &rect);

        moveRectangle(rect, dx, dy);

        // 4️⃣ Present final image to screen
        SDL_RenderPresent(renderer);

        SDL_Delay(16);
        frame++;
    }

    SDL_Quit();
    return 0;
}