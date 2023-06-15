#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include<locale.h>
 
#define STRNAMELEN 12 //用户账号结构体长度
#define STRPASSLEN 20 //用户密码结构体长度
#define UARRLEN 3 //用户数组结构体初始内存大小
 
#define BARRLEN 5 //图书数组结构体初始内存大小
#define BOOKNAME 30 //图书名字最大数
#define BOOKAUTOR 30 //图书作者最大数
#define BOOKPRESS 10 //图书出版社最大数
 
#define STRCHLEN 20 //pl结构体ch数组长度
#define STRFHLEN 5  //pl结构体fh数组长度
#define BLSTRLEN 13  //遍历结构体数组的下标
 
// 用户结构体
typedef struct username {
	int uid; //用户id
	char uname[STRNAMELEN]; //用户名
	char upass[STRNAMELEN]; //用户密码
	int usign; //用户标记 0代表普通用户  1代表管理员
}user;
 
//用户结构体数组
typedef struct userArray {
	user* uArr; //用户结构体数组
	int uSub; //用户结构体数组当前下标
	int uMaxLen;  //用户结构体数组当前最大容量
}userArr;
 
//图书结构体
typedef struct books {
	int id; //图书编号
	char title[BOOKNAME]; //图书名字
	char autor[BOOKAUTOR]; //图书作者
	char press[BOOKPRESS]; //出版社
	int much; //数量
}book;
 
//图书结构体数组
typedef struct booksArray {
	book* bArr; //图书结构体指针
	int bSub; //图书结构体数组当前下标
	int bMaxLen; //图书结构体数组当前最大容量
}bookArr;
 
//借阅信息结构体
typedef struct bookRecord {
	char reName[STRNAMELEN]; //借阅人姓名
	char reBook[BOOKNAME]; //书籍
	char re[5]; //是否归还
}record;
 
typedef struct strRecord {
	record* reArr;
	int reSub;
	int reMaxLen;
}reStr;
 
//遍历结构体
typedef struct pl {
	char ch[STRCHLEN];
	char fh[STRFHLEN];
}pl;
 
typedef struct plArr {
	pl o[BLSTRLEN]; //遍历结构体数组
	int i;	 //全局变量-下标
}pArr;
 
//管理员选择函数
void adminChoice(userArr* p, pArr* po, bookArr* pb);
//删除图书
void delBook(bookArr* p);
//导出图书
void expBook(bookArr* p);
//遍历图书
void ergBook(bookArr* p);
//查找图书
void lookupBook(bookArr* p);
//修改图书
void modifyBook(bookArr* p);
//添加图书
void regBook(bookArr* p);
//写入图书
void writeBook(bookArr* p);
//删除账号
void adminDel(userArr* p);
//导出账号
void adminExp(userArr* p);
//遍历用户
void adminErg(userArr* p);
//查找账号
void adminLookup(userArr* p);
//修改账号
void adminModify(userArr* p);
//管理登录页面
void adSig(userArr* p, bookArr* pb);
//向上移动
void  moveup(pArr* po);
//向下移动
void  movedown(pArr* po);
//遍历打印结构体数组
void see(pArr* po);
//初始化遍历结构体数组
void begin(pArr* po);
//登录用户
void sign(userArr* p, bookArr* pb);
//图书动态内存扩展
void bExpMemory(bookArr* p);
//读取图书信息
void readBook(bookArr* p);
//book申请动态
void bAppMemory(bookArr* p);
//注册用户
void regUser(userArr* p);
//写入用户信息
void writeUser(userArr* p);
//读取用户信息
void readUser(userArr* p);
//动态内存申请扩展
void uExpMemory(userArr* p);
//user申请动态内存
void uAppMemory(userArr* p);
//登录页面
void login(userArr* p, bookArr* pb);
//加载页面
void load();
//初始化打印数组
void memBegin(pArr* po);
//遍历打印数组
void memSee(pArr* po);
//向下移动
void  memMovedown(pArr* po);
//向上移动
void  memMoveup(pArr* po);
//遍历打印数组
void memSee(pArr* po);
//会员选择函数
void memChoice(userArr* p, pArr* po, bookArr* pb);
//借阅图书
void borBook(userArr* p, bookArr* pb, reStr* pr);
//初始化借阅数组
void rAppMemory(reStr* pr);
//扩展
void reExpMemory(reStr* pr);
//读取借阅记录
void readRe(reStr* pr);
//写入借阅记录
void writeRe(reStr* p);
//归还图书
void returnBook(userArr* p, bookArr* pb, reStr* pr);
//查看借阅记录
void bookErg(userArr* p, bookArr* pb, reStr* pr);
//修改个人信息
void userModify(userArr* p);
 
