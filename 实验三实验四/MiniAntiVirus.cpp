#include <stdio.h>
#include <string>
#include <iostream>
#include <io.h>
#include <Windows.h>
#include <sys/stat.h>
#define INFECTFLAG_M 0x736c796976616c65650a  //我的特征码sylvialee
#define INFECTFLAG_H 0x8b4d0883c101894d08c7 //同伴的特征码
using namespace std;
		
long offset[3],len[3];
string dest;
char path[100][260];	
char dest_c[100];
int num;
unsigned char signature[3][100]= {{0x73,0x79,0x6C,0x76,0x69,0x61,0x6C,0x65,0x65,0x0A},{0x8B,0x4D,0x08,0x83,0xC1,0x01,0x89,0x4D,0x08,0xC7}};  //特征根据恶意代码反汇编选取
bool scan_virus(const char *FileName,long offset, int length, void *signature)
{ 	FILE *fp = NULL;  
 	int result=0;  
	char rvir[255]={ 0 };  
	bool Flag=false;
  	fp=fopen(FileName,"rb");      //以2进制打开指定文件
  	if(fp==NULL)
 	 { return Flag; }
  	fseek(fp,offset,SEEK_SET);   //把文件指针指向偏移地址
  	fread(rvir,length,1,fp);         //读取length长度的代码
 	result=memcmp(signature,rvir,length);  //与我们提取的代码比较，返回值放到result中
  	if(result==0) 
 	   { Flag=true;}
	fclose(fp);  
	return Flag;
}
void virus_warning(char *name,char *path,int num){  //文件夹查杀中输出病毒警示
	struct stat buf ;   //获取文件大小 
    if ( stat( path, &buf ) < 0 )
    {
        perror( "stat" );
        return;
    }
    if (num==1) cout<<"警告！发现病毒！"<<endl<<"virus"<<num<<":"<<endl; else cout<<"virus"<<num<<":"<<endl;
	
	cout<<"病毒文件名： "<<name<<endl; 
	cout<<"病毒路径:   "<<path<<endl; 
	cout<<"该文件大小： "<<buf.st_size<<"字节"<<endl<<endl;; 
} 
int Find_Virus(char *Path){  //文件夹查杀中扫描所有文件

    int done;
    int i;
    struct _finddata_t ffblk;
    char document[100]; 
	strcpy(document, Path);
	strcat(document,"\\");
	strcat(document,  "\\*.exe");  //遍历路径下所有exe文件 
    done = _findfirst(document,&ffblk);
    int ii=1;		
    if(done!=-1L)
    { 
		char file_path[100];   
		strcpy(file_path,Path);
		strcat(file_path,"\\");  
		strcat(file_path,"\\");  
		strcat(file_path,ffblk.name);  //遍历路径下所有文件
		if (scan_virus(ffblk.name,offset[0],len[0],signature[0])||scan_virus(ffblk.name,offset[1],len[1],signature[1])) {
			virus_warning(ffblk.name,file_path,ii);
			ii++;
		}                   
        while ((_findnext(done,&ffblk))==0)
        {
            strcpy(file_path,Path);
			strcat(file_path,"\\");
			strcat(file_path,"\\");  
			strcat(file_path,ffblk.name);  
			if (scan_virus(file_path,offset[0],len[0],signature[0])||scan_virus(file_path,offset[1],len[1],signature[1])) {
				virus_warning(ffblk.name,file_path,ii);
				ii++;
			}             
        } 
		_findclose(done);
        if (ii==1) cout<<"没有发现病毒"<<endl;
    } 
   
    return 1;
}
int main()
{ 
	bool flag=false;
	offset[0]=0x00000013;
	offset[1]=0x000110D0;
	len[0]=0x0A;
	len[1]=0x0A;
	int l=1;
	while (l==1){
	
		printf("请输入您要以哪种方式进行查杀：\n 1.指定文件查杀 2.指定文件夹扫描\n");
		cin>>num;
			printf("请输入查杀路径：");
			scanf("%s",dest_c);
			dest=dest_c;
	
			int i;
			for(i=0; i<dest.length(); ++i)
			{
		   		dest_c[i] = dest[i];
			}
			dest_c[i] = '\0';
	
		if(num==2) Find_Virus(dest_c);
		if (num==1) {
			if (scan_virus(dest_c,offset[0],len[0],signature[0])||scan_virus(dest_c,offset[1],len[1],signature[1])) {//特征值匹配 
				
				int pos = dest.find_last_of('\\');
				string s((string)dest.substr(pos + 1) );  //获取文件名 
				struct stat buf ;   //获取文件大小 
			    if ( stat( dest_c, &buf ) < 0 )
			    {
			    	
			        perror( "stat" );
			    }
				cout<<"警告！发现病毒！"<<endl;
				cout<<"病毒文件名： "<<s<<endl; 
				cout<<"病毒路径:  "<<dest<<endl; 
				cout<<"该文件大小： "<<buf.st_size<<"字节"<<endl; 
				
			}else {
				cout<<"没有发现病毒"<<endl; 
			}
		}
		cout<<"请问您是否继续进行查杀？继续请输入1，退出请输入0" <<endl;
		cin>>l; 
	}
}
