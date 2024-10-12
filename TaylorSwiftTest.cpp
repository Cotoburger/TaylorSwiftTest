#include <iostream>
#include <windows.h>
#include <cstdlib> // Для использования функции system()
#include <string>
#include <chrono>
#include <thread>
#include <vector>
using namespace std;
int rate;

// Функция для получения и проверки региона
bool isRegionUSA() {
	GEOID geoID = GetUserGeoID(GEOCLASS_NATION);  // Получаем ID региона пользователя

	if (geoID == GEOID_NOT_AVAILABLE) {
		cerr << "Could not determine the region." << endl;
		return false;  // Если не удалось получить регион
	}

	// Проверяем, соответствует ли регион коду США
	if (geoID == 244) {  // Код региона для США (244)
		cout << "The program is not available for execution in the United States." << endl;
		return true;
	}

	return false;  // Если регион не соответствует США
}
// Function to calculate time zone offset
int calculateTimezoneOffset() {
	// Get the current time
	auto now = std::chrono::system_clock::now();
	std::time_t currentTime = std::chrono::system_clock::to_time_t(now);

	// Convert to local time
	std::tm localTime;
	localtime_s(&localTime, &currentTime);  // On Windows (use localtime on Linux)

	// Convert to UTC time
	std::tm utcTime;
	gmtime_s(&utcTime, &currentTime);  // On Windows (use gmtime on Linux)

	// Convert local and UTC times to seconds since the start of the day
	int localSeconds = localTime.tm_hour * 3600 + localTime.tm_min * 60 + localTime.tm_sec;
	int utcSeconds = utcTime.tm_hour * 3600 + utcTime.tm_min * 60 + utcTime.tm_sec;

	// Calculate the difference in seconds between local time and UTC
	int timezoneOffsetInSeconds = localSeconds - utcSeconds;

	// Convert the difference to hours
	int timezoneOffsetHours = timezoneOffsetInSeconds / 3600;

	// Adjust the time zone offset to account for negative values and wrap around 24 hours
	if (timezoneOffsetHours < -12) {
		timezoneOffsetHours += 24;
	}
	else if (timezoneOffsetHours > 12) {
		timezoneOffsetHours -= 24;
	}

	// Output the time zone offset
	// std::cout << "Time zone offset: UTC" << (timezoneOffsetHours >= 0 ? "+" : "") << timezoneOffsetHours << std::endl;

	return timezoneOffsetHours;
}

void printProgressBar(int progress, int totalLength) {
	if (progress > 100) progress = 100;  // Убеждаемся, что прогресс не больше 100%

	int completed = (progress * totalLength) / 100;
	cout << "[";
	for (int i = 0; i < totalLength; ++i) {
		if (i < completed)
			cout << "#";
		else
			cout << " ";
	}
	cout << "] " << progress << "%";
}

