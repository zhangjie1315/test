//选择排序  不稳定排序 时间复杂度为O(N^2)
//选择排序为打擂台思想
//bound为擂主，cur=bound+1:挑战者，按照条件挑战成功则交换
//[0,bound)为有序区间，(bound,size]为无序区间
void selectsort(int arr[],size_t size)
{
    if(arr==NULL||size=0)
    {
        return;
    }
    size_t bound = 0;
    for(bound=0;bound<size;bound++)
    {
        size_t cur = bound+1;
        for(cur=bound+1;cur<size;cur++)
        {
            if(array[bound]>array[cur])
            {
                swap(&array[bound],&array[cur]);
            }
        }
    }
}
