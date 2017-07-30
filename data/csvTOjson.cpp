#include <fstream>
#include <unordered_map>
#include <string>
#include <sstream>

using namespace std;

struct Details
{
	Details() {}
	Details(string pt, string ya, string pb, double gs) : Publisher(pb), Year(ya), Platform(pt), Global_Sales(gs){ }
	string Platform; // 3
	string Year; // 4
	string Publisher; // 6
	double Global_Sales; // 11
};

unordered_map<string, unordered_map<string, Details> > genres;

string csvLine(istream & is) {
	string line;
	while (is.peek() != '\n') {
		if (is.peek() == '"') {
			line += is.get();
			if (is.peek() != '"') {
				while (true) {
					if (is.peek() == '"') {
						line += is.get();
						if (is.peek() != '"') {
							break;
						}
					}
					line += is.get();
				}
			}
			else line += is.get();
		}
		else line += is.get();
	}
	is.get();
	return line;
}

string getID(const string& line, int col) {
	bool first = true;
	string id;
	char c;
	stringstream ss(line);
	int last = 1; //start from 1
	if (!first) id += ',';
	while (last != col) {
		ss.get(c);
		while (c != ',') {
			if (c == '"') {
				if (ss.peek() == '"') ss.get(c);
				else {
					while (true) {
						ss.get(c);
						if (c == '"') {
							if (ss.peek() == '"') {
								ss.get(c);
							}
							else break;
						}
					}
				}
			}
			ss.get(c);
		}
		last++;
	}
	ss.get(c);
	while (c != ',' && !ss.eof()) {
		if (c == '"') {
			id += c;
			ss.get(c);
			if (c == '"') {}
			else {
				while (true) {
					if (c == '"') {
						id += c;
						ss.get(c);
						if (c == '"') {}
						else {
							break;
						}
					}
					id += c;
					ss.get(c);
				}
			}
		}
		else {
			id += c;
			ss.get(c);
		}
	}
	last++;
	if (first) first = false;
	return id;
}

void load() {
	ifstream ifs("vgsales.csv");
	string line;
	string genre; // 5
	string name; // 2
	string platform; // 3
	string year; // 4
	string publisher; // 6
	string global_sales; // 11
	stringstream ss;
	double gs;
	getline(ifs, line);

	while (ifs && ifs.peek() != EOF) {
		line = csvLine(ifs);
		genre = getID(line, 5);
		name = getID(line, 2);
		if (name[0] == '"') {
			name = '\\' + name.substr(0, name.size() - 1) + '\\' + '"';
		}
		platform = getID(line, 3);
		year = getID(line, 4);
		publisher = getID(line, 6);
		if (publisher[0] == '"') {
			publisher = '\\' + publisher.substr(0, publisher.size() - 1) + '\\' + '"';
		}
		global_sales = getID(line, 11);
		ss.clear();
		ss = stringstream(global_sales);
		ss >> gs;
		genres[genre][name] = Details(platform, year, publisher, gs);
	}
}

void write() {
	ofstream ofs("vgsales.json");
	ofs << "{\n";
	ofs << " \"name\": \"flare\",\n";
	ofs << " \"description\" : \"flare\",\n";
	ofs << " \"children\": [\n";
	bool first = true;
	bool firstt = true;
	unordered_map<string, unordered_map<string, Details> >::iterator ite;
	unordered_map<string, Details>::iterator itee;
	for (ite = genres.begin(); ite != genres.end(); ite++) {
		if (!first) ofs << "  },\n";
		ofs << "  {\n";
		ofs << "   \"name\": \"" << ite->first << "\",\n";
		ofs << "   \"description\": \"genre\",\n";
		ofs << "   \"children\": [\n";

		firstt = true;
		for (itee = ite->second.begin(); itee != ite->second.end(); itee++) {
			if (!firstt) ofs << "},\n";
			ofs << "    {";
			ofs << "\"name\": \"" << itee->first << "\", \"description\": \"";
			ofs << itee->second.Publisher << ", " << itee->second.Platform << ", " << itee->second.Year << "\",";
			ofs << "\"size\": " << itee->second.Global_Sales;
			if (firstt) firstt = false;
		}
		ofs << "}\n";

		ofs << "   ]";
		if (first) first = false;
	}
	ofs << "  }\n";
	ofs << " ]\n";
	ofs << "}";
}

int main() {
	load();
	write();
	return 0;
}