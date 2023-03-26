# Compilation
To compile file run `make -f makefile`. This command will crate a binary executable "huffman".

# Usage
## Help
To get instruction run `./huffman --help`.

## Compressing
To compress file run `./huffman --compress <path to file>`.

**Example:**
For example you want to compress file "f.txt". So you need to run `./huffamn f.txt`.
The program will create arive with name "f.txt.data", "data" is the extention of archives. 

## Decompressing
To recover file form archive run `./huffman --decompress <path to archive>`.

**Example:**
For example you want to recover file "f.txt" form archive "f.txt.data". 
So you need to run `./huffamn --decompress f.txt.data`.
It will create file "f.txt.back".

I made extension "back" for recovered files to prevent overriding of the sorce file. It's convenient for testing of the program.



A program with CLI interface for compressing and decompressing files, using Huffman algorithm.
