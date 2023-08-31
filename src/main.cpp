#include <bits/stdc++.h>
#include <cctype>
#include <iostream>
#include <sstream>
#include <filesystem>

using namespace std;
namespace fs = std::filesystem;

vector<string> explode(string s, char delim = ' ') {
    vector<string> result;
    istringstream stream(s);

    string token;
    while (getline(stream, token, delim)) {
        result.push_back(token);
    }

    return result;
}

string toLowerCase(string characters) {
    for (char &character : characters) {
        character = tolower(character);
    }

    return characters;
}

string pad(string s) {
    if (s.length() >= 2) {
        return s;
    }

    return string(1, '0').append(s);
}

string convertHours(string hours, string period = "pm") {
    const int HALF_DAY_HOURS = 12;
    const int FULL_DAY_HOURS = 24;

    string toLowerCasePeriod = toLowerCase(period);
    int currentTime = stoi(hours) + HALF_DAY_HOURS;
    if (period.find("pm") != string::npos) {
        if (currentTime == FULL_DAY_HOURS) {
            return to_string(HALF_DAY_HOURS);
        }

        return to_string(currentTime);
    }

    if (currentTime >= FULL_DAY_HOURS) {
        return to_string(currentTime - FULL_DAY_HOURS);
    }

    return hours;
}

string timeConversion(string s) {
    string period = s.substr(s.length() - 2);
    s.erase(s.length() - 2);
    vector<string> result = explode(s, ':');

    string hours = result[0];
    period = toLowerCase(period);
    hours = convertHours(hours, period);

    ostringstream output;
    output << pad(hours) << ":" << result[1] << ":" << result[2];
    return output.str();
}

int main() {
    ifstream fin("../test/test.txt");
    ofstream fout("../out/output.txt", ios::trunc);

    if (!fs::exists("../out")) {
        fs::create_directory("../out");
    }

    cout << "Welcome to time conversion CLI" << endl;
    cout << "Type the time that you want convert or type 'test' to run test routine" << endl << endl;

    string s;
    getline(cin, s);

    if (s == "test") {
        string line;
        while(getline(fin, line)) {
            string result = timeConversion(line);
            fout << result << endl;
        }

        fin.close();
        fout.close();

        return 0;
    }

    string result = timeConversion(s);
    fout << result << endl;

    fout.close();
    fin.close();

    return 0;
}