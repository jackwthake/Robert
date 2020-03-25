import os

# use these flags for very strict C
cflags = [ "-Wall", "-Wextra", "-pedantic", "-Wno-deprecated", "-std=c99" ]
lflags = [ "-lm" ]
include = [ "lib/dyad/src" ]
source = [ "lib/dyad/src" ]

if "client" in opt:
    lflags += [ "-L`pwd`/lib/CSFML/lib", "-lcsfml-graphics", "-lcsfml-window" ]
    include += [ "lib/CSFML/include", "lib/microui/src" ]
    source += [ "src/Control-Panel", "lib/microui/src" ]
    output = "robert-control-panel"

if "robot" in opt:
    lflags += [ "-lwiringPi", "-lncurses" ]
    source += [ "src/Robot" ]
    output = "robert"

if "sanitize" in opt:
    log("address sanitizer enabled")
    cflags += [ "-fsanitize=address" ]
    lflags += [ "-fsanitize=address" ]

def post():
    if "client" in opt:
        os.system("install_name_tool -add_rpath @executable_path/lib/CSFML/lib/. robert-control-panel")
