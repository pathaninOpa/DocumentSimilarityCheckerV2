#include "node.h"
#include <vector>

using namespace std;

class Queue{
  private:
    NODE* head = NULL;
    NODE* tail = NULL;
    int size;

  public:
    Queue();
    ~Queue();
    vector<int> get_head();
    void enqueue(vector<int>);
		vector<int> dequeue();
    int get_size();
};

Queue::Queue() {
	this->head = NULL;
	this->tail = NULL;
	this->size = 0;
}

Queue::~Queue() {
	for(NODE* temp = this->head; this->head != NULL; temp = this->head) {
		this->head = temp->getNext();
		delete temp;
		this->size--;
	}
}
vector<int> Queue::get_head() {
	return this->head->getNext()->getValues();
}

void Queue::enqueue(vector<int> value) {
	this->size++;
	NODE * newNODE = new NODE(value);
	if(this->head == NULL) {
		this->head = newNODE;
		this->tail = newNODE;
		return;
	}
	this->tail->setNext(newNODE);
	this->tail = this->tail->getNext();
}

vector<int> Queue::dequeue() {
	this->size--;
	if(this->head == NULL){
    vector<int> dummy;
    return dummy;
  }
	if(this->head == this->tail) this->tail = NULL;
	NODE * temp = this->head;
	vector<int> value = temp->getValues();
	this->head = this->head->getNext();
	delete temp;
	return value;
}

int Queue::get_size(){
  return this->size;
}