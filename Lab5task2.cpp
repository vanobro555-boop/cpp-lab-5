#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <map>
#include <numeric>

using namespace std;

template <typename AllTypes> //шаблон данных любого типа
class Repository {
private:
	vector<AllTypes> storage; //массив который хранит данные любого типа
public:
	void addItem(const AllTypes& Item) { //добавляет элемент в конец
		storage.push_back(Item);
	}

	void eraseItem(int index) { //удаляет элемент по индексу
		if (index < 0 || index >= static_cast<int>(storage.size())) {
			throw out_of_range("Ошибка: индекс выходит за рамки массива!");
		}
		storage.erase(storage.begin() + index);
	}

	const AllTypes& returnItem(int index) const { //возвращает элемент массива по индексу
		if (index < 0 || index >= static_cast<int>(storage.size())) {
			throw out_of_range("Ошибка: индекс выходит за рамки массива!");
		}
		return storage[index];
	}

	int returnSize() const { //возвращает кол-во элементов массива
		return static_cast<int>(storage.size());
	}

	bool isEmpty() const { //проверяет массив на пустоту
		return storage.empty();
	}

	//работа с предикатами
	//принимает предикат и возвращает первый обьект удовлетворяющий условию
	const AllTypes& findFirst(function<bool(const AllTypes&)> predicate) const {
		for (int i = 0; i < static_cast<int>(storage.size()); i++) {
			if (predicate(storage[i])) { //если ответ да, то возвращаем элемент удовл условию
				return storage[i];
			}
		}
		throw runtime_error("Элемент, удовлетворяющий условию, не найден!");
	}

	//принимает предикат и возвращает новый репозиторий удовлетворяющий условию
	Repository<AllTypes> filter(function<bool(const AllTypes&)> predicate) {
		Repository<AllTypes> filterRepository; //создаем новый обьект
		for (int i = 0; i < static_cast<int>(storage.size()); i++) {
			if (predicate(storage[i])) { //если да, то добавляем эл удовл условию в конец
				filterRepository.addItem(storage[i]);
			}
		}
		return filterRepository; //возвращаем этот обьект
	}

	//принимает компортаор сортирующий элементы в массиве
	void sortBy(function<bool(const AllTypes&, const AllTypes&)> comporator) {
		sort(storage.begin(), storage.end(), comporator);
	}

	//возвращает все элементы контейнера удовл условию
	vector<AllTypes> findAll(function<bool(const AllTypes&)> predicate) {
		if (storage.empty()) {
			throw invalid_argument("Ошбка: пустой массив, нечего сравнивать!");
		}
		vector<AllTypes> newStorage;
		copy_if(storage.begin(), storage.end(), back_inserter(newStorage), predicate);

		if (newStorage.empty()) {
			throw runtime_error("Ошибка: элементы, удовлетворяющие условию, не найдены.");
		}
		return newStorage;
	}

	//считает кол-во элементов удовл условию
	int countIf(function <bool(const AllTypes&)> predicate) {
		if (storage.empty()) {
			throw invalid_argument("Ошбка: пустой массив, нечего сравнивать!");
		}
		int count = 0;
		for (int i = 0; i < storage.size(); i++) {
			if (predicate(storage[i])) {
				count++;
			}
		}
		if (count == 0) {
			throw runtime_error("Ошибка: не существует элементов в массиве, удовлетворяющих условию.");
		}

		return count;
	}

	//преобразует каждый элемент массива с помощью заданной функции
	template<typename Final>
	vector<Final> transformAll(function<Final(const AllTypes&)> transformFunction) {
		if (storage.empty()) {
			throw invalid_argument("Ошбка: пустой массив, нечего сравнивать!");
		}
		vector<Final> newStorage;
		newStorage.reserve(storage.size());
		
		transform(storage.begin(), storage.end(), back_inserter(newStorage), transformFunction);
		return newStorage;
	}

	//группирует элементы коллекции по ключу, вычисляемому для каждого элемента
	template<typename Key>
	map<Key, vector<AllTypes>> groupBy(function<Key(const AllTypes&)> KeyExtractor) {
		map<Key, vector<AllTypes>> newMap;
		for (size_t i = 0; i < storage.size(); i++) {
			Key key = KeyExtractor(storage[i]);
			newMap[key].push_back(storage[i]);
		}
		return newMap;
	}

