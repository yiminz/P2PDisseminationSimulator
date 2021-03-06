#ifndef simulator_hh
#define simulator_hh

#include "statistics.hh"
#include "node.hh"
#include "update.hh"
#include <mutex>

struct thread_data{
	int  tid;
        int FANOUT;
        int NUM_NODES;
        int NUM_CONTENTS;
        int NUM_THREADS;
	class Node *nodes;
	mutex *inUpdatesLocks;
	set<Update> *inUpdates;
};

class Simulator {	
        // TODO add that they cannot be modified
        int NUM_NODES;
        int NUM_ROUNDS;
        int RTE;
        int NUM_UPDS_PER_ROUND;
        int FANOUT;
        int DURATION_PROPOSE;
        int NUM_CONTENTS;
        int NUM_THREADS; 
        
	class Node *nodes;	
	set<Update> *inUpdates; // Messages that are being transmitted during one round
	
	mutex *inUpdatesLocks;
	struct thread_data *td;
        pthread_t *threads;
        
        class Statistics *stats;
        
public: 
	Simulator(int NUM_NODES, int NUM_ROUNDS, int RTE, int NUM_UPDS_PER_ROUND, 
                  int FANOUT, int DURATION_PROPOSE, int NUM_CONTENTS, int NUM_THREADS,
		  int PROBAITOI, int PROBAITOJ
 		);
	~Simulator();

        static int getContentIdFromNodeId(int nodeId, int NUM_CONTENTS);
        static int getRandNodeIdFromContent(int contentId, int NUM_NODES, int NUM_CONTENTS);
        static int getRandNodeIdFromOtherContent(int contentId, int NUM_NODES, int NUM_CONTENTS);
	
	void sourceSendNewUpdates(int roundId);
	void peersPushUpdates();
	void peersEndOfRound(int roundId);
};


#endif
