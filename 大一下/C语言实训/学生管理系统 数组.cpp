#include<stdio.h>
#include<math.h>
#include<bits/stdc++.h>
#include<stdlib.h>

const int N=3;
float aSum[N]={0};
FILE *fp;


struct Student{
    long long stuNumber;
    char name[100];
    char major[100];
    int clas;
    int grade[4];
};

Student stu[N];

void PrintMenu();
void swap(int *a, int *b);
void qiu_sum();
void select_sort(int *data, int length);
void insert_sort(int* data,int length);
void buble_sort(int *data, int length);
void Input();
void OutPut();
void Save(int stu_id);
void Fetch();
void Max(int grade_n);
void Sort_select(char *major1);
void Sort_buble(int clas1);
void Sort_insert(int clas_n,int grade_n);
void Search(int clas_n,int sum_n);

void Input(){
    int n;
    printf("请输入是第几个学生");
    scanf("%d",&n);
    if(n>N) return;
    printf("请输入学生学号");
    scanf("%lld",&stu[n].stuNumber);
    printf("请输入学生姓名");
    scanf("%s",&stu[n].name);
    printf("请输入学生班级");
    scanf("%d",&stu[n].clas);
    printf("请输入学生专业");
    scanf("%s",&stu[n].major);
    printf("请输入学生三门成绩");
    for(int i=0;i<3;i++){
        scanf("%d",&stu[n].grade[i]);
    }
}

void OutPut(){
    int n;
    printf("请输入是第几个学生");
    scanf("%d",&n);
    if(n>N) return;
    printf("该生的学号为");
    printf("%lld\n",stu[n].stuNumber);
    printf("该生的姓名为");
    printf("%s\n",stu[n].name);
    printf("该生所在班级为");
    printf("%d\n",stu[n].clas);
    printf("该生的专业为");
    printf("%s\n",stu[n].major);
    printf("该生的三门成绩为");
    for(int i=0;i<3;i++){
        printf("%d",stu[n].grade[i]);
    }
}

void  Save(int id_n) {
    char filename[20];
    int i;
    printf("请输入要保存的文件名称\n");
    gets(filename);
    if((fp=fopen(filename, "wb"))==NULL){
        printf("新建文件失败 请重新输入\n");
        return;
    }
    for(i=0;i<N;i++){
        if((fwrite(stu[i]),sizeof(Student),1,fp)!=1)
            printf("文件写入失败 请重新输入");
    }
    fclose(fp);
}

void Fetch(){
    if((fp=fopen(filename,"rb"))==NULL){
        fclose(fp);
        return 0;
    }

    fclose(fp);
}

