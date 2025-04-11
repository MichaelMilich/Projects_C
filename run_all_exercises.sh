#!/bin/sh
set -e

echo "🚀 Running all exercises..."

for c_file in new_c_excersizes/*.c; do
    basename=$(basename "$c_file" .c)
    so_file="test/c_lib/$basename.so"
    exe_file="bin/$basename.o"
    test_file="test/test_$basename.py"

    echo "=============================="
    echo "🔧 Building: $basename"

    # Clean old files
    [ -f "$so_file" ] && echo "🧹 Removing $so_file" && rm "$so_file"
    [ -f "$exe_file" ] && echo "🧹 Removing $exe_file" && rm "$exe_file"

    # Build
    make "$so_file"
    make "$exe_file"

    # Run test
    if [ -f "$test_file" ]; then
        echo "🧪 Running test: $test_file"
        python3 "$test_file"
    else
        echo "⚠️  No test found for $basename"
    fi
done

echo "✅ All exercises processed."
