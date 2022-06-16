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
		    printf("请输入即将录入信息的学生数\n");
            scanf("%d",&N);
            for(int i=0;i<N;i++){
				Input(stu+i,i);
			}
			break;
        }
		case 3:{
			getchar();
			Save(stu);
			printf("文件保存成功！\n");
			Ask();
			break;
		}
		case 2:{
			printf("请输入想查看第几个学生的信息：\n");
			scanf("%d",&n);
			if(i>=0&&n<N){
				Output(stu+n-1);
			}
			else{
				printf("输入错误，查无此人\n");
			}
			Ask();
			break;
		}
		case 4:{
			if(Fetch(stu)==0){
				printf("提取失败\n");
				}
			Ask();
			break;
		}
		case 5:{
			printf("请输入想查哪门科目的最高分\n");
			scanf("%d",&m);
			Max(stu,m);
			Ask();
			break;
		}
		case 6:{
                printf("对某个专业的学生，按平均成绩由低到高选择排序为:\n");
				Sort_select(stu);
				Ask();
				break;
			}
        case 7:{
		    printf("对某个班级的学生，按平均成绩由高到低起泡排名为：\n");
			Sort_buble(stu);
			Ask();
			break;
		}
		case 8:{
		    printf("对某个班级的学生，按某门课程成绩由低到高进行直接插入排序：\n");
			Sort_insert(stu);
			Ask();
			break;
		}
		case 9:{
		    printf("输入班级及某个分数，查找同学");
			getchar();
			Search(stu);
			Ask();
			break;
		}
		default:{
			printf("请正确输入0~9之间的数字!\n");
            break;
				}
		}//while
    }return 0;
}
//main
//***********************************************************

//输入函数：学号、姓名、专业、班级、三科成绩、总成绩
void Input(STU *p,int &i){
        int j;
        printf("请输入第%d个学生的全部信息\n",i+1);
		printf("请输入学生学号,回车结束\n");
		scanf("%s",&p->num);
		getchar();
		printf("请输入学生姓名,回车结束\n");
		gets(p->name);
		printf("请输入学生专业,回车结束\n");
		gets(p->major);
		printf("请输入学生班级，回车结束\n");
		scanf("%s",&p->clas);
		getchar();
		for(j=0;j<3;j++){
            printf("请输入第%d门成绩,回车结束\n",j);
            scanf("%d",&p->score[j]);

        }
        getchar();
	}

//输出函数
void Output(STU *p){
        printf("\n学号   名字     专业   班级     高数    日语    C语言");
		printf("\n%s\t%s\t%s\t%s\t%d\t%d\t%d\t",p->num,p->name,p->major,p->clas,p->score[0],p->score[1],p->score[2]);
}

//保存函数、将数据存入文件
void Save(STU *p)
{
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
	for(i=0;i<N;i++)
	{
		//if(fwrite(p++,sizeof(STU),1,fp)!=1)
		fprintf(fp,"学号   名字     专业   班级     高数    日语    C语言\n");
		fprintf(fp,"%s\t%s\t%s\t%s\t%d\t%d\t%d\t",(p+i)->num,(p+i)->name,(p+i)->major,(p+i)->clas,(p+i)->score[0],(p+i)->score[1],(p+i)->score[2]);
			//printf("文件写入失败，请重试！\n");
	}
	fclose(fp);
}

//阅读函数、读取文件中学生的信息
int Fetch(STU *p)
{
	FILE *fp;
	int i=0;
	if ((fp = fopen("C:\\Users\\余悸\\Desktop\\student_list.txt","rb")) == NULL)
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
    printf("已读取到第%d个学生的信息\n",i+1);
    printf("学号   名字     专业   班级     高数    日语    C语言\n");
    printf("%s\t%s\t%s\t%s\t%d\t%d\t%d\t",(p+i)->num,(p+i)->name,(p+i)->major,(p+i)->clas,(p+i)->score[0],(p+i)->score[1],(p+i)->score[2]);
	fclose(fp);
	return 1;
}

//选择排序函数、对某个专业的学生，按总平均成绩由低到高进行选择排序
void Sort_select(STU *p){
	int i,j,k;
	double t,aver[N];
	STU a;
	char b[10];
	getchar();//吸收回车字符
	printf("请输入你要查看成绩的专业:\n");
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
		        aver[i]=aver[k];//交换平均值
	        	aver[k]=t;
				a=*(p+i);
				*(p+i)=*(p+k);
				*(p+k)=a;//交换指针的引用
				}
	for(i=0;i<N;i++){
		if(!strcmp((p+i)->major,b)){
			printf("专业: %s\t班级: %s\t姓名: %s\t平均成绩: %5.3f\n",(p+i)->major,(p+i)->clas,(p+i)->name,aver[i]);}
	}
}

