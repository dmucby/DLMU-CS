#include<iostream>
#include<cstdio>
#include<algorithm>
#include<string.h>

using namespace std;

int n;

struct Student{
    char num[20];
	char name[20];
	char major[20];
	char clas[20];
	float score[3];
	Student *next;
	//Student *pre;
};

typedef Student Node;

void CreateList(Node *h,int n);//�������� ����ѧ������Ϣ
void OutPut(Node *p);//������л�һ��ѧ������Ϣ
void Save(Node *h);  //��������ѧ����Ϣ���ļ�
int  Fetch(Node *h);//�����ȡĳ��ѧ������Ϣ
void Search_num( Node *h, char *stu_id ) ; // ����ָ��ѧ�ŵ�ѧ�������ظ�ѧ����ָ��
void InsertList( Node *h, char *id); // ���һ��ѧ����Ϣ�������У�����������
void Delete_num( Node *h, char *stu_id ) ; // ɾ��ָ��ѧ�ŵ�ѧ��
void Search_Major_Subject_Score(Node *h, char* stu_profes , int score_id , int stu_score ) ; // ����ĳ��רҵĳ�ſγ�С��ĳ��������ѧ��
void Delete_Class_Subject_Score(Node *h, char* stu_profes , int score_id , int stu_score ) ; // ɾ��ĳ���༶ĳ�ſγ�С��ĳ��������ѧ��
void PrintMenu();//��ӡ�˵�

int main(){
    int op;
    Node *h;
    h = new (Student);// ��ʼ������h
    h->next = NULL ;
    while( 1 ) {
        PrintMenu() ;
        printf( "������ѡ���ܣ�" ) ;
        scanf( "%d", &op ) ;
        if (op == 1) {
            printf( "������ѧ��������" ) ;
            scanf( "%d", &n );
            CreateList(h,n);
        }
        else if (op == 2) {
            int op2;
            printf("��ѡ���������:\n");
            printf("1.���ȫ��ѧ������Ϣ��\n");
            printf("2.���ĳ��ѧ������Ϣ��\n");
            scanf("%d",&op2);
            if(op2 == 1){
                Node *p=h;
                p=p->next;
                while(p!=NULL){
                    OutPut(p);
                    p = p->next;
                }

            }
            else if( op2 == 2){
                int n;
                Node *p=h;
                printf("������鿴ѧ����˳��\n");
                scanf("%d",&n);
                p=p->next;
                for(int i=0;i<n;i++){
                    p = p->next;
                }
                OutPut(p);
            }
            else{
                printf("��������ȷ�����֣�\n");
            }
        }
        else if (op == 3) {
            Save(h);
            printf( "�ɹ����浽�ļ���student_list.txt����\n" ) ;
        }
        else if(op==4){
            if(Fetch(h)==0){
				printf("��ȡʧ��\n");
				}
        }
        else if(op==5){
            printf("���������ѧ����ѧ��\n");
            char str[20];
            scanf("%s",str);
            Search_num(h,str);

        }
        else if(op==6){
            printf("���������ѧ����ѧ��");
            char id[100];
            scanf("%s",&id);
            InsertList(h,id);
        }
        else if(op==7){
            printf("������Ҫɾ��ѧ����ѧ��\n");
            char str[20];
            scanf("%s",str);
            Delete_num(h,str);
        }
        else if(op==8){
            printf("������Ҫ����ѧ����רҵ �γ� С�ڵķ���\n");
            char str[20];
            int class_i,score_d;
            scanf("%s",str);
            scanf("%d %d",&class_i,&score_d);
            Search_Major_Subject_Score(h,str,class_i,score_d);

        }
        else if(op==9){
            printf("������Ҫɾ��ѧ���ĵ�רҵ �γ� С�ڵķ���\n");
            char str[20];
            int class_i,score_d;
            scanf("%s",str);
            scanf("%d %d",&class_i,&score_d);
            Delete_Class_Subject_Score(h,str,class_i,score_d);
        }
        else if( op == 0){
            break;
        }
        else{
            printf("��������ȷ�����֣�\n");
        }
    }
    return 0;
}


void CreateList(Node *h,int n){
    for(int i=0;i<n;i++){
        Student *s = new(Student);
        printf("�������%d��ѧ����ȫ����Ϣ\n",i+1);
        printf("�����������ѧ�� ���� רҵ �༶\n");
        scanf( "%s%s%s%s", &s->num, s->name, s->major, s->clas ) ;
        printf("�������ѧ���ĸ��� ���� C���Եĳɼ�\n");
        scanf( "%f%f%f", &s->score[0], &s->score[1], &s->score[2] ) ;
        s->next = h->next; // s�ӵ���һ���ڵ�ǰ��
        h->next = s ;       // s��ɵ�һ��
    }
}

