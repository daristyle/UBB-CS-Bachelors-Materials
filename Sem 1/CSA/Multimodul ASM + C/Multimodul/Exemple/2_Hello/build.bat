
nasm hello.asm -fwin32 -o hello.obj

cl /Z7 main.c /link hello.obj
