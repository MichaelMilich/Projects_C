# Default compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC
LDFLAGS = -shared

# Default targets (empty to avoid full project-wide build)
all:

# Pattern rule to build a shared library
test/c_lib/%.so: new_c_excersizes/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $< -o $@
	@echo "[✓] Built shared library: $@"

# Pattern rule to build a CLI binary (optional)
bin/%.o: new_c_excersizes/%.c
	@mkdir -p $(dir $@)
	$(CC) $< -o $@
	@echo "[✓] Built executable: $@"

.PHONY: all
