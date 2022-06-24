/*
* Создайте систему управления персональными финансами.
Система должна иметь следующие возможности:
■
Наличие разных кошельков и карт (дебетовых/кредитных);
■
Пополнение кошельков и карт;
■
Внесение затрат. Каждая затрата относится к определенной категории;
■
Формирование отчетов по затратам и категориям:
• день;
• неделя;
• месяц.
■
Формирование рейтингов по максимальным суммам:
• ТОП-3 затрат:
ӽ неделя;
ӽ месяц.
• ТОП-3 категорий:
ӽ неделя;
ӽ месяц.
■
Сохранение отчетов и рейтингов в файл.
*/
#include <iostream>
#include "Date.h"
#include "Wallets.h"
#include "Cards.h"
using namespace std;

enum class Command
{
    wallets = 1, cards
};

std::map<int, std::string> commands =
{
    {(int)Command::wallets, "Счета..."},
    {(int)Command::cards, "Карты..."},
};

const string walletsFile{ "wallets.txt" };
const string cardsFile{ "cards.txt" };

Date today;
Menu* menu;
Items* wallets;
Items* cards;

class MainMenu : public Menu
{
public:
    MainMenu(map<int, string> commands) : Menu(commands)
    {}
private:
    void execCommand(int command) override;
};

void MainMenu::execCommand(int command)
{
    switch ((Command)command)
    {
    case Command::wallets:
        wallets->displayAll();
        wallets->run();
        break;
    case Command::cards:
        cards->displayAll();
        cards->run();
        break;
    default:
        break;
    }
}

int main()
{
    setlocale(LC_ALL, "rus");
    cout << "Управление финансами" << endl << endl;

    //cout << "Enter current date: ";
    //cin >> today;
    today = Date::getCurrentDate();
    cout << "Сегодня " << today << endl << endl;

    wallets = new Wallets();
    wallets->open(walletsFile);

    cards = new Cards();
    cards->open(cardsFile);

    menu = new MainMenu(commands);
    menu->run();

    wallets->save(walletsFile);
    delete wallets;

    cards->save(cardsFile);
    delete cards;

    delete menu;

    return 0;
}