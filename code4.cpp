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
		//�ַ���sΪ�ļ��е�·�� C:\Users\86175\Desktop\�ļ���
	len=strlen(s);
	filePath=s;
    vector<string> files;
	getFiles(filePath,files);
	char str[50];
	char name[10][50];//�����ļ�ȫ����·��
	char sname[10][15]; //�����ļ��� 
	int size = files.size();
		//�ļ�����   files[i].c_str()Ϊ�ļ������ļ�·�� 
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
double getfilesize(char* filename)  	//�����ļ����ֽ�����С 
{
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
        return 0;
    fseek(fp,0,SEEK_END);
    return ftell(fp);
}
void outsize(char * filename)		//���ļ��Ĵ�С����Ҫ��ת������ӡ 
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
