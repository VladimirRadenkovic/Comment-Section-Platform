#include "Node.h"

Node::Node(const string& text):text_(text),grade_(0){}

Node::~Node(){
	for (auto i : answers_) delete i;

}

string Node::getText() const{
	return text_;
}

int Node::getGrade() const{
	return grade_;
}

int Node::getAnswerSize() const
{
	return answers_.size();
}

void Node::addAnswer(const string& text){
	Node* newNode = new Node(text);
	answers_.push_back(newNode);
	grades_.push_back(&newNode->grade_);
}

void Node::addAnswer(){
	string text;
	cout << "Molimo Vas unesite tekst odgovora.\n";
	//cin >> text;
	cin.ignore();
	getline(cin, text);
	if (answers_.size() == 10) throw new fullNode();
	addAnswer(text);
}

void Node::changeGrade(int d){
	grade_ += d;
}

Node* Node::findAnswer(const string& text){
	for (auto i : answers_) 
		if (i->getText() == text) return i;
	throw new answerNotFound(text);
}

Node* Node::findAnswerPreorder(const string& text){
	stack<Node*> s;
	s.push(this);
	Node* next;
	while (!s.empty()) {
		next = s.top();
		s.pop();
		while (next != nullptr) {
			if (next->getText() == text) return next;
			if (!next->answers_.empty()) {
				list<Node*>::reverse_iterator it;
				for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
					s.push(*it);
				next = s.top();
				s.pop();
			}
			else break;
		}
		
	}
	throw new answerNotFound(text);
}

Node* Node::findMaxAnswer(){
	Node* max = this;
	Node* next;
	stack<Node*> s;
	s.push(max);
	while (!s.empty()) {
		next = s.top();
		s.pop();
		while (next != nullptr) {
			if (next->getGrade() > max->getGrade()) max = next;
			if (!next->answers_.empty()) {
				list<Node*>::reverse_iterator it;
				for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
					s.push(*it);
				next = s.top();
				s.pop();
			}
			else break;
		}
	}
	return max;
}


void Node::preorderTraversal(void(Node::*func)()){
	stack<Node*> s;
	s.push(this);
	Node* next;
	while (!s.empty()) {
		next = s.top();
		s.pop();
		while (next != nullptr) {
			(*next.*func)();
			if (!next->answers_.empty()) {
				list<Node*>::reverse_iterator it;
				for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
					s.push(*it);
				next = s.top();
				s.pop();
			}
			else break;
		}
	}
}

void Node::grade(Node* node, int d){
	grade_ += d;
}

void Node::sortAnswers(){
	answers_.sort([](Node* a, Node* b) { return a->grade_ > b->grade_; });
}

/*void Node::deleteAnswers(){
	stack<Node*> s;
//	s.push(this);
	Node* next = this;
	if (!next->answers_.empty()) {
		list<Node*>::reverse_iterator it;
		for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
			s.push(*it);
	}
	while (!s.empty()) {
		next = s.top();
		s.pop();
		while (next != nullptr) {
			if (!next->answers_.empty()) {
				list<Node*>::reverse_iterator it;
				for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
					s.push(*it);
				cout << "Obrisan odgovor: " << next->text_ << "\n";
				delete next;
				next = s.top();
				s.pop();
			}
			else {
				cout << "Obrisan odgovor: " << next->text_ << "\n";
				delete next;
				break;
			}
		}
	}
}*/

void Node::deleteAnswer(const string& ans){
	stack<Node*> s;
	s.push(this);
	Node* next;
	while (!s.empty()) {
		next = s.top();
		s.pop();
		while (next != nullptr) {
			list<Node*>::iterator it;
			for (it = next->answers_.begin(); it != next->answers_.end(); it++) 
				if ((*it)->text_ == ans) {
					list<int*>::iterator it1;
					for (it1 = next->grades_.begin(); it1 != next->grades_.end(); it1++)
						if ((*it1) == &(*it)->grade_) {
							next->grades_.erase(it1);
							break;
						}
					delete* it;
					next->answers_.erase(it);
					return;
				}
			if (!next->answers_.empty()) {
				list<Node*>::reverse_iterator it;
				for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
					s.push(*it);
				next = s.top();
				s.pop();
			}
			else break;
		}
	}
	throw new answerNotFound(ans);
}

void Node::printText(){
	cout << text_ << '\n';
}

