// My Playlist Dictionary - Closed Hashing
// A C program that inserts, deletes, and searches the song genre in a closed hashing dictionary using the cursor-based implementation.

#include<stdio.h>
#include<string.h>
#define CLDI_H

#define MAX 32

typedef char String[30];

typedef struct{
	String songName;
	String singer;
	String genre;
}Song;

typedef struct{
	Song elem;
	int next;
}Heapspace;

typedef struct{
	Heapspace H[MAX];
	int avail;
}VirtualHeap;

void initDict(VirtualHeap *VH);
void insert(VirtualHeap *VH,Song song);
void deleteMember(VirtualHeap *VH,Song song);
int search(VirtualHeap VH,Song song);
int hash(String genre);
void displayDict(VirtualHeap VH);

int main(){
	Song songBook[20]={	{"Someone Like You","Adele","Ballad"},
						{"Yellow Submarine","Beatles","Pop Rock"},
						{"Training Season","Dua Lipa","Pop"},
						{"Let's go back","Jungle","Dance"},
						{"Sway","Michael Buble","Jazz"},
						{"Love Story","Taylor Swift","Country Pop"},
						{"Where is my Husband?","Raye","Jazz"},
						{"Fly me to the moon","Frank Sinatra","Jazz"},
						{"Thinking Out Loud","Ed Sheeran","Ballad"},
						{"Back on 74","Jungle","Dance"},
						{"Mr. Brightside","The Killers","Pop Rock"},
						{"Kirari","Fuji Kaze","J-Pop"},
						{"This is What You Came For","Calvin Harris","Pop"},
						{"Rock with you","SEVENTEEN","K-Pop"},
						{"Symphony no. 8","Beethoven","Classical"},
						{"Defying Gravity","Wicked","Theater"},
						{"Alone","Marshmello","EDM"},
						{"Buwan","Juan Karlos","OPM"},
						{"NO PROBLEMZ","Jungle","Dance"},
						{"Doo Wop'","Lauryn Hill","R&B"}};

	int trav;
	Song temp={"Fly me to the moon","Frank Sinatra","Jazz"};
	Song check={"Everynight","Jungle","Dance"};
	Song delFirst={"Training Season","Dua Lipa","Pop"};
	VirtualHeap VH;

	initDict(&VH);

	for(trav=0;trav<20;trav++){
		insert(&VH,songBook[trav]);
	}

	displayDict(VH);
	printf("\n");

	printf("\nThe song \"%s\" %s in my playlist",check.songName,(search(VH,check))?"exists":"does not exist");
	printf("\nThe song \"%s\" %s in my playlist",temp.songName,(search(VH,temp))?"exists":"does not exist");

	printf("\n\nDeleting song %s",temp.songName);
	deleteMember(&VH,temp);
	printf("\nDeleting song %s",delFirst.songName);
	deleteMember(&VH,delFirst);
	printf("\n\nInserting song %s",check.songName);
	insert(&VH,check);

	printf("\n");
	displayDict(VH);

	return 0;

}

void initDict(VirtualHeap *VH)
{
	int i,Lim,Half;
	Lim=MAX-1;
	Half=MAX/2;
	for(i=0 ; i<Half ; i++){
		strcpy(VH->H[i].elem.genre,"Empty");
        VH->H[i].elem.songName[0] = '\0';
        VH->H[i].elem.singer[0] = '\0';
		VH->H[i].next=-1;
	}


	for(; i<Lim ; i++){
		VH->H[i].next=i+1;
	}

	VH->H[i].next=-1;
	VH->avail=16;
}


