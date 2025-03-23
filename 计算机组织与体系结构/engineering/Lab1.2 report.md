author：2300012969 盛梓航

一.  阅读2021年CF论文《A Comparative Survey of Open-Source Application Class RISC-V Processor Implementations》， 完成下述实验，回答下列问题。

> 1、根据文中给出的或网上查阅的资料，填写下表

注：不特殊注明，默认为 in-order, pipeline

| 处理器名称  | 支持的ISA   | 基本特性           | Git[^1] | Google[^2] | FPGA[^3]  | Tapeouts[^4] |
| ------ | -------- | -------------- | ------- | ---------- | --------- | ------------ |
| Rocket | RV64/32G | 5-stage        | 154     | 2050       | Chipyard  | 多次           |
| BOOM   | RV64GC   | 10-stage , OoO | 42      | 1140       | Chipyard  | 1次           |
| CVA6   | RV64GC   | 6-stage        | 161     | 939        | OpenPiton | 6次           |
| SHAKTI | RV32/64I | 5-stage        | 32      | 292        | 独立框架      | 2次           |

说明：其中 Git contributors，Google Scholar hits 数据来源是最新的

在 FPGA 支持方面，**Rocket**、**Boom** 支持 Chipyard 框架，**CVA6** 支持 OpenPiton 框架，支持面均较广；而 **SHAKTI** 独立框架，较小

Tapeouts 方面：
- **Rocket**：至少包括（查到至少11次） 
	- EOS14（IBM 45 nm SOI，双核，1.5 GHz，0.9 V）
	- Raven-3（ST 28 nm FD-SOI，单核，1.3 GHz）
	- SiFive U54（TSMC 28 nm HPC，四核，1.5 GHz）等
- **BOOM**：BROOM（TSMC 28 nm HPM ，1MB L2缓存，1 GHz，0.9 V，3.77 CoreMark/MHz）
- **CVA6**：包括 
	- Poseidon（GlobalFoundries 22 nm FD-SOI，单核，910 MHz，0.8 V）
	- Kosmodrom（1.3 GHz/300 MHz，0.8 V）
	- Baikonur（1.0 GHz/250 MHz，0.8 V）
	- Scarabaeus（单核，200 MHz，1.2 V）
	- Urania（单核 CVA6 和 CV32E40P 集群，100 MHz，1.2 V）等
- **SHAKTI**：RIMO（SCL 180 nm，350 MHz）和 RISECREEK（Intel 22 nm FinFET，70 MHz）

> 2、本文选择应用级处理器作为比较对象，请解释什么是应用级处理器 （Application-class processor），并说明这样选择的优点和不足

原文 **Application-class** : complies to the RV64I ISA base with a word size of 64 bit and if it is ca pable to boot a UNIX-based OS

应用级处理器指的是支持UNIX类操作系统的高性能处理器
- 优点：
	- 支持复杂的软件生态系统，可以利用现有的库、驱动和程序
	- 具有内存管理和用户程序隔离功能，支持多线程并发执行
- 缺点：
	- 硬件复杂性较高，需特权模式、TLB、缓存等（在比较时需要考虑更多的因素）
	- 需要较大的物理空间和功耗（限制了比较的灵活性和可扩展性）

> 3、请阐述文中对四个处理器进行比较时采用的思路和方法，并举例说明

**思路**：统一配置与测试环境，并使用多角度（性能、面积、功耗和能效）的专业测试

**方法**：统一配置，所有处理器采用相同的缓存大小（L1D/L1I 16KB）、分支预测参数（BHT 512、BTB 32、RAS 8）和工具链设置。

测试平台，Xilinx Virtex UltraScale+ FPGA 和 GlobalFoundries 22FDX ASIC

基准测试：
- 性能，如 Dhrystone、CoreMark、SPEC CPU 2017，对比每MHz性能（IPC）和最大频率（Fmax）
- 面积，Vivado和Genus工具链生成了详细的资源利用报告，比较处理器在 FPGA 和 ASIC 技术下的面积占用情况
- 功耗，使用功率管理总线（PMBus）测量 FPGA 上的静态和动态功耗，并通过合成工具估计 ASIC 上的功耗
- 能效，计算处理器完成特定工作负载所需的能量，比较其能效指标（如 MOp/J 或 GOp/J）

> 4、第五章中使用性能、面积和能效作为评价指标，对上述四个处理器进行比较，得到结论。试回答：

>（1）对性能进行比较时，采用下图中参数作为评价指标，试一一解释。
![[Pasted image 20250307150132.png]]

**DMIPS per MHz**：每MHz下Dhrystone测试的DMIPS得分，反映整数运算效率
**CoreMark per MHz**：每MHz下CoreMark得分，衡量嵌入式核心的综合性能
**SPEC17 IPC**：SPECintrate测试的每周期指令数（IPC），体现复杂负载下的指令吞吐量
**Fmax [MHz]**：处理器在XCVU9P FPGA和22FDX ASIC上的最大时钟频率，反映工艺适配性

>（2）对能效进行比较时，对比了功耗（power consumption）和能效（energy efficiency），通过论文或查阅资料，解释他们的异同

**功耗**：处理器运行时消耗的总功率（静态+动态），单位为毫瓦（mW）
**能效**：单位能量完成的运算量（如MOp/J），综合性能与功耗的比值

前者衡量能量消耗，后者反映能量利用效率

>（3）看下面的图表，尝试分析BOOM处理器的特点
![[Pasted image 20250307154855.png]]

由于 **BOOM** 处理器是一个乱序执行（OoO），并使用复杂分支预测（TAGE/NLP）的处理器，通过指令级并行在**性能**上遥遥领先。  ASIC上Fmax最高（943 MHz）；因为跨SLR布局限制，在FPGA频率低（88 MHz，最低）

总之，BOOM 在 ASIC 处理性能上领先，代价在 FPGA 上表现并不好

---
二. 分析下列指令系统、微结构等方面的变化，对程序中的指令数目、CPI、时钟周期以及整体性能的影响。如有影响，请在下表内写明提升（增加）或降低 （减少）或不确定，并说明原因。如无影响，请写无影响并说明原因。

|              | 程序指令数 | CPI     | 时钟周期   | 整体性能 | 原因说明                                      |
| ------------ | ----- | ------- | ------ | ---- | ----------------------------------------- |
| **增加复杂指令**   | 减少    | 增加      | 增加     | 不确定  | 复杂指令减少指令数，<br>但执行时间可能更长，<br>CPI增加，频率可能下降。 |
| **减少通用寄存器**  | 增加    | **无影响** | **下降** | 降低   | 寄存器不足导致更多访存，<br>指令数和 CPI 增加，<br>但时钟周期不变。  |
| **改善存储速度**   | 无影响   | 降低      | 无影响    | 提升   | 减少访存延迟，CPI 下降                             |
| **添加16位指令**  | 不确定   | 降低      | 降低     | 提升   | 指令密度提升，总数不确定，<br>短指令可能降低CPI，<br>频率可能优化。   |
| **CISC转微操作** | 增加    | 降低      | 降低     | 不确定  | 指令数上升，CPI下降，\|<br>时钟周期减小，性能不确定<br>        |




[^1]:  Git contributors (community activity)
[^2]:  Google Scholar hits (academic impact)
[^3]:  FPGA Boards (technology support)
[^4]:  Tapeouts (technology support especially documents)
