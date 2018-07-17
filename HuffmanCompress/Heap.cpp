/*************************************************************************
	> File Name: Heap.cpp
	> Author: Timmy
	> Created Time: 2018年03月04日 星期日 12时27分41秒
 ************************************************************************/

//堆是一种数组对象，被视为完全二叉树结构
//最大堆：父节点大于等于孩子节点
//最小堆：父节点小于等于孩子节点
#include <iostream>
#include <vector>

using namespace std;
#include "Heap.h"

int main(){
	system("clear");
	TestHeap();
	return 0;
}
