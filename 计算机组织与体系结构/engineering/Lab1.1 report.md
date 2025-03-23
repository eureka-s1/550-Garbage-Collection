author：2300012969 盛梓航

>**一、**   **针对系统评测的不同目标会采用不同的评测程序。在目前已有的评测程序中，为下列评测目标找到合适的评测程序（列出即可）。**

| 评测目标        | 评测程序                                                         |
| ----------- | ------------------------------------------------------------ |
| CPU整点性能     | SPECint (SPEC CPU整数测试) <br>Geekbench (整数部分)<br>Dhrystone     |
| CPU浮点性能     | SPECfp (SPEC CPU浮点测试)<br>Linpack (HPL)<br>Whetstone          |
| 计算机事务处理能力   | TPC-C (联机事务处理)<br>TPC-E (企业级事务处理)                            |
| 嵌入式系统计算能力   | EEMBC CoreMark<br>EEMBC AutoBench (汽车嵌入式)                    |
| 2D处理能力      | X11perf (X Window系统性能)<br>Cairo Graphics Benchmark           |
| 3D处理能力      | 3DMark<br>Cinebench<br>Unigine Heaven/Valley                 |
| 并行计算性能      | HPL (High Performance Linpack)<br>NAS Parallel Benchmarks    |
| 系统响应速度      | UnixBench (系统综合性能)<br>PCMark (系统整体响应)                        |
| 编译优化能力      | SPECrate (编译器优化效率)<br>LLVM Test Suite                        |
| 操作系统性能      | Phoronix Test Suite<br>UnixBench<br>LMbench (延迟和带宽)          |
| 多媒体处理能力     | x264/x265视频编码测试<br>POV-Ray (光线追踪渲染)                          |
| IO处理能力      | fio (灵活IO测试)<br>IOzone (文件系统性能)<br>CrystalDiskMark (磁盘性能)    |
| 浏览器性能       | Speedometer 2.0<br>JetStream 2                               |
| 网络传输速率      | iPerf3 (带宽与吞吐量)<br>Netperf<br>LAN Speed Test                 |
| Java运行环境性能  | SPECjbb (Java服务器性能)<br>DaCapo Benchmark<br>Renaissance Suite |
| 邮件服务性能      | SPECmail (邮件服务器负载测试)<br>MailStone                            |
| 文件服务器性能     | SPECsfs (文件系统吞吐量)<br>fio (模拟多用户并发IO)<br>Apache JMeter        |
| Web服务器性能    | ApacheBench (ab)<br>wrk<br>Siege<br>WebBench                 |

-----
>**二、   阅读文献（Reinhold P.Weicker, An Overview of Common Benchmarks, IEEE Computer, December 1990.）并回答下面的问题**

>(1) 简述用于性能评测的MIPS指标之含义，以及它是如何被计算的。

**字面意义**：MIPS（Millions of Instructions Per Second）表示“每秒百万条指令”，用于直接衡量计算机的指令执行速度。

**相对意义**：随着计算机架构的发展，尤其是 RISC 和 CISC 架构的出现，MIPS 指标逐渐被用作一种**相对性能**指标。例如，以VAX 11/780计算机为基准，其性能被定义为1 MIPS。其他计算机的性能则通过与VAX 11/780的性能比较来确定，称为“VAX MIPS”或“VUP”（VAX单位性能）。

>(2) 使用linux下的剖视工具（例如gprof）对 dhrystone 和 whetstone 进行剖视，参考论文Table 1形式给出数据，你的结果和该论文是否一致？如有不同，请说明原因。
##### dhrystone
使用 `perf`来剖视，以下分别是 `cc_dry2, cc_dry2reg, gcc_dry2, gcc_dry2reg`的结果
![[Pasted image 20250228211355.png|]]
![[Pasted image 20250228211759.png]]
![[Pasted image 20250228211934.png]]
![[Pasted image 20250228212603.png]]

可以看出，这和论文中给出的数据大不相同。如今有很大一部分性能开销都在 `strcmp`上（`strcmp_avx2` 在2013年后使用，一次处理 32 字节）。

