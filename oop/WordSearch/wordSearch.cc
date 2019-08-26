#include <iostream>
#include <vector>
#include <set>
#include <memory>
#include <sstream>
#include <map>
#include <algorithm>
#include <fstream>
#include <string>

using namespace std;


class Query_base;
class Query;

class TextQuery
{
	public:
	void read_file(std::ifstream &is) {store_file(is); build_map();}
	set<size_t> run_query(const string &query_word)
	{
		auto loc = word_map.find(query_word);
		
		if(loc == word_map.end())
			return set<size_t>();
		else
			return loc->second;
	}
	
	string text_line(size_t line)
	{
		if(line < lines_of_text.size())
			return lines_of_text[line];
		return NULL;
	}
	
	void store_file(std::ifstream& is)
	{
		string textline;
		while(getline(is,textline))
		{
			lines_of_text.push_back(textline);
			//cout << textline << endl;
		}
	}
	
	void build_map()
	{
		for(size_t line_num=0; line_num!=lines_of_text.size(); ++line_num)
		{
			istringstream line(lines_of_text[line_num]);
			string word;
			while(line>>word)
			{
				word_map[word].insert(line_num);
			}
		}
	}
	
	std::vector<std::string> lines_of_text;
	std::map<std::string, std::set<size_t> > word_map;
};


class Query_base
{
	public:
	virtual set<size_t> eval(TextQuery *t) = 0;
};

class WordQuery: public Query_base
{
	public:
	WordQuery(const string &s):str(s){cout << "WordQuery()" << endl;}
	set<size_t> eval(TextQuery *t) override
	{
		set<size_t> tmp = t->run_query(str);
		//for (auto i = tmp.begin(); i != tmp.end(); i++)
		//	cout << *i << endl;
		return tmp;
	}
	
	~WordQuery(){cout << "~WordQuery" << endl;}
	
	string str;
};

class Query
{
	public:
	Query()=default;
	Query(const string &s):q(make_shared<WordQuery>(s)){}
	Query(const shared_ptr<Query_base> &p):q(p){}
	set<size_t> eval(TextQuery *t)
	{
		return q->eval(t);
	}
	
	shared_ptr<Query_base> q;
};

class AndQuery: public Query_base
{
	public:
	AndQuery(const Query &l1, const Query &r1):l(l1), r(r1){cout << "AndQuery()" << endl;}
	set<size_t> eval(TextQuery *t) override
	{
		 //for (auto iter = t->word_map.begin(); iter != t->word_map.end(); iter++)
		//{
    	//cout << iter->first << "-" << endl;
    	//}
		set<size_t> left = l.eval(t);
		set<size_t> right = r.eval(t);
		set<size_t> ret;
		set_intersection(left.begin(), left.end(), right.begin(), right.end(), inserter(ret,ret.begin()));
		return ret;
	}
	
	Query l;
	Query r;
	~AndQuery(){cout << "~AndQuery" << endl;}
};


inline Query operator& (const Query &l, const Query &r)
{
	return Query(make_shared<AndQuery>(l, r));
}


int main(void)
{
	ifstream is("text.txt");
    TextQuery tq;
    tq.read_file(is);
    
    Query q = Query("eval") & Query("file") & Query("s") & Query("ds");
    
    cout << "=======start========" << endl;
    set<size_t> locs = q.eval(&tq);
    size_t size = locs.size();

	auto it = locs.begin();
	for(; it!=locs.end(); ++it)
		cout<< (*it)+1 << "\t" << tq.text_line(*it) << endl;
	cout << "===========end========" << endl;
}
