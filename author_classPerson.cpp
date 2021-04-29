#include <map>
#include <string>
#include <iostream>
#include <vector>
#include <set>

using namespace std;

string PrintNames(const vector <string>& str){ // str - хронологически наоборот
	string ans = str[0];
	set <string> s;
	for (const string& item : str){
		s.insert(item);
	}
	if (s.size() == 1) return ans;
	if ((str.size() > 1)){
		ans += " (";
		int i = 1;
		while (str[i] == str[0]){
			++i;
		}
		for (i; i < str.size(); ++i){
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



// если имя неизвестно, возвращает пустую строку
string FindNameByYear(const map<int, string>& names, int& year) {
  string name;  // изначально имя неизвестно
  int curr_year = year;
  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= curr_year) {
      name = item.second;
      year = item.first;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
      break;
    }
  }

  return name;
}

// если имя неизвестно, возвращает пустую строку
string FindNameByYearForFirst(const map<int, string>& names, int year) {
  string name;  // изначально имя неизвестно
  // перебираем всю историю по возрастанию ключа словаря, то есть в хронологическом порядке
  for (const auto& item : names) {
    // если очередной год не больше данного, обновляем имя
    if (item.first <= year) {
      name = item.second;
    } else {
      // иначе пора остановиться, так как эта запись и все последующие относятся к будущему
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
    // получаем имя и фамилию по состоянию на год year
    const string first_name = FindNameByYearForFirst(first_names, year);
    const string last_name = FindNameByYearForFirst(last_names, year);

    // если и имя, и фамилия неизвестны
    if (first_name.empty() && last_name.empty()) {
      return "Incognito";

    // если неизвестно только имя
    } else if (first_name.empty()) {
      return last_name + " with unknown first name";

    // если неизвестна только фамилия
    } else if (last_name.empty()) {
      return first_name + " with unknown last name";

    // если известны и имя, и фамилия
    } else {
      return first_name + " " + last_name;
    }
  }
  string GetFullNameWithHistory(int year) {

	// разбираемся с именем
	vector <string> names;
	int curr_year = year;
    // получить все имена и фамилии по состоянию на конец года year
    string first_name = FindNameByYear(first_names, curr_year);
	while (first_name.empty() != 1){
	    names.push_back(first_name);
		--curr_year;
	    first_name = FindNameByYear(first_names, curr_year);
	}

	// с фамилией
	vector <string> surnames;
	curr_year = year;
	// получить все имена и фамилии по состоянию на конец года year
    string last_name = FindNameByYear(last_names, curr_year);
	while (last_name.empty() != 1){
		surnames.push_back(last_name);
		--curr_year;
		last_name = FindNameByYear(last_names, curr_year);
	}

	if (names.empty() && surnames.empty()) {
	      return "Incognito";

	    // если неизвестно только имя
	} else if (surnames.empty()) {
	    	return PrintNames(names) + " with unknown last name";

	    // если неизвестна только фамилия
    } else if (names.empty()) {
	    	return PrintNames(surnames) + " with unknown first name";

	    // если известны и имя, и фамилия
	} else {
	        return PrintNames(names) + ' ' + PrintNames(surnames);
	}
  }

private:
  map<int, string> first_names;
  map<int, string> last_names;
};



