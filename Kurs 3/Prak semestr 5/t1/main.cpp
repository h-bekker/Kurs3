#include <iostream>
#include <fstream>
#include <cstring>
#include <map>
using namespace std;

map <wchar_t,int> eng = { {'A', 0} , {'B', 1} , {'C', 2}, {'D', 3}, {'E', 4}, {'F', 5}, {'G', 6}, {'H', 7}, {'I', 8}, {'J', 9}, {'K', 10}, {'L', 11}, {'M', 12}, {'N', 13}, {'O', 14}, {'P', 15}, {'Q', 16}, {'R', 17}, {'S', 18}, {'T', 19}, {'U', 20}, {'V', 21}, {'W', 22}, {'X', 23}, {'Y', 24}, {'Z', 25} };
map <wchar_t,int> engl = { {'a', 0} , {'b', 1} , {'c', 2}, {'d', 3}, {'e', 4}, {'f', 5}, {'g', 6}, {'h', 7}, {'i', 8}, {'j', 9}, {'k', 10}, {'l', 11}, {'m', 12}, {'n', 13}, {'o', 14}, {'p', 15}, {'q', 16}, {'r', 17}, {'s', 18}, {'t', 19}, {'u', 20}, {'v', 21}, {'w', 22}, {'x', 23}, {'y', 24}, {'z', 25} };
map <wchar_t,int>::iterator it;
char* buff;
char* answer;

int gcd(int a, int b)
{
	if (b==0)
		return a;
	return gcd(b,a%b);
}

char* crypt(int a, int b, const char* mode) //действие с режимым mode
{
	int y;
	bool flag;
	if ((!strcmp(mode,"encrypt")) or (!strcmp(mode,"encrypt\r")))
		flag = true;
	else
		flag = false;
	bool h1gh = true;
	char c;
	answer[0]='\0';
	int len = strlen(buff);
	for (int i=0; i<len; i++)
	{
		c = buff[i];
		if ((c < 'A') || (c > 'Z'))
		{
			if ((c == ' ') || (c == '_') || (c == ',') || (c == '.')) //проверка символа
			{
				answer[i]=c;
				continue;
			}
			else if ((c >= 'a') && (c <= 'z'))
			{
				h1gh = false;
				it = engl.find(c);
				y = (*it).second;
			}
				else throw c; //если символ недопустим
		}
		else {
			it = eng.find(c);
			y = (*it).second;
		}
		if (flag) //режим encrypt
		{
			y = (a*y+b) % 26;
			if (y<0)
			{
				y %= 26;
				y = 26 - abs(y);
			}
			if (h1gh)
			{
				for (it=eng.begin(); it!=eng.end(); it++)
					if ((*it).second == y)
					{
						answer[i]=(*it).first;
						break;
					}
			}
			else
			{
				for (it=engl.begin(); it!=engl.end(); it++)
					if ((*it).second == y)
					{
						answer[i]=(*it).first;
						break;
					}	
			}
		}
		else //режим decrypt
		{
			for (int j=0; j<26; j++)
			{
				if (y == (a*j+b) % 26)
				{
					if (h1gh)
					{
						for (it=eng.begin(); it!=eng.end(); it++)
							if ((*it).second == j)
							{
								answer[i]=(*it).first;
								break;
							}
					}
					else
					{
						for (it=engl.begin(); it!=engl.end(); it++)
							if ((*it).second == j)
							{
								answer[i]=(*it).first;
								break;
							}
					}				
					break;
				}
			}
		}
	h1gh = true;
	}
	return answer;
}

int reverse(int count) //обратное число по модулю
{
	int tmp;
	for (int i=1; i<26; i++)
	{
		tmp = (count*i) % 26;
		if (tmp == 1) 
		{
			tmp = i;
			break;
		}
	}
	return tmp;
}				
		
ifstream openfile(int argc, char** argv) //открытие параметр-файла
{
	if (argc != 2)
		throw "Few parametrs";
	ifstream file(argv[1]); //перенаправление потока ввода
	if (!file.is_open())
		throw "Error. File is not open\n";
	return file;
}
		
char* action(ifstream & f, const char* mode)
{
	int a,b;
	f >> a >> b; //считываем параметры 
	f.getline(buff,2000);
	buff[0]='\0';
	f.getline(buff,2000); //считываем текст
	if ((!strcmp(mode,"decrypt")) or (!strcmp(mode,"decrypt\r")))
	{
		if (gcd(a,26) != 1) //ограничение для параметра a
			throw "Error: number is no coprime with 26"; 
	}
	answer = crypt(a,b,mode); //действие с заданным режимом
	return answer;
}		
		
char* breakmode(ifstream & f) //действие для режима break
{
	int a,b;
	char c;
	int temp[4];
	for (int i=0; i<4; i++)
	{
		f >> c;
		temp[i] = c - 'A'; //пары открытый текст и шифротекст
	}
	int det = temp[0]-temp[1]; //определитель
	det = (det % 26 + 26) % 26; //определитель в кольце
	if (gcd(det,26)!=1) 
		throw "Error: inverse elem does not exis";
	int detreverse;
	detreverse = reverse(det); //обратное число в кольце 
	a = detreverse*(temp[2]-temp[3]);
	b = detreverse*(temp[0]*temp[3]-temp[1]*temp[2]);
	a = (a % 26 + 26) % 26; //параметр a в кольце
	b = (b % 26 + 26) % 26; //параметр b в кольце 
	f.getline(buff,2000);
	buff[0]='\0';
	f.getline(buff,2000);
	answer = crypt(a,b,"decrypt"); //расшифровка по найденным параметрам
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
		if ((!strcmp(buff,"encrypt")) or (!strcmp(buff,"encrypt\r")))
			answer = action(file,"encrypt"); //действие при режиме encrypt
		else if ((!strcmp(buff,"decrypt")) or (!strcmp(buff,"decrypt\r")))
			answer = action(file,"decrypt"); //действие при режиме decrypt
			else if ((!strcmp(buff,"break")) or (!strcmp(buff,"break\r")))
				answer = breakmode(file);
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
	catch (char c)
	{
		cout << "unexpected symbol: " << c << endl;
		return 1;
	}
}
