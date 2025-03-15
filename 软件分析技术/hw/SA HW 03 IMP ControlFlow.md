修改数据结构，首先用新类型 Edges 表示边的出入基本块以及边的类型；
将 PrimitiveNode 改为存放一系列基本语句，表示一个基本块，也就是最底层的 Node；
CompoundNode 表示一个子控制流图，nodes 存放一系列 PrimitiveNode，也就是基本块，edges 存放边，startNode 和 endNode 分别表示开始和结束的基本块（分别没有入边和出边，当然，他们也可能是同一个基本块）

用全局变量 nextID 来给语句编号，方便区分

```
Node {} 
nextID = 0

ControlFlowEdge Implements Edge{
	int from;
	int to;
	string type;
}
PrimitiveNode implements Node { 
	List<string> content; 
}
CompoundNode implements Node { 
	Map<int, Node> nodes; 
	List<Edge> edges; 
	int startNode; 
	int endNode; 
}
```

先定义一个函数来合并两个子控制流图，分为串并行两种情况

并行情况：直接把所有信息 copy ，合成并返回一个大的，不完善的控制流图，以待进一步处理

串行情况：基本块的合并会在前一个图的尾基本块和后一个图的首基本块发生，如果首基本块不是某个跳转的出口，那么就是可以合并的。合并的信息包括：nodes 里存放的编号，edges 里的编号，以及两个 content

```
//isSerial 表示是否是串行的
Node Union(Node preNode, Node nxtNode, bool isSerial) {
	//映射是每个block的startNode到每个block
	nodes = mapMerge(preNode.nodes, nxtNode.nodes) 
	edges = listMerge(preNode.edges, nxtNode.edges)
	startNode = preNode.startNode;
	endNode = nxtNode.endNode;
	
	//不是串行，不合并
	if(!isSerial) 
		return new CompoundNode(nodes, edges, startNode, endNode)
	
	//串行,合并基本块
	bool merge = 1 
	int x = preNode.endNode
	int y = nxtNode.startNode
	//如果将要合并的后一个块是某个跳转的出口，则不合并
	for edge in edges:
		if(edge.to == y) merge = 0
	
	if(!merge) { // 直接相连
		edges.put(
			ControlFlowEdge(x, y, "Jmp") )
		return new CompoundNode(nodes, edges, startNode, endNode)
	}

	//合并,将其存储的基本语句连起来
	nodes[x].content.cat(nodes[y].content)
	for edge in edges://修改边的信息
		if(edge.from == y) edge.from = x
	nodes.delete(x)//删除
	return new CompoundNode(nodes, edges, startNode, endNode)
}
```

对于基本语句，直接创建一个只包含一个基本块，基本块里只有一个语句的子控制流图并返回
```
f(skip) = {
	nextID++;
	Node p = new PrimitiveNode({"skip"})
	return new CompoundNode({(nextID, p)}, {}, nextID, nextID)
}
f(x := e) = {
	nextID++;
	Node p = new PrimitiveNode({str(x) + ":=" + str(e)})
	return new CompoundNode({(nextID, p)}, {}, nextID, nextID)
}
```

直接调用合并函数
```
f(c1; c2) = {
	Node preNode = f(c1)
	Node nxtNode = f(c2)
	return Union(preNode, nxtNode, True)
}
```

if 语句，需要创建一个condition block 和一个 end block，把分支的两个部分以并行的方式合在一起，然后再加入块和边
```
f(if e then c1 else c2 end) = { 
	//新建条件语句和end
	nextID++;
	Node condititonNode = new PrimitiveNode({str(e)})
	nextID++;
	Node endifNode = new PrimitiveNode({"end"})

	Node preNode = f(c1)
	Node nxtNode = f(c2)
	Node unionNode = Union(preNode, nxtNode, False) // 并行合并
	
	//加入新建的基本语句
	unionNode.nodes.put(nextID-1, condititonNode)
	unionNode.nodes.put(nextID, endifNode)
	
	//条件为真
	unionNode.edges.put(
		ControlFlowEdge(nextID-1, preNode.startNode, "True") )
	//条件为假
	unionNode.edges.put(
		ControlFlowEdge(nextID-1, nxtNode.startNode, "False") )
	//无条件跳转
	unionNode.edges.put(
		ControlFlowEdge(preNode.endNode, nextID, "Jmp") )
	unionNode.edges.put(
		ControlFlowEdge(nxtNode.endNode, nextID, "Jmp") )
		
	return unionNode 
}
```

while 语句类似
```
f(while e do c end) = {
//新建条件语句和end
	nextID++;
	Node condititonNode = new PrimitiveNode({str(e)})
	nextID++;
	Node endwhileNode = new PrimitiveNode({"end"})

	nodes = f(c).nodes
	bodyNode.nodes.put(nextID - 1, condititonNode)
	bodyNode.nodes.put(nextID, endwhileNode)
	
	edges = f(c).edges
	//while 为真
	edges.put(
		ControlFlowEdge(nextID - 1, f(c).startNode, "True") )
	//while 为假
	edges.put(
		ControlFlowEdge(nextID - 1, nextID, "False") )
	//无条件跳转
	edges.put(
		ControlFlowEdge(f(c).endNode, nextID - 1, "Jmp") )

	startNode = nextID - 1;
	endNode = nextID

	return new CompoundNode(nodes, edges, startNode, endNode)
}
```
