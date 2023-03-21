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
- Download from remote machine, `get <FileName>`
- Upload local file, `put <FileName>`
## Tools
`grep -R <String> <path>`, to find all avaible text matches <String> within <path>
`find -name <fileName>`, find the path of <fileName> from the current working directory recursively

## Acknowledge
- Labs and programing assignments published in this repository is built on scripts primarily written in C language and provided by Professor Hoque. \
https://ecs.syracuse.edu/faculty-staff/endadul-hoque

- Nachos kernel adopted since Lab3 is developed by University of California from 1992, copyright of the project is attached in head of files.