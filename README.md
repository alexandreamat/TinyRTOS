# 🐝 TinyRTOS 


TinyRTOS is an operating system designed for small embedded systems.
It is a lightweight implementation of a small fraction of POSIX and focuses on real-time services.
The purpose of this project is educational, as it touches upon critical concepts of Computer Science.

# 🧩 Features

The project is organised as a collection of software modules.
This is the directory tree structure:

```
TinyRTOS
├── Makefile                // Makefile
├── README.md               // This file
├── arch                    // Hardware-specific code (lower-level)
├── include                 // Common headers
│   ├── hal                 // Hardware Abstraction Layer, implemented in arch
│   │   ├── delay.h         // CPU delay
│   │   ├── gpio.h          // GPIO manipulation
│   │   ├── interrupts.h    // CPU interrupts
│   │   ├── serial_io.h     // Implementation of standard input/output
│   │   └── timer_core.h    // Hardware timer
│   ├── kernel              // OS kernel code
│   │   ├── sched.h         // Threads scheduler
│   │   └── timer.h         // Software timers
│   ├── libc                // libc implementations
│   │   └── time.h          // <time.h> implementation
│   ├── peripherals         // Optional peripherals
│   │   └── hd44780u.h      // LCD display
│   ├── posix               // POSIX API implementation
│   │   ├── pthread.h       // <pthread.h> library implementation
│   │   └── unistd.h        // <unistd.h> library implementation
│   └── utils               // Tools and basic data structures
│       ├── min_heap.h      // Min-heap implementation
│       ├── morse.h         // Morse code implementation on LED
│       └── queue.h         // Array-based queue
└── src                     // Common source code (higher-level)
    ...                     // (mimics include directories)
    └── main.c              // OS main entry point
```


The `arch` directory contains lower-level hardware-specific code that abstracts the details of the underlying hardware.
This abstraction is achieved by implementing of a Hardware Abstraction Layer (HAL).
The HAL is a set of software functions that encapsulate the low-level hardware details and provide a consistent interface to the rest of the system.

The `include` and `src` directories contain higher-level code used by the system, which does not depend on the platform.

 - `kernel`: The OS kernel code and the `libc` directory contains the implementation of standard C library functions, such as `clock()`
 - `posix`: Implementation of the Portable Operating System Interface (POSIX) API, which provides a standardised API for software running on different operating systems; this is a wrapper around kernel functions
 - `libc`: Implementation of ISO C functions that require support from the OS
 - `utils` Basic data structures and algorithms used by the system; for instance, queues, heaps, lists, and hash maps belong here


Overall, TinyRTOS is designed to provide a platform-agnostic OS that abstracts the hardware details, making it easier to develop software that runs on different embedded systems.

## 🗺️ Roadmap 

Here's a high-level overview of the features we plan to implement in our TinyRTOS:

|     | Feature               | State |                                Description                                 |
| --- | :-------------------- | :---: | :------------------------------------------------------------------------: |
| 💬   | Serial I/O            |   ✅   | Availability of functions like `printf`, `putchar`, `puts`, `putc`, `gets` |
| 🚥   | GPIO access           |   ✅   |             Set, clear, toggle, and enable interrupts for GPIO             |
| 🕰️   | Timers                |   🏗️   |                Schedule tasks to be executed in the future                 |
| 🔁   | Round-robin Scheduler |   🏗️   |   Execution concurrency with multi-threading using the time-slice method   |
| 💤   | Sleep                 |   🏗️   |                  Put tasks to sleep for an amount of time                  |
| 🚦   | Semaphores            |   ❌   |                           Mutexes and semaphores                           |
| 🔝   | Priority Scheduler    |   ❌   |                       Add priorities to the threads                        |

This is a partial list, but it should give you an idea of the project's direction.
Feature requests are welcome!

# 💾 Hardware support

Currently, TinyRTOS supports the ARM BCM2711 (Raspberry Pi) and AVR ATmega328p (Arduino UNO).

These have been chosen for their availability, community, and development ease, although none of the official OS or libraries are used, apart from the ones provided by the toolchain.

Apart from these, virtually any hardware with timer features could support it.

| Architecture |    CPU     | GPIO  | Interrupts | Serial I/O | Timer Core |
| :----------: | :--------: | :---: | :--------: | :--------: | :--------: |
|    `avr`     | ATmega328p |   ✅   |     ✅      |     ✅      |     ✅      |
|  `aarch64`   |  BCM-2711  |   ✅   |     ✅      |     ✅      |     🏗️      |


More architectures are welcome via PR!

# 💿 Installation

After following these steps, you can run `make` to compile the code.

## AVR (Arduino UNO)

- Get an Arduino UNO, which comes with the ATmega328p and a USB cable
- Get the [toolchain](https://www.microchip.com/en-us/tools-resources/develop/microchip-studio/gcc-compilers)
- Get the [programmer](https://www.nongnu.org/avrdude/)
- Get a serial terminal, like [PuTTY](https://www.putty.org), [Serial Monitor](https://marketplace.visualstudio.com/items?itemName=ms-vscode.vscode-serial-monitor), or Unix `screen`
- Set the env var `TARGET` to `avr/atmega328p`

## ARM (Raspberry Pi 4)

- Get a Raspberry Pi 4, an Micro SD card, and an SD card adapter
- Download the [Raspberry Pi Imager](https://www.raspberrypi.com/software/)
- Get the [toolchain](https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads)
- Follow the instructions to flash Raspberry Pi OS lite
- Delete any files containing the string `kernel` from the resulting SD card image
- Delete the `config.txt` file
- Set the env var `TARGET` to `aarch64/bcm2711`

# 🤝 Let's Get in Touch!

If you have any questions, feedback or just want to say hi, feel free to contact me! 📩

- ✉️ Drop me an email at alex.amat AT hotmail.com
- 💼  Connect with me on [LinkedIn](linkedin.com/in/amatalexandre) and let's expand our network! 

