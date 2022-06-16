#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#define M 8
using namespace std;

//*******************************************************
struct Student{
	char num[20];
	char name[20];
	char major[20];
	char clas[20];
	int score[3];
};

int N;
typedef struct Student STU;

//*******************************************************
void Input(STU *p,int &i);
void Output(STU *p);
void Save(STU *p);
int Fetch(STU *p);
void Max(STU[],int m);
double average_person(STU *p);
void Sort_select(STU *P);
void Sort_buble(STU *p);
void Sort_insert(STU *p);
void Search(STU *p);
void Ask();
void PrintMenu();

//*******************************************************
int main(){
	int choice;
	int m,n,i,j;
	STU stu[N];
	char filename[10];
	STU *p;
	p=stu;
    while(1){
	PrintMenu();
	scanf("%d",&choice);
	switch(choice){
		case 1:{
		    printf("�����뼴��¼����Ϣ��ѧ����\n");
            scanf("%d",&N);
            for(int i=0;i<N;i++){
				Input(stu+i,i);
			}
			break;
        }
		case 3:{
			getchar();
			Save(stu);
			printf("�ļ�����ɹ���\n");
			Ask();
			break;
		}
		case 2:{
			printf("��������鿴�ڼ���ѧ������Ϣ��\n");
			scanf("%d",&n);
			if(i>=0&&n<N){
				Output(stu+n-1);
			}
			else{
				printf("������󣬲��޴���\n");
			}
			Ask();
			break;
		}
		case 4:{
			if(Fetch(stu)==0){
				printf("��ȡʧ��\n");
				}
			Ask();
			break;
		}
		case 5:{
			printf("������������ſ�Ŀ����߷�\n");
			scanf("%d",&m);
			Max(stu,m);
			Ask();
			break;
		}
		case 6:{
                printf("��ĳ��רҵ��ѧ������ƽ���ɼ��ɵ͵���ѡ������Ϊ:\n");
				Sort_select(stu);
				Ask();
				break;
			}
        case 7:{
		    printf("��ĳ���༶��ѧ������ƽ���ɼ��ɸߵ�����������Ϊ��\n");
			Sort_buble(stu);
			Ask();
			break;
		}
		case 8:{
		    printf("��ĳ���༶��ѧ������ĳ�ſγ̳ɼ��ɵ͵��߽���ֱ�Ӳ�������\n");
			Sort_insert(stu);
			Ask();
			break;
		}
		case 9:{
		    printf("����༶��ĳ������������ͬѧ");
			getchar();
			Search(stu);
			Ask();
			break;
		}
		default:{
			printf("����ȷ����0~9֮�������!\n");
            break;
				}
		}//while
    }return 0;
}
//main
//***********************************************************

//���뺯����ѧ�š�������רҵ���༶�����Ƴɼ����ܳɼ�
void Input(STU *p,int &i){
        int j;
        printf("�������%d��ѧ����ȫ����Ϣ\n",i+1);
		printf("������ѧ��ѧ��,�س�����\n");
		scanf("%s",&p->num);
		getchar();
		printf("������ѧ������,�س�����\n");
		gets(p->name);
		printf("������ѧ��רҵ,�س�����\n");
		gets(p->major);
		printf("������ѧ���༶���س�����\n");
		scanf("%s",&p->clas);
		getchar();
		for(j=0;j<3;j++){
            printf("�������%d�ųɼ�,�س�����\n",j);
            scanf("%d",&p->score[j]);

        }
        getchar();
	}

