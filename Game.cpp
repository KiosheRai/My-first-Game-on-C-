//Game of Year 2,AAA project
#include<iostream>
#include<cmath>
#include<conio.h>
#include<iomanip>
#include<Windows.h>
#include<random>
#include<ctime>
#include<string>
#include<ctype.h>
using namespace std;
void text(string s);
void play(float difficult);
int enemy_phase(int hero_hp, int max_monster_damage, int min_monster_damage, int monster_hp, int protection);
void death(int hero_hp);
int boss_phase(int hero_hp, int max_monster_damage, int min_monster_damage, int boss, int *phase, int *time_spell, int protection, int drop_money, int money, int *monster_hp);
void safe_zone(int *money,int *potion_heal,int *potion_df,int safe_zone);
void history();
struct bosses {
	int hp;
	int damgae;
	int ulta;
};
void text(string s) {
	for (int i = 0; i < s.length(); i++) {//Вывод текста.
		char a[200];
		if (_kbhit()) {
			cout << s[i];
		}
		else {
			cout << s[i];
			Sleep(20);
		}
	}
}
void texd(string s) {
	for (int i = 0; i < s.length(); i++) {//Вывод текста.
		char a[200];
		if (_kbhit()) {
			cout << s[i];
		}
		else {
			cout << s[i];
			Sleep(20);
		}
	}
}
void text(string s, int speed) {
	for (int i = 0; i < s.length(); i++) {//Вывод текста.
		char a[200];
		if (_kbhit()) {
			cout << s[i];
		}
		else {
			cout << s[i];
			Sleep(speed);
		}
	}
}
int boss_phase(int hero_hp, int max_monster_damage, int min_monster_damage, int boss,int *phase,int *time_spell,int protection,int drop_money,int money,int *monster_hp) {//Ход босса
	int hp = hero_hp,damage, heal,monster_heal, wheel_luck,ulta_b=rand()%3;
	system("cls");
	
	if (ulta_b % 3 == 0) {
		switch (boss)
		{
		case 0://Опездал
			text("Опездал бъёт вас по лицу и оглушает.\n");
			damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage - 20 - protection;
			text("Вам нанесли[");
			hp = hero_hp - damage;
			cout << damage;
			text("]урона. И оглушили на 1 ход\n");
			if (*time_spell > 0) {
				*time_spell -= 1;
			}
			damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage - 20 - protection;
			text("Вам нанесли[");
			hp = hero_hp - damage;
			cout << damage;
			text("]урона.\n");
			break;
		case 1://Вил
			text("Вил крутит колесо фартуны... "); wheel_luck = rand() % 5;
			switch (wheel_luck)
			{
			case 0:text("Вил получает чистый урон...");
				damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage + 10;
				text("Вам нанесли[");
				hp = hero_hp - damage;
				cout << damage;
				text("]урона.\n"); _getch();
				break;
			case 1:	
				heal = rand()%20+20;
				text("Вил лечит вас на "); cout << heal;
				text(" хп...");
					hp =hero_hp + heal;
				break;
			case 2:
				damage = rand() % 20 + 20;
				text("Вил получает урон...");
				*monster_hp -= damage;
				break;
			case 3:text("Вил увеличивает ваш урон...");
				*time_spell += 1;
				break;
			case 4:text("Вил наносит вам критический урон...\n");
				damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage + 30;
				text("Вам нанесли[");
				hp = hero_hp - damage;
				cout << damage;
				text("]урона.\n"); _getch();
				break;
			}

			break;
		case 2://Дио
			text("Дио использует завардо и останавливает время.\n");
			for (int i = 0; i < 2; i++) {
				damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage - 20 - protection;
				text("Вам нанесли[");
				hp = hero_hp - damage;
				cout << damage;
				text("]урона.\n"); _getch();
			}
			break;
		case 3://Смоуг
			text("Смоуг использует лечение.\nСмоуг восстановил "); monster_heal = rand() %30+30;
			cout << monster_heal; text(" здоровья.");
			*monster_hp += monster_heal;
			_getch();
			break;
		case 4://Анкап
			if (drop_money >= 20) {
				text("Анкап бросился к монетам с целью собрать их. Анкап пропускает ход.");
				break; _getch();
			}
			else {
				damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage - 10 - protection;
				text("Анкап облагает вас налогом, его урон увеличен на кол-во ваших монет ");
				cout << money;
				text("Вам нанесли[");
				hp = hero_hp - damage - money;
				cout << damage;
				text("]урона.\n"); _getch();
				break;
			}
		}return hp;
	}
	else {
		damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage+10- protection;
		hp = hero_hp - damage;
		/*text("Вам нанесли[");
		cout << damage;
		text("]урона.\n"); _getch();*/
	}
	*phase+=1;

	return hp;
}
int enemy_phase(int hero_hp, int max_monster_damage, int min_monster_damage,int monster_hp,int protection) {//ход врага.
	int damage, hp;
	if (monster_hp > 0) {
		system("cls");
		damage = rand() % (max_monster_damage - min_monster_damage) + min_monster_damage - protection;
		text("Вам нанесли[");
		cout << damage;
		text("]урона.\n");
		hp = hero_hp - damage;
		return hp;
	}
	return hero_hp;
}
void safe_zone(int *money, int *potion_heal, int *potion_def,int safe_zone) {//Безопасные зоны.
	string campfire[10] = {"Лес мёртвых.","Поселение нежети.","Сад тёмных корней.","Поселение Морио.","Разрушенная церковь",
		"Подземелье Иритилла","Цитадель","Берега Междумория","Великая Вейшнорская стена","Палатка посреди поля"},
		person[10] = {"Колос","Крыс Мышовур","Милая Шалкуар","Йошикаге Кира","Джон Коффи","Данковский","Павший король","Сташинский","Смотритель","Дед Потап"};
	
	text("Вы достигли безопасной зоны. Ваше здоровье и мана были полностью восстановлены.\n");
	Sleep(2000);
	bool safe = true,shop = true;
	int choose, mon= *money,vodka = 1;
	while (safe) {
		system("cls");
		text("Локация : ");
		text(campfire[safe_zone]);//Интерфейс
		cout << endl;
		text("Монеты["); cout << mon; text("].\n");
		text("--Подойти к торговцу--1\n");
		text("---Продолжить путь----2\n");
		text("->");
		cin >> choose;
		system("cls");
		switch (choose)
		{
		case 1:
			text("Вы подходите к торговцу.\n");
			Sleep(1000);
			while (shop) {
				system("cls");
				int buy;
				text("Локация : ");
				text(campfire[safe_zone]);
				cout << endl;
				text("Торговец : ");
				text(person[safe_zone]);
				cout << endl;
				cout << endl;
				text("\nМонеты["); cout << *money; text("].\n");
				cout << endl;
				text("-----Купить Фласку(10)----1\n");
				text("--Купить зелье защиты(7)--2\n");
				text("--------Поговорить--------3\n");
				text("-----Продолжить путь------4\n");
				text("->");
				cin >> buy;
				switch (buy)
				{
				case 1:
					if (10 <= mon) {
						text("Вы купили фласку.");
						*money -= 10;
						*potion_heal += 1;
						Sleep(2000);
					}
					else { text("У вас нет денег - вы очень бедны."); Sleep(2000);}
					break;
				case 2:
					if (7 <= mon) {
						text("Вы купили зелье защиты.");
						*money -= 7;
						*potion_def += 1;
						Sleep(2000);
					}
					else { text("У вас нет денег - вы очень бедны."); Sleep(2000); }
					break;
				case 3:
					system("cls");
					switch (safe_zone)
					{
					case 0:
						texd("Колос вам не отвечает, он лишь качается на ветру.\n");
						texd("А чего вы вообще ожидали от колоса?\n");
						texd("Но вы явно запомните его золотистый цвет на долго.\n");
						_getch();
						break;
					case 1:
						texd("Добро пожаловать в мою скромную деревушку... Так ты здесь впервые?\n");
						texd("Может сейчас она и похожа на свалку, но до вторжения это было весьма людное место.\n");
						texd("Когда-то сюда приезжали торговцы со всей округи, деревня росла как на дрожжах.\n");
						texd("Жаль что эти времена кончились, надеюсь что когда-нибудь всё станет как прежде.");
						_getch();
						break;
					case 2:
						texd("Перед вами сидит кошка чёрно-серого цвета.\n");
						texd("На ней ошейник по которому вы узнали её имя \"Шалкуар\".\n");
						texd("На первый взгляд обычная кошка...Но они все вымерли во время пришествия\n");
						texd("Увы она не может говорить и никогда не расскажет как ей удалось выжить.\n");
						Sleep(1000);
						texd("Вы погладили кошку с мыслью о том что она последняя в своём роде.\'n");
						_getch();
						break;
					case 3:
						text("Меня зовут Кира Йошикаге. Мне 33 года. Мой дом находится в\nсеверо-восточной части Морио, где расположены все виллы.\nЯ не женат.Я работаю в универмаге Kame Yu и прихожу домой\nне позднее 8 вечера.Я не курю, но иногда выпиваю. \nЯ ложусь спать в 11 вечера, и убеждаюсь, что я получаю\nровно восемь часов сна, несмотря ни на что.\nВыпив стакан теплого молока и потянувшись минут двадцать\nперед сном, я обычно без проблем сплю до утра.Словно ребёнок, \nя просыпаюсь утром без всякой усталости и стресса.\nНа моём последнем осмотре мне сказали, что у меня нет никаких\nпроблем со здоровьем.Я пытаюсь донести, что я обычный человек, \nкоторый хочет жить спокойной жизнью.Я забочусь о том, \nчтобы не утруждать себя какими - либо врагами – победами и\n поражениями, которые могли бы потревожить мой сон.Вот как я\n отношусь к обществу, и я знаю, что это приносит мне счастье.\nХотя, если бы мне пришлось сражаться, я бы никому не проиграл.\n");
						_getch();
						break;
					case 4:
						texd("Вы заходите в самую тёмную комнату.\n");
						texd("\"Помогите, не включайте свет!!\"");
						texd("-Перед вами сидит слепой старик.\n");
						texd("\"Я жил в этой церкви, родители бросили меня ещё при рождении\".\n");
						texd("- сказал старик подняв голову и будто видя вас.");
						texd("\"Но эта церковь была не так проста. Над нами ставили эксперименты уже с 3 лет.\nОн считал что лекарство от мора стоит наших мучений.\",\n");
						texd(", -старик закрыл голову руками и затих, -\"Он сделал меня слепым\".");
						_getch();
						break;
					case 5:
						texd("Не часто встретишь тут гостей, что же вас сюда привело?\n");
						texd("Аккуратно, не ходите возле пробирок, там находится очень важные лекарства!\n");
						texd("Вам интересно какое? Это моя разработка, дело всей жизни.\n");
						texd("Лекарство от мора...Знали бы вы с каким трудом я его получил...\n");
						texd("Но вне всяких сомнейний оно того стоило.");
						texd("Надеюсь моя разработка сможет спасти много людей.\n");
						_getch();
						break;
					case 6:
						text("Чего тебе? Иди других обворовывай.\n",30);
						text("Оставь меня в покое! Ты знаешь кто я!\n",30);
						text("Так вот я тебе объясню: я был тем кто даровал тебе право на жизнь.\n");
						text("Если бы не я - ты бы гнил в земле, а не смаковал там наверху.\n");
						text("Почему пока я тут пытаюсь выжить, вы на всю отрываетесь?");
						text("Меня использовали и бросили, но знай чем быстрее я умру,\nтем быстрее рухнет и остров.");
						text("--Видимо вам пора.--");
						_getch();
						break;
					case 7:
						text("Что? Тебе интересно как я здесь оказался?\nХах, хорошо. Я жил хорошо, использовал свинную кишку как гондон,\n",50);
						text("но однажды она порвалась и я заразился сифилисом.\n",50);
						text("Теперь я доживаю здесь свой век.",50);
						_getch();;
						break;
					case 8:
						texd("О, куда путь держишь странник?\n");
						texd("Впечатляет правда? Я смотрю зна этими стенами уже 20 лет.\n");
						texd("Почему я не эвакуировался на острова?\n");
						texd("Смотреть за стенами - это не просто работа, это и моё хобби.\n");
						texd("Какой прок там будет от меня, а здесь всё ясно.\n");
						texd("Сидишь в тишине, иногда от монстров отбиваешься, раз в месяц полный обход стен.\n");
						texd("Мне другого не надо. Не просто так меня смотрителем прозвали.\n");
						_getch();
						break;
					case 9:
						text("Кем будешь? Назовись!\n");
						text("Да не пугайся ты, шучу ведь.\n");
						text("Не часто прохожего встретишь. Заходи, выпьем чего-нибудь!\n");
						text("Не хочешь что ли? Да не ври, я же вижу что хочешь.\n");
						text("Стесняешься что ли со мной пить? Ну и не надо.\n");
						text("Возьми одну с собой, пригодиться.\n");
						if (vodka == 1) {
							text("Вы получили одно зелье защиты.");
							*potion_def += 1;
						}
						_getch();
						break;
					}
					break;
				case 4:
					shop = false;
					safe = false;
					break;
				default:
					cout << "Число должно быть от 1 до 4.";
					Sleep(2000);
					break;
				}
			}
		case 2:
			break;
		default:
			cout << "Число должно быть от 1 до 2.";
			Sleep(2000);
			break;
		}
		system("cls");
		text("Вы собираетесь и полный сил уходите в путь.\n");
		Sleep(2000);
		safe = false;
	}
	return;

}
void death(int hero_hp) {
	if (hero_hp > 0) {
		return;
	}
	else {
		system("cls");
		for (int i = 1; i < 100; i++) {
			int time = 1500;
			cout << "|Вы погибли. Игра окончена.----|\n"; 
			Sleep(time); system("cls");
			cout << "|-Вы погибли. Игра окончена.---|\n"; 
			Sleep(time); system("cls");
			cout << "|--Вы погибли. Игра окончена.--|\n";
			Sleep(time); system("cls");
			cout << "|---Вы погибли. Игра окончена.-|\n"; 
			Sleep(time); system("cls");
			cout << "|----Вы погибли. Игра окончена.|\n"; 
			Sleep(time); system("cls");
			cout << "|---Вы погибли. Игра окончена.-|\n"; 
			Sleep(time); system("cls");
			cout << "|--Вы погибли. Игра окончена.--|\n";
			Sleep(time); system("cls");
			cout << "|-Вы погибли. Игра окончена.---|\n"; 
			Sleep(time); system("cls");
		}exit(0);
	}
}
void history() {
	int t = 50;
	text("Добро пожаловать в этот хрупкий,\nпостепенно разрушающийся мир без надежды на будущее.\n", t);
	Sleep(1500);
	text("...\n", 100);
	Sleep(1000);
	system("cls");
	text("Ты был призван с целью защиты нас от вторженцев.\n", t);
	Sleep(1000);
	text("Когда-то давным-давно произошло, как мы называем, пришествие.\n", t);
	text("На землю прилетели неизвестные корабли, которые уничтожили\nпочти всё живое на поверхности земли.\n", t);
	text("Лишь немногие смогли выжить, им пришлось адаптироваться в новом мире.\n", t);
	text("Великие короли подняли куски земли в небо - парящие острова.\n", t);
	text("Они стали нам новым домом.\n", t);
	text("Однако нашлись и отчаянные, что остались на земле несмотря ни на что.\n", t);
	Sleep(1500);
	system("cls");
	text("Так вот...\n", 70);
	text("Эти острова были лишь временные решением, скоро они упадут обратно на землю.\n", t);
	text("И ты должен спуститься на поверхность и одолеть вторженцев.\n", t);
	text("Ты должен вернуть нам наш дом...\n", t);
	Sleep(2000); system("cls");
}
void play(float difficult) {//Геймплей.---------
	int hero_damage, monster_damage,
		time_spell = 0, attack_monster,
		monster_hp, level = 1, max_hero_hp, max_hero_damage,
		min_hero_damage, hero_hp, max_hero_mana,
		hero_mana, max_monster_hp, min_monster_hp,
		max_monster_damage, min_monster_damage, boss, location, potion_heal = 2, money = rand() % 7 , potion_def = 2,protection,
		time_protect = 0,drop_money = 0;
	int boss_r[5] = { 0,1,2,3,4 }, location_r[5] = { 0,1,2,3,4 }, safe_zone_r[10] = {0,1,2,3,4,5,6,7,8,9};
	if (difficult == 1) {//Лёгкая
		max_hero_hp = 130,//Настройки.
			max_hero_damage = 70,
			min_hero_damage = 45,
			hero_hp = 130,
			max_hero_mana = 75,
			hero_mana = 75,
			max_monster_hp = 90,
			min_monster_hp = 50,
			max_monster_damage = 50,
			min_monster_damage = 20;
	}
	else if (difficult == 2) {
		max_hero_hp = 100,//Средняя.
			max_hero_damage = 60,
			min_hero_damage = 40,
			hero_hp = 100,
			max_hero_mana = 50,
			hero_mana = 50,
			max_monster_hp = 120,
			min_monster_hp = 80,
			max_monster_damage = 50,
			min_monster_damage = 40;
	}
	else if (difficult == 3) {
		max_hero_hp = 90,//Сложная.
			max_hero_damage = 60,
			min_hero_damage = 30,
			hero_hp = 90,
			max_hero_mana = 50,
			hero_mana = 50,
			max_monster_hp = 150,
			min_monster_hp = 90,
			max_monster_damage = 60,
			min_monster_damage = 40;
	}
	else if (difficult == 0) {
		max_hero_hp = 200,//Отладочная.
			max_hero_damage = 70,
			min_hero_damage = 69,
			hero_hp = 200,
			max_hero_mana = 50,
			hero_mana = 50,
			max_monster_hp = 75,
			min_monster_hp = 30,
			max_monster_damage = 2,
			min_monster_damage = 0;
	}
	int choose;//Управление.
	int phase;
	string set_monster[15] = { "Гуль","Упырь","Рыдцорб бездны","Демон Капра","Сирена Лилит","Чемош","Чувырла","Кимерис",
	"Мелек Таус","Мидгард","О-Яма" ,"Шива" ,"Тянь-мо" ,"Тецкатлипока" ,"Йен-ло-Ванг" },
		set_bosses[5] = { "Опездал","Вил","Дио","Смоуг","Анкап" },
		messages[6] = { "У вас провалился нос, перед вами встал : \n\t","Вы обернулись и перед вами встал : \n\t","Внезнапно с неба упал : \n\t",
		"Вы наступили на ветку и она превратилась в : \n\t","Вы подобрали пустой лист, вы переворачиваете его и из него вылазит : \n\t","Вы присели чтобы сделать карточный домик, но на него наступил : \n\t" },
		boss_messages[5] = { "Вы спустились в подземелье, но дверь за вами заперлась, перед вами встал босс : \n\t","Вы поднялись на верхушку башни перед вами встал : \n\t","Вы спустились в канализацию, вас ожидает : \n\t",
		"Вы идёте по мосту, но вдруг он проваливается под вами, вы оказываетесь на голове чудовища : \n\t","Вода в море раздвинулось пред вами, виновником этого стал : \n\t" };
	while (hero_hp > 0) {//-------------
		string enemy;
		system("cls");
		
		if (level == 10) {
			texd("Вы смогли освободить землю от вторженцев тем самым вернув дом людям.\n");
			texd("Города отстроили заново, человечество пришлок к новому витку развития.\n");
			texd("А вы стали великим героем человечества, вам была выделена высокая должность.\n");
			texd("В честь вас были возведены памятники, в честь вас стали называть улицы и города.\n");
			texd("В честь вас переименновали Кисловодск, который стал столицей мира.\n");
			Sleep(6000);
			system("cls");
			text("В течении 2 недель ничего не происходило, а потом",60);
			while (true) {
				text("...", 70);
			}
		}
		if (level % 3 == 0) {
			int i = rand() % 10;
			while (safe_zone_r[i] == 10) {
				i = rand() % 10;
			}
			hero_hp = max_hero_hp;
			hero_mana = max_hero_mana;
			safe_zone(&money, &potion_heal, &potion_def, i);
			safe_zone_r[i] = 10;
		}
		int boss = rand() % 5, location = rand() % 5;
		if (level %3==0) {//bosses
			while (boss_r[boss] == 5) {
				boss = rand() % 5;
			}
			while (location_r[location] == 5) {
				location = rand() % 5;
			}
			enemy = set_bosses[boss];
			text(boss_messages[location]);
			cout << enemy;
			monster_hp = rand() % (max_monster_hp - min_monster_hp) + min_monster_hp*3;
			boss_r[boss] = 5;
			location_r[location] = 5;
			phase = 1;
		}
		else {
			int monster = rand() % 15,mess = rand()%6;
			text(messages[mess]);//Интерфейс.
			enemy = set_monster[monster];
			cout << enemy;
			monster_hp = rand() % (max_monster_hp - min_monster_hp) + min_monster_hp;
		}
		while (monster_hp > 0) {
			if (hero_hp > 0) {
					text("\nВаше здоровье["); cout << hero_hp; text("] Ваша мана["); cout << hero_mana; text("]\n");//Интерфейс.
				if (time_spell > 1) {
						text("Ваш урон увеличен на 20 на "); cout << time_spell; text(" хода.");
						time_spell -= 1;
					}
				else if (time_spell == 1) {
						text("Ваш урон увеличен на 20 на "); cout << time_spell; text(" ход."); time_spell -= 1;
				}
				if (time_protect > 1) {
					text("Ваша защита увеличен на 35 на "); cout << time_protect; text(" хода.");
					time_protect -= 1;
					protection = 25;
				}
				else if(time_protect == 1){
					text("Ваша защита увеличен на 35 на "); cout << time_protect; text(" ход.");
					time_protect -= 1; protection = 25;
				}
				else { protection = 0; }
				text("\nЗдоровье врага["); cout << monster_hp; text("]\n");
				cout << endl;
				text("--Атаковать--1\n");
				text("--Инвентарь--2\n");
				text("----Магия----3\n");
				text("---Сдаться---4\n");
				cout << ("->");
				cin >> choose;
				switch (choose)
					{
				case 1://Атаки.
					if (time_spell > 0) {
						hero_damage = rand() % (max_hero_damage - min_hero_damage) + min_hero_damage + 20;
						}
					else {
						hero_damage = rand() % (max_hero_damage - min_hero_damage) + min_hero_damage;
					}
					text("Вы нанесли ");
					cout << hero_damage;
					text(" Урона.\n"); system("pause");
					monster_hp -= hero_damage;
					if (level %3 == 3) {
						hero_hp = boss_phase(hero_hp, max_monster_damage, min_monster_damage, boss, &phase, &time_spell,protection, drop_money,money, &monster_hp);
					}
					else {
						hero_hp = enemy_phase(hero_hp, max_monster_damage, min_monster_damage, monster_hp, protection);
					}
					break;
				case 2://Инвентарь.
					int inv_choose;
					system("cls");
					text("Кол-во монет        : "); cout << money <<endl;
					text("Кол-во фласок       : "); cout << potion_heal << endl;
					text("Кол-во зелей защиты : "); cout << potion_def << endl;
					cout << endl;
					text("-------Фласка------1\n");
					text("----Зелье защиты---2\n");
					text("-Выкинуть 10 монет-3\n");
					text("-------Назад-------4\n");
					cout << "->";
					cin >> inv_choose;
					switch (inv_choose)
					{
					case 1:
						if (potion_heal >= 1) {
							system("cls");
							text("Вы использовали фласку.\n");
							hero_hp += 100;
							if (hero_hp > max_hero_hp) {
								hero_hp = max_hero_hp;
							}
							potion_heal -= 1;
							Sleep(2000);
						}
						else { text("У вас нету фласок."); _getch(); }
						break;
					case 2:
						if (potion_def >= 1) {
							system("cls");
							text("Вы использовали зелье защиты.\n");
							protection += 35;
							time_protect = 2;
							potion_def -= 1; Sleep(2000);
						}
						else { text("У вас нету фласок."); _getch(); }
						break;
					case 3:
						if (money > 10) {
							system("cls");
							text("Вы выкинули 10 монет. Зачем?");
							money -= 10;
							drop_money += 10; Sleep(2000);
						}else { text("У вас нет денег - вы очень бедны."); _getch(); }
						break;
					default:
						break;
					}
					if (inv_choose>3) {
						system("cls");
						break;
					}
					else if (level % 3 ==0) {
						hero_hp = boss_phase(hero_hp, max_monster_damage, min_monster_damage, boss,&phase, &time_spell, protection, drop_money, money, &monster_hp);
						break;
					}
					else {
						hero_hp = enemy_phase(hero_hp, max_monster_damage, min_monster_damage, monster_hp, protection);
						break;
					}
				
				case 3://Магия.
					if (hero_mana > 0) {
						int magic;
						system("cls");
						cout << "Ваше здоровье[" << hero_hp << "] Ваша мана[" << hero_mana << "]\n\n";
						text("-Атакующая магия--(20маны)-1\n");
						text("--Магия лечения---(25маны)-2\n");
						text("-Увеличение урона-(10маны)-3\n");
						text("------Суицид------(50маны)-4\n");
						text("\n<-Для выхода нажмите 5.->\n");
							cout << "->";
						cin >> magic;
						switch (magic) {
						case 1:
							if (hero_mana >= 20) {
								system("cls");
								text("Вы использовали атакующую магию.\n");
								monster_hp -= 65;
								hero_mana -= 20;
							}
							else {
								text("У вас мало маны."); Sleep(2000);
							}
							break;
						case 2:
							if (hero_mana >= 25) {
								system("cls");
								text("Вы использовали магию лечения.\n");
								hero_hp += 65;
								if (hero_hp > max_hero_hp) {
									hero_hp = max_hero_hp;
								}
								hero_mana -= 25;
							}
							else { text("У вас мало маны."); Sleep(2000); }
							break;
						case 3:
							if (hero_mana >= 10) {
								system("cls");
									text("Ваш урон увеличен на 3 хода.\n");
								time_spell = 3;
								hero_mana -= 10;
							}
							else { text("У вас мало маны."); Sleep(2000); }
							
							break;
							
						case 4:
							if (hero_mana >= 50) {
								system("cls");
								
								text("Вы использовали магию суицида.\nВы погиби, но нанесли 150 урона врагу.\n");
								
								if (monster_hp <150 && level >= 6) {
									texd("Вы смогли освободить землю от вторженцев тем самым вернув дом людям.\n");
									texd("Города отстроили заново, человечество пришлок к новому витку развития.\n");
									texd("Аристократы присвоили все ваши достижения себе.\n");
									texd("В честь них были возведены памятники, в честь них стали называть улицы и города.\n");
									texd("В честь них переименновали Кисловодск, который стал столицей мира.\n");
									Sleep(3000);
									system("cls");
									text("В течении 2 недель ничего не происходило, а потом что-то произошло,\n но вы этого уже никогда не узнаете.", 60);
									Sleep(3000);
								}
								monster_hp -= 150;
								hero_hp = 0;
								_getch();
								death(hero_hp);
							}text("У вас мало маны.");
							break;
						default:
							system("cls");
							break;
						}if (magic != 1&& magic !=2&& magic !=3&& magic !=4) {
							break;
						}
						else if (level % 3 ==0) {
							hero_hp = boss_phase(hero_hp, max_monster_damage, min_monster_damage, boss, &phase, &time_spell, protection, drop_money, money,&monster_hp);
							break;
						}
						else {
							hero_hp = enemy_phase(hero_hp, max_monster_damage, min_monster_damage, monster_hp, protection);
							break;
						}break;
					}
					else {
						text("У вас мало маны.");
						break;
					}
					break;
					case 4://Сдаться. 
						int i;
						text("Вы уверены?\n1-да\n0-нет\n");
						cout << "->";
						cin >> i;
						if (i == 1) {
							hero_hp = 0;
						}
						else { break; }
				}
			}
				death(hero_hp);

		}	int plus_money;
			system("cls");
			text("\nВы победили.");
			cout << enemy << endl;
			level += 1;
			plus_money = rand() % 6+7;
			money += plus_money;
			text("Вы получаете[");
			cout << plus_money; text("] монет.");
			drop_money = 0;
			_getch();
}
	death(hero_hp);
	_getch();
	exit(0);
}//------



