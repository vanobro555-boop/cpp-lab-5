#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <functional>
#include <algorithm>

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
		throw runtime_error("в массиве нет ни одного четного числа");
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


	try {
		intRepository.returnItem(3);
	}
	catch (const out_of_range& error) {
		cout << error.what() << endl;
	}

	//лямбда-функция которая проверяет условие четности числа
	auto firstEven = intRepository.findFirst([](const int& intVectorValue) {
		return (intVectorValue % 2 == 0);
		});
	cout << "первое четное число в массиве - " << firstEven << endl;

	//демонстрация со string

	Repository<string> stringRepository;
	stringRepository.addItem("Apple");
	stringRepository.addItem("Lemon");
	stringRepository.addItem("Banana");

	//лямбда функция которая ищет элемент который начинается с нужной буквы
	Repository<string> findWord = stringRepository.filter([](const string& stringVectorValue) {
		return (stringVectorValue[0] == 'A');
		});
	cout << "Найдено слов на 'A': " << findWord.returnSize() << endl;

	//демонстрация иерархии и полиморфизма
	Repository<Animal*> animals;

	animals.addItem(new Lion(5, 190.0, "Лев", 50));
	animals.addItem(new Elephant(10, 3000.0, "Слон", 2));
	animals.addItem(new Penguin(2, 30.0, "Пингвин", 100));
	animals.addItem(new Dolphin(2, 30.0, "Дельфин", 2));

	//ищем первое животное тяжелее 1000 кг
	auto heavyAnimal = animals.findFirst([](Animal* animalVectorValue) {
		return animalVectorValue->getWeight() > 1000;
		});
	cout << "Первое тяжелое животное: " << heavyAnimal->getSpecies() << " Вес: " << heavyAnimal->getWeight() << " кг\n";

	//демонстрация ошибки, пытаемся найти животное по ошибочному параметру
	try {
		auto impossibleAnimal = animals.findFirst([](Animal* animalVectorValue) {
			return animalVectorValue->getWeight() > 10000; // Условие, которое никогда не выполнится
			});
		cout << impossibleAnimal->getSpecies() << "\n";
	}
	catch (const runtime_error& error) {
		cout << error.what() << endl;
	}

	//оставляем только молодых животных (возраст < 6 лет)
	Repository<Animal*> youngZoo = animals.filter([](Animal* animalVectorValue) {
		return animalVectorValue->getAge() < 6;
		});
	cout << "Молодых животных в зоопарке: " << youngZoo.returnSize() << endl;

	//сортируем всех животных по весу (от легких к тяжелым)
	animals.sortBy([](Animal* a, Animal* b) {
		return a->getWeight() < b->getWeight();
		});

	cout << "Животные после сортировки по весу:\n";
	for (int i = 0; i < animals.returnSize(); ++i) {
		Animal* a = animals.returnItem(i);
		cout << i + 1 << ". " << a->getSpecies() << " (" << a->getWeight() << " кг)\n";
		a->makeTheSound();
	}

	// Очистка памяти
	for (int i = 0; i < animals.returnSize(); ++i) {
		delete animals.returnItem(i);
	}

	return 0;
}