void OutPut(Node *p){
        printf("ѧ��   ����     רҵ   �༶     ����    ����    C����");
		printf("\n%s\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\n",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
}

void Save(Node *h){
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
	 Node *p=h;
     p=p->next;
     while(p!=NULL){
        fprintf(fp,"ѧ��   ����     רҵ   �༶     ����    ����    C����\n");
        fprintf(fp,"%s\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\t",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
        p = p->next;
    }

	fclose(fp);
}

int Fetch(Node *p){
    FILE *fp;
    p = p->next;
	int i=0;
	if ((fp = fopen("C:\\Users\\���\\Desktop\\student_list.txt","rb")) == NULL)
	{
		fclose(fp);
		return 0;
	}
	i = rand()%n;
	fseek(fp, sizeof(Student) * i, SEEK_SET);
	Student* student = new (Student);
    fread(student,sizeof(Node),1,fp);
    printf("�Ѷ�ȡ����%d��ѧ������Ϣ\n",i+1);
    printf("ѧ��   ����     רҵ   �༶     ����    ����    C����\n");
    printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
    printf("\n");
	fclose(fp);
	return 1;
}

void Search_num( Node *h,char *stu_id ) {
    Node *p = h;
    p=p->next;;
    while(p!=NULL){
        if(!(strcmp(p->num,stu_id))){
            printf("��ѧ������ϢΪ\n");
            OutPut(p);
            return ;
        }
        p=p->next;
    }
    printf("���޴��� ������ѧ��\n");
    return ;
}

void InsertList(Node *h,char *id){
    Node *p=h,*pre=h;   //����ǰָ���һ����ָ�� �����ҵ�����λ��
    p=p->next;
    Student *s = new(Student);
    strcpy(s->num,id);
    printf("�������²���ѧ����ȫ����Ϣ\n");
    printf("��������������� רҵ �༶\n");
    scanf( "%s%s%s", s->name, s->major, s->clas );
    printf("�������ѧ���ĸ��� ���� C���Եĳɼ�\n");
    scanf( "%f%f%f", &s->score[0], &s->score[1], &s->score[2]);
    while( p->next != NULL ) { //������������
        if(strcmp(p->num,s->num)<=0){// �ж�ѧ�Ŵ�С
            if(pre==NULL){ //��s�������ǰ  ǰ������
                s->next = p;
                p = s;
                return ;
            }else{
                s->next=pre->next;
                pre->next =s;
                return ;
            }
        }
        pre = p;
        p= p->next;
    }
    s->next = NULL; //û�ҵ�����λ��ֱ�Ӳ���β��
    p->next = s ;
    return ;
}


void Delete_num( Node *h,char *stu_id ){
    Node *p = h,*pre = h;
    p=p->next;
    while(p!=NULL){
        if(!(strcmp(p->num,stu_id))){
            pre->next = p->next;
            delete(p);
            printf("�ѳɹ�ɾ����ѧ������Ϣ\n");
            return;
        }
        pre = p;
        p = p->next;
    }
    printf("û�д�ѧ�ŵ�ѧ���������Ѿ���ɾ����!\n");
    return;
}

void Search_Major_Subject_Score(Node *h,char *major,int clas_i,int score_d){
    Node *p = h;
    p = p->next;
     while(p!=NULL){
        if(!(strcmp(p->major,major))){
                if(p->score[clas_i]<score_d){
                    printf("%sרҵ��%d�ſγ�С��%d�ֵ�ѧ������ϢΪ\n",major,clas_i,score_d);
                    OutPut(p);
                    return ;
                }
        }
        p=p->next;
    }
    printf("���޴��� ������ѧ��\n");
    return ;
}


void Delete_Class_Subject_Score(Node *head, char* stu_profes , int score_id , int stu_score ){
    Node *p=head->next;
    Node *q=head; //�������������ǰ����
    while(p!=NULL)
    {
        if(strcmp(p->major,stu_profes)==0 && p->score[score_id]<stu_score){
            q->next = p->next;
            free(p);
            p=q->next;
        }
        else{
            p=p->next;
            q=q->next;
        }
    }
    printf("ɾ���ɹ�\n");
    return ;
}


void PrintMenu(){
    printf( "***********************���ܲ˵�***************************************\n" ) ;
    printf( "1.����ѧ����Ϣ\n" ) ;
    printf( "2.���ѧ������Ϣ������ѧ��ѧ�ţ�\n");
    printf( "3.��ĳ��ѧ����Ϣ�����浽�ļ�������ѧ��ѧ�ţ�\n" );
    printf( "4.���ļ��������ȡĳ��ѧ������Ϣ������ѧ�ţ�\n" );
    printf( "5.����ĳ��ѧ������Ϣ������ѧ�ţ�\n" );
    printf( "6.���һ��ѧ������������������\n" );
    printf( "7.ɾ�������е�ĳ��ѧ��\n" );
    printf( "8.����ĳ��רҵĳ�ſγ�С��ĳ��������ѧ��\n" );
    printf( "9.ɾ��ĳ��רҵĳ�ſγ�С��ĳ��������ѧ��\n" );
    printf( "0.��������\n");
    printf( "***********************************************************************\n") ;
    printf("\n");
}