void Node::printAnswers(){
	int j = 1;
	for (auto i : answers_) {
		cout << "     " << j <<".";
		i->printText();
		j++;
	}
}

void Node::printAllAnswers(){
	stack<Node*> s;
	s.push(this);
	Node* next;
	stack<Node*> prev;
	prev.push(this);
	while (!s.empty()) {
		next = s.top();
		s.pop();
		while (next != nullptr) {
			while (true) {
				if (prev.top()->isChild(next)) {
					cout << prev.top()->getText() << "\\" << next->getText() << "\n";
					prev.push(next);
					break;
				}
				else if (prev.top() != next) prev.pop();
				else break;
			}
			if (!next->answers_.empty()) {
				list<Node*>::reverse_iterator it;
				for (it = next->answers_.rbegin(); it != next->answers_.rend(); it++)
					s.push(*it);
				next = s.top();
				s.pop();
			}
			else break;
		}
	}
}

bool Node::comp(Node* n1,Node* n2){
	return n1->grade_ < n2->grade_;
}

bool Node::isChild(Node* next){
	for (auto i : answers_) {
		if (next == i) return true;
	}
	return false;
}

QuestionList::QuestionList(){}

void QuestionList::addQuestion(){
	string text;
	cout << "Molimo Vas unesite tekst pitanja.\n";
	cin.ignore();
	getline(cin, text);
	//cin >> text;
	questions_.push_back(new Node(text));
	cout << "Pitanje je uspesno dodato.\n";
}

void QuestionList::addQuestion(const string& text){
	questions_.push_back(new Node(text));
}

void QuestionList::addAnswer(){
	string text;
	cout << "Unesite tekst pitanja na koje zelite da odgovorite" << '\n';
	cin.ignore();
	getline(cin, text);
	//cin >> text;
	Node* q= findQuestion(text);
	cout << "Pitanje: ";
	q->printText();
	cout << "Odgovori:\n";
	q->printAnswers();
	while (true) {
		int i;
		cout << "Molimo Vas izaberite opciju:\n";
		cout << "1.Unos odgovora na ispisano pitanje/odgovor.\n";
		cout << "2.Unos teksta odgovora od ponudjenih odgovora na koji zelite da odgovorite\n";
		cout << "3.Unos teksta odgovora za direktan pristup odgovoru na koje zelite da odgovorite\n";
		cin >> i;
		switch (i) {
		case(1): {
			q->addAnswer(); //PREKORACENJE RESI!!!!
			cout << "Odgovor je uspesno dodat.\n";
			return; }
		case(2): {
			cout << "Molimo Vas unesite tekst odgovora na koji zelite da odgovorite\n";
			cin.ignore();
			getline(cin, text);
			//cin >> text;
			q = q->findAnswer(text);
			break;
		case(3): {
			cout << "Molimo Vas unesite tekst odgovora za direktan pristup.\n";
			cin.ignore();
			getline(cin, text);
			//cin >> text;
			q = q->findAnswerPreorder(text);
			break;
		}
		default: {
			cout << "Nevalidan unos, Molimo Vas ponovite unos\n";
			i = 0;
		}
		}
		if (i == 1) break;
		else if (i == 0) {
			cout << "Odgovor: ";
			q->printText();
			cout << "Odgovori:\n";
			q->printAnswers();
		}
	}
		/*switch (i) {
		case 1: {
			if (q->getAnswerSize() == 10) {
				cout << "Pitanje/Odgovor sadrzi maksimalan broj odgovora. Nije moguce uneti odgovor.\n"; //EXPEPTIONS DOPUNI!!!!
			}
			cout << "Molimo Vas unesite tekst odgovora\n";
			cin >> text;
			q->addAnswer(text);
			break;
		}
		case 2: {
			cout << "Odgovor: ";
			q->printText();
			cout << "Odgovori:\n";
			q->printAnswers();
			cout << "Molimo Vas unesite tekst odgovora na koji zelite da odgovorite\n";
			cin >> text;
			q = q->findAnswer(text);
			break;
		}
		default: cout << "Nevalidan unos, Molimo Vas ponovite unos\n";
		}
		if (i == 1) break;*/
	}
}

Node* QuestionList::findQuestion(){
	string text;
	cout << "Unesite tekst trazenog pitanja." << '\n';
	cin.ignore();
	getline(cin, text);
	//cin >> text;
	Node* q = findQuestion(text);
	cout << "Pitanje: ";
	q->printText();
	cout << "Odgovori:\n";
	q->printAnswers();
	return q;
}