	//сворачивает коллекцию в одно значение, последовательно применяя заданную операцию
	template <typename Final, typename Accumulator>
	Final reduce(Final initialValue, Accumulator accumulator) {
		if (storage.empty()) {
			throw invalid_argument("Ошибка: передана пустая коллекция в reduce.");
		}
		return accumulate(storage.begin(), storage.end(), initialValue, accumulator);
	}
};

class Animal {
private:
	int m_age;
	double m_weight;
	string m_species;
public:
	//конструктор по умолчанию
	Animal() {}

	//конструктор с параметрами
	Animal(int age, double weight, string species) : m_age(age), m_weight(weight), m_species(species) {}

	//чистые виртуальные функции
	virtual void makeTheSound() = 0;
	virtual void toEat() = 0;
	virtual void toDescribe() = 0;

	//геттеры
	int getAge() const {
		return m_age;
	}

	double getWeight() const {
		return m_weight;
	}

	string getSpecies() const {
		return m_species;
	}

	//обычный метод для демонстрации раннего полиморфизма
	void sleep() const {
		cout << m_species << " спит" << endl;
	}

	//виртуальные деструктор
	virtual ~Animal() {}
};

//подкласс лев
class Lion : public Animal {
private:
	double m_runningSpeed; //скорость бега
public:
	Lion(int age, double weight, string species, double runningSpeed) : Animal(age, weight, species), m_runningSpeed(runningSpeed) {}

	double getRunningSpeed() const {
		return m_runningSpeed;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Лев рычит" << endl;
	}

	virtual void toEat() override {
		cout << "Лев ест мясо" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Лев" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "runningSpeed: " << getRunningSpeed() << endl;
	}
};

//подкласс слон
class Elephant : public Animal {
private:
	double m_earSize; //размер ушей
public:
	Elephant(int age, double weight, string species, double earSize) : Animal(age, weight, species), m_earSize(earSize) {}

	double getEarSize() const {
		return m_earSize;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Слон трубит" << endl;
	}

	virtual void toEat() override {
		cout << "Слон ест листья" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Слон" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "earSize: " << getEarSize() << endl;
	}
};

//подкласс пингвин
class Penguin : public Animal {
private:
	int m_flockSize; //размер стаи
public:
	Penguin(int age, double weight, string species, int flockSize) : Animal(age, weight, species), m_flockSize(flockSize) {}

	int getFlockSize() const {
		return m_flockSize;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Пингвин пищит" << endl;
	}

	virtual void toEat() override {
		cout << "Пингвин ест рыбу" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Пингвин" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "flockSize: " << getFlockSize() << endl;
	}
};

//подкласс дельфин
class Dolphin : public Animal {
private:
	double m_jumpHeight;
public:
	Dolphin(int age, double weight, string species, double jumpHeight) : Animal(age, weight, species), m_jumpHeight(jumpHeight) {}

	double getJumpHeight() const {
		return m_jumpHeight;
	}

	//переопределение методов
	virtual void makeTheSound() override {
		cout << "Дельфин издает какой-то звук" << endl;
	}

	virtual void toEat() override {
		cout << "Дельфин ест рыбу" << endl;
	}

	virtual void toDescribe() override {
		cout << "Животное: Дельфин" << endl;
		cout << "age: " << getAge() << endl;
		cout << "weight: " << getWeight() << endl;
		cout << "species: " << getSpecies() << endl;
		cout << "jumpHeight: " << getJumpHeight() << endl;
	}
};

