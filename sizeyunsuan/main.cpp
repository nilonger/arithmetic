#include<stdio.h>
#include<stdlib.h>
#include <time.h>
#include<string.h>
#include<io.h>
#include<math.h>
#define MINSIZE 256
#define MAXSIZE 1024
#define OK 1
#define ERROR 0


int r,n;   //�����������ֵ �� ʽ������ 
typedef int Status;

char* oneOperator();
char* creatOperator();
char* threeOperator();
char* twoOperator();
char *creatFormula(int y);
char* creatSnum();
Status Answer_Sq(char formula[],int y);

typedef struct StackNode{    //����ջ���
	int fm;    //��ĸ
	int fz;    //����
	struct StackNode *next;
}node1;

typedef struct Stackop {  //�����ջ���

	int data;            //�����ASCIIֵ
	struct Stackop *next;
}node2;

typedef struct stack1  { //����ջ

	node1 *top;
	int length;
}StackSq1;

typedef struct stack2  {  //�����ջ

	node2 *top;
	int length;
}StackSq2;



Status InitStack_Sq1(StackSq1 &S){   //��ʼ�� ������ ��ջ 

	S.top=NULL;
	S.length=0;
	return OK; 
}

Status InitStack_Sq2(StackSq2 &S){    //��ʼ�� ����� ��ջ 

	S.top=NULL;
	S.length=0;
	return OK;
}

Status StackEmpty_Sq(StackSq2 S){  // ��  ����� �пգ���Ϊ���򷵻�TURE�����򷵻�FALSE 
    if(S.length==0) return OK;
    else return ERROR;
}

Status Push_Sq1(StackSq1 &S,int fenzi,int fenmu){   //���� ��ջ 
	node1 *p;
	p=(node1 *)malloc(sizeof (node1));
	p->fm=fenmu;
	p->fz=fenzi;
	p->next=S.top;
	S.top=p;
	S.length++;
	return OK; 
} 

Status Push_Sq2(StackSq2 &S,int e){   //����� ��ջ 
	node2 *p;
	p=(node2 *)malloc(sizeof (node2));
	p->data=e;
	p->next=S.top;
	S.top=p;
	S.length++;
	return OK; 
} 

node1 Pop_Sq1(StackSq1 &S){  //�ǵ������� node1 
	node1 A;
	node1 *p=S.top;
	A.fm=p->fm;
	A.fz=p->fz;
	S.top=p->next;
	free(p);
	S.length--;
	return A;
} 

Status Pop_Sq2(StackSq2 &S){   //  �����ջ��  ��ջ 
	int e;
	node2 *p=S.top;
	e=p->data;
	S.top=p->next;
	free(p);
	S.length--;
	return e;
} 

Status Get_Top(StackSq2 S){     //ȡ  ����� ջ��Ԫ�� (����ջ) 
	if(S.top==NULL)return ERROR;
	return S.top->data;
}

int Priority(char op)	//�жϲ��������ȼ�
{
	switch (op)
	{
		case '(':
			return 4;
		case '/':
			return 3;	
		case '*':
		case '#':    //���� 
			return 2;
		case '+':
		case '-':
			return 1;
		default :
			return 0;
	}
}

int gcd(int x,int y)//շת����� ,�����������Լ�� 
{
    if(y==0) return x;
    return gcd(y,x%y);
} 


char* oneOperator()  //һ����������ʽ��
{
	srand((unsigned)time(NULL) + rand());
	char string[MINSIZE] = {};
	char* posture = string;
	char c[MINSIZE] = {};		
	strcpy(c, creatSnum());
	strcat(string, c);
    
	strcpy(c,creatOperator());
	strcat(string, c);
	//printf("%s\n", string);

	strcpy(c, creatSnum());
	strcat(string, c);
	//printf("%s\n", string);
	return posture;
}

char* twoOperator() //������������ʽ��
{
	srand((unsigned)time(NULL) + rand());
	int flag = 0;
	int tag=0;
	char string[128] = {};
	char* posture = string;
	char c[MAXSIZE] = {};

	flag = rand() % 2;
	if (flag == 0)
	{
		strcpy(c, "(");
		strcat(string, c);
		tag = 1;
	}

	strcpy(c, creatSnum());
	strcat(string, c);

	strcpy(c,creatOperator());
	strcat(string, c);

	strcpy(c, creatSnum());
	strcat(string, c);

	flag = rand() % 2;
	if (flag == 0)
	{
		if (tag == 1)
		{
			strcpy(c, ")");
			strcat(string, c);
		}
		tag = 0;
	}

	strcpy(c,creatOperator());
	strcat(string, c);

	strcpy(c, creatSnum());
	strcat(string, c);

	if (tag == 1)
	{
		strcpy(c, ")");
		strcat(string, c);
	}

	//printf("%s\n", string);
	return posture;
}


