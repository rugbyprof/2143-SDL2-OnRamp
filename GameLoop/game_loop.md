# Game Loop

This concept _confuses even some senior devs_ when they first meet a game loop. I mean it's infinite! `while(keep_going)` 🤣 is wierd. The mental model is different from a “normal program” where you: write input → process it → generate output → done. However game loops don't truly work the same, there is more going on behind the scenes. So let's explore it.

---

## 🧠 The Big Idea

The game loop is not just **running** and it's **not waiting** — it’s **checking** for things like events but it's checking to see what's happening a lot of times in a second.

> Think of some source code AI walking around the classroom (really FAST) and asking:  
> “Any questions? Any mouse clicks? You press a key? What about you? No? Cool, I’ll keep teaching.”

It doesn’t _block_ waiting for an event — it’s constantly _polling_ (like checking email really fast in a loop).

> Note: a blocking event forces everything to stop and wait until the request is handled. I'm sure you can see where this would be a problem. Similar in web applications. What if the very first "image" to load was from a server in the Phillipines and it was slooooow. The browser is like good job ... keep trying ... I'm moving on (asynchronous). If the image load _blocked_, then that page would lose traffic, because we would all leave.

---

## 🌀 Step-by-Step Breakdown

### 1️⃣ Outer Loop — “The Universe Keeps Ticking”

