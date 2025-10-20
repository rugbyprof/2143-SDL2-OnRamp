# Capture Mouse Input

- Below is the **bare minimum** needed to capture and interpret a mouse click in SDL2.
- This only has the _essential snippets_, not a working program.

---

## What Are Events

Oh yeah — SDL2 absolutely gives you **granular event detail** for both **mouse** and **keyboard** input.  
It’s one of the things that makes SDL2 feel lower-level but still sane — you can catch everything from _press_ to _release_ to _hold_, even relative motion and wheel scrolling.

Let’s break it down 👇

---

### 🖱️ Mouse Events (Granular Detail)

| Event Type            | Trigger                                 | Key Fields                                                                     | Notes                                                    |
| --------------------- | --------------------------------------- | ------------------------------------------------------------------------------ | -------------------------------------------------------- |
| `SDL_MOUSEBUTTONDOWN` | When a mouse button is **pressed down** | `e.button.button`, `e.button.x`, `e.button.y`                                  | Happens once per click _down_.                           |
| `SDL_MOUSEBUTTONUP`   | When a mouse button is **released**     | same fields                                                                    | Happens once per click _release_.                        |
| `SDL_MOUSEMOTION`     | When the mouse moves                    | `e.motion.x`, `e.motion.y`, `e.motion.xrel`, `e.motion.yrel`, `e.motion.state` | Captures continuous movement and which buttons are held. |
| `SDL_MOUSEWHEEL`      | When the wheel scrolls                  | `e.wheel.y` (1 = up, -1 = down)                                                | Works on most modern mice and trackpads.                 |

#### Example

```cpp
SDL_Event e;
while (SDL_PollEvent(&e)) {
    switch (e.type) {
        case SDL_MOUSEBUTTONDOWN:
            printf("Mouse button %d pressed at (%d,%d)\n",
                   e.button.button, e.button.x, e.button.y);
            break;
        case SDL_MOUSEBUTTONUP:
            printf("Mouse button %d released at (%d,%d)\n",
                   e.button.button, e.button.x, e.button.y);
            break;
        case SDL_MOUSEMOTION:
            printf("Mouse moved to (%d,%d)\n", e.motion.x, e.motion.y);
            break;
    }
}
```

---

### 🎹 Keyboard Events (Granular Detail)

| Event Type                | Trigger                                   | Key Fields                          | Notes                                        |
| ------------------------- | ----------------------------------------- | ----------------------------------- | -------------------------------------------- |
| `SDL_KEYDOWN`             | When a key is **pressed down**            | `e.key.keysym.sym`                  | Also gives modifier keys (Ctrl, Shift, etc.) |
| `SDL_KEYUP`               | When a key is **released**                | same fields                         |                                              |
| (optional) `e.key.repeat` | true if the OS repeats the key while held | helps detect "hold" vs single press |

#### Example

```cpp
while (SDL_PollEvent(&e)) {
    if (e.type == SDL_KEYDOWN) {
        if (e.key.repeat == 0) // ignore repeats if you want
            printf("Key down: %s\n", SDL_GetKeyName(e.key.keysym.sym));
    }
    else if (e.type == SDL_KEYUP) {
        printf("Key up: %s\n", SDL_GetKeyName(e.key.keysym.sym));
    }
}
```

---

## 🧩 Event Constants Overview

| Category              | Examples                                                                        |
| --------------------- | ------------------------------------------------------------------------------- |
| Window                | `SDL_WINDOWEVENT`, `SDL_QUIT`                                                   |
| Keyboard              | `SDL_KEYDOWN`, `SDL_KEYUP`, `SDL_TEXTINPUT`                                     |
| Mouse                 | `SDL_MOUSEMOTION`, `SDL_MOUSEBUTTONDOWN`, `SDL_MOUSEBUTTONUP`, `SDL_MOUSEWHEEL` |
| Joystick / Controller | `SDL_JOYAXISMOTION`, `SDL_CONTROLLERBUTTONDOWN`, etc.                           |
| App / Focus           | `SDL_APP_DIDENTERBACKGROUND`, `SDL_WINDOWEVENT_FOCUS_GAINED`                    |

---

## 🧠 Mouse Event Notes

Usually these methods are captured (especially for out GOL project)

- Handle **`SDL_MOUSEBUTTONDOWN`** for clicks
- Handle **`SDL_MOUSEBUTTONUP`** if you care about drag or release timing (this obviously combines with mouse move(motion))
- Handle **`SDL_MOUSEMOTION`** for hover/drag logic
- Handle **`SDL_KEYDOWN` / `SDL_KEYUP`** for keyboard controls

…and suddenly you’ve got all the interaction primitives you’ll ever need for a game, UI, or simulation.

---

Would you like a quick example where we capture both **mouse down + up** and **keyboard hold detection** (e.g. WASD movement while key is held)? That’s a killer next lecture snippet.

### 🧩 1️⃣ Declare an Event Variable

Below is a simple type that captures all events and places the event in `e`, which we then test to see what happened. See below.

```cpp
SDL_Event e;
```

---

### 🧩 2️⃣ Poll for Events

```cpp
while (SDL_PollEvent(&e)) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        // handle click here
    }
}
```

---

### 🧩 3️⃣ Get Mouse Coordinates

```cpp
int x = e.button.x;
int y = e.button.y;
```

---

### 🧩 4️⃣ (Optional) Identify Button Pressed

```cpp
if (e.button.button == SDL_BUTTON_LEFT) { /* left click */ }
if (e.button.button == SDL_BUTTON_RIGHT) { /* right click */ }
```

---

### 🧠 Summary (Minimum Viable Pattern)

```cpp
SDL_Event e;
while (SDL_PollEvent(&e)) {
    if (e.type == SDL_MOUSEBUTTONDOWN) {
        int x = e.button.x;
        int y = e.button.y;
        // use x, y however you like
    }
}
```
