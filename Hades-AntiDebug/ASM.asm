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

end