char tempAdmin[20]; //存放已登录的账号
 
int main() {
	userArr a; // 用户结构体数组
	bookArr c; //图书结构体数组
	uAppMemory(&a); //用户申请动态内存
	readUser(&a); //读取用户数据
	bAppMemory(&c);//book申请动态内存
	readBook(&c); //读取图书信息
	load(); //加载页面
	login(&a, &c); //首页面
	return 0;
}
//修改个人信息
void userModify(userArr* p) {
	int i = 0;
	char pass[20];
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(p->uArr[i].uname, tempAdmin) == 0) {
			printf("请输入想修改后的密码>");
			scanf("%s", pass);
			strcpy(p->uArr[i].upass, pass);
			writeUser(p);
			printf("修改成功\n");
			break;
		}
	}
}
//查看借阅记录
void bookErg(userArr* p, bookArr* pb, reStr* pr) {
	int i = 0;
	for (i = 0; i < pr->reSub; ++i) {
		if (strcmp(pr->reArr[i].reName, tempAdmin) == 0) {
			printf("借阅书籍:%s 是否归还:%s\n", pr->reArr[i].reBook, pr->reArr[i].re);
		}
	}
}
//归还图书
void returnBook(userArr* p, bookArr* pb, reStr* pr) {
	int i = 0;
	char bookName[30];
	system("cls");
	printf("请输入要归还的书名>");
	scanf("%s", bookName);
	for (i = 0; i < pr->reSub; ++i) {
		if (strcmp(tempAdmin, pr->reArr[i].reName) == 0) { //判断借阅人的名字是否存在
 
			if (strcmp(bookName, pr->reArr[i].reBook) == 0) { //判断是否存在借阅此书
				strcpy(pr->reArr[i].re, "是");
				break;
			}
		}
	}
	for (i = 0; i < pb->bSub; ++i) {
		if (strcmp(pb->bArr[i].title, bookName) == 0) {
			pb->bArr[i].much++;
			writeBook(pb);
			break;
		}
	}
	if (i == p->uSub) {
		printf("你没有借过此书\n");
	}
	else {
		printf("归还成功!\n");
	}
 
}
//写入借阅记录
void writeRe(reStr* pr) {
	int i = 0;
	FILE* fp = fopen("D:\\record.txt", "wt");
	for (i = 0; i < pr->reSub; ++i) {
		fprintf(fp, "用户:%s 书名:%s 是否归还:%s\n", pr->reArr[i].reName, pr->reArr[i].reBook, pr->reArr[i].re);
	}
	fclose(fp);
	fp = NULL;
}
//读取借阅记录
void readRe(reStr* pr) {
	FILE* fp = fopen("D:\\record.txt", "rt");
	while (fscanf(fp, "用户:%s 书名:%s 是否归还:%s\n", pr->reArr[pr->reSub].reName, pr->reArr[pr->reSub].reBook, pr->reArr[pr->reSub].re) != EOF) {
		pr->reSub++;
		reExpMemory(pr);
	}
	fclose(fp);
	fp = NULL;
}
//扩展
void reExpMemory(reStr* pr) {
	if (pr->reSub == pr->reMaxLen) {
		record* Q = realloc(pr->reArr, (pr->reMaxLen + 2) * sizeof(record));
		if (Q == NULL) {
			printf("程序出错\n");
			system("pause");
			exit(0);
		}
		else {
			pr->reArr = Q;
			pr->reMaxLen += 2;
		}
	}
}
//初始化借阅数组
void rAppMemory(reStr* pr) {
	//使用malloc函数进行申请
	record* Q = (record*)malloc(UARRLEN * sizeof(record));
	if (Q == NULL) {
		printf("程序出错，请重新运行\n");
		exit(0);
	}
	else {
		pr->reArr = Q;
		//使用memset函数进行初始化
		memset(pr->reArr, 0, sizeof(pr->reArr));
		pr->reSub = 0;
		pr->reMaxLen = UARRLEN;
	}
}
//借阅图书
void borBook(userArr* p, bookArr* pb, reStr* pr) {
	char bookName[30];
	int i = 0;
	system("cls");
	ergBook(pb);
	printf("请输入你要借阅的图书>");
	scanf("%s", bookName);
	for (i = 0; i < pb->bSub; ++i) {
		if (strcmp(bookName, pb->bArr[i].title) == 0) { //判断书本是否存在
			if (pb->bArr[i].much != 0) { //判断是否有存货
				strcpy(pr->reArr[pr->reSub].reName, tempAdmin); //将当前登录账号复制到借阅人信息中
				strcpy(pr->reArr[pr->reSub].reBook, bookName); //将借阅书籍名复制到被借阅书中
				strcpy(pr->reArr[pr->reSub].re, "否"); //写入否
				pr->reSub++; //下标自增
				reExpMemory(pr);  //判断数组内存是否满
				pb->bArr[i].much--;
				printf("借阅成功");
				break;
			}
			else {
				printf("抱歉,该书籍已空!");
				break;
			}
		}
	}
	if (i == pb->bSub) {
		printf("抱歉暂时没有该书,可联系管理员进行添加!");
	}
	writeBook(pb);
}
//用户选择函数
void memChoice(userArr* p, pArr* po, bookArr* pb) {
	reStr z;
	rAppMemory(&z);
	readRe(&z);
	switch (po->i) {
	case 0:
		borBook(p, pb, &z);
		break;
	case 1:
		returnBook(p, pb, &z);
		break;
	case 2:
		bookErg(p, pb, &z);
		break;
	case 3:
		userModify(p);
		break;
	case 4:
		printf("退出成功\n");
		system("pause");
		exit(0);
		break;
	}
	writeRe(&z);
}
//普通用户登录
void memSig(userArr* p, bookArr* pb) {
	pArr pm;
	pm.i = 0;
	memBegin(&pm);
 
	while (1)
	{
		memSee(&pm);
		switch (getch())
		{
		case 72:
			memMoveup(&pm);
			memSee(&pm);
			break;
		case 80:
			memMovedown(&pm);
			memSee(&pm);
			break;
		case 13:
			memChoice(p, &pm, pb);
			system("pause");
			system("cls");
			memSee(&pm);
			break;
		}
	}
}
//向上移动
void  memMoveup(pArr* po) {
	if (po->i <= 6 && po->i > 0)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[--(po->i)].fh, "<--");
 
	}
}
//向下移动
void  memMovedown(pArr* po) {
	if (po->i >= 0 && po->i < 4)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[++(po->i)].fh, "<--");
	}
}
//遍历打印数组
void memSee(pArr* po) {
	int j;
	system("cls");
	for (j = 0; j < 5; j++)
	{
		printf("\t\t\t\t%s%s\n", po->o[j].ch, po->o[j].fh);
	}
}
//初始化打印数组
void memBegin(pArr* po) {
	int i = 0;
	strcpy(po->o[0].ch, "借阅图书");
	strcpy(po->o[1].ch, "归还图书");
	strcpy(po->o[2].ch, "借阅记录");
	strcpy(po->o[3].ch, "修改信息");
	strcpy(po->o[4].ch, "退出系统");
	strcpy(po->o[0].fh, "<--"); //箭头
	for (i = 1; i < 5; ++i) {
		strcpy(po->o[i].fh, " "); //箭头
	}
}
//管理员选择函数
void adminChoice(userArr* p, pArr* po, bookArr* pb) {
	switch (po->i) {
	case 0:
		regUser(p);
		break;
	case 1:
		adminModify(p);
		break;
	case 2:
		adminLookup(p);
		break;
	case 3:
		adminErg(p);
		break;
	case 4:
		adminExp(p);
		break;
	case 5:
		adminDel(p);
		break;
	case 6:
		regBook(pb);
		break;
	case 7:
		modifyBook(pb);
		break;
	case 8:
		lookupBook(pb);
		break;
	case 9:
		ergBook(pb);
		break;
	case 10:
		expBook(pb);
		break;
	case 11:
		delBook(pb);
		break;
	case 12:exit(0); break;
	}
}
//删除图书
void delBook(bookArr* p) {
	char b1[30];
	int i = 0;
	system("cls");
	printf("请输入你要删除的书名>");
	scanf("%11s", b1);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(b1, p->bArr[i].title) == 0) {
			for (; i < p->bSub; ++i) {
				p->bArr[i] = p->bArr[i + 1];
			}
			p->bSub--;
		}
	}
}
//导出图书
void expBook(bookArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\bk.txt", "wt");
 
	if (fp == NULL) {
		printf("程序出错!");
	}
	else {
		for (i = 0; i < p->bSub; ++i) {
			fprintf(fp, "编号:%d 书名:%s 作者:%s 出版社:%s 数量:%d\n", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
		}
	}
	fclose(fp);
	fp = NULL;
	printf("导出成功\n");
}
//遍历图书
void ergBook(bookArr* p) {
	int i = 0;
	system("cls");
	for (i = 0; i < p->bSub; ++i) {
		printf("编号:%d 书名:%s 作者:%s 出版社:%s 数量%d\n", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
	}
}
//查找图书
void lookupBook(bookArr* p) {
	int i = 0;
	char bookName[30];
	system("cls");
	printf("请输入要查找的书籍>");
	scanf("%s", bookName);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(bookName, p->bArr[i].title) == 0) {
			printf("编号:%d 书名:%s 作者:%s 出版社:%s 数量%d", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
			break;
		}
	}
	if (i == p->bSub) {
		printf("不存在该书\n");
	}
}
//修改图书
void modifyBook(bookArr* p) {
	int num = 0, i = 0;
	char bookName[30];
	system("cls");
	printf("请输入要修改的书名>");
	scanf("%s", bookName);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(bookName, p->bArr[i].title) == 0) {
			printf("请输入要修改后的数量\n");
			scanf("%d", &num);
			p->bArr[i].much = num;
			break;
		}
	}
	if (i == p->bSub) {
		printf("不存在该书\n");
	}
	writeBook(p);
}
//添加图书
void regBook(bookArr* p) {
	int i = 0;
	int num = 0;
	char bookName[30];
	system("cls");
	printf("请输入书名>");
	scanf("%s", bookName);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(bookName, p->bArr[i].title) == 0) {
			printf("输入要添加的数量\n");
			scanf("%d", &num);
			p->bArr[i].much += num;
			break;
		}
	}
	if (i == p->bSub) {
		p->bArr[i].id = p->bArr[i - 1].id + 1;
		strcpy(p->bArr[i].title, bookName);
		printf("请输入作者>");
		scanf("%s", p->bArr[i].autor);
		printf("请输入出版社>");
		scanf("%s", p->bArr[i].press);
		printf("请输入数量>");
		scanf("%d", &p->bArr[i].much);
		p->bSub++;
	}
	writeBook(p);
}
//写入图书
void writeBook(bookArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\book.txt", "wt");
	if (fp == NULL) {
		printf("程序出错\n");
		exit(0);
	}
	else {
		for (i = 0; i < p->bSub; ++i) {
			fprintf(fp, "id:%d title:%s autor:%s press:%s much:%d\n", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
		}
	}
	fclose(fp);
	fp = NULL;
}
//删除账号
void adminDel(userArr* p) {
	char u1[STRNAMELEN];
	int i = 0;
	system("cls");
	printf("请输入你要删除的账号>");
	scanf("%11s", u1);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(u1, p->uArr[i].uname) == 0) {
			for (; i < p->uSub; ++i) {
				p->uArr[i] = p->uArr[i + 1];
			}
			p->uSub--;
		}
	}
	writeUser(p);
}
//导出账号
void adminExp(userArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\ur.txt", "wt");
 
	if (fp == NULL) {
		printf("程序出错!");
	}
	else {
		for (i = 0; i < p->uSub; ++i) {
			fprintf(fp, "编号:%d 账号:%s 是否为管理员:%s\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].usign ? "是" : "否");
		}
	}
	fclose(fp);
	fp = NULL;
	printf("导出成功\n");
}
//遍历用户
void adminErg(userArr* p) {
	int i = 0;
	system("cls");
	for (i = 0; i < p->uSub; ++i) {
		printf("编号:%d 账号:%s 是否管理员:%s\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].usign ? "是" : "否");
	}
}
//管理员查找账号
void adminLookup(userArr* p) {
	int i = 0;
	char u1[STRNAMELEN];
	system("cls");
	printf("请输入要查找的账号信息");
	scanf("%s", u1);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(u1, p->uArr[i].uname) == 0) {
			printf("编号:%d 账号:%s 是否管理员:%s\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].usign ? "是" : "否");
		}
	}
}
//管理员修改账号
void adminModify(userArr* p) {
	char u1[STRNAMELEN];
	char u2[STRPASSLEN];
	int i = 0;
	int t = 0;
	int l = 1;
	system("cls");
	printf("请输入要修改的账号>");
	scanf("%s", u1);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(u1, tempAdmin) == 0) {
			printf("请输入想修改的密码>");
			scanf("%s", u2);
			for (i = 0; i < p->uSub; ++i) {
				if (strcmp(u1, p->uArr[i].uname) == 0) {
					strcpy(p->uArr[i].upass, u2);
					writeUser(p);
					printf("修改成功!");
					l = 0;
				}
			}
			break;
		}
		else {
			for (i = 0; i < p->uSub; ++i) {
				if (strcmp(u1, p->uArr[i].uname) == 0 && strcmp(u1, p->uArr[0].uname) != 0) {
					printf("是否成为管理员?1/0\n");
					scanf("%d", &t);
					if (t == 1) {
						p->uArr[i].usign = 1;
						writeUser(p);
						printf("修改成功!");
						l = 0;
						break;
					}
					else {
						p->uArr[i].usign = 0;
						writeUser(p);
						printf("修改成功!");
						l = 0;
						break;
					}
				}
			}
			break;
		}
		break;
	}
	if (l) {
		printf("不存在该账号!");
	}
}
//管理员登录页面
void adSig(userArr* p, bookArr* pb) {
	pArr po;
	po.i = 0;
	begin(&po);
 
	while (1)
	{
		see(&po);
		switch (getch())
		{
		case 72:
			moveup(&po);
			see(&po);
			break;
		case 80:
			movedown(&po);
			see(&po);
			break;
		case 13:
			adminChoice(p, &po, pb);
			system("pause");
			system("cls");
			see(&po);
			break;
		}
	}
}
//向上移动
void  moveup(pArr* po) {
	if (po->i <= 13 && po->i > 0)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[--(po->i)].fh, "<--");
 
	}
}
//向下移动
void  movedown(pArr* po) {
	if (po->i >= 0 && po->i < 12)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[++(po->i)].fh, "<--");
	}
}
//遍历打印结构体数组
void see(pArr* po) {
	int j;
	system("cls");
	printf("\t============================用户===========================\n\n");
	for (j = 0; j < BLSTRLEN; j++)
	{
		printf("\t\t\t\t%s%s\n", po->o[j].ch, po->o[j].fh);
		if (j == 5) {
			printf("\n\t============================图书===========================\n\n");
		}
	}
}
//初始化遍历结构体数组
void begin(pArr* po) {
	int i = 0;
	strcpy(po->o[12].ch, "退出系统");
	strcpy(po->o[0].ch, "增加账号");
	strcpy(po->o[1].ch, "修改账号");
	strcpy(po->o[2].ch, "查找账号");
	strcpy(po->o[3].ch, "遍历账号");
	strcpy(po->o[4].ch, "导出账号");
	strcpy(po->o[5].ch, "删除账号");
	strcpy(po->o[6].ch, "增加图书");
	strcpy(po->o[7].ch, "修改图书");
	strcpy(po->o[8].ch, "查找图书");
	strcpy(po->o[9].ch, "遍历图书");
	strcpy(po->o[10].ch, "导出图书");
	strcpy(po->o[11].ch, "删除图书");
	strcpy(po->o[0].fh, "<--"); //箭头
	for (i = 1; i < 13; ++i) {
		strcpy(po->o[i].fh, " "); //箭头
	}
}
//登录用户
void sign(userArr* p, bookArr* pb) {
	char user[12];
	char pass[20];
	int i = 0;
	FILE* fp = fopen("D:\\user.txt", "rt");
POOK:printf("请输入登录账号>");
	scanf("%11s", user);
	printf("请输入登录密码>");
	scanf("%19s", pass);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(user, p->uArr[i].uname) == 0 && strcmp(pass, p->uArr[i].upass) == 0) {
			if (p->uArr[i].usign == 0) {
				printf("欢迎你尊敬的%s会员\n", p->uArr[i].uname);
				strcpy(tempAdmin, p->uArr[i].uname);
				system("pause");
				system("cls");
				memSig(p, pb);
				break;
			}
			else {
				printf("欢迎你尊敬的%s管理员\n", p->uArr[i].uname);
				strcpy(tempAdmin, p->uArr[i].uname);
				system("pause");
				system("cls");
				adSig(p, pb);
				break;
			}
		}
	}
	if (i == p->uSub) {
		printf("账号或密码错误，请重新输入!");
		system("pause");
		system("cls");
		goto POOK;
	}
	fclose(fp);
	fp = NULL;
}
//图书动态内存扩展
void bExpMemory(bookArr* p) {
	if (p->bSub == p->bMaxLen) {
		book* Q = realloc(p->bArr, (p->bMaxLen + 2) * sizeof(book));
		if (Q == NULL) {
			printf("程序出错\n");
			system("pause");
			exit(0);
		}
		else {
			p->bArr = Q;
			p->bMaxLen += 2;
		}
	}
}
//读取图书信息
void readBook(bookArr* p) {
	FILE* fp = fopen("D:\\book.txt", "rt");
	while ((fscanf(fp, "id:%d title:%s autor:%s press:%s much:%d\n", &p->bArr[p->bSub].id, p->bArr[p->bSub].title, p->bArr[p->bSub].autor, p->bArr[p->bSub].press, &p->bArr[p->bSub].much)) != EOF) {
		p->bSub++;
		bExpMemory(p);
	}
	fclose(fp);
	fp = NULL;
}
//book申请动态
void bAppMemory(bookArr* p) {
	//使用malloc函数进行申请
	book* Q = (book*)malloc(BARRLEN * sizeof(book));
	if (Q == NULL) {
		printf("程序出错，请重新运行\n");
		exit(0);
	}
	else {
		p->bArr = Q;
		//使用memset函数进行初始化
		memset(p->bArr, 0, sizeof(p->bArr));
		p->bSub = 0;
		p->bMaxLen = BARRLEN;
	}
}
//注册用户
void regUser(userArr* p) {
	
	char user[12];
	char pass[20];
	int i = 0;
	uExpMemory(p);
	printf("请输入账号(最多11位)>");
	scanf("%11s", user);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(user, p->uArr[i].uname) == 0) {
			printf("用户名已存在！");
			break;
		}
	}
	if (i == p->uSub) {
		printf("请输入密码>");
		scanf("%19s", pass);
		strcpy(p->uArr[p->uSub].uname, user);
		strcpy(p->uArr[p->uSub].upass, pass);
		p->uArr[p->uSub].uid = p->uArr[p->uSub - 1].uid + 1;
		p->uArr[p->uSub].usign = 0;
		p->uSub++;
	}
	writeUser(p);
}
//写入用户信息
void writeUser(userArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\user.txt", "wt");
	for (i = 0; i < p->uSub; ++i) {
		fprintf(fp, "id:%d user:%s password:%s key:%d\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].upass, p->uArr[i].usign);
	}
	fclose(fp);
	fp = NULL;
}
//读取用户信息
void readUser(userArr* p) {
	FILE* fp = fopen("D:\\user.txt", "rt");
	while ((fscanf(fp, "id:%d user:%s password:%s key:%d\n", &p->uArr[p->uSub].uid, p->uArr[p->uSub].uname, p->uArr[p->uSub].upass, &p->uArr[p->uSub].usign)) != EOF) {
		p->uSub++;
		uExpMemory(p);
	}
	fclose(fp);
	fp = NULL;
}
//动态内存申请扩展
void uExpMemory(userArr* p) {
	if (p->uSub == p->uMaxLen) {
		user* Q = realloc(p->uArr, (p->uMaxLen + 2) * sizeof(user));
		if (Q == NULL) {
			printf("程序出错\n");
			system("pause");
			exit(0);
		}
		else {
			p->uArr = Q;
			p->uMaxLen += 2;
		}
	}
}
//user申请动态内存
void uAppMemory(userArr* p) {
	//使用malloc函数进行申请
	user* Q = (user*)malloc(UARRLEN * sizeof(user));
	if (Q == NULL) {
		printf("程序出错，请重新运行\n");
		exit(0);
	}
	else {
		p->uArr = Q;
		//使用memset函数进行初始化
		memset(p->uArr, 0, sizeof(p->uArr));
		p->uSub = 0;
		p->uMaxLen = UARRLEN;
	}
}
//登录页面
void login(userArr* p, bookArr* pb) {
 
	int key = 0;
	int i = 1;
	while (i) {
		printf("\n\n\n\n\t\t====================图书管理系统====================\n");
		printf("\t\t====================1.登录系统  ====================\n");
		printf("\t\t====================2.注册账号  ====================\n");
		printf("\t\t====================0.退出系统  ====================\n");
		printf("\t\t\t\t请按数字键回车确定>");
		scanf("%d", &key);
		switch (key) {
		case 1:
			sign(p, pb);
			system("pause");
			system("cls");
			break;
		case 2:
			system("cls");
			regUser(p);
			system("pause");
			system("cls");
			break;
		case 0:
			system("pause");
			system("cls");
			i = 0;
			break;
		default:
			system("cls");
			printf("输入错误请重新输入\n");
			system("pause");
			system("cls");
			break;
		}
	}
}
//加载页面
void load() {
	int i = 0;
	//■□
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t■■■■■■■■■■");
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
 
	for (i = 0; i < 10; ++i) {
		Sleep(350);
		printf("□");
	}
	system("cls");
}