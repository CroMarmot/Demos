
./a.m:     file format elf64-x86-64


Disassembly of section .init:

00000000000005d8 <_init>:
 5d8:	48 83 ec 08          	sub    $0x8,%rsp
 5dc:	48 8b 05 05 0a 20 00 	mov    0x200a05(%rip),%rax        # 200fe8 <__gmon_start__>
 5e3:	48 85 c0             	test   %rax,%rax
 5e6:	74 02                	je     5ea <_init+0x12>
 5e8:	ff d0                	callq  *%rax
 5ea:	48 83 c4 08          	add    $0x8,%rsp
 5ee:	c3                   	retq   

Disassembly of section .plt:

00000000000005f0 <.plt>:
 5f0:	ff 35 ba 09 20 00    	pushq  0x2009ba(%rip)        # 200fb0 <_GLOBAL_OFFSET_TABLE_+0x8>
 5f6:	ff 25 bc 09 20 00    	jmpq   *0x2009bc(%rip)        # 200fb8 <_GLOBAL_OFFSET_TABLE_+0x10>
 5fc:	0f 1f 40 00          	nopl   0x0(%rax)

0000000000000600 <__cxa_atexit@plt>:
 600:	ff 25 ba 09 20 00    	jmpq   *0x2009ba(%rip)        # 200fc0 <__cxa_atexit@GLIBC_2.2.5>
 606:	68 00 00 00 00       	pushq  $0x0
 60b:	e9 e0 ff ff ff       	jmpq   5f0 <.plt>

0000000000000610 <_ZNSt8ios_base4InitC1Ev@plt>:
 610:	ff 25 b2 09 20 00    	jmpq   *0x2009b2(%rip)        # 200fc8 <_ZNSt8ios_base4InitC1Ev@GLIBCXX_3.4>
 616:	68 01 00 00 00       	pushq  $0x1
 61b:	e9 d0 ff ff ff       	jmpq   5f0 <.plt>

Disassembly of section .plt.got:

0000000000000620 <__cxa_finalize@plt>:
 620:	ff 25 aa 09 20 00    	jmpq   *0x2009aa(%rip)        # 200fd0 <__cxa_finalize@GLIBC_2.2.5>
 626:	66 90                	xchg   %ax,%ax

Disassembly of section .text:

0000000000000630 <_start>:
 630:	31 ed                	xor    %ebp,%ebp
 632:	49 89 d1             	mov    %rdx,%r9
 635:	5e                   	pop    %rsi
 636:	48 89 e2             	mov    %rsp,%rdx
 639:	48 83 e4 f0          	and    $0xfffffffffffffff0,%rsp
 63d:	50                   	push   %rax
 63e:	54                   	push   %rsp
 63f:	4c 8d 05 6a 02 00 00 	lea    0x26a(%rip),%r8        # 8b0 <__libc_csu_fini>
 646:	48 8d 0d f3 01 00 00 	lea    0x1f3(%rip),%rcx        # 840 <__libc_csu_init>
 64d:	48 8d 3d e6 00 00 00 	lea    0xe6(%rip),%rdi        # 73a <main>
 654:	ff 15 86 09 20 00    	callq  *0x200986(%rip)        # 200fe0 <__libc_start_main@GLIBC_2.2.5>
 65a:	f4                   	hlt    
 65b:	0f 1f 44 00 00       	nopl   0x0(%rax,%rax,1)

0000000000000660 <deregister_tm_clones>:
 660:	48 8d 3d a9 09 20 00 	lea    0x2009a9(%rip),%rdi        # 201010 <__TMC_END__>
 667:	55                   	push   %rbp
 668:	48 8d 05 a1 09 20 00 	lea    0x2009a1(%rip),%rax        # 201010 <__TMC_END__>
 66f:	48 39 f8             	cmp    %rdi,%rax
 672:	48 89 e5             	mov    %rsp,%rbp
 675:	74 19                	je     690 <deregister_tm_clones+0x30>
 677:	48 8b 05 5a 09 20 00 	mov    0x20095a(%rip),%rax        # 200fd8 <_ITM_deregisterTMCloneTable>
 67e:	48 85 c0             	test   %rax,%rax
 681:	74 0d                	je     690 <deregister_tm_clones+0x30>
 683:	5d                   	pop    %rbp
 684:	ff e0                	jmpq   *%rax
 686:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 68d:	00 00 00 
 690:	5d                   	pop    %rbp
 691:	c3                   	retq   
 692:	0f 1f 40 00          	nopl   0x0(%rax)
 696:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 69d:	00 00 00 

