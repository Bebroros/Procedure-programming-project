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

By default, screenshots will be saved in `./app/screenshot_app` folder with filenames `screenshot_YEAR_MONTH_DAY_HOUR-MIN-SEC.png`