# rarstatus

A minimal, stdout-only system status printer for Linux. No Xlib. No Wayland deps.
Works with any bar or compositor that accepts piped input.

```
2026-05-02 21:42 | RAM:3.14 GiB | CPU:4% | DISK:42.1 GiB | BAT:87%+
```

## Why not slstatus?

slstatus pulls Xlib and writes directly to the X root window — it assumes you're
on X11 and using dwm. rarstatus just prints to stdout, so you can pipe it anywhere:
a Wayland bar, dwm via xsetroot, a script, a log file, whatever you want.

## Features

| Component | Function |
| :--- | :--- |
| CPU usage | `print_cpu_usage()` |
| RAM (used / free) | `getusedmeminfo()` / `getfreememinfo()` |
| Disk usage | `getuseddiskinfo()` |
| Battery | `readbatterycapacity()` |
| Uptime | `uptime()` |
| Date & time | `datetime()` |
| Hostname | `print_hostname()` |
| Brightness | `brightness()` |
| Print a file | `cat_a_file()` |
| Run a command | `run_command()` |

## Installation

```sh
git clone https://github.com/rar12455/rarstatus.git
cd rarstatus
```

Edit `config.h` to set paths (battery, brightness, etc.) and `main.c` to enable
the components you want, then build:

```sh
sudo make clean install
```

## Configuration

All configuration is done at compile time. Two files to know:

**`config.h`** — paths, intervals, separators:
```c
#define INTERVAL 1          /* update interval in seconds */
#define BATTERY_PATH "/sys/class/power_supply/BAT0/capacity"
static const char *separator = " | ";
```

**`main.c` / `main_loop()`** — uncomment the components you want:
```c
datetime(iso_format);
decorate(no_newline);
getusedmeminfo();
decorate(no_newline);
print_cpu_usage(0);
decorate(show_newline);
```

## Usage

### With dwm (X11) via xsetroot

```sh
while true; do xsetroot -name "$(rarstatus -1)"; sleep 1; done
```

Or run it in the background and let it loop on its own:

```sh
rarstatus | while read -r line; do xsetroot -name "$line"; done &
```

### With dwl or any Wayland bar (yambar, waybar custom module, etc.)
Just pipe or redirect stdout into whatever your bar expects.

```sh
rarstatus
```
### For dwl with bar.patch applied you can just pipe it:

```sh
rarstatus | dwl
```


### One-shot output (for scripts)

```sh
rarstatus -1
```

## Compatibility

| | Status |
| :--- | :--- |
| glibc | ✅ |
| musl libc | ✅ |
| X11 | ✅ |
| Wayland | ✅ |
| BSD | ❌ (uses `/proc` and `sysinfo()`) |

rarstatus is Linux-only. Several components depend on `/proc/` and `sysinfo()`.
BSD support would require rewriting those components.

## Contributing

Contributions welcome, new components, bug fixes, or BSD porting work.
Keep it minimal and dependency-free.

## License

GPL v3. See LICENSE.

---

*Inspired by the modularity of slstatus, written from scratch.*
