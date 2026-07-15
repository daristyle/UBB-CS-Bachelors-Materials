nasm modulConcatenare.asm -fwin32 -g -o modulConcatenare.obj

cl /Z7 mainConcatenare.c /link modulConcatenare.obj
