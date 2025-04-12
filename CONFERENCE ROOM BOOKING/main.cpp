#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>

using namespace std;

class building{
    vector<string> conference_rooms;
    public:
    building() {}
    string building_name;
    building(string b){
        building_name=b;
    }
    void add_confroom(string s){
        conference_rooms.push_back(s);
    }
    vector<string> get_confroom(){
        return conference_rooms;
        
    }


};

class floor{
    vector<string> conference_rooms;
    public:
    floor() {}
    string floor_name;
    floor(string f){
        floor_name=f;
    }
    void add_confroom(string s){
        conference_rooms.push_back(s);
    }
    vector<string> get_confroom(){
        return conference_rooms;
        
    }


};

class conference_room{
    public:
    conference_room() {}
    string cid;
    string floor_name;
    string building_name;
    vector <bool> slots;
    conference_room(string id, string floor, string building){
        cid=id;
        floor_name=floor;
        building_name=building;
        slots.resize(24, false);
    }
    void book(pair<int,int> slot){
        for(int i=slot.first;i<=slot.second;i++){
            slots[i-1]=true;
        }
    }
    bool is_available(pair<int,int> slot){
        for(int i=slot.first;i<=slot.second;i++){
            if(slots[i-1]==true){
                return false;
            }
        }
        return true;
        }
    void cancel_booking(pair<int,int> slot){
        for(int i=slot.first;i<=slot.second;i++){
            slots[i-1]=false;
        }
    }

     
};


class BOOKING{
    public:
    unordered_map <string, conference_room> all_conf_rooms;
    set <pair<string,pair<int,int>>> bookings_made;
    unordered_map<string,building> all_buildings;
    unordered_map<string,floor> all_floors;

    void add_building(string n){
        all_buildings[n]=building(n);

    }
    void add_floor(string n){
        all_floors[n]=floor(n);
    }
    void add_confroom(string b, string f, string cid){
        
        all_conf_rooms[cid]=conference_room(cid, f, b);
        all_floors[f].add_confroom(cid);
        all_buildings[b].add_confroom(cid);

    }
    void book(pair<int,int> slot, string cid, string b_name, string f_name){
        if(!all_conf_rooms[cid].is_available(slot)){
            cout<<"No sorry this conference room is already booked\n";
            return;
        }
        all_conf_rooms[cid].book(slot);
        bookings_made.insert(make_pair(cid,slot));
    }
    void cancel_booking(pair<int,int> slot, string cid, string b_name, string f_name){
        
        if(bookings_made.find(make_pair(cid,slot))!=bookings_made.end()){
            bookings_made.erase(make_pair(cid,slot));
            
        }
        all_conf_rooms[cid].cancel_booking(slot);
        
    }
    void list_booking(){
        for(auto x: bookings_made){
            conference_room c= all_conf_rooms[x.first];
            pair <int, int> slot=x.second;
            cout<< slot.first<<":"<<slot.second<<"  "<< c.building_name <<"   "<< c.floor_name<<"   "<< c.cid << endl;
        }
    }
    void search(pair<int,int> slot, string b, string f ){
        vector<string> conf_available;
        
        for(auto x: all_floors[f].get_confroom()){
            if(all_conf_rooms[x].is_available(slot)){
                conf_available.push_back(x);
            }
        }
        cout<< "[";
        for(int i=0;i<conf_available.size();i++){
            cout<<" "<<conf_available[i];
        }
        cout<<" ]"<<endl;
    }
    void search(pair<int,int> slot, string b){
        vector<string> conf_available;
        
        for(auto x: all_buildings[b].get_confroom()){
            if(all_conf_rooms[x].is_available(slot)){
                conf_available.push_back(x);
            }
        }
        cout<< "[";
        for(int i=0;i<conf_available.size();i++){
            cout<<" "<<conf_available[i];
        }
        cout<<" ]"<<endl;
    }
    void search(pair<int,int> slot, string b,string f, string cid){
        conference_room c= all_conf_rooms[cid];
        if(c.is_available(slot)){
            cout<< "YES! it is available for booking"<<endl;
        }
        else{
            cout<<"No sorry this conference room is already booked\n";
        }
    }

};


int main() {
    BOOKING bookingSystem;

    // Add buildings and floors
    bookingSystem.add_building("AlphaTower");
    bookingSystem.add_floor("Floor1");
    bookingSystem.add_floor("Floor2");

    // Add conference rooms
    bookingSystem.add_confroom("AlphaTower", "Floor1", "CR101");
    bookingSystem.add_confroom("AlphaTower", "Floor1", "CR102");
    bookingSystem.add_confroom("AlphaTower", "Floor2", "CR201");

    // Search availability before booking
    cout << "Search available rooms on Floor1 (9AM to 11AM):\n";
    bookingSystem.search({9, 11}, "AlphaTower", "Floor1");

    // Book a room
    cout << "\nBooking CR101 on Floor1 from 9AM to 11AM...\n";
    bookingSystem.book({9, 11}, "CR101", "AlphaTower", "Floor1");

    // Try booking the same room again
    cout << "\nTrying to book CR101 again (same slot)...\n";
    bookingSystem.book({9, 11}, "CR101", "AlphaTower", "Floor1");

    // Search again
    cout << "\nSearch available rooms on Floor1 (9AM to 11AM):\n";
    bookingSystem.search({9, 11}, "AlphaTower", "Floor1");

    // Cancel the booking
    cout << "\nCancelling booking of CR101 (9AM to 11AM)...\n";
    bookingSystem.cancel_booking({9, 11}, "CR101", "AlphaTower", "Floor1");

    // List all bookings
    cout << "\nCurrent bookings:\n";
    bookingSystem.list_booking();

    // Final availability check
    cout << "\nSearch available rooms on Floor1 again (9AM to 11AM):\n";
    bookingSystem.search({9, 11}, "AlphaTower", "Floor1");

    return 0;
}
