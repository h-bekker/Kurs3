#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>
#include <cmath>
#include <bitset>
using namespace std;

enum poliz {
	XOR, //+            //0
	ADD, // #
	PROT, // >>
	CONC, // |
	CALL, // SPE        //4
	CUR_ITER, // I[i]
	CUR_KEY, // k
	CUR_RIGHT, // R
	PNUMBER             //8
};

enum type_of_lex {
	NUMBER, //0
	ID,
	ROT,
	LBRACE,
	RBRACE,
	ASSIGN, //5
	OP_XOR,
	OP_ADD,
	OP_CONC,
	LBRACKET,
	RBRACKET, //10
	COMMA,
	LINDEX,
	RINDEX,
	EF,
	NEWLINE //15
};

enum Names_ID {
	ROUND_NUM, //0
	BLOCK_LEN,
	KEY_LEN,
	FUNC, //3
	KEY,
	I_CONST, //5
	RIGHT_PART,
	NONE
};

struct expression {
	poliz pol;
	string name;
	size_t num;
};

template<typename T>
class stack {
	T* arr;
	size_t cap;
	size_t size;
public:
	stack() : arr(new T[10]), cap(10), size(0) {}
	bool empty() { return size == 0; }
	T& top() { return arr[size - 1]; }
	void push(const T & value) {
		if(size >= cap) {
			cap = 2 * cap;
			auto narr = new T[cap];
			for(size_t i = 0; i < size; ++i) {
				narr[i] = arr[i];
			}
			delete[] arr;
			arr = narr;
		}
		arr[size++] = value;
	}
	pair<T*, size_t> get_stack() {
		T* a = new T[size];
		for(size_t i = 0; i < size; ++i)
			a[i] = arr[i];
		return make_pair(a, size);
	}
	T pop() { return arr[--size]; }
};

struct config {
	size_t r;
	size_t n;
	size_t k;
	size_t* I;
	map<string, pair<size_t*, size_t> > SPE;
	pair<expression*, size_t> F;
	pair<expression*, size_t> K;
	void print_SPE(); 
	void print_F();
	void print_K();
	void set(uint64_t&, size_t, bool);
	bool at(uint64_t, size_t);
	uint64_t exec_F(uint32_t, uint64_t);
	uint64_t round_key(uint64_t, size_t);
	uint64_t rotation(uint64_t, uint64_t, uint64_t, uint64_t);
	void freecfg();
};

void config::print_SPE() {
	map<string, pair<size_t*, size_t> >::iterator it;
	for (it=SPE.begin(); it!=SPE.end(); it++)
	{
		cout << it->first << "= { ";
		for (int i = 0; i < it->second.second; i++)
			cout << it->second.first[i] << ' ';
		cout << "}\n";
	}
}

void config::print_F() {
	for (int i = 0; i < F.second; i++)
	{
		switch(F.first[i].pol) 
		{
			case 0:			
				cout << "XOR" << ' ';
				break;
			case 1:	
				cout << "ADD" << ' ';
				break;
			case 2:	
				cout << "ROT" << ' ';
				break;
			case 3:	
				cout << "CONC" << ' ';
				break;
			case 4:	
				cout << "CALL" << ' ';
				break;
			case 5:	
				cout << "CUR_ITER" << ' ';
				break;
			case 6:
				cout << "CUR_KEY" << ' ';
				break;
			case 7:	
				cout << "CUR_RIGHT" << ' ';
				break;
			case 8:	
				cout << "NUMBER" << ' ';			
				break;
		}
		cout << F.first[i].name << ' ' << F.first[i].num << endl;
	}
}

void config::print_K() {
	for (int i = 0; i < K.second; i++)
	{
		switch(K.first[i].pol) 
		{
			case 0:			
				cout << "XOR" << ' ';
				break;
			case 1:	
				cout << "ADD" << ' ';
				break;
			case 2:	
				cout << "ROT" << ' ';
				break;
			case 3:	
				cout << "CONC" << ' ';
				break;
			case 4:	
				cout << "CALL" << ' ';
				break;
			case 5:	
				cout << "CUR_ITER" << ' ';
				break;
			case 6:
				cout << "CUR_KEY" << ' ';
				break;
			case 7:	
				cout << "CUR_RIGHT" << ' ';
				break;
			case 8:	
				cout << "NUMBER" << ' ';			
				break;
		}
		cout << K.first[i].name << ' ' << K.first[i].num << endl;
	}
}

