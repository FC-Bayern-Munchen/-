#include<io.h>
#include<direct.h>
using namespace std;
double getfilesize(char* filename);
void getFiles( string, vector<string>& );
void outsize(char * filename);
int main()
{
	int len;
	char * filePath;
	char s[30];
	cin>>s;	
		//字符串s为文件夹的路径 C:\Users\86175\Desktop\文件夹
	len=strlen(s);
	filePath=s;
    vector<string> files;
	getFiles(filePath,files);
	char str[50];
	char name[10][50];//储存文件全名含路径
	char sname[10][15]; //储存文件名 
	int size = files.size();
		//文件个数   files[i].c_str()为文件夹内文件路径 
	for(int i=0;i<size;i++){
		strcpy(name[i],files[i].c_str());
		int k=0;
		for(int j=len+1;name[i][j]!='\0';j++)
			sname[i][k++]=name[i][j];
		sname[i][k]='\0';
		cout<<sname[i]<<' '<<getfilesize(name[i])<<' ';
		outsize(name[i]);
		cout<<endl;
	}
	
}
void getFiles( string path, vector<string>& files )
{
   long  hFile=0;
    struct _finddata_t fileinfo;
    string p;
   if((hFile =  _findfirst(p.assign(path).append("\\*").c_str(),&fileinfo)) !=  -1)
   {
       do
       {
           if ((fileinfo.attrib &  _A_SUBDIR))
          {
               if(strcmp(fileinfo.name,".") != 0  &&  strcmp(fileinfo.name,"..") != 0)
                   getFiles( p.assign(path).append("\\").append(fileinfo.name), files );
           }
           else
               files.push_back(p.assign(path).append("\\").append(fileinfo.name) );
       }while(_findnext(hFile, &fileinfo) == 0);
       _findclose(hFile);
    }
}
double getfilesize(char* filename)  	//计算文件的字节数大小 
{
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
        return 0;
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}
void outsize(char * filename)		//将文件的大小按照要求转换并打印 
{
	double len;
	len=getfilesize(filename);
	//printf("%.0lf",len);
	if(len<1024) printf("%.0lf",len);
	if(len>=1024&&len<1024*1024){
		if(len/1024<10)
		printf("%.1lf",len/1024);
		else printf("%.0lf",len/1024);
		printf("K");
	}
	if(len>=1024*1024&&len<1024*1024*1024){
		if(len/1024/1024<10)
		printf("%.1lf",len/1024/1024);
		else printf("%.0lf",len/1024/1024);
		printf("M");
	}
	if(len>=1024*1024*1024){
		printf("%.1lf",len/1024/1024/1024);
		printf("G");
	}
}
