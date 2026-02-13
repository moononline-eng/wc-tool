# Word Count Tool (mywc)

A C++ implementation of the Unix `wc` (word count) command that counts lines, words, characters, and bytes in text files.

## Compilation
```bash
g++ mywc.cpp -o mywc
```

## Usage
```bash
./mywc [OPTION] [FILE]
```

If no FILE is specified, reads from standard input.

## Options

| Option | Description |
|--------|-------------|
| (none) | Display line count, word count, and byte count |
| `-l` | Count lines only |
| `-w` | Count words only |
| `-m` | Count characters (UTF-8 aware) |
| `-c` | Count bytes (file size) |

## Examples

### Default output (lines, words, bytes)
```bash
./mywc test.txt
# Output: 7145 58164 342190 test.txt
```

### Count bytes only
```bash
./mywc -c test.txt
# Output: 342190 test.txt
```

### Count characters only
```bash
./mywc -m test.txt
# Output: 339292 test.txt
```

### Count lines from piped input
```bash
cat test.txt | ./mywc -l
# Output: 7145
```
