Import("env")
import os

# Files that cause compile errors on ESP32 due to missing symbols or wrong architecture
bad_files = [
    os.path.join(env["PROJECT_LIBDEPS_DIR"], "esp32dev", "lvgl", "src", "widgets", "scale", "lv_scale.c"),
    os.path.join(env["PROJECT_LIBDEPS_DIR"], "esp32dev", "lvgl", "src", "draw", "sw", "blend", "helium", "lv_blend_helium.S"),
]

for f in bad_files:
    if os.path.isfile(f):
        os.remove(f)
        print(f"Pre-build: removed {f}")
    else:
        print(f"Pre-build: already gone {f}")
