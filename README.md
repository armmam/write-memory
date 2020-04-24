## Usage

```
./write_memory your_file
```

Memory representation is written to `memory.txt` in the folder where the binary has been placed. If such file already exists, the user will be asked to overwrite it.

## Format

Each line comprises 16 bytes, first represented as hexadecimals, then as ASCII characters (as `.` if non-printable).

For example, the output for `.gitignore` from this repository is
```
2320 4f62 6a65 6374 2066 696c 6573 0a2a # Object files.*
2e6f 0a0a 2320 4578 6563 7574 6162 6c65 .o..# Executable
730a 2a2e 6f75 740a 0a23 2056 696d 0a2a s.*.out..# Vim.*
2e73 7770 0a2a 2e73 776f 0a0a 2320 5653 .swp.*.swo..# VS
436f 6465 0a2e 7673 636f 6465 0a0a 2320 Code..vscode..# 
4d61 630a 2e44 535f 5374 6f72 650a      Mac..DS_Store.
```

###### *Code style inspired by Norminette from 42*
