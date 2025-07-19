#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#define STACK_INIT_SEIZ 100
#define STACKINCREMENT 10
#define ARGC_CNT 2
typedef char elemtype1;
typedef double elemtype2;

int exam(elemtype1 c)
{
	if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
		return 1;
	else return 0;
}//判断c是否为运算符

elemtype2 trans(char c) {
	switch (c) {
	case '0': return 0;
	case '1': return 1;
	case '2': return 2;
	case '3': return 3;
	case '4': return 4;
	case '5': return 5;
	case '6': return 6;
	case '7': return 7;
	case '8': return 8;
	case '9': return 9;
	default: return -1;
	}
}//将字符转换成运算数字

int cmp(char s1, char s2) {
	int priority[256] = { 0 };
	priority['+'] = priority['-'] = 1;
	priority['*'] = priority['/'] = 2;
	priority['^'] = 3;
	priority['('] = priority[')'] = 4;
	if (s1 == '^' && s2 == '^') return 1;
	if (priority[s1] > priority[s2]) return 1;
	if (priority[s1] == priority[s2]) return 0;
	if (priority[s1] < priority[s2]) return -1;
	else return -2;
}//判断运算符优先级

elemtype2 operate(elemtype2 a, elemtype2 b, char c)
{
	switch (c)
	{
	case '+':return a + b; break;
	case '-':return a - b; break;
	case '*':return a * b; break;
	case '/':return a / b; break;
	case '^':
	{
		if (b == 0)
			return 1;
		else

		{
			int j = a;
			for (int i = 0; i < b - 1; i++)
				a = a * j;
			return a;
		}
	}
	default: return -1;
	}
}//进行运算

typedef struct
{
	elemtype1* data;
	int top;
	int stacksize;
} sqstack1;//定义符号栈

sqstack1 initstack1()
{
	sqstack1 s;
	s.data = (elemtype1*)malloc(STACK_INIT_SEIZ * sizeof(elemtype1));
	s.top = -1;
	s.stacksize = STACK_INIT_SEIZ;
	return s;
}

int stackempty1(sqstack1* s)
{
	if (s->top == -1)
		return 1;
	else return 0;
}

void push1(sqstack1* s, elemtype1 e)
{
	if (s->top >= s->stacksize)
	{
		s->data = (elemtype1*)malloc((STACK_INIT_SEIZ + STACKINCREMENT) * sizeof(elemtype1));
		s->stacksize += STACKINCREMENT;
	}
	s->top++;
	s->data[s->top] = e;
}

elemtype1 pop1(sqstack1* s)
{
	if (s->top >= 0)
	{
		elemtype1 e = s->data[s->top];
		s->top--;
		return e;
	}
	else return -2;
}

elemtype1 gettop(sqstack1* s)
{
	elemtype1 e = '0';
	if (s->top > -1)
		e = s->data[s->top];
	return e;
}
//符号栈的操作

typedef struct
{
	elemtype2* data;
	int top;
	int stacksize;
} sqstack2;//定义数字栈

sqstack2 initstack2()
{
	sqstack2 s;
	s.data = (elemtype2*)malloc(STACK_INIT_SEIZ * sizeof(elemtype2));
	s.top = -1;
	s.stacksize = STACK_INIT_SEIZ;
	return s;
}

int stackempty2(sqstack2* s)
{
	if (s->top == -1)
		return 1;
	else return 0;
}

void push2(sqstack2* s, elemtype2 e)
{
	if (s->top >= s->stacksize)
	{
		s->data = (elemtype2*)malloc((STACK_INIT_SEIZ + STACKINCREMENT) * sizeof(elemtype2));
		s->stacksize += STACKINCREMENT;
	}
	s->top++;
	s->data[s->top] = e;
}

elemtype2 pop2(sqstack2* s)
{
	elemtype2 e = 0;
	if (s->top >= 0)
	{
		e = s->data[s->top];
		s->top--;
		return e;
	}
	else return -2;
}
//数字栈操作

