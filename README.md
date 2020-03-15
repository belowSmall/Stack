## 栈定义
栈（stack）又名堆栈，它是一种运算受限的线性表。限定仅在表尾进行插入和删除操作的线性表。这一端被称为栈顶，相对地，把另一端称为栈底。向一个栈插入新元素又称作进栈、入栈或压栈，它是把新元素放到栈顶元素的上面，使之成为新的栈顶元素；从一个栈删除元素又称作出栈或退栈，它是把栈顶元素删除掉，使其相邻的元素成为新的栈顶元素。（转自百度百科）

> **这里我的做法是：初始化的时候先分配一段栈空间，当空间不足时，再重新分配空间**
> **top是指向栈顶元素的下一个（比如初始的栈顶top = 0，当插入一个元素后，插入的元素放在 0 处，然后top = 1，1 这个地方是没有实际元素的）**

#### 1.栈的数据结构
```c
#define ALLOC_SIZE   512  // 初始的栈空间
typedef int KEY_TYPE;  // 需要存的数据的数据类型。这里可以更改为自定义的结构体

typedef struct _stack {
	KEY_TYPE *base;  // 初始的栈空间    
	int top;         // 栈顶
	int stack_size;  // 当前栈空间大小
} stack;
```

#### 2.栈的初始化
包括分配空间，栈顶指向0，栈大小为ALLOC_SIZE
```c
void init_stack(stack *s) {
	s->base = (KEY_TYPE*)calloc(ALLOC_SIZE, sizeof(KEY_TYPE)); // 分配空间
	assert(s->base);

	s->top = 0;
	s->stack_size = ALLOC_SIZE;
}
```

#### 3.入栈
先对栈s检查。然后判断栈空间是否满了。如果是满的，先重新分配空间，再插入元素
```c
void push_stack(stack *s, KEY_TYPE data) {
	assert(s);
	if (s->top >= s->stack_size) { // 空间不足，重新分配空间
		s->base = (KEY_TYPE*)realloc(s->base, (s->stack_size + ALLOC_SIZE) * sizeof(KEY_TYPE));
		assert(s->base);

		s->stack_size += ALLOC_SIZE;
	}
	s->base[s->top] = data; // 插入数据到栈顶
	s->top++;  // top指向下一个
}
```

#### 4.出栈
```c
void pop_stack(stack *s, KEY_TYPE *data) { // 取出栈顶元素
	assert(s);
	*data = s->base[--s->top]; // 这里相当于  s->top--;  *data = s->base[s->top];
}
```

* **其实到这里，核心操作就入栈和出栈。但是，要明白一点的是：出栈的时候，只是改变了top的指向，并没有将这个数据空间释放掉，下面介绍如何释放栈空间。**

#### 5.销毁栈
```c
void destory_stack(stack *s) { // 销毁栈
	assert(s);

	free(s->base);
	s->base = NULL;
	s->stack_size = 0;
	s->top = 0;
}
```
* **对比下3、4、5步，就可以发现，刚才说的——出栈并没有释放数据空间**
---
2020.1.5  22:23  广州
