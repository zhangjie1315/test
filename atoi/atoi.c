#include <stdio.h>
#include<assert.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
//atoi函数功能：用来将字符串类型转换为整型
//该函数会从第一个字符开始跳过前边的空格，直至遇到正负号才开始转换，遇到非数字或者'\0'就会结束转换。
//
//如果不能转换或是空字符串就返回0

//思路：首先检测空格跳过空格，其次检测正负号，将其记录下来返回带符号的结果，然后将单个字符减去'0'(字符0)就能
//转换为数字，然后通过计算得到结果

int my_atoi(const char * str)
{//str指针可以改变，但是指向的内容不能改变
  assert(str);//断言
  int num=0;
  int sign=1;//标志位
  char *p=(char *)str;
  while(*p!='\0')
  {
      if(*p==' ')
      {
          p++;
      }
      else if(*p=='+')
      {
          p++;
          sign=1;
      }
      else if(*p=='-')
      {
          p++;
          sign=-1;
      }
      while(*p>='0'&&*p<='9')
      {
          int n=*p-'0';
          p++;
          num=(num*10+n);
      }

      return sign*num;
  }
  return 0;
}

int main()
{
    char str1[]="abcd";
    char str2[]="1234";
    char str3[]="-1234";
    char str4[]="123abcd";
    printf("%d\n",my_atoi(str1));
    printf("%d\n",my_atoi(str2));
    printf("%d\n",my_atoi(str3));
    printf("%d\n",my_atoi(str4));
}



//int my_atoi(const char* str)
//{
//    assert(str!=NULL);
//    int sum = 0;
//    int sign = 1;
//    char *p = (char*)str;
//    while(*p!=NULL)
//    {
//        if(*p=="")
//        {
//            p++;
//        }
//        if(*p=="+")
//        {
//            sign = 1;
//            p++;
//        }
//        if(*p="-")
//        {
//            sign = "-1";
//            p++;
//        }
//        while(*p>='0'&&*p<='9')
//        {
//            int m = *p-'0';
//            sum = 10*sum + m;
//            p++;
//        }
//        return sign*num;
//    }
//
//}
//int main()
//{
//    char arr1[]="abcd";
//}
//