// Main quiz function
void startQuiz() {
	setlocale(LC_ALL, "Ukrainian");
	const int numQuestions = 10;        // Количество вопросов
	const int totalProgress = 100;      // Процент завершения
	const int barLength = 25;           // Длина индикатора

	vector<int> progresses(numQuestions, 0);  // Прогресс для каждого вопроса

	cout << "Welcome to the quiz about Taylor Swift!" << endl;
	Sleep(500);
	cout << "Today we'll test how well you know Taylor Swift!" << endl;
	Sleep(2500);
	cout << "\n---------------------------------------------------------------------------------" << endl;
	cout << "Quiz Loading...\n";

	for (int i = 0; i < numQuestions; ++i) {
		// Пока текущий вопрос не завершён
		while (progresses[i] < totalProgress) {
			cout << "\rВопрос " << i + 1 << ": ";
			printProgressBar(progresses[i], barLength);

			progresses[i] += rand() % 50 + 1;  // Случайное увеличение для вопроса

			if (progresses[i] > totalProgress) {
				progresses[i] = totalProgress; // Ограничиваем прогресс до 100%
			}

			cout.flush();  // Обновляем вывод

			// Ускоренная задержка (с 200 мс до ~67 мс)
			this_thread::sleep_for(chrono::milliseconds(67));
		}

		// После завершения вопроса переходим к следующему
		cout << "\rВопрос " << i + 1 << ": ";
		printProgressBar(progresses[i], barLength);
		cout << endl;  // Переход на следующую строку
	}

	cout << endl << "ALL QUESTIONS DOWNLOADED" << endl;

	Sleep(444);
	system("cls"); // Очистить экран
	int result = 1;
	cout << "0. " << endl;
	cout << "What country does Taylor Swift live in ? " << endl;
	cout << "0 - Russia, 1 - Finland, 2 - USA, 3 - Greenland" << endl;
	string zero;
	cout << "0/1/2/3" << endl;
	cin >> zero;
	system("cls"); // Очистить экран
	if (zero == "3") {
		result = result - 1;
	}
	if (zero == "2") {
		result = result + 2;
	}
	if (zero == "1") {
		result = result - 1;
	}
	if (zero == "0") {
		result = result - 2;
	}

	cout << "1. " << endl;
	cout << "Are you on r/TaylorSwift?" << endl;
	string first;
	cout << "0/1" << endl;
	cin >> first;
	system("cls"); // Очистить экран
	if (first == "1") {
		result = result + 2;
	}
	if (first == "0") {
		result = result - 1;
	}

	cout << "2. " << endl;
	cout << "Are you Taylor Swift fan?" << endl;
	string second;
	cout << "0/1" << endl;
	cin >> second;
	system("cls"); // Очистить экран
	if (second == "1") {
		result = result + 2;
	}
	if (second == "0") {
		result = result - 2;
	}

	cout << "3. " << endl;
	cout << "Motherland(0) or Taylor Swift(1)?" << endl;
	string third;
	cout << "0/1" << endl;
	cin >> third;
	system("cls"); // Очистить экран
	if (third == "1") {
		result = result + 2;
	}
	if (third == "0") {
		result = result + 1;
	}

	cout << "4. " << endl;
	cout << "What is Taylor Swift's favorite cat breed?" << endl;
	cout << "0 - Scottish Fold, 1 - Russian Blue, 2 - Maine Coon" << endl;
	string four;
	cout << "0/1/2" << endl;
	cin >> four;
	system("cls"); // Очистить экран
	if (four == "2") {
		result = result - 0;
	}
	if (four == "1") {
		result = result - 1;
	}
	if (four == "0") {
		result = result + 1;
	}

	cout << "5. " << endl;
	cout << "What year was Taylor Swift born ? " << endl;
	string five;
	cout << "For example: 2024" << endl;
	cin >> five;
	system("cls"); // Очистить экран
	if (five == "1989") {
		result = result + 2;
	}
	else if (five != "1989") {
		result = result - 2;
	}

	cout << "6. " << endl;
	cout << "Which album is Taylor Swift's best-selling album in its first week of release in the USA?" << endl;
	cout << "0 - 1989, 1 - Reputation, 2 - Fearless (Taylor's Version)? 3 - Lover" << endl;
	string six;
	cout << "0/1/2/3" << endl;
	cin >> six;
	system("cls"); // Очистить экран
	if (six == "3") {
		result = result - 1;
	}
	if (six == "2") {
		result = result - 0;
	}
	if (six == "1") {
		result = result - 1;
	}
	if (six == "0") {
		result = result + 2;
	}

	cout << "7. " << endl;
	cout << "Taylor Swift is..." << endl;
	cout << "0 - Man, 1 - Woman, 2 - Girl" << endl;
	string seven;
	cout << "0/1/2" << endl;
	cin >> seven;
	system("cls"); // Очистить экран
	if (seven == "2") {
		result = result + 2;
	}
	if (seven == "1") {
		result = result + 0;
	}
	if (seven == "0") {
		result = result - 1;
	}

	cout << "8. " << endl;
	cout << "Do You support war in Ukraine" << endl;
	string eight;
	cout << "0/1" << endl;
	cin >> eight;
	system("cls"); // Очистить экран
	if (eight == "1") {
		result = result - 1;
	}
	if (eight == "0") {
		result = result + 2;
	}

	cout << "9. " << endl;
	cout << "are you subscribed to Taylor Swift tiktok?" << endl;
	string nine;
	cout << "0 - No, 1 - Yes, 2 - Maybe" << endl;
	cin >> eight;
	system("cls"); // Очистить экран
	if (nine == "2") {
		result = result - 0;
	}
	if (nine == "1") {
		result = result + 2;
	}
	if (nine == "0") {
		result = result - 1;
	}

	cout << "Almost done!" << endl;

	system("cls"); // Очистить экран
	if (result < -4) {
		rate = 0;
	}
	else if (result >= -4 && result < 0) {
		rate = 1;
	}
	else if (result >= 0 && result < 6) {
		rate = 2;
	}
	else if (result >= 6 && result < 10) {
		rate = 3;
	}
	else if (result >= 10 && result < 13) {
		rate = 4;
	}
	else if (result >= 13) {
		rate = 5;
	}

	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Let's count the points...  ";
	Sleep(500);

	for (size_t a = 0; a < 15; a++)
	{
		cout << '|';
		Sleep(100 + (rand() % 200));
	}
	system("cls"); // Очистить экран
	string end;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Your result: " << result << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	if (rate == 0) {
		end = "Kill yourself";
	}
	if (rate == 1) {
		end = "You know Taylor Swift very poorly, like REALLY BADLY. \nNothing can help you anymore.";
	}
	if (rate == 2) {
		end = "You know Taylor Swift very poorly. \nI recommend you to re-listen to all of her tracks and watch at least 100 TikToks in SwiftTok.";
	}
	if (rate == 3) {
		end = "You know Taylor Swift at the level of an ordinary garbage dude. \nI recommend watching a couple of biographies and top interesting facts about Taylor Swift on YouTube.";
	}
	if (rate == 4) {
		end = "You know Taylor Swift quite well. But still, not perfect. \nOrder a mug with Taylor Swift.";
	}
	if (rate == 5) {
		end = "You know Taylor Swift excellently! A true Swiftie!";
	}
	cout << end << endl;

	if (rate > 2) {
		Sleep(1000);
		cout << "\n\n" << endl;
		cout << "---------------------------------------------------------------------------------" << endl;
		cout << "Certificate loading...  ";
		for (size_t a = 0; a < 15; a++)
		{
			cout << '|';
			Sleep(2 + (rand() % 100));
		}
		Sleep(333);
		cout << "\n" << endl;
		cout << "___________________________________________" << endl;
		cout << "|               Certificate               |" << endl;
		cout << "|              ==============             |" << endl;
		cout << "|                                         |" << endl;
		if (rate == 3) {
			cout << "|   For a decent completion of the quiz   |" << endl;
			cout << "|       On knowledge of Taylor Swift      |" << endl;
		}
		if (rate == 4) {
			cout << "|    For a good completion of the quiz    |" << endl;
			cout << "|       On knowledge of Taylor Swift      |" << endl;
		}
		if (rate == 5) {
			cout << "|  For an AMAZING completion of the quiz  |" << endl;
			cout << "|       On knowledge of Taylor Swift      |" << endl;
		}
		cout << "|                                         |" << endl;
		cout << "-------------------------------------------" << endl;
		cout << "\n" << endl;
		if (rate >= 4) {
			cout << "You unlocked next test: Olivia Rodrigo Test!";
			cout << "\npress any button no continue.\n";
			cin.get();
		}
	
	}
	cin.get();
}