void config::set(uint64_t & block, size_t i, bool v) {
    uint64_t mask = 1u;
    mask = mask << (63 - i);
    if(!v) {
        mask = ~mask;
        block = block & mask;
    } else {
        block = block | mask;
    }
}

bool config::at(uint64_t block, size_t i) {
    return (block >> (63 - i)) % 2 == 1;
}

uint64_t config::rotation(uint64_t what, uint64_t how_much, uint64_t where_to_start, uint64_t where_to_end) {
    auto delta = where_to_end - where_to_start + 1;
    how_much = how_much % delta;
    uint64_t result = what;
    for(size_t i = 0; i < delta; ++i)
        set(result, (i + how_much) % delta + where_to_start, at(what, where_to_start + i));
    return result;
}

uint64_t config::exec_F(uint32_t r_right, uint64_t r_key) {
    expression* dirs;
    size_t dirsize;
    tie(dirs, dirsize) = F;
    stack<uint64_t> values;
    for(size_t j = 0; j < dirsize; ++j) {
        uint64_t left,right,a,b,c,d, val, res;
        string func;
        pair<size_t *, size_t> p;
        switch (dirs[j].pol) {
            case CUR_ITER:
                throw "Unexpected lexeme";
            case CUR_KEY:
                values.push(r_key);
                break;
            case CUR_RIGHT:
                a = r_right;
                a = a << 32;
                values.push(a);
                break;
            case PNUMBER:
                val = dirs[j].num;
                values.push(val);
                break;
            case XOR:
                left = values.pop();
                right = values.pop();
                values.push(left ^ right);
                break;
            case ADD:
                left = values.pop();
                left = left >> 32;
                right = values.pop();
                right = right >> 32;
                values.push(((left + right) & 0xFFFFFFFFu) << 32);
                break;
            case CONC:
                right = values.pop();
                left = values.pop();
                values.push((left << 4) ^ (right & 0xFu));
                break;
            case ROT:
                a = values.pop();
                b = values.pop();
                c = values.pop();
                d = values.pop();
                values.push(rotation(d, c, b, a));
                break;
            case CALL:
                func = dirs[j].name;
                p = SPE[func];
                if(func.find('E') == 0 || func.find('P') == 0) {
                    a = values.pop();
                    if(func == "P1")
                        a = a << 32;
                    b = 0;
                    for(size_t i = 0; i < p.second; ++i)
                        set(b, p.first[i], at(a, i));
                    values.push(b);
                } else if(func.find('S') == 0) {
                    a = values.pop();
                    b = values.pop();
                    c = values.pop();
                    if(a - b + 1 != 6) {
                        throw "Wrong s-box size";
                    }
                    res = (c >> (63 - a)) & 0x3Fu;
                    val = p.first[res];
                    values.push(val);
                } else
                    throw "Unknown function";
                break;
        }
    }
    return values.top() >> 32;
}

uint64_t config::round_key(uint64_t key, size_t iter) {
    expression* dirs;
    size_t dirsize;
    tie(dirs, dirsize) = K;
    stack<uint64_t> values;
    for(size_t j = 0; j < dirsize; ++j) {
        uint64_t left, right, a, b, c, d, val, res;
        string func;
        pair<size_t*, size_t> p;
        switch (dirs[j].pol) {
            case CUR_ITER:
                val = I[iter];
                values.push(val);
                break;
            case CUR_KEY:
                values.push(key);
                break;
            case PNUMBER:
                val = dirs[j].num;
                values.push(val);
                break;
            case XOR:
                left = values.pop();
                right = values.pop();
                values.push(left ^ right);
                break;
            case ADD:
                left = values.pop();
                left = left >> 32;
                right = values.pop();
                right = right >> 32;
                values.push(((left + right) & 0xFFFFFFFFu) << 32);
                break;
            case CONC:
                right = values.pop();
                left = values.pop();
                values.push((left & 0xFFFFFFFF00000000u) ^ ((right >> 32)& 0xFFFFFFFFu));
                break;
            case ROT:
                a = values.pop();
                b = values.pop();
                c = values.pop();
                d = values.pop();
                values.push(rotation(d, c, b, a));
                break;
            case CALL:
                func = dirs[j].name;
                p = SPE[func];
                if(func.find('E') == 0 || func.find('P') == 0) {
                    a = values.pop();
                    b = 0;
                    for(size_t i = 0; i < p.second; ++i)
                        set(b, p.first[i], at(a, i));
                    values.push(b);
                } else if(func.find('S') == 0) {
                    a = values.pop();
                    b = values.pop();
                    c = values.pop();
                    res = 0;
                    if(a - b + 1 != 6) {
                        throw "Wrong s-box size";
                    }
                    res = (c >> (63 - a)) & 0x3Fu;
                    val = p.first[res];
                    values.push(val);
                } else
                    throw "Unknown function";
                break;
        }
    }
    return values.top();
}