int main() {
	setlocale(LC_ALL, "RU");

	//демонстрация с int
	Repository<int> intRepository;
	intRepository.addItem(5);
	intRepository.addItem(15);
	intRepository.addItem(10);
	intRepository.addItem(8);
	intRepository.addItem(22);

	// findAll
	auto evens = intRepository.findAll([](int n) { return n % 2 == 0; });
	cout << "findALL (четные): ";
	for (int n : evens) cout << n << " ";
	cout << endl;

	// countIf
	int bigCount = intRepository.countIf([](int n) { return n > 10; });
	cout << "countIf (> 10): " << bigCount << endl;

	// transformAll
	auto doubled = intRepository.transformAll<int>([](int n) { return n * 2; });
	cout << "transformAll (умножить на 2): ";
	for (int n : doubled) cout << n << " ";
	cout << "\n";

	// reduce (сумма)
	int sum = intRepository.reduce<int>(0, [](int acc, int n) { return acc + n; });
	cout << "reduce (сумма всех): " << sum << "\n";

	// groupBy (по признаку четности)
	auto groupedInts = intRepository.groupBy<bool>([](int n) { return n % 2 == 0; });
	cout << "groupBy (четных чисел в группе): " << groupedInts[true].size() << " шт.\n\n";

	//демонстрация со string
	Repository<string> stringRepository;
	stringRepository.addItem("Apple");
	stringRepository.addItem("Banana");
	stringRepository.addItem("Apricot");
	stringRepository.addItem("Cherry");

	// findALL
	auto aWords = stringRepository.findAll([](const string& s) { return s[0] == 'A'; });
	cout << "findALL (на букву 'A'): ";
	for (const string& s : aWords) cout << s << " ";
	cout << "\n";

	// transformAll (string -> size_t)
	auto lengths = stringRepository.transformAll<size_t>([](const string& s) { return s.length(); });
	cout << "transformAll (длины слов): ";
	for (size_t len : lengths) cout << len << " ";
	cout << "\n";

	// reduce (конкатенация)
	string concat = stringRepository.reduce(string(""), [](const string& acc, const string& s) {
		return acc.empty() ? s : acc + ", " + s;
		});
	cout << "reduce (объединение): " << concat << "\n\n";

	//демонстрация с Animal
	Repository<Animal*> animalRepository;
	animalRepository.addItem(new Lion(5, 190.0, "Лев", 50.0));
	animalRepository.addItem(new Elephant(10, 3000.0, "Слон", 2.0));
	animalRepository.addItem(new Penguin(2, 30.0, "Пингвин", 100));
	animalRepository.addItem(new Dolphin(2, 30.0, "Дельфин", 2.0));

	// findALL
	auto heavyAnimals = animalRepository.findAll([](Animal* a) { return a->getWeight() > 100; });
	cout << "findALL (тяжелее 100 кг):\n";
	for (Animal* a : heavyAnimals) cout << " - " << a->getSpecies() << " (" << a->getWeight() << " кг)\n";

	// countIf
	int youngCount = animalRepository.countIf([](Animal* a) { return a->getAge() < 6; });
	cout << "countIf (возраст < 6 лет): " << youngCount << " шт.\n";

	// transformAll (Animal* -> double)
	auto weights = animalRepository.transformAll<double>([](Animal* a) { return a->getWeight(); });
	cout << "transformAll (веса всех животных): ";
	for (double w : weights) cout << w << " ";
	cout << "\n";

	// reduce (общий вес)
	double totalWeight = animalRepository.reduce(0.0, [](double acc, Animal* a) { return acc + a->getWeight(); });
	cout << "reduce (общий вес зоопарка): " << totalWeight << " кг\n";

	// groupBy (по виду)
	auto groupedBySpecies = animalRepository.groupBy<string>([](Animal* a) { return a->getSpecies(); });
	cout << "groupBy (по видам):\n";
	for (const auto& pair : groupedBySpecies) {
		cout << " - Вид '" << pair.first << "': " << pair.second.size() << " шт.\n";
	}
	cout << "\n";

	//демонстрация обработки ошибок
	try {
		cout << "Попытка получить элемент по индексу 100: ";
		animalRepository.returnItem(100);
	}
	catch (const out_of_range& e) {
		cout << "Перехвачено " << e.what() << "\n";
	}

	try {
		cout << "Попытка найти животное весом > 10000 кг: ";
		animalRepository.findAll([](Animal* a) { return a->getWeight() > 10000; });
	}
	catch (const runtime_error& e) {
		cout << "Перехвачено " << e.what() << "\n";
	}

	//очистка памяти
	for (int i = 0; i < animalRepository.returnSize(); ++i) {
		delete animalRepository.returnItem(i);
	}

	return 0;
}