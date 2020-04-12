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


int r,n;   //生成数的最大值 和 式子数量 
typedef int Status;

char* oneOperator();
char* creatOperator();
char* threeOperator();
char* twoOperator();
char *creatFormula(int y);
char* creatSnum();
Status Answer_Sq(char formula[],int y);

typedef struct StackNode{    //分数栈结点
	int fm;    //分母
	int fz;    //分子
	struct StackNode *next;
}node1;

typedef struct Stackop {  //运算符栈结点

	int data;            //运算符ASCII值
	struct Stackop *next;
}node2;

typedef struct stack1  { //分数栈

	node1 *top;
	int length;
}StackSq1;

typedef struct stack2  {  //运算符栈

	node2 *top;
	int length;
}StackSq2;



Status InitStack_Sq1(StackSq1 &S){   //初始化 运算数 的栈 

	S.top=NULL;
	S.length=0;
	return OK; 
}

Status InitStack_Sq2(StackSq2 &S){    //初始化 运算符 的栈 

	S.top=NULL;
	S.length=0;
	return OK;
}

Status StackEmpty_Sq(StackSq2 S){  // 对  运算符 判空，若为空则返回TURE，否则返回FALSE 
    if(S.length==0) return OK;
    else return ERROR;
}

Status Push_Sq1(StackSq1 &S,int fenzi,int fenmu){   //分数 进栈 
	node1 *p;
	p=(node1 *)malloc(sizeof (node1));
	p->fm=fenmu;
	p->fz=fenzi;
	p->next=S.top;
	S.top=p;
	S.length++;
	return OK; 
} 

Status Push_Sq2(StackSq2 &S,int e){   //运算符 进栈 
	node2 *p;
	p=(node2 *)malloc(sizeof (node2));
	p->data=e;
	p->next=S.top;
	S.top=p;
	S.length++;
	return OK; 
} 

node1 Pop_Sq1(StackSq1 &S){  //记得类型是 node1 
	node1 A;
	node1 *p=S.top;
	A.fm=p->fm;
	A.fz=p->fz;
	S.top=p->next;
	free(p);
	S.length--;
	return A;
} 

Status Pop_Sq2(StackSq2 &S){   //  运算符栈顶  出栈 
	int e;
	node2 *p=S.top;
	e=p->data;
	S.top=p->next;
	free(p);
	S.length--;
	return e;
} 

Status Get_Top(StackSq2 S){     //取  运算符 栈顶元素 (不出栈) 
	if(S.top==NULL)return ERROR;
	return S.top->data;
}

int Priority(char op)	//判断操作符优先级
{
	switch (op)
	{
		case '(':
			return 4;
		case '/':
			return 3;	
		case '*':
		case '#':    //除号 
			return 2;
		case '+':
		case '-':
			return 1;
		default :
			return 0;
	}
}

int gcd(int x,int y)//辗转相除法 ,两整数的最大公约数 
{
    if(y==0) return x;
    return gcd(y,x%y);
} 


char* oneOperator()  //一个操作符的式子
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

char* twoOperator() //两个操作符得式子
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


char* threeOperator()  //三个操作符得式子
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

char* creatOperator() //生成运算符
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

