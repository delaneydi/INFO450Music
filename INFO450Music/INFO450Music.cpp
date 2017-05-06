/// LinkListExample1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class songNode 
{
private:
	string artistName;
	string songName;
	songNode* next;

public:
	songNode(string, string);
	string getArtist();
	string getSong();
	songNode* getNext();
	void setNext(songNode*);
};

class playlist 
{
private:
	songNode* head;
	songNode* currentSong;

public:
	playlist();
	~playlist();
	void add(string, string);
	void removeSong();
	void skipSong(int);
	void nextSong();
	songNode* getCurrentSong();
	void write(ofstream& ofs);
};

songNode::songNode(string a, string s) 
{
	this->artistName = a;
	this->songName = s;
	next = NULL;
}

string songNode::getArtist() 
{
	return artistName;
}

string songNode::getSong() 
{
	return songName;
}

songNode* songNode::getNext() 
{
	return next;
}

void songNode::setNext(songNode* n)
{
	this->next = n;
}

playlist::playlist() {
	head = NULL;
	currentSong = NULL;
}

playlist::~playlist() {
	songNode* temp; 
	songNode* current = head;

	while (current != NULL)
	{
		temp = current;
		current = current->getNext();


		delete (temp);
	}
}

void playlist::add(string a, string s) 
{
	songNode *newNode = new songNode(a, s);
	if (head == NULL)
	{
		head = newNode;
		currentSong = newNode;
	}
	else 
	{
		songNode *current = head;
		while (current->getNext() != NULL)
		{
			current = current->getNext();
		}
		current->setNext(newNode);
	}
}

void playlist::removeSong() 
{
	if (head == NULL)
	{
		return;
	}

	songNode *prev = NULL;
	songNode *current = head;
	while (current != currentSong)
	{
		prev = current;
		current = current->getNext();
	}

	if (prev == NULL)
	{
		if (currentSong == head)
		{
			currentSong = head->getNext();
		}
		head = head->getNext();
	}
	else 
	{
		prev->setNext(current->getNext());
		currentSong = currentSong->getNext();
		if (currentSong == NULL)
		{
			currentSong = head;
		}
	}
	delete current;
}

void playlist::skipSong(int n) 
{
	if (head == NULL)
	{
		return;
	}
	for (int i = 0; i < n; i++)
	{
		songNode *prev = NULL;
		songNode *current = head;
		while (current != currentSong)
		{
			prev = current;
			current = current->getNext();
		}
		songNode *tail = head;
		while (tail != NULL && tail->getNext() != NULL)
		{
			tail = tail->getNext();
		}

		if (current == tail)
		{
			return;
		}
		if (prev == NULL)
		{
			head = head->getNext();
			current->setNext(NULL);
			tail->setNext(current);
			currentSong = head;
		}
		else 
		{
			currentSong = currentSong->getNext();
			if (currentSong == NULL)
			{
				currentSong = head;
			}
			prev->setNext(current->getNext());
			current->setNext(NULL);
			tail->setNext(current);
		}
	}
}

void playlist::nextSong() 
{
	if (currentSong != NULL)
	{
		currentSong = currentSong->getNext();
		if (currentSong == NULL)
		{
			currentSong = head;
		}
	}
}

songNode* playlist::getCurrentSong()  
{
	return currentSong;
}
 
void playlist::write(ofstream& ofs) 
{
	songNode *current = head;
	while (current != NULL)
	{
		ofs << current->getArtist() << "," << current->getSong() << endl;
		current = current->getNext();
	}
}

int main()
{
	playlist list;
	int n;
	string filename;
	string numberSkips;
	string artist, song;
	songNode *currentSong;
	string filename = "c:\\users\\desmund\\desktop\\mymusic.txt";
	playlist myplaylist;
	string answer;
	ifstream infile;
	infile.open(filename);
	if (infile.is_open()) 
	{
		while (!infile.eof())
		{
			getline(infile, song, ',');
			getline(infile, artist);
			list.add(artist, song);
		}
		infile.close();
	}
	else {
		cout << "File not found" << endl;
	}

	char choice;
	do
	{
		cout << "The song is " << currentSong->getSong() << "by " << currentSong->getArtist() << ". [D]elete, [S]kip, [P]lay  or [Q]uit?" << endl;
		cin >> choice;
		switch (choice)
		{
		case 'D':
		case 'd':
			list.removeSong();
			break;
		case 'S':
		case 's':
			cout << "Skip how many songs?";
			getline(cin, numberSkips); 
			int n = stoi(numberSkips);
			list.skipSong(n);
			break;
		case 'P':
		case 'p':
			currentSong = list.getCurrentSong();
			if (currentSong == NULL)
			{
				cout << "Song currently unavailable." << endl;
			}
			else
			{
				cout << currentSong->getSong() << "by " << currentSong->getArtist() << " is playing." << endl;
			}
			list.nextSong();
			break;
		case 'Q':
		case 'q':
			cout << "Quitting - thanks for listening. " << endl;
			break;
		default:
			cout << "Sorry, invalid entry! Please try again." << endl;
			break;
		}
	}

	while (choice == 'Y' || choice == 'y');
	return 0;
}