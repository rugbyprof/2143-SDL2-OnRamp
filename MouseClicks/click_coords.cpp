// =============================================================
// click_coords.cpp - SDL2 Grid + Mouse Coordinates Demo
// =============================================================
// Compile (macOS example):
// g++ click_coords.cpp -o clickcoords -I/opt/homebrew/include/SDL2 -I/opt/homebrew/include/SDL2_ttf -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
// =============================================================

#include <SDL.h>
#include <SDL_ttf.h>

#include <sstream>
#include <string>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window*   window = SDL_CreateWindow("Click Coordinate Demo",
                                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    // Load a system or fallback font
    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 20);
    if (!font) font = TTF_OpenFont("DejaVuSans.ttf", 20);

    bool      running = true;
    SDL_Event e;
    int       cellSize = 40;
    int       clickX = -1, clickY = -1;

    while (running) {
        // 1️⃣ Event handling
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                clickX = e.button.x;
                clickY = e.button.y;
            }
        }

        // 2️⃣ Background color
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // 3️⃣ Draw grid
        SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
        for (int x = 0; x < 800; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);
        for (int y = 0; y < 600; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);

        // 4️⃣ Draw mouse coordinates (if clicked)
        if (clickX >= 0 && clickY >= 0) {
            std::ostringstream oss;
            oss << "(" << clickX << ", " << clickY << ")";
            std::string text = oss.str();

            SDL_Color    white = {255, 255, 255, 255};
            SDL_Surface* surf = TTF_RenderText_Solid(font, text.c_str(), white);
            SDL_Texture* tex = SDL_CreateTextureFromSurface(renderer, surf);

            int w, h;
            SDL_QueryTexture(tex, NULL, NULL, &w, &h);

            SDL_Rect dst = {800 - w - 10, 10, w, h};
            SDL_RenderCopy(renderer, tex, NULL, &dst);

            SDL_DestroyTexture(tex);
            SDL_FreeSurface(surf);
        }

        // 5️⃣ Present
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}