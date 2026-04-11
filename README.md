# rarstatus

**A performance-oriented, Display Server agnostic, modern implementation of slstatus.**

`rarstatus` is a minimalist status monitor written in C, designed to be lightweight and fast. It follows the philosophy of "Doing one thing well" by fetching system information through direct Linux system calls and efficient file parsing, making it ideal for tiling window managers like `dwl` or `dwm`.

##  Key Goals

* **Performance:** Minimize CPU cycles by using direct syscalls where possible (e.g., `statvfs`, `uname`).
* **Agnosticism:** Designed to output to `stdout`, allowing it to work with any display server (Wayland/X11) or status bar that accepts piped input.
* **No Bloat:** Avoids complex memory management (`malloc`) and advanced pointers to remain stable and predictable.

##  Current Features

The following modules are currently implemented and functional:

* **Memory (RAM):** Parses `/proc/meminfo` to calculate available memory.
* **Disk Usage:** Uses the `statvfs` syscall to calculate used space by subtracting available blocks from total blocks.
* **Kernel Version:** Uses the `uname` syscall to retrieve the `release` string directly from the kernel.
* **Battery:** Reads capacity directly from `/sys/class/power_supply/`.
* **Uptime:** Calculates system uptime in a human-readable format.
* **DateTime:** Highly customizable date and time formatting.
* **Hostname**: print hostname using efficient a syscall. 
* **Brightness**: print Brightness value or percentage by parsing brightness file.
* **Cat a file**: print a arbituary file as you wish.
* **Run command**: print output of the command as you wish.
* **Cpu usage**: print cpu usage in percantage.

##  How It Works

Internally, `rarstatus` uses a modular approach where each system metric is fetched by a dedicated function:

1. **Syscall Execution:** Functions like `getkernelversion()` call the Linux kernel directly via `uname()`.
2. **Data Processing:** Raw byte values are passed to `print_human_readable_data()`, which handles conversion to KiB, MiB, or GiB dynamically.
3. **Output Decoration:** The `decorate()` function manages separators between modules without unnecessary string concatenation.

## Compatibility & Supported Operating Systems

### Supported operating systems

'rarstatus' (currently) only works on GNU/Linux systems,while it doesn't have a major linux-spesific dependency, some components needs to rewritten to be usable on respected UNIX-like operating systems (such as BSD's). The OpenBSD support is planned and likely, it will be ready in a short ammount of time.

### Libc and display server compatibility

'rarstatus' is also musl-libc compatible,this makes it also a good candidate for static linking, which is **recommended**, it also supports Wayland/X11 out of the box without any configuration, virtually any system has a working STDIN/STDOUT, can access system information.

As the table seen below summarizes the information:

| Feature | Status |
| :--- | :--- |
| **Musl/Glibc** | Works ✅ |
| **Wayland/X11** | Works ✅ |
| **BSD support?** | Mostly broken ❌ |
| **OpenBSD support?** | Planned ⚠️ |

##  Installation & Configuration

Configuration is generally handled at compile-time via `config.h` but you can configure `main.c` which is where main logic exists.

1. **Clone the repo:**
```bash
git clone https://github.com/rar12455/rarstatus.git
cd rarstatus

```


2. **Edit `config.h` or `main.c` to change the update interval, separators, etc.**
3. **Build:**
```bash
sudo make clean install

```



### Usage

To use `rarstatus` with a Wayland compositor like `dwl`:

```bash
./rarstatus | dwl

```

Or for X11-based `dwm` using `xsetroot`:

```bash
while true; do xsetroot -name "$(./rarstatus)"; done

```

##  Contributing

Since this is a hobbyist project, contributions are welcome. If you have a more efficient way to parse `/proc` or a new syscall-based module, feel free to open a Pull Request.

##  License

**NOTE:** This project is inspired by the modularity of slstatus, but it is written from scratch for performance and display-server agnosticism, thus it does not include **ISC License** notice.
This project is licensed under the **GPL v3** License - see the LICENSE file for details.