可能是 Dhrystone 代码量过小，在现代CPU中，它能够被放进指令缓存中，所以它并不能严格的测量取指性能。也有可能是经过编译器迭代后优化掉了一部分测试项（在Dhrystone中有大量的字符串复制语句，而一个优化性能好的编译器能够在去掉循环的情形下通过一连串字的移动替代对字符串的复制，这将会快很多）

>(3) 论文中讨论了CPU之外可能对性能造成影响的几种因素。请阐述文中不同编程语言对程序性能影响的观点，并分别使用两种不同的语言使用相同算法实现快速排序、矩阵乘法、求Ackermann函数，验证以上观点。

不同编译语言, 在函数调用序列, 指针语法和字符串语法等方面的不同会导致性能的差异

|           | C     | Java  |
| --------- | ----- | ----- |
| quicksort | 0.70  | 0.77  |
| matrix    | 0.069 | 0.081 |
| ackermann | 0.18  | 0.238 |
能看到，一般情况下，C语言的程序比相同实现的Java程序要快，这证明了编程语言对于性能测试的影响。

具体实现见附件

----
>**三、**   **性能评测**

##### 工作背景和评测目标
本次评测使用了北京大学 Linux 俱乐部维护的云计算实验平台 [**PKU Clab**](https://clab.pku.edu.cn/) ：开箱即用的免费云计算服务，为教学与科研服务

Clab 性能优异，稳定可靠，采用最新的硬件，确保您的服务有足够的性能，采用多副本技术，确保服务的稳定性和可靠性。（以上来自官网）我们将来评测其使用的虚拟CPU。

#####  **评测环境**

| 项目            | 虚拟CPU                                                                                              |
| ------------- | -------------------------------------------------------------------------------------------------- |
| 处理器型号及相关参数    | AMD EPYC 7773X 64-Core Processor（云主机 2 核）<br>cpu MHz:  2195.874<br>cache size:  512 KB             |
| 内存            | 2G                                                                                                 |
| 外存            | 40G                                                                                                |
| 操作系统及其版本      | Distributor ID:  Ubuntu<br>Description:  Ubuntu 24.04.2 LTS<br>Release:  24.04<br>Codename:  noble |
| 编译器版本 （及编译参数） | gcc version 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04)                                                  |
| 库函数及其版本       | GLIBC_2.39                                                                                         |
编译参数可见注[^1]

#####  **评测步骤及要求**
注：以下结果均已多次求几何平均，具体数据可参看附件

>1.1 在linux下基于dhrystone-2.1所提供的Makefile编译dhrystone

>1.2 分别采用$10^8$、$3\times 10^8$、$5\times 10^8$、$7\times 10^8$、$9\times 10^8$为输入次数，运行编译生成的两个程序，记录、处理相关数据并做出解释。

|               | `gcc_dry2`    | `gcc_dry2reg` | Ratio      |
| ------------- | ------------- | ------------- | ---------- |
| $10^8$        | $22605664.42$ | $23346304$    | $1.032763$ |
| $3\times10^8$ | $23306001.66$ | $23176276.89$ | $0.994434$ |
| $5\times10^8$ | $23137276.8$  | $23213863.99$ | $1.00331$  |
| $7\times10^8$ | $23170813.27$ | $23260203.95$ | $1.003858$ |
| $9\times10^8$ | $23316063.88$ | $23206000.14$ | $0.995279$ |

两个程序的性能并没有看出特别的差距。

也有可能如前文所述，是 Dhrystone 代码量过小，在现代CPU中，它能够被放进指令缓存中，所以它并不能严格的测量性能。当然，缓存和内存层次结构也更加复杂，能够有效地减少内存访问延迟。

> 1.3 对dhrystone代码做少量修改，使其运行结果不变但“性能”提升.

注意到 `dhry_1.c` 有几处标注了 `not executed` 的地方，应该是 dhrystone 用一些方式规避了死代码检测，从而使得编译器不能完成完整的优化。把这些地方都注释掉后，性能获得了微弱的提升

|               | `gcc_dry2reg` | optimized `gcc_dry2reg` | Ratio      |
| ------------- | ------------- | ----------------------- | ---------- |
| $10^8$        | $23346304$    | $22986256.88$           | $1.015664$ |
| $3\times10^8$ | $23176276.89$ | $22691520.39$           | $1.021363$ |
| $5\times10^8$ | $23213863.99$ | $22825315.71$           | $1.017023$ |
| $7\times10^8$ | $23260203.95$ | $23038953.74$           | $1.009603$ |
| $9\times10^8$ | $23206000.14$ | $22855928.87$           | $1.015316$ |


