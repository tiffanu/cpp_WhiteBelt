#include <iostream>
#include <map>
#include <vector>
#include <string>
using namespace std;

int main(){
	int n;
	cin >> n;

	map<string, string> dict;

	string command;
	string capital, country, old_capital, new_capital, old_country_name, new_country_name;

	for (int i=0; i < n; i++){
		cin >> command;
		if (command == "CHANGE_CAPITAL"){
			cin >> country >> new_capital;
			if (dict[country] == ""){
				dict[country] = new_capital;
				cout << "Introduce new country " << country << " with capital " << new_capital << endl;
			} else if (dict[country] == new_capital){
				cout << "Country " << country << " hasn't changed its capital" << endl;
			} else {
				old_capital = dict[country];
				dict[country] = new_capital;
				cout << "Country " << country << " has changed its capital from " << old_capital << " to " << new_capital << endl;
			}
		} else if (command == "RENAME"){
			cin >> old_country_name >> new_country_name;
			if (old_country_name == new_country_name){
				cout << "Incorrect rename, skip" << endl;
			} else if (dict[old_country_name] == ""){
			    dict.erase(old_country_name);
				cout << "Incorrect rename, skip" << endl;
			} else if (dict[new_country_name] != ""){
			    dict.erase(new_country_name);                       // maybe this line is excess
				cout << "Incorrect rename, skip" << endl;
			} else {
				capital = dict[old_country_name];
				dict.erase(old_country_name);
				dict[new_country_name] = capital;
				cout << "Country " << old_country_name << " with capital " << capital << " has been renamed to " << new_country_name << endl;
			}
		} else if (command == "ABOUT"){
			cin >> country;
			if (dict[country] == ""){
				cout << "Country " << country << " doesn't exist" << endl;
				dict.erase(country);
			} else {
				cout << "Country " << country << " has capital " << dict[country] << endl;
			}
		} else if (command == "DUMP"){
			if (dict.size() == 0){
				cout << "There are no countries in the world" << endl;
			} else {
				for (const auto& pair : dict){
					cout << pair.first << '/' << pair.second << ' ';
				}
				cout << endl;
			}
		}
	}
	return 0;
}
