# wlclipblock

A hack to prevent Wayland compositors from advertising support for the primary clipboard (aka "primary selection").

This only takes care of hiding the `zwp-primary-selection-device-manager-v1` protocol.

`wlr-data-control-unstable-v1` and Xwayland are unaffected.

## How to use

Add `/usr/lib/libwlclipblock.so` to `/etc/ld.so.preload`.

If you use Firefox, you might also want to use [gtkclipblock](https://github.com/notpeelz/gtkclipblock) to work around [this bug](https://bugzilla.mozilla.org/show_bug.cgi?id=1791417).

## Install from package

Available on the [AUR](https://aur.archlinux.org/packages/wlclipblock).

## Install from source

```sh
meson setup --prefix=/usr/local build
meson install -C build
```
