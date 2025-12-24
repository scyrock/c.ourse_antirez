# Makefile collect a list of operations needed to build or execute a program.

# Each line composed by a target to compile followed by the prerequisite needed
# to compile it.

# By default the make command compiles the first presented target.
# Is it common practice to start make file using the target `all` using as
# prerequisite the program name.
all: toyforth

# To obtain the target toyforth the file `toyforth.c` is needed.
# $(CC) is used to indicate the predefined C compiler of the machine.
toyforth: toyforth.c
	$(CC) toyforth.c -Wall -W -O2 -o toyforth

# Remove the generated binary file
clean:
	rm -rf toyforth

# The program compilation can be executed by using the command `make`
# The program is compiled only if the last modification of the file is after the
# last file compilation.
#
# By using the target clean (eg `$ make clean`) the binary file is deleted.
