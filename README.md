# Memmap
Just a tool that prints the open memory adress ranges of a specified process.<br>
Method: reading the memort map file of the process and printing the start and end of each memory address range.<br><br>
Example usage:
```
[x0@0x0-80tx ~]$ ./memmap 1549
[+] Found process 1549
[+] Open memory address range: 0x5605b3901000 - 0x5605b3905000
[+] Open memory address range: 0xbf46f6000 - 0x7f0bf46f7000
```
Download stable build [here](https://github.com/meth1337/memmap/releases/latest)
