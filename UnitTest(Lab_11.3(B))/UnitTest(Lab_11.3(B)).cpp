#include "pch.h"
#include "CppUnitTest.h"
#include "../Lab_11.3(B)/Lab_11.3(B).cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTestLab113B
{
	TEST_CLASS(UnitTestLab113B)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			student s;
			student str_a;
			student str_b;
			student str;

			fstream file_s("E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_11.3(B)\\Lab_11.3(B)\\test", ios::binary);

			s.prizv = "swwe";
			s.kurs = 2;
			s.specialization = (Special)2;
			s.phisuka = 4;
			s.matematic = 5;
			s.pedahohica = 4;

			file_s.write((char*)&s, sizeof(student));
			file_s.close();

			file_s.open("E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_11.3(B)\\Lab_11.3(B)\\test", ios::binary);

			s.prizv = "eeeew";
			s.kurs = 2;
			s.specialization = (Special)3;
			s.phisuka = 2;
			s.matematic = 3;
			s.pedahohica = 4;

			file_s.write((char*)&s, sizeof(student));
			file_s.close();


			file_s.open("E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_11.3(B)\\Lab_11.3(B)\\test", ios::binary);

			s.prizv = "sfgdf";
			s.kurs = 2;
			s.specialization = (Special)4;
			s.phisuka = 4;
			s.matematic = 2;
			s.pedahohica = 4;

			file_s.write((char*)&s, sizeof(student));
			file_s.close();

			fstream f;
			SortBIN(str, str_a, str_b, 3, "E:\\Моя папка. Навчання\\Student [IK-11] [Дорожовець]\\Lab_11.3(B)\\Lab_11.3(B)\\test", f);

			file_s.read((char*)&s, sizeof(student));
			Assert::AreEqual(s.matematic, 2);
			file_s.close();
		}
	};
}