void config::freecfg() {
	delete[] F.first;
	delete[] K.first;
	delete[] I;
}

struct Lex {
	string value;
	type_of_lex type;
	type_of_lex get_type() { return type; }
	string get_value () { return value; }
	friend ostream& operator << (ostream & s, Lex l ) {
			s << '(' << l.type << ',' << l.value << ");" ;
			return s;
			}
};

struct Parser {
	Lex curr_lex;
	type_of_lex curr_type;
	string curr_value;
	ifstream cf;
	void gl() {
		curr_lex = get_lex();
		curr_type = curr_lex.get_type();
		curr_value = curr_lex.get_value();
		};
	size_t atois(string);
	Lex get_lex();
	pair<expression*, size_t> big_expr(ifstream&, bool);
	config analyze();
	Parser(const char* program) : cf(program) {
		if(!cf.is_open())
			throw "Config file doesn't found"; 
	}
};

size_t Parser::atois(string s) {
	size_t acc = 0;
	for(auto c:s) {
		acc = acc * 10 + c - '0';
	}
	return acc;
}

Lex Parser::get_lex() {
	const int eof = char_traits<char>::eof();
	Lex curr_lex;
	int c;
	if(cf.good())
		c = cf.get();
	else {
		curr_lex.type = EF;
		return curr_lex;
	}
	while(c == ' ' || c == '\r' || c == '\t')
		c = cf.get();
	if (c == eof) {
		curr_lex.type = EF;
		return curr_lex;
	}
	curr_lex.value += c;
	if(isdigit(c)) {
		curr_lex.type = NUMBER;
		while(true) {
			c = cf.get();
			if (c == eof)
				throw c;
			if(isdigit(c))
				curr_lex.value += c;
			else 
				break;
		}
		cf.unget();
	} 
	else 
		if(isalpha(c)) {
			curr_lex.type = ID;
			while(true) {
				c = cf.get();
				if (c == eof)
					throw c;
				if(isdigit(c) || isalpha(c))
					curr_lex.value += c;
				else
					break;
			}
			cf.unget();
		} 
		else {
			switch(c) {
				case '=':
					curr_lex.type = ASSIGN;
					break;
				case '{':
					curr_lex.type = LBRACE;
					break;
				case '}':
					curr_lex.type = RBRACE;
					break;
				case '>':
					curr_lex.type = ROT;
					c = cf.get();
					if (c == eof)
						throw c;
					if(c != '>')
						throw c;
					curr_lex.value += c;
					break;
				case '+':
					curr_lex.type = OP_XOR;
					break;
				case '#':
					curr_lex.type = OP_ADD;
					break;
				case '|':
					curr_lex.type = OP_CONC;
					break;
				case '(':
					curr_lex.type = LBRACKET;
					break;
				case ')':
					curr_lex.type = RBRACKET;
					break;
				case ',':
					curr_lex.type = COMMA;
					break;
				case '[':
					curr_lex.type = LINDEX;
					break;
				case ']':
					curr_lex.type = RINDEX;
					break;
				case '\n':
					curr_lex.type = NEWLINE;
					break;
				default:
					throw c;
			}
		}
	return curr_lex;
}

