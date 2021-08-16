#include <iostream>
#include <iomanip>
#include <string>
#include <set>
#include <vector>
#include <map>

using namespace std;

class Date {
public:
  int GetYear() const{
	  return year;
  }
  int GetMonth() const{
	  return month;
  }
  int GetDay() const{
	  return day;
  }

  Date(int new_year, int new_month, int new_day){
	  year = new_year;
	  month = new_month;
	  day = new_day;
  }

private:
  int day;
  int month;
  int year;
};

bool operator<(const Date& lhs, const Date& rhs){     // overload operator< for Data so we
	if (lhs.GetYear() == rhs.GetYear()){              // can create std::map<Date, *smth*>
		if (lhs.GetMonth() == rhs.GetMonth()){
			return lhs.GetDay() < rhs.GetDay();
		}
		return lhs.GetMonth() < rhs.GetMonth();
	}
	return lhs.GetYear() < rhs.GetYear();
}

void PrintDate(Date date){                        // i create function but also could
	cout << setfill('0');                         // overload operator<< for Date 
	cout << setw(4) << date.GetYear() << '-';
	cout << setfill('0');
	cout << setw(2) << date.GetMonth() << '-';
	cout << setfill('0');
	cout << setw(2) << date.GetDay();
}

void _isvalidFormat(const string& date_str){       // first checking for valid format
	int num_delim = 0;
	string error = "Wrong date format: " + date_str;

	for (const char& c : date_str){
		if (c == '-') num_delim++;
		if (c != '-' && c != '+' && (c < '0' || c > '9')){
			throw runtime_error(error);
		}
	}

	if (num_delim < 2 || num_delim > 5) throw runtime_error(error); 
}

Date StrToDate(const string& date_str){ // valid format is YYYY-MM-DD

	int year, month, day;

	stringstream stream(date_str);
	string error = "Wrong date format: " + date_str;
	_isvalidFormat(date_str);

	if (stream.peek() == '-'){
		stream.ignore(1);
		if (stream.peek() == '-' || stream.peek() == '+' || stream.peek() == EOF) throw runtime_error(error);
		stream >> year;
		year *= -1;
	} else {
		stream >> year;
	}
	if (stream.peek() != '-' || stream.peek() == EOF) throw runtime_error(error);
	stream.ignore(1);
	if (stream.peek() == EOF) throw runtime_error(error);

	if (stream.peek() == '-'){
		stream.ignore(1);
		if (stream.peek() == '-' || stream.peek() == EOF) throw runtime_error(error);
		stream >> month;
		month *= -1;
	} else {
		stream >> month;
	}
	if (stream.peek() != '-' || stream.peek() == EOF) throw runtime_error(error);
	stream.ignore(1);
	if (stream.peek() == EOF) throw runtime_error(error);

	if (stream.peek() == '-'){
		stream.ignore(1);
		if (stream.peek() == '-' || stream.peek() == EOF) throw runtime_error(error);
		stream >> day;
		day *= -1;
	} else {
		stream >> day;
	}
	if (stream.peek() != EOF) throw runtime_error(error);

	if (month < 1 || month > 12){
		error = "Month value is invalid: " + to_string(month);
		throw runtime_error(error);
	}

	if (day < 1 || day > 31){
		error = "Day value is invalid: " + to_string(day);
		throw runtime_error(error);
	}

	Date date(year, month, day);
	return date;
}

class Database {
public:

  void AddEvent(const Date& date, const string& event){
	  events[date].insert(event);
  }

  bool DeleteEvent(const Date& date, const string& event){
	  if (events[date].count(event)){
		  events[date].erase(event);
		  return 1;
	  } else {
		  return 0;
	  }
  }

  int DeleteDate(const Date& date){
	  int count = events[date].size();
	  events.erase(date);
	  return count;
  }

  void Find(const Date& date) const {
	  if (events.count(date)){
		  set<string> value = events.at(date);
		  for (const string& str : value){
			  cout << str << endl;
		  }
	  }
  }

  void Print() const {
	  for (const auto& [key, events_vector] : events){
		  for (const string& str : events_vector){
			  PrintDate(key);
			  cout << ' ' << str << endl;
		  }
	  }
  }

private:
  map<Date, set<string>> events;
};

int main() {
  Database db;

  try {
	  string line;
	  while (getline(cin, line)) {

		  if (line.empty()) continue;

		  string command = line.substr(0, line.find(' '));
		  line.erase(0, line.find(' ') + 1);

		  if (command == "Add"){

			  string date_str = line.substr(0, line.find(' '));
			  line.erase(0, line.find(' ') + 1);

			  string event = line.substr(0, line.find(' '));
			  line.erase(0, line.find(' ') + 1);


			  Date date = StrToDate(date_str);
			  db.AddEvent(date, event);


		  } else if (command == "Del"){

			  string date_str = line.substr(0, line.find(' '));
			  Date date = StrToDate(date_str);

			  if (line.find(' ') == string::npos){

				  cout << "Deleted " << db.DeleteDate(date) << " events" << endl;

			  } else {

				  line.erase(0, line.find(' ') + 1);
				  string event = line.substr(0, line.find(' '));
				  line.erase(0, line.find(' ') + 1);

				  if (db.DeleteEvent(date, event)){
					  cout << "Deleted successfully" << endl;
				  } else {
					  cout << "Event not found" << endl;
				  }

			  }

		  } else if (command == "Find"){

			  string date_str = line.substr(0, line.find(' '));
			  line.erase(0, line.find(' ') + 1);

			  Date date = StrToDate(date_str);
			  db.Find(date);

		  } else if (command == "Print"){

			  db.Print();

		  } else {

			  cout << "Unknown command: " << command << endl;
			  break;

		  }
	  }
  } catch (exception& ex) {
	  cout << ex.what();
	  return 0;
  }

}

