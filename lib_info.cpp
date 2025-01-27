//NAMES: Kylie Norosky, Ada Whitefield
//PROGRAM: Project01, Lib_info
//DESCRIPTION:

//I hate Git rn
#include <iostream>
#include <map>
#include <sstream>
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

int convertToSec(string duration){
    string minutes = duration.substr(0,2);
    string seconds = duration.substr(3,2);
    int m = stoi(minutes);
    int s = stoi(seconds);
    m *= 60;
    s += m;
    
    return s;

}

string convertToString(int seconds) {
    //divide by 60 for minutes
    int minutes = seconds / 60;
    int leftoverSec = seconds - minutes; 

    string line = "";
    line.push_back(minutes);
    line.push_back(':');

    if(leftoverSec > 9) {
        line.push_back(leftoverSec);
    }
    else {
        line.push_back('0' + leftoverSec);
    }
    return line;
}
map<string, Artist> artists;
int main() {
	//declare read in variables
	string title;
	string artist;
	string duration;
	string album;
	string genre;
	int track;
	
	map<string, Artist>::iterator sit; //iterates through artist
	map<string, Album>::iterator ait; //iterates through album

	while(cin >> title >> artist >> duration >> album >> genre >> track) {
		int tDuration = convertToSec(duration);	//Immediately we can take in the string and convert to int
		//find artist, if not there insert with album
		sit = artists.find(artist); //iterator points where artist is
		if(sit == artists.end()) { //if not found
    
			//create new artist
			Artist *theArtist = new Artist(); //create new artist
			//update Artist attributes
			theArtist->name = artist; //initialized with read in artist variable
			theArtist->time = tDuration; //initialized with read in time
			theArtist->nsongs = track; //initialized with read in track

			//create new album
			Album *theAlbum = new Album(); //create album
			//update Album attributes
			theAlbum->name = album; //initialized with read in album name
			theAlbum->time = tDuration; //initialized with read in song time
			theAlbum->nsongs = 1; //initialized with the 1 song inserted

			//create new song
			Song *theSong = new Song();
			theSong->title = title; //initilized with read in song
			theSong->time = tDuration; //initialized with read in song length
			
			//This is the point where neovim starts to fuss
	    

			//connect to Artist map with Album struct
			theArtist->albums.insert(make_pair(artist, theAlbum));
			//connect to Album map with Song struct
			theAlbum->songs.insert(track, title);
			theSong->title = title;
			theSong->time = tDuration;


			//insert artist name and album in TheArtist albums map
			ait = theArtist->albums.insert(make_pair(track, album));
			//insert track/title in albums songs map
			ait->second->songs.insert(make_pair(track,title));
		}
		else{
		    
		//ait = Artist->albums.find(artist); //iterator points where artist is --> need to check for album name here
		//if(ait == Artist->albums.end()) { //if not found

		}
	}
	
	return 0;
}
