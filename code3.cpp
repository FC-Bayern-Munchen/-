#include<bits/stdc++.h>
#include<stdlib.h>
#include<io.h>
#include<direct.h>
using namespace std;

void getFiles( string, vector<string>& );
int getfilesize(char* filename);
void copy1(char * s1,char *s2,int n);
void hefiles();
void fenfiles();
void copyfile(int x,char *filename);

struct file{	 
	char s1[50];//��·�����ļ���
	char s2[10];//����·�����ļ��� 
	int namesize;//�ļ����ĳ��� 
	int fsize;//�ļ����ݵ��ֽ��� 
}f[30];

struct data{
	char s[50];	//����ļ������ļ���·�� 
	int a;		//��ȡ���ļ������� 
	int b;		//��ȡ���ļ����ֽ��� 
}d[30];

int size,x;
int len;
long long sum=0;
char * filePath1="C:\\Users\\86175\\Desktop\\�ļ���\\folder";
//Ҫ����ļ����ڵ��ļ��� 
char * filePath2="C:\\Users\\86175\\Desktop\\�ļ���\\newfolder\\";
//��ѹ���ļ����ڵ�·�� 

int main()
{
    vector<string> files;
	getFiles(filePath1,files);
	char str[50];
	size = files.size();	//�ļ������ļ��ĸ��� 
	len=strlen(filePath1);//Ҫ�ϲ����ļ��е�·������ 
	for(int i=0;i<size;i++){
		strcpy(f[i].s1,files[i].c_str());
		copy1(f[i].s2,f[i].s1,len+1);
		f[i].namesize=strlen(f[i].s2);
		f[i].fsize=getfilesize(f[i].s1);
	}	//���ļ������ݴ���ṹ������ 
	hefiles();	//�ϲ��ļ� 
	fenfiles();	//����ļ� 
}

void getFiles( string path, vector<string>& files )	//��ȡ�ļ����������ļ��� 
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

int getfilesize(char* filename)  	//�����ļ����ֽ�����С 
{
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
        return 0;
    fseek(fp,0,SEEK_END);
    return ftell(fp);
    fclose(fp);
}

void copy1(char * s1,char *s2,int n)	//���ַ���s2��n���ַ�����ַ����ݸ��Ƹ��ַ���s1 
{
	int i=0,j=n;
	while(s2[j]!=0){
		s1[i++]=s2[j++];
	}
	s1[i]='\0';
}

void hefiles()	//���ļ����Ϊһ���������ļ� 
{
	FILE *fp1;
	int i;
	char c;
	fp1=fopen("C:\\Users\\86175\\Desktop\\�ļ���\\newfile.bin","wb");
	if(fp1==NULL){
		printf("error1");
		exit(0);
	}
	fwrite((char *)&size,4,1,fp1);	//��int��д��������ļ��� 
	for(i=0;i<size;i++){
		fwrite((char *)&f[i].namesize,4,1,fp1);
		fwrite((char *)&f[i].fsize,4,1,fp1);
	}
	fclose(fp1);
	for(i=0;i<size;i++){	//��ab�ķ�ʽ���ļ��е����ݸ��Ƶ��������ļ���β 
		copyfile(i,f[i].s1);
	}
	cout<<"�ļ�����ɹ�"<<endl;
//	cout<<"�ϳ��ļ�·��Ϊ:"<<"C:\\Users\\86175\\Desktop\\�ļ���\\newfile.bin"<<endl;
}

void fenfiles()		//�������ƽṹ�ļ���ԭΪԭ�ļ� 
{
	
	FILE *fp1=fopen("C:\\Users\\86175\\Desktop\\�ļ���\\newfile.bin","r");
	FILE *fp2;
	if (!fp1)
	{
		puts("�ļ���ʧ�ܣ�");
		exit(0);
	}
	fread((char *)&x,4,1,fp1);
	sum+=4;		//sumΪ��¼ָ���ƶ� 
	for(int i=0;i<x;i++){
		fread((char *)&d[i].a,4,1,fp1);
		fread((char *)&d[i].b,4,1,fp1);
		sum+=8;
	}
	for(int i=0;i<x;i++){
		char str[10];
		char ch;
		fseek(fp1,sum,0);
		for(int j=0;j<d[i].a;j++){
			fread(&ch,1,1,fp1);
			str[j]=ch;
		}	//str�����ļ��� 
		str[d[i].a]='\0';
		sum+=d[i].a;
		strcpy(d[i].s,filePath2);
		strcat(d[i].s,str);	//���ļ�·�����ļ���	
		fp2=fopen(d[i].s,"wb");
		for(int j=0;j<d[i].b;j++){
			fread(&ch,1,1,fp1);
			fwrite(&ch,1,1,fp2);
			sum++;
		}
		fclose(fp2);
	}
	cout<<"�ļ���ԭ�ɹ�"<<endl; 
//	cout<<"��ԭ�ļ������ļ���Ϊ:"<<"C:\\Users\\86175\\Desktop\\�ļ���\\newfolder"<<endl;
}

void copyfile(int x,char *filename)		//��һ���ļ��е����ݸ��Ƶ������ƽṹ�ļ��� 
{
	FILE* fp1 = fopen(filename, "rb");
	FILE* fp2 = fopen("C:\\Users\\86175\\Desktop\\�ļ���\\newfile.bin","ab");
	if (!fp1)
	{
		puts("�ļ���ʧ�ܣ�");
		exit(0);
	}
	if (!fp2)
	{
		puts("�ļ���ʧ�ܣ�");
		exit(0);
	}
	fputs(f[x].s2,fp2);
	char ch;
	while(fread(&ch,1,1,fp1)){
		fwrite(&ch,1,1,fp2);
	}
	fclose(fp1);
	fclose(fp2);
}