int main() {
	int difficulty = 2;
	bool first = true, second = true;
	srand(time(0));//Откат времени на 0, для придания рандома рандомайзеру.
	setlocale(0, "");
	string error[7] = { "1488x229","You have micropenis.","Ваш компьютер не соответствует минимальным требованиям.","Обновите драйвера и презапустите игру.",
	"syntax error","File 1939/polsha not found","please reload the game" };
	cout << "<GAME OF YEAR 2,AAA PROJECT>\n";
	for (int i = 0; i <= 100; i += 10) {//Загрузка
		if(6==rand()%17){cout<<"Error "<<error[rand()%7];
		_getch();
		exit(0);}
		cout << "---------Loading---------" << i << "%"<<endl;
		Sleep(rand()%1000);
	}
	system("cls");
	history();
	system("cls");
	while (second) {
		int ch;
		text("---Начать игру---1\n-Выбрать уровень-2\n-----Авторы------3\n------Выход------4\n");
		cout << "->";
		cin >> ch;
		switch (ch)//Выбор сложности.
		{
		case 1:
			system("cls");
			play(difficulty);
			break;
		case 2:
			system("cls");
			int d;
			text("Выберите уровень сложности:\nЛёгкая--1\nСредняя-2\nСложная-3");
			cout << "\n->";
			cin >> d;
			if (d == 1) {
				difficulty = 1;
				system("color 0a"); system("cls");
			}
			else if (d == 2) {
				difficulty = 2;
				system("color 0f"); system("cls");
			}
			else if (d == 3)
			{
				difficulty = 3;
				system("color 0c"); system("cls");
			}
			else if (d == 0)
			{
				text("Вы зашли в режим отладки, теперь враги не наносят урона.\nНажмите кнопку для продолжения.");
				difficulty = 0;
				system("color 0e"); _getch(); system("cls");
			}
			break;
		case 3://Авторы.
			system("cls");
			text("Глава кампании Dangeon Master.\n\nнажмите на любую кнопку.");
			_getch();
			system("cls");
			break;
		case 4://Выхода нет.
			int q;
			system("cls");
			text("ВЫ УВЕРЕНЫ?\n1-да\n0-нет\n");
			cout << "\n->";
			cin >> q;
			if (q == 1) {
				return 0;
			}
			else {
				system("cls");
				break;
			}
		default:text("Введите число от 1 до 4.\n");
			break;
		}
	}
	system("pause");
	return 1;
}
