#include "linked.h"

LINKED_node* created_LINKED() {
	LINKED_node* HEAD = new LINKED_node;
	HEAD -> next = NULL;
	return HEAD;
}

void LINKED_Insert(LINKED_node* HEAD, LINKED_node* data_node) {
    //LINKED_node* q = HEAD;
    // 为了保证O(1)的时间复杂度，采用头插法
    data_node->next = HEAD->next;
    HEAD->next = data_node;
    /*
    while(q->next != NULL)
        q = q->next;
    q->next = data_node;
    */
}

void LINKED_Query(LINKED_node* HEAD, int* LINKED_Query) {
    LINKED_node* q;
    cout << "查找：" << endl;
    for(int i = 0; i < 10; i++){
        q = HEAD;
        while((q!=NULL) && (q->index!=LINKED_Query[i]))
            q = q->next;
        if(q != NULL) // q不为空，代表找到了
            cout << LINKED_Query[i] << "的mac地址为：" << q->mac << endl;
        else // 否则没找到
            cout << LINKED_Query[i] << "无记录" << endl;
    }
}

void LINKED_Delete(LINKED_node* HEAD, int* LINKED_Delete) {
    LINKED_node * q;
    LINKED_node * p;
    cout << "删除：" << endl;
    for(int i = 0; i < 10; i++){
        q = HEAD;
        // 欲删除，先查找
        while((q->next!= NULL) && (q->next->index!=LINKED_Delete[i]))
            q = q->next;
        if(q->next != NULL){ // 找到
            p = q->next;
            cout << LINKED_Delete[i] << "的mac地址为：" << q->next->mac << endl;
            q->next = p->next;
            delete(p);
        }
        else if((q->next==NULL) && (q->index==LINKED_Delete[i]))
            delete(q);
        else // 没找到
            cout << LINKED_Delete[i] << "无记录" << endl;

    }
}
