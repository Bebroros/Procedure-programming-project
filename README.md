# Procedure-programming-project

- Artem Shkilniuk: Bebroros
- Vysokovskykh Kateryna: Kvstkk
---
# Linux application for taking screenshots

Application which allows to take screenshots on linux systems. <br>

It runs in the background, captures and saves either full screen or single window screenshot, once hotkey provided.

---
## Set up enviroment

1. **Dependencies** 

- gcc
- xlib
- libpng 

Commands to install all(For Debian/Ubuntu):
   ```
   sudo apt update
   sudo apt install build-essential libx11-dev libpng-dev
   ```
2. **Compile**

   `make`

3. **Run app**

   `./app/screenshot_app`

4. **Hotkeys**

- Full screen: `Ctrl + Shift + 1`
- Single Window: `Ctrl + Shift + 3` *(point cursor on window)*
- Exit:`Ctrl+C`

Screenshots are saved in in current folder with filenames `screenshot_YEAR_MONTH_DAY_HOUR-MIN-SEC.png`

5. **Functions and key implementation details**

1. `struct image* make_fullscreen_screenshot()`
   1) Display is opened with XOpenDisplay()
   2) Get fullscreen window is opened with DefaultRootWindow() 
   3) Get window attributes with XGetWindowAttributes
   4) Get image of opened window and save into image struct
   After usage of this function it requires to free opened window and created image: `XCloseDisplay(image->display)` and `XDestroyImage(image->image_ptr)`

2. `struct image* make_window_screenshot()`
   1) Display is opened with XOpenDisplay()
   2) Get fullscreen window is opened with DefaultRootWindow() 
   3) Initialise required variables fo XQueryPointer() and call it
   4) Get window attributes of child window queried with XQueryPointer()  | If there is no window under pointer, then get attributes of whole screen
   5) Get image of window and save into image struct
   After usage of this function it requires to free opened window and created image: `XCloseDisplay(image->display)` and `XDestroyImage(image->image_ptr)`

3. `int convert_to_png(struct image *img, char *filename)`

   1) Create and open file for writing in write binary mode
   2) Initialize LibPNG structures
   3) Set up error handling with setjmp
   4) Configure PNG header with image width, height, and format
   5) Allocate memory for a single row of pixels
   6) Iterate through pixels: Read each pixel from XImage, extract Red/Green/Blue components using bitwise masks and shifts, and store them in the row buffer
   7) Write data row-by-row into the file using png_write_row
   8) Free all allocated memory destroy structures
   
4. `int main()`
   1) Grab key with XGrabKey of '1' and '3' with 'Shift | Ctrl' modifier
   2) Create event listener and wait for KeyPress
   3) When '1' or '3' is pressed, then call one of screenshot function
   4) PNG encode images returned
   5) Close Display and free Image which is required by make_screenshot functions
   6) If 'CTRL+C' pressed, ungrab keys '1' and '3' and close main display
