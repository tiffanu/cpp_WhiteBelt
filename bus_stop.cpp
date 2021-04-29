#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

int main() {
	int n;
	cin >> n;

	map<int, string> number_of_bus;
	map<string, vector<string>> bus_stop;

	string command;
	string bus, stop;
	int stop_count;

	int number = 0;
	for (int i = 0; i < n; ++i){
		cin >> command;
		if (command == "NEW_BUS"){
			cin >> bus >> stop_count;
			number_of_bus[number] = bus;
			for (int j=0; j<stop_count; ++j){
				cin >> stop;
				bus_stop[bus].push_back(stop);
			}
			number++;

		} else if (command == "BUSES_FOR_STOP"){
			cin >> stop;
			int count_bus = 0;
			for (const auto& pair : number_of_bus){
				for (const string& s : bus_stop[pair.second]){
					if (s == stop){
						cout << pair.second << ' ';
						count_bus++;
						break;
					}
				}
			}
			if (count_bus == 0){
				cout << "No stop" << endl;
				continue;
			}
			cout << endl;

		} else if (command == "STOPS_FOR_BUS"){
			cin >> bus;
			if (bus_stop.count(bus) == 0) {
				cout << "No bus" << endl;
				continue;
			}
			for (const string& cur_stop : bus_stop[bus]){
				cout << "Stop " << cur_stop << ":";
				int count_bus = 0;
				for (const auto& pair : number_of_bus){
					if (pair.second == bus) continue;
					for (const string& s : bus_stop[pair.second]){
						if (s == cur_stop){
							cout << ' ' << pair.second;
							count_bus++;
							break;
						}
					}
				}
				if (count_bus == 0) {
					cout << " no interchange" << endl;
					continue;;
				}
				cout << endl;
			}

		} else {                                        // command == ALL_BUSES
			if (bus_stop.size() == 0) {
				cout << "No buses" << endl;
				continue;
			}
			for (const auto& pair : bus_stop){
				cout << "Bus " << pair.first << ":";
				for (const string& s : pair.second){
					cout << ' ' << s;
				}
				cout << endl;
			}
		}
	}
	return 0;
}