char* threeOperator()  //������������ʽ��
{
	srand((unsigned)time(NULL) + rand());
	char string[128] = {};
	char* posture = string;
	char c[MAXSIZE] = {};

	strcpy(c, creatSnum());
	strcat(string, c);

	strcpy(c,creatOperator());
	strcat(string, c);

	strcpy(c, creatSnum());
	strcat(string, c);

	strcpy(c,creatOperator());
	strcat(string, c);

	strcpy(c, creatSnum());
	strcat(string, c);

	strcpy(c,creatOperator());
	strcat(string, c);

	strcpy(c, creatSnum());
	strcat(string, c);



	//("%s\n", string);
	return posture;
}

char* creatOperator() //���������
{
	srand((unsigned)time(NULL) + rand());
	char* c = new char[2];
	int a = rand() % 4;
	//int a = 1;
	switch (a)
	{
	case 1:  strcpy(c, "+");  break;
	case 2: strcpy(c, "-"); break;
	case 3: strcpy(c, "*"); break;
	case 0:  strcpy(c, "#"); break;
	default:
		break;
	}
	return c;
}

char* creatSnum()  //���������� 
{
	srand((unsigned)time(NULL) + rand());
	char* string = NULL;
	char string1[MAXSIZE] = {};
	string = string1;
	char c[MAXSIZE] = {};
	int tag = rand() % 2;
	int num1=0,num2=0;
	if (tag == 0)
	{
		num1 = rand() % (r)+1;    //��Ҫ��size+1������֤������Ϊ  0 
		sprintf(c, "%d", num1);
		strcat(string1, c);
		
	}
	else
	{
		num1 = rand() %(r-1) ;   //���Ϊ m-2����������㷨 
		
		if (num1 != 0)
		{
			sprintf(c, "%d", num1);
			strcat(string1, c);
			strcat(string1, "/");
		}
		while (num2 == 0 || num2 <= num1)
		   {
			  num2 = rand() % r;    //���Ϊ m-1 
		   }
		sprintf(c, "%d", num2);
		strcat(string1, c);

	}
	return string;
}


char pan[5]={"-1"};
char *mp=pan;
char duan[5]={"1"};
char *np=duan;

char *creatFormula(int y)   //����ʽ��
{    
 	srand((unsigned)time(NULL) + rand());
//	char op[3];
	char string[MAXSIZE] = {};
	char* posture = string;
	int a = rand() % 3;    //���ɵ�������������������
	//printf("%d\n", a);

	FILE *fp;
	fp=fopen("test.txt","a");
	int i=0;
	
	char divi[5]={"��"};  //���ں������ļ� 
	char mult[5]={"��"};
	
	switch (a)
	{
	case 0:strcpy(string, oneOperator()); 		
//			printf("%s\n",posture);   //���ļ����Ƚ�   
		    break;
	
	case 1:strcpy(string, twoOperator());
//			printf("%s\n",posture);
		    break;
		    
	case 2:strcpy(string, threeOperator());
//			printf("%s\n",posture); 
			break;
			 
	default:break;
	}
	if(Answer_Sq(posture,y)<0)    //�����ʱ����  ���� �㣬��ӡ��Ҫת��һ�� 
	{
		fclose(fp);
		return mp;   // ��Ϊ�� char �ͺ���������ֱ�ӷ���-1 
	}
	else {
//		fprintf(fp,"%d.%s = \n",y,posture);
		fprintf(fp,"%d.",y);
		while(string[i]!='\0')
			{
				if(string[i]=='#') 
				{
					fprintf(fp,"%s",divi);
					i++;
					continue;
				}
				else if(string[i]=='*')
				{
					fprintf(fp,"%s",mult);
					i++;
					continue;
				}
				fprintf(fp,"%c",string[i]);
				i++;
			}
			fprintf(fp,"=%c",'\n');
		fclose(fp);
		return np;
	}
//	fclose(fp);
//	return posture;
	 
}

