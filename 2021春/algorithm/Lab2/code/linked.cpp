#include "linked.h"

LINKED_node* created_LINKED() {
	LINKED_node* HEAD = new LINKED_node;
	HEAD -> next = NULL;
	return HEAD;
}

void LINKED_Insert(LINKED_node* HEAD, LINKED_node* data_node) {
    //LINKED_node* q = HEAD;
    // Ϊ�˱�֤O(1)��ʱ�临�Ӷȣ�����ͷ�巨
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
    cout << "���ң�" << endl;
    for(int i = 0; i < 10; i++){
        q = HEAD;
        while((q!=NULL) && (q->index!=LINKED_Query[i]))
            q = q->next;
        if(q != NULL) // q��Ϊ�գ������ҵ���
            cout << LINKED_Query[i] << "��mac��ַΪ��" << q->mac << endl;
        else // ����û�ҵ�
            cout << LINKED_Query[i] << "�޼�¼" << endl;
    }
}

void LINKED_Delete(LINKED_node* HEAD, int* LINKED_Delete) {
    LINKED_node * q;
    LINKED_node * p;
    cout << "ɾ����" << endl;
    for(int i = 0; i < 10; i++){
        q = HEAD;
        // ��ɾ�����Ȳ���
        while((q->next!= NULL) && (q->next->index!=LINKED_Delete[i]))
            q = q->next;
        if(q->next != NULL){ // �ҵ�
            p = q->next;
            cout << LINKED_Delete[i] << "��mac��ַΪ��" << q->next->mac << endl;
            q->next = p->next;
            delete(p);
        }
        else if((q->next==NULL) && (q->index==LINKED_Delete[i]))
            delete(q);
        else // û�ҵ�
            cout << LINKED_Delete[i] << "�޼�¼" << endl;

    }
}
