#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

struct Stack
{
  char data[MAX];
  int top;
} stack;

void push(char c)
{
  // check stack is full
  if (stack.top == MAX - 1)
    printf("Stack Overflow");

  //add element to the stack
  else
    stack.data[++stack.top] = c;
}
char pop()
{
  // check stack is empty
  if (stack.top == -1)
    printf("Stack Underflow");
  // remove element from the stack
  else
    return stack.data[stack.top--];

  return 0;
}
char peek()
{
  //check stack is empty
  if (stack.top == -1)
    printf("Stack Underflow");
  // extract stack top for display
  else
    return stack.data[stack.top];

  return 0;
}
int is_operator(char c)
{
  // are the operators used valid
  return (c == '+' || c == '-' || c == '*' || c == '/' || c == '^');
}
int is_operand(char c)
{
  // are the operands used valid
  return (c >= 'a' && c <= 'z');
}
int precedence(char c)
{
  // return precedence of the operators
  switch (c)
  {
  case '+':
  case '-':
    return 1;
    break;
  case '*':
  case '/':
    return 2;
    break;
  case '^':
    return 3;
    break;
  }
  return -1;
}
void get_postfix(char string[])
{
  char temp;
  int index = 0;
  char out_string[MAX];

  int len = strlen(string);
  for (int i = 0; i < len; ++i)
  {
    temp = string[i];
    if (temp == '(')
    {
      push(temp);
    }
    else if (is_operand(temp))
    {
      out_string[index++] = temp;
    }
    else if (temp == ')')
    {
      while (peek() != '(')
      {
        out_string[index++] = pop();
      }
      pop();
    }
    else if (is_operator(temp))
    {
      while (stack.top != -1 && precedence(temp) <= precedence(peek()))
      {
        out_string[index++] = pop();
      }
      push(temp);
    }
  }
  while (stack.top != -1)
  {
    out_string[index++] = pop();
  }
  printf("postfix expression: ");

  for (int i = 0; i < index; i++)
  {
    printf("%c", out_string[i]);
  }
}

int main()
{
  // initialize stack top to -1
  stack.top = -1;
  char string[MAX];

  printf("enter infix expression: ");
  scanf("%s", string);
  get_postfix(string);

  return 0;
}
