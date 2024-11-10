
output.elf:     file format elf64-x86-64


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

Disassembly of section .text:

0000000000001020 <_start>:
    1020:	f3 0f 1e fa          	endbr64
    1024:	31 ed                	xor    ebp,ebp
    1026:	49 89 d1             	mov    r9,rdx
    1029:	5e                   	pop    rsi
    102a:	48 89 e2             	mov    rdx,rsp
    102d:	48 83 e4 f0          	and    rsp,0xfffffffffffffff0
    1031:	50                   	push   rax
    1032:	54                   	push   rsp
    1033:	45 31 c0             	xor    r8d,r8d
    1036:	31 c9                	xor    ecx,ecx
    1038:	48 8d 3d 07 01 00 00 	lea    rdi,[rip+0x107]        # 1146 <main>
    103f:	ff 15 7b 2f 00 00    	call   QWORD PTR [rip+0x2f7b]        # 3fc0 <__libc_start_main@GLIBC_2.34>
    1045:	f4                   	hlt
    1046:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    104d:	00 00 00 
    1050:	48 8d 3d b9 2f 00 00 	lea    rdi,[rip+0x2fb9]        # 4010 <__TMC_END__>
    1057:	48 8d 05 b2 2f 00 00 	lea    rax,[rip+0x2fb2]        # 4010 <__TMC_END__>
    105e:	48 39 f8             	cmp    rax,rdi
    1061:	74 15                	je     1078 <_start+0x58>
    1063:	48 8b 05 5e 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f5e]        # 3fc8 <_ITM_deregisterTMCloneTable@Base>
    106a:	48 85 c0             	test   rax,rax
    106d:	74 09                	je     1078 <_start+0x58>
    106f:	ff e0                	jmp    rax
    1071:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1078:	c3                   	ret
    1079:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    1080:	48 8d 3d 89 2f 00 00 	lea    rdi,[rip+0x2f89]        # 4010 <__TMC_END__>
    1087:	48 8d 35 82 2f 00 00 	lea    rsi,[rip+0x2f82]        # 4010 <__TMC_END__>
    108e:	48 29 fe             	sub    rsi,rdi
    1091:	48 89 f0             	mov    rax,rsi
    1094:	48 c1 ee 3f          	shr    rsi,0x3f
    1098:	48 c1 f8 03          	sar    rax,0x3
    109c:	48 01 c6             	add    rsi,rax
    109f:	48 d1 fe             	sar    rsi,1
    10a2:	74 14                	je     10b8 <_start+0x98>
    10a4:	48 8b 05 2d 2f 00 00 	mov    rax,QWORD PTR [rip+0x2f2d]        # 3fd8 <_ITM_registerTMCloneTable@Base>
    10ab:	48 85 c0             	test   rax,rax
    10ae:	74 08                	je     10b8 <_start+0x98>
    10b0:	ff e0                	jmp    rax
    10b2:	66 0f 1f 44 00 00    	nop    WORD PTR [rax+rax*1+0x0]
    10b8:	c3                   	ret
    10b9:	0f 1f 80 00 00 00 00 	nop    DWORD PTR [rax+0x0]
    10c0:	f3 0f 1e fa          	endbr64
    10c4:	80 3d 45 2f 00 00 00 	cmp    BYTE PTR [rip+0x2f45],0x0        # 4010 <__TMC_END__>
    10cb:	75 33                	jne    1100 <_start+0xe0>
    10cd:	55                   	push   rbp
    10ce:	48 83 3d 0a 2f 00 00 	cmp    QWORD PTR [rip+0x2f0a],0x0        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10d5:	00 
    10d6:	48 89 e5             	mov    rbp,rsp
    10d9:	74 0d                	je     10e8 <_start+0xc8>
    10db:	48 8b 3d 26 2f 00 00 	mov    rdi,QWORD PTR [rip+0x2f26]        # 4008 <__dso_handle>
    10e2:	ff 15 f8 2e 00 00    	call   QWORD PTR [rip+0x2ef8]        # 3fe0 <__cxa_finalize@GLIBC_2.2.5>
    10e8:	e8 63 ff ff ff       	call   1050 <_start+0x30>
    10ed:	c6 05 1c 2f 00 00 01 	mov    BYTE PTR [rip+0x2f1c],0x1        # 4010 <__TMC_END__>
    10f4:	5d                   	pop    rbp
    10f5:	c3                   	ret
    10f6:	66 2e 0f 1f 84 00 00 	cs nop WORD PTR [rax+rax*1+0x0]
    10fd:	00 00 00 
    1100:	c3                   	ret
    1101:	66 66 2e 0f 1f 84 00 	data16 cs nop WORD PTR [rax+rax*1+0x0]
    1108:	00 00 00 00 
    110c:	0f 1f 40 00          	nop    DWORD PTR [rax+0x0]
    1110:	f3 0f 1e fa          	endbr64
    1114:	e9 67 ff ff ff       	jmp    1080 <_start+0x60>

0000000000001119 <function1>:
    1119:	55                   	push   rbp
    111a:	48 89 e5             	mov    rbp,rsp
    111d:	89 7d ec             	mov    DWORD PTR [rbp-0x14],edi
    1120:	89 75 e8             	mov    DWORD PTR [rbp-0x18],esi
    1123:	8b 45 ec             	mov    eax,DWORD PTR [rbp-0x14]
    1126:	89 45 f0             	mov    DWORD PTR [rbp-0x10],eax
    1129:	8b 45 e8             	mov    eax,DWORD PTR [rbp-0x18]
    112c:	89 45 f4             	mov    DWORD PTR [rbp-0xc],eax
    112f:	8b 45 f0             	mov    eax,DWORD PTR [rbp-0x10]
    1132:	89 45 f8             	mov    DWORD PTR [rbp-0x8],eax
    1135:	8b 45 f4             	mov    eax,DWORD PTR [rbp-0xc]
    1138:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
    113b:	8b 45 f8             	mov    eax,DWORD PTR [rbp-0x8]
    113e:	01 45 fc             	add    DWORD PTR [rbp-0x4],eax
    1141:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
    1144:	5d                   	pop    rbp
    1145:	c3                   	ret

0000000000001146 <main>:
    1146:	55                   	push   rbp
    1147:	48 89 e5             	mov    rbp,rsp
    114a:	48 83 ec 10          	sub    rsp,0x10
    114e:	be 02 00 00 00       	mov    esi,0x2
    1153:	bf 05 00 00 00       	mov    edi,0x5
    1158:	e8 bc ff ff ff       	call   1119 <function1>
    115d:	89 45 fc             	mov    DWORD PTR [rbp-0x4],eax
    1160:	8b 45 fc             	mov    eax,DWORD PTR [rbp-0x4]
    1163:	c9                   	leave
    1164:	c3                   	ret

Disassembly of section .fini:

0000000000001168 <_fini>:
    1168:	f3 0f 1e fa          	endbr64
    116c:	48 83 ec 08          	sub    rsp,0x8
    1170:	48 83 c4 08          	add    rsp,0x8
    1174:	c3                   	ret
