
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

0000000000001020 <__stack_chk_fail@plt-0x10>:
    1020:	ff 35 ca 2f 00 00    	push   QWORD PTR [rip+0x2fca]        # 3ff0 <_GLOBAL_OFFSET_TABLE_+0x8>
    1026:	ff 25 cc 2f 00 00    	jmp    QWORD PTR [rip+0x2fcc]        # 3ff8 <_GLOBAL_OFFSET_TABLE_+0x10>
    102c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]

0000000000001030 <__stack_chk_fail@plt>:
    1030:	ff 25 ca 2f 00 00    	jmp    QWORD PTR [rip+0x2fca]        # 4000 <__stack_chk_fail@GLIBC_2.4>
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
    1058:	48 8d 3d 30 01 00 00 	lea    rdi,[rip+0x130]        # 118f <main>
    105f:	ff 15 5b 2f 00 00    	call   QWORD PTR [rip+0x2f5b]        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1065:	f4                   	hlt
    1066:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    106d:	00 00 00 
    1070:	48 8d 3d a9 2f 00 00 	lea    rdi,[rip+0x2fa9]        # 4020 <__TMC_END__>
    1077:	48 8d 05 a2 2f 00 00 	lea    rax,[rip+0x2fa2]        # 4020 <__TMC_END__>
    107e:	48 39 f8             	cmp    rax,rdi
    1081:	74 15                	je     1098 <_start+0x58>
    1083:	48 8b 05 3e 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f3e]        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    108a:	48 85 c0             	test   rax,rax
    108d:	74 09                	je     1098 <_start+0x58>
    108f:	ff e0                	jmp    rax
    1091:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1098:	c3                   	ret
    1099:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10a0:	48 8d 3d 79 2f 00 00 	lea    rdi,[rip+0x2f79]        # 4020 <__TMC_END__>
    10a7:	48 8d 35 72 2f 00 00 	lea    rsi,[rip+0x2f72]        # 4020 <__TMC_END__>
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
    10e4:	80 3d 31 2f 00 00 00 	cmp    BYTE PTR [rip+0x2f31],0x0        # 401c <__bss_start>
    10eb:	75 33                	jne    1120 <_start+0xe0>
    10ed:	55                   	push   rbp
    10ee:	48 83 3d ea 2e 00 00 	cmp    QWORD PTR [rip+0x2eea],0x0        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10f5:	00 
    10f6:	48 89 e5             	mov    rbp,rsp
    10f9:	74 0d                	je     1108 <_start+0xc8>
    10fb:	48 8b 3d 0e 2f 00 00 	mov    rdi,QWORD PTR [rip+0x2f0e]        # 4010 <__dso_handle>
    1102:	ff 15 d8 2e 00 00    	call   QWORD PTR [rip+0x2ed8]        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    1108:	e8 63 ff ff ff       	call   1070 <_start+0x30>
    110d:	c6 05 08 2f 00 00 01 	mov    BYTE PTR [rip+0x2f08],0x1        # 401c <__bss_start>
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
    113d:	48 89 7d d8          	mov    QWORD PTR [rbp-0x28],rdi
    1141:	89 75 d4             	mov    DWORD PTR [rbp-0x2c],esi
    1144:	c7 45 e0 01 00 00 00 	mov    DWORD PTR [rbp-0x20],0x1
    114b:	c7 45 e4 02 00 00 00 	mov    DWORD PTR [rbp-0x1c],0x2
    1152:	c7 45 e8 03 00 00 00 	mov    DWORD PTR [rbp-0x18],0x3
    1159:	c7 45 ec 01 00 00 00 	mov    DWORD PTR [rbp-0x14],0x1
    1160:	c7 45 f0 02 00 00 00 	mov    DWORD PTR [rbp-0x10],0x2
    1167:	c7 45 f4 03 00 00 00 	mov    DWORD PTR [rbp-0xc],0x3
    116e:	48 8b 4d d8          	mov    rcx,QWORD PTR [rbp-0x28]
    1172:	48 8b 45 e0          	mov    rax,QWORD PTR [rbp-0x20]
    1176:	48 8b 55 e8          	mov    rdx,QWORD PTR [rbp-0x18]
    117a:	48 89 01             	mov    QWORD PTR [rcx],rax
    117d:	48 89 51 08          	mov    QWORD PTR [rcx+0x8],rdx
    1181:	48 8b 45 f0          	mov    rax,QWORD PTR [rbp-0x10]
    1185:	48 89 41 10          	mov    QWORD PTR [rcx+0x10],rax
    1189:	48 8b 45 d8          	mov    rax,QWORD PTR [rbp-0x28]
    118d:	5d                   	pop    rbp
    118e:	c3                   	ret

000000000000118f <main>:
    118f:	55                   	push   rbp
    1190:	48 89 e5             	mov    rbp,rsp
    1193:	48 83 ec 30          	sub    rsp,0x30
    1197:	64 48 8b 04 25 28 00 	mov    rax,QWORD PTR fs:0x28
    119e:	00 00 
    11a0:	48 89 45 f8          	mov    QWORD PTR [rbp-0x8],rax
    11a4:	31 c0                	xor    eax,eax
    11a6:	48 8d 45 d0          	lea    rax,[rbp-0x30]
    11aa:	be 05 00 00 00       	mov    esi,0x5
    11af:	48 89 c7             	mov    rdi,rax
    11b2:	e8 82 ff ff ff       	call   1139 <function1>
    11b7:	8b 05 5b 2e 00 00    	mov    eax,DWORD PTR [rip+0x2e5b]        # 4018 <globalVar>
    11bd:	48 8b 55 f8          	mov    rdx,QWORD PTR [rbp-0x8]
    11c1:	64 48 2b 14 25 28 00 	sub    rdx,QWORD PTR fs:0x28
    11c8:	00 00 
    11ca:	74 05                	je     11d1 <main+0x42>
    11cc:	e8 5f fe ff ff       	call   1030 <__stack_chk_fail@plt>
    11d1:	c9                   	leave
    11d2:	c3                   	ret

Disassembly of section .fini:

00000000000011d4 <_fini>:
    11d4:	f3 0f 1e fa          	endbr64
    11d8:	48 83 ec 08          	sub    rsp,0x8
    11dc:	48 83 c4 08          	add    rsp,0x8
    11e0:	c3                   	ret