void startOlivia() {
	setlocale(LC_ALL, "Ukrainian");
	const int numQuestions = 10;        // Количество вопросов
	const int totalProgress = 100;      // Процент завершения
	const int barLength = 25;           // Длина индикатора

	vector<int> progresses(numQuestions, 0);  // Прогресс для каждого вопроса

	system("cls"); // Очистить экран
	cout << "Welcome to the quiz about Olivia Rodrigo" << endl;
	Sleep(500);
	cout << "Today we'll test how well you know Olivia Rodrigo!" << endl;
	Sleep(2500);
	cout << "\n---------------------------------------------------------------------------------" << endl;
	cout << "Quiz Loading...\n";

	for (int i = 0; i < numQuestions; ++i) {
		// Пока текущий вопрос не завершён
		while (progresses[i] < totalProgress) {
			cout << "\rВопрос " << i + 1 << ": ";
			printProgressBar(progresses[i], barLength);

			progresses[i] += rand() % 50 + 1;  // Случайное увеличение для вопроса

			if (progresses[i] > totalProgress) {
				progresses[i] = totalProgress; // Ограничиваем прогресс до 100%
			}

			cout.flush();  // Обновляем вывод

			// Ускоренная задержка (с 200 мс до ~67 мс)
			this_thread::sleep_for(chrono::milliseconds(67));
		}

		// После завершения вопроса переходим к следующему
		cout << "\rВопрос " << i + 1 << ": ";
		printProgressBar(progresses[i], barLength);
		cout << endl;  // Переход на следующую строку
	}

	cout << endl << "ALL QUESTIONS DOWNLOADED" << endl;

	Sleep(444);
	system("cls"); // Очистить экран
	int result = 1;
	rate = 0;
	cout << "0. " << endl;
	cout << "What is the name of Olivia Rodrigo's debut album?" << endl;
	cout << "0 - Fearless, 1 - SOUR, 2 - Red" << endl;
	string zero;
	cout << "0/1/2" << endl;
	cin >> zero;
	system("cls"); // Очистить экран
	if (zero == "2") {
		result = result - 1;
	}
	if (zero == "1") {
		result = result + 2;
	}
	if (zero == "0") {
		result = result - 1;
	}

	cout << "1. " << endl;
	cout << "In what year was the SOUR album released?" << endl;
	cout << "0 - 2021, 1 - 2020, 2 - 2019" << endl;
	string first;
	cout << "0/1/2" << endl;
	cin >> first;
	system("cls"); // Очистить экран
	if (first == "2") {
		result = result - 1;
	}
	if (first == "1") {
		result = result + 0;
	}
	if (first == "0") {
		result = result + 1;
	}

	cout << "2. " << endl;
	cout << "Which song was Olivia Rodrigo's first major hit?" << endl;
	cout << "0 - good 4 u, 1 - drivers license, 2 - deja vu" << endl;
	string second;
	cout << "0/1" << endl;
	cin >> second;
	system("cls"); // Очистить экран
	if (first == "2") {
		result = result + 0;
	}
	if (second == "1") {
		result = result + 0;
	}
	if (second == "0") {
		result = result + 2;
	}

	cout << "3. " << endl;
	cout << "What role did Olivia Rodrigo play in the series High School Musical: The Musical: The Series?" << endl;
	cout << "0 - Nini Salazar-Roberts, 1 - Ashlyn Caswell, 2 - Gina Porter" << endl;
	string third;
	cout << "0/1" << endl;
	cin >> third;
	system("cls"); // Очистить экран
	if (third == "2") {
		result = result + 0;
	}
	if (third == "1") {
		result = result - 1;
	}
	if (third == "0") {
		result = result + 2;
	}

	cout << "4. " << endl;
	cout << "In which country was Olivia Rodrigo born?" << endl;
	cout << "0 - USA, 1 - Canada, 2 - United Kingdom" << endl;
	string four;
	cout << "0/1/2" << endl;
	cin >> four;
	system("cls"); // Очистить экран
	if (four == "2") {
		result = result - 1;
	}
	if (four == "1") {
		result = result - 1;
	}
	if (four == "0") {
		result = result + 1;
	}

	cout << "5. " << endl;
	cout << "Which Olivia Rodrigo song was nominated for a Grammy Award for Song of the Year? " << endl;
	cout << "0 - traitor, 1 - drivers license, 2 - brutal" << endl;
	string five;
	cin >> five;
	system("cls"); // Очистить экран
	if (five == "2") {
		result = result - 1;
	}
	if (five == "1") {
		result = result + 2;
	}
	if (five == "0") {
		result = result + 0;
	}

	cout << "6. " << endl;
	cout << "What is Olivia Rodrigo's heritage?" << endl;
	cout << "0 - American and Filipino, 1 - American and Mexican, 2 - American and Italian" << endl;
	string six;
	cout << "0/1/2/3" << endl;
	cin >> six;
	system("cls"); // Очистить экран
	if (six == "2") {
		result = result - 1;
	}
	if (six == "1") {
		result = result - 1;
	}
	if (six == "0") {
		result = result + 2;
	}

	cout << "7. " << endl;
	cout << "How many Grammy Awards did Olivia Rodrigo win in 2022?" << endl;
	cout << "0 - 1, 1 - 2, 2 - 3" << endl;
	string seven;
	cout << "0/1/2" << endl;
	cin >> seven;
	system("cls"); // Очистить экран
	if (seven == "2") {
		result = result + 2;
	}
	if (seven == "1") {
		result = result + 0;
	}
	if (seven == "0") {
		result = result - 1;
	}

	cout << "8. " << endl;
	cout << "What is the name of Olivia Rodrigo's second studio album?" << endl;
	cout << "0 - GUTS, 1 - SOUR 2, 2 - SUP" << endl;
	string eight;
	cout << "0/1" << endl;
	cin >> eight;
	system("cls"); // Очистить экран
	if (seven == "2") {
		result = result + 1;
	}
	if (seven == "1") {
		result = result - 1;
	}
	if (seven == "0") {
		result = result - 1;
	}

	cout << "9. " << endl;
	cout << "Which Olivia Rodrigo song became popular on TikTok?" << endl;
	string nine;
	cout << "0 - happier, 1 - good 4 u, 2 - jealousy, jealousy" << endl;
	cin >> eight;
	system("cls"); // Очистить экран
	if (nine == "2") {
		result = result - 1;
	}
	if (nine == "1") {
		result = result + 2;
	}
	if (nine == "0") {
		result = result - 1;
	}

	cout << "Almost done!" << endl;
	int rate;
	system("cls"); // Очистить экран
	if (result < -4) {
		rate = 0;
	}
	else if (result >= -4 && result < 0) {
		rate = 1;
	}
	else if (result >= 0 && result < 6) {
		rate = 2;
	}
	else if (result >= 6 && result < 10) {
		rate = 3;
	}
	else if (result >= 10 && result < 13) {
		rate = 4;
	}
	else if (result >= 13) {
		rate = 5;
	}

	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Let's count the points...  ";
	Sleep(500);

	for (size_t a = 0; a < 15; a++)
	{
		cout << '|';
		Sleep(100 + (rand() % 200));
	}
	system("cls"); // Очистить экран
	string end;
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << "Your result: " << result << endl;
	cout << "---------------------------------------------------------------------------------" << endl;
	if (rate == 0) {
		end = "Kill yourself";
	}
	if (rate == 1) {
		end = "You know Olivia Rodrigo very poorly, like REALLY BADLY. \nNothing can help you anymore.";
	}
	if (rate == 2) {
		end = "You know Olivia Rodrigo very poorly. \nI recommend you to re-listen to all of her tracks and watch at least 100 TikToks";
	}
	if (rate == 3) {
		end = "You know Olivia Rodrigo at the level of an ordinary garbage dude. \nI recommend watching a couple of biographies and top interesting facts about Taylor Swift on YouTube.";
	}
	if (rate == 4) {
		end = "You know Olivia Rodrigo quite well. But still, not perfect. \nOrder a mug with Taylor Swift.";
	}
	if (rate == 5) {
		end = "You know Olivia excellently!\n\n";
	}
	cout << end << endl;
	cout << "This test does not support certificate for now.";
	cin.get();
}

int main() {
	// Проверка региона
	if (isRegionUSA()) {
		cin.get();
		return 1;  // Завершаем программу, если пользователь в США
	}

	int timezoneOffsetHours = calculateTimezoneOffset();

	// Check if the time zone corresponds to US time zones (UTC-4 to UTC-10)
	if (timezoneOffsetHours <= -4 && timezoneOffsetHours >= -10) {
		std::cout << "The program is not available for execution in the United States." << std::endl;

	}

	// Start the quiz if time zone is valid
	startQuiz();
	if (rate >= 4) {
		startOlivia();
	}
	cin.get();
}