#include "pch.h"
#include "CppUnitTest.h"
#include "../main-project/protocol.h"
#include "../main-project/processing.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace unittestproject
{

	// вспомогательная функция для создания одной записи
	protocol* build_result(int start_hour, int start_min, int start_sec, int finish_hour, int finish_min, int finish_sec, char* program_path)
	{
		protocol* result = new protocol;
		result->start.hour = start_hour;
		result->start.min = start_min;
		result->start.sec = start_sec;
		result->end.hour = finish_hour;
		result->end.min = finish_min;
		result->end.sec = finish_sec;
		strcpy_s(result->path, program_path);
		return result;
	}

	// вспомогательная функция для удаления массива тестовых данных
	void delete_result(protocol* array[], int size)
	{
		for (int i = 0; i < size; i++)
		{
			delete array[i];
		}
	}

	TEST_CLASS(unittestproject)
	{
	public:

		TEST_METHOD(TestMethod1) // Стандартная ситуация 1
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "CSGO");
			protocol* results[3];
			results[0] = build_result(11, 03, 22, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //26581
			results[1] = build_result(14, 24, 51, 16, 44, 56, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //8405
			results[2] = build_result(19, 30, 00, 20, 43, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //4403
			Assert::AreEqual(39389, process(results, 3, program));
			delete_result(results, 3);
		}

		TEST_METHOD(TestMethod2) // Стандартная ситуация 2
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "CSGO");
			protocol* results[3];
			results[0] = build_result(11, 03, 22, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //26581
			results[1] = build_result(14, 24, 51, 16, 44, 56, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //8405
			results[2] = build_result(19, 30, 00, 20, 43, 23, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //4403
			Assert::AreEqual(34986, process(results, 3, program));
			delete_result(results, 3);
		}

		TEST_METHOD(TestMethod3) // Стандартная ситуация 3
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "CSGO");
			protocol* results[3];
			results[0] = build_result(11, 03, 22, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\microsoft.exe"); //26581
			results[1] = build_result(14, 24, 51, 16, 44, 56, "C:\\Users\\User\\Desktop\\Programs\\Steam\\cmd.exe"); //8405
			results[2] = build_result(19, 30, 00, 20, 43, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\skype.exe"); //4403
			Assert::AreEqual(0, process(results, 3, program));
			delete_result(results, 3);
		}

		TEST_METHOD(TestMethod4) // CamelCase
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "CsGo");
			protocol* results[3];
			results[0] = build_result(11, 03, 22, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //26581
			results[1] = build_result(14, 24, 51, 16, 44, 56, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //8405
			results[2] = build_result(19, 30, 00, 20, 43, 23, "C:\\Users\\User\\Desktop\\Programs\\Steam\\CSGO.exe"); //4403
			Assert::AreEqual(39389, process(results, 3, program));
			delete_result(results, 3);
		}

		TEST_METHOD(TestMethod5) // Необычное время
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "Skype");
			protocol* results[3];
			results[0] = build_result(00, 00, 00, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //66383
			results[1] = build_result(14, 24, 51, 0, 0, 0, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //51891
			results[2] = build_result(22, 00, 00, 00, 00, 00, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //79200
			Assert::AreEqual(197474, process(results, 3, program));
			delete_result(results, 3);
		}

		TEST_METHOD(TestMethod6) // Нестандартный ввод 1
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "Skype.exe");
			protocol* results[3];
			results[0] = build_result(00, 00, 00, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //66383
			results[1] = build_result(14, 24, 51, 0, 0, 0, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //51891
			results[2] = build_result(22, 00, 00, 00, 00, 00, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //79200
			Assert::AreEqual(197474, process(results, 3, program));
			delete_result(results, 3);
		}

		TEST_METHOD(TestMethod7) // Нестандартный ввод 2
		{
			char* program = new char[MAX_STRING_SIZE];
			strcpy_s(program, MAX_STRING_SIZE, "SkYpE.eXe");
			protocol* results[3];
			results[0] = build_result(00, 00, 00, 18, 26, 23, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //66383
			results[1] = build_result(14, 24, 51, 0, 0, 0, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //51891
			results[2] = build_result(22, 00, 00, 00, 00, 00, "C:\\Users\\User\\Desktop\\Programs\\Skype\\Skype.exe"); //79200
			Assert::AreEqual(197474, process(results, 3, program));
			delete_result(results, 3);
		}
	};
}
