![SquachWare](https://user-images.githubusercontent.com/16942638/211815956-4dd70fca-97d8-49c5-a98b-08f2c7fa8786.jpg)


# SquachWare Community Firmware
SquachWare is a community driven firmware!  Our goal is to creat a firmware that has 98% of the functionality of other custom firmwares, but also be 100% legal in the process!  After having use all of the other custom firmwares, we realized that most people don't even use features that require unlocking the region lock, and we certainly don't want to include illegal addon files!  Enjoy a stable branch of the Developer branch of Official Firmware, packed with custom graphics, applications, badUSB files, IR files, SubGhz files and more!!!

FULL DOCUMENTATION INCLUDING LINKS TO ALL AUTHORS WILL BE DONE SHORTLY.
Right now I'm just getting the basics all sorted out!

# Flipper Zero Firmware

- [Flipper Zero Official Website](https://flipperzero.one). A simple way to explain to your friends what the Flipper Zero can do
- [Flipper Zero Firmware Update](https://update.flipperzero.one). Improvements for your dolphin: latest firmware releases, upgrade tools for PC and Mobile devices
- [User Documentation](https://docs.flipperzero.one). Learn more about your dolphin: specs, usage guides, and everything that you wanted to ask

# Contributing

If you'd like to contribute to this project, the best way to start would be to join the Squachtopia Hangout Discord server! https://discord.gg/squachtopia

## I need help

The best place to search for answers is our [User Documentation](https://docs.flipperzero.one). If you can't find the answer there, you can check our [Discord Server](https://flipp.dev/discord) or our [Forum](https://forum.flipperzero.one/).


Supported development platforms:

- Windows 10+ with PowerShell and Git (x86_64)
- macOS 12+ with Command Line tools (x86_64, arm64)
- Ubuntu 20.04+ with build-essential and Git (x86_64)

Supported in-circuit debuggers (optional but highly recommended):

- [Flipper Zero Wi-Fi Development Board](https://shop.flipperzero.one/products/wifi-devboard)
- ST-Link
- J-Link

Everything else will be taken care of by Flipper Build System.

## Cloning Source Code

Ensure that you have enough space and clone source code with Git:

```shell
git clone --recursive https://github.com/skizzophrenic/SquachWare-CFW.git

## Building

Build firmware using Flipper Build Tool:

```shell
./fbt
```

## Flashing Firmware using an in-circuit debugger

Connect your in-circuit debugger to the Flipper and flash firmware using Flipper Build Tool:

```shell
./fbt flash
```

## Flashing Firmware using USB

Ensure that your Flipper is working, connect it using a USB cable and flash firmware using Flipper Build Tool:

```shell
./fbt flash_usb
```

## Documentation

- [Flipper Build Tool](/documentation/fbt.md) - building, flashing, and debugging Flipper software
- [Applications](/documentation/AppsOnSDCard.md), [Application Manifest](/documentation/AppManifests.md) - developing, building, deploying, and debugging Flipper applications
- [Hardware combos and Un-bricking](/documentation/KeyCombo.md) - recovering your Flipper from most nasty situations
- [Flipper File Formats](/documentation/file_formats) - everything about how Flipper stores your data and how you can work with it
- [Universal Remotes](/documentation/UniversalRemotes.md) - contributing your infrared remote to the universal remote database
- [Firmware Roadmap](/documentation/RoadMap.md)
- And much more in the [Documentation](/documentation) folder

# Links

- Discord: https://discord.gg/squachtopia
- Website: http://talkingsasquach.com (soon)


# Project structure

- `applications`    - Applications and services used in firmware
- `assets`          - Assets used by applications and services
- `furi`            - Furi Core: OS-level primitives and helpers
- `debug`           - Debug tool: GDB-plugins, SVD-file and etc
- `documentation`   - Documentation generation system configs and input files
- `firmware`        - Firmware source code
- `lib`             - Our and 3rd party libraries, drivers, etc.
- `scripts`         - Supplementary scripts and python libraries home

Also, pay attention to `ReadMe.md` files inside those directories.
