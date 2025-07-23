# FPGA学习路径

参考教程：

•[FPGA学习路线-CSDN博客](https://blog.csdn.net/k331922164/article/details/44626989?ops_request_misc=%7B%22request%5Fid%22%3A%22798649ca2cdc177d745f5fdc23226a1c%22%2C%22scm%22%3A%2220140713.130102334..%22%7D&request_id=798649ca2cdc177d745f5fdc23226a1c&biz_id=0&utm_medium=distribute.pc_search_result.none-task-blog-2~all~top_positive~default-1-44626989-null-null.142^v102^pc_search_result_base7&utm_term=fpga学习线路&spm=1018.2226.3001.4187)

•[FPGA：我的零基础学习路线（2022秋招已上岸）持续更新中~_fpga 学习路线-CSDN博客](https://blog.csdn.net/m0_46830519/article/details/127855773)



## 一、数电

​	首先，还没学过**数电**的先学数电，数电中的卡诺图、真值表、触发器和组合/时序逻辑电路分析等是编写Verilog HDL或VHDL的基础。只有在大致了解数电基本知识的情况下才能去编写硬件描述语言

​	数电相关知识可以参考我库中的**<u>[数字逻辑电路II](https://github.com/Lionoskay/Learning-resources/tree/main/%E6%95%B0%E5%AD%97%E9%80%BB%E8%BE%91%E7%94%B5%E8%B7%AF)</u>**，重点是卡诺图，真值表和触发器这几块。当基本掌握了这些内容后就可以进入Verilog的实战。

​	由于西安交通大学的数字逻辑电路II实验主要使用Verilog语言进行开发，本文着重介绍Verilog语言的学习路径



## 二、硬件描述语言

​	硬件描述语言HDL（Verilog+VHDL）是FPGA开发的基本代码语言，重点突出**硬件**这一特点，解决问题时需要用数电的思维去编程（通过波形图反向编程等）而不是使用C语言等高级语言的思路。Verilog语法可以参考我编写的**<u>Verilog HDL笔记</u>**

​	如果喜欢跟着视频进行学习，这里推荐两个FPGA开发视频教程，这两个教程适合快速入门数电和Verilog，看完后能大概认识到FPGA能完成什么样的功能

•[零基础轻松学习FPGA，小梅哥FPGA设计思想与验证方法视频教程](https://www.bilibili.com/video/BV1KE411h7AZ/?share_source=copy_web&vd_source=b67ef7078a005d600d85a8c0876aa69c)

•[【野火】FPGA系列教学视频，真正的手把手教学，“波形图”教学法，现场画波形图写代码，硬件基于野火FPGA EP4CE10征途系列开发板，已完结_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV17z411i7er/?spm_id_from=333.999.0.0&vd_source=8cb4d3f3cb5630969f7666e55f49f2e3)

​	熟练掌握Verilog进行编程是后续FPGA开发的基础，当你觉得自己可以写一点简单的Verilog代码后哦,就可以开始刷题了。这里推荐一个Verilog刷题网站，题目比较多，涵盖了几乎所有Verilog的常用语法，每道题都会先进行教学再提供一个练习的机会，**强烈建议刷一遍里面的题**，并且认真学习每道题的前置知识（这是个全英网站，看得懂的尽量不要翻译，英文教程讲的非常好，翻译过来会丢失很多信息）

•[HDLBits](https://hdlbits.01xz.net/wiki/Main_Page)

•[HDLBits_孤独的单刀的博客-CSDN博客 ](https://blog.csdn.net/wuzhikaidetb/category_11328778.html?spm=1001.2014.3001.5482)——答案



## 三、项目

​	当你大致掌握Verilog语言后就可以尝试做一些项目,熟悉AMD的Vivado开发操作。这里我提供了西安交通大学数字逻辑电路II的实验项目，每个实验都有详细的实验指导文档，跟着实验来一遍后就基本能掌握Vivado的开发流程了

​	这个实验是基于Xilinx的EGO1平台进行的，使用了Xilinx的Artix-7系列芯片

[【依元素】Xilinx Artix-7 FPGA开发板 口袋实验平台EGO1 学习板-淘宝网](https://item.taobao.com/item.htm?spm=a1z10.1-c.w4004-18530409179.2.55712ef6VubgLu&id=574255050542)

​	将这个实验基本过完后可以做一些网上的开源项目了，具体的项目和细节可以转到

[FPGA：我的零基础学习路线（2022秋招已上岸）持续更新中~_fpga 学习路线-CSDN博客](https://blog.csdn.net/m0_46830519/article/details/127855773)

中继续查看



## 四、补充

最近太忙了，先整理到这里，有需要补充的地方可以联系我