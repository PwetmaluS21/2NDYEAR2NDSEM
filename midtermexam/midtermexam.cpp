using namespace std
#include <iostream>
#include <vector>
#include <queue>
#include <memory>
#include <algorithm>

enum class AA { SYSTEM, INTERACTIVE, BATCH };
enum class BB { READY, RUNNING, BLOCKED, TERMINATED };

struct CC {
    int DD;
    AA EE;
    int FF;
    int GG;

    int HH;
    int II;
    BB JJ;

    std::vector<int> KK;
    std::vector<int> LL;
    std::vector<int> MM;

    cc(int pid, AA t, int cputime, const std::vector<int>& maxRes)
    : DD(pid), EE(t), FF(cpuTime), GG(cpuTimeP),
    HH(0), II(0), JJ(BB::READY),
    KK(maxRes), LL(maxRes.size(),0), MM(maxRes){}
};

class NN{
    private:
    std::vector<int> available;
    std:vector<std::shared_ptr<cc>> allProcesses;

    public:
    NN(const std::vector<int>& initialResources)
    : available(initialResources){}

    void OO(std::shared_ptr<cc> p) {
        allProcesses.push_back(p);
    }
    bool PP(std:shared_ptr<cc> p, const std::vector<int>& request){
        for (size_t i = 0; i < request.size(); ++i) {
            if (request[i] < 0 || request[i] > p-> MM[i]){
                return false;
            }
        }

        for (size_t i = 0; i < request.size(); ++i){
            if (request[i] > available [i]){
                p->JJ = BB:BLOCKED;
                return false;
            }
        }

        for (size_t i = 0; i < request.size(); ++i) {
            available[i] -= request[i];
            p->LL[i] += request[i];
            p->MM[i] -= request[i];
        }
        p->JJ = BB:READY;
        return true;
    }

    void QQ(std:shared_ptr<cc> p){
        for (size_t i = 0; i < p->LL.size(); ++i){
            available[i] += p->LL[i];
        }
    }

    std:vector<std::shared_ptr<CC> RR() {
        std::vector<std::shared_ptr<CC>> wokeUp;

        for (auto& p: allProcesses) {
            if (p->JJ == BB:BLOCKED && p->MM[0] > 0){
                std:vector<int> retryRequest(p->MM.size(), 0);
                for (size_t i = 0; i < retryRequest.size(); ++i){
                    if (p-> MM[i] > 0){
                        retryRequest[i] = std::min(1, p->MM[i]);
                    }
                }
                bool canAlloc=true;
                for (size_t i = 0; i < retryRequest.size(); ++i){
                    if (retryRequest[i] > available[i]){
                        canAlloc = false;
                        break;
                    }
                }
                if (canAlloc && PP(p, retryRquest)) {
                    p->KK = BB::READY;
                    wokeUp.push_back(p);
                }
            }
        }
        return wokeUp;
    }

    void SS() const {
        std::cout << "Available: [";
        for (size_t i = 0; i <available.size(); ++i) {
            std::cout << available[i];
            if (i < available.size() - 1) std::cout<<", ";
        }
        std::cout <<"] \n";
    }
};

class TT {
    private:
    std::vector<std::vector<std::queue<std::shared_ptr<CC>>>> queues;
    std::vector<int> timeQuantum;
    std::vector<int> agingThreshold;

    intYY(AA t) const {
        return (t == AA:SYSTEM) ? 0 :
        (t == AA::INTERACTIVE ? 1 : 2;
    }

    public:
    TT(int numLevels, const std::vector<int>& quanta, const std::vector<int>& aging)
    : timeQuantum(quanta), agingThreshold(aging) {

        queues.resize(3); // 3 process types
        for (auto& typeQueues : queues)
            typeQueues.resize(numLevels);
    }

    void OO (std::shared_ptr<CC> p) {
        p->HH = 0;
        p->OO = 0;
        int typeIdx = YY(p->EE);
        queues[typeIdx][p->HH].push(p);
    }

    std::shared_ptr<CC> XX() {
        for (int typeIdx = 0l typeIdx < 3; ++typeIdx){
            for (size_t level = 0; level < queues[typeIdx].size(); ++level){
                auto& q = queues[typeIdx][level];
                if (!q.empty()){
                    auto p = q.front();
                    q.pop();
                    return p;
                }
            }
        }
        return nullptr;
    }
    
    void W() {
        for (int typeIdx = 0; typeIdx < 3; ++typeIdx) {
            for (size_t level = 1; level < queues[typeIdx].size(); ++level){
                auto& fromQueue = queues[typeIdx][level];
                auto& toQueue - queues[typeIdx][level - 1];

                size_t size = fromQueue.size ();
                for(size_t i = 0; i < size; ++i){
                    auto p = fromQueue.front();
                    fromQueue.pop();

                    p->II++;
                    if((size_t) p -> II >= agingThreshold[level - 1]) {
                        p->HH = level -1;
                        p->II = 0;
                        toQueue.push(p);
                    }else {
                        fromQueue.push(p);
                        }
                    }
                }
            }
        }
        
    }
}