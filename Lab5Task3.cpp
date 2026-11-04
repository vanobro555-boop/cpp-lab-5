#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

template <typename AllTypes>
class DynamicArray {
private:
	AllTypes* m_array; //указатель на массив
	size_t m_size; //текущий размер массива
	size_t m_capacity; // текущая выделенная емкость
	size_t m_max_capacity; // предел расширения массива

	//метод расширенния массива
	void expand() {
		if (m_capacity >= m_max_capacity) {
			throw overflow_error("Ошибка: достигнут максимальный предел");
		}
		size_t new_capacity = 0;

		if (m_capacity == 0) {
			new_capacity = 2;
		}
		else {
			new_capacity = m_capacity * 2;
		}
		AllTypes* new_array = new AllTypes[new_capacity];

		//копируем данные в новый массив
		for (int i = 0; i < m_size; i++) {
			new_array[i] = m_array[i];
		}

		delete[] m_array;
		m_array = new_array;
		m_capacity = new_capacity;
	}
public:

	//конструктор
	DynamicArray(size_t initial_capacity = 2, size_t max_capacity = 10)
		: m_size(0), m_capacity(initial_capacity), m_max_capacity(max_capacity) {
		if (m_capacity == 0) {
			m_capacity = 1;
		}
		m_array = new AllTypes[m_capacity];
	}

	//деструктор
	~DynamicArray() {
		delete[] m_array;
	}

	//конструктор копирования
	DynamicArray(const DynamicArray& other)
		: m_size(other.m_size), m_capacity(other.m_capacity), m_max_capacity(other.m_max_capacity) {
		m_array = new AllTypes[m_capacity];
		for (size_t i = 0; i < m_size; ++i) {
			m_array[i] = other.m_array[i];
		}
	}

	// Оператор присваивания
	DynamicArray& operator=(const DynamicArray& other) {
		if (this != &other) {
			delete[] m_array;
			m_capacity = other.m_capacity;
			m_max_capacity = other.m_max_capacity;
			m_size = other.m_size;
			m_array = new AllTypes[m_capacity];
			for (size_t i = 0; i < m_size; ++i) {
				m_array[i] = other.m_array[i];
			}
		}
		return *this;
	}

	//Добавление элемента (с автоматическим расширением)
	void addItem(const AllTypes& item) {
		if (m_size == m_capacity) {
			expand(); // Пытаемся расширить. Если нельзя, expand() выбросит ошибку
		}
		m_array[m_size++] = item;
	}

	//Извлечение элемента (удаляет и возвращает последний элемент)
	AllTypes extractItem() {
		if (isEmpty()) {
			throw underflow_error("Ошибка: извлечение из пустого хранилища!");
		}
		return m_array[--m_size];
	}

	//Доступ по индексу (неконстантная версия для изменения)
	AllTypes& operator[](size_t index) {
		if (index >= m_size) {
			throw out_of_range("Ошибка: выход за границы массива при записи!");
		}
		return m_array[index];
	}

	//Доступ по индексу (константная версия для чтения)
	const AllTypes& operator[](size_t index) const {
		if (index >= m_size) {
			throw out_of_range("Ошибка: выход за границы массива при чтении!");
		}
		return m_array[index];
	}

	//Проверка на пустоту
	bool isEmpty() const {
		return m_size == 0;
	}

	//Проверка на заполненность (достигнут ли абсолютный максимум)
	bool isFull() const {
		return m_size == m_max_capacity;
	}

	//Получение размера и вместимости
	size_t getSize() const {
		return m_size;
	}

	size_t getCapacity() const {
		return m_capacity;
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
	// Создаем массив с начальной емкостью 2 и макс. пределом 5
	DynamicArray<int> intArray(2, 5);

	cout << "Начальная емкость: " << intArray.getCapacity() << "\n";
	intArray.addItem(10);
	intArray.addItem(20);
	cout << "После 2 добавлений емкость: " << intArray.getCapacity() << " (произошло расширение!)\n";

	intArray.addItem(30); // Емкость станет 4
	intArray.addItem(40);
	intArray.addItem(50); // Емкость станет 5 (максимум)

	cout << "Элемент по индексу 2: " << intArray[2] << "\n";
	cout << "Извлеченный элемент: " << intArray.extractItem() << "\n";
	cout << "Размер после извлечения: " << intArray.getSize() << "\n\n";

	//демонстрация с double
	DynamicArray<double> doubleArray(3);
	doubleArray.addItem(3.14);
	doubleArray.addItem(2.71);
	cout << "Сумма элементов: " << doubleArray[0] + doubleArray[1] << "\n\n";

	//демонстация с string
	DynamicArray<string> stringArray(2);
	stringArray.addItem("Привет");
	stringArray.addItem("Мир");
	cout << "Объединенная строка: " << stringArray[0] << ", " << stringArray[1] << "\n\n";

	//демонстрация с Animal
	DynamicArray<Animal*> animalArray(3);

	animalArray.addItem(new Lion(5, 190.0, "Лев", 50));
	animalArray.addItem(new Elephant(10, 3000.0, "Слон", 3));
	animalArray.addItem(new Penguin(10, 30.0, "Пингвин", 100));
	animalArray.addItem(new Dolphin(7, 150.0, "Дельфин", 2));

	cout << "Животное под индексом 1: ";
	animalArray[1]->makeTheSound(); // Полиморфный вызов

	// Извлекаем и сразу удаляем, чтобы не было утечки памяти
	Animal* extractedAnimal = animalArray.extractItem();
	cout << "Извлечено и удалено животное: " << extractedAnimal->getSpecies() << "\n";
	delete extractedAnimal;

	// Очистка оставшихся элементов
	while (!animalArray.isEmpty()) {
		delete animalArray.extractItem();
	}
	cout << "\n";

	//демонстрация обработки ошибок
	// Создаем массив с жестким лимитом в 2 элемента для быстрой демонстрации
	DynamicArray<int> testArray(1, 2);
	testArray.addItem(100);
	testArray.addItem(200); // Здесь емкость расширится до максимума (2)

	// Ошибка 1: Добавление в заполненное хранилище
	try {
		cout << "Попытка добавить 3-й элемент в массив с макс. емкостью 2... ";
		testArray.addItem(300);
	}
	catch (const overflow_error& e) {
		cout << "Перехвачено " << e.what() << "\n";
	}

	// Ошибка 2: Извлечение из пустого хранилища
	try {
		testArray.extractItem(); // Теперь размер 1
		testArray.extractItem(); // Теперь размер 0 (пусто)
		cout << "Попытка извлечь элемент из пустого массива... ";
		testArray.extractItem();
	}
	catch (const underflow_error& e) {
		cout << "Перехвачено " << e.what() << "\n";
	}

	// Ошибка 3: Выход за границы при доступе
	try {
		cout << "Попытка обратиться к индексу 5 в пустом массиве... ";
		cout << testArray[5] << "\n";
	}
	catch (const out_of_range& e) {
		cout << "Перехвачено " << e.what() << "\n";
	}
	return 0;
}