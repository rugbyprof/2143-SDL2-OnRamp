// =============================================================
// click_to_cell_toggle.cpp - SDL2 Clickable Grid (Editable Cells)
// =============================================================
// Compile (macOS example):
// g++ click_to_cell_toggle.cpp -o clicktoggle -I/opt/homebrew/include/SDL2 -I/opt/homebrew/include/SDL2_ttf -L/opt/homebrew/lib -lSDL2 -lSDL2_ttf
// =============================================================

#include <SDL.h>
#include <SDL_ttf.h>

#include <sstream>
#include <string>
#include <vector>

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    TTF_Init();

    SDL_Window*   window = SDL_CreateWindow("Click-to-Toggle Grid",
                                            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                            800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    TTF_Font* font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 20);
    if (!font) font = TTF_OpenFont("DejaVuSans.ttf", 20);

    // -------------------------------------------------------------
    // GRID CONFIGURATION
    // -------------------------------------------------------------
    const int cellSize = 40;
    const int cols = 800 / cellSize;
    const int rows = 600 / cellSize;

    // 2D grid of booleans (false = dead, true = alive)
    std::vector< std::vector< bool > > cells(rows, std::vector< bool >(cols, false));

    int clickedRow = -1;
    int clickedCol = -1;

    bool      running = true;
    SDL_Event e;

    while (running) {
        // ---------------------------------------------------------
        // 1️⃣ HANDLE EVENTS
        // ---------------------------------------------------------
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)
                running = false;
            else if (e.type == SDL_MOUSEBUTTONDOWN) {
                int mouseX = e.button.x;
                int mouseY = e.button.y;

                clickedCol = mouseX / cellSize;
                clickedRow = mouseY / cellSize;

                // Toggle state on click
                if (clickedRow >= 0 && clickedRow < rows &&
                    clickedCol >= 0 && clickedCol < cols) {
                    cells[clickedRow][clickedCol] = !cells[clickedRow][clickedCol];
                }
            }
        }

        // ---------------------------------------------------------
        // 2️⃣ CLEAR BACKGROUND
        // ---------------------------------------------------------
        SDL_SetRenderDrawColor(renderer, 30, 30, 40, 255);
        SDL_RenderClear(renderer);

        // ---------------------------------------------------------
        // 3️⃣ DRAW LIVE CELLS
        // ---------------------------------------------------------
        SDL_SetRenderDrawColor(renderer, 255, 200, 0, 255);
        for (int r = 0; r < rows; ++r)
            for (int c = 0; c < cols; ++c)
                if (cells[r][c]) {
                    SDL_Rect cellRect = {c * cellSize, r * cellSize, cellSize, cellSize};
                    SDL_RenderFillRect(renderer, &cellRect);
                }

        // ---------------------------------------------------------
        // 4️⃣ DRAW GRID LINES
        // ---------------------------------------------------------
        SDL_SetRenderDrawColor(renderer, 80, 80, 100, 255);
        for (int x = 0; x <= 800; x += cellSize)
            SDL_RenderDrawLine(renderer, x, 0, x, 600);
        for (int y = 0; y <= 600; y += cellSize)
            SDL_RenderDrawLine(renderer, 0, y, 800, y);

        // ---------------------------------------------------------
        // 5️⃣ DISPLAY LAST CLICKED CELL INDEX
        // ---------------------------------------------------------
        if (clickedRow >= 0 && clickedCol >= 0) {
            std::ostringstream oss;
            oss << "[col=" << clickedCol << ", row=" << clickedRow
                << "] " << (cells[clickedRow][clickedCol] ? "Alive" : "Dead");
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

        // ---------------------------------------------------------
        // 6️⃣ PRESENT FRAME
        // ---------------------------------------------------------
        SDL_RenderPresent(renderer);
        SDL_Delay(16);
    }

    // -------------------------------------------------------------
    // CLEANUP
    // -------------------------------------------------------------
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();
    return 0;
}