# Architecture

Everything is contained in a single source file: `main.cpp`.

## Structure

1. **English Monograph Frequencies (`ENG_FREQ`)**
   Standard relative letter frequencies for the English language (A–Z) used to evaluate decrypted candidates.

2. **Ciphers**
   - `caesar(text, shift)`: Shifts lowercase and uppercase letters modulo 26 while preserving case, punctuation, and spaces. Normalizes negative shifts.
   - `vigenere(text, key, decode)`: Shifts letters using successive characters from a keyword.
   - `atbash(text)`: Symmetric reverse mapping (`a` <-> `z`, `A` <-> `Z`).
   - `rot47(text)`: Rotates printable ASCII characters (33–126).

3. **Cracker & Frequency Analysis**
   - `chiSquared(text)`: Measures how closely the letter frequencies in a candidate string match standard English. Lower values represent higher likelihood of valid English.
   - `crackAll(text)`: Tests all 25 potential shifts and sorts results from lowest to highest Chi-squared score.

4. **CLI & User Interface**
   - `parseArgs(argc, argv)`: Parses flags (`-e`, `-d`, `-c`, `-b`, `-m`, `-f`, `-o`, `-k`, `-t`).
   - `interactive()`: Fallback text menu when run without flags.
   - `main(argc, argv)`: Resolves input source (flag, file, stdin), applies the chosen cipher or cryptanalysis routine, and writes output (file or stdout).
