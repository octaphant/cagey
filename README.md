# Cage: a Wayland kiosk, with input emulation

## Important notice!
This program is still in the early stages of development! It is **not functional**, let alone stable. Do not use it until more work has been done!

## Rationale
The loss of `xdotool` has been widely bemoaned since Wayland has grown more popular. Alternatives such as [ydotool](https://github.com/ReimuNotMoe/ydotool) have sprung up, but they create kernel input devices to emulate input to the compositor. While this solution is functional, in this developer's humble opinion, it is quite flawed for the following reasons:

1. Elegance: Creating a virtual uinput device is a low-level operation that affects the entire system. For automating tasks within the confines of a single graphical environment, and often on a single application, it is excessive; furthermore, it has the potential to create unintended side-effects.
2. Security: This method sends arbitrary inputs to the system as if through a real keyboard and mouse. This poses the same risks as did the APIs leveraged by xdotool, which led to their exclusion from the Wayland protocol. This is, again, especially serious in the case of input emulation on a single application, wherein inputs may be sent to the rest of the graphical environment, or even to the virtual console. Furthermore, it requires components of the program to run as root, which is disastrous if any exploit were to be discovered.

## Cagey's solution
Cagey aims to resolve both of these problems for the single-application use case. It consists of a modified version of the cage kiosk compositor, which exposes an IPC socket that allows input events to be sent to the program within. Because it is an isolated compositor, it is completely impossible for these events to be received by any program other than the intended recipient. The entire setup is completely rootless, and can be easily used on a pre-existing graphical environment via cage's pre-existing nested mode.

## Building and running

Cagey has exactly the same dependencies as cage; see its README for details.

The build process is the same, as well:

```
$ meson setup build
$ meson compile -C build
```

By default, this builds a debug build. To build a release build, use `meson
setup build --buildtype=release`.

You can run Cagey by running `./build/cagey APPLICATION`. It will launch in nested mode if you are already in a graphical session, and directly on the display if not. 
In debug mode (default build type with Meson), press <kbd>Alt</kbd>+<kbd>Esc</kbd> to quit. 

Please be aware that this functionality is not available in release builds. If you accidentally launch such a build on a virtual console without the `-s` option to enable virtual terminal switching, there is **no way** to exit it other than closing the application through its own interface, if possible.
Should that be impossible, you will unfortunately forced to use the magic SysRq key or physical power button.

For more configuration options, see
[Configuration](https://github.com/octaphant/cagey/wiki/Configuration) (WIP).

## Bugs

For any bug, please [create an
issue](https://github.com/octaphant/cagey/issues/new) on
[GitHub](https://github.com/octaphant/cagey). 

Please note that any issues submitted before the software is actually completed will be ignored, as it is not meant for use in its present state.

## License

Please see
[LICENSE](https://github.com/octaphant/cagey/blob/master/LICENSE) on
[GitHub](https://github.com/octaphant/cagey).

## Credits
Cage is copyright © 2018-2020 Jente Hidskes <dev@hjdskes.nl>. It is used in accordance with its license.

The idea for IPC-based input emulation was inspired by the [Hyprland](https://github.com/hyprwm/Hyprland) project, which implements the possibility for it.
