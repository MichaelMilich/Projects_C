#!/bin/sh
set -e

# === Argument parsing ===
if [ $# -ne 1 ]; then
    echo "Usage: $0 <c_file_basename>.c"
    echo "Example: $0 3_1_string_reversal.c"
    exit 1
fi

# === Extract file components ===
filename=$1
basename=$(basename "$filename" .c)

so_file="test/c_lib/$basename.so"
exe_file="bin/$basename.o"
test_file="test/test_$basename.py"

echo "📦 Preparing to build and test: $basename"

# === Clean up old artifacts ===
if [ -f "$so_file" ]; then
    echo "🧹 Removing old shared library: $so_file"
    rm "$so_file"
fi

if [ -f "$exe_file" ]; then
    echo "🧹 Removing old executable: $exe_file"
    rm "$exe_file"
fi

# === Build targets ===
echo "🔧 Building shared library and executable..."
make "$so_file"
make "$exe_file"

# === Run test ===
if [ -f "$test_file" ]; then
    echo "🧪 Running Python test: $test_file"
    python3 "$test_file"
else
    echo "⚠️  Test file not found: $test_file"
    exit 1
fi
