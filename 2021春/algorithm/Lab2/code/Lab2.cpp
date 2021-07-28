// Lab2.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <windows.h>
#include "ultity.h"
#include "array.h"
#include "linked.h"
#include "RBTree.h"

using namespace std;

void arr_test(){
    vector<struct CSVDATA> dataList = dataload();
	// Get the data from CSV File
	std::cout << "There are " << dataList.size() << " datas in the CSV file." << std::endl;
    ARRAY_node* data_ARRAY = new ARRAY_node[10];
	int ARRAY_length = 0;
	// ����
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 10; i++) {
		ARRAY_node new_data;
		new_data.mac = dataList[i].mac;
		new_data.index = dataList[i].index;
		ARRAY_Insert(data_ARRAY, new_data, ARRAY_length);
		ARRAY_length++;
	}
	QueryPerformanceCounter(&t2);
	for (int i = 0; i < ARRAY_length; i++)
        cout << data_ARRAY[i].index << "��" << data_ARRAY[i].mac << " ";
    cout << endl;
	double ARRAY_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_insert_time = " << ARRAY_insert_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ���� =======
	int* Query_index = new int[4]{ 19399, 77667, 1, 2};
	QueryPerformanceCounter(&t1);
	ARRAY_Query(data_ARRAY, Query_index, ARRAY_length);
	QueryPerformanceCounter(&t2);
	double ARRAY_query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_query_time = " << ARRAY_query_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ɾ�� =======
	int* Delete_index = new int[3]{ 19399, 34808, 1};
	QueryPerformanceCounter(&t1);
	ARRAY_Delete(data_ARRAY, Delete_index, ARRAY_length);
	QueryPerformanceCounter(&t2);
	for (int i = 0; i < ARRAY_length; i++)
        cout << data_ARRAY[i].index << "��" << data_ARRAY[i].mac << " ";
    cout << endl;
	double ARRAY_delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_delete_time = " << ARRAY_delete_time << " s" << endl;  //���ʱ�䣨��λ����

}

void link_test(){
    vector<struct CSVDATA> dataList = dataload();
	// Get the data from CSV File
	std::cout << "There are " << dataList.size() << " datas in the CSV file." << std::endl;

    LINKED_node* HEAD = created_LINKED();
    LINKED_node* p = NULL;
    // ����
    LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 10; i++) {
		LINKED_node* new_data = new LINKED_node;
		new_data->mac = dataList[i].mac;
		new_data->index = dataList[i].index;
		new_data->next = NULL;
		LINKED_Insert(HEAD, new_data);
	}
	QueryPerformanceCounter(&t2);
	double LINKED_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	p = HEAD;
	while(p->next!=NULL){
        cout << p->next->index << "��" << p->next->mac << " ";
        p = p->next;
	}
    cout << endl;
	cout << "LINKED_insert_time = " << LINKED_insert_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ���� =======
	int* Query_index = new int[3]{ 19399, 77667, 1};
	QueryPerformanceCounter(&t1);
	LINKED_Query(HEAD, Query_index);
	QueryPerformanceCounter(&t2);
	double LINKED_query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_query_time = " << LINKED_query_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ɾ�� =======
	int* Delete_index = new int[3]{ 19399, 34808, 1};
	QueryPerformanceCounter(&t1);
	LINKED_Delete(HEAD, Delete_index);
	QueryPerformanceCounter(&t2);
	double LINKED_Delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	p = HEAD;
	while(p->next!=NULL){
        cout << p->next->index << "��" << p->next->mac << " ";
        p = p->next;
	}
    cout << endl;
	cout << "LINKED_Delete_time = " << LINKED_Delete_time << " s" << endl;  //���ʱ�䣨��λ����;
}

