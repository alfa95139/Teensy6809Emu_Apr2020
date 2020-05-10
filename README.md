# Teensy6809Emu_Apr2020
Implements the 6809 Emulator by Jerome Thoen in TeensyDuino.
The code is from example.asm, which was already compiled and available in the original distribution.
Note that this version does not include the disassambler, as I needed to keep things simple.
Most work was around substituting the code from console.c in the *.ino code.
Also NOTE: the *.hex code (also avail in the original distro) is NOT what we hardcoded in the *.ino. We had to first read that *.hex from the int6809.c routine.

example.asm:

        org     $0

        ;; to display text on the console :
        ;; X : addr of the C-string (terminated with '\0').
        ;; A : 1 (simulator entry to display text)

        ldx     #txt
        lda     #1
        swi

        ;; to read a string from input
        ;; X : addr of the buffer
        ;; B : size in bytes of the buffer
        ;; A : 2 (simulator entry to read a string)
        ;; return : the buffer is filled with the input
        ;; string, truncated to the size of the buffer
        ;; ('\0' included)

        ldx     #input
        ldb     #10
        lda     #2
        swi

        ldx     #txt2
        lda     #1
        swi

        ldx     #input
        lda     #1
        swi

        ldx     #endl
        lda     #1
        swi
        
        ;; to terminate a 6809 program
        ;; and return into the debugger
        ;; A : 0

        lda     #0
        swi

txt     fcc     "Enter a string (9 chars max): "
endl    fcb     $0A,0

txt2    fcc     "You entered this string : "
        fcb     0

input   rmb     10

        end

example.hex:

:200000008e002386013f8e005fc60a86023f8e004386013f8e005f86013f8e004186013f06
:2000200086003f456e746572206120737472696e67202839206368617273206d6178293a4a
:1f004000200a00596f757220656e7465726564207468697320737472696e67203a2000b8
:00000001ff

Hardcoded in TD6809.ino

const unsigned char example[] = {
0x8e, 0x00, 0x23, 0x86, 0x01, 0x3f, 0x8e, 0x00, 0x5f, 0xc6, 0x0a, 0x86, 0x02, 0x3f, 0x8e, 0x00,
0x43, 0x86, 0x01, 0x3f, 0x8e, 0x00, 0x5f, 0x86, 0x01, 0x3f, 0x8e, 0x00, 0x41, 0x86, 0x01, 0x3f,
0x86, 0x00, 0x3f, 0x45, 0x6e, 0x74, 0x65, 0x72, 0x20, 0x61, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e,
0x67, 0x20, 0x28, 0x39, 0x20, 0x63, 0x68, 0x61, 0x72, 0x73, 0x20, 0x6d, 0x61, 0x78, 0x29, 0x3a,
0x20, 0x0a, 0x00, 0x59, 0x6f, 0x75, 0x72, 0x20, 0x65, 0x6e, 0x74, 0x65, 0x72, 0x65, 0x64, 0x20,
0x74, 0x68, 0x69, 0x73, 0x20, 0x73, 0x74, 0x72, 0x69, 0x6e, 0x67, 0x20, 0x3a, 0x20, 0x00, 0x00
};