//�������
void Output(STU *p){
        printf("\nѧ��   ����     רҵ   �༶     ����    ����    C����");
		printf("\n%s\t%s\t%s\t%s\t%d\t%d\t%d\t",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
}

//���溯���������ݴ����ļ�
void Save(STU *p)
{
	FILE *fp;
	char filename[20];
	int i;
	printf("������Ҫ������ļ�����:\n");
	gets(filename);
	if((fp=fopen("C:\\Users\\���\\Desktop\\student_list.txt","w+"))==NULL)
	{
		printf("�½��ļ�ʧ�ܣ�������:\n");
		return;
	}
	for(i=0;i<N;i++)
	{
		//if(fwrite(p++,sizeof(STU),1,fp)!=1)
		fprintf(fp,"ѧ��   ����     רҵ   �༶     ����    ����    C����\n");
		fprintf(fp,"%s\t%s\t%s\t%s\t%d\t%d\t%d\t",(p+i)->num,(p+i)->name,(p+i)->major,(p+i)->clas,(p+i)->score[0],(p+i)->score[1],(p+i)->score[2]);
			//printf("�ļ�д��ʧ�ܣ������ԣ�\n");
	}
	fclose(fp);
}

//�Ķ���������ȡ�ļ���ѧ������Ϣ
int Fetch(STU *p)
{
	FILE *fp;
	int i=0;
	if ((fp = fopen("C:\\Users\\���\\Desktop\\student_list.txt","rb")) == NULL)
	{
	    //printf("1");
		fclose(fp);
		return 0;
	}
	//fseek(fp,(long)(sizeof(STU)),0);
	//rand()%N;
	fseek(fp, sizeof(Student) * 1, SEEK_SET);
	Student* student = new Student();
    fread(student,sizeof(STU),1,fp);
    printf("�Ѷ�ȡ����%d��ѧ������Ϣ\n",i+1);
    printf("ѧ��   ����     רҵ   �༶     ����    ����    C����\n");
    printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t",(p+i)->num,(p+i)->name,(p+i)->major,(p+i)->clas,(p+i)->score[0],(p+i)->score[1],(p+i)->score[2]);
	fclose(fp);
	return 1;
}

//ѡ������������ĳ��רҵ��ѧ��������ƽ���ɼ��ɵ͵��߽���ѡ������
void Sort_select(STU *p){
	int i,j,k;
	double t,aver[N];
	STU a;
	char b[10];
	getchar();//���ջس��ַ�
	printf("��������Ҫ�鿴�ɼ���רҵ:\n");
	gets(b);
	for(i=0;i<N;i++)
	{
		aver[i]=average_person(p+i);
	}
	for(i=0;i<N-1;i++)
	{
		k=i;
		for(j=i+1;j<N;j++)
			if(aver[k]>aver[j])
				k=j;
		        t=aver[i];
		        aver[i]=aver[k];//����ƽ��ֵ
	        	aver[k]=t;
				a=*(p+i);
				*(p+i)=*(p+k);
				*(p+k)=a;//����ָ�������
				}
	for(i=0;i<N;i++){
		if(!strcmp((p+i)->major,b)){
			printf("רҵ: %s\t�༶: %s\t����: %s\tƽ���ɼ�: %5.3f\n",(p+i)->major,(p+i)->clas,(p+i)->name,aver[i]);}
	}
}

//ð������������ĳ���༶��ѧ��������ƽ���ɼ��ɸߵ��ͽ�����������
void Sort_buble(STU *p)
{
	int i,j;
	double t, aver[N];
	char b[20];
	STU a;
	printf("ѡ��һ���༶��\n");
	scanf("%s",b);
	for(i = 0;i < N;i++)
	{
		aver[i] = average_person(p+i);
	}
	for(i = 0;i < N;i++){
        for(j = 0;j < N-1-i;j++){
            if(aver[j]<aver[j+1])
            {
			t = aver[j];
			aver[j] = aver[j+1];
			aver[j+1] = t;
			a = *(p+j);
			*(p+j) = *(p+j+1);
			*(p+j+1) = a;
            }
        }
	}
	printf("%s��ƽ���ִӸߵ���Ϊ\n",b);
    for(i = 0;i < N;i++){
        if(!strcmp((p+i)->clas,b)){
            printf("������%s\tƽ����=%5.3f\n",(p+i)->name,aver[i]);
        }
    }

}
//��������������ĳ���༶��ѧ������ĳ�ſγ̳ɼ��ɵ͵��߽���ֱ�Ӳ�������
void Sort_insert(STU *p)
{
	int i, j, id, temp;
	int grade[N];
	char b[20];
	int k = 0;
	STU *m;
	m = p;
	printf("����������鿴�ɼ��İ༶��\n");
	scanf("%s",&b);
	printf("����������鿴�ɼ��Ŀγ̣�\n");
	scanf("%d", &id);
	if(id<0||id>2){
        printf("��������ȷ�Ŀ�Ŀ!\n");
        return;
	}
	getchar();
	for (i = 0;i < N;i++,p++){
		if(!strcmp((p+i)->clas,b)){
			grade[k] = p->score[id];
			k++;
		}
	}
	for (i = 1;i < k;i++)
		if(grade[i]<grade[i-1])
		{
			temp = grade[i];
			j = i-1;

			do{
				grade[j+1] = grade[j];
				j--;
				}
				while (j >= 0&&temp < grade[j]);
			grade[j+1] = temp;
		}
        printf("�Ըð༶��ѧ�������γ̳ɼ��ɵ͵��߽��в�������Ϊ��\n");
		for(i = 0;i < k; i++){
			p = m;
			for (j = 0; j < N;j++,p++){
				if((!strcmp(p->clas,b))&&(p->score[id]==grade[i])){
					printf("רҵ: %s\t�༶: %s\t����: %s\t���ſγ̵ķ���Ϊ: %5.3f\n",(p)->major,(p)->clas,(p)->name,p->score[id]);
					printf("\n");
				}
			}
    }
}

//����������ʵ�ְ༶�ͳɼ����ۺϲ���
void Search(STU *m){
	STU *p;
	int j,sum_scores;
	int limit_score;
	int op;
	char a[20];
	j=0;
	printf("������ѧ���༶��\n");
	scanf("%s",&a);
	getchar();
	printf("���������ѡ��1.����ĳ���� 2.����ĳ����\n");
	scanf("%d",&op);
	if(op==2){
        printf("��������Ҫ��ѯ�ܷ��ٶ�������ѧ����\n");
        scanf("%d",&limit_score);
        printf("����ѯ��ѧ����ϢΪ��\n");
        for(p=m;p<m+N;p++){
            sum_scores=(p->score[0])+(p->score[1])+(p->score[2]);
            if(!strcmp((p->clas),a)){
                if(sum_scores>=limit_score){
				Output(p);
				printf("\n");
				j++;
			}
			else{
                printf("�ð��޳���%d��ѧ����\n",limit_score);
			}
		}
		if(j==0){
			printf("�����ҵİ༶������!");
            }
		}
	}
	else if(op==1){
        printf("��������Ҫ��ѯ�ܷ��ڶ�������ѧ����\n");
        scanf("%d",&limit_score);
        printf("����ѯ��ѧ����ϢΪ��\n");
        for(p=m;p<m+N;p++){
            sum_scores=(p->score[0])+(p->score[1])+(p->score[2]);
            if(!strcmp((p->clas),a)){
                if(sum_scores<=limit_score){
				Output(p);
				printf("\n");
				j++;
			}
			else{
                printf("�ð��޵���%d��ѧ����\n",limit_score);
			}
		}
		if(j==0){
			printf("�����ҵİ༶������!");
            }
		}
	}
		else{
            printf("��������ȷ�����ֹ��ܣ�\n");
		}
}//Search

//������ѧ��ĳ�ſγ̵���߷ֺͷ�����ߵ�ѧ��������
void Max(STU *stu,int grade_m)
{
    STU *p;
    p=stu;
    if(grade_m<0||grade_m>2){
        printf("��������ȷ�Ŀ�Ŀ!\n");
        return;
        }
    int max1=0;
    for(int i=0;i<N;i++){
        if((p+i)->score[grade_m]>max1){
            max1=(p)->score[grade_m];
        }
    }
    for(int i=0;i<N;i++){
        if(max1==(p+i)->score[grade_m]){
            printf("��%d�Ƶ���߷ֵ����� %s\n",grade_m,(p+i)->name);
            printf("���ĵ�%d�Ƶķ����� %d",grade_m,(p+i)->score[grade_m]);
            printf("\n");
        }
    }
    return ;
}

//ѯ�ʺ���
void Ask()
{
	int c;
	printf("\n������Ҫ�Ĺ����Ѿ�ʵ�֣��Ƿ�������У����˳�������0\n");
	scanf("%d",&c);
	if(c==0)
		exit(0);
}

//����ƽ���ֺ���
double average_person(STU *p)
{
	return (((p->score[0])+(p->score[1])+(p->score[2]))/3.0);
}

void PrintMenu(){
    printf( "***********************���ܲ˵�***************************************\n" ) ;
    printf( "1.����ѧ����Ϣ\n" ) ;
    printf( "2.����ĳѧ������Ϣ������ѧ��ѧ�ţ�\n");
    printf( "3.��ĳ��ѧ����Ϣ�����浽�ļ�������ѧ��ѧ�ţ�\n" );
    printf( "4.���ļ��������ȡĳ��ѧ������Ϣ������ѧ�ţ�\n" );
    printf( "5.������ѧ��ĳ�ſγ̵���߷ֺͷ�����ߵ�ѧ��������\n" ) ;
    printf( "6.��ĳ��רҵѧ������ƽ��ƽ���ɼ��ӵ͵���ѡ���������\n" );
    printf( "7.��ĳ���༶��ѧ������ƽ���ɼ��Ӹߵ���ð���������\n" );
    printf( "8.��ĳ���༶��ѧ����ĳ�ſγ̴ӵ͵��߲����������\n" );
    printf( "9.ʵ�ְ༶�ͳɼ����ۺϲ���\n" ) ;
    printf( "0.��������\n" ) ;
    printf( "***********************************************************************\n") ;
    printf("\n");
    printf("������ѡ��Ĺ���\n");
}
