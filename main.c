#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct deque deque;
typedef struct dqitem dqitem;
typedef struct dqitem
{
	int value;
	dqitem* prev;
	dqitem* next;
} dqitem;

typedef struct deque
{
	dqitem* front;
	dqitem* end;
} deque;

void print(deque* dequeue, bool backwards)
{
	dqitem* anchor;
	if (backwards)
		anchor = dequeue -> end;
	else
		anchor = dequeue -> front;

	if (anchor == NULL)
	{
		printf("Lista pusta\n");
		return;
	}

	while (anchor != NULL)
	{
		printf("%i ", anchor -> value);
		if (backwards)
			anchor = anchor -> prev;
		else
			anchor = anchor -> next;
	}
	printf("\n");
}

void push(deque* dequeue, int value)
{
	dqitem* newItem = (dqitem*)malloc(sizeof(dqitem));
	newItem -> value = value;
	newItem -> prev = NULL;
	newItem -> next = dequeue -> front;
	if (dequeue -> front != NULL)
		dequeue -> front -> prev = newItem;
	dequeue -> front = newItem;
	if (dequeue -> end == NULL)
		dequeue -> end = newItem;
}

int pop(deque* dequeue)
{
	if (dequeue -> end == NULL)
	{
		printf("Kolejka pusta - brak zdjecia wartosci (kod -1)\n");
		return -1;
	}

	dqitem* addresToFree = dequeue -> end;
	dequeue -> end = dequeue -> end -> prev;
	if (dequeue -> end != NULL)
		dequeue -> end -> next = NULL;
	if (dequeue -> front == addresToFree)
		dequeue -> front = NULL;
	int toReturn = addresToFree -> value;
	free(addresToFree);
	return toReturn;
}

dqitem* getItemAt(deque* dequeue, int position)
{
	int iter = 0;
	dqitem* cur = dequeue -> front;
	while (iter != position)
	{
		if (cur == NULL)
			return NULL; //obsluga dalej
		cur = cur -> next;
		iter++;
	}

	return cur;
}

int getItemsCount(deque* dequeue)
{
	int count = 0;
	dqitem* cur = dequeue -> front;
	while (cur != NULL)
	{
		cur = cur -> next;
		count++;
	}

	return count;
}

void removeQ(deque* dequeue, int position)
{
	dqitem* item = getItemAt(dequeue, position);
	if (item == NULL)
	{
		printf("Kolejka ma za malo elementow\n");
		return;
	}

	if (item -> next != NULL)
		item -> next -> prev = item -> prev;
	if (item -> prev != NULL)
		item -> prev -> next = item -> next;

	if (dequeue -> front == item)
		dequeue -> front = item -> next;
	if (dequeue -> end == item)
		dequeue -> end = item -> prev;

	free(item);
}

void insert(deque* dequeue, int value, int position)
{
	if (dequeue -> front == NULL && position == 0)
	{
		push(dequeue, value);
		return;
	}

	dqitem* item = getItemAt(dequeue, position);
	if (item == NULL)
	{
		if (position == getItemsCount(dequeue))
		{
			dqitem* newItem = (dqitem*)malloc(sizeof(dqitem));
			newItem -> value = value;
			newItem -> next = NULL;
			newItem -> prev = dequeue -> end;
			dequeue -> end -> next = newItem;
			dequeue -> end = newItem;
			return;
		}
		printf("Kolejka ma za malo elementow\n");
		return;
	}

	dqitem* newItem = (dqitem*)malloc(sizeof(dqitem));
	newItem -> value = value;
	newItem -> next = item;
	newItem -> prev = item -> prev;
	if (item -> prev != NULL)
		item -> prev -> next = newItem;
	item -> prev = newItem;

	if (dequeue -> front == item)
		dequeue -> front = newItem;
	if (dequeue -> end == item)
		dequeue -> end = newItem;
}

void handleWrongInput()
{
	printf("Bledna wartosc\n");
	int n;
	while ((n = getchar()) != EOF && n != '\n');
}

void handlePrint(deque *dequeue)
{
	printf("0 - normalnie, 1 - od konca\n");
	int choice;
	if (scanf_s("%i", &choice) != 1)
	{
		handleWrongInput();
		return;
	}
	print(dequeue, choice);
}

void handlePush(deque* dequeue)
{
	printf("Podaj wartosc\n");
	int value;
	if (scanf_s("%i", &value) != 1)
	{
		handleWrongInput();
		return;
	}
	push(dequeue, value);
}

void handlePop(deque* dequeue)
{
	int value = pop(dequeue);
	printf("Zdjeto wartosc %i\n", value);
}

void handleInsert(deque* dequeue)
{
	printf("Podaj wartosc\n");
	int value;
	if (scanf_s("%i", &value) != 1)
	{
		handleWrongInput();
		return;
	}
	printf("Podaj indeks\n");
	int index;
	if (scanf_s("%i", &index) != 1)
	{
		handleWrongInput();
		return;
	}
	insert(dequeue, value, index);
}

void handleRemove(deque* dequeue)
{
	printf("Podaj indeks\n");
	int index;
	if (scanf_s("%i", &index) != 1)
	{
		handleWrongInput();
		return;
	}
	removeQ(dequeue, index);
}

int main(int argc, char **argv)
{	
	deque dequeue;
	dequeue.front = NULL;
	dequeue.end = NULL;

	while (true)
	{
		printf("1 - print\n");
		printf("2 - push\n");
		printf("3 - pop\n");
		printf("4 - insert\n");
		printf("5 - remove\n");
		printf("0 - end\n");
		int choice;
		if (scanf_s("%i", &choice) != 1)
		{
			handleWrongInput();
			continue;
		}
		switch (choice)
		{
		case 1:
			handlePrint(&dequeue);
			break;
		case 2:
			handlePush(&dequeue);
			break;
		case 3:
			handlePop(&dequeue);
			break;
		case 4:
			handleInsert(&dequeue);
			break;
		case 5:
			handleRemove(&dequeue);
			break;
		case 0:
			return 0;
		}
	}
		
	dqitem* item = dequeue.front;
	while (item != NULL)
		free(item);

	return 0;
}
