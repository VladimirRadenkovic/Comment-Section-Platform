#ifndef NODE_H
#define NODE_H
#include<string>
#include<list>
#include<vector>
#include<stack>
#include<queue>
#include<iostream>
#include"Exeptions.h"
using namespace std;

class Node {
public:
	Node(const string& text);
	~Node();

	string getText() const;
	int getGrade() const;
	int getAnswerSize() const;

	void addAnswer(const string& text);
	void addAnswer();
	void changeGrade(int d);
	Node* findAnswer(const string& text);
	Node* findAnswerPreorder(const string& text);
	Node* findMaxAnswer();
	void preorderTraversal(void (Node::* func)());
	void grade(Node* node,int d);
	void sortAnswers();
	//void deleteAnswers();
	void deleteAnswer(const string& ans);
	void printText();
	void printAnswers();
	void printAllAnswers();
private:
	bool comp(Node* n1, Node* n2);
	bool isChild(Node* next);
	string text_;
	list<Node*> answers_;
	int grade_;
	list<int*> grades_;

};

class QuestionList {
public:
public:
	QuestionList();

	void addQuestion();
	void addAnswer(); //Dodaj da moze direktno da se pristupi odgovoru na koji se odgovara
	Node* findQuestion();
	Node* findAnswer(); 
	void changeGrade(); 
	void printQuestions();
	void sortQuestions();
	void printAnswers();
	void findMaxAnswer();
	void printAnswers(const string& question); //Resiti ispis!
	void deleteQuestion();
	//void deleteQuestion1();
	void deleteAnswers();
	
	void addQuestion(const string& text);
	void addAnswer(const string& question, const string& text, const string& answer = "");
	void addAnswer2(const string& question, const string& answer, const string& text);
	Node* findAnswer(const string& question, const string& answer);
	Node* findQuestion(const string& text);
	
private:	
	list<Node*> questions_;
};
#endif