node1 CalculatorSq(node1 a,node1 b,int c){  // �������ļ��� 

	node1 d;
	switch(c)
	{
		case'+':
			d.fz=b.fz*a.fm + b.fm*a.fz;
			d.fm=a.fm*b.fm;
			break;
		case'-':
			d.fz=b.fz*a.fm - b.fm*a.fz;
			d.fm=a.fm*b.fm;
			break;
		case'*':
			d.fz=b.fz*a.fz;
			d.fm=a.fm*b.fm;
			break;
		case'#':
		case'/':
		 	d.fz=b.fz*a.fm;
			d.fm=b.fm*a.fz;
			break;

		default:break;
	}
	return d; 
}

void Simpli_Fenshu(int z,int m,char strings[]) {        //�������򣨽�ԭʼ������Ϊ  ���������������������
	int a,b,c;       
	char h[20]={};
	
	if(z%m==0)
	{
		a=z/m;
		itoa(a,strings,10);      //�� aת��Ϊ�ַ�������strings[]�� 
	// printf("%s\n",strings);   //����ֱ���� exe���� ����
	}
	else if(z>m) 
	{
		a=z/m;
		b=z-a*m;
		c=gcd(b,m);    //���µķ��ӷ�ĸ��  ������� 
		itoa(a,strings,10);
		strcat(strings,"'");
		sprintf(h,"%d",b/c);
		strcat(strings,h);
		strcat(strings,"/");
		sprintf(h,"%d",m/c);
		strcat(strings,h);
	//	printf("%s\n",strings);
	}
	else if(z<m)
	{
		c=gcd(z,m);
		a=z/c;
		b=m/c;
		itoa(a,strings,10);
		strcat(strings,"/");
		itoa(b,h,10);
		strcat(strings,h);
	//	printf("%s\n",strings);
	}
}

Status Answer_Sq(char formula[],int y){    //����� ,formula[] Ϊ��������ʽ�� 
	StackSq1 S_num;  //����ջ 
	StackSq2 S_ope;   //����� ջ 
	
	int i=0,tmp=0;
	
	node1 A,B,C;   //��� 	   
	int D;        //����� 
	
	FILE *fp;
	fp=fopen("answer.txt","a");
	if(InitStack_Sq1(S_num)!=OK || InitStack_Sq2(S_ope)!=OK)
	{
		printf("��ʼ��ջʧ��");
		exit(1); 
	}
	
	while(formula[i]!='\0' || StackEmpty_Sq(S_ope)!=OK)
	{
		if(formula[i]>='0'&&formula[i]<='9')	//�ж�����
		{
			tmp=tmp*10+formula[i]-'0';     //���滹�����֣����� 
			i++;
			if(formula[i]>'9' || formula[i]<'0')                 //�ж� ��һ�� �Ƿ� �ַ� 
			 {
			 	Push_Sq1(S_num,tmp,1);   //��������Ϊ ���� ��ջ
				tmp=0;  	//���㣬���ڼ�¼��һ��  ��  
			 } 
		} 
		
		else   //�����
		{                //�ȼ��ߵ�               						ջ����������',str[i]���������� 			   �����ջΪ�� 
			if((Priority(formula[i]) > Priority(Get_Top(S_ope))) || (Get_Top(S_ope)=='(' && formula[i]!=')') || (StackEmpty_Sq(S_ope)==OK))
			{
				Push_Sq2(S_ope,formula[i]);  //����� ��ջ 
				i++;
				continue;
			}
			
			if(Get_Top(S_ope)=='(' && formula[i]==')') 
			{
				Pop_Sq2(S_ope);   //ջ�� ���� ��ջ�������� 
				i++;
				continue; 
			}
//					�µ���������ȼ� ��  �����ջ���� �� 					���ֿ��ˣ��������û��				�µ�������������� 
			if((Priority(formula[i]) <= Priority(Get_Top(S_ope))) || (formula[i]=='\0'&&StackEmpty_Sq(S_ope)!=OK) || formula[i]==')')
			{
				A=Pop_Sq1(S_num);   //��ջ ������ 
				B=Pop_Sq1(S_num);
				D=Pop_Sq2(S_ope);   //������� 
							
//				printf("aaa%d/%d\n",A.fz,A.fm);    //��Щע�Ͷ���Ϊ����exe������ʾ ������� 
//				printf("bbb%d/%d\n",B.fz,B.fm);
//				printf("ccc%c\n",D);
				
				C=CalculatorSq(A,B,D);     //�����м�ֵ (ע���������)
			
//				printf("daan%d/%d\n",C.fz,C.fm);
				
				Push_Sq1(S_num,C.fz,C.fm);   //�м�ֵΪ��ֵ����ջ 
				continue;
			} 
		} 
	}
	if(C.fz<0)
	{	
		fclose(fp);
		return -1;   //  �����ͷ��� -1
	}
	
	char daan[20]={};   //������� 
	Simpli_Fenshu(C.fz,C.fm,daan);  //���ؼ򻯺�Ĵ� 
	fprintf(fp,"%d.%s\n",y,daan);
	fclose(fp);
	return 1;	
}


