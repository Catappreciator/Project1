//NAMES: Kylie Norosky, Ada Whitefield
//PROGRAM: Project01, Lib_info
//DESCRIPTION:

//I hate Git rn
#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Song { 
    string title;
    int time;  // could also be a string
};

struct Album {
    map <int, Song > songs;
    string name;
    int time;
    int nsongs;  // optional variable but makes it easier
};

struct Artist {
    map <string, Album > albums;
    string name;
    int time;
    int nsongs;
};

int convertToSec(string duration) {

	string minutes = "";
	string seconds = "";
	bool before = true;
	for(int i = 0; i < duration.size(); i++) {
		if(duration[i] == ':') {
			before = false;
			i++;
		}
		if(before) {
			minutes += duration[i];
		}
		else {
			seconds += duration[i];
		}
	}
    int m = stoi(minutes);
    int s = stoi(seconds);
    m *= 60;
    s += m;
   
    return s;

}

string convertToString(int seconds) {
    //divide by 60 for minutes
    int minutes = seconds / 60;
    int leftoverSec = seconds % 60; 
	stringstream ss;
	ss << minutes << ':' << setw(2) << setfill('0') << leftoverSec;

    return ss.str();
}
//Removes underscore in string variables
string stripUnderscore(string name){
    for(int i = 0; i < name.size(); i++){
		if(name[i] == '_'){
			name[i] = ' ';
		}
    }
    return name;

}

int main(int argc, char *argv[]) {
	if(argc != 2) return 1;
	//Open file from the command line argument to read in information
	ifstream fin;
	fin.open(argv[1]);
	if(fin.fail()) return 1;
	//declare read in variables
	string title;
	string artist;
	string duration;
	string album;
	string genre;
	int track;
	
	map<string, Artist> artists;
	map<string, Artist>::iterator sit; //iterates through artist
	map<string, Album>::iterator ait; //iterates through album
    

	//TODO: Add up time for both artists and albums separately
	//Use file stream to read in variables instead of cin
	while(fin >> title >> duration >> artist >> album >> genre >> track) {
		int tDuration = convertToSec(duration);
		//Immediately we can take in the string and convert to int
		//find artist, if not there insert with album
		sit = artists.find(artist); //iterator points where artist is
		if(sit == artists.end()) { //if not found
		
			//create new artist
//			cout << "New Artist: " << stripUnderscore(artist) << endl; //TODO: print formatted (spaces not '_')
			Artist theArtist;
			theArtist.name = artist; //initialized with read in artist variable
			theArtist.time = tDuration; //initialized with read in time
			theArtist.nsongs = 1; //initialized with read in number of songs

			//create new album
//			cout << "New Album: " << stripUnderscore(album) << endl; //TODO print formatted
			Album theAlbum; //create album
			//update Album attributes
			theAlbum.name = album; //initialized with read in album name
			theAlbum.time = tDuration; //initialized with read in song time
			theAlbum.nsongs = 1; //initialized with the 1 song inserted

			//create new song
			Song theSong;
			theSong.title = title; //initilized with read in song
			theSong.time = tDuration; //initialized with read in song length
				

			//connect to Album map with Song struct
			theAlbum.songs.insert(make_pair(track, theSong));
			//connect to Artist map with Album struct
			theArtist.albums.insert(make_pair(album, theAlbum));
			//insert artist 
			artists.insert(make_pair(artist, theArtist));


		}
		else { 
			//artist exists If it is there, print "Old Artist: " and the name
//			cout << "Old Artist: " << stripUnderscore(artist) << endl; 
			//increase time and songs for artist  TODO check if song was previously exiosting
			sit->second.time += tDuration;
			sit->second.nsongs++;

			//check if album exists. If it is there, print "Old Album: " and the name
			ait = sit->second.albums.find(album);
			if(ait == sit->second.albums.end()) { //album does not exist
//				cout << "New Album: " << stripUnderscore(album) << endl; //TODO formatting
				//create album
				Album theAlbum;
				theAlbum.name = album; //initialized with read in album name
				theAlbum.time = tDuration; //initialized with read in song time
				theAlbum.nsongs = 1; //initialized with the 1 song inserted

				//add album to artist
				sit->second.albums.insert(make_pair(album,theAlbum));
				ait = sit->second.albums.find(album); //set iterator

			}
			else { //album exists
//				cout << "Old Album: " << stripUnderscore(album) << endl; 
				//Increment number of songs and time if album already exists
				ait->second.nsongs++;
				ait->second.time += tDuration;
			}
			//insert songs into album song and update album total song time
			Song theSong;
			theSong.title = title; //initilized with read in song
			theSong.time = tDuration; //initialized with read in song length
			ait->second.songs.insert(make_pair(track, theSong));
		}
	}

    //grayed out stuff is where I started on basic skeleton of output algorithm, don't want to run anything with it yet because it'll make things more confusing.

	map<string, Artist>::iterator mit; //artist iterator
	map<string, Album>::iterator oit; //album
	map<int, Song>::iterator pit; //song

	//Loop through artists, maps should make it in lexographic order
	for(mit = artists.begin(); mit != artists.end(); mit++) {
		
		//Convert time back into string format
	    string artistTime = convertToString(mit->second.time);
		//Print artist introduction
	    cout << stripUnderscore(mit->first) << ": " << mit->second.nsongs << ", " << artistTime << endl;
	    
		//Loop and output artist's albums
	    for(oit = mit->second.albums.begin(); oit != mit->second.albums.end(); oit++){
			//get album time
			string albumTime = convertToString(oit->second.time);
			cout << "        " << stripUnderscore(oit->first) << ": " << oit->second.nsongs << ", " << albumTime << endl;
			
			for(pit = oit->second.songs.begin(); pit != oit->second.songs.end(); pit++){
				string songTime = convertToString(pit->second.time);
				cout << "                " << pit->first << ". " << stripUnderscore(pit->second.title) << ": " << songTime << endl;
			}
	    }
	//General pattern to follow for output:
	
	}
	
	
	
	return 0;
}