void acceptance_test()//ʵ�����պ������������޸ģ���Ҫ�Ķ���������ϸ�Ķ����룬���IO�ӿ�
{
	vector<struct CSVDATA> dataList = dataload();
	// Get the data from CSV File
	std::cout << "There are " << dataList.size() << " datas in the CSV file." << std::endl;

	/* ���鲿�� ����ʼ��*/
	// ��������
	ARRAY_node* data_ARRAY = new ARRAY_node[100000];
	int ARRAY_length = 0;
	for (int i = 0; i < 99900; i++) {
		ARRAY_node new_data;
		new_data.mac = dataList[i].mac;
		new_data.index = dataList[i].index;
		ARRAY_Insert(data_ARRAY, new_data, ARRAY_length);
		ARRAY_length++;
	}

	// ======= ���� =======
	LARGE_INTEGER t1, t2, tc;
	QueryPerformanceFrequency(&tc);
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 100; i++) {
		ARRAY_node new_data;
		new_data.mac = dataList[i + 99900].mac;
		new_data.index = dataList[i + 99900].index;
		ARRAY_Insert(data_ARRAY, new_data, ARRAY_length);
		ARRAY_length++;
	}
	QueryPerformanceCounter(&t2);
	double ARRAY_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_insert_time = " << ARRAY_insert_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ���� =======
	int* Query_index = new int[10]{ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 99999 };
	QueryPerformanceCounter(&t1);
	ARRAY_Query(data_ARRAY, Query_index, ARRAY_length);
	QueryPerformanceCounter(&t2);
	double ARRAY_query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_query_time = " << ARRAY_query_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ɾ�� =======
	int* Delete_index = new int[10]{ 15000, 25000, 35000, 45000, 55000, 65000, 75000, 85000, 95000, 99999 };
	QueryPerformanceCounter(&t1);
	ARRAY_Delete(data_ARRAY, Delete_index, ARRAY_length);
	QueryPerformanceCounter(&t2);
	double ARRAY_delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "ARRAY_delete_time = " << ARRAY_delete_time << " s" << endl;  //���ʱ�䣨��λ����

	/* ���鲿�֣������� */
	cout << endl;


	/* ������ ����ʼ��*/
	//��������ͷ
	LINKED_node* HEAD = created_LINKED();

	for (int i = 0; i < 99900; i++) {
		LINKED_node* new_data = new LINKED_node;
		new_data->mac = dataList[i].mac;
		new_data->index = dataList[i].index;
		new_data->next = NULL;
		LINKED_Insert(HEAD, new_data);
	}

	// ======= ���� =======
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 100; i++) {
		LINKED_node* new_data = new LINKED_node;
		new_data->mac = dataList[i + 99900].mac;
		new_data->index = dataList[i + 99900].index;
		new_data->next = NULL;
		LINKED_Insert(HEAD, new_data);
	}
	QueryPerformanceCounter(&t2);
	double LINKED_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_insert_time = " << LINKED_insert_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ���� =======
	QueryPerformanceCounter(&t1);
	LINKED_Query(HEAD, Query_index);
	QueryPerformanceCounter(&t2);
	double LINKED_query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_query_time = " << LINKED_query_time << " s" << endl;  //���ʱ�䣨��λ����

	// ======= ɾ�� =======
	QueryPerformanceCounter(&t1);
	LINKED_Delete(HEAD, Delete_index);
	QueryPerformanceCounter(&t2);
	double LINKED_Delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "LINKED_Delete_time = " << LINKED_Delete_time << " s" << endl;  //���ʱ�䣨��λ����;

	/* ������ ��������*/
	cout << endl;


	/*��������֣���ʼ��*/
	//���ɺ����
	RBTree* tree = new RBTree();
	for (int i = 0; i < 99900; i++)
		tree->insert(dataList[i].index, dataList[i].mac);

	// ======= ���� =======
	QueryPerformanceCounter(&t1);
	for (int i = 99900; i < 100000; i++)
		tree->insert(dataList[i].index, dataList[i].mac);
	QueryPerformanceCounter(&t2);
	double RBTREE_insert_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "RBTREE_insert_time = " << RBTREE_insert_time << " s" << endl;  //���ʱ�䣨��λ����;

	// ======= ���� =======
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 10; i++)
		cout << Query_index[i] << " : " << tree->search(Query_index[i])->mac << endl;
	QueryPerformanceCounter(&t2);
	double RBTREE_Query_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "RBTREE_Query_time = " << RBTREE_Query_time << " s" << endl;  //���ʱ�䣨��λ����;

	// ======= ɾ�� =======
	QueryPerformanceCounter(&t1);
	for (int i = 0; i < 10; i++)
		tree->remove(Delete_index[i]);
	QueryPerformanceCounter(&t2);
	double RBTREE_Delete_time = (double)(t2.QuadPart - t1.QuadPart) / (double)tc.QuadPart;
	cout << "RBTREE_Delete_time = " << RBTREE_Delete_time << " s" << endl;  //���ʱ�䣨��λ����;

	/*��������֣�������*/
	cout << endl;
}

void RBTree_test()//��������Ժ�������ͬѧ�ڲ�ȫ���������ʱ������ȷ�ԣ�����ʱҲ���ô˺����Ժ����������ȷ�Խ��в���
{
	/*���������ʾ��---��������д�ĺ����������ȷ��--�����б���������޸���Ϸ������ǰ�뻹ԭ����ʾ����*/
	RBTree* test = new RBTree();
	cout << "RBTree test" << endl;
	test->insert(8, "I");
	test->print();
	test->insert(2, "L");
	test->print();
	test->insert(5, "O");
	test->print();
	test->insert(9, "V");
	test->print();
	test->insert(1, "E");
	test->print();
	test->insert(7, "U");
	test->print();
	test->insert(6, "S");
	test->print();
	test->insert(10, "T");
	test->print();
	test->insert(4, "C");
	test->print();
	test->remove(2);
	test->print();
	/*��������Խ���*/
	cout << endl;
}
void RBTree_test_my()//��������Ժ�������ͬѧ�ڲ�ȫ���������ʱ������ȷ�ԣ�����ʱҲ���ô˺����Ժ����������ȷ�Խ��в���
{
	/*���������ʾ��---��������д�ĺ����������ȷ��--�����б���������޸���Ϸ������ǰ�뻹ԭ����ʾ����*/
	RBTree* test = new RBTree();
	cout << "RBTree test" << endl;
	test->insert(34808, "I"); // fixup��������
	test->print();
	test->insert(47209, "L");
	test->print();
	test->insert(77667, "O");
	test->print();
	/*test->insert(9, "V");
	test->print();
	test->insert(1, "E");
	test->print();
	test->insert(7, "U");
	test->print();
	test->insert(6, "S");
	test->print();
	test->insert(10, "T");
	test->print();
	test->insert(4, "C");
	test->print();
	test->remove(2);
	test->print();*/
	/*��������Խ���*/
	cout << endl;
}

int main()
{
	//acceptance_test();//ʵ������
	RBTree_test();//���������
	//arr_test(); //�����������
    //link_test(); //�������
	return 0;
}
