//NAMES: Kylie Norosky, Ada Whitefield
//PROGRAM: Project01, Lib_info
//DESCRIPTION: A program to sort through and organize a musical library in lexicographical format.

#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

struct Song { 
	string title;
	int time;  
};

struct Album {
	map <int, Song > songs;
	string name;
	int time;
	int nsongs;  
};

struct Artist {
	map <string, Album > albums;
	string name;
	int time;
	int nsongs;
};

//This helper function converts the time string that is read in to seconds in integer form.
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

//This helper function converts seconds to time in proper format (as a string).
string convertToString(int seconds) {
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

	string title;
	string artist;
	string duration;
	string album;
	string genre;
	int track;

	//Here a map to hold artists is declared along with iterators for the artist map and album map.
	map<string, Artist> artists;
	map<string, Artist>::iterator sit; 
	map<string, Album>::iterator ait; 

	//While loop reads in variables and helper functions are used for the set up.
	while(fin >> title >> duration >> artist >> album >> genre >> track) {
		artist = stripUnderscore(artist);
		album = stripUnderscore(album);
		title = stripUnderscore(title);
		int tDuration = convertToSec(duration);

		//Find artist, if not there insert with album
		sit = artists.find(artist); 
		if(sit == artists.end()) { 

			//Creates artist struct and fills the attributes
			Artist theArtist;
			theArtist.name = artist; 
			theArtist.time = tDuration; 
			theArtist.nsongs = 1; 

			//Creates new album struct and fills attributes 

			Album theAlbum; 

			theAlbum.name = album; 
			theAlbum.time = tDuration; 
			theAlbum.nsongs = 1; 

			//Creates new song struct and fills attributes
			Song theSong;
			theSong.title = title;
			theSong.time = tDuration;


			//Insert map pairs into structs
			theAlbum.songs.insert(make_pair(track, theSong));
			theArtist.albums.insert(make_pair(album, theAlbum));
			artists.insert(make_pair(artist, theArtist));


		}
		else { 
			//Increment time
			sit->second.time += tDuration;
			sit->second.nsongs++;

			//Artist exists, check to see if the album already exists
			ait = sit->second.albums.find(album);
			if(ait == sit->second.albums.end()) { 
				//Create new album if it doesn't exist.				
				Album theAlbum;
				theAlbum.name = album; 
				theAlbum.time = tDuration; 
				theAlbum.nsongs = 1; 

				//Add album to artist
				sit->second.albums.insert(make_pair(album,theAlbum));
				ait = sit->second.albums.find(album); //set iterator

			}
			else { //Album already exists. Increment songs and time.

				ait->second.nsongs++;
				ait->second.time += tDuration;
			}
			//Insert songs into album song and update album total song time
			Song theSong;
			theSong.title = title; 
			theSong.time = tDuration; 
			ait->second.songs.insert(make_pair(track, theSong));
		}
	}

	map<string, Artist>::iterator mit; //Artist iterator
	map<string, Album>::iterator oit; //Album iterator
	map<int, Song>::iterator pit; //Song iterator

	//Loop through artists, maps should make it in lexicographic order
	for(mit = artists.begin(); mit != artists.end(); mit++) {

		//Convert time and print artist introduction
		string artistTime = convertToString(mit->second.time);
		cout << mit->first << ": " << mit->second.nsongs << ", " << artistTime << endl;

		//Loop and output artist's albums
		for(oit = mit->second.albums.begin(); oit != mit->second.albums.end(); oit++){
			string albumTime = convertToString(oit->second.time);
			cout << "        " << oit->first << ": " << oit->second.nsongs << ", " << albumTime << endl;
			//Loop and output songs from albums
			for(pit = oit->second.songs.begin(); pit != oit->second.songs.end(); pit++){
				string songTime = convertToString(pit->second.time);
				cout << "                " << pit->first << ". " << pit->second.title << ": " << songTime << endl;
			}
		}


	}



	return 0;
}