00000000000006a0 <register_tm_clones>:
 6a0:	48 8d 3d 69 09 20 00 	lea    0x200969(%rip),%rdi        # 201010 <__TMC_END__>
 6a7:	48 8d 35 62 09 20 00 	lea    0x200962(%rip),%rsi        # 201010 <__TMC_END__>
 6ae:	55                   	push   %rbp
 6af:	48 29 fe             	sub    %rdi,%rsi
 6b2:	48 89 e5             	mov    %rsp,%rbp
 6b5:	48 c1 fe 03          	sar    $0x3,%rsi
 6b9:	48 89 f0             	mov    %rsi,%rax
 6bc:	48 c1 e8 3f          	shr    $0x3f,%rax
 6c0:	48 01 c6             	add    %rax,%rsi
 6c3:	48 d1 fe             	sar    %rsi
 6c6:	74 18                	je     6e0 <register_tm_clones+0x40>
 6c8:	48 8b 05 21 09 20 00 	mov    0x200921(%rip),%rax        # 200ff0 <_ITM_registerTMCloneTable>
 6cf:	48 85 c0             	test   %rax,%rax
 6d2:	74 0c                	je     6e0 <register_tm_clones+0x40>
 6d4:	5d                   	pop    %rbp
 6d5:	ff e0                	jmpq   *%rax
 6d7:	66 0f 1f 84 00 00 00 	nopw   0x0(%rax,%rax,1)
 6de:	00 00 
 6e0:	5d                   	pop    %rbp
 6e1:	c3                   	retq   
 6e2:	0f 1f 40 00          	nopl   0x0(%rax)
 6e6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 6ed:	00 00 00 

00000000000006f0 <__do_global_dtors_aux>:
 6f0:	80 3d 19 09 20 00 00 	cmpb   $0x0,0x200919(%rip)        # 201010 <__TMC_END__>
 6f7:	75 2f                	jne    728 <__do_global_dtors_aux+0x38>
 6f9:	48 83 3d cf 08 20 00 	cmpq   $0x0,0x2008cf(%rip)        # 200fd0 <__cxa_finalize@GLIBC_2.2.5>
 700:	00 
 701:	55                   	push   %rbp
 702:	48 89 e5             	mov    %rsp,%rbp
 705:	74 0c                	je     713 <__do_global_dtors_aux+0x23>
 707:	48 8b 3d fa 08 20 00 	mov    0x2008fa(%rip),%rdi        # 201008 <__dso_handle>
 70e:	e8 0d ff ff ff       	callq  620 <__cxa_finalize@plt>
 713:	e8 48 ff ff ff       	callq  660 <deregister_tm_clones>
 718:	c6 05 f1 08 20 00 01 	movb   $0x1,0x2008f1(%rip)        # 201010 <__TMC_END__>
 71f:	5d                   	pop    %rbp
 720:	c3                   	retq   
 721:	0f 1f 80 00 00 00 00 	nopl   0x0(%rax)
 728:	f3 c3                	repz retq 
 72a:	66 0f 1f 44 00 00    	nopw   0x0(%rax,%rax,1)

0000000000000730 <frame_dummy>:
 730:	55                   	push   %rbp
 731:	48 89 e5             	mov    %rsp,%rbp
 734:	5d                   	pop    %rbp
 735:	e9 66 ff ff ff       	jmpq   6a0 <register_tm_clones>

