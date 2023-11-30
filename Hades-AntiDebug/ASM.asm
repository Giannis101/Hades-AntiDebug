.code

Internal_NtQueryVirtualMemory proc
    mov r10,rcx
    mov eax, 35
    syscall
    ret
Internal_NtQueryVirtualMemory endp

Internal_NtQueryInformationProcess proc
    mov r10,rcx
    mov eax, 25
    syscall
    ret
Internal_NtQueryInformationProcess endp

Internal_NtTerminateProcess proc
    mov r10,rcx
    mov eax, 44
    syscall
    ret
Internal_NtTerminateProcess endp

Internal_NtOpenProcess proc
    mov r10,rcx
    mov eax, 38
    syscall
    ret
Internal_NtOpenProcess endp

Internal_NtClose proc
    mov r10,rcx
    mov eax, 15
    syscall
    ret
Internal_NtClose endp

Internal_NtReadVirtualMemory proc
    mov r10,rcx
    mov eax, 63
    syscall
    ret
Internal_NtReadVirtualMemory endp

end