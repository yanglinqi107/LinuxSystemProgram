#include <stdio.h>
#include <stdlib.h>

//预定义数据结构
typedef struct stuInfo
{
	char stuName[10];	//学生姓名
	int Age;	//年龄
}ElemType;

typedef struct node
{
	ElemType data;
	struct node *next;
}ListNode, *ListPtr;

ListNode* CreateList()
{
	static ListNode *head;
	head = (ListNode*)malloc(sizeof(ListNode));
	return head;
}

void PrintList(ListNode *head)
{
	if(head == NULL)
	{
		printf("error! please create list first\n");
		return;
	}
	ListNode *tail = head->next;
	printf("姓名\t年龄\n");
	while(tail != NULL)
	{
		printf("%s\t%d\n", tail->data.stuName, tail->data.Age);
		tail = tail->next;
	}
}

void InsertList(ListNode* head)
{
	if(head == NULL)
	{
		printf("error! please create list first\n");
		return;
	}
	ListNode *tail = head;
	while(tail->next != NULL) tail = tail->next;
	tail->next = (ListNode*)malloc(sizeof(ListNode));
	printf("input name: ");
	scanf("%s", tail->next->data.stuName);
	printf("input age: ");
	scanf("%d", &(tail->next->data.Age));
}

void deleteList(ListNode* head)
{
	while(head != NULL)
	{
		ListNode* tmp = head;
		head = head->next;
		free(tmp);
	}
}

int main(int argc, char *argv[])
{
	ListNode *ListHead = NULL;
	while(1)
	{
		printf("1 Create List\n");
		printf("2 Printf List\n");
		printf("3 Insert List\n");
		printf("4 Quit\n");
		char command = getchar();
		switch(command)
		{
			case '1': 
			{
				ListHead = CreateList();
				break;
			}
			case '2':
			{
				PrintList(ListHead);
				break;
			}
			case '3':
			{
				InsertList(ListHead);
				break;
			}
			case '4':
			{
				deleteList(ListHead);
				return 0;
			}
			default:
			{
				printf("input error\n");
			}
		}
		while(getchar() != '\n'); // 清楚键盘缓冲区
	}
	return 0;
}