#include <stdio.h>
#include <string>
#include <iostream>
#include <io.h>
#include <Windows.h>
#include <sys/stat.h>
#define INFECTFLAG_M 0x736c796976616c65650a  //�ҵ�������sylvialee
#define INFECTFLAG_H 0x8b4d0883c101894d08c7 //ͬ���������
using namespace std;
		
long offset[3],len[3];
string dest;
char path[100][260];	
char dest_c[100];
int num;
unsigned char signature[3][100]= {{0x73,0x79,0x6C,0x76,0x69,0x61,0x6C,0x65,0x65,0x0A},{0x8B,0x4D,0x08,0x83,0xC1,0x01,0x89,0x4D,0x08,0xC7}};  //�������ݶ�����뷴���ѡȡ
bool scan_virus(const char *FileName,long offset, int length, void *signature)
{ 	FILE *fp = NULL;  
 	int result=0;  
	char rvir[255]={ 0 };  
	bool Flag=false;
  	fp=fopen(FileName,"rb");      //��2���ƴ�ָ���ļ�
  	if(fp==NULL)
 	 { return Flag; }
  	fseek(fp,offset,SEEK_SET);   //���ļ�ָ��ָ��ƫ�Ƶ�ַ
  	fread(rvir,length,1,fp);         //��ȡlength���ȵĴ���
 	result=memcmp(signature,rvir,length);  //��������ȡ�Ĵ���Ƚϣ�����ֵ�ŵ�result��
  	if(result==0) 
 	   { Flag=true;}
	fclose(fp);  
	return Flag;
}
void virus_warning(char *name,char *path,int num){  //�ļ��в�ɱ�����������ʾ
	struct stat buf ;   //��ȡ�ļ���С 
    if ( stat( path, &buf ) < 0 )
    {
        perror( "stat" );
        return;
    }
    if (num==1) cout<<"���棡���ֲ�����"<<endl<<"virus"<<num<<":"<<endl; else cout<<"virus"<<num<<":"<<endl;
	
	cout<<"�����ļ����� "<<name<<endl; 
	cout<<"����·��:   "<<path<<endl; 
	cout<<"���ļ���С�� "<<buf.st_size<<"�ֽ�"<<endl<<endl;; 
} 
int Find_Virus(char *Path){  //�ļ��в�ɱ��ɨ�������ļ�

    int done;
    int i;
    struct _finddata_t ffblk;
    char document[100]; 
	strcpy(document, Path);
	strcat(document,"\\");
	strcat(document,  "\\*.exe");  //����·��������exe�ļ� 
    done = _findfirst(document,&ffblk);
    int ii=1;		
    if(done!=-1L)
    { 
		char file_path[100];   
		strcpy(file_path,Path);
		strcat(file_path,"\\");  
		strcat(file_path,"\\");  
		strcat(file_path,ffblk.name);  //����·���������ļ�
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
        if (ii==1) cout<<"û�з��ֲ���"<<endl;
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
	
		printf("��������Ҫ�����ַ�ʽ���в�ɱ��\n 1.ָ���ļ���ɱ 2.ָ���ļ���ɨ��\n");
		cin>>num;
			printf("�������ɱ·����");
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
			if (scan_virus(dest_c,offset[0],len[0],signature[0])||scan_virus(dest_c,offset[1],len[1],signature[1])) {//����ֵƥ�� 
				
				int pos = dest.find_last_of('\\');
				string s((string)dest.substr(pos + 1) );  //��ȡ�ļ��� 
				struct stat buf ;   //��ȡ�ļ���С 
			    if ( stat( dest_c, &buf ) < 0 )
			    {
			    	
			        perror( "stat" );
			    }
				cout<<"���棡���ֲ�����"<<endl;
				cout<<"�����ļ����� "<<s<<endl; 
				cout<<"����·��:  "<<dest<<endl; 
				cout<<"���ļ���С�� "<<buf.st_size<<"�ֽ�"<<endl; 
				
			}else {
				cout<<"û�з��ֲ���"<<endl; 
			}
		}
		cout<<"�������Ƿ�������в�ɱ������������1���˳�������0" <<endl;
		cin>>l; 
	}
}