000000000000073a <main>:
 73a:	55                   	push   %rbp
 73b:	48 89 e5             	mov    %rsp,%rbp
 73e:	f3 0f 10 05 82 01 00 	movss  0x182(%rip),%xmm0        # 8c8 <_ZStL19piecewise_construct+0x4>
 745:	00 
 746:	f3 0f 11 45 f8       	movss  %xmm0,-0x8(%rbp)
 74b:	f3 0f 10 05 79 01 00 	movss  0x179(%rip),%xmm0        # 8cc <_ZStL19piecewise_construct+0x8>
 752:	00 
 753:	f3 0f 11 45 fc       	movss  %xmm0,-0x4(%rbp)
 758:	f3 0f 10 05 68 01 00 	movss  0x168(%rip),%xmm0        # 8c8 <_ZStL19piecewise_construct+0x4>
 75f:	00 
 760:	f3 0f 11 45 f0       	movss  %xmm0,-0x10(%rbp)
 765:	c7 45 f4 00 00 00 00 	movl   $0x0,-0xc(%rbp)
 76c:	81 7d f4 7f 4a 5d 05 	cmpl   $0x55d4a7f,-0xc(%rbp)
 773:	7f 5e                	jg     7d3 <main+0x99>
 775:	f3 0f 10 4d f0       	movss  -0x10(%rbp),%xmm1
 77a:	f3 0f 10 05 46 01 00 	movss  0x146(%rip),%xmm0        # 8c8 <_ZStL19piecewise_construct+0x4>
 781:	00 
 782:	f3 0f 59 c1          	mulss  %xmm1,%xmm0
 786:	f3 0f 11 45 f0       	movss  %xmm0,-0x10(%rbp)
 78b:	f3 0f 10 45 f0       	movss  -0x10(%rbp),%xmm0
 790:	f3 0f 10 0d 34 01 00 	movss  0x134(%rip),%xmm1        # 8cc <_ZStL19piecewise_construct+0x8>
 797:	00 
 798:	f3 0f 5e c1          	divss  %xmm1,%xmm0
 79c:	f3 0f 11 45 f0       	movss  %xmm0,-0x10(%rbp)
 7a1:	f3 0f 10 4d f0       	movss  -0x10(%rbp),%xmm1
 7a6:	f3 0f 10 05 22 01 00 	movss  0x122(%rip),%xmm0        # 8d0 <_ZStL19piecewise_construct+0xc>
 7ad:	00 
 7ae:	66 0f ef c0          	pxor   %xmm0,%xmm0
 7b2:	f3 0f 11 45 f0       	movss  %xmm0,-0x10(%rbp)
 7b7:	f3 0f 10 45 f0       	movss  -0x10(%rbp),%xmm0
 7bc:	f3 0f 10 0d 0c 01 00 	movss  0x10c(%rip),%xmm1        # 8d0 <_ZStL19piecewise_construct+0xc>
 7c3:	00 
 7c4:	f3 0f 5c c1          	subss  %xmm1,%xmm0
 7c8:	f3 0f 11 45 f0       	movss  %xmm0,-0x10(%rbp)
 7cd:	83 45 f4 01          	addl   $0x1,-0xc(%rbp)
 7d1:	eb 99                	jmp    76c <main+0x32>
 7d3:	b8 00 00 00 00       	mov    $0x0,%eax
 7d8:	5d                   	pop    %rbp
 7d9:	c3                   	retq   

00000000000007da <_Z41__static_initialization_and_destruction_0ii>:
 7da:	55                   	push   %rbp
 7db:	48 89 e5             	mov    %rsp,%rbp
 7de:	48 83 ec 10          	sub    $0x10,%rsp
 7e2:	89 7d fc             	mov    %edi,-0x4(%rbp)
 7e5:	89 75 f8             	mov    %esi,-0x8(%rbp)
 7e8:	83 7d fc 01          	cmpl   $0x1,-0x4(%rbp)
 7ec:	75 32                	jne    820 <_Z41__static_initialization_and_destruction_0ii+0x46>
 7ee:	81 7d f8 ff ff 00 00 	cmpl   $0xffff,-0x8(%rbp)
 7f5:	75 29                	jne    820 <_Z41__static_initialization_and_destruction_0ii+0x46>
 7f7:	48 8d 3d 13 08 20 00 	lea    0x200813(%rip),%rdi        # 201011 <_ZStL8__ioinit>
 7fe:	e8 0d fe ff ff       	callq  610 <_ZNSt8ios_base4InitC1Ev@plt>
 803:	48 8d 15 fe 07 20 00 	lea    0x2007fe(%rip),%rdx        # 201008 <__dso_handle>
 80a:	48 8d 35 00 08 20 00 	lea    0x200800(%rip),%rsi        # 201011 <_ZStL8__ioinit>
 811:	48 8b 05 e0 07 20 00 	mov    0x2007e0(%rip),%rax        # 200ff8 <_ZNSt8ios_base4InitD1Ev@GLIBCXX_3.4>
 818:	48 89 c7             	mov    %rax,%rdi
 81b:	e8 e0 fd ff ff       	callq  600 <__cxa_atexit@plt>
 820:	90                   	nop
 821:	c9                   	leaveq 
 822:	c3                   	retq   

