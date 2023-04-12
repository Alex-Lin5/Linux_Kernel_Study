# Linux_Kernel_Study
The repository is about the basic linux kernel functions and resources virtualization, scripts are written in C language

## Server 
### Information
```
$ uname -a
Linux lcs-vc-cis486 5.4.0-136-generic #153-Ubuntu SMP Thu Nov 24 15:56:58 UTC 2022 x86_64 x86_64 x86_64 GNU/Linux
$ gcc --version
gcc (Ubuntu 9.4.0-1ubuntu1~20.04.1) 9.4.0
Copyright (C) 2019 Free Software Foundation, Inc.
```
### SSH Connection
- `ssh -p 10500 your_SU_netid@cis-os-linux.syr.edu`
### SFTP for file transfer
- `sftp username@servername`
- Find current working directory locally and remotely, `lpwd` vs `pwd`
- Change current working directory locally and remotely, `lcd` vs `cd`
- Download from remote machine, `get <FileName>`
- Upload local file, `put <FileName>`
## Tools
- `grep -R <String> <path>`, to find all avaible text matches <String> within <path>
- `find -name <fileName>`, find the path of <fileName> from the current working directory recursively
- file content comparison
  - In Linux, `diff file1 file2`
  - In Windows, `diff (get-content file1) (get-content file2)`
- file compress and depress
  - `tar czf zippedFile.tar.gz folder/` to compress into zipped file
  - `tar tvzf zippedFile.tar.gz` to preview the content in compressed zipped file
  - `tar xzf zippedFile.tar.gz` to depress the zipped file
- GDB debugging program, `gdb ./program`
  - `run arg1 arg2` or `r`, run program with optional arguements
  - `continue` or `c`, continue running program until next break point or error
  - `break func()` or `b f()`, to put a break point on the begining of function
  - `break` or `b`, put a break point at current line
  - `info break`, list breakpoints
  - `backtrace` or `bt`, prints current stack trace
  - `delete N` or `d N`, delete breakpoint numbered N
  - `print var` or `p var`, get variable var value in current stack
  - `quit` or `q`, quits gdb

## Acknowledge
- Labs and programing assignments published in this repository is built on scripts primarily written in C language and provided by Professor Hoque. \
https://ecs.syracuse.edu/faculty-staff/endadul-hoque

- Nachos kernel adopted since Lab3 is developed by University of California from 1992, copyright of the project is attached in head of files.