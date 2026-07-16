#!/usr/bin/env python3
"""Generate ``.inc.c`` files for ``CUSTOM_TEXTURES=1`` mode.

For each PNG texture file, create a ``.inc.c`` containing the PNG path as a
C byte array (matching the Makefile's ``hexdump -e '1/1 "0x%X,"'`` output).
"""

from __future__ import annotations

import os
import sys
from pathlib import Path

BUILD_DIR = "build/us_pc"

# Texture format suffixes recognised by the ``CUSTOM_TEXTURES=1`` pipeline.
# e.g. ``texture.rgba16.png``, ``data.ia8.png``.
TEXTURE_FORMATS: tuple[str, ...] = (
    "rgba16",
    "ia16",
    "ia8",
    "ia4",
    "ia1",
    "i8",
    "i4",
    "ci8",
    "ci4",
)

# Source trees scanned for ``*.png`` textures.
TEXTURE_SEARCH_DIRS: tuple[str, ...] = ("actors", "textures", "levels")

# Binary sound assets copied verbatim into ``.inc.c`` byte arrays.
SOUND_SOURCES: tuple[tuple[str, str], ...] = (
    ("sound/sound_data.ctl", "sound/sound_data.ctl.inc.c"),
    ("sound/sound_data.tbl", "sound/sound_data.tbl.inc.c"),
    ("sound/sequences.bin", "sound/sequences.bin.inc.c"),
)


def path_to_byte_array(rel_path: str) -> str:
    """Encode a relative path as a C byte-array literal (trailing NUL included)."""
    path_bytes = rel_path.encode("ascii") + b"\x00"
    return "".join(f"0x{b:02X}," for b in path_bytes)


def generate_texture_inc(png_rel: str, output_root: Path) -> bool:
    """Write a ``.inc.c`` stub for one PNG texture. Returns ``True`` if written."""
    base = png_rel[:-4]  # strip ".png"
    inc_path = output_root / (base + ".inc.c")

    if inc_path.exists():
        return False

    inc_path.parent.mkdir(parents=True, exist_ok=True)
    byte_arr = path_to_byte_array(base.replace("\\", "/"))

    inc_path.write_text(byte_arr + "\n0x00\n")
    print(f"  Generated: {inc_path}")
    return True


def generate_sound_inc(source_root: Path, output_root: Path) -> int:
    """Emit ``.inc.c`` byte arrays for the binary sound assets."""
    count = 0
    for src_rel, dst_rel in SOUND_SOURCES:
        src_path = source_root / src_rel
        if not src_path.is_file():
            continue

        dst_path = output_root / dst_rel
        dst_path.parent.mkdir(parents=True, exist_ok=True)

        raw = src_path.read_bytes()
        encoded = ",".join(f"0x{b:02X}" for b in raw)
        dst_path.write_text(encoded + "\n")
        print(f"  Generated: {dst_path}")
        count += 1
    return count


def main() -> None:
    source_root = Path(sys.argv[1] if len(sys.argv) > 1 else os.getcwd()).resolve()
    output_root = (source_root / BUILD_DIR).resolve()

    print(f"Generating .inc.c files from PNG textures...")
    print(f"  Source root: {source_root}")
    print(f"  Output root: {output_root}")

    count = 0
    for search_dir in TEXTURE_SEARCH_DIRS:
        full = source_root / search_dir
        if not full.is_dir():
            continue
        for dirpath, _dirnames, filenames in os.walk(full):
            for fname in filenames:
                if not fname.endswith(".png"):
                    continue
                name_no_ext = fname[:-4]
                if any(name_no_ext.endswith("." + fmt) for fmt in TEXTURE_FORMATS):
                    rel = Path(dirpath).relative_to(source_root).as_posix()
                    png_rel = f"{rel}/{fname}"
                    if generate_texture_inc(png_rel, output_root):
                        count += 1

    count += generate_sound_inc(source_root, output_root)
    print(f"Done. Generated {count} .inc.c files.")


if __name__ == "__main__":
    main()
