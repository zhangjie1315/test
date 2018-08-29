int partion(int arr[],int beg,int end)
{
    //定义区间
    int left = beg;
    int right = end-1;
    //确定最后一个元素为基准值
    int key = array[right];
    while(left<right){
    //从左向右找第一个大于基准值的元素
    while(left<right&&array[left]<=key)
    {
        left++;
    }
    //从右向左找到第一个小于基准值的元素
    while(left<right&&array[right]>=key)
    {
        right--;
    }
    //交换得到的两个元素
    if(left<right)
    {
        swap(&array[left],&array[right]);
    }
    }
    //交换left指向的元素和基准值
    swap(&array[left],&array[end-1]);
    return left;
}

