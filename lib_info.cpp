//NAMES: Kylie Norosky, Ada Whitefield
//PROGRAM: Project01, Lib_info
//DESCRIPTION:

//I hate Git rn
#include <iostream>
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

int main() {
	//declare read in variables
	string title;
	string artist;
	int time;
	string album;
	string genre;
	int track;
	
	map<string, Album>::iterator ait; //iterates through artist

	while(cin >> title >> artist >> time >> album >> genre >> track) {
		
		//find artist, if not there insert with album
		ait = Artist->albums.find(artist);
		if(ait == Artist->albums.end()) {
			Artist *theArtist = new Artist();
			Album *theAlbum = new Album();
			Song *theSong = new Song();
			ait = theArtist->albums.insert(make_pair(artist, album));
			ait->second->songs.insert(make_pair(track,title));
		}
	}
	
	return 0;
}
