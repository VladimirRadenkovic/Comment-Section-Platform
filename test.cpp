#include"Node.h"
#include"Exeptions.h"
void menu() {
	cout << "Sadrzaj menija:\n";
	cout << "1.Dodavanje novog pitanja.\n";
	cout << "2.Dodavanje odgovora na neko pitanje ili odgovor.\n";
	cout << "3.Pretraga pitanja.\n";
	cout << "4.Pretraga odgovora\n";
	cout << "5.Povecanje ocene nekog odgovora\n";
	cout << "6.Uredjivanje odgovora prema njihovoj oceni za sva pitanja prema vrednosti ocene u nerastucem poretku.\n";
	cout << "7.Ispis svih pitanja.\n";
	cout << "8.Ispis pojedinacnog pitanja i njemu pridruzenih odgovora i komentara\n";
	cout << "9.Brisanje pojedinacnog pitanja i njemu pridruzenih odgovora i komentara\n";
	cout << "10.Brisanje pojedinacnog odgovora i svih njegovih potomaka.\n";
	cout << "11.Ispis odgovora sa najvecom ocenom.\n";
	cout << "0.Prekid programa\n";
}

void chooseOperation(QuestionList* questions) {
	int i = 0;
	while (true) {
		menu();
		cout << "Izaberite jednu od opcija iz menija.\n";
		cin >> i;
		try {
			if (i == 0) break;
			switch (i) {
			case(1): {
				questions->addQuestion();
				break; }
			case(2): {
				questions->addAnswer();
				break; }
			case(3): {
				questions->findQuestion();
				break; }
			case(4): {
				questions->findAnswer();
				break; }
			case(5): {
				questions->changeGrade();
				break; }
			case(6): {
				questions->sortQuestions();
				break; }
			case(7): {
				questions->printQuestions();
				break; }
			case(8): {
				questions->printAnswers();
				break; }
			case(9): {
				questions->deleteQuestion();
				break; }
			case(10): {
				questions->deleteAnswers();
				break; }
			case(11): {
				questions->findMaxAnswer();
				break; }
			default: {
				cout << "Nevalidan unos, molimo Vas ponovite unos\n";
				break; }
			}
		}
		catch (fullNode* e) {
			cout << e->what();
		}
		catch (questionNotFound* e) {
			cout << e->what() << e->getText() << endl;
		}
		catch (answerNotFound* e) {
			cout << e->what() << e->getText() << endl;
		}
	}
}
int main() {
	QuestionList* questions = new QuestionList();
	questions->addQuestion("q1");
	questions->addQuestion("q2");
	questions->addQuestion("q3");
	questions->addQuestion("q4");
	questions->addQuestion("q5");
	//questions->printQuestions();
	questions->addAnswer("q1", "a1");
	questions->addAnswer("q1", "a2");
	questions->addAnswer("q1", "a3");
	questions->addAnswer("q1", "a4");
	questions->addAnswer("q1", "a5");
	questions->addAnswer("q1", "a6");
	questions->addAnswer("q1", "a7");
	questions->addAnswer("q1", "a8"); 
	questions->addAnswer("q1", "a9"); 
	questions->addAnswer("q1", "a10");

	/*questions->addAnswer("q2", "a1");
	questions->addAnswer("q2", "a2");
	questions->addAnswer("q2", "a3");

	questions->addAnswer("q3", "a1");
	questions->addAnswer("q3", "a2");
	questions->addAnswer("q3", "a3");

	questions->addAnswer("q4", "a1");
	questions->addAnswer("q4", "a2");
	questions->addAnswer("q4", "a3");*/

	questions->addAnswer2("q1", "a1", "a11");
	questions->addAnswer2("q1", "a1", "a12");
	questions->addAnswer2("q1", "a1", "a13");
	questions->addAnswer2("q1", "a2", "a21");
	questions->addAnswer2("q1", "a2", "a22");
	questions->addAnswer2("q1", "a2", "a23");
	questions->addAnswer2("q1", "a3", "a31");
	questions->addAnswer2("q1", "a3", "a32");
	questions->addAnswer2("q1", "a3", "a33");

	questions->addAnswer2("q1", "a11", "a111");
	questions->addAnswer2("q1", "a11", "a112");
	questions->addAnswer2("q1", "a11", "a113");
	questions->addAnswer2("q1", "a11", "a114");
	questions->addAnswer2("q1", "a11", "a115");
	questions->addAnswer2("q1", "a11", "a116");
	questions->addAnswer2("q1", "a11", "a117");
	questions->addAnswer2("q1", "a11", "a118");
	questions->addAnswer2("q1", "a11", "a119");
	questions->addAnswer2("q1", "a11", "a1110");

	questions->addAnswer2("q1", "a111", "a1111");
	questions->addAnswer2("q1", "a111", "a1112");

	questions->addAnswer2("q1", "a112", "a1121");
	questions->addAnswer2("q1", "a1111", "a11111");
	questions->addAnswer2("q1", "a1111", "a11112");
	questions->addAnswer2("q1", "a1111", "a11113");

	chooseOperation(questions);
	/*questions->addAnswer2("q1", "a11", "a111");
	questions->addAnswer2("q1", "a11", "a112");
	questions->addAnswer2("q1", "a11", "a113");
	questions->addAnswer2("q1", "a11", "a114");*/

	/*questions->addAnswer("q2", "a11", "a1");
	questions->addAnswer("q2", "a12", "a1");
	questions->addAnswer("q2", "a13", "a1");
	questions->addAnswer("q2", "a21", "a2");
	questions->addAnswer("q2", "a22", "a2");
	questions->addAnswer("q2", "a23", "a2");
	questions->addAnswer("q2", "a31", "a3");
	questions->addAnswer("q2", "a32", "a3");
	questions->addAnswer("q2", "a33", "a3");

	questions->addAnswer("q3", "a11", "a1");
	questions->addAnswer("q3", "a12", "a1");
	questions->addAnswer("q3", "a13", "a1");
	questions->addAnswer("q3", "a21", "a2");
	questions->addAnswer("q3", "a22", "a2");
	questions->addAnswer("q3", "a23", "a2");
	questions->addAnswer("q3", "a31", "a3");
	questions->addAnswer("q3", "a32", "a3");
	questions->addAnswer("q3", "a33", "a3");

	questions->addAnswer("q4", "a11", "a1");
	questions->addAnswer("q4", "a12", "a1");
	questions->addAnswer("q4", "a13", "a1");
	questions->addAnswer("q4", "a21", "a2");
	questions->addAnswer("q4", "a22", "a2");
	questions->addAnswer("q4", "a23", "a2");
	questions->addAnswer("q4", "a31", "a3");
	questions->addAnswer("q4", "a32", "a3");
	questions->addAnswer("q4", "a33", "a3");
	/*for (int i = 1; i <= 4; i++) 
		for (int j = 1; j <= 3; j++) {
			questions->findAnswer("q" + to_string(i), "a" + to_string(j))->changeGrade(rand() % 100);
			for (int k = 1; k <= 3; k++) 
				questions->findAnswer("q" + to_string(i), "a" + to_string(j)+to_string(k))->changeGrade(rand() % 100);
		}*/
	//questions->findMaxAnswer();
	//questions->printAnswers("q1");
	/*questions->deleteQuestion();
	questions->printAnswers();
	cout << "\n\n\n\n" << questions->findQuestion("q1")->getText() << "\n";
	questions->printAnswers("q1");
	questions->sortQuestions();
	cout << "\n\n";
	questions->printAnswers("q1");
	cout << "\n\n";
	//Node* a = questions->findAnswer();
	questions->printQuestions();*/
	return 0;
}
