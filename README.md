# Commander OS

**Commander** is (meant to be) a toy operating system written from scratch.

## General idea

- lets the user do anything

## Design goals

- preemptive scheduling
- monolithic with loadable modules
- everything in ring 0
- (ideally) architecture independence

## Build systems

Individual components (kernel, apps) are built with Meson.

To build the Commander OS distribution (bootloader, initrd, rootfs), we use the Nix package manager.
