#include<bits/stdc++.h>
#include<io.h>
#include<direct.h>
using namespace std;
double getfilesize(char* filename);
void getFiles( string, vector<string>& );
void outsize(char * filename);
void print();
struct file{
	char s1[50];//含路径的文件名
	char s2[50];//文件名不含路径 
	char s3[10];//文件名，不含路径和后缀名 
	char s4[10];//扩展名 
}f[30]; 
int size;

int main()
{
	int len1,len2,j;
	char * filePath;
	char s[50];
	cin>>s;	  //字符串s为文件夹的路径 C:\Users\86175\Desktop\文件夹
	len1=strlen(s);//len为文件夹路径的字符串长度 
	filePath=s;
    vector<string> files;
	getFiles(filePath,files);
	char str[50];
	size = files.size();	//size为文件个数   files[i].c_str()为文件夹内文件路径 
	for(int i=0;i<size;i++){ 
		strcpy(f[i].s1,files[i].c_str());
		len2=strlen(f[i].s1);
		int k=0,m=0;
		if(f[i].s1[len1+1]=='.'){
			f[i].s4[0]='.';
			f[i].s4[1]='\0';
			for(j=len1+1;f[i].s1[j]!='\0';j++){
				f[i].s2[k++]=f[i].s1[j];
			} 
			strcpy(f[i].s3,f[i].s2);
		}
		else{
			for(j=len1+1;(f[i].s1[j]!='.')&&(f[i].s1[j]!='\0');j++){
				f[i].s2[k]=f[i].s1[j];
				f[i].s3[k]=f[i].s1[j];
				k++;
			}
			if(j>=len2){
				f[i].s4[0]='.';
				f[i].s4[1]='\0';
			}
			else{
				f[i].s2[k++]='.';
				while(f[i].s1[j]!='\0'){
					f[i].s4[m++]=f[i].s1[j++];
					f[i].s2[k++]=f[i].s1[j];
				}
			}
		}
		/*
		cout<<f[i].s2<<' '<<getfilesize(f[i].s1)<<' ';
		outsize(f[i].s1);
		cout<<endl;
		*/
	}
	print();
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
void print()
{
	for(int i=0;i<size;i++){
		printf("%s\n",f[i].s1);
		printf("%s\n",f[i].s2);
		printf("%s\n",f[i].s3);
		printf("%s\n",f[i].s4);
		printf("\n");
	}
}

