# Cipher Tool

A lightweight, single-file C++ tool for encoding, decoding, and cracking classical ciphers.

## Features

- **Caesar Cipher**: Shift letters with positive or negative keys.
- **Auto-Cracker**: Breaks Caesar ciphers without knowing the key by analyzing letter frequency.
- **Brute-Force**: Shows all 25 shifts ranked by natural English probability.
- **Additional Ciphers**: Vigenere, Atbash, ROT13, and ROT47.
- **Flexible**: Use interactive prompts, command-line arguments, file input/output, or shell piping.

## Build

```bash
make
```

Or with `g++`:

```bash
g++ -std=c++17 -O2 main.cpp -o caesar_cipher
```

## Usage

### Interactive Menu
Run with no arguments:
```bash
./caesar_cipher
```

### Command Line Flags

```text
Modes:
  -e, --encode          Encode input
  -d, --decode          Decode input
  -c, --crack           Auto-crack Caesar cipher without key
  -b, --bruteforce      List all 25 shifts ranked by English fit
  -i, --interactive     Launch menu (default)

Ciphers (-t):
  caesar (default), vigenere, atbash, rot13, rot47

Options:
  -k, --key KEY         Shift integer (Caesar) or passphrase (Vigenere)
  -m, --message TEXT    Direct input text
  -f, --input FILE      Read from file
  -o, --output FILE     Write to file
  --scores              Show Chi-squared fit scores
```

## Examples

**Caesar encode and decode:**
```bash
./caesar_cipher -e -k 3 -m "Hello, World!"
./caesar_cipher -d -k 3 -m "Khoor, Zruog!"
```

**Auto-crack ciphertext:**
```bash
./caesar_cipher -c -m "Ym NX f xjhwjy rjxxflj."
```

**Vigenere encode:**
```bash
./caesar_cipher -e -t vigenere -k "SECRET" -m "Attack at dawn"
```

**File I/O:**
```bash
./caesar_cipher -e -k 7 -f plain.txt -o encrypted.txt
./caesar_cipher -c -f encrypted.txt
```