//冒泡排序函数、对某个班级的学生，按总平均成绩由高到低进行起泡排序
void Sort_buble(STU *p)
{
	int i,j;
	double t, aver[N];
	char b[20];
	STU a;
	printf("选择一个班级：\n");
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
	printf("%s班平均分从高到低为\n",b);
    for(i = 0;i < N;i++){
        if(!strcmp((p+i)->clas,b)){
            printf("姓名：%s\t平均分=%5.3f\n",(p+i)->name,aver[i]);
        }
    }

}
//插入排序函数、对某个班级的学生，按某门课程成绩由低到高进行直接插入排序
void Sort_insert(STU *p)
{
	int i, j, id, temp;
	int grade[N];
	char b[20];
	int k = 0;
	STU *m;
	m = p;
	printf("请输入你想查看成绩的班级：\n");
	scanf("%s",&b);
	printf("请输入你想查看成绩的课程：\n");
	scanf("%d", &id);
	if(id<0||id>2){
        printf("请输入正确的科目!\n");
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
        printf("对该班级的学生，按课程成绩由低到高进行插入排序为：\n");
		for(i = 0;i < k; i++){
			p = m;
			for (j = 0; j < N;j++,p++){
				if((!strcmp(p->clas,b))&&(p->score[id]==grade[i])){
					printf("专业: %s\t班级: %s\t姓名: %s\t该门课程的分数为: %5.3f\n",(p)->major,(p)->clas,(p)->name,p->score[id]);
					printf("\n");
				}
			}
    }
}

//搜索函数、实现班级和成绩的综合查找
void Search(STU *m){
	STU *p;
	int j,sum_scores;
	int limit_score;
	int op;
	char a[20];
	j=0;
	printf("请输入学生班级：\n");
	scanf("%s",&a);
	getchar();
	printf("请输入查找选项1.低于某分数 2.高于某分数\n");
	scanf("%d",&op);
	if(op==2){
        printf("请问您想要查询总分再多少以上学生？\n");
        scanf("%d",&limit_score);
        printf("您查询的学生信息为：\n");
        for(p=m;p<m+N;p++){
            sum_scores=(p->score[0])+(p->score[1])+(p->score[2]);
            if(!strcmp((p->clas),a)){
                if(sum_scores>=limit_score){
				Output(p);
				printf("\n");
				j++;
			}
			else{
                printf("该班无超过%d的学生！\n",limit_score);
			}
		}
		if(j==0){
			printf("您查找的班级不存在!");
            }
		}
	}
	else if(op==1){
        printf("请问您想要查询总分在多少以下学生？\n");
        scanf("%d",&limit_score);
        printf("您查询的学生信息为：\n");
        for(p=m;p<m+N;p++){
            sum_scores=(p->score[0])+(p->score[1])+(p->score[2]);
            if(!strcmp((p->clas),a)){
                if(sum_scores<=limit_score){
				Output(p);
				printf("\n");
				j++;
			}
			else{
                printf("该班无低于%d的学生！\n",limit_score);
			}
		}
		if(j==0){
			printf("您查找的班级不存在!");
            }
		}
	}
		else{
            printf("请输入正确的数字功能！\n");
		}
}//Search

//求所有学生某门课程的最高分和分数最高的学生的姓名
void Max(STU *stu,int grade_m)
{
    STU *p;
    p=stu;
    if(grade_m<0||grade_m>2){
        printf("请输入正确的科目!\n");
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
            printf("第%d科的最高分的人是 %s\n",grade_m,(p+i)->name);
            printf("他的第%d科的分数是 %d",grade_m,(p+i)->score[grade_m]);
            printf("\n");
        }
    }
    return ;
}

//询问函数
void Ask()
{
	int c;
	printf("\n您所需要的功能已经实现，是否继续进行？若退出请输入0\n");
	scanf("%d",&c);
	if(c==0)
		exit(0);
}

//计算平均分函数
double average_person(STU *p)
{
	return (((p->score[0])+(p->score[1])+(p->score[2]))/3.0);
}

void PrintMenu(){
    printf( "***********************功能菜单***************************************\n" ) ;
    printf( "1.输入学生信息\n" ) ;
    printf( "2.查找某学生的信息（输入学生学号）\n");
    printf( "3.将某个学生信息到保存到文件（输入学生学号）\n" );
    printf( "4.从文件中随机读取某个学生的信息（输入学号）\n" );
    printf( "5.求所有学生某门课程的最高分和分数最高的学生的姓名\n" ) ;
    printf( "6.对某个专业学生，总平均平均成绩从低到高选择排序并输出\n" );
    printf( "7.对某个班级的学生，总平均成绩从高到低冒泡排序输出\n" );
    printf( "8.对某个班级的学生，某门课程从低到高插入排序输出\n" );
    printf( "9.实现班级和成绩的综合查找\n" ) ;
    printf( "0.结束程序\n" ) ;
    printf( "***********************************************************************\n") ;
    printf("\n");
    printf("请输入选择的功能\n");
}
