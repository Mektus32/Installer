# Program installer

---

## What is it?

It is installer with programs versions.
It has two programs: **server** and **client**.
1. Python server for storage archived programs
2. C++ client for downloading programs on a user pc.
---
## How to use?
1. Download git [repository](https://github.com/Mektus32/Installer.git). 
2. Open **client** directory and use CMakeLists.txt as a project.
3. Use flag `-DCMAKE_PREFIX_PATH=` and set path to `QT6`
4. After this open **python_server** directory and install required packages from requirements.txt
5. Set your `ip` and `path` for programs in **config.json**.
6. Use the following hierarchy in programs directory.  
   6.1. First level is used for directories that have program names  
   6.2. Second level needs for directories that have program version names  
   6.3. And in directories with version names you should keep yours `zip` files with program data
7. Change `ip` in client app(you can use find in files with `https:` match)
8. #### Start python server!
9. #### Build and start client!
10. Now you have **installer** and **server** with your programs.
