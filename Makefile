# Default compiler and flags
CC = gcc
CFLAGS = -Wall -fPIC -Iutils
LDFLAGS = -shared

# Utility object files
UTILS_OBJS = utils/dynamic_int_array.o utils/string_to_array.o utils/calc_lexer.o utils/calc_parser.o utils/file_utils.o utils/student.o

# Default targets
all: $(UTILS_OBJS)

# Compile utility files
utils/%.o: utils/%.c utils/%.h
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@echo "[✓] Compiled utility: $@"

# Pattern rule to build a shared library
test/c_lib/%.so: new_c_excersizes/%.c $(UTILS_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(LDFLAGS) $< $(UTILS_OBJS) -o $@
	@echo "[✓] Built shared library: $@"

# Pattern rule to build a CLI binary
bin/%: new_c_excersizes/%.c $(UTILS_OBJS)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $< $(UTILS_OBJS) -o $@ -lm
	@echo "[✓] Built executable: $@"

# Clean rule
clean:
	rm -f $(UTILS_OBJS) test/c_lib/*.so bin/*

.PHONY: all clean
