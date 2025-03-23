2300012969 盛梓航

#### 开发环境
Clab，使用 RISC-V的64位交叉工具链riscv64-unknown-elf-gcc

`docker run --rm -it -v ~/pku/simulator:/root/simulator harsonlau/riscv-tools /bin/bash`

#### 模拟器构成
##### 存储接口
`common.h` 中定义了内存的基址和容量，用结构体 `CPU_state` 来表示寄存器堆和`pc`的状态

`memory.h` 包括了比较重要的几个部分：
- `load_image` 将指定路径的二进制程序镜像文件加载到模拟器的内存中，完成内存映射
- `mem_read` 和 `mem_write`
- `inst_fetch` 取指

##### 指令解码
`decode_operand` 中定义了各类指令（`R, S, I, U, B, J`）的编码解析方式

`decode_exec` 中可以自由定义新的指令及其对应的操作，由 `INSTPAT` 宏来解析指令编码。具体来说，涵盖了除取值外一周期的操作：
1. 将 `predict PC` 设置为默认 `PC + 4`
2. 识别编码，包括 invaild instruction 的处理
3. 解析编码，返回对应的 `src1, src2` 等
4. 完成执行、访存、写回等任务
![[Pasted image 20250321174619.png]]

主要增加的部分：
- 补充了 `B, R` 类型 
- 实现了大部分 RV64IM 指令（除 `fence, ecall` 以及 `CSR` 系）
测试通过全部 10 个测试用例

##### `Debug` 模式
实现了要求的功能，加上命令行参数 `debug` 即可进入，类似 GDB 
- `help` ：打印命令的帮助信息
- `c`：继续执行被暂停的程序
- `q`：退出模拟器
- `si [N]`：让程序单步执行N条指令后暂停执行，当N 没有给出时，缺省为1
- `info r`：打印寄存器状态（包括PC）
- `x N ADDR`：将 `ADDR` 作为起始内存地址，以十六进制 形式输出连续的N个4字节
在 `debug` 模式下默认显示更详细的信息

##### 测试程序及构建
和 simulator 的构建本质独立，主要功能是将源代码文件编译、链接生成 ELF 可执行文件，最终转换为二进制文件 .bin

`Makefile` 中指定交叉编译工具链前缀为 `riscv64-unknown-elf-`，并定义了各个工具的变量，如汇编器（AS）、C 编译器（CC），包括编译参数，如指定架构，入口点等

提供 `make all-tests` 命令来测试 `/test/src` 下所有程序

#### 总结
实现了 Lab2.1 最基础的部分

使用 `make T=prog debug` 来测试 `prog.c` 
使用 `make all-tests` 来测试 `/test/src` 下所有程序


一些坑点：
1. 32位操作与64位操作将导致不同的行为，操作是32位要截断后符号扩展
2. 对于移位 shamt 来源寄存器的移位指令，其 shamt 部分对于64位和32位分别是6位和5位。
3. `JALR` 指令忽略立即数的最低位
4. `Branch` 不将 `PC+4` 写入`GPR[rd]`，只有`JAL`与`JALR`这么做