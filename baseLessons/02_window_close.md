🧩 `02_Window_Close_Event.md`

````markdown
---
title: SDL2 - Window Close (SDL_QUIT)
description: Minimal snippet showing how to detect and handle the window close (quit) event.
tags: [SDL2, Events, GameLoop, Quit]
---

### 🧩 Topic: Window Close (SDL_QUIT Event)

**Essential Snippet**

```cpp
SDL_Event e;
bool running = true;

while (running) {
    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT)
            running = false; // Exit main loop
    }
}
```
````

**Concepts**

- The **outer loop** keeps the program running.
- The **inner loop** checks for any pending SDL events.
- When you click the window’s close button (❌), SDL creates an `SDL_QUIT` event.
- Setting `running = false` breaks the outer loop and ends the program.

**Common Use**

```cpp
if (e.type == SDL_QUIT) {
    running = false;
    // Optional cleanup or save logic before exit
}
```

**Teaches**

- Program lifecycle control via events.
- Difference between ending a frame vs ending the entire application.
- That SDL doesn’t automatically exit—you choose when the loop stops.

**Student Prompt**

> Add this snippet to your existing grid or input project.  
> Try closing the window — confirm that it ends cleanly.  
> Then add a message like `std::cout << "Exiting..."` right before quitting.

```

---

Would you like me to continue with **Doc #3: Drawing a Rectangle (Minimal Rendering)** next?
That one introduces just the three rendering calls that every frame needs: clear → draw → present.
```
