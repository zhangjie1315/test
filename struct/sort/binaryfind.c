# include <stdio.h>
int main()
{
    int arr[]={1,2,3,4,5,6,7,8,9};
    int key=4;
    int left=0;
    int right=sizeof(arr)/sizeof(arr[0])-1;
    int mid=0;
    while(left<=right)
    {
        mid=(left+right)>>1;
        if(arr[mid]>key)
        {
            right=mid-1;
        }
      if(arr[mid]<key)
        {
            left=mid+1;
        }
      else break;
    }
    if(left<=right)
        printf("找到了，下标是%d\n",mid);
    else 
        printf("没找到\n");
}
