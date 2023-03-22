#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H
#include "Node.h"
#include <exception>
using namespace std;
class fullNode : public exception {
public:
	fullNode() : exception("Greska: Pitanje/odgovor vec ima 10 odgovora. Nije moguc unos novog odgovora\n"){}
};
class questionNotFound : public exception {
public:
	questionNotFound(const string& s): exception("Ne postoji pitanje sa unetim tekstom: "), s_(s) {}
	string getText() const {
		return s_;}
private:
	string s_;
};
class answerNotFound : public exception {
public:
	answerNotFound(const string& s): exception("Ne postoji odgovor sa unetim tekstom: "), s_(s) {}
	string getText() const {
		return s_;}
private:
	string s_;
};
#endif