>1.4 讨论采用 dhrystone 进行评测存在哪些可以改进的地方，对其做出修改、评测和说明。

Dhrystone 作为一种经典的基准测试程序，虽然在评估整数运算性能方面有一定的参考价值，但在现代处理器上已经有些过时了。

可以引入实际应用的测试模块：比如时兴的图像处理、矩阵计算、数据库操作等，以更全面地评估大数据时代下处理器的性能。

>2.1 在linux下使用编译器分别采用`-O0、-O2、-O3` 选项对whetstone程序进行编译并执行，记录评测结果。

>2.2 分别采用 $10^6、10^7、10^8$ 为输入次数，运行编译生成的可执行程序，记录、处理相关数据并做出解释。

>2.3 进一步改进 whetstone 程序性能（例如新的编译选项），用实验结果回答。

耗时太久的测试项就省略了

| MIPS or time(s) | `-O1`     | `-O2`     | `-O3`     | `-Ofast`  |
| --------------- | --------- | --------- | --------- | --------- |
| $10^6$          | $11111.1$ | $16666.7$ | $20000.0$ | $50000.0$ |
| $10^7$          | $10752.7$ | $17543.9$ | $20833.3$ | $76923.1$ |
| $10^8$          | 930s      | 570s      | 490s      | 130s      |
可以看出，在不同的优化等级下，程序的性能差距非常大。这证明了不同的编译选项对于性能测试的影响。

尤其是在优化非常激进，不会严格遵循语言标准的 `-Ofast` 下，对于浮点运算提升巨大。

##### 其他测评工具
我们还可以使用一些如 cpuz_x64 这样的工具来方便地评测性能

这是我本地电脑相对于 `Core i7-10700`  的分数对比，能很直观的看出不同处理器之间的差距
![[Pasted image 20250228235810.png|450]]
![[Pasted image 20250228235919.png]]




-----
#### 总结
对于性能，各个不同的方面都会产生影响，如语言，编译器，编译选项等。在使用一种 Benchmark 进行评测的时候，应该做好变量控制，尽量减少评测浮动。

同时，由于编译技术，处理器技术迭代地非常快，过去的评测方式不一定适合现在。需要根据时代的需要选择不同的评测方式。















[^1]: Configured with: ../src/configure -v --with-pkgversion='Ubuntu 13.3.0-6ubuntu2~24.04' --with-bugurl=file:///usr/share/doc/gcc-13/README.Bugs --enable-languages=c,ada,c++,go,d,fortran,objc,obj-c++,m2 --prefix=/usr --with-gcc-major-version-only --program-suffix=-13 --program-prefix=x86_64-linux-gnu- --enable-shared --enable-linker-build-id --libexecdir=/usr/libexec --without-included-gettext --enable-threads=posix --libdir=/usr/lib --enable-nls --enable-bootstrap --enable-clocale=gnu --enable-libstdcxx-debug --enable-libstdcxx-time=yes --with-default-libstdcxx-abi=new --enable-libstdcxx-backtrace --enable-gnu-unique-object --disable-vtable-verify --enable-plugin --enable-default-pie --with-system-zlib --enable-libphobos-checking=release --with-target-system-zlib=auto --enable-objc-gc=auto --enable-multiarch --disable-werror --enable-cet --with-arch-32=i686 --with-abi=m64 --with-multilib-list=m32,m64,mx32 --enable-multilib --with-tune=generic --enable-offload-targets=nvptx-none=/build/gcc-13-fG75Ri/gcc-13-13.3.0/debian/tmp-nvptx/usr,amdgcn-amdhsa=/build/gcc-13-fG75Ri/gcc-13-13.3.0/debian/tmp-gcn/usr --enable-offload-defaulted --without-cuda-driver --enable-checking=release --build=x86_64-linux-gnu --host=x86_64-linux-gnu --target=x86_64-linux-gnu --with-build-config=bootstrap-lto-lean --enable-link-serialization=2 
