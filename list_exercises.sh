#!/bin/sh

echo "📚 Available C exercises:"
for file in new_c_excersizes/*.c; do
    basename=$(basename "$file")
    echo "  - $basename"
done