char* creatSnum()  //生成运算数 
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
		num1 = rand() % (r)+1;    //不要（size+1），保证整数不为  0 
		sprintf(c, "%d", num1);
		strcat(string1, c);
		
	}
	else
	{
		num1 = rand() %(r-1) ;   //最大为 m-2，方便后面算法 
		
		if (num1 != 0)
		{
			sprintf(c, "%d", num1);
			strcat(string1, c);
			strcat(string1, "/");
		}
		while (num2 == 0 || num2 <= num1)
		   {
			  num2 = rand() % r;    //最大为 m-1 
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

char *creatFormula(int y)   //生成式子
{    
 	srand((unsigned)time(NULL) + rand());
//	char op[3];
	char string[MAXSIZE] = {};
	char* posture = string;
	int a = rand() % 3;    //生成的随机数，即运算符个数
	//printf("%d\n", a);

	FILE *fp;
	fp=fopen("test.txt","a");
	int i=0;
	
	char divi[5]={"÷"};  //用于后面存进文件 
	char mult[5]={"×"};
	
	switch (a)
	{
	case 0:strcpy(string, oneOperator()); 		
//			printf("%s\n",posture);   //和文件作比较   
		    break;
	
	case 1:strcpy(string, twoOperator());
//			printf("%s\n",posture);
		    break;
		    
	case 2:strcpy(string, threeOperator());
//			printf("%s\n",posture); 
			break;
			 
	default:break;
	}
	if(Answer_Sq(posture,y)<0)    //计算的时候用  数组 算，打印则要转化一下 
	{
		fclose(fp);
		return mp;   // 因为是 char 型函数，不能直接返回-1 
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

node1 CalculatorSq(node1 a,node1 b,int c){  // 两个数的计算 

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

void Simpli_Fenshu(int z,int m,char strings[]) {        //分数化简（将原始分数化为  真分数、带分数、整数）
	int a,b,c;       
	char h[20]={};
	
	if(z%m==0)
	{
		a=z/m;
		itoa(a,strings,10);      //把 a转化为字符，存在strings[]中 
	// printf("%s\n",strings);   //可以直接在 exe窗口 看答案
	}
	else if(z>m) 
	{
		a=z/m;
		b=z-a*m;
		c=gcd(b,m);    //求新的分子分母的  最大公因数 
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

Status Answer_Sq(char formula[],int y){    //计算答案 ,formula[] 为传进来的式子 
	StackSq1 S_num;  //分数栈 
	StackSq2 S_ope;   //运算符 栈 
	
	int i=0,tmp=0;
	
	node1 A,B,C;   //结点 	   
	int D;        //运算符 
	
	FILE *fp;
	fp=fopen("answer.txt","a");
	if(InitStack_Sq1(S_num)!=OK || InitStack_Sq2(S_ope)!=OK)
	{
		printf("初始化栈失败");
		exit(1); 
	}
	
	while(formula[i]!='\0' || StackEmpty_Sq(S_ope)!=OK)
	{
		if(formula[i]>='0'&&formula[i]<='9')	//判断数字
		{
			tmp=tmp*10+formula[i]-'0';     //后面还是数字，继续 
			i++;
			if(formula[i]>'9' || formula[i]<'0')                 //判断 后一个 是否 字符 
			 {
			 	Push_Sq1(S_num,tmp,1);   //把整数化为 分数 进栈
				tmp=0;  	//清零，用于记录下一个  数  
			 } 
		} 
		
		else   //运算符
		{                //等级高的               						栈顶是左括号',str[i]不是右括号 			   运算符栈为空 
			if((Priority(formula[i]) > Priority(Get_Top(S_ope))) || (Get_Top(S_ope)=='(' && formula[i]!=')') || (StackEmpty_Sq(S_ope)==OK))
			{
				Push_Sq2(S_ope,formula[i]);  //运算符 进栈 
				i++;
				continue;
			}
			
			if(Get_Top(S_ope)=='(' && formula[i]==')') 
			{
				Pop_Sq2(S_ope);   //栈顶 括号 出栈，不计算 
				i++;
				continue; 
			}
//					新的运算符优先级 比  运算符栈顶的 低 					数字空了，运算符还没空				新的运算符是右括号 
			if((Priority(formula[i]) <= Priority(Get_Top(S_ope))) || (formula[i]=='\0'&&StackEmpty_Sq(S_ope)!=OK) || formula[i]==')')
			{
				A=Pop_Sq1(S_num);   //出栈 两个数 
				B=Pop_Sq1(S_num);
				D=Pop_Sq2(S_ope);   //出运算符 
							
//				printf("aaa%d/%d\n",A.fz,A.fm);    //这些注释都是为了在exe窗口显示 计算过程 
//				printf("bbb%d/%d\n",B.fz,B.fm);
//				printf("ccc%c\n",D);
				
				C=CalculatorSq(A,B,D);     //计算中间值 (注意这里！！！)
			
//				printf("daan%d/%d\n",C.fz,C.fm);
				
				Push_Sq1(S_num,C.fz,C.fm);   //中间值为正值，入栈 
				continue;
			} 
		} 
	}
	if(C.fz<0)
	{	
		fclose(fp);
		return -1;   //  负数就返回 -1
	}
	
	char daan[20]={};   //用来存答案 
	Simpli_Fenshu(C.fz,C.fm,daan);  //返回简化后的答案 
	fprintf(fp,"%d.%s\n",y,daan);
	fclose(fp);
	return 1;	
}


void CheckAnswer(char eflie1[],char afile2[]){
	FILE *p1,*p2,*p3;

	p1=fopen("answer.txt","r");
	p2=fopen(afile2,"r");       //传进来的文件名会变 
	p3=fopen("Grade.txt","w");
	
	char answer1[20]={};  //放标准答案的数组 
	char answer2[20]={};  //放新答案文件 fgets出来的答案
	 
	int y=1;       //第一条式子 
	int c=0,w=0;   //用于计算对和错的总题数 
	int correct_d[10000]={};   //用于储存  对的和错的题号
	int wrong_d[10000]={};
	
	while(fgets(answer1,20,p1)!=NULL && fgets(answer2,20,p2)!=NULL)
	{	
		//不要fgets  10个字符，我吃柠檬 
	
//		printf("%s",answer1);      
//		printf("222%s",answer2);
		
		if(strcmp(answer1,answer2)==0)  //比较前n个字节的大小 
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
//	printf("要生成还是对比答案：\n") 
//	char* line;
//	int y=1;  //第一道题 
//	
//	printf("请输入想要生成的式子数-n:");
//	scanf("%d",&n);
//	printf("请输入生成数的最大值-r:");
//	scanf("%d",&m); 
//	srand(time(0) + rand());
//	while(n>0)
//	{
//		line=creatFormula(y);	
//		if(atoi(line)<0)continue;	 
//		y++;
//		n--;	
//	}	
//	printf("输入题目文件：");
//	char efile[20]={};
//	scanf("%s",efile);   // "test.txt"
//	printf("输入要判断的答案文件："); 
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
	if(argc<3)   //参数没有 4个 
	{
		printf("你输错了或 去cmd运行！！！\n");
		return 0;
	}
	if(strcmp(argv[1],"-n")==0 && strcmp(argv[3],"-r")==0)
	{
		n=atoi(argv[2]); //字符串变为整数 
		r=atoi(argv[4]);
		
		srand((unsigned)time(NULL)+rand());   //加个种子，随机数不同 
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
