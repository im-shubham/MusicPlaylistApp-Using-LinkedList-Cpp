#include <iostream>
#include <string>
using namespace std;

class Song {
public:
    string title;
    string artist;
    int duration;  // in seconds
    Song* next;

    Song(string title, string artist, int duration) {
        this->title = title;
        this->artist = artist;
        this->duration = duration;
        this->next = nullptr;
    }
};

class Playlist {
public:
    Playlist() {
        head = nullptr;
    }

    ~Playlist() {
        while (head != nullptr) {
            Song* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void addSong(string title, string artist, int duration) {
        Song* newSong = new Song(title, artist, duration);
        if (head == nullptr) {
            head = newSong;
        } else {
            Song* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = newSong;
        }
        cout << "Added song: " << title << " by " << artist << endl;
    }

    void removeSong(int index) {
        if (head == nullptr) {
            cout << "The playlist is empty." << endl;
            return;
        }
        if (index == 0) {
            Song* temp = head;
            head = head->next;
            cout << "Removed song: " << temp->title << " by " << temp->artist << endl;
            delete temp;
        } else {
            Song* current = head;
            Song* previous = nullptr;
            int i = 0;
            while (i < index && current != nullptr) {
                previous = current;
                current = current->next;
                i++;
            }
            if (current == nullptr) {
                cout << "Invalid song index." << endl;
                return;
            }
            previous->next = current->next;
            cout << "Removed song: " << current->title << " by " << current->artist << endl;
            delete current;
        }
    }

    void play() {
        if (head == nullptr) {
            cout << "The playlist is empty." << endl;
            return;
        }
        Song* current = head;
        while (current != nullptr) {
            cout << "Playing song: " << current->title << " by " << current->artist << " (" << current->duration << " seconds)" << endl;
            current = current->next;
        }
    }

private:
    Song* head;
};

int main() {
    Playlist playlist;
    int choice, index, duration;
    string title, artist;

    do {
        cout << "Enter 1 to add a song, 2 to remove a song, 3 to play the playlist, or 0 to exit: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the song title: ";
                getline(cin >> ws, title);
                cout << "Enter the artist: ";
                getline(cin >> ws, artist);
                cout << "Enter the duration (in seconds): ";
                cin >> duration;
                playlist.addSong(title, artist, duration);
                break;
            case 2:
                cout << "Enter the index of the song to remove: ";
                cin >> index;
                playlist.removeSong(index);
                break;
            case 3:
                playlist.play();
                break;
            case 0:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid choice." << endl;
                break;
        }

    } while (choice != 0);

    return 0;
}
