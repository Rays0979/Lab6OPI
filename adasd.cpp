#include <iostream>
#include <string>
#include <Windows.h>
using namespace std;
const char* names[5]
{
    "Phone", "Case", "Laptop", "Mouse", "Keyboard"
};
int prices[5] = { 12000, 300, 32000, 600, 1500 };
struct database
{
    char tovar[20];
    int price;
};
database mass[5];
int indbase = 0;
bool flagsearch = false;
int indforsearch;
char query[50];
void showProducts()
{
    cout << "Каталог товарів:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << i + 1 << ". " << names[i] << " — " << prices[i] << " грн" << endl;
    }
}

void printKosh()
{
    cout << "\n=== ВАШ КОШИК ===" << endl;
    if (indbase == 0) cout << "Кошик порожній." << endl;
    for (int i = 0; i < indbase; i++)
    {
        cout << i + 1 << ". " << mass[i].tovar << " || " << mass[i].price << " $$" << endl;
    }
}
void del()
{
   int index = 0;
    cout << "Введіть індекс товару" << endl;
    cin >> index;
	if (index>indbase)
	{
		cout << "Товару з таким індексом немає" << endl;
	}
	else
	{
		for (index; index < indbase; index++)
    	{
        strcpy_s(mass[index].tovar, mass[index + 1].tovar);
        mass[index].price = prices[index + 1];
    	}
		indbase--;
	}
    printKosh();
}
void sum()
{
    int total = 0;
    for (int i = 0; i < indbase; i++)
    {
        total += mass[i].price;
    }
    cout << "\nСума усіх товарів : " << total << " грн" << endl;
}
void check(char fullname[50], char phone[50], char email[50],
    char delivery[50], char address[50], char payment[50],
    char card[50], char exp[10], char cvv[10])
{
    cout << "========================" << endl;
    cout << "ЗАМОВЛЕННЯ ПІДТВЕРДЖЕНО" << endl;
    cout << "Покупець: " << fullname << endl;
    cout << "Телефон: " << phone << endl;
    cout << "Email: " << email << endl;
    cout << "Доставка: " << delivery << ", адреса: " << address << endl;
    cout << "Оплата: " << payment << endl;

    sum();
    cout << "========================" << endl;
    exit(0);
}
bool validateEmail(const char* email)
{
    const char* at = strchr(email, '@');
    if (!at)
        return false;

    if (at == email)
        return false;

    const char* dot = strchr(at + 1, '.');
    if (!dot)
        return false;

    if (dot == at + 1)
        return false;

    if (strlen(dot + 1) < 2)
        return false;

    return true;
}


bool isDigits(const char* s)
{
    for (int i = 0; s[i]; i++)
        if (!isdigit(s[i]))
            return false;
    return true;
}

// Перевірка ПІБ
bool validateName(const char* name)
{
    int words = 0;
    bool inWord = false;

    for (int i = 0; name[i]; i++)
    {
        unsigned char ch = (unsigned char)name[i];

        if (ch == ' ')
        {
            inWord = false;
        }
        else
        {
            if (!isalpha(ch))
                return false;

            if (!inWord)
            {
                inWord = true;
                words++;
            }
        }
    }
    return words == 3;
}


// Безпечний ввід числа
bool safeInt(int& x)
{
    cin >> x;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(1000, '\n');
        return false;
    }
    cin.ignore();
    return true;
}