void CheckAnswer(char eflie1[],char afile2[]){
	FILE *p1,*p2,*p3;

	p1=fopen("answer.txt","r");
	p2=fopen(afile2,"r");       //���������ļ������ 
	p3=fopen("Grade.txt","w");
	
	char answer1[20]={};  //�ű�׼�𰸵����� 
	char answer2[20]={};  //���´��ļ� fgets�����Ĵ�
	 
	int y=1;       //��һ��ʽ�� 
	int c=0,w=0;   //���ڼ���Ժʹ�������� 
	int correct_d[10000]={};   //���ڴ���  �Եĺʹ�����
	int wrong_d[10000]={};
	
	while(fgets(answer1,20,p1)!=NULL && fgets(answer2,20,p2)!=NULL)
	{	
		//��Ҫfgets  10���ַ����ҳ����� 
	
//		printf("%s",answer1);      
//		printf("222%s",answer2);
		
		if(strcmp(answer1,answer2)==0)  //�Ƚ�ǰn���ֽڵĴ�С 
		{
			correct_d[c++]=y;
			y++; 
		}
		else if(strcmp(answer1,answer2)!=0)
		{
			wrong_d[w++]=y;
			y++;
		}
	}
 
	fprintf(p3,"Correct: %d (",c);
	for(int i=0;i<c;i++)
	{
		fprintf(p3,"%d",correct_d[i]);
		if(i!=c-1) fprintf(p3,",");
	}
	fprintf(p3,")\n");
	 
	fprintf(p3,"Wrong: %d (",w);
	for(int i=0;i<w;i++)
	{
		fprintf(p3,"%d",wrong_d[i]);
		if(i!=w-1) fprintf(p3,",");
	}
	fprintf(p3,")");
	fclose(p1);
	fclose(p2);
	fclose(p3);		
} 

//int main(){
//	
//	printf("Ҫ���ɻ��ǶԱȴ𰸣�\n") 
//	char* line;
//	int y=1;  //��һ���� 
//	
//	printf("��������Ҫ���ɵ�ʽ����-n:");
//	scanf("%d",&n);
//	printf("�����������������ֵ-r:");
//	scanf("%d",&m); 
//	srand(time(0) + rand());
//	while(n>0)
//	{
//		line=creatFormula(y);	
//		if(atoi(line)<0)continue;	 
//		y++;
//		n--;	
//	}	
//	printf("������Ŀ�ļ���");
//	char efile[20]={};
//	scanf("%s",efile);   // "test.txt"
//	printf("����Ҫ�жϵĴ��ļ���"); 
//	char afile[20]={};
//	scanf("%s",afile);   //"newanswer.txt"
//	
//	CheckAnswer(efile,afile); 
//	
//	return 0;	
//} 

int main(int argc,char *argv[]){
	char *line;
	int y=1;
	if(argc<3)   //����û�� 4�� 
	{
		printf("������˻� ȥcmd���У�����\n");
		return 0;
	}
	if(strcmp(argv[1],"-n")==0 && strcmp(argv[3],"-r")==0)
	{
		n=atoi(argv[2]); //�ַ�����Ϊ���� 
		r=atoi(argv[4]);
		
		srand((unsigned)time(NULL)+rand());   //�Ӹ����ӣ��������ͬ 
		while(n>0)
		{   
			
			line=creatFormula(y);	
			if(atoi(line)<0)continue;	 
			y++;
			n--;	
		}	
	} 
	else if(!strcmp(argv[1],"-e") && !strcmp(argv[3],"-a"))
	{
		CheckAnswer(argv[2],argv[4]); 	
	}
	return 0;
}
