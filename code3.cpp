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
	char s1[50];//含路径的文件名
	char s2[10];//不含路径的文件名 
	int namesize;//文件名的长度 
	int fsize;//文件内容的字节数 
}f[30];

struct data{
	char s[50];	//解包文件夹中文件的路径 
	int a;		//读取的文件名长度 
	int b;		//读取的文件的字节数 
}d[30];

int size,x;
int len;
long long sum=0;
char * filePath1="C:\\Users\\86175\\Desktop\\文件夹\\folder";
//要打包文件所在的文件夹 
char * filePath2="C:\\Users\\86175\\Desktop\\文件夹\\newfolder\\";
//解压后文件所在的路径 

int main()
{
    vector<string> files;
	getFiles(filePath1,files);
	char str[50];
	size = files.size();	//文件夹中文件的个数 
	len=strlen(filePath1);//要合并的文件夹的路径长度 
	for(int i=0;i<size;i++){
		strcpy(f[i].s1,files[i].c_str());
		copy1(f[i].s2,f[i].s1,len+1);
		f[i].namesize=strlen(f[i].s2);
		f[i].fsize=getfilesize(f[i].s1);
	}	//将文件的数据存入结构体数组 
	hefiles();	//合并文件 
	fenfiles();	//解包文件 
}

void getFiles( string path, vector<string>& files )	//获取文件夹中所有文件名 
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

int getfilesize(char* filename)  	//计算文件的字节数大小 
{
    FILE *fp;
    if((fp=fopen(filename,"r"))==NULL)
        return 0;
    fseek(fp,0,SEEK_END);
    return ftell(fp);
    fclose(fp);
}

void copy1(char * s1,char *s2,int n)	//将字符串s2第n个字符后的字符内容复制给字符串s1 
{
	int i=0,j=n;
	while(s2[j]!=0){
		s1[i++]=s2[j++];
	}
	s1[i]='\0';
}

void hefiles()	//将文件打包为一个二进制文件 
{
	FILE *fp1;
	int i;
	char c;
	fp1=fopen("C:\\Users\\86175\\Desktop\\文件夹\\newfile.bin","wb");
	if(fp1==NULL){
		printf("error1");
		exit(0);
	}
	fwrite((char *)&size,4,1,fp1);	//将int型写入二进制文件中 
	for(i=0;i<size;i++){
		fwrite((char *)&f[i].namesize,4,1,fp1);
		fwrite((char *)&f[i].fsize,4,1,fp1);
	}
	fclose(fp1);
	for(i=0;i<size;i++){	//以ab的方式将文件中的内容复制到二进制文件结尾 
		copyfile(i,f[i].s1);
	}
	cout<<"文件打包成功"<<endl;
//	cout<<"合成文件路径为:"<<"C:\\Users\\86175\\Desktop\\文件夹\\newfile.bin"<<endl;
}

void fenfiles()		//将二进制结构文件复原为原文件 
{
	
	FILE *fp1=fopen("C:\\Users\\86175\\Desktop\\文件夹\\newfile.bin","r");
	FILE *fp2;
	if (!fp1)
	{
		puts("文件打开失败！");
		exit(0);
	}
	fread((char *)&x,4,1,fp1);
	sum+=4;		//sum为记录指针移动 
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
		}	//str储存文件名 
		str[d[i].a]='\0';
		sum+=d[i].a;
		strcpy(d[i].s,filePath2);
		strcat(d[i].s,str);	//含文件路径的文件名	
		fp2=fopen(d[i].s,"wb");
		for(int j=0;j<d[i].b;j++){
			fread(&ch,1,1,fp1);
			fwrite(&ch,1,1,fp2);
			sum++;
		}
		fclose(fp2);
	}
	cout<<"文件复原成功"<<endl; 
//	cout<<"复原文件所在文件夹为:"<<"C:\\Users\\86175\\Desktop\\文件夹\\newfolder"<<endl;
}

void copyfile(int x,char *filename)		//将一个文件夹的内容复制到二进制结构文件中 
{
	FILE* fp1 = fopen(filename, "rb");
	FILE* fp2 = fopen("C:\\Users\\86175\\Desktop\\文件夹\\newfile.bin","ab");
	if (!fp1)
	{
		puts("文件打开失败！");
		exit(0);
	}
	if (!fp2)
	{
		puts("文件打开失败！");
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
