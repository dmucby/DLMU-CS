#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std ;

const int keywordNum = 16 ;       //�����ָ���
const int singlewordNum = 10 ;     //���ֽ������
const int pureSingleNum = 6 ;     //�����ַ�����
const int doublewordNum = 6 ;     //˫�ֽ������

char identifier[105] ;          //��¼��ǰ�ı�ʶ��
int identifierLength = 0 ;      //��ʶ������
int keywordPlace ;              //�����ֵ�λ��
char numbers[105] ;             //��¼��ǰ���ִ�С
int numbersLength = 0 ;         //����λ��
char character[10] ;             //��¼Ŀǰ�ֽ��
int characterNum = 0 ;         //�ֽ����
char note[2] ;                  //��¼������ע�͵��ַ�
int noteNum = 0 ;               //ע����
bool startFlag = false ;       //����Ƿ����ע��
char prior ;                    //��һ����ȡ���ַ�
int errorSum = 0 ;              //��������
int line = 1 ;                  //Դ��������
char inputAddress[20] ;     //�����ļ���ַ
char outputAddress[20] ;    //����ļ���ַ
FILE *inputFile ;               //����test�ļ�
FILE *outputFile ;              //�������ļ�

char keyword[keywordNum][20] = {"break", "call", "case", "default", "do",
            "else", "for", "function", "if", "int", "read", "switch", "then", "while", "write","return" } ; //�����֣����ֵ����ź�
char pureSingleword[pureSingleNum] = {'(', ')', ',', ';', '{', '}'} ;           //�����ַ�
char singleword[singlewordNum] = {'!', '&', '*','%', '+', '-', '<', '=', '>', '|'} ;//���ַ�����ܴ���˫�ַ�
char doubleword[doublewordNum][5] = {"!=", "&&", "<=", "==", ">=", "||"} ;      //˫�ַ�
char errors[105][50] ;

//�۰���ұ����֣�Ҫʹ�ñ����Ȱѱ����ֱ���С�����˳���ź�
bool binarySearch(char temp[], int left, int right) {
    if(left > right)    //��������Ԫ�ض��Ҳ���
        return false ;
    int mid = (left+right) / 2 ;
    if(!strcmp(temp, keyword[mid])) {       //�ҵ�����ʱ�洢�ڱ�ʶ��������ͬ�ľ��Ǳ�����
        keywordPlace = mid ;
        return true ;
    }
    else if(strcmp(temp, keyword[mid]) > 0)
        return binarySearch(temp, mid+1, right) ;
    else
        return binarySearch(temp, left, mid-1) ;
}
//�ж��ַ��Ƿ�Ϊ����
bool isNull(char temp) {
    if(temp=='\n') {
        line++ ;            //ÿ��һ���س��ͼ�һ��
        return true ;
    }
    if(temp==' ' || temp=='\t' || temp=='\n')//���ְ����ո񡢻س���tab
        return true ;
    else
        return false ;
}
//�ж��ַ��Ƿ�����ĸ
bool isLetter(char temp) {
    if(temp<='z' && temp>='a')  //Сд��ĸ
        return true ;
    if(temp<='Z' && temp>='A')  //��д��ĸ
        return true ;
    return false ;
}
//�ж��ַ��Ƿ�������
bool isNumber(char temp) {
    if(temp<='9' && temp>='0')
        return true ;
    return false ;
}
//�ж��Ƿ��Ǵ����ַ�
bool isPureSingleword(char temp) {
    for(int i=0; i<pureSingleNum; i++) {    //���Ѿ�д�õĴ����ַ�������ͬ�ľ���
        if(temp == pureSingleword[i])
            return true ;
    }
    return false ;
}
//�ж��Ƿ��ǵ��ַ�
bool isSingleword(char temp) {
    for(int i=0; i<singlewordNum; i++) {    //���Ѿ�д�õĵ��ַ�������ͬ�ľ���
        if(temp == singleword[i])
            return true ;
    }
    return false ;
}

//�ж��Ƿ��ǵ�˫�ַ�
bool isDoubleword() {
    for(int i=0; i<doublewordNum; i++) {    //���Ѿ�д�õ�˫�ַ�������ͬ�ľ���
        if(!strcmp(character, doubleword[i]))
            return true ;
    }
    return false ;
}

//�ж��Ƿ��� '/'  �����ж��Ƿ��п�����ע�͵Ŀ�ʼ��־
bool isDiagonal(char temp) {
    if(temp=='/' || temp=='*')      //ע�͵Ŀ�ʼ��־��  /*  ���
        return true ;
    return false ;
}

