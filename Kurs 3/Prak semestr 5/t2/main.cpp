#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
using namespace std;

map <wchar_t,int> eng = { {'A', 11}, {'B', 12}, {'C', 13}, {'D', 14}, {'E', 15}, 
						  {'F', 21}, {'G', 22}, {'H', 23}, {'I', 24}, {'K', 25}, 
						  {'L', 31}, {'M', 32}, {'N', 33}, {'O', 34}, {'P', 35}, 
						  {'Q', 41}, {'R', 42}, {'S', 43}, {'T', 44}, {'U', 45}, 
						  {'V', 51}, {'W', 52}, {'X', 53}, {'Y', 54}, {'Z', 55} };
map <wchar_t,int>::iterator it;
char* buff;
char* answer;

int* indicesofsim(char* str) //формирует массив индексов по строке
{
	char c;
	int* tmp;
	int len = strlen(str);
	tmp = new int[len]; //координаты символов в таблице
	for (int i=0; i<len; i++)
	{
		c = str[i];
		it = eng.find(c);
		if (it == eng.end()) //если найден недопустимый символ
			throw "uncorrect symbol\n";
		tmp[i]=(*it).second;
	}
	return tmp;
}

int* encrypt(int* arrofindex, int shift)
{	
	int firstsim = arrofindex[0] / 10;
	int len = strlen(buff);
	for (int i=0; i<len-1; i++) //сдвигаем координаты влево один раз
	{
		arrofindex[i]%=10;
		arrofindex[i]=(arrofindex[i]*10)+(arrofindex[i+1] / 10);
	}
	arrofindex[len-1]%=10; //определение последней координаты
	arrofindex[len-1]=(arrofindex[len-1]*10)+firstsim;
	int shiftnum = (shift/2) % len;
	int* ansarray;
	ansarray = new int[len]; //координаты в таблице символов ответа
	for (int i=0; i<len; i++)
		ansarray[i]=arrofindex[(shiftnum+i) % len];
	return ansarray;
}

int* decrypt(int* arrofindex, int shift)
{
	int lastsim = arrofindex[strlen(buff)-1] % 10;
	int len = strlen(buff);
	for (int i=len-1; i>0; i--) //сдвигаем координаты вправо один раз
	{
		arrofindex[i]/=10;
		arrofindex[i]=((arrofindex[i-1]%10)*10)+arrofindex[i];
	}
	arrofindex[0]/=10; //определение первой координаты
	arrofindex[0]=lastsim*10+arrofindex[0];
	int shiftnum = (shift/2) % len;
	int* ansarray;
	ansarray = new int[len]; //координаты в таблице символов ответа
	for (int i=0; i<len; i++)
		ansarray[i]=arrofindex[(len-shiftnum+i) % len];
	return ansarray;
}

char* crypt(int shift, const char* mode) //действие с режимым mode
{
	if ((shift % 2) == 0)  //если сдвиг задан четным числом
		throw shift;
	int* tmp;
	int len = strlen(buff);
	tmp = new int[len]; //координаты символов в таблице
	tmp = indicesofsim(buff);
	bool flag = !(strcmp(mode,"encrypt")); //флаг, отвечающий за действие
	int* ansarray; //координаты в таблице символов ответа
	ansarray = new int[len];
	if (shift < 0)
	{
		shift = -shift;
		if (!strcmp(mode,"encrypt"))
			flag = false;
		else
			flag = true;
	}
	if (flag) //режим encrypt
		ansarray = encrypt(tmp,shift);
	else //режим decrypt
		ansarray = decrypt(tmp,shift);
	for (int i=0; i<len; i++)
		for (it=eng.begin(); it!=eng.end(); it++) //поиск в контейнере i-го символа ответа 
			if ((*it).second == ansarray[i])
			{
				answer[i]=(*it).first;
				break;
			}
	return answer;
}	
	
ifstream openfile(int argc, char** argv) //открытие параметр-файла
{
	if (argc != 2)
		throw "Few parametrs\n";
	ifstream file(argv[1]); //перенаправление потока ввода
	if (!file.is_open())
		throw "File is not open\n";
	return file;
}

char* action(ifstream & f, const char* mode)
{
	int shift;
	f >> shift; //считываем количество сдвигов
	f.getline(buff,2000);
	buff[0]='\0';
	f.getline(buff,2000); //считываем текст
	answer = crypt(shift,mode); //действие с заданным режимом
	return answer;
}
	

int main(int argc, char** argv) 
{
	try 
	{
		buff = new char [2001];
		answer = new char [2001]; //выделяем память
		ifstream file = openfile(argc,argv); //работа с заданным параметром-файлом
		file.getline(buff,2000); //считываем режим
		if (!strcmp(buff,"encrypt"))
			answer = action(file,"encrypt"); //действие при режиме encrypt
		else if (!strcmp(buff,"decrypt")) 
			answer = action(file,"decrypt"); //действие при режиме decrypt
		else throw "uncorrect mode\n"; //если задан иной режим
		cout << answer << endl;
		file.close();
		return 0;
	}
	catch (const char* source) 
	{
		cout << source << endl;
		return 1;
	}
	catch (int k)
	{
		cout << "shift must me odd. You set the number: " << k << endl;
		return 1;
	}
}
