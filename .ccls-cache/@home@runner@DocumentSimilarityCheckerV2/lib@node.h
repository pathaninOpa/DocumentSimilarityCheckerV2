#include <vector>

using namespace std;
class NODE {
private:
    vector<int> values;
    NODE* next = nullptr;

public:
    NODE(const vector<int>& values);
    NODE* getNext();
    void setNext(NODE* next);
    const vector<int>& getValues();
    ~NODE();
};

NODE::NODE(const vector<int>& values) {
    this->values = values;
}

NODE* NODE::getNext() {
    return this->next;
}

void NODE::setNext(NODE* next) {
    this->next = next;
}

const vector<int>& NODE::getValues() {
    return this->values;
}

NODE::~NODE() {
}