//���֮ǰ��δ���������
void printbefore() {
    /*���ֳ��Ȳ�Ϊ0��˵�������ڽ��дʷ��������ַ�֮ǰ�в�ͬ���͵Ķ���û�����
    ������Щ�϶����ڵ�ǰ�ַ�֮ǰ������Ӧ���������*/
    if(identifierLength != 0) {         //֮ǰ��һ����ʶ�����߱�����
        char temp[50] ;
        strcpy(temp, identifier) ;
        strlwr(temp) ;          //��ֹ���ִ�Сд�������д�д������Сд
        if(isNumber(identifier[0])) {             //�Ƿ���ʶ�����󣬵�һλ������
            sprintf(errors[errorSum], "��%d��:   �Ƿ���ʶ��%s", line, identifier);
            errorSum++ ;
        }
        else if(binarySearch(temp, 0, keywordNum-1)) {  //������
            printf("%s      %s\n", keyword[keywordPlace], identifier) ;
            fprintf(outputFile, "%s      %s\n", keyword[keywordPlace], identifier) ;//д������ļ���
        }
        else {                                  //��ʶ��
            printf("ID      %s\n", identifier) ;
            fprintf(outputFile, "ID      %s\n", identifier) ;
        }
        memset(identifier, 0, sizeof(identifier)) ; //����ַ�������
        identifierLength = 0 ;                      //����ַ�������
    }
    if(numbersLength != 0) {               //֮ǰ��һ������
        int num = 0 ;
        for(int i=0; i<numbersLength; i++) {    //���ַ�����Ϊ����
            num *= 10 ;
            num += (numbers[i] - '0') ;
        }
        printf("NUM     %d\n", num) ;
        fprintf(outputFile, "NUM     %d\n", num) ;
        memset(numbers, 0, sizeof(numbers)) ;   //����ַ�������
        numbersLength = 0 ;
    }
    if(characterNum != 0) {            //֮ǰ�ǵ��ַ���˫�ַ�
        if(characterNum > 2) {      //û�д��������ַ�����ϣ����ڴ���
            sprintf(errors[errorSum], "��%d��:   �Ƿ���ʶ��%s", line, character);
            errorSum++ ;
        }
        if(characterNum == 1) {         //���ַ�
            printf("%c     %c\n", character[0], character[0]) ;
            fprintf(outputFile, "%c     %c\n", character[0], character[0]) ;
        }
        if(characterNum == 2) {    //˫�ַ�
            if(isDoubleword()) {    //����Ҫ�ж��������������ַ��ǲ���˫�ַ�
                printf("%s     %s\n", character, character) ;
                fprintf(outputFile, "%s     %s\n", character, character) ;
            }
        }
        memset(character, 0, sizeof(character)) ;   //�����ǵ��ַ�����˫�ַ���Ҫ���
        characterNum = 0 ;
    }
    if(noteNum != 0) {            //֮ǰ�ǵ��ַ���ע��
        if(noteNum == 1) {         //���ַ�
            printf("%c     %c\n", note[0], note[0]) ;
            fprintf(outputFile, "%c     %c\n", note[0], note[0]) ;
            memset(note, 0, sizeof(note)) ;   //�����ǵ��ַ�����ע�Ͷ�Ҫ���
            noteNum = 0 ;
        }
        else if(noteNum == 2) {    //ע��
            if(!strcmp(note, "/*"))     //����ע�Ϳ�ʼ
                startFlag = true ;
            else {
                printf("%c     %c\n", note[0], note[0]) ;
                printf("%c     %c\n", note[1], note[1]) ;
                fprintf(outputFile, "%c     %c\n%c     %c\n", note[0], note[0], note[1], note[1]) ;
            }
            memset(note, 0, sizeof(note)) ;
            noteNum = 0 ;
        }
    }
}
//�ʷ�����
void wordanalysis(char temp) {
    if(isNull(temp)) {      //�������־ͼ�������һ���ַ�
        printbefore() ;     //�������ǰ�ж���û�д�����Ҫ���в���
        prior = temp ;      //���뵽�˴��Ͳ���ִ�к���������ˣ��˴�ҲҪ������һ���ַ�
        return ;            //�˳��ú���
    }
    if(isLetter(temp) || (isLetter(prior)&&isNumber(temp))) {    //�жϵ�ǰ�ַ��ǲ�����ĸ
        //��ĸ�����ֵ����Ҳ�����Ǳ�ʶ��
        if(isNumber(prior) && identifierLength==0 ) {   //�������ּ���ĸ�ǷǷ��ı�ʶ��
            //�����ʶ�������л�û���κ��ַ��������ڵ�һ����ĸ֮ǰ���������������ǷǷ���ʶ��
            for(int i=0; i<numbersLength; i++) {    //�����������е�����ȫ��ת�Ƶ���ʶ��������
                identifier[identifierLength] = numbers[i] ;
                identifierLength++ ;
            }
            memset(numbers, 0, sizeof(numbers)) ;   //��ճ�������
            numbersLength = 0 ;
        }
        if(!isLetter(prior) && identifierLength==0)//��ʶ������Ϊ0��֤��֮ǰ�����ֲ������ڱ�ʶ����
            printbefore() ;
        if(!startFlag) {    //������֮ǰ��if���жϳ�����ע���˾Ͳ����ټ�����
            identifier[identifierLength] = temp ;   //�Ǿͽ�����뵽��ǰ�ı�ʶ��������
            identifierLength++ ;
        }
    }
    else if(isNumber(temp)) {   //�жϵ�ǰ�ַ��ǲ�������
        if(!isNumber(prior))    //���ǰ���ַ����Ͳ�ͬ���п���Ҫ���һЩ����
            printbefore() ;
        if(!startFlag) {
            numbers[numbersLength] = temp ; //�����־ͼ��뵽����������
            numbersLength++ ;
        }
    }
    else if(isPureSingleword(temp)) {           //�жϵ�ǰ�ַ��ǲ��Ǵ����ַ�
        if(!isPureSingleword(prior))
            printbefore();
        if(!startFlag) {
            printf("%c     %c\n", temp, temp) ;     //�Ǵ����ַ���ֱ�����
            fprintf(outputFile, "%c     %c\n", temp, temp) ;
        }
    }
    else if(!(temp=='*'&&prior=='/') && isSingleword(temp) ) {    //�жϵ�ǰ�ַ��ǲ��ǵ��ַ�
        //Ҫע�⿼��ע�͵����
        if(!isSingleword(prior))
            printbefore() ;
        if(!startFlag) {
            character[characterNum] = temp ;
            characterNum++ ;
        }
    }
    else if(isDiagonal(temp)) {          //�жϵ�ǰ�ַ��ǲ���/
        if(!isDiagonal(prior))
            printbefore() ;
        if(!startFlag) {
            note[noteNum] = temp ;
            noteNum++ ;
            if(!strcmp(note, "/*")) {    //����ע�Ϳ�ʼ
                startFlag = true ;
                memset(note, 0, sizeof(note)) ;
            	noteNum = 0 ;
            }
        }
    }
    else {          //�����жϷǷ��ַ�
        printbefore() ;
        if(!startFlag) {
            sprintf(errors[errorSum], "��%d��:   �Ƿ��ַ�%c", line, temp);
            errorSum++ ;
        }
    }
    prior = temp ;              //�����굱ǰ�ַ���ͽ�����Ϊ��һ���ַ�
}
int main() {
    //��ʼ�����õ���������ļ�
    printf("������ �����ļ���ַ��") ;
    scanf("%s", inputAddress) ;
    if((inputFile=fopen(inputAddress, "r")) == NULL)     //��ȡ�����ļ�
        printf("\nerror: �޷��������ļ�\n\n");
    printf("������ ����ļ���ַ��") ;
    scanf("%s", outputAddress) ;
    if((outputFile=fopen(outputAddress, "w")) == NULL)   //��ȡ����ļ�
        printf("\nerror: �޷��򿪽���ļ�\n\n");

    while(!feof(inputFile)) {   //��ȡ�����ļ�ֱ�����ݽ���
        char current ;          //��ǰ�ַ�
        fscanf(inputFile, "%c", &current) ;    //ÿ�ζ�ȡһ���ַ�
        if(startFlag) {         //��ע���оͲ����дʷ�����
            if(current=='/' && prior=='*') {    //������ע�ͽ�����־ʱ�޸�״̬
                prior = current ;
                startFlag = false ;
            }
            else {
                if(current=='\n') //ע���е�����ҲҪ��������
                    line++ ;
                prior = current ;   //ע����ֻ��Ҫ��¼��һ���ַ���ʲô��Ϊ���ҵ�����ע����׼��
            }
        }
        else                //����ע���о�Ҫ���дʷ�����
            wordanalysis(current) ;
        current = ' ' ;     //ÿ�δ����궼Ҫ��Ϊ���ַ�ֹĩβ�ַ������һ��
    }
    if(startFlag) {       //���ע��û�н������ţ���ע��֮������ݶ�û���ˣ����ܻ����
        //printf("\nerror: ע��û�з��\n\n");
        sprintf(errors[errorSum], "��%d��:   ע��û�з��", line);
        errorSum++ ;
    }
    //����������
    printf("\n\n===========================================") ;
    if(errorSum == 0)
        printf("\n�ʷ������ɹ�\n") ;
    else {
        printf("\n��������:  %d \n", errorSum) ;
        for(int i=0; i<errorSum; i++)
            printf("%s\n", errors[i]) ;
    }
    return 0 ;
}

