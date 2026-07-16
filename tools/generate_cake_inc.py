#!/usr/bin/env python3
"""Generate ``levels/ending/cake.inc.c`` from a ``cake.png`` (or raw RGBA16 file).

The cake ending screen is 320x240 RGBA16, divided into 48 tiles of 80x20.

Usage (from PNG)::

    python generate_cake_inc.py levels/ending/cake.png build/us_pc/levels/ending/cake.inc.c

Usage (from raw RGBA16)::

    python generate_cake_inc.py cake.raw build/us_pc/levels/ending/cake.inc.c
"""

from __future__ import annotations

import sys
from pathlib import Path

from PIL import Image

TILE_W = 80
TILE_H = 20
COLS = 4   # 320 / 80
ROWS = 12  # 240 / 20


def rgba8_to_rgba16(r: int, g: int, b: int, a: int) -> int:
    """Convert 8-bit RGBA to 16-bit RGBA16 (1-5-5-1 format)."""
    r5 = r >> 3
    g5 = g >> 3
    b5 = b >> 3
    a1 = a >> 7
    return (a1 << 15) | (r5 << 10) | (g5 << 5) | b5


def _write_tiles(f, pixels, src_w: int) -> int:
    """Write the 48 cake tiles from a flat RGBA pixel list. Returns tile count."""
    tex_idx = 0
    for row in range(ROWS):
        for col in range(COLS):
            f.write(f"ALIGNED8 static const Texture cake_end_texture_{tex_idx}[] = {{\n")
            for ty in range(TILE_H):
                pixel_row = row * TILE_H + ty
                for tx in range(TILE_W):
                    pixel_col = col * TILE_W + tx
                    idx = pixel_row * src_w + pixel_col
                    if idx < len(pixels):
                        r, g, b, a = pixels[idx]
                    else:
                        r = g = b = a = 0
                    f.write(f"0x{rgba8_to_rgba16(r, g, b, a):04X},")
            f.write("\n};\n\n")
            tex_idx += 1
    return tex_idx


def generate_cake_inc_from_raw(raw_data: bytes, output_path: Path) -> None:
    """Generate ``cake.inc.c`` from 320x240 RGBA16 raw bytes."""
    if len(raw_data) < 320 * 240 * 2:
        print(f"Warning: expected at least {320 * 240 * 2} bytes, got {len(raw_data)}",
              file=sys.stderr)

    output_path.parent.mkdir(parents=True, exist_ok=True)
    with output_path.open("w") as f:
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
                f.write("\n};\n\n")
                tex_idx += 1
    print(f"  Generated: {output_path} ({tex_idx} textures)")


def generate_cake_inc_from_png(png_path: Path, output_path: Path) -> None:
    """Generate ``cake.inc.c`` from a PNG, center-padded to 320x240."""
    img = Image.open(png_path).convert("RGBA")
    w, h = img.size

    src_img = Image.new("RGBA", (320, 240), (0, 0, 0, 0))
    paste_x = (320 - w) // 2
    paste_y = (240 - h) // 2
    src_img.paste(img, (paste_x, paste_y))

    output_path.parent.mkdir(parents=True, exist_ok=True)
    pixels = list(src_img.get_flattened_data())  # Pillow 14+: getdata() is deprecated

    with output_path.open("w") as f:
        tex_idx = _write_tiles(f, pixels, src_w=320)
    print(f"  Generated: {output_path} ({tex_idx} textures)")


def main() -> None:
    if len(sys.argv) < 3:
        print(f"Usage: {sys.argv[0]} <png_or_raw_file> <output_inc_c>")
        sys.exit(1)

    input_path = Path(sys.argv[1])
    output_path = Path(sys.argv[2])

    if input_path.suffix.lower() == ".png":
        generate_cake_inc_from_png(input_path, output_path)
    else:
        generate_cake_inc_from_raw(input_path.read_bytes(), output_path)


if __name__ == "__main__":
    main()
