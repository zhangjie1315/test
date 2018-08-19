//从尾到头打印单链表
//可以采用递归的思想  打印1234   123+4   12+3+4  1+2+3+4
//
void LinkListPrintReverse(LinkList* phead)
{
    if(phead = NULL){
        //空链表
        return;
    }
    LinkListPrintReverse(phead->next);
    printf("%c",phead->next);
    return;
}