0000000000000823 <_GLOBAL__sub_I_main>:
 823:	55                   	push   %rbp
 824:	48 89 e5             	mov    %rsp,%rbp
 827:	be ff ff 00 00       	mov    $0xffff,%esi
 82c:	bf 01 00 00 00       	mov    $0x1,%edi
 831:	e8 a4 ff ff ff       	callq  7da <_Z41__static_initialization_and_destruction_0ii>
 836:	5d                   	pop    %rbp
 837:	c3                   	retq   
 838:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 83f:	00 

0000000000000840 <__libc_csu_init>:
 840:	41 57                	push   %r15
 842:	41 56                	push   %r14
 844:	49 89 d7             	mov    %rdx,%r15
 847:	41 55                	push   %r13
 849:	41 54                	push   %r12
 84b:	4c 8d 25 3e 05 20 00 	lea    0x20053e(%rip),%r12        # 200d90 <__frame_dummy_init_array_entry>
 852:	55                   	push   %rbp
 853:	48 8d 2d 46 05 20 00 	lea    0x200546(%rip),%rbp        # 200da0 <__init_array_end>
 85a:	53                   	push   %rbx
 85b:	41 89 fd             	mov    %edi,%r13d
 85e:	49 89 f6             	mov    %rsi,%r14
 861:	4c 29 e5             	sub    %r12,%rbp
 864:	48 83 ec 08          	sub    $0x8,%rsp
 868:	48 c1 fd 03          	sar    $0x3,%rbp
 86c:	e8 67 fd ff ff       	callq  5d8 <_init>
 871:	48 85 ed             	test   %rbp,%rbp
 874:	74 20                	je     896 <__libc_csu_init+0x56>
 876:	31 db                	xor    %ebx,%ebx
 878:	0f 1f 84 00 00 00 00 	nopl   0x0(%rax,%rax,1)
 87f:	00 
 880:	4c 89 fa             	mov    %r15,%rdx
 883:	4c 89 f6             	mov    %r14,%rsi
 886:	44 89 ef             	mov    %r13d,%edi
 889:	41 ff 14 dc          	callq  *(%r12,%rbx,8)
 88d:	48 83 c3 01          	add    $0x1,%rbx
 891:	48 39 dd             	cmp    %rbx,%rbp
 894:	75 ea                	jne    880 <__libc_csu_init+0x40>
 896:	48 83 c4 08          	add    $0x8,%rsp
 89a:	5b                   	pop    %rbx
 89b:	5d                   	pop    %rbp
 89c:	41 5c                	pop    %r12
 89e:	41 5d                	pop    %r13
 8a0:	41 5e                	pop    %r14
 8a2:	41 5f                	pop    %r15
 8a4:	c3                   	retq   
 8a5:	90                   	nop
 8a6:	66 2e 0f 1f 84 00 00 	nopw   %cs:0x0(%rax,%rax,1)
 8ad:	00 00 00 

00000000000008b0 <__libc_csu_fini>:
 8b0:	f3 c3                	repz retq 

Disassembly of section .fini:

00000000000008b4 <_fini>:
 8b4:	48 83 ec 08          	sub    $0x8,%rsp
 8b8:	48 83 c4 08          	add    $0x8,%rsp
 8bc:	c3                   	retq   
