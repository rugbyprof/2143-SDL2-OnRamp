# 🧩 `09_Centering_Shapes.md`

### 🧩 Topic: Centering Shapes (Relative Position)

Minimal snippet showing how to draw shapes centered on the screen or another object.

**Essential Snippet**

```cpp
int screenW = 800;
int screenH = 600;
SDL_Rect box{screenW/2 - 40, screenH/2 - 40, 80, 80};
```

**Concepts**

- SDL’s coordinate system starts at the **top-left corner (0, 0)**.
- To center an object, offset its top-left corner by half the window size minus half the object’s size.
- Works for both X and Y axes.
- You can reuse the same math to center objects on other shapes, text, or the mouse.

**Common Use**

```cpp
// Center a rectangle of width=100, height=60 on the screen
SDL_Rect rect;
rect.w = 100;
rect.h = 60;
rect.x = screenW/2 - rect.w/2;
rect.y = screenH/2 - rect.h/2;
```

**Teaches**

- Spatial reasoning using coordinates and dimensions.
- Relationship between **anchor point** and **object size**.
- Why centering isn’t just dividing by two — you must account for the object’s own size.
- Prepares students for future work with cameras, UI layouts, and transformations.

**Mini Challenge**

> Center a rectangle in your window.  
> Resize the window — can you keep the rectangle centered dynamically?  
> Bonus: make it follow the mouse but stay centered around the cursor instead of top-left aligned.
