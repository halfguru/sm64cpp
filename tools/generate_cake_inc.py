#!/usr/bin/env python3
"""Generate levels/ending/cake.inc.c from a cake.png (or raw RGBA16 file).
The cake ending screen is 320x240 RGBA16, divided into 48 tiles of 80x20.

Usage (from PNG):
  python generate_cake_inc.py levels/ending/cake.png build/us_pc/levels/ending/cake.inc.c

Usage (from raw RGBA16):
  python generate_cake_inc.py cake.raw build/us_pc/levels/ending/cake.inc.c
"""

import os
import sys
import struct

TILE_W = 80
TILE_H = 20
COLS = 4   # 320 / 80
ROWS = 12  # 240 / 20


def rgba8_to_rgba16(r, g, b, a):
    """Convert 8-bit RGBA to 16-bit RGBA16 (1-5-5-1 format)."""
    r5 = r >> 3
    g5 = g >> 3
    b5 = b >> 3
    a1 = a >> 7
    return (a1 << 15) | (r5 << 10) | (g5 << 5) | b5


def generate_cake_inc_from_raw(raw_data, output_path):
    """Generate cake.inc.c from 320x240 RGBA16 raw data."""
    if len(raw_data) < 320 * 240 * 2:
        print(f"Warning: expected at least {320*240*2} bytes, got {len(raw_data)}", file=sys.stderr)

    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    with open(output_path, "w") as f:
        tex_idx = 0
        for row in range(ROWS):
            for col in range(COLS):
                f.write(f"ALIGNED8 static const Texture cake_end_texture_{tex_idx}[] = {{\n")
                
                for ty in range(TILE_H):
                    pixel_row = row * TILE_H + ty
                    for tx in range(TILE_W):
                        pixel_col = col * TILE_W + tx
                        src_offset = (pixel_row * 320 + pixel_col) * 2
                        if src_offset + 1 < len(raw_data):
                            b1 = raw_data[src_offset]
                            b2 = raw_data[src_offset + 1]
                        else:
                            b1 = b2 = 0
                        f.write(f"0x{b1:02X},0x{b2:02X},")
                    f.write("\n")
                
                f.write("};\n\n")
                tex_idx += 1

    print(f"  Generated: {output_path} ({tex_idx} textures)")


def generate_cake_inc_from_png(png_path, output_path):
    """Generate cake.inc.c from a PNG, center-padded to 320x240."""
    from PIL import Image
    img = Image.open(png_path).convert("RGBA")
    w, h = img.size

    src_img = Image.new("RGBA", (320, 240), (0, 0, 0, 0))
    paste_x = (320 - w) // 2
    paste_y = (240 - h) // 2
    src_img.paste(img, (paste_x, paste_y))

    os.makedirs(os.path.dirname(output_path), exist_ok=True)

    pixels = list(src_img.getdata())

    with open(output_path, "w") as f:
        tex_idx = 0
        for row in range(ROWS):
            for col in range(COLS):
                f.write(f"ALIGNED8 static const Texture cake_end_texture_{tex_idx}[] = {{\n")
                
                for ty in range(TILE_H):
                    pixel_row = row * TILE_H + ty
                    for tx in range(TILE_W):
                        pixel_col = col * TILE_W + tx
                        idx = pixel_row * 320 + pixel_col
                        r, g, b, a = pixels[idx]
                        rgba16 = rgba8_to_rgba16(r, g, b, a)
                        f.write(f"0x{rgba16:04X},")
                    f.write("\n")
                
                f.write("};\n\n")
                tex_idx += 1

    print(f"  Generated: {output_path} ({tex_idx} textures)")


if __name__ == "__main__":
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <png_or_raw_file> <output_inc_c>")
        sys.exit(1)

    input_path = sys.argv[1]
    output_path = sys.argv[2]

    if input_path.lower().endswith(".png"):
        generate_cake_inc_from_png(input_path, output_path)
    else:
        with open(input_path, "rb") as f:
            raw = f.read()
        generate_cake_inc_from_raw(raw, output_path)