Node* QuestionList::findAnswer(){
	Node* q = findQuestion();
	string text;
	cout << "Unesite tekst trazenog odgovora.\n";
	getline(cin, text);
	//cin >> text;
	q = q->findAnswerPreorder(text);
	cout << "Odgovor: " << q->getText() << "\n";
	return q;
}

void QuestionList::changeGrade(){
	Node* a = findAnswer();
	int d;
	cout << "Molimo Vas unesite promenu ocene.\n";
	cin >> d;
	a->changeGrade(d);
	cout << "Nova ocena pitanja: " << a->getGrade() << "\n";
}

void QuestionList::printQuestions(){
	int j = 1;
	cout << "Ispis pitanja:\n";
	for (auto i : questions_) {
		cout << j << ". ";
		i->printText();
		j++;
	}
}

void QuestionList::sortQuestions(){
	for (auto i : questions_) {
		i->preorderTraversal(&Node::sortAnswers);
	}
	cout << "Sadrzaj je uspesno sortiran.\n";
}

void QuestionList::printAnswers(){
	string text;
	cout << "Molimo Vas unesite tekst pitanja cije je odgovore potrebno ispisati.\n";
	cin.ignore();
	getline(cin, text);
	//cin >> text;
	findQuestion(text)->printAllAnswers();
}

void QuestionList::findMaxAnswer(){
	string text;
	cout << "Molimo Vas unesite pitanje ciji se odgovor sa maskimalnom ocenom trazi.\n";
	cin.ignore();
	getline(cin, text);
	//cin >> text;
	cout << "Odgovor sa maksimalnom ocenom je: \n" << findQuestion(text)->findMaxAnswer()->getText() << "\n";
}

void QuestionList::printAnswers(const string& question){
	Node* q = findQuestion(question);
	q->preorderTraversal(&Node::printText);
}

/*void QuestionList::deleteQuestion1(){
	string text;
	cout << "Unesite tekst pitanja koje zelite da obrisete.\n";
	cin >> text;
	for (auto it = questions_.begin(); it != questions_.end(); it++)
		if ((*it)->getText() == text) {
			//delete* it;
			(*it)->deleteAnswers();
			delete* it;
			questions_.erase(it);
			cout << "Pitanje je uspesno obrisano.\n";
			return;
		}
}*/

void QuestionList::deleteQuestion(){
	string text;
	cout << "Unesite tekst pitanja koje zelite da obrisete.\n";
	cin.ignore();
	getline(cin, text);
	//cin >> text;
	for (auto it = questions_.begin(); it != questions_.end(); it++)
		if ((*it)->getText() == text) {
			delete* it;
			questions_.erase(it);
			cout << "Pitanje je uspesno obrisano.\n";
			return;
		}
	throw new questionNotFound(text);
}

void QuestionList::deleteAnswers(){
	string question;
	string answer;
	cout << "Molimo Vas unesite tekst pitanja ciji odgovor zelite da obrisete.\n";
	cin.ignore();
	getline(cin, question);
	//cin >> question;
	cout << "Molimo Vas unesite tekst odgovora ciji odgovor zelite da obrisete.\n";
	getline(cin, answer);
	//cin >> answer;
	findQuestion(question)->deleteAnswer(answer);
	cout << "Uspesno je obrisan odgovor: " << answer << endl;
}

void QuestionList::addAnswer(const string& question, const string& text, const string& answer){
	if (answer != "") findQuestion(question)->findAnswerPreorder(answer)->addAnswer(text);
	else findQuestion(question)->addAnswer(text);
	int i = rand() % 100;
	cout << text << " ";
	cout << i << "\n";
	findQuestion(question)->findAnswer(text)->changeGrade(i);
}

void QuestionList::addAnswer2(const string& question, const string& answer, const string& text){
	findQuestion(question)->findAnswerPreorder(answer)->addAnswer(text);
	int i = rand() % 100;
	cout << text << " ";
	cout << i << "\n";
	findAnswer(question, text)->changeGrade(i);
}

Node* QuestionList::findAnswer(const string& question, const string& answer){
	return findQuestion(question)->findAnswerPreorder(answer);
}


Node* QuestionList::findQuestion(const string& text){
	for (auto i : questions_) 
		if (i->getText() == text) return i;
	throw new questionNotFound(text);
}
