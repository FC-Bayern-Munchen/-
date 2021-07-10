#include <stdio.h>
double getfilesize(char* filename)  	//计算文件的字节数大小 
{
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
        return 0;
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}
int main()
{
    double size;
    char str[100];
    scanf("%s",str);
    size=getfilesize(str);
    printf("%.0lf",size);
    return 0;
}
