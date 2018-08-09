
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include </usr/include/mysql/mysql.h>

void select_data()
{
    printf("<html>");
    printf("<meta charset=utf-8>");
    MYSQL *mysql_fd = mysql_init(NULL);//获取mysql文件描述符

    if(mysql_real_connect(mysql_fd, 
                          "127.0.0.1", "root", "4321", "http", 
                          3306, NULL, 0) == NULL)
    {
        printf("<h2>数据库连接失败 !</h2>\n");
        return;
    }
    printf("<h2>连接数据库成功 !</h2>\n");
    mysql_set_character_set(mysql_fd, "utf8");
    const char* charset = mysql_character_set_name(mysql_fd);
    printf("<字符集: %s><br>", charset);

    char sql[1024];

    sprintf(sql, "SELECT * FROM user");
    mysql_query(mysql_fd, sql);
     //读取结果
    MYSQL_RES *res = mysql_store_result(mysql_fd);
	//获取当前的表对应的行
    int row = mysql_num_rows(res);
	//获取当前表对应的列
    int col = mysql_num_fields(res);
	//获取当前表对应的列名
    MYSQL_FIELD *field = mysql_fetch_fields(res);
    int i = 0;
    printf("<table border=\"1\">");
    for(; i < col; i++)
    {
        printf("<td>%s</td>", field[i].name);
    }
    printf("\n");

    for(i=0; i < row; i++)
    {
        MYSQL_ROW rowData = mysql_fetch_row(res);
        int j = 0;
        printf("<tr>");
        for(; j < col; j++)
        {
            printf("<td>%s</td>", rowData[j]);
        }
        printf("</tr>");
    }
    printf("</table>");
    printf("</html>");

    mysql_close(mysql_fd);
}

int main()
{
    char data[1024];
    if(getenv("METHOD"))
    {
        if(strcasecmp("GET", getenv("METHOD")) == 0)
        {
            strcpy(data, getenv("QUERY_STRING"));
        } 
        else
        {
            int content_length = atoi(getenv("CONTENT_LENGTH"));
            int i = 0;
            for(; i < content_length; i++)
            {
                read(0, data+i, 1);
            }
            data[i] = 0;
        }
    }
    select_data();
    return 0;
}
