#include "array.h"

void ARRAY_Insert(ARRAY_node data_ARRAY[], ARRAY_node data_node, int ARRAY_length) {
    if(ARRAY_length == 100000){
        cout << "数组已满，插入失败" << endl;
        return;
    }
    if(ARRAY_length == 0){ // 空数组，data_node作第一项
        data_ARRAY[0] = data_node;
        return;
    }
    // 否则进行插入
    int i = 0;
    for(i = ARRAY_length-1; i >= 0; i--){
        if(data_ARRAY[i].index > data_node.index) // index大于data_node的往后移
            data_ARRAY[i+1] = data_ARRAY[i];
        else if(data_ARRAY[i].index <= data_node.index){ // 插入data_node
            data_ARRAY[i+1] = data_node;
            break;
        }
    }
    if(i == -1) // i==-1意味着首元素后移，则data_node应插在第一项
        data_ARRAY[0] = data_node;
}

void ARRAY_Query(ARRAY_node data_ARRAY[], int* Query_index, int ARRAY_length) {
    int flag = 0;
    int low,high,mid;
    cout << "查找：" << endl;
    for(int i = 0; i < 10 ; i++){
        low = 0;
        high = ARRAY_length - 1;
        if(Query_index[i] > 99999 || Query_index[i] < 0){
            cout << "下标错误" << endl;
            return;
        }
        // 按附录时间复杂度要求，使用二分查找
        while(low <= high){
            mid = (low+high)/2;
            if(data_ARRAY[mid].index == Query_index[i]){
                flag = 1;
                cout << Query_index[i] << "的mac地址为：" << data_ARRAY[mid].mac << endl;
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
                cout << Query_index[i] << "的mac地址为：" << data_ARRAY[j].mac << endl;
                break;
            }
        }*/
        if(flag == 0){
            cout << Query_index[i] << "无记录" << endl;
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
    cout << "删除：" << endl;
    for(i = 0; i < 10 ; i++){
        low = 0;
        high = ARRAY_length - 1;
        if(Delete_index[i] > 99999 || Delete_index[i] < 0){
            cout << "下标错误" << endl;
            return;
        }
        // 要删除，首先要查找
        while(low <= high){
            mid = (low+high)/2;
            if(data_ARRAY[mid].index == Delete_index[i]){
                flag = 1;
                cout << Delete_index[i] << "的mac地址为：" << data_ARRAY[mid].mac << endl;
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
                cout << Delete_index[i] << "的mac地址为：" << data_ARRAY[j].mac << endl;
                break;
            }
        }*/
        if(flag == 0){
            cout << Delete_index[i] << "无记录" << endl;
            continue;
        }
        flag = 0;
        // 如果删除最后一个元素，直接把数组长度-1
        if(mid == ARRAY_length-1){
            ARRAY_length = ARRAY_length-1;
            continue;
        }
        // 若不是最后一个元素，则将该元素以后整体前移
        j = mid;
        while(j < ARRAY_length-1){
            data_ARRAY[j] = data_ARRAY[j+1];
            j++;
        }
        ARRAY_length = ARRAY_length-1;
    }
}
