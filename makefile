# ----------------------------
# Makefile Options
# ----------------------------

NAME = IDK
# ICON = icon.png
DESCRIPTION = "idk"
COMPRESSED = YES
ARCHIVED = YES

CFLAGS = -Wall -Wextra -Oz
CXXFLAGS = -Wall -Wextra -Oz

# ----------------------------

include $(shell cedev-config --makefile)