void Max(int grade_m){
    int max1=0;
    for(int i=0;i<N;i++){
        if(stu[i].grade[grade_m]>max1){
            max1=stu[i].grade[grade_m];
        }
    }
    for(int i=0;i<N;i++){
        if(max1==stu[i].grade[grade_m]){
            printf("第%d科的最高分的人是 %s",grade_m,stu[i].name);
            printf("他的第%d科的分数是 %d",grade_m,stu[i].grade[grade_m]);
            printf("\n");
        }
    }
    return ;
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void qiu_sum(){
    for(int i=0;i<N;i++){
        for(int j=0;j<3;j++){
            aSum[i]+=stu[i].grade[j];
        }
        aSum[i]=aSum[i]/3;
    }
}

void select_sort(int *data, int length) {
    int temp;
    for(int i=0;i<length-1;i++){
        temp=i;
        for(int j=i+1;j<length;j++){
            if(data[temp]<data[j]){
                temp=j;
            }
        }
        if(i!=temp){
        swap(&data[i],&data[temp]);
        }
    }
}

void Sort_select(char *major1){
    int zSum[N];
    int k=0;
    for(int i=0;i<N;i++){
        if(strcmp(stu[i].major,major1)){
            zSum[k++]=aSum[i];
        }
    }
    select_sort(zSum,sizeof(zSum)/sizeof(zSum[0]));
    for(int i=0;i<N;i++){
        if(zSum[i]!=0){
            printf("%d ",zSum[i]);
        }
    }
    printf("\n");
}

void buble_sort(int *data, int length) {
    int temp;
    for(int i=0;i<length-1;i++){
        for(int j=i+1;j<length;j++){
            if(data[i]>data[j]){
            swap(&temp,&data[i]);
            swap(&data[i],&data[j]);
            swap(&data[j],&temp);
            }
        }
    }
}

void Sort_buble(int clas1){
    int cSum[N];
    int k=0;
    for(int i=0;i<N;i++){
        if(stu[i].clas==clas1){
            cSum[k++]=aSum[i];
        }
    }
    buble_sort(cSum,sizeof(cSum)/sizeof(cSum[0]));
    for(int i=0;i<N;i++){
        if(cSum[i]!=0){
            printf("%d ",cSum[i]);
        }
    }
    printf("\n");
}

void insert_sort(int* data,int length){
    for(int i=1;i<length;i++){
        int temp = data[i];
        int j;
        for(int j=i-1;j>=0 && data[j] >temp;j--){
            data[j+1]=data[j];
        }
        data[j+1]=temp;
    }
}

void Sort_insert(int clas_n,int grade_n){
    int kSum[N];
    int k=0;
    for(int i=0;i<N;i++){
        if(stu[i].clas==clas_n){
            kSum[k++]=stu[i].grade[grade_n];
        }
    }
    insert_sort(kSum,sizeof(kSum)/sizeof(kSum[0]));
    printf("%d班的%d科成绩从低到高为\n");
    for(int i=0;i<N;i++){
        if(kSum[i]!=0){
            printf("%d ",kSum[i]);
        }
    }
    printf("\n");
}

void Search(int clas_n,int sum_n){
    printf("综合查询\n");
    for(int i=0;i<N;i++){
        if(stu[i].clas==clas_n){
            if(aSum[i]*3>sum_n){
                printf("%d班大于%d的学生的 学号：%lld 姓名：%s\n",clas_n,sum_n,stu[i].stuNumber,stu[i].name );
            }
        }
    }
}

void PrintMenu(){
    printf( "***********************功能菜单***************************************\n" ) ;
    printf( "1.输入学生信息\n" ) ;
    printf( "2.输出某个学生的信息（输入学生学号）\n");
    printf( "3.将某个学生信息到文件（输入学生学号）\n" ) ;
    printf( "4.从文件中随机读取某个学生的信息（输入学号）\n" ) ;
    printf( "5.求所有学生某门课程的最高分和分数最高的学生的姓名\n" ) ;
    printf( "6.对某个专业学生，总平均平均成绩从低到高选择排序并输出\n" ) ;
    printf( "7.对某个班级的学生，总平均成绩从高到低冒泡排序输出\n" ) ;
    printf( "8.对某个班级的学生，某门课程从低到高插入排序输出\n" ) ;
    printf( "9.实现班级和成绩的综合查找\n" ) ;
    printf( "0.结束程序\n" ) ;
    printf( "***********************************************************************\n") ;
    printf("\n");
}

int main(){
    int n;
    while(1){
        PrintMenu();
        printf("请选择输入的功能:\n");
        scanf("%d",&n);
        if(n==1){
           printf("请输入一个学生全部信息:\n");
           Input();
        }
        if(n==2){
            printf("输出某学生信息");
            OutPut();
        }
        if(n==3){
            int id;
            printf("请输入输入学生顺序:\n");
            scanf("%d",id);
            Save(id);
        }
        if(n==4){
            printf("随机读取某个学生的信息\n");
            Fetch();
            printf("\n");
        }
        if(n==5){
            int s;
            printf("请输入第几门课程\n");
            scanf("%d",&s);
            Max(s);
        }
        if(n==6){
            char s[100];
            printf("请输入所求专业\n");
            scanf("%s",&s);
            Sort_select(s);
        }
        if(n==7){
            int s1;
            printf("请输入所求班级\n");
            scanf("%d",&s1);;
            Sort_buble(s1);
        }
        if(n==8){
            int s2,s3;
            printf("请输入所求班级和课程\n");
            scanf("%d",&s2);
            scanf("%d",&s3);
            Sort_insert(s2,s3);
        }
        if(n==9){
            int s4,s5;
            printf("请输入所求班级和要求分数");
            scanf("%d %d",&s4,&s5);
            Search(s4,s5);
        }
        if(n==0){
            break;
        }
    }
    return 0;
}

