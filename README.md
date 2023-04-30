# Linux CMD Tools and Shell Program

This project contains several small programs and a shell program written in C for the Linux operating system. The project is split into three parts, each with its own set of requirements:

1. Files operations 
2. Dynamic libraries
3. Basic shell

## System Environment

The programs in this project were developed and tested on Ubuntu 20.04 LTS.

## Part A: Files Operations

### Tool 1: cmp

The `cmp` tool compares two files and returns an integer value. It supports the following flags:

- `-v`: Print "equal" or "distinct" in addition to the integer value.
- `-i`: Ignore uppder-case letters when comparing.

#### Usage example

```
cmp <file1> <file2> -v
```

#### Output

The tool will output "equal" or "distinct" in addition to the integer value that will return.

### Tool 2: copy

The `copy` tool copies a file to another location or name. It returns an integer value indicating success or failure. It supports the following flags:

- `-v`: Print "success", "target file exists", or "general failure" in addition to the integer value.
- `-f`: Force overwrite of the target file.

#### Usage example

```
copy <file1> <file2> -v
```

#### Output

The tool will output "success", "target file exists", or "general failure" in addition to the integer value.

## Part B: Dynamic Libraries

This part of the project includes two coding libraries:

1. `codecA`: Converts all lowercase characters to uppercase and all uppercase characters to lowercase.
2. `codecB`: Converts all characters to the 3rd next character (adding 3 to the ASCII value).

Both libraries support "encode" and "decode" methods and are reversible.

### Tool 1: encode

The `encode` tool utilizes the `codecA` or `codecB` library to encode a message. It supports the following usage:

```
encode <codecA/codecB> <message>
```

#### Output

The tool will output the encoded string.

### Tool 2: decode

The `decode` tool utilizes the `codecA` or `codecB` library to decode a message. It supports the following usage:

```
decode <codec> <message>
```

#### Output

The tool will output the decoded string.

## Part C: Basic Shell

`stshell` is a Unix shell simulator that allows users to run basic Unix commands and features, as well as some additional improvements. The shell supports features such as `touch`, `ls`, `cd`, handling pipline (`|`) , and redirection (`>`,`>>`).

### Usage

Once you've started `stshell`, you can run Unix commands just like you would in a regular terminal. Here are some examples:

```
$ ls
$ touch file.txt
$ cd /path/to/directory
```

In addition to these basic commands, `stshell` also supports the following features:

#### Redirection

You can use `>` and `>>` to redirect output to a file. For example:

```
$ ls > output.txt
$ echo "Hello, world!" >> output.txt
```

#### Pipeline

You can use the `|` symbol to pipeline commands. For example:

```
$ ls | grep "file"
$ cat file.txt | grep "hello" | wc -l
```

#### Output

The shell program will start and allow the user to input CMD commands.

## Makefile

A Makefile is included in the project for compiling and running the programs. The following commands are available:

- `make`: Compile all programs.
- `make clean`: Remove all compiled files.

## Authors

- Bar alayof (@barmud3)
- Dor shir (@dorshir)
