[![GitHub license](https://img.shields.io/github/license/jupiteer/JupiteerOS)](https://github.com/jupiteer/JupiteerOS/blob/master/LICENSE)
[![GitHub stars](https://img.shields.io/github/stars/jupiteer/JupiteerOS)](https://github.com/jupiteer/JupiteerOS/stargazers)
[![GitHub forks](https://img.shields.io/github/forks/jupiteer/JupiteerOS)](https://github.com/jupiteer/JupiteerOS/network)
# JupiteerOS
Experimental Operating System (by @furkanonder)

## Notes
The original repository is removed from GitHub. And I wanted to share this really instructive OS with you again.

JupiteerOS is a good starting point for the beginners who wants to get into kernel hacking and deep dive into x86 architectural structures.

I've made an easy PS/2 keyboard patch in the kernel_main.c file, so the keyboard is working now. It was a really easy fix.
## Build requirements
In order to build JupiteerOS, make sure to have the following installed:
- Bash
- GNU Make
- GCC (i686-elf-gcc is preferred) 
- NASM
- QEMU (to test it)

### Build
```
make
```
### Build as an ISO file
```
make iso (Uses xorriso to do its trick.)
```
### Run in QEMU
```
make run
```
### Run in Bochs
```
make bochs
```
After running bochs, type "c" to start it.

### V0.11
* Programmable Interrupt Controller 
* Programmable Interval Timer
* Keyboard Driver

  Live Test: https://www.youtube.com/watch?v=e0YiMWGrxLo

### V0.1
* GRUB bootloader
* Global and Interrupt Descriptor Table
* ISR handler

  Live test:https://www.youtube.com/watch?v=uwXuIsBbxJ0

### References
* https://wiki.osdev.org/
