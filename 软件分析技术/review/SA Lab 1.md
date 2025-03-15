分析分为三种层级：Method, Class, Program ，分别通过继承MethodAnslysis, ClassAnalysis, ProgramAnalysis来实现

BenchmarkN
- alloc 标记分配点，遇到 New语句，将语句和 id 放入 obj_ids 这个 Map 中
- test 标记测试点编号和被测变量



先实现了一个非上下文敏感的版本，主要用到了 Tai-e 的 IR 相关类，参考了 HeapModel 的设计


