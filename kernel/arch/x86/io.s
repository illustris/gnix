[GLOBAL io_inb]
io_inb:
    mov dx, [esp + 4]
    xor eax, eax
    in al, dx
    ret

[GLOBAL io_inw]
io_inw:
    mov dx, [esp + 4]
    xor eax, eax
    in ax, dx
    ret

[GLOBAL io_ind]
io_ind:
    mov dx, [esp + 4]
    in eax, dx
    ret

[GLOBAL io_outb]
io_outb:
    mov dx, [esp + 4]
    mov al, [esp + 8]
    out dx, al
    ret

[GLOBAL io_outw]
io_outw:
    mov dx, [esp + 4]
    mov ax, [esp + 8]
    out dx, ax
    ret

[GLOBAL io_outd]
io_outd:
    mov dx, [esp + 4]
    mov eax, [esp + 8]
    out dx, eax
    ret
