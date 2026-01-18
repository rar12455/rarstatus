# rarstatus:

A performance-oriented, Display Server agnostic, and modern re-implementation of slstatus.

rarstatus is a minimalist status monitor written in C, designed to be lightweight and fast. It follows the philosophy of "Doing one thing well" by fetching system information through direct Linux system calls and efficient file parsing, making it ideal for tiling window managers like dwl or dwm.

# 🚀 Key Goals

    Performance: Minimize CPU cycles by using direct syscalls where possible (e.g., statvfs, uname).

    Agnosticism: Designed to output to stdout, allowing it to work with any display server (Wayland/X11) or status bar that accepts piped input.

    No Bloat: Avoids complex memory management (malloc) and advanced pointers to remain stable and predictable for hobbyists and power users alike.

# 🛠 Current Features

The following modules are currently implemented and functional:

    Memory (RAM): Parses /proc/meminfo to calculate used memory in GiB.

    Disk Usage: Uses the statvfs syscall to report used space on the root filesystem.

    Kernel Version: Uses the uname syscall to retrieve the current Linux release.

    Battery: Reads capacity directly from /sys/class/power_supply/.

    Uptime: Reports system uptime in hours and minutes.

    DateTime: Highly customizable date and time formatting using strftime.

# ⚙️ How It Works

rarstatus operates on a simple, infinite while(1) loop defined in main.c. It executes the selected modules, formats the output into a single string, and prints it to the terminal.

Unlike tools that rely on external shell scripts, rarstatus handles the logic internally, which significantly reduces the overhead of spawning new processes every second.

# 🔧 Installation & Configuration

Configuration is handled at compile-time via config.h.


git clone https://github.com/rar12455/rarstatus.git
cd rarstatus



Edit config.h to change the update interval or formatting.

Build:
Bash

    gcc main.c -o rarstatus

Usage:
To use it,simply pass it through using pipes in shell:
./rarstatus | dwl
or
./rarstatus | dwm

# 📜 License

This project is licensed under the GPL v3 License - see the LICENSE file for details.