void displayDict(VirtualHeap VH){

	int trav,cntr,set,LIM;
	set=1;
	LIM=MAX/2;

	printf("Playlist of Janie Sabado");
	printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
	printf("\n  %3s   %30s   %-15s   %-13s","Ndx","Song Name","Singer","Genre");
	printf("\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
	for(trav=0;trav<LIM;trav++){
		if(strcmp(VH.H[trav].elem.genre,"Empty")==0){
			printf("\n  %3d.  %30s - %-15s | %-13s",trav+1,"---","---","---");
			//printf("%5d",VH.H[trav].next);
		}else{
			printf("\n  %3d.  %30s - %-15s | %-13s",trav+1,VH.H[trav].elem.songName,VH.H[trav].elem.singer,VH.H[trav].elem.genre);
			//printf("%5d",VH.H[trav].next);
            cntr = VH.H[trav].next;
            while(cntr != -1){
                printf("\n        %30s - %-15s | %-13s",VH.H[cntr].elem.songName, VH.H[cntr].elem.singer, VH.H[cntr].elem.genre);
                //printf("%5d",VH.H[cntr].next);
				cntr = VH.H[cntr].next;
            }
		}

		printf("\n\n - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - ");
	}

}

String genreTable[16] = {
    "Ballad", "Pop Rock", "Pop", "R&B", "Rock", "Country Pop", "J-Pop", "K-Pop",
    "Classical", "Theater", "EDM", "OPM", "Reggae","Dance", "Jazz",  "Indie"
};

static int sameSong(Song *a, Song *b) {
    return strcmp(a->songName, b->songName) == 0 &&
           strcmp(a->singer, b->singer) == 0 && 
           strcmp(a->genre, b->genre) == 0;
}

static int isEmptyDeleted(Heapspace *cell) {
    return strcmp(cell->elem.genre, "Empty") == 0 ||
           strcmp(cell->elem.genre, "Deleted") == 0;
}

void insert(VirtualHeap *VH,Song song) {
    int pos = hash(song.genre);
    
    if (isEmptyDeleted(&VH->H[pos])){
        VH->H[pos].elem = song;
        VH->H[pos].next = -1;
        return;
    }
    
    for (int i = pos; i != -1; i = VH->H[i].next) {
        if (sameSong(&VH->H[i].elem, &song)) return;
    }
    
    int tail;
    for (tail = pos; VH->H[tail].next != -1; tail = VH->H[tail].next) { }
    
    int idx = VH->avail;
    if (idx != -1) VH->avail = VH->H[idx].next;
    
    VH->H[tail].next = idx;
    VH->H[idx].elem = song;
    VH->H[idx].next = -1;
}

void deleteMember(VirtualHeap *VH,Song song) {
    int pos = hash(song.genre);
    
    if (isEmptyDeleted(&VH->H[pos])) return;
    if (sameSong(&VH->H[pos].elem, &song)) {
        int firstNode = VH->H[pos].next;
        if (firstNode == -1) {
            strcpy(VH->H[pos].elem.genre, "Deleted");
            VH->H[pos].elem.songName[0] = '\0';
            VH->H[pos].elem.singer[0] = '\0';
            VH->H[pos].next = -1;
        } else {
            VH->H[pos].elem = VH->H[firstNode].elem;
            VH->H[pos].next = VH->H[firstNode].next;
            VH->H[firstNode].next = VH->avail;
            VH->avail = firstNode;
        }
        return;
    }
    
    int prev = pos;
    int curr = VH->H[pos].next;
    while (curr != -1 && !sameSong(&VH->H[curr].elem, &song)) {
        prev = curr;
        curr = VH->H[curr].next;
    }
    if (curr == -1) return;
    VH->H[prev].next = VH->H[curr].next;
    VH->H[curr].next = VH->avail;
    VH->avail = curr;
}

int search(VirtualHeap VH,Song song) {
    int pos = hash(song.genre);
    if (isEmptyDeleted(&VH.H[pos])) return 0;
    for (int i = pos; i != -1; i = VH.H[i].next) {
        if (sameSong(&VH.H[i].elem, &song)) return 1;
    }
    return 0;
}

int hash(String genre) {
    for (int i = 0; i < 16; i++) {
        if (strcmp(genre, genreTable[i]) == 0) return i;
    }
    return -1;
}