#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <Windows.h> 

using namespace std;

enum Special { КІ, КБ, КН, СА, АЕ };

string s_special[] = { "Комп’ютерна інженерія ",
					   "Кібербезпека",
					   "Комп’ютерні науки",
					   "Системний аналіз",
					   "Атомна енергетика " };

struct student
{
	string prizv;
	int kurs;
	Special specialization;
	int phisuka;
	int matematic;
	union
	{
		int programing;
		int chuslo_metod;
		int pedahohica;
	};
};


void Create(student& s, const int kilkist, ofstream& file_s);
void Print(student& s, const int kilkist, ifstream& file_l);

void SortBIN(student& str, student& str_a, student& str_b, const int kilkist, const char* fname, fstream& f);

int* Sort_INDEX(student& str_a, student& str_b, const int kilkist, const char* fname, fstream& file_l);

int BinSearch(student& s, const int kilkist, const string prizv, const int kurs, const int matematic, const char* fname, ifstream& file_l);

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int kil_student;
	cout << "Введіть кількість студентів: "; cin >> kil_student;
	cout << endl;
	student s;
	student str;
	student str_a;
	student str_b;

	char fname[101];
	cout << "Введіть назву фізичного файлу: "; cin >> fname; cout << endl;

	ifstream file_l;
	ofstream file_s;
	fstream f;

	string prizv;
	int kurs;
	int matematic;
	int found;

	int menuItem;
	do {
		cout << "Виберіть дію:" << endl << endl;
		cout << " [1] - введення даних з клавіатури" << endl;
		cout << " [2] - вивід даних на екран" << endl;

		cout << " [3] - фізичне впорядкування даних" << endl;
		cout << " [4] - індексне впорядкування та вивід даних" << endl;
		cout << " [5] - бінарний пошук студента" << endl;

		cout << " [0] - вихід та завершення роботи програми" << endl << endl;
		cout << "Введіть пункт меню: "; cin >> menuItem;

		switch (menuItem)
		{
		case 1:
			file_s.open(fname, ios::binary);
			Create(s, kil_student, file_s);
			file_s.close();
			break;
		case 2:
			file_l.open(fname, ios::binary);
			Print(s, kil_student, file_l);
			file_l.close();
			break;
		case 3:
			SortBIN(str, str_a, str_b, kil_student, fname, f);
			break;
		case 4:
			Sort_INDEX(str_a, str_b, kil_student, fname, f);
			file_l.open(fname, ios::binary);
			Print(s, kil_student, file_l);
			file_l.close();
			break;
		case 5:
			cout << "Введіть ключі пошуку:" << endl;
			cin.get();
			cin.sync();
			cout << " прізвище: ";
			getline(cin, prizv);

			cout << " курс: ";
			cin >> kurs;

			cout << " бал з математики: "; cin >> matematic;
			cout << endl;
			if ((found = BinSearch(s, kil_student, prizv, kurs, matematic, fname, file_l)) != -1)
				cout << "Знайдено студента в списку під номером " << found + 1 << endl;
			else
				cout << "Шуканого студента в списку не знайдено" << endl;
			break;

		case 0:
			break;
		default:
			cout << "Ви ввели помилкове значення! "
				"Слід ввести число - номер вибраного пункту меню" << endl;
		}
		cout << endl;
	} while (menuItem != 0);
	exit(0);
}

void Create(student& s, const int kilkist, ofstream& file_s)
{
	int special;
	for (int i = 0; i < kilkist; i++)
	{
		cout << endl;
		cout << "студент № " << i + 1 << endl;

		cin.get();
		cin.sync();

		cout << "  прізвище: "; getline(cin, s.prizv);
		cout << "  курс: "; cin >> s.kurs;
		cout << "  спеціальність (0 - Комп’ютерна інженерія, 1 - Кібербезпека, 2 - Комп’ютерні науки, 3 - Системний аналіз, 4 - Атомна енергетика ): "; cin >> special;
		s.specialization = (Special)special;
		cout << "  оцінка з фізики: "; cin >> s.phisuka;
		cout << "  оцінка з математики: "; cin >> s.matematic;
		switch (special)
		{
		case 0:
			cout << "  оцінка з програмування: "; cin >> s.programing;
			break;
		case 1:
			cout << "  оцінка з чисельних методів: "; cin >> s.chuslo_metod;
			break;
		case 2:
		case 3:
		case 4:
			cout << "  оцінка з педагогіки: "; cin >> s.pedahohica;
			break;
		default:
			cout << "Ви ввели помилкове значення! " << endl;
		}
		cout << endl;

		if (!file_s.write((char*)&s, sizeof(student)))
		{
			cerr << "Error writing file." << endl;
		}
	}
}