void order()
{
    char fullname[50];
    char phone[50];
    char email[50];
    char delivery[50];
    char address[50];
    char payment[50];
    char card[50];
    char exp[10];
    char cvv[10];

    int answer;

    cout << "=================" << endl;
    cout << "ОФОРМЛЕННЯ ЗАМОВЛЕННЯ" << endl;

    cin.ignore();

    // ПІБ
    while (true)
    {
        cout << "Введіть ПІБ (3 слова, тільки букви): ";
        cin.getline(fullname, 50);

        if (validateName(fullname))
            break;

        cout << "Помилка! ПІБ має містити тільки літери і складатися з 3 слів!\n";
    }

    // телефон
    while (true)
    {
        cout << "Номер телефону (формат +380XXXXXXXXX): ";
        cin.getline(phone, 50);

        if (strncmp(phone, "+380", 4) == 0 &&
            strlen(phone) == 13 &&
            isDigits(phone + 4))
        {
            break;
        }
        cout << "Помилка! Введіть номер у форматі +380XXXXXXXXX\n";
    }

    // email
    while (true)
    {
        cout << "Email: ";
        cin.getline(email, 50);
        if (validateEmail(email))
            break;
        cout << "Email некоректний! Має містити @ і .\n";
    }

    bool flag = true;
    // доставка
    while (flag)
    {
        cout << "Спосіб доставки (1 - кур'єр || 2 - поштомат || 3 - відділення): ";
        cin >> answer;
        if (answer == 1)
        {
            strcpy_s(delivery, "кур'єр");
            break;
        }
        else if (answer == 2)
        {
            strcpy_s(delivery, "поштомат");
            break;
        }
        else if (answer == 3)
        {
            strcpy_s(delivery, "відділення");
            break;
        }
        else
        {
            cout << "ПОМИЛКА! Виберіть 1, 2 або 3.\n";
            flag = false;
        }

    }

    cout << "Адреса доставки: ";
    cin.getline(address, 50);

    // оплата
    while (true)
    {
        cout << "Спосіб оплати (1 - карта || 2 - оплата при отриманні): ";

        if (!safeInt(answer))
        {
            cout << "ПОМИЛКА! Введіть 1 або 2.\n";
            continue;
        }

        if (answer == 1)
        {
            strcpy_s(payment, "карта");

            // номер картки
            while (true)
            {
                cout << "Введіть номер картки (16 цифр): ";
                cin.getline(card, 50);

                if (strlen(card) == 16 && isDigits(card))
                    break;

                cout << "Невірний формат! Потрібно рівно 16 цифр.\n";
            }

            // термін дії MM/YY
            while (true)
            {
                cout << "Введіть термін дії (MM/YY): ";
                cin.getline(exp, 10);

                if (strlen(exp) == 5 && exp[2] == '/' &&
                    isdigit(exp[0]) && isdigit(exp[1]) &&
                    isdigit(exp[3]) && isdigit(exp[4]))
                {
                    int mm = (exp[0] - '0') * 10 + (exp[1] - '0');
                    if (mm >= 1 && mm <= 12)
                        break;
                }
                cout << "Формат невірний! Має бути MM/YY.\n";
            }

            // CVV
            while (true)
            {
                cout << "Введіть CVV (3 цифри): ";
                cin.getline(cvv, 10);

                if (strlen(cvv) == 3 && isDigits(cvv)) break;

                cout << "CVV повинен містити 3 цифри!\n";
            }

            break; // вихід з оплати
        }
        else if (answer == 2)
        {
            strcpy_s(payment, "оплата при отриманні");
            break;
        }

        cout << "ПОМИЛКА! Виберіть 1 або 2.\n";
    }

    check(fullname, phone, email, delivery, address, payment, card, exp, cvv);
}

void menuKosh()
{
    int answer;
    do
    {
        printKosh();
        cout << "=================" << endl;
        cout << "\nОберіть дію:" << endl;
        cout << "[1] - Видалити товар" << endl;
        cout << "[2] - Сума замовлення" << endl;
        cout << "[3] - Очистити весь кошик" << endl;
        cout << "[4] - Продовжити покупки (назад до каталогу)" << endl;
        cout << "[5] - Оформити замовлення" << endl;
        cout << "Ваш вибір: ";
        cin >> answer;
        if (answer == 1)
        {
            del();
        }
        else if (answer == 2)
        {
            sum();
        }
        else if (answer == 3)
        {
            indbase = 0;
            cout << "Кошик очищено!" << endl;
        }
        else if (answer == 5)
        {
            if (indbase != 0)
            {
                order();
            }
        }
    } while (answer != 4);
}

bool transformToLowerCase(const char* text, const char* pattern)
{
    char a[50], b[50];
    strcpy_s(a, text);
    strcpy_s(b, pattern);

    for (int i = 0; a[i]; i++) a[i] = tolower(a[i]);
    for (int i = 0; b[i]; i++) b[i] = tolower(b[i]);

    return strstr(a, b) != nullptr;
}

void searchByName()
{
    int answer;
    showProducts();

    while (true)
    {
        cout << "Введіть назву для пошуку: " << endl;
        cin >> query;
        cout << "Результати пошуку:" << endl;
        int foundIndexes[10];
        int foundCount = 0;
        flagsearch = false;
        for (int i = 0; i < 5; i++)
        {
            if (transformToLowerCase(names[i], query))
            {
                cout << foundCount + 1 << ") " << names[i] << " — " << prices[i] << " грн\n";

                foundIndexes[foundCount] = i;
                foundCount++;
                flagsearch = true;
            }
        }

        if (!flagsearch)
        {
            cout << "Такого товару не має" << endl;
        }
        else
        {
            cout << "Оберіть номер товару для додавання (0 — пропустити): " << endl;
            cin >> answer;

            if (answer > 0 && answer <= foundCount)
            {
                int idx = foundIndexes[answer - 1];

					strcpy_s(mass[indbase].tovar, names[i]);
					mass[indbase].price = prices[indforsearch];
                    indbase++;
               
                cout << "Товар додано!" << endl;
            }
        }

        cout << "2 - Меню кошика || 0 - Новий пошук: " << endl;
        cin >> answer;

        if (answer == 2)
        {
            menuKosh();
        }
    }
}
int main()
{
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    searchByName();
}
