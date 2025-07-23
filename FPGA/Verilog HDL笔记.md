# Verilog HDL笔记

## Verilog基础

### Verilog language

#### I. Basics

##### wire

###### 类型定义

wire类型类似于物理导线，不存储值，有方向性的将值从一端传输到另一端，用于连接电路中的各模块

​	见下图，wire in连接着前部模块，将值从前部模块中引入当前模块，wire out连接着后部模块，此时需要在当前模块中通过赋值将两根“导线”in和out连接

###### 赋值语句——assign连续赋值语句

对于wire型变量进行赋值时需要使用assign连续赋值语句，一旦输入信号发生变化，输出信号能立即更新

![image-20250722101642707](C:\Users\30606\AppData\Roaming\Typora\typora-user-images\image-20250722101642707.png)

例如：在top_module模块中，前端接入一个wire类型接口，后端输出一个wire类型接口，要将这两个wire类型变量连接起来需要使用assign连续赋值语句

###### 特点

1、连续赋值语句**不需要在意端口顺序**

When you have multiple assign statements, the **order** in which they appear in the code **does not matter**



##### 运算逻辑——分为**<u>*算数运算和逻辑运算*</u>**

###### 算数运算符

| 运算逻辑 | 运算符 |
| -------- | ------ |
| 按位取反 | ~      |
| 按位与   | &      |
| 按位或   | \|     |
| 按位异或 | ^      |

###### 逻辑运算符

| 运算逻辑 | 运算符 |
| -------- | ------ |
| 逻辑非   | ！     |
| 逻辑与   | &&     |
| 逻辑或   | \|\|   |





##### wire decl

对于一个模块中的各部分components，需要使用中间wire变量进行连接，此时声明的中间wire变量应当声明在模块内部

![image-20250722104743262](C:\Users\30606\AppData\Roaming\Typora\typora-user-images\image-20250722104743262.png)

例如图中的**wire not_in**

这样声明的中间变量在外部是invisiable的



#### II. Vectors——向量

向量用于将一组相关的信号打包为一组，更加方便。

##### 定义方式

向量必须被定义，定义方法为：

```verilog
type [upper:lower] vector_name；
//例如：
wire [99:0] w;
```

向量大小在前面申明，名称在后



###### **<u>*打包与未打包数组*</u>**

位于**向量名前的是打包数组**，表示打包的位数，在向量名后的是未打包数组，通常用于声明**内存数组**

```verilog
type [upper:lower] vector_name [upper:lower]；
//例如：
wire [99:0] w [10:0];
```



##### 访问方式

###### 访问整个向量

通过向量名称实现

```verilog
assign w = a;
```

要调用一个n位宽中第i个位的值，使用：

```verilog
w[i]/w[i:i]
```

要访问n位宽向量中第i~m的数据位数

```
w[i:m]
```



##### 端序限定

**向量的端序必须统一**，不能在前文已经声明了[3:0] vec后，于后文书写vec[0:3]

由于端序必须统一，要对一个向量进行翻转时，不能直接用端序方法，最好使用位拼接操作



##### 赋值方式

```verilog
wire [3:0] w;
assign w = 3'b001;
```



##### 位拼接

使用”{}"操作

```verilog
wire [3:0] a = 4'b1010;
wire [1:0] b = 2'b11;
wire [7:0] result;

// 拼接为8位向量：{高4位, 中间2位, 低2位}
assign result = {a, b, 2'b01};  // 结果为8'b1010_1101
```



##### 复制操作

使用"{N{vector}}"进行向量的复制操作，复制向量vector N遍然后拼接

```verilog
wire [1:0] a = 2'b10;
wire [7:0] result;

// 复制3次a并拼接1位0
assign result = {3{a}, 1'b0};  // 结果为8'b10_10_10_0
```



#### III. Module——模块

##### 模块调用

###### 位置调用法

按照原模块端口顺序，按顺序连接端口名称

```verilog
mod_a instance (a,b,c);
```



###### 名称调用法

按照名称将信号连接到端口的模块

```verilog
mod_a instance (.in1(a),.out(c),.in2(b));
```



#### IV. Procedures——过程

##### 赋值方式

###### 连续赋值——assign

只能在**过程块外部使用**



###### 阻塞赋值——“=”

赋值语句立即执行，阻塞后续语句，直至当前语句完成

具有**顺序依赖**效果，后续语句必须依赖于前序阻塞赋值的结果



###### 非阻塞赋值——“<=”

赋值语句在当前时间步结束时同步更新，不阻塞后续语句执行

**无顺序依赖**，在赋值时刻并行执行



##### 变量类型

在always过程块中，只允许对**reg类型**的变量进行操作



##### always块

always块中不允许使用连续赋值 “assign”

always过程块中可以使用诸如**case/if-else**等语句块

###### 基本语法

```verilog
always @(<sensitivity_list>) begin
    // 语句块
end
```

**I.** **敏感列表sensitivity_list**

用于指定触发always块执行的信号变化

对于**组合逻辑**，需要包含所有输入信号：“*”

对于**时序逻辑**，通常为时钟边沿：posedge clk / negedge clk



###### 组合逻辑

**敏感列表**——包含所有输入信号（组合逻辑中一旦输入信号发生改变，输出必然发生改变，相当于连续）

**赋值方式**——阻塞赋值（=）





###### **时序逻辑**

**敏感列表**——时钟边沿（必要时包含异步复位（时钟信号+复位信号））

**赋值方式**——非阻塞赋值（<=）



###### 锁存/闩锁（latch）

**敏感列表**——不完整的组合逻辑敏感列表

**结果**——意外生成锁存器，导致时序问题



##### case块

用于多路分支选择，匹配第一个等于该值的分支后立即跳出

```verilog
case (<expression>)
    <value1>: <statement1>;
    <value2>: <statement2>;
    // ...
    default: <default_statement>;  // 可选
endcase
	
//————————————————例1————————————————————//
case (sel)
        2'b00: out = 4'b0001;
        2'b01: out = 4'b0010;
        2'b10: out = 4'b0100;
        2'b11: out = 4'b1000;
        default: out = 4'b0000;  // 可选，但推荐添加
endcase

//-----------------例2-------------------//
//带有多条语句的分支
case (state)
    S_IDLE: begin
        counter = 0;
        enable = 1'b0;
    end
    S_RUN: begin
        counter = counter + 1;
        enable = 1'b1;
    end
    default: ;  // 空语句
endcase
```



##### if-else块

if-else块必须在always过程块中使用，并且，单条语句**不需要使用** begin-end，多条语句**必须使用** begin-end

```verilog
always @(*) begin
    if (sel)
        out = a;  // 单条语句，无需begin-end
    else
        out = b;  // 单条语句，无需begin-end
end
```

```verilog
always @(*) begin
    if (condition) begin
        out1 = a;  // 多条语句，需用begin-end
        out2 = b;
    end else begin
        out1 = c;
        out2 = d;
    end
end
```

