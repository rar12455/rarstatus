# rarstatus

**A performance-oriented, Display Server agnostic and modern re-implementation of slstatus.**

`rarstatus` is a minimalist status monitor written in C, designed to be lightweight and fast. It follows the philosophy of "Doing one thing well" by fetching system information through direct Linux system calls and efficient file parsing, making it ideal for tiling window managers like `dwl` or `dwm`.

## 🚀 Key Goals

* **Performance:** Minimize CPU cycles by using direct syscalls where possible (e.g., `statvfs`, `uname`).
* **Agnosticism:** Designed to output to `stdout`, allowing it to work with any display server (Wayland/X11) or status bar that accepts piped input.
* **No Bloat:** Avoids complex memory management (`malloc`) and advanced pointers to remain stable and predictable.

## 🛠 Current Features

The following modules are currently implemented and functional:

* **Memory (RAM):** Parses `/proc/meminfo` to calculate available memory.
* **Disk Usage:** Uses the `statvfs` syscall to calculate used space by subtracting available blocks from total blocks.
* **Kernel Version:** Uses the `uname` syscall to retrieve the `release` string directly from the kernel.
* **Battery:** Reads capacity directly from `/sys/class/power_supply/`.
* **Uptime:** Calculates system uptime in a human-readable format.
* **DateTime:** Highly customizable date and time formatting.

## ⚙️ How It Works

Internally, `rarstatus` uses a modular approach where each system metric is fetched by a dedicated function:

1. **Syscall Execution:** Functions like `getkernelversion()` call the Linux kernel directly via `uname()`.
2. **Data Processing:** Raw byte values are passed to `print_human_readable_data()`, which handles conversion to KiB, MiB, or GiB dynamically.
3. **Output Decoration:** The `decorate()` function manages separators between modules without unnecessary string concatenation.

## 🔧 Installation & Configuration

Configuration is handled at compile-time via `config.h`.

1. **Clone the repo:**
```bash
git clone https://github.com/rar12455/rarstatus.git
cd rarstatus

```


2. **Edit `config.h**` to change the update interval, separators, or formatting strings.
3. **Build:**
```bash
gcc main.c -o rarstatus

```



### Usage

To use `rarstatus` with a Wayland compositor like `dwl`:

```bash
./rarstatus | dwl

```

Or for X11-based `dwm` using `xsetroot`:

```bash
while true; do xsetroot -name "$(./rarstatus)"; sleep 1; done

```

## 🤝 Contributing

Since this is a hobbyist project, contributions are welcome. If you have a more efficient way to parse `/proc` or a new syscall-based module, feel free to open a Pull Request.

## 📜 License

This project is licensed under the **GPL v3** License - see the LICENSE file for details.
