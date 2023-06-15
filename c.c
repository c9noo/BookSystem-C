#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include<locale.h>
 
#define STRNAMELEN 12 //�û��˺Žṹ�峤��
#define STRPASSLEN 20 //�û�����ṹ�峤��
#define UARRLEN 3 //�û�����ṹ���ʼ�ڴ��С
 
#define BARRLEN 5 //ͼ������ṹ���ʼ�ڴ��С
#define BOOKNAME 30 //ͼ�����������
#define BOOKAUTOR 30 //ͼ�����������
#define BOOKPRESS 10 //ͼ������������
 
#define STRCHLEN 20 //pl�ṹ��ch���鳤��
#define STRFHLEN 5  //pl�ṹ��fh���鳤��
#define BLSTRLEN 13  //�����ṹ��������±�
 
// �û��ṹ��
typedef struct username {
	int uid; //�û�id
	char uname[STRNAMELEN]; //�û���
	char upass[STRNAMELEN]; //�û�����
	int usign; //�û���� 0������ͨ�û�  1�������Ա
}user;
 
//�û��ṹ������
typedef struct userArray {
	user* uArr; //�û��ṹ������
	int uSub; //�û��ṹ�����鵱ǰ�±�
	int uMaxLen;  //�û��ṹ�����鵱ǰ�������
}userArr;
 
//ͼ��ṹ��
typedef struct books {
	int id; //ͼ����
	char title[BOOKNAME]; //ͼ������
	char autor[BOOKAUTOR]; //ͼ������
	char press[BOOKPRESS]; //������
	int much; //����
}book;
 
//ͼ��ṹ������
typedef struct booksArray {
	book* bArr; //ͼ��ṹ��ָ��
	int bSub; //ͼ��ṹ�����鵱ǰ�±�
	int bMaxLen; //ͼ��ṹ�����鵱ǰ�������
}bookArr;
 
//������Ϣ�ṹ��
typedef struct bookRecord {
	char reName[STRNAMELEN]; //����������
	char reBook[BOOKNAME]; //�鼮
	char re[5]; //�Ƿ�黹
}record;
 
typedef struct strRecord {
	record* reArr;
	int reSub;
	int reMaxLen;
}reStr;
 
//�����ṹ��
typedef struct pl {
	char ch[STRCHLEN];
	char fh[STRFHLEN];
}pl;
 
typedef struct plArr {
	pl o[BLSTRLEN]; //�����ṹ������
	int i;	 //ȫ�ֱ���-�±�
}pArr;
 
//����Աѡ����
void adminChoice(userArr* p, pArr* po, bookArr* pb);
//ɾ��ͼ��
void delBook(bookArr* p);
//����ͼ��
void expBook(bookArr* p);
//����ͼ��
void ergBook(bookArr* p);
//����ͼ��
void lookupBook(bookArr* p);
//�޸�ͼ��
void modifyBook(bookArr* p);
//���ͼ��
void regBook(bookArr* p);
//д��ͼ��
void writeBook(bookArr* p);
//ɾ���˺�
void adminDel(userArr* p);
//�����˺�
void adminExp(userArr* p);
//�����û�
void adminErg(userArr* p);
//�����˺�
void adminLookup(userArr* p);
//�޸��˺�
void adminModify(userArr* p);
//�����¼ҳ��
void adSig(userArr* p, bookArr* pb);
//�����ƶ�
void  moveup(pArr* po);
//�����ƶ�
void  movedown(pArr* po);
//������ӡ�ṹ������
void see(pArr* po);
//��ʼ�������ṹ������
void begin(pArr* po);
//��¼�û�
void sign(userArr* p, bookArr* pb);
//ͼ�鶯̬�ڴ���չ
void bExpMemory(bookArr* p);
//��ȡͼ����Ϣ
void readBook(bookArr* p);
//book���붯̬
void bAppMemory(bookArr* p);
//ע���û�
void regUser(userArr* p);
//д���û���Ϣ
void writeUser(userArr* p);
//��ȡ�û���Ϣ
void readUser(userArr* p);
//��̬�ڴ�������չ
void uExpMemory(userArr* p);
//user���붯̬�ڴ�
void uAppMemory(userArr* p);
//��¼ҳ��
void login(userArr* p, bookArr* pb);
//����ҳ��
void load();
//��ʼ����ӡ����
void memBegin(pArr* po);
//������ӡ����
void memSee(pArr* po);
//�����ƶ�
void  memMovedown(pArr* po);
//�����ƶ�
void  memMoveup(pArr* po);
//������ӡ����
void memSee(pArr* po);
//��Աѡ����
void memChoice(userArr* p, pArr* po, bookArr* pb);
//����ͼ��
void borBook(userArr* p, bookArr* pb, reStr* pr);
//��ʼ����������
void rAppMemory(reStr* pr);
//��չ
void reExpMemory(reStr* pr);
//��ȡ���ļ�¼
void readRe(reStr* pr);
//д����ļ�¼
void writeRe(reStr* p);
//�黹ͼ��
void returnBook(userArr* p, bookArr* pb, reStr* pr);
//�鿴���ļ�¼
void bookErg(userArr* p, bookArr* pb, reStr* pr);
//�޸ĸ�����Ϣ
void userModify(userArr* p);
 
