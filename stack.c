#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define ALLOC_SIZE   512  // 初始的栈空间

typedef int KEY_TYPE;  // 需要存的数据的数据类型。这里可以更改为自定义的结构体

typedef struct _stack {
	KEY_TYPE *base;  // 初始的栈空间
	int top;         // 栈顶
	int stack_size;  // 当前栈空间大小
} stack;

void init_stack(stack *s) {
	s->base = (KEY_TYPE*)calloc(ALLOC_SIZE, sizeof(KEY_TYPE)); // 分配空间
	assert(s->base);

	s->top = 0;
	s->stack_size = ALLOC_SIZE;
}

void destory_stack(stack *s) { // 销毁栈
	assert(s);

	free(s->base);
	s->base = NULL;
	s->stack_size = 0;
	s->top = 0;
}

void push_stack(stack *s, KEY_TYPE data) {
	assert(s);
	if (s->top >= s->stack_size) { // 空间不足，重新分配空间
		s->base = (KEY_TYPE*)realloc(s->base, (s->stack_size + ALLOC_SIZE) * sizeof(KEY_TYPE));
		assert(s->base);

		s->stack_size += ALLOC_SIZE;
	}
	s->base[s->top] = data; // 插入数据到栈顶
	s->top++;
}

void pop_stack(stack *s, KEY_TYPE *data) { // 取出栈顶元素
	assert(s);
	*data = s->base[--s->top];
}

int emtry_stack(stack *s) {
	return s->top == 0 ? 0 : 1;
}

int size_stack(stack *s) {
	return s->top;
}

int main() {
	stack s;

	init_stack(&s);

	int i = 0;
	for (i = 0; i < 1000; i++) {
		push_stack(&s, i+1);
	}

	while (emtry_stack(&s)) {
		int data;
		
		pop_stack(&s, &data);
		printf("%4d", data);
	}
	printf("\n");

	destory_stack(&s);
}
