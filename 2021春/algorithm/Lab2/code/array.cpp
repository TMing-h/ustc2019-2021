#include "array.h"

void ARRAY_Insert(ARRAY_node data_ARRAY[], ARRAY_node data_node, int ARRAY_length) {
    if(ARRAY_length == 100000){
        cout << "��������������ʧ��" << endl;
        return;
    }
    if(ARRAY_length == 0){ // �����飬data_node����һ��
        data_ARRAY[0] = data_node;
        return;
    }
    // ������в���
    int i = 0;
    for(i = ARRAY_length-1; i >= 0; i--){
        if(data_ARRAY[i].index > data_node.index) // index����data_node��������
            data_ARRAY[i+1] = data_ARRAY[i];
        else if(data_ARRAY[i].index <= data_node.index){ // ����data_node
            data_ARRAY[i+1] = data_node;
            break;
        }
    }
    if(i == -1) // i==-1��ζ����Ԫ�غ��ƣ���data_nodeӦ���ڵ�һ��
        data_ARRAY[0] = data_node;
}

void ARRAY_Query(ARRAY_node data_ARRAY[], int* Query_index, int ARRAY_length) {
    int flag = 0;
    int low,high,mid;
    cout << "���ң�" << endl;
    for(int i = 0; i < 10 ; i++){
        low = 0;
        high = ARRAY_length - 1;
        if(Query_index[i] > 99999 || Query_index[i] < 0){
            cout << "�±����" << endl;
            return;
        }
        // ����¼ʱ�临�Ӷ�Ҫ��ʹ�ö��ֲ���
        while(low <= high){
            mid = (low+high)/2;
            if(data_ARRAY[mid].index == Query_index[i]){
                flag = 1;
                cout << Query_index[i] << "��mac��ַΪ��" << data_ARRAY[mid].mac << endl;
                break;
            }
            else if(data_ARRAY[mid].index > Query_index[i])
                high = mid - 1;
            else
                low = mid + 1;
        }
        /*for(int j = 0; j < ARRAY_length; j++){
            if(data_ARRAY[j].index == Query_index[i]){
                flag = 1;
                cout << Query_index[i] << "��mac��ַΪ��" << data_ARRAY[j].mac << endl;
                break;
            }
        }*/
        if(flag == 0){
            cout << Query_index[i] << "�޼�¼" << endl;
            continue;
        }
        flag = 0;
    }
}

void ARRAY_Delete(ARRAY_node data_ARRAY[], int* Delete_index, int& ARRAY_length) {
    int flag = 0;
    int i;
    int j;
    int low,high,mid;
    cout << "ɾ����" << endl;
    for(i = 0; i < 10 ; i++){
        low = 0;
        high = ARRAY_length - 1;
        if(Delete_index[i] > 99999 || Delete_index[i] < 0){
            cout << "�±����" << endl;
            return;
        }
        // Ҫɾ��������Ҫ����
        while(low <= high){
            mid = (low+high)/2;
            if(data_ARRAY[mid].index == Delete_index[i]){
                flag = 1;
                cout << Delete_index[i] << "��mac��ַΪ��" << data_ARRAY[mid].mac << endl;
                break;
            }
            else if(data_ARRAY[mid].index > Delete_index[i])
                high = mid - 1;
            else
                low = mid + 1;
        }
        /*for(j = 0; j < ARRAY_length; j++){
            if(data_ARRAY[j].index == Delete_index[i]){
                flag = 1;
                cout << Delete_index[i] << "��mac��ַΪ��" << data_ARRAY[j].mac << endl;
                break;
            }
        }*/
        if(flag == 0){
            cout << Delete_index[i] << "�޼�¼" << endl;
            continue;
        }
        flag = 0;
        // ���ɾ�����һ��Ԫ�أ�ֱ�Ӱ����鳤��-1
        if(mid == ARRAY_length-1){
            ARRAY_length = ARRAY_length-1;
            continue;
        }
        // ���������һ��Ԫ�أ��򽫸�Ԫ���Ժ�����ǰ��
        j = mid;
        while(j < ARRAY_length-1){
            data_ARRAY[j] = data_ARRAY[j+1];
            j++;
        }
        ARRAY_length = ARRAY_length-1;
    }
}