int main()
{
	char str[1024];
	fgets(str, 1024, stdin);

	sqstack1 opr;
	opr = initstack1();
	sqstack2 num;
	num = initstack2();
	//初始化栈
	elemtype1 theta1 = '0', theta2 = '0', theta3 = '0';
	elemtype2 num1 = 0, num2 = 0;
	char c = '0';
	int left = 0, right = 0, i = 0, pos = 0;
	//定义需要的变量 
	double dec = 1;
	int ii = 0;
	while (c != '\0')
	{
		c = str[ii];
		ii++;
		if ((&opr)->data[(&opr)->top] == '.' && (c > '9' || c < '0'))
			pop1(&opr);
		if (c == '\0') break;
		if ((c > '9' || c < '0') && (theta3 > '9' || theta3 < '0') && c != '(')
		{
			printf("ERROR_02");
			return -1;
		}
		if (c == ')') right++;
		if (c == '(') left++;
		if (right > left)
		{
			printf("ERROR_02");
			return -1;
		}
		if ((c > '9' || c < '0') && exam(c) == 0 && c != '(' && c != ')' && c != '.')
		{
			printf("ERROR_02");
			return -1;
		}
		//错误情况ERROR_02
		if (c == ')')
		{
			while (gettop(&opr) != '(')
			{
				num1 = pop2(&num);
				num2 = pop2(&num);
				theta1 = pop1(&opr);
				if (gettop(&opr) == '-')
				{
					if (theta1 == '-')
						theta1 = '+';
					else if (theta1 == '+')
						theta1 = '-';
				}
				if (gettop(&opr) == '/')
				{
					if (theta1 == '/')
						theta1 = '*';
					else if (theta1 == '*')
						theta1 = '/';
				}
				if (theta1 == '/' && num2 == 0)
				{
					printf("ERROR_03");
					return -1;
				}
				num1 = operate(num2, num1, theta1);
				push2(&num, num1);
			}
			pop1(&opr);
			continue;
		}//处理括号运算
		if (c >= '0' && c <= '9')
		{
			if ((&opr)->data[(&opr)->top] == '.')
			{
				pos = 0;
				dec = dec * 0.1;
				num1 = dec * trans(c);
				(&num)->data[(&num)->top] = (&num)->data[(&num)->top] + num1;
			}


			if (pos != 0)
			{
				(&num)->data[(&num)->top] = (&num)->data[(&num)->top] * 10;
				num1 = trans(c);
				(&num)->data[(&num)->top] = (&num)->data[(&num)->top] + num1;
			}
			if (pos == 0 && (&opr)->data[(&opr)->top] != '.')
			{
				num1 = trans(c);
				push2(&num, num1);
			}
			pos++;
		}
		if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '.' || c == '(')
		{
			push1(&opr, c);
			pos = 0;
		}
		//入栈
		if ((&opr)->top == -1) continue;
		if (exam((&opr)->data[(&opr)->top]) == 1 && exam((&opr)->data[((&opr)->top) - 1]) == 1 && cmp((&opr)->data[((&opr)->top) - 1], (&opr)->data[(&opr)->top]) > 0)
		{
			theta1 = pop1(&opr);
			num1 = pop2(&num);
			num2 = pop2(&num);
			theta2 = pop1(&opr);
			if (gettop(&opr) == '-')
			{
				if (theta2 == '-')
					theta2 = '+';
				else if (theta2 == '+')
					theta2 = '-';
			}
			if (gettop(&opr) == '/')
			{
				if (theta2 == '/')
					theta2 = '*';
				else if (theta2 == '*')
					theta2 = '/';
			}
			if (theta2 == '/' && num1 == 0)
			{
				printf("ERROR_03");
				return -1;
			}
			num1 = operate(num2, num1, theta2);
			push2(&num, num1);
			push1(&opr, theta1);
		}//进行优先级运算
		theta3 = c;
	}
	if (right != left)
	{
		printf("ERROR_02");
		return -1;
	}
	//括号错误判断
	while ((&num)->top != 0)
	{
		num1 = pop2(&num);
		num2 = pop2(&num);
		theta1 = pop1(&opr);
		if (gettop(&opr) == '-')
		{
			if (theta1 == '-')
				theta1 = '+';
			else if (theta1 == '+')
				theta1 = '-';
		}
		if (gettop(&opr) == '/')
		{
			if (theta1 == '/')
				theta1 = '*';
			else if (theta1 == '*')
				theta1 = '/';
		}
		if (theta1 == '/' && num1 == 0)
		{
			printf("ERROR_03");
			return -1;
		}
		num1 = operate(num2, num1, theta1);
		push2(&num, num1);
	}
	//进行最后运算
	num1 = pop2(&num);
	printf("%g", num1);
	//输出
	return 0;
}