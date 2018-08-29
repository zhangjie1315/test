//插入排序 稳定排序 时间复杂度为O(N^2)
//思路：不再是数据的交换而是数据的搬运
//bound=1 定义边界[0,bound)为已排区间，[bound，size)是未排区间
//保存bound指向的元素
//从后往前找到合适的位置进行插入(从后向前比array[i]大的值都进行搬运)
void insertsort(int array[],size_t size)
{
    if(size<=1)
    {
        return;
    }
    size_t bound = 1;
    for(bound;bound<size;bound++)
    {
        int value = array[bound];
        size_t i = bound;
        for(i=bound;i>0;i--)
        {
           if(array[i-1]>array[i])
           {
               array[i]=array[i-1];
           }
           else 
           {
               break;
           }
        }//无论上边通过i=0退出循环或者已经找到位置，下边的填坑都成立
        array[i]=value;//进行填坑
    }
}