While no one has quit (or some end condition isn't metaphor) ... keep running.

```cpp
while (running) {
    // 1 frame of your game happens here
}
```

That’s your **heartbeat** — the universe ticking 60 times per second.  
Inside that loop, you’ll handle:

- **inputs** (what the player did)
- **updates** (how the game world changes)
- **rendering** (what to show next frame)

It’s _intentionally infinite_ — the game runs until you quit (or some conditions are met).

---

### 2️⃣ Inner Loop — “The Inbox of Events”

This is also a little confusing. Another `while` loop inside the outer `while` loop. Does this program ever stop?!

```cpp
while (SDL_PollEvent(&event)) {
    // Handle all pending events this frame
}
```

- This loop doesn't effect the game loop. Why? It's looping on it's own waiting for events, and when one happens it puts it on an event queue.
- When the game loop comes back around, it asks: "got anything"? If yes: the event gets handled, if no: game loop moves right on past it.
- But the while loop waiting for events is critical because they should be capture immediately, but also placed in a queue where they are handled in order.

`SDL_PollEvent()` _checks_ if an event is waiting in SDL’s queue.

Again:

- If event loop returns `true`, you process it.
- If loop returns `false`, you move on and handle `drawing` and `updating`.

---

### 3️⃣ Why We Need Both

Because events can happen **faster than you draw** — or several might come in during one frame:

- Mouse moved 10 times
- Two keys pressed
- Window resized

So we drain the **event queue** inside the main **game loop** each frame.

---

### 🧩 Analogy: The Classroom

You’re the game loop.

- Every _frame_, you walk around the classroom (outer loop).
- You look in everyone’s hand for raised questions (inner loop).
- If nobody has a question, you still walk around and look for raised hands.

If someone says “class dismissed!” (`SDL_QUIT`), you break the game loop.

---

### 🕰️ Frame-by-Frame Mental Model

Each iteration of `while(running)` = one **frame**.

Within that frame:

1. 📨 Check for events (non-blocking)
2. 🧮 Update game state
3. 🎨 Render the new frame
4. 💤 Small delay (like `SDL_Delay(16)` for ~60 FPS)

Then it repeats.

---

### 🧪 Demo Visualization

You can even add debug prints to _prove_ it’s not stuck:

```cpp
while (running) {
    std::cout << "New frame...\n";

    while (SDL_PollEvent(&e)) {
        std::cout << "Event found: " << e.type << "\n";
    }

    SDL_Delay(500);  // half a second pause per frame for clarity
}
```

Output:

```
New frame...
New frame...
New frame...
Event found: 256  // (SDL_QUIT)
New frame...
```

You’ll see the outer loop keeps going even when no events arrive.

---

### 🧠 TL;DR Summary

| Concept                    | Description                                             | Analogy                             |
| -------------------------- | ------------------------------------------------------- | ----------------------------------- |
| Outer loop                 | Runs once per frame, forever until quit                 | Heartbeat                           |
| Inner loop                 | Handles all pending events this frame                   | Checking inbox                      |
| SDL_PollEvent()            | Non-blocking, returns false if queue is empty           | Checking mail, not waiting for mail |
| Why not `SDL_WaitEvent()`? | That one _does_ block, useful for static UIs, not games | Waiting at the mailbox              |

# ================================================================================================================

# **“Heartbeat Loop Visualizer”**

- The SDL2 demo that literally _shows_ what’s happening inside both loops.
- This is a pretty cool visualization tool because it's terminal based and as it runs along side a "window" or "gui" it shows that there is activity even when the window looks static.
- So we run it alongside the SDL window and we should still see life in the SDL2 window.

---

## 🧩 File: `event_loop_debug.cpp`

```cpp
#include <SDL.h>
#include <iostream>
#include <string>

// Optional helper to turn event types into readable names
std::string eventName(Uint32 type) {
    switch (type) {
        case SDL_QUIT: return "SDL_QUIT";
        case SDL_KEYDOWN: return "SDL_KEYDOWN";
        case SDL_KEYUP: return "SDL_KEYUP";
        case SDL_MOUSEBUTTONDOWN: return "SDL_MOUSEBUTTONDOWN";
        case SDL_MOUSEBUTTONUP: return "SDL_MOUSEBUTTONUP";
        case SDL_MOUSEMOTION: return "SDL_MOUSEMOTION";
        default: return "OTHER";
    }
}

int main() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window* window = SDL_CreateWindow(
        "Event Loop Debugger",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        600, 400, 0);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    bool running = true;
    SDL_Event e;
    int frame = 0;

    std::cout << "🚀 Starting event loop debugger...\n";
    std::cout << "(Press keys, move mouse, or close window to quit)\n\n";

    // Main game loop
    while (running) {
        frame++;
        int eventCount = 0;

        // --------------------------------------------------------
        // INNER LOOP — Poll all events this frame
        // --------------------------------------------------------
        while (SDL_PollEvent(&e)) {
            eventCount++;
            std::cout << "  🔹 Event: " << eventName(e.type);

            // Show extra info for some events
            if (e.type == SDL_MOUSEMOTION)
                std::cout << "  (mouse moved to: " << e.motion.x << "," << e.motion.y << ")";
            else if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP)
                std::cout << "  (button " << (int)e.button.button
                          << " at " << e.button.x << "," << e.button.y << ")";
            else if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
                std::cout << "  (key: " << SDL_GetKeyName(e.key.keysym.sym) << ")";
            std::cout << "\n";

            if (e.type == SDL_QUIT)
                running = false;
        }

        // --------------------------------------------------------
        // OUTER LOOP — Happens once per frame
        // --------------------------------------------------------
        std::cout << "Frame #" << frame
                  << " — processed " << eventCount << " event(s)\n";

        // Visual feedback (clear screen)
        SDL_SetRenderDrawColor(renderer, 30, 30, 50, 255);
        SDL_RenderClear(renderer);
        SDL_RenderPresent(renderer);

        SDL_Delay(500); // Slow down frames for easy visualization
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
```

---

## 🧠 What It Teaches Visually

| Action       | Console Output                                                         |
| ------------ | ---------------------------------------------------------------------- |
| Do nothing   | `Frame #5 — processed 0 event(s)`<br>`Frame #6 — processed 0 event(s)` |
| Move mouse   | 🔹 `SDL_MOUSEMOTION (mouse moved to: 311,220)`                         |
| Click mouse  | 🔹 `SDL_MOUSEBUTTONDOWN` / `SDL_MOUSEBUTTONUP`                         |
| Press key    | 🔹 `SDL_KEYDOWN (key: W)` / `SDL_KEYUP (key: W)`                       |
| Close window | 🔹 `SDL_QUIT` → program exits                                          |

---

### 🧩 Teaching Moment

Now you can literally show them:

- The **outer loop** keeps ticking even when nothing happens.
- The **inner loop** is empty until there’s input.
- Events appear in bursts between frames.
- The program _is never stuck waiting_ — it’s alive and scanning constantly.

---

### 🧪 Optional tweak for fun

If you want to visualize frames **in the SDL window**, just render a rectangle whose color changes every frame.  
Students will _see the heartbeat_ visually even when no input happens.

Would you like me to add that “pulsing heartbeat” visual next (so they see both terminal logs **and** on-screen frame changes)?
