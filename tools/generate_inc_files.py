#!/usr/bin/env python3
"""Generate .inc.c files for CUSTOM_TEXTURES=1 mode.
For each PNG texture file, creates an .inc.c containing the PNG path as a C byte array.
"""

import os
import sys
import json
import subprocess

BUILD_DIR = "build/us_pc"

def path_to_byte_array(path):
    """Convert a relative path to C byte array format (matches Makefile's hexdump -e '1/1 "0x%X,"')."""
    path_bytes = path.encode("ascii") + b"\x00"
    return "".join(f"0x{b:02X}," for b in path_bytes)

def generate_texture_inc(png_rel, output_root):
    """Generate .inc.c from a .png file (CUSTOM_TEXTURES=1 method)."""
    base = png_rel[:-4]  # strip .png
    inc_name = base + ".inc.c"
    inc_path = os.path.join(output_root, inc_name)

    if os.path.exists(inc_path):
        return

    os.makedirs(os.path.dirname(inc_path), exist_ok=True)

    # The "data" is the relative path without extension
    data_path = base.replace("\\", "/")
    byte_arr = path_to_byte_array(data_path)

    with open(inc_path, "w") as f:
        f.write(byte_arr)
        f.write("\n0x00\n")

    print(f"  Generated: {inc_path}")

def generate_sound_inc(png_rel, output_root):
    pass

def main():
    source_root = os.path.abspath(sys.argv[1]) if len(sys.argv) > 1 else os.getcwd()
    output_root = os.path.abspath(os.path.join(source_root, BUILD_DIR))

    print(f"Generating .inc.c files from PNG textures...")
    print(f"  Source root: {source_root}")
    print(f"  Output root: {output_root}")

    # Only process PNGs that have a texture format suffix (.rgba16, .ia16, etc.)
    # This matches the Makefile's pattern for CUSTOM_TEXTURES=1
    texture_formats = ("rgba16", "ia16", "ia8", "ia4", "ia1", "i8", "i4", "ci8", "ci4")
    search_dirs = ["actors", "textures", "levels"]
    count = 0
    for search_dir in search_dirs:
        full_path = os.path.join(source_root, search_dir)
        if not os.path.isdir(full_path):
            continue
        for dirpath, dirnames, filenames in os.walk(full_path):
            for f in filenames:
                # Check if the filename has a texture format extension before .png
                # e.g., "texture.rgba16.png", "data.ia8.png"
                name_without_ext = f[:-4] if f.endswith(".png") else f
                if any(name_without_ext.endswith("." + fmt) for fmt in texture_formats):
                    rel_dir = os.path.relpath(dirpath, source_root)
                    png_rel = os.path.join(rel_dir, f).replace("\\", "/")
                    generate_texture_inc(png_rel, output_root)
                    count += 1

    # Also handle the "sound" directory for .inc.c generation of binary data
    # (sound_data.ctl.inc.c etc.)
    sound_sources = [
        ("sound/sound_data.ctl", "sound/sound_data.ctl.inc.c"),
        ("sound/sound_data.tbl", "sound/sound_data.tbl.inc.c"),
        ("sound/sequences.bin", "sound/sequences.bin.inc.c"),
    ]
    for src_rel, dst_rel in sound_sources:
        src_path = os.path.join(source_root, src_rel)
        if not os.path.isfile(src_path):
            continue
        dst_path = os.path.join(output_root, dst_rel)
        os.makedirs(os.path.dirname(dst_path), exist_ok=True)
        with open(src_path, "rb") as sf:
            data = sf.read()
        with open(dst_path, "w") as df:
            first = True
            for b in data:
                if not first:
                    df.write(",")
                df.write(f"0x{b:02X}")
                first = False
            df.write("\n")
        print(f"  Generated: {dst_path}")
        count += 1

    print(f"Done. Generated {count} .inc.c files.")

if __name__ == "__main__":
    main()
