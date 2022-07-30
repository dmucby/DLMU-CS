#include<bits/stdc++.h>
#define keyNum 11
using namespace std;
char keyWord[keyNum][10]={"call","do","else","for","function","if","int","main","read","while","write"};
char singleWord[]="+-*%():;,{}";//?????ֽ?
char doubleWord[]=">=<!";
FILE *Fin,*Fout;//???ָ?
char cifa_in[300];//??????
char cifa_out[300];
int init();//??ʼ??
int scan();//??
int isSaved(char *s){//????????? (????)
	int l=0,r=keyNum;
	while(l<r){
		int mid=(l+r)/2;
		if(strcasecmp(s,keyWord[mid])==0) return 1;
		if(strcasecmp(s,keyWord[mid])>0) l=mid+1;
		else r=mid;
	}
	return 0;
}

int init(){
	cout<<"Please input the File:"<<endl;
	cin>>cifa_in;
	strcat(cifa_in,".txt");
	if((Fin=fopen(cifa_in,"r"))==NULL){
		cout<<"Cn't find the File!"<<endl;
		return 0;
	}
	strcpy(cifa_out,"out_cifa_");
	strcat(cifa_out,cifa_in);
	if((Fout=fopen(cifa_out,"w"))==NULL){
		cout<<"Create lexical File Error!"<<endl;
		return 0;
	}
	return 1;
}

int scan(){
	char ch,buff[40];
	int es=1,j;
	int cnt=1;//???????ǰ???
	ch=getc(Fin);
	while(ch!=EOF){
		while(ch==' '||ch=='\t'||ch=='\n'){
			if(ch=='\n') cnt++;
			ch=getc(Fin);
		}
		if(ch==EOF) break;
		if(isalpha(ch)){//?????????
			buff[0]=ch;j=1;
			ch=getc(Fin);
			while(isalnum(ch)){
				buff[j++]=ch;
				ch=getc(Fin);
			}
			buff[j]='\0';
			if(isSaved(buff)) fprintf(Fout,"%s\t%s\n",buff,buff);
			else  fprintf(Fout,"%s\t%s\n","ID",buff);
		}
		else if(isdigit(ch)){//??????
			buff[0]=ch;ch=getc(Fin);j=1;
			while(isdigit(ch)){
				buff[j++]=ch;
				ch=getc(Fin);
			}
			buff[j]='\0';
			fprintf(Fout,"%s\t%s\n","NUM",buff);
		}
		else if(strchr(singleWord,ch)>0){//???ֽ?
			buff[0]=ch;buff[1]='\0';
			ch=getc(Fin);
			fprintf(Fout,"%s\t%s\n",buff,buff);
		}

		else if(strchr(doubleWord,ch)>0){//˫
			 buff[0]=ch; ch=getc(Fin);
			 if(ch=='='){
			 	buff[1]=ch;buff[2]='\0';
			 	ch=getc(Fin);
			 }
			 else buff[1]='\0';

			 fprintf(Fout,"%s\t%s\n",buff,buff);
		}
		else if(ch=='/'){
			ch=getc(Fin);
			if(ch=='*'){
				char ch1;
				ch1=getc(Fin);
				do{
					ch=ch1;ch1=getc(Fin);
				}while((ch!='*'||ch1!='/')&&ch1!=EOF);

				ch=getc(Fin);
			}
			else{
				buff[0]='/';buff[1]='\0';
				fprintf(Fout,"%s\t%s\n",buff,buff);
			}
		}
		else if(ch=='&'){
			buff[0]=ch;
			ch=getc(Fin);
			if(ch=='&'){
				buff[1]=ch;buff[2]='\0';
				fprintf(Fout,"%s\t%s\n",buff,buff);
				ch=getc(Fin);
			}
			else{
				buff[1]='\0';
				ch=getc(Fin);
				es=0;
				printf("%s\t%d\t%s\n","ERROR at line",cnt,buff);
			}
		}
		else if(ch=='|'){
			buff[0]=ch;
			ch=getc(Fin);
			if(ch=='|'){
				buff[1]=ch;buff[2]='\0';
				fprintf(Fout,"%s\t%s\n",buff,buff);
				ch=getc(Fin);
			}
			else{
				buff[1]='\0';
				ch=getc(Fin);
				es=0;
				printf("%s\t%d\t%s\n","ERROR at line ",cnt,buff);
			}
		}
		else{
			buff[0]=ch;buff[1]='\0';
			ch=getc(Fin);
			es=0;
			printf("%s\t%d\t%s\n","ERROR at line ",cnt,buff);
		}
	}
	fclose(Fin);
	fclose(Fout);
	return es;
}