char tempAdmin[20]; //����ѵ�¼���˺�
 
int main() {
	userArr a; // �û��ṹ������
	bookArr c; //ͼ��ṹ������
	uAppMemory(&a); //�û����붯̬�ڴ�
	readUser(&a); //��ȡ�û�����
	bAppMemory(&c);//book���붯̬�ڴ�
	readBook(&c); //��ȡͼ����Ϣ
	load(); //����ҳ��
	login(&a, &c); //��ҳ��
	return 0;
}
//�޸ĸ�����Ϣ
void userModify(userArr* p) {
	int i = 0;
	char pass[20];
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(p->uArr[i].uname, tempAdmin) == 0) {
			printf("���������޸ĺ������>");
			scanf("%s", pass);
			strcpy(p->uArr[i].upass, pass);
			writeUser(p);
			printf("�޸ĳɹ�\n");
			break;
		}
	}
}
//�鿴���ļ�¼
void bookErg(userArr* p, bookArr* pb, reStr* pr) {
	int i = 0;
	for (i = 0; i < pr->reSub; ++i) {
		if (strcmp(pr->reArr[i].reName, tempAdmin) == 0) {
			printf("�����鼮:%s �Ƿ�黹:%s\n", pr->reArr[i].reBook, pr->reArr[i].re);
		}
	}
}
//�黹ͼ��
void returnBook(userArr* p, bookArr* pb, reStr* pr) {
	int i = 0;
	char bookName[30];
	system("cls");
	printf("������Ҫ�黹������>");
	scanf("%s", bookName);
	for (i = 0; i < pr->reSub; ++i) {
		if (strcmp(tempAdmin, pr->reArr[i].reName) == 0) { //�жϽ����˵������Ƿ����
 
			if (strcmp(bookName, pr->reArr[i].reBook) == 0) { //�ж��Ƿ���ڽ��Ĵ���
				strcpy(pr->reArr[i].re, "��");
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
		printf("��û�н������\n");
	}
	else {
		printf("�黹�ɹ�!\n");
	}
 
}
//д����ļ�¼
void writeRe(reStr* pr) {
	int i = 0;
	FILE* fp = fopen("D:\\record.txt", "wt");
	for (i = 0; i < pr->reSub; ++i) {
		fprintf(fp, "�û�:%s ����:%s �Ƿ�黹:%s\n", pr->reArr[i].reName, pr->reArr[i].reBook, pr->reArr[i].re);
	}
	fclose(fp);
	fp = NULL;
}
//��ȡ���ļ�¼
void readRe(reStr* pr) {
	FILE* fp = fopen("D:\\record.txt", "rt");
	while (fscanf(fp, "�û�:%s ����:%s �Ƿ�黹:%s\n", pr->reArr[pr->reSub].reName, pr->reArr[pr->reSub].reBook, pr->reArr[pr->reSub].re) != EOF) {
		pr->reSub++;
		reExpMemory(pr);
	}
	fclose(fp);
	fp = NULL;
}
//��չ
void reExpMemory(reStr* pr) {
	if (pr->reSub == pr->reMaxLen) {
		record* Q = realloc(pr->reArr, (pr->reMaxLen + 2) * sizeof(record));
		if (Q == NULL) {
			printf("�������\n");
			system("pause");
			exit(0);
		}
		else {
			pr->reArr = Q;
			pr->reMaxLen += 2;
		}
	}
}
//��ʼ����������
void rAppMemory(reStr* pr) {
	//ʹ��malloc������������
	record* Q = (record*)malloc(UARRLEN * sizeof(record));
	if (Q == NULL) {
		printf("�����������������\n");
		exit(0);
	}
	else {
		pr->reArr = Q;
		//ʹ��memset�������г�ʼ��
		memset(pr->reArr, 0, sizeof(pr->reArr));
		pr->reSub = 0;
		pr->reMaxLen = UARRLEN;
	}
}
//����ͼ��
void borBook(userArr* p, bookArr* pb, reStr* pr) {
	char bookName[30];
	int i = 0;
	system("cls");
	ergBook(pb);
	printf("��������Ҫ���ĵ�ͼ��>");
	scanf("%s", bookName);
	for (i = 0; i < pb->bSub; ++i) {
		if (strcmp(bookName, pb->bArr[i].title) == 0) { //�ж��鱾�Ƿ����
			if (pb->bArr[i].much != 0) { //�ж��Ƿ��д��
				strcpy(pr->reArr[pr->reSub].reName, tempAdmin); //����ǰ��¼�˺Ÿ��Ƶ���������Ϣ��
				strcpy(pr->reArr[pr->reSub].reBook, bookName); //�������鼮�����Ƶ�����������
				strcpy(pr->reArr[pr->reSub].re, "��"); //д���
				pr->reSub++; //�±�����
				reExpMemory(pr);  //�ж������ڴ��Ƿ���
				pb->bArr[i].much--;
				printf("���ĳɹ�");
				break;
			}
			else {
				printf("��Ǹ,���鼮�ѿ�!");
				break;
			}
		}
	}
	if (i == pb->bSub) {
		printf("��Ǹ��ʱû�и���,����ϵ����Ա�������!");
	}
	writeBook(pb);
}
//�û�ѡ����
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
		printf("�˳��ɹ�\n");
		system("pause");
		exit(0);
		break;
	}
	writeRe(&z);
}
//��ͨ�û���¼
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
//�����ƶ�
void  memMoveup(pArr* po) {
	if (po->i <= 6 && po->i > 0)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[--(po->i)].fh, "<--");
 
	}
}
//�����ƶ�
void  memMovedown(pArr* po) {
	if (po->i >= 0 && po->i < 4)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[++(po->i)].fh, "<--");
	}
}
//������ӡ����
void memSee(pArr* po) {
	int j;
	system("cls");
	for (j = 0; j < 5; j++)
	{
		printf("\t\t\t\t%s%s\n", po->o[j].ch, po->o[j].fh);
	}
}
//��ʼ����ӡ����
void memBegin(pArr* po) {
	int i = 0;
	strcpy(po->o[0].ch, "����ͼ��");
	strcpy(po->o[1].ch, "�黹ͼ��");
	strcpy(po->o[2].ch, "���ļ�¼");
	strcpy(po->o[3].ch, "�޸���Ϣ");
	strcpy(po->o[4].ch, "�˳�ϵͳ");
	strcpy(po->o[0].fh, "<--"); //��ͷ
	for (i = 1; i < 5; ++i) {
		strcpy(po->o[i].fh, " "); //��ͷ
	}
}
//����Աѡ����
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
//ɾ��ͼ��
void delBook(bookArr* p) {
	char b1[30];
	int i = 0;
	system("cls");
	printf("��������Ҫɾ��������>");
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
//����ͼ��
void expBook(bookArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\bk.txt", "wt");
 
	if (fp == NULL) {
		printf("�������!");
	}
	else {
		for (i = 0; i < p->bSub; ++i) {
			fprintf(fp, "���:%d ����:%s ����:%s ������:%s ����:%d\n", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
		}
	}
	fclose(fp);
	fp = NULL;
	printf("�����ɹ�\n");
}
//����ͼ��
void ergBook(bookArr* p) {
	int i = 0;
	system("cls");
	for (i = 0; i < p->bSub; ++i) {
		printf("���:%d ����:%s ����:%s ������:%s ����%d\n", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
	}
}
//����ͼ��
void lookupBook(bookArr* p) {
	int i = 0;
	char bookName[30];
	system("cls");
	printf("������Ҫ���ҵ��鼮>");
	scanf("%s", bookName);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(bookName, p->bArr[i].title) == 0) {
			printf("���:%d ����:%s ����:%s ������:%s ����%d", p->bArr[i].id, p->bArr[i].title, p->bArr[i].autor, p->bArr[i].press, p->bArr[i].much);
			break;
		}
	}
	if (i == p->bSub) {
		printf("�����ڸ���\n");
	}
}
//�޸�ͼ��
void modifyBook(bookArr* p) {
	int num = 0, i = 0;
	char bookName[30];
	system("cls");
	printf("������Ҫ�޸ĵ�����>");
	scanf("%s", bookName);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(bookName, p->bArr[i].title) == 0) {
			printf("������Ҫ�޸ĺ������\n");
			scanf("%d", &num);
			p->bArr[i].much = num;
			break;
		}
	}
	if (i == p->bSub) {
		printf("�����ڸ���\n");
	}
	writeBook(p);
}
//���ͼ��
void regBook(bookArr* p) {
	int i = 0;
	int num = 0;
	char bookName[30];
	system("cls");
	printf("����������>");
	scanf("%s", bookName);
	for (i = 0; i < p->bSub; ++i) {
		if (strcmp(bookName, p->bArr[i].title) == 0) {
			printf("����Ҫ��ӵ�����\n");
			scanf("%d", &num);
			p->bArr[i].much += num;
			break;
		}
	}
	if (i == p->bSub) {
		p->bArr[i].id = p->bArr[i - 1].id + 1;
		strcpy(p->bArr[i].title, bookName);
		printf("����������>");
		scanf("%s", p->bArr[i].autor);
		printf("�����������>");
		scanf("%s", p->bArr[i].press);
		printf("����������>");
		scanf("%d", &p->bArr[i].much);
		p->bSub++;
	}
	writeBook(p);
}
//д��ͼ��
void writeBook(bookArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\book.txt", "wt");
	if (fp == NULL) {
		printf("�������\n");
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
//ɾ���˺�
void adminDel(userArr* p) {
	char u1[STRNAMELEN];
	int i = 0;
	system("cls");
	printf("��������Ҫɾ�����˺�>");
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
//�����˺�
void adminExp(userArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\ur.txt", "wt");
 
	if (fp == NULL) {
		printf("�������!");
	}
	else {
		for (i = 0; i < p->uSub; ++i) {
			fprintf(fp, "���:%d �˺�:%s �Ƿ�Ϊ����Ա:%s\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].usign ? "��" : "��");
		}
	}
	fclose(fp);
	fp = NULL;
	printf("�����ɹ�\n");
}
//�����û�
void adminErg(userArr* p) {
	int i = 0;
	system("cls");
	for (i = 0; i < p->uSub; ++i) {
		printf("���:%d �˺�:%s �Ƿ����Ա:%s\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].usign ? "��" : "��");
	}
}
//����Ա�����˺�
void adminLookup(userArr* p) {
	int i = 0;
	char u1[STRNAMELEN];
	system("cls");
	printf("������Ҫ���ҵ��˺���Ϣ");
	scanf("%s", u1);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(u1, p->uArr[i].uname) == 0) {
			printf("���:%d �˺�:%s �Ƿ����Ա:%s\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].usign ? "��" : "��");
		}
	}
}
//����Ա�޸��˺�
void adminModify(userArr* p) {
	char u1[STRNAMELEN];
	char u2[STRPASSLEN];
	int i = 0;
	int t = 0;
	int l = 1;
	system("cls");
	printf("������Ҫ�޸ĵ��˺�>");
	scanf("%s", u1);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(u1, tempAdmin) == 0) {
			printf("���������޸ĵ�����>");
			scanf("%s", u2);
			for (i = 0; i < p->uSub; ++i) {
				if (strcmp(u1, p->uArr[i].uname) == 0) {
					strcpy(p->uArr[i].upass, u2);
					writeUser(p);
					printf("�޸ĳɹ�!");
					l = 0;
				}
			}
			break;
		}
		else {
			for (i = 0; i < p->uSub; ++i) {
				if (strcmp(u1, p->uArr[i].uname) == 0 && strcmp(u1, p->uArr[0].uname) != 0) {
					printf("�Ƿ��Ϊ����Ա?1/0\n");
					scanf("%d", &t);
					if (t == 1) {
						p->uArr[i].usign = 1;
						writeUser(p);
						printf("�޸ĳɹ�!");
						l = 0;
						break;
					}
					else {
						p->uArr[i].usign = 0;
						writeUser(p);
						printf("�޸ĳɹ�!");
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
		printf("�����ڸ��˺�!");
	}
}
//����Ա��¼ҳ��
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
//�����ƶ�
void  moveup(pArr* po) {
	if (po->i <= 13 && po->i > 0)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[--(po->i)].fh, "<--");
 
	}
}
//�����ƶ�
void  movedown(pArr* po) {
	if (po->i >= 0 && po->i < 12)
	{
		strcpy(po->o[po->i].fh, " ");
		strcpy(po->o[++(po->i)].fh, "<--");
	}
}
//������ӡ�ṹ������
void see(pArr* po) {
	int j;
	system("cls");
	printf("\t============================�û�===========================\n\n");
	for (j = 0; j < BLSTRLEN; j++)
	{
		printf("\t\t\t\t%s%s\n", po->o[j].ch, po->o[j].fh);
		if (j == 5) {
			printf("\n\t============================ͼ��===========================\n\n");
		}
	}
}
//��ʼ�������ṹ������
void begin(pArr* po) {
	int i = 0;
	strcpy(po->o[12].ch, "�˳�ϵͳ");
	strcpy(po->o[0].ch, "�����˺�");
	strcpy(po->o[1].ch, "�޸��˺�");
	strcpy(po->o[2].ch, "�����˺�");
	strcpy(po->o[3].ch, "�����˺�");
	strcpy(po->o[4].ch, "�����˺�");
	strcpy(po->o[5].ch, "ɾ���˺�");
	strcpy(po->o[6].ch, "����ͼ��");
	strcpy(po->o[7].ch, "�޸�ͼ��");
	strcpy(po->o[8].ch, "����ͼ��");
	strcpy(po->o[9].ch, "����ͼ��");
	strcpy(po->o[10].ch, "����ͼ��");
	strcpy(po->o[11].ch, "ɾ��ͼ��");
	strcpy(po->o[0].fh, "<--"); //��ͷ
	for (i = 1; i < 13; ++i) {
		strcpy(po->o[i].fh, " "); //��ͷ
	}
}
//��¼�û�
void sign(userArr* p, bookArr* pb) {
	char user[12];
	char pass[20];
	int i = 0;
	FILE* fp = fopen("D:\\user.txt", "rt");
POOK:printf("�������¼�˺�>");
	scanf("%11s", user);
	printf("�������¼����>");
	scanf("%19s", pass);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(user, p->uArr[i].uname) == 0 && strcmp(pass, p->uArr[i].upass) == 0) {
			if (p->uArr[i].usign == 0) {
				printf("��ӭ���𾴵�%s��Ա\n", p->uArr[i].uname);
				strcpy(tempAdmin, p->uArr[i].uname);
				system("pause");
				system("cls");
				memSig(p, pb);
				break;
			}
			else {
				printf("��ӭ���𾴵�%s����Ա\n", p->uArr[i].uname);
				strcpy(tempAdmin, p->uArr[i].uname);
				system("pause");
				system("cls");
				adSig(p, pb);
				break;
			}
		}
	}
	if (i == p->uSub) {
		printf("�˺Ż������������������!");
		system("pause");
		system("cls");
		goto POOK;
	}
	fclose(fp);
	fp = NULL;
}
//ͼ�鶯̬�ڴ���չ
void bExpMemory(bookArr* p) {
	if (p->bSub == p->bMaxLen) {
		book* Q = realloc(p->bArr, (p->bMaxLen + 2) * sizeof(book));
		if (Q == NULL) {
			printf("�������\n");
			system("pause");
			exit(0);
		}
		else {
			p->bArr = Q;
			p->bMaxLen += 2;
		}
	}
}
//��ȡͼ����Ϣ
void readBook(bookArr* p) {
	FILE* fp = fopen("D:\\book.txt", "rt");
	while ((fscanf(fp, "id:%d title:%s autor:%s press:%s much:%d\n", &p->bArr[p->bSub].id, p->bArr[p->bSub].title, p->bArr[p->bSub].autor, p->bArr[p->bSub].press, &p->bArr[p->bSub].much)) != EOF) {
		p->bSub++;
		bExpMemory(p);
	}
	fclose(fp);
	fp = NULL;
}
//book���붯̬
void bAppMemory(bookArr* p) {
	//ʹ��malloc������������
	book* Q = (book*)malloc(BARRLEN * sizeof(book));
	if (Q == NULL) {
		printf("�����������������\n");
		exit(0);
	}
	else {
		p->bArr = Q;
		//ʹ��memset�������г�ʼ��
		memset(p->bArr, 0, sizeof(p->bArr));
		p->bSub = 0;
		p->bMaxLen = BARRLEN;
	}
}
//ע���û�
void regUser(userArr* p) {
	
	char user[12];
	char pass[20];
	int i = 0;
	uExpMemory(p);
	printf("�������˺�(���11λ)>");
	scanf("%11s", user);
	for (i = 0; i < p->uSub; ++i) {
		if (strcmp(user, p->uArr[i].uname) == 0) {
			printf("�û����Ѵ��ڣ�");
			break;
		}
	}
	if (i == p->uSub) {
		printf("����������>");
		scanf("%19s", pass);
		strcpy(p->uArr[p->uSub].uname, user);
		strcpy(p->uArr[p->uSub].upass, pass);
		p->uArr[p->uSub].uid = p->uArr[p->uSub - 1].uid + 1;
		p->uArr[p->uSub].usign = 0;
		p->uSub++;
	}
	writeUser(p);
}
//д���û���Ϣ
void writeUser(userArr* p) {
	int i = 0;
	FILE* fp = fopen("D:\\user.txt", "wt");
	for (i = 0; i < p->uSub; ++i) {
		fprintf(fp, "id:%d user:%s password:%s key:%d\n", p->uArr[i].uid, p->uArr[i].uname, p->uArr[i].upass, p->uArr[i].usign);
	}
	fclose(fp);
	fp = NULL;
}
//��ȡ�û���Ϣ
void readUser(userArr* p) {
	FILE* fp = fopen("D:\\user.txt", "rt");
	while ((fscanf(fp, "id:%d user:%s password:%s key:%d\n", &p->uArr[p->uSub].uid, p->uArr[p->uSub].uname, p->uArr[p->uSub].upass, &p->uArr[p->uSub].usign)) != EOF) {
		p->uSub++;
		uExpMemory(p);
	}
	fclose(fp);
	fp = NULL;
}
//��̬�ڴ�������չ
void uExpMemory(userArr* p) {
	if (p->uSub == p->uMaxLen) {
		user* Q = realloc(p->uArr, (p->uMaxLen + 2) * sizeof(user));
		if (Q == NULL) {
			printf("�������\n");
			system("pause");
			exit(0);
		}
		else {
			p->uArr = Q;
			p->uMaxLen += 2;
		}
	}
}
//user���붯̬�ڴ�
void uAppMemory(userArr* p) {
	//ʹ��malloc������������
	user* Q = (user*)malloc(UARRLEN * sizeof(user));
	if (Q == NULL) {
		printf("�����������������\n");
		exit(0);
	}
	else {
		p->uArr = Q;
		//ʹ��memset�������г�ʼ��
		memset(p->uArr, 0, sizeof(p->uArr));
		p->uSub = 0;
		p->uMaxLen = UARRLEN;
	}
}
//��¼ҳ��
void login(userArr* p, bookArr* pb) {
 
	int key = 0;
	int i = 1;
	while (i) {
		printf("\n\n\n\n\t\t====================ͼ�����ϵͳ====================\n");
		printf("\t\t====================1.��¼ϵͳ  ====================\n");
		printf("\t\t====================2.ע���˺�  ====================\n");
		printf("\t\t====================0.�˳�ϵͳ  ====================\n");
		printf("\t\t\t\t�밴���ּ��س�ȷ��>");
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
			printf("�����������������\n");
			system("pause");
			system("cls");
			break;
		}
	}
}
//����ҳ��
void load() {
	int i = 0;
	//����
	printf("\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t��������������������");
	printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b");
 
	for (i = 0; i < 10; ++i) {
		Sleep(350);
		printf("��");
	}
	system("cls");
}