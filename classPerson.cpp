#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

string PrintNames(const vector <string>& str){ 
	string ans = str[0];
	set <string> s;
	for (const string& item : str){
		s.insert(item);
	}
	if (s.size() == 1) return ans;
	if ((str.size() > 1)){
		ans += " (";
		for (int i = 1; i < str.size(); ++i){
			if (i == str.size()-1){
				ans += str[i];
				ans += ")";
				break;
			}
			if (str[i] == str[i+1]){
				continue;
			}
			ans += str[i];
			ans += ", ";
		}
	}

	return ans;
}


string FindNameByYear(const map<int, string>& names, int& year) {
  string name;  
  int curr_year = year;
  for (const auto& item : names) {
    if (item.first <= curr_year) {
      name = item.second;
      year = item.first;
    } else {
      break;
    }
  }

  return name;
}

class Person {
public:
  void ChangeFirstName(int year, const string& first_name) {
    first_names[year] = first_name;
  }
  void ChangeLastName(int year, const string& last_name) {
    last_names[year] = last_name;
  }

  string GetFullName(int year) {
    const string first_name = FindNameByYear(first_names, year);
    const string last_name = FindNameByYear(last_names, year);

    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    } else {
      return first_name + " " + last_name;
    }
  }
  string GetFullNameWithHistory(int year) {

	vector <string> names;
	int curr_year = year;
    string first_name = FindNameByYear(first_names, curr_year);
	while (first_name.empty() != 1){
	    names.push_back(first_name);
		--curr_year;
	    first_name = FindNameByYear(first_names, curr_year);
	}

	vector <string> surnames;
	curr_year = year;
    string last_name = FindNameByYear(last_names, curr_year);
	while (last_name.empty() != 1){
		surnames.push_back(last_name);
		--curr_year;
		last_name = FindNameByYear(last_names, curr_year);
	}

	if (names.empty() && surnames.empty()) {
	      return "Incognito";

	} else if (surnames.empty()) {
	    	return PrintNames(names) + " with unknown last name";

    } else if (names.empty()) {
	    	return PrintNames(surnames) + " with unknown first name";

	} else {
	        return PrintNames(names) + ' ' + PrintNames(surnames);
	}
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};
