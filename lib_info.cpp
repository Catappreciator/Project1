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
	int duration;
	string album;
	string genre;
	int track;
	
	map<string, Album>::iterator ait; //iterates through artist

	while(cin >> title >> artist >> duration >> album >> genre >> track) {
		
		//find artist, if not there insert with album
		ait = Artist->albums.find(artist); //iterator points where artist is
		if(ait == Artist->albums.end()) { //if not found

			//create new artist
			Artist *theArtist = new Artist(); //create new artist
			//update Artist attributes
			theArtist->name = artist; //initialized with read in artist variable
			theArtist->time = time; //initialized with read in time
			theArtist->nsongs = track; //initialized with read in track

			//create new album
			Album *theAlbum = new Album(); //create album
			//update Album attributes
			theAlbum->name = album; //initialized with read in album name
			theAlbum->time = duration; //initialized with read in song time
			theAlbum->nsongs = 1; //initialized with the 1 song inserted

			//create new song
			Song *theSong = new Song();
			theSong->name = title; //initilized with read in song
			theSong->time = duration; //initialized with read in song length
			

			//connect to Artist map with Album struct
			theArtist->albums.insert(make_pair(artist, theAlbum);
			//connect to Album map with Song struct
			theAlbum->songs.insert(track, title);
			theSong->title = title;
			theSong->time = duration;


			//insert artist name and album in TheArtist albums map
			ait = theArtist->albums.insert(make_pair(track, album));
			//insert track/title in albums songs map
			ait->second->songs.insert(make_pair(track,title));
		}
	}
	
	return 0;
}
