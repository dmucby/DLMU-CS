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

void CreateList(Node *h,int n);//创建链表 输入学生的信息
void OutPut(Node *p);//输出所有或一个学生的信息
void Save(Node *h);  //保存所有学生信息到文件
int  Fetch(Node *h);//随机读取某个学生的信息
void Search_num( Node *h, char *stu_id ) ; // 查找指定学号的学生，返回该学生的指针
void InsertList( Node *h, char *id); // 添加一个学生信息到链表中，保持有序性
void Delete_num( Node *h, char *stu_id ) ; // 删除指定学号的学生
void Search_Major_Subject_Score(Node *h, char* stu_profes , int score_id , int stu_score ) ; // 查找某个专业某门课程小于某个分数的学生
void Delete_Class_Subject_Score(Node *h, char* stu_profes , int score_id , int stu_score ) ; // 删除某个班级某门课程小于某个分数的学生
void PrintMenu();//打印菜单

int main(){
    int op;
    Node *h;
    h = new (Student);// 初始化链表h
    h->next = NULL ;
    while( 1 ) {
        PrintMenu() ;
        printf( "请输入选择功能：" ) ;
        scanf( "%d", &op ) ;
        if (op == 1) {
            printf( "请输入学生个数：" ) ;
            scanf( "%d", &n );
            CreateList(h,n);
        }
        else if (op == 2) {
            int op2;
            printf("请选择输出功能:\n");
            printf("1.输出全部学生的信息。\n");
            printf("2.输出某个学生的信息。\n");
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
                printf("请输入查看学生的顺序\n");
                scanf("%d",&n);
                p=p->next;
                for(int i=0;i<n;i++){
                    p = p->next;
                }
                OutPut(p);
            }
            else{
                printf("请输入正确的数字！\n");
            }
        }
        else if (op == 3) {
            Save(h);
            printf( "成功保存到文件“student_list.txt”中\n" ) ;
        }
        else if(op==4){
            if(Fetch(h)==0){
				printf("提取失败\n");
				}
        }
        else if(op==5){
            printf("请输入查找学生的学号\n");
            char str[20];
            scanf("%s",str);
            Search_num(h,str);

        }
        else if(op==6){
            printf("请输入插入学生的学号");
            char id[100];
            scanf("%s",&id);
            InsertList(h,id);
        }
        else if(op==7){
            printf("请输入要删除学生的学号\n");
            char str[20];
            scanf("%s",str);
            Delete_num(h,str);
        }
        else if(op==8){
            printf("请输入要查找学生的专业 课程 小于的分数\n");
            char str[20];
            int class_i,score_d;
            scanf("%s",str);
            scanf("%d %d",&class_i,&score_d);
            Search_Major_Subject_Score(h,str,class_i,score_d);

        }
        else if(op==9){
            printf("请输入要删除学生的的专业 课程 小于的分数\n");
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
            printf("请输入正确的数字！\n");
        }
    }
    return 0;
}


void CreateList(Node *h,int n){
    for(int i=0;i<n;i++){
        Student *s = new(Student);
        printf("请输入第%d个学生的全部信息\n",i+1);
        printf("请输入该生的学号 姓名 专业 班级\n");
        scanf( "%s%s%s%s", &s->num, s->name, s->major, s->clas ) ;
        printf("请输入该学生的高数 日语 C语言的成绩\n");
        scanf( "%f%f%f", &s->score[0], &s->score[1], &s->score[2] ) ;
        s->next = h->next; // s接到第一个节点前面
        h->next = s ;       // s变成第一个
    }
}

void OutPut(Node *p){
        printf("学号   名字     专业   班级     高数    日语    C语言");
		printf("\n%s\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\n",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
}

void Save(Node *h){
    FILE *fp;
	char filename[20];
	int i;
	printf("请输入要保存的文件名称:\n");
	gets(filename);
	if((fp=fopen("C:\\Users\\余悸\\Desktop\\student_list.txt","w+"))==NULL)
	{
		printf("新建文件失败，请重试:\n");
		return;
	}
	 Node *p=h;
     p=p->next;
     while(p!=NULL){
        fprintf(fp,"学号   名字     专业   班级     高数    日语    C语言\n");
        fprintf(fp,"%s\t%s\t%s\t%s\t%.2f\t%.2f\t%.2f\t",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
        p = p->next;
    }

	fclose(fp);
}

int Fetch(Node *p){
    FILE *fp;
    p = p->next;
	int i=0;
	if ((fp = fopen("C:\\Users\\余悸\\Desktop\\student_list.txt","rb")) == NULL)
	{
		fclose(fp);
		return 0;
	}
	i = rand()%n;
	fseek(fp, sizeof(Student) * i, SEEK_SET);
	Student* student = new (Student);
    fread(student,sizeof(Node),1,fp);
    printf("已读取到第%d个学生的信息\n",i+1);
    printf("学号   名字     专业   班级     高数    日语    C语言\n");
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
            printf("该学生的信息为\n");
            OutPut(p);
            return ;
        }
        p=p->next;
    }
    printf("查无此人 可能退学了\n");
    return ;
}

void InsertList(Node *h,char *id){
    Node *p=h,*pre=h;   //申请前指针和一个后指针 便于找到插入位置
    p=p->next;
    Student *s = new(Student);
    strcpy(s->num,id);
    printf("请输入新插入学生的全部信息\n");
    printf("请输入该生的姓名 专业 班级\n");
    scanf( "%s%s%s", s->name, s->major, s->clas );
    printf("请输入该学生的高数 日语 C语言的成绩\n");
    scanf( "%f%f%f", &s->score[0], &s->score[1], &s->score[2]);
    while( p->next != NULL ) { //遍历整个链表
        if(strcmp(p->num,s->num)<=0){// 判断学号大小
            if(pre==NULL){ //将s插入后结点前  前结点后面
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
    s->next = NULL; //没找到合适位置直接插入尾部
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
            printf("已成功删除该学生的信息\n");
            return;
        }
        pre = p;
        p = p->next;
    }
    printf("没有此学号的学生，可能已经被删除了!\n");
    return;
}

void Search_Major_Subject_Score(Node *h,char *major,int clas_i,int score_d){
    Node *p = h;
    p = p->next;
     while(p!=NULL){
        if(!(strcmp(p->major,major))){
                if(p->score[clas_i]<score_d){
                    printf("%s专业第%d门课程小于%d分的学生的信息为\n",major,clas_i,score_d);
                    OutPut(p);
                    return ;
                }
        }
        p=p->next;
    }
    printf("查无此人 可能退学了\n");
    return ;
}


void Delete_Class_Subject_Score(Node *head, char* stu_profes , int score_id , int stu_score ){
    Node *p=head->next;
    Node *q=head; //与插入类似申请前后结点
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
    printf("删除成功\n");
    return ;
}


void PrintMenu(){
    printf( "***********************功能菜单***************************************\n" ) ;
    printf( "1.输入学生信息\n" ) ;
    printf( "2.输出学生的信息（输入学生学号）\n");
    printf( "3.将某个学生信息到保存到文件（输入学生学号）\n" );
    printf( "4.从文件中随机读取某个学生的信息（输入学号）\n" );
    printf( "5.查找某个学生的信息（输入学号）\n" );
    printf( "6.添加一个学生到链表保持其有序性\n" );
    printf( "7.删除链表中的某个学生\n" );
    printf( "8.查找某个专业某门课程小于某个分数的学生\n" );
    printf( "9.删除某个专业某门课程小于某个分数的学生\n" );
    printf( "0.结束程序\n");
    printf( "***********************************************************************\n") ;
    printf("\n");
}

