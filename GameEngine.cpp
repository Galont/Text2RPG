#include "GameEngine.h"
//Wolfie is now A Master Wizard at Code
GameEngine::GameEngine (FILE *fp) {
    vector <string> list_rooms = {};
    vector <string> list_description = {};

    char buf[1024];
    while (fgets(buf, 1023, fp)) {
        buf[strlen(buf) - 1] = '\0';
        // maybe convert to a switch statement?
        if (buf[0] == 'r') {
            if (list_rooms.size() != list_description.size()) { // one description per room required
                fprintf(stderr, "%s: Room has no description\n", list_rooms.back().c_str());
                exit(1);
            }
            list_rooms.push_back(string(buf + 2)); // skip the 'r' and the ' '
        }
        else if (buf[0] == 'd') { // description
            if (list_rooms.size() == 0) {
                fprintf(stderr, "Can't have a description without rooms\n");
                exit(1);
            }
            if (list_rooms.size() == list_description.size()) { // not first description segment
                string temp = list_description.back() + string("\t\t") + string(buf + 2) + string("\n");
                list_description.pop_back();
                list_description.push_back(temp);
            }
            else if (list_rooms.size() == list_description.size() + 1) {
                list_description.push_back(string("\t\t") + string(buf + 2) + string("\n")); // first description segment
            } else {
                fprintf(stderr, "%s: Room has no description\n", list_rooms.back().c_str());
                exit(1);
            }
        }
    }
    if (list_rooms.size() != list_description.size()) { // one description per room required
        fprintf(stderr, "%s: Room has no description\n", list_rooms.back().c_str());
        exit(1);
    }
    for (size_t i = 0; i < list_rooms.size(); i++) {
        string room = list_rooms.at(i);
        string description = list_description.at(i);
        fprintf(stdout, "%zd: %s\n", i + 1, room.c_str());
        fprintf(stdout, "%s", description.c_str());
    }
}
