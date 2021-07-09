[![Open in Visual Studio Code](https://open.vscode.dev/badges/open-in-vscode.svg)](https://open.vscode.dev/organization/repository)

# `bat_notify`

The battery-reporting superhero.

This reports if battery levels go over a threshold (if charging) or below another (if not charging).

## Dependencies

- Any Desktop which implements `libnotify (0.7.7+)`

## Build Dependencies

- `meson`: Meson Build System.
- `ninja`: For emitting Meson generation.
- `gcc`/`clang`: C Compiler.
- `libnotify-devel` or `libnotify-dev`: Development files for `libnotify`.

## Build Instructions

1. Configure the Build Directory

    ```bash
    meson setup _build
    ```
    
    NOTE: For `clang`, do the follwing:
    
    ```bash
    CC="clang" meson setup _build
    ```

2. Build `bat_notify`

    ```bash
    meson compile -C _build
    ```

3. The built binary can be found in `_build/bat_notify`.

    ```bash
    ./_build/bat_notify
    ```

## License

Copyright (C) 2021 Goutham Krishna K V

[MIT LICENSE](LICENSE)