void Print(student& s, const int kilkist, ifstream& file_l)
{
	cout << "============================================================================================================================"
		<< endl;
	cout << "| №  | Прізвище     | Курс | Спеціальність           | Фізика | Математика  | Програмування | Чисельні методи | Педагогіка |"
		<< endl;
	cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;

	int i = 0;
	while (i < kilkist)
	{
		file_l.read((char*)&s, sizeof(student));
		cout << "| " << setw(2) << right << i + 1 << " ";
		cout << "| " << setw(13) << left << s.prizv;
		cout << "| " << setw(3) << right << s.kurs << "  ";
		cout << "| " << setw(23) << left << s_special[s.specialization] << " ";
		cout << "| " << setw(4) << right << s.phisuka << "   ";
		cout << "| " << setw(6) << right << s.matematic << "      ";
		switch (s.specialization)
		{
		case 0:
			cout << "| " << setw(7) << right << s.programing << "       |" << setw(18) << "|" << setw(13) << "|" << endl;
			break;
		case 1:
			cout << "| " << setw(15) << "|" << setw(10) << right << s.chuslo_metod << "       |" << setw(13) << "|" << endl;
			break;
		case 2:
		case 3:
		case 4:
			cout << "| " << setw(15) << "|" << setw(18) << "|" << right << setw(7) << s.pedahohica << "     |" << endl;
			break;
		}
		i++;
	}
	cout << "============================================================================================================================" << endl;
}


void SortBIN(student& str, student& str_a, student& str_b, const int kilkist, const char* fname, fstream& f)
{
	for (int i0 = 1; i0 < kilkist; i0++)
	{
		for (int i1 = 0; i1 < kilkist - i0; i1++)
		{
			f.open(fname, ios::binary | ios::in | ios::out);
			int l, m;
			l = i1;
			m = i1 + 2;
			while (l < m)
			{
				f.seekg(l * sizeof(student), ios::beg);
				f.read((char*)&str, sizeof(student));
				if (l == m - 2)
					str_a = str;
				else
					str_b = str;
				l++;
			}

			if ((str_a.kurs > str_b.kurs)
				|| (str_a.kurs == str_b.kurs && str_a.matematic > str_b.matematic)
				|| (str_a.kurs == str_b.kurs && str_a.matematic == str_b.matematic && str_a.prizv > str_b.prizv)
				)
			{
				l = i1;
				while (l < m)
				{
					if (l == m - 2)
						str = str_b;
					else
						str = str_a;
					f.seekp(l * sizeof(student), ios::beg);
					f.write((char*)&str, sizeof(student));
					l++;
				}
			}
			f.close();
		}
	}
}

int* Sort_INDEX(student& str_a, student& str_b, const int kilkist, const char* fname, fstream& f)
{
	int* I = new int[kilkist];

	for (int i = 0; i < kilkist; i++)
		I[i] = i;

	int a, b, zmina;
	int i, j, value, stochik = 0;
	for (i = 1; i < kilkist; i++)
	{
		value = I[i];

		f.open(fname, ios::binary | ios::in | ios::out);
		f.seekg(value * sizeof(student), ios::beg);
		f.read((char*)&str_b, sizeof(student));
		f.close();
		j = i - 1;
		for (j; j >= 0;j--)
		{
			zmina = j;

			f.open(fname, ios::binary | ios::in | ios::out);
			f.seekg(j * sizeof(student), ios::beg);
			f.read((char*)&str_a, sizeof(student));
			f.close();

			if ((str_a.kurs > str_b.kurs)
				|| (str_a.kurs == str_b.kurs && str_a.matematic > str_b.matematic)
				|| (str_a.kurs == str_b.kurs && str_a.matematic == str_b.matematic && str_a.prizv < str_b.prizv)
				)
			{
				I[j + 1] = I[j];
				a = j + 1;
				f.open(fname, ios::binary | ios::in | ios::out);
				f.seekg(a * sizeof(student), ios::beg);
				f.write((char*)&str_a, sizeof(student));
				f.close();
				stochik++;
				zmina--;
			}
		}
		I[zmina + 1] = value;
		b = zmina + 1;
		if (stochik != 0)
		{
			f.open(fname, ios::binary | ios::in | ios::out);
			f.seekg(b * sizeof(student), ios::beg);
			f.write((char*)&str_b, sizeof(student));
			f.close();
		}
	}
	return I;
}

int BinSearch(student& s, const int kilkist, const string prizv, const int kurs, const int matematic, const char* fname, ifstream& file_l)
{
	int L = 0, R = kilkist - 1, m;
	do {
		m = (L + R) / 2;
		file_l.open(fname, ios::binary);
		file_l.seekg(m * sizeof(student), ios::beg);
		file_l.read((char*)&s, sizeof(student));
		file_l.close();
		if (s.kurs == kurs && s.matematic == matematic && s.prizv == prizv)
			return m;
		if (
			(s.kurs < kurs)
			|| (s.kurs == kurs && s.matematic < matematic)
			|| (s.kurs == kurs && s.matematic == matematic && s.prizv < prizv)
			)
		{
			R = m - 1;
		}
		else
		{
			L = m + 1;
		}
	} while (L <= R);
	return -1;
}