pair<expression*, size_t> Parser::big_expr(ifstream& f, bool restrict_R) {
	stack<expression> expr;
	stack<Lex> tmp_stack;
	Lex tmp;
	Lex ol;
	bool fin = false;
	gl();
	while(true) {
		if(fin) break;
		switch (curr_type) {
			case COMMA:
				if (tmp_stack.empty())
					throw "Comma outside function call";
				while (!tmp_stack.empty()) {
					if (tmp_stack.top().type == OP_ADD || tmp_stack.top().type == OP_XOR || tmp_stack.top().type == OP_CONC) {
						tmp = tmp_stack.pop();
						if (tmp.type == OP_ADD)
							expr.push({ADD, "", 0});
						else 
							if(tmp.type == OP_XOR)
								expr.push({XOR, "", 0});
							else 
								if(tmp.type == OP_CONC)
									expr.push({CONC, "", 0});
					} 
					else
						break;
				}
				break;
			case EF:
				throw curr_lex;
			case LBRACKET:
				tmp_stack.push(curr_lex);
				break;
			case NUMBER:
				expr.push({PNUMBER, curr_value, atois(curr_value)});
				break;
			case RBRACKET:
				if (tmp_stack.empty())
					throw "Unbalanced brackets";
				tmp = tmp_stack.pop();
				while (tmp.type != LBRACKET) {
					switch (tmp.type) {
						case OP_XOR:
							expr.push({XOR, "", 0});
							break;
						case OP_ADD:
							expr.push({ADD, "", 0});
							break;
						case OP_CONC:
							expr.push({CONC, "", 0});
							break;
						case ROT:
							expr.push({PROT, "", 0});
							break;
						case ID:
							expr.push({CALL, tmp.value, 0});
							break;
					}
					if (tmp_stack.empty()) {
						throw "Unbalanced brackets";
					}
					tmp = tmp_stack.pop();
				}
				if(!tmp_stack.empty()){
					if(tmp_stack.top().type == ID) {
						tmp = tmp_stack.pop();
						expr.push({CALL, tmp.value, 0});
					}
				}
				break;
			case ROT:
			case ID:
				if (curr_value == "I") {
					gl();
					if (curr_type != LINDEX)
						throw curr_lex;
					gl();
					if (curr_type != ID)
						throw curr_lex;
					gl();
					if (curr_type != RINDEX)
						throw curr_lex;
					expr.push({CUR_ITER, "", 0});
				} 
				else 
					if (curr_value == "k")
						expr.push({CUR_KEY, "", 0});
					else 
						if (curr_value == "R") {
							if (!restrict_R)
								expr.push({CUR_RIGHT, "", 0});
							else
								throw "Cannot use R in Key derivation function";
						} 
						else
							tmp_stack.push(curr_lex);
				break;
			case OP_XOR:
			case OP_ADD:
				tmp_stack.push(curr_lex);
				break;
			case OP_CONC:
				ol = curr_lex;
				while (!tmp_stack.empty()) {
					if (tmp_stack.top().type == OP_ADD || tmp_stack.top().type == OP_XOR || tmp_stack.top().type == OP_CONC) {
						tmp = tmp_stack.pop();
						if (tmp.type == OP_ADD)
							expr.push({ADD, "", 0});
						else 
							if(tmp.type == OP_XOR)
						 		expr.push({XOR, "", 0});
							else 
								if(tmp.type == OP_CONC)
									expr.push({CONC, "", 0});
					} 
					else
						break;
				}
				tmp_stack.push(ol);
				break;
			case NEWLINE:
				while (!tmp_stack.empty()) {
					tmp = tmp_stack.pop();
					if (tmp.type == LBRACKET)
						throw "Unbalanced brackets";
					else {
						switch (tmp.type) {
							case ROT:
								expr.push({PROT, "", 0});
								break;
							case OP_ADD:
								expr.push({ADD, "", 0});
								break;
							case OP_XOR:
								expr.push({XOR, "", 0});
								break;
							case OP_CONC:
								expr.push({CONC, "", 0});
								break;
							case ID:
								expr.push({CALL, tmp.value, 0});
								break;
							default:
								throw curr_lex;
						}
					}
				}
				fin = true;
				break;
			default:
				throw curr_lex;
		}
		if(!fin)
			gl();
	}
	return expr.get_stack();
}

