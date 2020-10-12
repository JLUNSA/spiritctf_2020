## EzVm
虚拟机题，程序实现了个基于栈的虚拟机，为了平衡难度将指令用`std::mt19937`加密了，并且~~因为STL模板编译出来太难看了~~所以给了pdb。

程序大致框架不难，先解密指令，然后一个while循环里面用switch找对应的操作。应用内存~~为了偷懒~~直接用了`std
::stack`。

指令部分包含入栈出栈、读取打印字符（串）、加减乘除、异或、左右移、对比、跳转。

解题思路应该先手动把解密后的内存dump出来或者干脆自己写个程序用于解密，然后根据switch/case里面的内容猜测每个指令的用途，并且将指令区parse出来，然后人工分析这些指令做了啥。

实际上程序先把加密后的flag倒序压进栈，然后逐字符读取用户输入，然后将每个用户输入的字符乘以0x17，加上0x41，然后与0xc6异或。

知道了这点我们就可以先给所有可能的字符打个表：
```python
import string
src = bytes(string.printable, encoding="u8")
for i in src:
    c = (i * 0x17) & 0xff
    c = (c + 0x41) & 0xff
    c = c ^ 0xc6
    print(hex(c) + ",", end="")
```
得到
```
0x57,0x6e,0x79,0x10,0x2b,0xc2,0xdd,0xf4,0x8f,0xa6,0x3e,0xc9,0xe0,0xfb,0x92,0xad,0x44,0x5f,0x76,0x1,0x18,0x33,0xca,0xe5,0xfc,0x97,0xae,0xb9,0x50,0x6b,0x2,0x1d,0x34,0xcf,0xe6,0xf1,0xde,0xe9,0x80,0x9b,0xb2,0x4d,0x64,0x7f,0x16,0x21,0x38,0xd3,0xea,0x85,0x9c,0xb7,0x4e,0x59,0x70,0xb,0x22,0x3d,0xd4,0xef,0x86,0x91,0xfe,0x89,0xa0,0xbb,0x52,0x6d,0x4,0x1f,0x36,0xc1,0xd8,0xf3,0x8a,0xa5,0xbc,0xb1,0x48,0x63,0x7a,0x15,0x2c,0xc7,0xa8,0x43,0x5a,0x75,0xc,0x27,0x88,0xa3,0xba,0x55,0xe7,0xd6,0xe1,0xaa,0xf8,0x93,
```
然后把指令中压进栈进行对比的flag取出，然后跟表对比，即可得到flag
```python
import string

tbl1 = [0x57,0x6e,0x79,0x10,0x2b,0xc2,0xdd,0xf4,0x8f,0xa6,0x3e,0xc9,0xe0,0xfb,0x92,0xad,0x44,0x5f,0x76,0x1,0x18,0x33,0xca,0xe5,0xfc,0x97,0xae,0xb9,0x50,0x6b,0x2,0x1d,0x34,0xcf,0xe6,0xf1,0xde,0xe9,0x80,0x9b,0xb2,0x4d,0x64,0x7f,0x16,0x21,0x38,0xd3,0xea,0x85,0x9c,0xb7,0x4e,0x59,0x70,0xb,0x22,0x3d,0xd4,0xef,0x86,0x91,0xfe,0x89,0xa0,0xbb,0x52,0x6d,0x4,0x1f,0x36,0xc1,0xd8,0xf3,0x8a,0xa5,0xbc,0xb1,0x48,0x63,0x7a,0x15,0x2c,0xc7,0xa8,0x43,0x5a,0x75,0xc,0x27,0x88,0xa3,0xba,0x55,0xe7,0xd6,0xe1,0xaa,0xf8,0x93]
tbl2 = string.printable

encrypted = [0xba,0xad,0x6e,0xf4,0xdd,0xdd,0xdd,0x8f,0xfb,0x2b,0x57,0xf4,0xc9,0x8a,0x57,0xad,0x2b,0xa6,0x8a,0xa6,0xf4,0xc2,0x2b,0x8a,0xc9,0x8f,0x10,0x6e,0x8a,0x10,0xdd,0x92,0xfb,0xfb,0x79,0x79,0xdd,0x88,0x6b,0x76,0xb9,0x76,0x97,0x70][::-1]
result = ""
for i in encrypted:
    index = tbl1.index(i)
    result += tbl2[index]
print(result)
```
输出: `Spirit{622dde63-138b-4579-94f0-b704d866671f}`