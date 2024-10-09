# simple_tray_program
#### An 85-lines code snippet demonstrating the use of a notification tray icon in a Win32 application.

---

## Screenshots
![](screenshots/startup%20dialog.png) \
![](screenshots/context%20menu.png) \
![](screenshots/about%20dialog.png) \
![](screenshots/multi-instance%20warning.png)

---

## Build Instructions
Using MSVC : \
`cl User32.lib Shell32.lib main.c /link /SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup` \
Using MinGW : \
`gcc -mwindows main.c -o main.exe`