config Parser::analyze() {
	string name[] = { "r", "n", "ks", "F", "K", "I", "R" };
	Names_ID expr[] = { ROUND_NUM, BLOCK_LEN, KEY_LEN, FUNC, KEY, I_CONST, RIGHT_PART };
	gl();
	config cfg;
	map<string, pair<size_t*, size_t> > spe;
	while(curr_type != EF) {
		while(curr_type == NEWLINE)
			gl();
		if(curr_type == EF)
			break;
		if(curr_type != ID)
			throw curr_lex;
		else {
			Names_ID b = NONE;
			int acc = 0;
			for (auto c:name) {
				if (curr_value == c) {
					b = expr[acc];
					break;
				}
				acc++;
			}
			size_t* round;
			switch(b) {
				case ROUND_NUM:
					cout << "\nr\n";
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					gl();
					if(curr_type != NUMBER)
						throw curr_lex;
					else
						cfg.r = atois(curr_value);
					break;
				case BLOCK_LEN:
					cout << "\nn\n";
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					gl();
					if(curr_type != NUMBER)
						throw curr_lex;
					else
						cfg.n = atois(curr_value);
					break;
				case KEY_LEN:
					cout << "\nks\n";
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					gl();
					if(curr_type != NUMBER)
						throw curr_lex;
					else
						cfg.k = atois(curr_value);
					break;
				case I_CONST:
					cout << "\nI\n";
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					gl();
					if(curr_type != LBRACE)
						throw curr_lex;
					round = new size_t[cfg.r];
					for(size_t i = 0; i < cfg.r; ++i) {
						gl();
						if(curr_type != NUMBER) {
							delete[] round;
							throw curr_lex;
						} 
						else
							round[i] = atois(curr_value);
						if(i < cfg.r - 1) {
							gl();
							if (curr_type != COMMA) {
								delete[] round;
								throw curr_lex;
							}
						}
					}
					gl();
					if(curr_type != RBRACE) {
						delete[] round;
						throw curr_lex;
					}
					cfg.I = round;
					break;
				case KEY:
					cout << "\nK\n";
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					cfg.K = big_expr(cf, true);
					break;
				case FUNC:
					cout << "\nF\n";
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					cfg.F = big_expr(cf, false);
					break;
				case NONE:
					string str = curr_value;
					gl();
					if(curr_type != ASSIGN)
						throw curr_lex;
					gl();
					if(curr_type != LBRACE)
						throw curr_lex;
					stack<size_t> nums;
					gl();
					while(curr_type == NEWLINE)
						gl();
					while(curr_type == NUMBER) {
						nums.push(atois(curr_value));
						gl();
						while(curr_type == NEWLINE)
							gl();
					}
					if(curr_type != RBRACE)
						throw curr_lex;
					if(spe.find(str) == spe.end())
						spe[str] = nums.get_stack();
					else
						throw "Twice!";
					break;
			}
			gl();
		}
	}
	cfg.SPE = spe;
	return cfg;
}

enum in_types {
    FILENAME,
    PASSWORD,
    MODE_E,
    MODE_D,
    INPUT
};

enum mode {
    ENC,
    DEC
};

struct input_data {
    string filename;
    string password;
    mode operation;
};

uint64_t feistel_dec(config & cfg, uint64_t block, uint64_t key) {
    size_t rounds = cfg.r;
    uint32_t left = (block >> 32) & 0xFFFFFFFFu;
    uint32_t right0;
    uint32_t right = block & 0xFFFFFFFFu;
    for(size_t i = 16; i != 0; --i) {
        right0 = right;
        right = left;
        uint64_t k = cfg.round_key(key, i - 1);
        uint32_t f = cfg.exec_F(left, k);
        left = right0 ^ f;
    }
    uint64_t out = left;
    out = out << 32;
    out = out ^ right;
    return out;
}

uint64_t feistel_enc(config & cfg, uint64_t block, uint64_t key) {
    size_t rounds = cfg.r;
    uint32_t left = (block >> 32) & 0xFFFFFFFFu;
    uint32_t left0;
    uint32_t right = block & 0xFFFFFFFFu;
    for(size_t i = 0; i < rounds; ++i) {
        left0 = left;
        left = right;
        uint64_t k = cfg.round_key(key, i);
        uint32_t f = cfg.exec_F(right, k);
        right = left0 ^ f;
		cout << i << ": " << hex << bitset<32>(left).to_ullong();
		cout << ' '       << hex << bitset<32>(right).to_ullong() << endl;
    }
    uint64_t out = left;
    out = out << 32;
    out = out ^ right;
    return out;
}

