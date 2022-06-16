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
    printf("�������ǵڼ���ѧ��");
    scanf("%d",&n);
    if(n>N) return;
    printf("������ѧ��ѧ��");
    scanf("%lld",&stu[n].stuNumber);
    printf("������ѧ������");
    scanf("%s",&stu[n].name);
    printf("������ѧ���༶");
    scanf("%d",&stu[n].clas);
    printf("������ѧ��רҵ");
    scanf("%s",&stu[n].major);
    printf("������ѧ�����ųɼ�");
    for(int i=0;i<3;i++){
        scanf("%d",&stu[n].grade[i]);
    }
}

void OutPut(){
    int n;
    printf("�������ǵڼ���ѧ��");
    scanf("%d",&n);
    if(n>N) return;
    printf("������ѧ��Ϊ");
    printf("%lld\n",stu[n].stuNumber);
    printf("����������Ϊ");
    printf("%s\n",stu[n].name);
    printf("�������ڰ༶Ϊ");
    printf("%d\n",stu[n].clas);
    printf("������רҵΪ");
    printf("%s\n",stu[n].major);
    printf("���������ųɼ�Ϊ");
    for(int i=0;i<3;i++){
        printf("%d",stu[n].grade[i]);
    }
}

void  Save(int id_n) {
    char filename[20];
    int i;
    printf("������Ҫ������ļ�����\n");
    gets(filename);
    if((fp=fopen(filename, "wb"))==NULL){
        printf("�½��ļ�ʧ�� ����������\n");
        return;
    }
    for(i=0;i<N;i++){
        if((fwrite(stu[i]),sizeof(Student),1,fp)!=1)
            printf("�ļ�д��ʧ�� ����������");
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
            printf("��%d�Ƶ���߷ֵ����� %s",grade_m,stu[i].name);
            printf("���ĵ�%d�Ƶķ����� %d",grade_m,stu[i].grade[grade_m]);
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
    printf("%d���%d�Ƴɼ��ӵ͵���Ϊ\n");
    for(int i=0;i<N;i++){
        if(kSum[i]!=0){
            printf("%d ",kSum[i]);
        }
    }
    printf("\n");
}

void Search(int clas_n,int sum_n){
    printf("�ۺϲ�ѯ\n");
    for(int i=0;i<N;i++){
        if(stu[i].clas==clas_n){
            if(aSum[i]*3>sum_n){
                printf("%d�����%d��ѧ���� ѧ�ţ�%lld ������%s\n",clas_n,sum_n,stu[i].stuNumber,stu[i].name );
            }
        }
    }
}

void PrintMenu(){
    printf( "***********************���ܲ˵�***************************************\n" ) ;
    printf( "1.����ѧ����Ϣ\n" ) ;
    printf( "2.���ĳ��ѧ������Ϣ������ѧ��ѧ�ţ�\n");
    printf( "3.��ĳ��ѧ����Ϣ���ļ�������ѧ��ѧ�ţ�\n" ) ;
    printf( "4.���ļ��������ȡĳ��ѧ������Ϣ������ѧ�ţ�\n" ) ;
    printf( "5.������ѧ��ĳ�ſγ̵���߷ֺͷ�����ߵ�ѧ��������\n" ) ;
    printf( "6.��ĳ��רҵѧ������ƽ��ƽ���ɼ��ӵ͵���ѡ���������\n" ) ;
    printf( "7.��ĳ���༶��ѧ������ƽ���ɼ��Ӹߵ���ð���������\n" ) ;
    printf( "8.��ĳ���༶��ѧ����ĳ�ſγ̴ӵ͵��߲����������\n" ) ;
    printf( "9.ʵ�ְ༶�ͳɼ����ۺϲ���\n" ) ;
    printf( "0.��������\n" ) ;
    printf( "***********************************************************************\n") ;
    printf("\n");
}

int main(){
    int n;
    while(1){
        PrintMenu();
        printf("��ѡ������Ĺ���:\n");
        scanf("%d",&n);
        if(n==1){
           printf("������һ��ѧ��ȫ����Ϣ:\n");
           Input();
        }
        if(n==2){
            printf("���ĳѧ����Ϣ");
            OutPut();
        }
        if(n==3){
            int id;
            printf("����������ѧ��˳��:\n");
            scanf("%d",id);
            Save(id);
        }
        if(n==4){
            printf("�����ȡĳ��ѧ������Ϣ\n");
            Fetch();
            printf("\n");
        }
        if(n==5){
            int s;
            printf("������ڼ��ſγ�\n");
            scanf("%d",&s);
            Max(s);
        }
        if(n==6){
            char s[100];
            printf("����������רҵ\n");
            scanf("%s",&s);
            Sort_select(s);
        }
        if(n==7){
            int s1;
            printf("����������༶\n");
            scanf("%d",&s1);;
            Sort_buble(s1);
        }
        if(n==8){
            int s2,s3;
            printf("����������༶�Ϳγ�\n");
            scanf("%d",&s2);
            scanf("%d",&s3);
            Sort_insert(s2,s3);
        }
        if(n==9){
            int s4,s5;
            printf("����������༶��Ҫ�����");
            scanf("%d %d",&s4,&s5);
            Search(s4,s5);
        }
        if(n==0){
            break;
        }
    }
    return 0;
}

