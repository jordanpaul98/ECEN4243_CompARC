# lab1

## Compilation
The Makefile does not appear to be working properly yet.
Running the following command makes it compile and work properly:
```$ gcc sim.c shell.c -o sim -O2 -g -std=gnu99```

## Running
The program appears to run and function properly at the moment.
Run using the following command:
```$ ./sim ./testing/add.memfile``` 
This works with all of the memfiles in the testing folder.
Make sure to use the .memfile extension rather than .s or .elf.
Those will not work. All files still need to be tested for accuracy.