bool perform_block(config & cfg, ifstream & in, ofstream & out, uint64_t key, mode m) {
    uint64_t in_block = 0;
    const int eof = char_traits<char>::eof();
    size_t bs = (cfg.n + 7)/ 8;
    size_t i = 0;
    bool full = true;
    for(; i < bs; ++i) {
        int c = in.get();
        if(c != eof) {
            in_block = in_block << 8;
            in_block = in_block ^ (static_cast<uint64_t>(c) & 0xFFu);
        } else {
            break;
        }
    }
    if(i < bs) {
        full = false;
        uint64_t fill = bs - i;
        for(; i < bs; ++i) {
            in_block = in_block << 8;
            in_block = in_block ^ (fill & 0xFFu);
        }
    }
    if(bs < 8)
        in_block = in_block << 8 * (8 - bs);
    uint64_t out_block = m == ENC ? feistel_enc(cfg, in_block, key) : feistel_dec(cfg, in_block, key);
    for(i = 0; i < bs; ++i) {
        uint8_t oc = static_cast<uint8_t>((out_block >> 8 * (7 - i)) & 0xFFu);
        if(oc == bs - i)
            break;
        out << static_cast<char>(oc);
    }
}

uint64_t derive_key(string & password) {
    uint64_t hash = 0;
    for (auto c : password) {
        hash = 2147483647 * hash + static_cast<uint64_t >(c);
    }
    return hash;
}

void cfgexec(config & cfg, string & filename, string & password, mode m) {
    string outfile = filename + (m == ENC ? ".enc" : ".dec");
    ifstream in(filename);
    ofstream out(outfile);
    if(!in.is_open())
        throw "Couldn't open input file";
    if(!out.is_open())
        throw "Couldn't open output file";
    uint64_t k = derive_key(password);
    bool full = false;
    while(in.good())
        full = perform_block(cfg, in, out, k, m);
    if(full)
        perform_block(cfg, in, out, k, m);
}

class argparser {
    int argcount;
    int cpos;
    char** argvector;
   	map<string, in_types> key_to_type;
    string next_lex();
    void fill_in_types(map<string, in_types>& m);
public:

    argparser(int argc, char ** argv) : argcount(argc), cpos(0), argvector(argv) { fill_in_types(key_to_type); };

    input_data yield();
};

string argparser::next_lex() {
    if(cpos <  argcount) {
        return string(argvector[cpos++]);
    } else {
        throw out_of_range("No more lexems");
    }
}

void argparser::fill_in_types(map<string, in_types> & m) {
    m.clear();
    m["-f"] = m["-file"] = m["-filename"] = FILENAME;
    m["-p"] = m["-pwd"] = m["-password"] = PASSWORD;
    m["-e"] = m["-enc"] = m["-encrypt"] = MODE_E;
    m["-d"] = m["-dec"] = m["-decrypt"] = MODE_D;
}

input_data argparser::yield() {
    in_types in = INPUT;
    input_data data;
    while(cpos < argcount) {
        string lex = next_lex();
        if(lex.find('-') == 0) {
            if(key_to_type.find(lex) != key_to_type.end()) {
                in = key_to_type[lex];
            } else {
                throw "No such key \'" + lex + "\'";
            }
        } else {
            in = INPUT;
        }
        switch(in) {
            case FILENAME:
                try {
                    data.filename = next_lex();
                } catch(out_of_range & e) {
                    cerr << "Param list not long enough" << endl;
                    throw;
                }
                break;
            case PASSWORD:
                try {
                    data.password = next_lex();
                } catch(out_of_range & e) {
                    cerr << "Param list not long enough" << endl;
                    throw;
                }
                break;
            case MODE_D:
                data.operation = DEC;
                break;
            case MODE_E:
                data.operation = ENC;
                break;
            case INPUT:
                break;
        }
    }
    return data;
}

int main(int argc, char** argv)
{
	try
	{
		argparser parser(argc, argv);
		input_data data = parser.yield();
		Parser pars("config1.txt");
		config cfig = pars.analyze();
		//cfig.print_SPE();
		cfig.print_F();
		cout << endl << endl;
		cfig.print_K();
		cfgexec(cfig, data.filename, data.password, data.operation);
	    cfig.freecfg();
		return 0;
	}
	catch (int c) {
		cout << "unexpected symbol " << static_cast<char>(c) << endl;
		return 1;
		}
	catch (Lex l) {
		cout << "unexpected lexeme" << endl;
		return 1;
		}
	catch (const char* source) {
		cout << source << endl;
		return 1;
		}
}
