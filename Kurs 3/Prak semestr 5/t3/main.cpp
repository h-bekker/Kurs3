#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
using namespace std;

map <wchar_t,int> eng = { {'A', 0} , {'B', 1} , {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25} };
map <wchar_t,int> engl = { {'a', 0} , {'b', 1} , {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24}, {'z', 25} };
map <wchar_t,int>::iterator it;
map <wchar_t,int>::iterator itkey;
map <wchar_t,int>::iterator itbuff;
char* buff;
char* key;
char* newkey;
char* answer;

char* createkey(int sizebuff, int sizekey) //приведение ключа под текст
{
	int keyindex=0;
	for (int i=0; i < sizebuff; i++)
	{
		if (((buff[i] == ' ') || (buff[i] == '_') || (buff[i] == ',') || (buff[i] == '.')) or ((buff[i] >= '0') and (buff[i] <= '9'))) //остающийся символы
		{
			newkey[i] = buff[i];
			continue;
		}
		newkey[i] = key[keyindex % sizekey]; 
		keyindex++;
	}
	return newkey;
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

char* getline(ifstream & f, char* str) //считывание строки
{
	char c;
	f.get(c); //считываем пробел
	f.getline(str,2000); //считываем строку 
	return str;
}

char* crypt(int sizebuff, const char* mode) //действие с режимым mode
{
	int ansindex;
	bool flag = !(strcmp(mode,"encrypt")); //флаг, отвечающий за действие
	bool h1gh = true;
	char c;
	for (int i=0; i < sizebuff; i++)
	{
		if (((buff[i] == ' ') || (buff[i] == '_') || (buff[i] == ',') || (buff[i] == '.')) or ((buff[i] >= '0') and (buff[i] <= '9')))  //остающийся символы
		{
			answer[i] = buff[i];
			continue;
		}
		itkey = eng.find(newkey[i]); //находим символ ключа в контейнере
		if (itkey == eng.end()) //если встретился недопустимый символ
		{
			itkey = engl.find(newkey[i]);
			if (itkey == engl.end())
			{
				c = newkey[i];
				throw c;
			}
		}
		itbuff = eng.find(buff[i]); //находим i-ый символ текста в контейнере
		if (itbuff == eng.end()) //если встретился недопустимый символ
		{
			itbuff = engl.find(buff[i]);
			if (itbuff == engl.end())
			{
				c = buff[i];
				throw c;
			}
			h1gh = false;
		}
		if (flag) //режим encrypt
			ansindex = ((*itbuff).second + (*itkey).second) % 26;
		else //режим decrypt
			ansindex = ((*itbuff).second - (*itkey).second + 26) % 26;
		if (h1gh)
		{
			for (it=eng.begin(); it!=eng.end(); it++) //поиск в контейнере i-го символа ответа 
				if ((*it).second == ansindex)
				{
					answer[i]=(*it).first;
					break;
				}
		}
		else 
		{
			for (it=engl.begin(); it!=engl.end(); it++) //поиск в контейнере i-го символа ответа 
				if ((*it).second == ansindex)
				{
					answer[i]=(*it).first;
					break;
				}
		}
		h1gh = true;
	}
	return answer;
}

char* action(ifstream & f, const char* mode)
{
	int sizekey, sizebuff;
	f >> sizekey; //считываем ключ
	key = getline(f,key);
	if (!strlen(key))
		throw key; 
	f >> sizebuff; //считываем текст
	buff = getline(f,buff);
	newkey = createkey(sizebuff,sizekey); //приведение ключа под текст
	answer = crypt(sizebuff,mode); //действие с заданным режимом
	return answer;
}

int main(int argc, char** argv) 
{
	try
	{
		buff = new char [2001];
		key = new char [2001];
		newkey = new char [2001];

		answer = new char [2001]; // выделяем память
		ifstream file = openfile(argc,argv); //работа с заданным параметром-файлом
		file.getline(buff,2000); //считываем режим
		if ((!strcmp(buff,"encrypt")) or (!strcmp(buff,"encrypt\r")))
			answer = action(file,"encrypt"); //действие при режиме encrypt
		else if ((!strcmp(buff,"decrypt")) or (!strcmp(buff,"decrypt\r")))
			answer = action(file,"decrypt"); //действие при режиме decrypt
		else throw "uncorrect mode\n"; //если задан иной режим
		cout << answer << endl;
		file.close();
		return 0;
	}
	catch (const char* source) 
	{
		cout << "Error. " << source << endl;
		return 1;
	}
	catch (char c)
	{
		cout << "Error" << endl;
		return 1;
	}
}
