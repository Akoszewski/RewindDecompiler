
a.out:     file format elf64-x86-64

Contents of section .rodata:
 2000 01000200 61736466 0a00               ....asdf..      

a.out:     file format elf64-x86-64


Disassembly of section .init:

0000000000001000 <_init>:
    1000:	f3 0f 1e fa          	endbr64
    1004:	48 83 ec 08          	sub    rsp,0x8
    1008:	48 8b 05 c1 2f 00 00 	mov    rax,QWORD PTR [rip+0x2fc1]        # 3fd0 <__gmon_start__@Base>
    100f:	48 85 c0             	test   rax,rax
    1012:	74 02                	je     1016 <_init+0x16>
    1014:	ff d0                	call   rax
    1016:	48 83 c4 08          	add    rsp,0x8
    101a:	c3                   	ret

Disassembly of section .plt:

0000000000001020 <puts@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   QWORD PTR [rip+0x2fca]        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    QWORD PTR [rip+0x2fcc]        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000001030 <puts@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    QWORD PTR [rip+0x2fca]        # 4000 <puts@GLIBC_2.2.5>
    1036:	68 00 00 00 00       	push   0x0
    103b:	e9 e0 ff ff ff       	jmp    1020 <_init+0x20>

Disassembly of section .text:

0000000000001040 <_start>:
    1040:	f3 0f 1e fa          	endbr64
    1044:	31 ed                	xor    ebp,ebp
    1046:	49 89 d1             	mov    r9,rdx
    1049:	5e                   	pop    rsi
    104a:	48 89 e2             	mov    rdx,rsp
    104d:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    1051:	50                   	push   rax
    1052:	54                   	push   rsp
    1053:	45 31 c0             	xor    r8d,r8d
    1056:	31 c9                	xor    ecx,ecx
    1058:	48 8d 3d f3 00 00 00 	lea    rdi,[rip+0xf3]        # 1152 <main>
    105f:	ff 15 5b 2f 00 00    	call   QWORD PTR [rip+0x2f5b]        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1065:	f4                   	hlt
    1066:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    106d:	00 00 00 
    1070:	48 8d 3d a1 2f 00 00 	lea    rdi,[rip+0x2fa1]        # 4018 <__TMC_END__>
    1077:	48 8d 05 9a 2f 00 00 	lea    rax,[rip+0x2f9a]        # 4018 <__TMC_END__>
    107e:	48 39 f8             	cmp    rax,rdi
    1081:	74 15                	je     1098 <_start+0x58>
    1083:	48 8b 05 3e 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f3e]        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    108a:	48 85 c0             	test   rax,rax
    108d:	74 09                	je     1098 <_start+0x58>
    108f:	ff e0                	jmp    rax
    1091:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1098:	c3                   	ret
    1099:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10a0:	48 8d 3d 71 2f 00 00 	lea    rdi,[rip+0x2f71]        # 4018 <__TMC_END__>
    10a7:	48 8d 35 6a 2f 00 00 	lea    rsi,[rip+0x2f6a]        # 4018 <__TMC_END__>
    10ae:	48 29 fe             	sub    rsi,rdi
    10b1:	48 89 f0             	mov    rax,rsi
    10b4:	48 c1 ee 3f          	shr    rsi,0x3f
    10b8:	48 c1 f8 03          	sar    rax,0x3
    10bc:	48 01 c6             	add    rsi,rax
    10bf:	48 d1 fe             	sar    rsi,1
    10c2:	74 14                	je     10d8 <_start+0x98>
    10c4:	48 8b 05 0d 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f0d]        # 3fd8 <_ITM_registerTMCloneTable@Base>
    10cb:	48 85 c0             	test   rax,rax
    10ce:	74 08                	je     10d8 <_start+0x98>
    10d0:	ff e0                	jmp    rax
    10d2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    10d8:	c3                   	ret
    10d9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10e0:	f3 0f 1e fa          	endbr64
    10e4:	80 3d 2d 2f 00 00 00 	cmp    BYTE PTR [rip+0x2f2d],0x0        # 4018 <__TMC_END__>
    10eb:	75 33                	jne    1120 <_start+0xe0>
    10ed:	55                   	push   rbp
    10ee:	48 83 3d ea 2e 00 00 	cmp    QWORD PTR [rip+0x2eea],0x0        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10f5:	00 
    10f6:	48 89 e5             	mov    rbp,rsp
    10f9:	74 0d                	je     1108 <_start+0xc8>
    10fb:	48 8b 3d 0e 2f 00 00 	mov    rdi,QWORD PTR [rip+0x2f0e]        # 4010 <__dso_handle>
    1102:	ff 15 d8 2e 00 00    	call   QWORD PTR [rip+0x2ed8]        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1108:	e8 63 ff ff ff       	call   1070 <_start+0x30>
    110d:	c6 05 04 2f 00 00 01 	mov    BYTE PTR [rip+0x2f04],0x1        # 4018 <__TMC_END__>
    1114:	5d                   	pop    rbp
    1115:	c3                   	ret
    1116:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    111d:	00 00 00 
    1120:	c3                   	ret
    1121:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    1128:	00 00 00 00 
    112c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    1130:	f3 0f 1e fa          	endbr64
    1134:	e9 67 ff ff ff       	jmp    10a0 <_start+0x60>

0000000000001139 <function1>:
    1139:	55                   	push   rbp
    113a:	48 89 e5             	mov    rbp,rsp
    113d:	89 7d fc             	mov    DWORD PTR [rbp-0x4],edi
    1140:	89 f0                	mov    eax,esi
    1142:	88 45 f8             	mov    BYTE PTR [rbp-0x8],al
    1145:	0f be 45 f8          	movsx  eax,BYTE PTR [rbp-0x8]
    1149:	8b 55 fc             	mov    edx,DWORD PTR [rbp-0x4]
    114c:	29 c2                	sub    edx,eax
    114e:	89 d0                	mov    eax,edx
    1150:	5d                   	pop    rbp
    1151:	c3                   	ret

0000000000001152 <main>:
    1152:	55                   	push   rbp
    1153:	48 89 e5             	mov    rbp,rsp
    1156:	be 05 00 00 00       	mov    esi,0x5
    115b:	bf 02 00 00 00       	mov    edi,0x2
    1160:	e8 d4 ff ff ff       	call   1139 <function1>
    1165:	48 8d 05 98 0e 00 00 	lea    rax,[rip+0xe98]        # 2004 <_IO_stdin_used+0x4>
    116c:	48 89 c7             	mov    rdi,rax
    116f:	e8 bc fe ff ff       	call   1030 <puts@plt>
    1174:	b8 00 00 00 00       	mov    eax,0x0
    1179:	5d                   	pop    rbp
    117a:	c3                   	ret

Disassembly of section .fini:

000000000000117c <_fini>:
    117c:	f3 0f 1e fa          	endbr64
    1180:	48 83 ec 08          	sub    rsp,0x8
    1184:	48 83 c4 08          	add    rsp,0x8
    1188:	c3                   	ret
