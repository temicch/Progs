#include "mySimpleComputer.h"
#include "myTerm.h"
#include "myBigChars.h"
#include "myReadkey.h"

#include <signal.h>

extern int bigChars[17][2];

int selectedCell = 0;

enum colors textColor =			WHITE,
			textEditSelected =	WHITE,
			textCounter	=		GREEN;

extern void sc_regInit();
// Обновить содержимое ячейки памяти
void updateMemory(int i)
{
	// Выставить фон текста как консольный
	mt_setbgcolor(CONSOLE);
	// Выставить цвет текста как textColor (белый)
	mt_setfgcolor(textColor);
	
	// Перейти на то место, где должно располагаться содержимое ячейки.
	mt_gotoXY(2 + 6 * (i % 10), 2 + (i / 10));
	int value, command, operand;
	// Получить содержимое ячейки по адресу (i), занести информацию в переменную (value)
	sc_memoryGet(i, &value);
	// Декодировать команду
	sc_commandDecode(value, &command, &operand);
	// Если нужная ячейка совпадает с той, на которой стоит курсор пользователя, выделить эту ячейку фоном цвета textEditSelected (белый)
	if (i == selectedCell)
	{
		mt_setbgcolor(textEditSelected);
		mt_setfgcolor(BLACK);
	}
	// Если обновляемая ячейка является ячейкой, которая выполняется, выделить ее фоном textCounter (зеленый)
	if (i == instructionCounter)
		mt_setbgcolor(textCounter);
	// Формируем строку, которая отображает содержимое ячейки (при этом если 15 бит равен единице, то ставим перед содержимым - минус, иначе - плюс)
	sprintf(temp, "%s%02X%02X", (value < 0) ? "-" : "+", command, operand);
	// Выводим строку 
	write(1, temp, strlen(temp));
	// Возвращаем фон текста и цвет в изначальное состояние
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
}
// Обновить значение аккумулятора
int updateEAX(int value)
{
	// Если новое число аккумулятора имеет больше 15 разрядов (0x7FFF(16) Это самое максимальное 15 битное число)
	if(abs(value) > 0x7fff)
	{
		// То устанавливаем флаг "Переполнение при выполнении операции" в активное состояние
		sc_regSet(REG_OVERFLOW, 1);
		// Функция завершена с ошибкой
		return -1;
	}
	// Присваиваем аккумулятору новое значение
	EAX = value;
	// Назначаем фон текста и цвет текста как консольный и textColor соответственно
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Переходим в координату, где отображается содержимое аккумулятора в консоли
	mt_gotoXY(62 + 3 + 2, 1 + 1);
	// Формируем содержимое ячейки. Если 15 разряд аккумулятор содержит единицу, значит в аккумуляторе отрицательное число, поэтому
	// перед числом ставим минус (иначе плюс).
	sprintf(temp, "%s%04X", (value < 0) ? "-" : "+", abs(EAX) );
	// Выводим содержимое аккумулятора
	write(1, temp, strlen(temp));
	return 0;
}
// Обновить указатель текущей выбранной/выполняемой ячейки
void updateICounter()
{
	// Установить фон текста и цвет
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Перейти в поле, куда записывается "выполняемая команда(команда, на которую указывает пользователь)"
	mt_gotoXY(62 + 5, 1 + 3 + 1);
	// Формирование строки
	sprintf(temp, "%02d(%02d)", instructionCounter, selectedCell);
	// Вывод строки
	write(1, temp, strlen(temp));
}
// Обновить содержимое ячейки памяти, на которую указывает счетчик
void updateOperation()
{
	// Установить фон текста и цвет
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Перейти в поле, куда записывается содержимое ячейки памяти, на которую указывает счетчик
	mt_gotoXY(62 + 2 + 1, 1 + 3 + 3 + 1);
	int value, command, operand;
	// Получить содержимое памяти в ячейке instructionCounter
	sc_memoryGet(instructionCounter, &value);
	// Декодировать команду
	sc_commandDecode(value, &command, &operand);
	// Формирование строки
	sprintf(temp, "%s%02X : %02X", (value < 0) ? "-" : "+", command, operand);
	// Вывод строки
	write(1, temp, strlen(temp));
}
// Обновить регистр. В качестве аргумента указывается регистр:
// 		Выход за пределы памяти
// 			#define REG_MEMOUTSIDE		0x0		
// 		Неизвестная команда
// 			#define REG_UNKNOWNCOMMAND	0x1		
// 		Ошибка деления на ноль
// 			#define REG_DIVIDEZERO		0x2		
// 		Переполнение ячейки
// 			#define REG_OVERFLOW		0x3		
// 		Игнорирование тактовых импульсов 
// 			#define REG_CLOCKIGNORE		0x4		
void updateFlag(int i)
{
	// Установить фон текста и цвет
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Перейти в поле, куда записывются регистры
	mt_gotoXY(62 + 1 + 3 * i, 1 + 3 + 3 + 3 + 1);
	int valueIn;
	switch (i)
	{
	case REG_OVERFLOW:
		// Установить фон текста
		mt_setbgcolor(CONSOLE);
		// Пользователь может редактировать ячейки памяти и содержимое регистров. Для того, чтобы определить, на какой ячейке находится указатель,
		// используется переменная (selectedCell). Т.к. ячеек памяти 100, то, обычно, эта переменная равна значениям (0...99). Но если выбран регистр,
		// то значение этой переменной может быть [100, 101, 102, 103, 104]. 
		// Если выбран этот регистр, то нужно область этого регистра выделить белым цветом
		if(selectedCell == 103)
		{
			mt_setbgcolor(WHITE);
			mt_setfgcolor(BLACK);
		}
		// Получить содержимое регистра REG_OVERFLOW в переменную valueIn
		sc_regGet(REG_OVERFLOW, &valueIn);
		// Если регистр активен, то графически выделяем этот регистр, заключив его индикатор в квадратные скобки
		if (valueIn)
			write(1, "[P]", 3);
		else
			write(1, " P ", 3);
		break;
	case REG_DIVIDEZERO:
		// Установить фон текста
		mt_setbgcolor(CONSOLE);
		// Если выбран этот регистр, то нужно область этого регистра выделить белым цветом
		if(selectedCell == 102)
		{
			mt_setbgcolor(WHITE);
			mt_setfgcolor(BLACK);
		}
		// Получить содержимое регистра REG_DIVIDEZERO в переменную valueIn
		sc_regGet(REG_DIVIDEZERO, &valueIn);
		// Если регистр активен, то графически выделяем этот регистр, заключив его индикатор в квадратные скобки
		if (valueIn)
			write(1, "[0]", 3);
		else
			write(1, " 0 ", 3);
		break;
	case REG_MEMOUTSIDE:
		// Установить фон текста
		mt_setbgcolor(CONSOLE);
		// Если выбран этот регистр, то нужно область этого регистра выделить белым цветом
		if(selectedCell == 100)
		{
			mt_setbgcolor(WHITE);
			mt_setfgcolor(BLACK);
		}
		// Получить содержимое регистра REG_MEMOUTSIDE в переменную valueIn
		sc_regGet(REG_MEMOUTSIDE, &valueIn);
		// Если регистр активен, то графически выделяем этот регистр, заключив его индикатор в квадратные скобки
		if (valueIn)
			write(1, "[M]", 3);
		else
			write(1, " M ", 3);
		break;
	case REG_CLOCKIGNORE:
		// Установить фон текста
		mt_setbgcolor(CONSOLE);
		// Если выбран этот регистр, то нужно область этого регистра выделить белым цветом
		if(selectedCell == 104)
		{
			mt_setbgcolor(WHITE);
			mt_setfgcolor(BLACK);
		}
		// Получить содержимое регистра REG_CLOCKIGNORE в переменную valueIn
		sc_regGet(REG_CLOCKIGNORE, &valueIn);
		// Если регистр активен, то графически выделяем этот регистр, заключив его индикатор в квадратные скобки
		if (valueIn)
			write(1, "[T]", 3);
		else
			write(1, " T ", 3);
		break;
	case REG_UNKNOWNCOMMAND:
		// Установить фон текста
		mt_setbgcolor(CONSOLE);
		// Если выбран этот регистр, то нужно область этого регистра выделить белым цветом
		if(selectedCell == 101)
		{
			mt_setbgcolor(WHITE);
			mt_setfgcolor(BLACK);
		}
		// Получить содержимое регистра REG_UNKNOWNCOMMAND в переменную valueIn
		sc_regGet(REG_UNKNOWNCOMMAND, &valueIn);
		// Если регистр активен, то графически выделяем этот регистр, заключив его индикатор в квадратные скобки
		if (valueIn)
			write(1, "[E]", 3);
		else
			write(1, " E ", 3);
		break;
	}
}
// Обновить текущую ячейку памяти в виде больших символов
void updateBigMemory()
{
	int value, command, operand;
	char valueChar[5];
	// Получить содержимое памяти по адресу (instructionCounter) - выполняемой команды
	sc_memoryGet(instructionCounter, &value);
	// Декодировать команду
	sc_commandDecode(value, &command, &operand);
	// Сформировать строку из декодированной команды
	sprintf(valueChar, "%s%02X%02X", (value < 0) ? "-" : "+", command, operand);
	// Цикл, проходящий строку больших символов
	for (int i = 0; i < 5; i++)
	// В зависимости от символа, нарисовать ту или иную букву
	switch (valueChar[i])
	{
	case '1': bc_printbigchar(bigChars[0], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '2': bc_printbigchar(bigChars[1], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '3': bc_printbigchar(bigChars[2], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '4': bc_printbigchar(bigChars[3], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '5': bc_printbigchar(bigChars[4], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '6': bc_printbigchar(bigChars[5], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '7': bc_printbigchar(bigChars[6], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '8': bc_printbigchar(bigChars[7], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '9': bc_printbigchar(bigChars[8], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '0': bc_printbigchar(bigChars[9], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case 'A': bc_printbigchar(bigChars[10], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case 'B': bc_printbigchar(bigChars[11], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case 'C': bc_printbigchar(bigChars[12], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case 'D': bc_printbigchar(bigChars[13], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case 'E': bc_printbigchar(bigChars[14], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case 'F': bc_printbigchar(bigChars[15], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '+': bc_printbigchar(bigChars[16], 2 + 8 * i, 14, textColor, CONSOLE); break;
	case '-': bc_printbigchar(bigChars[17], 2 + 8 * i, 14, textColor, CONSOLE); break;
	default:  bc_printbigchar(bigChars[18], 2 + 8 * i, 14, textColor, CONSOLE); break;
	}
}
// Внизу консоли есть область, куда записывается техническая информацию и поле ввода. Эта функция формирует эту область с текстом (c)
void outputWrite(char *c)
{
	// Перейти в область (1, 23). То есть, первый столбец, 23 строка
	mt_gotoXY(1, 23);
	// Установить фон и цвет текста
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(WHITE);
	// Вывести текст
	write(1, c, strlen(c));
}
// Очистить поле технической информации
void outputClear()
{
	// Перейти в область (1, 23). То есть, первый столбец, 23 строка
	mt_gotoXY(1, 23);
	// Установить фон и цвет текста
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(WHITE);
	// Вывести "пустой" текст
	write(1, "                                                         ", strlen("                                                         "));
	// Вернуть каретку в начало строки
	mt_gotoXY(1, 23);
}
// Инициализация графической составляющей консоли
void initiateConsole()
{
	// Прямоугольная область для ячеек памяти. Здесь рисуется прямоугольник и текст "Memory"
	// Установить фон и цвет текста
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Нарисовать прямоугольник по координатам (1, 1), шириной 59 столбцов и высотой 10 строк
	bc_box(1, 1, 59, 10);
	// Перейти в верхнее основание прямоугольника и написать текст "Memory"
	mt_gotoXY(27, 1);
	write(1, "Memory", 6);
	
	
	// Область, где написана техническая информация по горячим клавишам
	// Установить фон и цвет текста
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Нарисовать прямоугольник по координатам (43, 13), шириной 34 столбцов и высотой 8 строк	
	bc_box(43, 13, 34, 8);
	// Перейти в верхнее основание прямоугольника и написать текст "Keys"
	mt_gotoXY(44, 13);
	write(1, "Keys", 4);
	// Переходы на координаты и написание горячих клавиш
	mt_gotoXY(44, 14);
	write(1, "L - load", strlen("L - load"));
	mt_gotoXY(44, 14 + 1);
	write(1, "S - save", strlen("S - save"));
	mt_gotoXY(44, 14 + 1 + 1);
	write(1, "R - run / Ctrl + C - stop", strlen("R - run / Ctrl + C - stop"));
	mt_gotoXY(44, 14 + 1 + 1 + 1);
	write(1, "T - step", strlen("T - step"));
	mt_gotoXY(44, 14 + 1 + 1 + 1 + 1);
	write(1, "I - reset", strlen("I - reset"));
	mt_gotoXY(44, 14 + 1 + 1 + 1 + 1 + 1);
	write(1, "F5 - EAX", strlen("F5 - EAX"));
	mt_gotoXY(44, 14 + 1 + 1 + 1 + 1 + 1 + 1);
	write(1, "F6 - iCounter", strlen("F6 - iCounter"));
	mt_gotoXY(44, 14 + 1 + 1 + 1 + 1 + 1 + 1 + 1);
	write(1, "TAB - iCounter at cursor", strlen("TAB - iCounter at cursor"));
	
	// Прямоугольные области справа, которые отображают информацию по аккумулятору, instructionCounter, Operation, Flags (регистры)
	// Установить фон и цвет текста
	mt_setbgcolor(CONSOLE);
	mt_setfgcolor(textColor);
	// Нарисовать прямоугольники
	bc_box(62, 1, 15, 1);
	bc_box(62, 1 + 3, 15, 1);
	bc_box(62, 1 + 3 + 3, 15, 1);
	bc_box(62, 1 + 3 + 3 + 3, 15, 1);
	// Переходы на координаты и написание текста
	mt_gotoXY(62 + 1, 1);
	write(1, "EAX", strlen("EAX"));
	mt_gotoXY(62 + 1, 1 + 3);
	write(1, "instructionCounter", strlen("instructionCounter"));
	mt_gotoXY(62 + 1, 1 + 3 + 3);
	write(1, "Operation", strlen("Operation"));
	mt_gotoXY(62 + 1, 1 + 3 + 3 + 3);
	write(1, "Flags", strlen("Flags"));
	
	// Прямоугольник для "Больших символов"
	// Установить фон
	mt_setbgcolor(CONSOLE);
	// Нарисовать прямоугольник по координатам (1, 13), шириной 40 столбцов и высотой 8 строк	
	bc_box(1, 13, 40, 8);
	
	// Обновить графически содержимое аккумулятора и "Большой символ"
	updateEAX(EAX);
	updateBigMemory();
	// Обновить графически содержимое регистров
	for (int i = 0; i <= REG_MAX; i++)
		updateFlag(i);
	// Обновить графически (instructionCounter) - текущую выполняемую команду
	updateICounter();
	// Обновить графически содержимое ячеек памяти
	for (int i = 0; i < 100; i++)
		updateMemory(i);
	// Обновить графически текущую выполняемую команду
	updateOperation();
}
// Значение этой переменной определяет, какая задержка (в секундах) между выполнениями отдельных команд при автоматической работе машины
int tact = 1;

// Переменная для хранения результата предыдущей операции
int lastResult = 0;

int ALU(int, int);
// Обработчик команд
int CU()
{
	int command, operand;
	// Если дошли до последней ячейки памяти - "останавливаем" работу
	if(instructionCounter > 99)
		return instructionCounter;
	// Декодирование текущей команды по адресу (instructionCounter). Результат помещается в (command) и (operand) - номер команды и операнд
	if(sc_commandDecode(memory[instructionCounter], &command, &operand) == -1)
	{
		// Если не удается выполнить команду - ставим регистр "неизвестная команда" в активное состояние
		sc_regSet(REG_UNKNOWNCOMMAND, 1);
		// Возвращаем указатель на текущую выполняемую команду
		return instructionCounter;
	}
	// Обработка команд
	switch(command)
	{	
		// Если номер команды - READ (Ввод с терминала в указанную ячейку памяти с контролем переполнения)
		case 0x10:
			{
				outputWrite("Input value (IN HEX): ");
				int temp, result;
				// Считывание пользовательской строки в 16 системе счисления
				scanf("%x", &temp);
				// Записать в ячейку памяти (operand) содержимое (temp). Результат выполнения функции заносится в (result)
				result = sc_memorySet(operand, temp);
				// Опустошить буфер ввода
				while (getchar() != '\n');
				// Очистить поле ввода
				outputClear();
				// Если функция завершена с ошибкой, выставляем регистр "Игнорирование тактовых импульсов" в неактивное состояние, 
				// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
				if(result)
				{					
					sc_regSet(REG_CLOCKIGNORE, 0);
					sc_regSet(REG_OVERFLOW, 1);
					alarm(0);
					return instructionCounter;
				}
				// Сохранить значение результата операции в (lastResult)
				lastResult = temp;
			}
			break;
		// Если номер команды - WRITE (Вывод на терминал значения указанной ячейки памяти)
		case 0x11:
			{
				char temp[30];
				int temp2;
				// Получаем содержимое памяти по адресу (operand) в переменную (temp2). Если функция вернула 0, выводим (temp2) на экран
				if(!sc_memoryGet(operand, &temp2))
				{
					// Очищение поля ввода/вывода
					outputClear();
					// Фрмирование строки
					sprintf(temp, "Output value: %s%X", ((temp2 >> 15) & 0x1) == 1 ? "-" : "", ((temp2 >> 15) & 0x1) == 1 ? ~(temp2 - 1) : temp2);
					// Вывод строки 
					outputWrite(temp);
				}
				else
				{					
					// Если функция завершилась с ошибкой (неверно указан номер ячейки), выставляем регистр "Игнорирование тактовых импульсов" 
					// в неактивное состояние, 
					// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
					sc_regSet(REG_CLOCKIGNORE, 0);
					sc_regSet(REG_MEMOUTSIDE, 1);
					alarm(0);
					return instructionCounter;
				}
			}
			break;
		// Если номер команды - LOAD (Загрузка в аккумулятор значения из указанного адреса памяти)			
		case 0x20:
			// Получить содержимое ячейки памяти по адресу (operand) в переменную command. Если функция завершилась с ошибкой, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, 
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(sc_memoryGet(operand, &command))
			{					
				sc_regSet(REG_CLOCKIGNORE, 0);
				sc_regSet(REG_MEMOUTSIDE, 1);
				alarm(0);
				return instructionCounter;
			}
			// Обновляем аккумулятор содержимым переменной (command). 
			// Если функция завершилась с ошибкой, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, 
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(updateEAX(command))
			{					
				sc_regSet(REG_CLOCKIGNORE, 0);
				sc_regSet(REG_OVERFLOW, 1);
				alarm(0);
				return instructionCounter;
			}
			// Сохранить значение результата операции в (lastResult)
			lastResult = command;
			break;
		// Если номер команды - STORE (Выгрузка значения из аккумулятора по указанному адресу памяти)		
		case 0x21:
			// Присвоение значения аккумулятора (EAX) ячейке памяти по адресу (operand)
			// Если функция завершилась с ошибкой, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, 
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(sc_memorySet(operand, EAX))
			{					
				sc_regSet(REG_CLOCKIGNORE, 0);
				sc_regSet(REG_OVERFLOW, 1);
				alarm(0);
				return instructionCounter;
			}
			// Сохранить значение результата операции в (lastResult)
			lastResult = EAX;
			break;
		// Если номера команд - ADD, SUB, DIVIDE, MUL (сложение, вычитание, деление, умножение). Операции аккумулятора с ячейкой
		// памяти по адресу (operand).
		// Эти функции - арифметические. По условию задания, они должны обрабатываться в функции ALU, а результат обрабатывается здесь.
		case 0x30:
		case 0x31:
		case 0x32:
		case 0x33:
			// Вызываем функцию ALU, которая обрабатывает арифметические операции. 
			// В качестве аргументов передается номер команды (сложение,... умножение), операнд.
			// Если функция завершилась с ошибкой, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, 
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(ALU(command, operand))
			{					
				sc_regSet(REG_CLOCKIGNORE, 0);
				sc_regSet(REG_OVERFLOW, 1);
				alarm(0);
				return instructionCounter;
			}
			// Сохранить значение результата операции в (lastResult)
			lastResult = EAX;
			break;
		// Если номер команды - JUMP (Переход к указанному адресу памяти)		
		case 0x40:
			// Если указана неверная ячейка памяти, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, регистр "Выход за пределы памяти" в активное состояние,
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(operand > 99 || operand < 0)
			{
				sc_regSet(REG_MEMOUTSIDE, 1);		
				sc_regSet(REG_CLOCKIGNORE, 0);
				alarm(0);
				return instructionCounter;
			}
			// Возвращаем адрес ячейки памяти (operand)
			return operand;
			break;
		// Если номер команды - JNEG (Переход к указанному адресу памяти, если в аккумуляторе находится отрицательное число)	
		case 0x41:
			// Если указана неверная ячейка памяти, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, регистр "Выход за пределы памяти" в активное состояние,
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(operand > 99 || operand < 0)
			{
				sc_regSet(REG_MEMOUTSIDE, 1);
				sc_regSet(REG_CLOCKIGNORE, 0);
				alarm(0);
				return instructionCounter;
			}
			// Если аккумулятор отрицательный, возвращаем адрес ячейки памяти (operand)
			if(EAX < 0)
				return operand;
			break;
		// Если номер команды - JZ (Переход к указанному адресу памяти, если в аккумуляторе находится нуль)	
		case 0x42:
			// Если указана неверная ячейка памяти, 
			// выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние, регистр "Выход за пределы памяти" в активное состояние,
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			if(operand > 99 || operand < 0)
			{
				sc_regSet(REG_MEMOUTSIDE, 1);
				sc_regSet(REG_CLOCKIGNORE, 0);
				alarm(0);
				return instructionCounter;
			}
			// Если аккумулятор равен нулю, возвращаем адрес ячейки памяти (operand)
			if(EAX == 0)
				return operand;
			break;
		// Если номер команды - HALT (Останов, выполняется при завершении работы программы)	
		case 0x43:
			// Выставляем регистр "Игнорирование тактовых импульсов" 
			// в неактивное состояние
			// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
			alarm(0);
			sc_regSet(REG_CLOCKIGNORE, 0);
			outputClear();
			outputWrite("Stop");
			return instructionCounter;
			break;
		// Пользовательская функция по варианту
		// Если номер команды - JP (Переход к указанному адресу памяти, если результат предыдущей операции чётный)	
		case 0x58:
			{
				// Если результат предыдущей операции четный
				if(lastResult % 2 == 0)
				{
					// Если указана неверная ячейка памяти, 
					// выставляем регистр "Игнорирование тактовых импульсов" 
					// в неактивное состояние, регистр "Выход за пределы памяти" в активное состояние,
					// посылаем сигнал alarm, функция завершается с указанием на текущую выполняемую команду без сдвига на следующую команду.
					if(operand > 99 || operand < 0)
					{
						sc_regSet(REG_MEMOUTSIDE, 1);
						sc_regSet(REG_CLOCKIGNORE, 0);
						alarm(0);
						return instructionCounter;
					}
					// Возвращаем значение (operand)
					return operand;					
				}
			}
			break;
		// Если указана неизвестная команда
		default:
			// Выставляем флаг "Неизвестная команда" в активное состояние
			sc_regSet(REG_UNKNOWNCOMMAND, 1);				
			// Выставляем флаг "Игнорирование тактовых импульсов" в неактивное состояние
			sc_regSet(REG_CLOCKIGNORE, 0);
			// Посылаем сигнал (alarm)
			alarm(0);
			// Возвращаем указатель на текущую выполняемую команду без сдвига на следующую.
			return instructionCounter;
	}
	// Возвращаем указатель на текущую выполняемую команду СО сдвигом на следующую.
	return instructionCounter + 1;
}
// Выполнить арифметическую операцию
int ALU (int command, int operand)
{
	switch(command)
	{
		// Если номер команды - ADD (Выполняет сложение слова в аккумуляторе и слова из указанной ячейки памяти (результат в аккумуляторе))
		case 0x30:
			{
				int temp;
				// Получить содержимое ячейки памяти по адресу (operand) в переменную (temp). Если функция вернула 0 - значит все нормально
				if(!sc_memoryGet(operand, &temp))
				{
					// Вернуть результат обновления аккумулятора, куда заносится значение (EAX + temp) = содержимое аккумулятора + содержимое ячейки
					return updateEAX(EAX + temp);
				}
				else
				// Если указана неверная ячейка памяти, возвращаем -1 (функция завершена с ошибкой)
					return -1;
			}
			break;
		// Если номер команды - SUB (Вычитает из слова в аккумуляторе слово из указанной ячейки памяти (результат в аккумуляторе))
		case 0x31:
			{
				int temp;
				// Получить содержимое ячейки памяти по адресу (operand) в переменную (temp). Если функция вернула 0 - значит все нормально
				if(!sc_memoryGet(operand, &temp))
				{
					// Вернуть результат обновления аккумулятора, куда заносится значение (EAX - temp) = содержимое аккумулятора - содержимое ячейки
					return updateEAX(EAX - temp);
				}
				else
				// Если указана неверная ячейка памяти, возвращаем -1 (функция завершена с ошибкой)
					return -1;
			}
			break;
		// Если номер команды - DIVIDE (Выполняет деление слова в аккумуляторе на слово из указанной ячейки памяти (результат в аккумуляторе))
		case 0x32:
			{
				int temp;
				// Получить содержимое ячейки памяти по адресу (operand) в переменную (temp). Если функция вернула 0 - значит все нормально
				if(!sc_memoryGet(operand, &temp))
				{
					// Если в указанной ячейки памяти содержится ноль, то устанавливаем регистр "Деление на ноль" в активное состояни,
					// функцию завершаем с ошибкой.
					if(temp == 0)
					{
						sc_regSet(REG_DIVIDEZERO, 1);
						return -1;
					}
					else
						// Вернуть результат обновления аккумулятора, куда заносится значение (EAX / temp) = содержимое аккумулятора / содержимое ячейки
						return updateEAX(EAX / temp);
				}
				else
				// Если указана неверная ячейка памяти, возвращаем -1 (функция завершена с ошибкой)
					return -1;
			}
			break;
		// Если номер команды - MUL (Выполняет произведение слова в аккумуляторе и слова из указанной ячейки памяти (результат в аккумуляторе))
		case 0x33:
			{
				int temp;
				// Получить содержимое ячейки памяти по адресу (operand) в переменную (temp). Если функция вернула 0 - значит все нормально
				if(!sc_memoryGet(operand, &temp))
				{
					// Вернуть результат обновления аккумулятора, куда заносится значение (EAX * temp) = содержимое аккумулятора * содержимое ячейки
					return updateEAX(EAX * temp);
				}
				else
				// Если указана неверная ячейка памяти, возвращаем -1 (функция завершена с ошибкой)
					return -1;
			}
			break;
	}
	return 0;
}
// Один такт работы машины
void step()
{
	// Запомнить текущую выполняемую команду, чтобы потом обновить ее графически, если она изменится
	int lastICounter = instructionCounter;
	// Вызвать функцию CU(), которая вернет указатель на новую команду
	int iCounter = CU();
	// Если дошли до конца - возвращаем пустое значение функции, чтобы не выполнять дальнейшие инструкции
	if(iCounter > 99)
		return;
	// Назначаем новый (instructionCounter), указатель на новую выполняемую команду
	instructionCounter = iCounter;
	// Графически обновляем элементы интерфейса
	updateBigMemory();
	updateMemory(lastICounter);
	updateMemory(instructionCounter);
	updateOperation(instructionCounter);
	updateICounter();
	mt_gotoXY(1, 23);	
}
// Обработчик сигналов. Нужен для обработки нажатия Ctrl + C
void signalHandler(int sigNum)
{
	// Вырезка из методички:
	//
	// SIGALRM – сигнал таймера (англ. alarm clock). Посылается процессу
	// ядром при срабатывании таймера. Каждый процесс может устанавливать
	// не менее трѐх таймеров. Первый из них измеряет прошедшее реальное
	// время. Этот таймер устанавливается самим процессом при помощи
	// системных вызовов alarm или setitimer.
	//
	// Если был вызван alarm(). По сути, это как таймер, поскольку внутри содержится alarm(), который вновь вызовет данные инструкции.
	if (sigNum == SIGALRM)
	{
		int reg;
		// Получаем содержимое регистра "Игнорирование тактовых импульсов"
		sc_regGet(REG_CLOCKIGNORE, &reg);
		// Если регистр не активен - завершаем функцию, не вызывая более alarm(). Автоматическая работа машины останавливается
		if(!reg)
			return;
		// Такт работы машины
		step();
		// Если дошли до последней команды - завершаем работу машины, ставим регистр "Игнорирование тактовых импульсов" в неактивное состояние.
		if (instructionCounter == 99)
		{
			sc_regSet(REG_CLOCKIGNORE, 0);
			//alarm(0);
			mt_gotoXY(1, 23);
			return;
		}
		// Делаем задержку в (tact) секунд. Как только задержка завершится - вновь вызовется эта функция, т.к. в main() был подписан обработчик этого
		// прерывания (alarm вызывает прерывание).
		alarm(tact);
	}
	// Вырезка из методички:
	//
	// SIGUSR1 и SIGUSR2 – пользовательские сигналы (англ. user defined
	// signals 1 and 2). Так же как и сигнал SIGTERM, эти сигналы
	// никогда не посылаются ядром и могут использоваться для любых
	// целей по выбору пользователя.
	//
	// Если был поднят пользовательский сигнал (вызывается с помощью raise(SIGUSR1)).
	// Этот сигнал вызывается при обработке в main() клавиши I, которая отвечает за сброс состояния машины.
	else if (sigNum == SIGUSR1)
	{
		// Сброс ячеек памяти
		sc_memoryInit();
		// Сброс регистров
		sc_regInit();
		// Сдвигаем указатель текущей выполняемой команды на самую первую
		instructionCounter = 0;
		// Обновляем графически содержимое памяти
		for (int i = 0; i < 100; i++)
			updateMemory(i);
		// Обновляем графически "Большой символ"
		updateBigMemory();
		// Обновляем графически содержимое аккумулятора, устанавливаем его в ноль
		updateEAX(0);
		// Обновляем графически содержимое регистров
		for (int i = 0; i <= REG_MAX; i++)
			updateFlag(i);
		// Обновляем графически указатель на текущую выполняемую команду
		updateICounter();
		// Обновляем графически содержимое текущей выполняемой операции
		updateOperation();
	}
	// Вырезка из методички:
	//
	// SIGINT – сигнал прерывания программы (англ. interrupt). Посылается
	// ядром всем процессам, связанным с терминалом, когда пользователь
	// нажимает клавишу прерывания (другими словами, в потоке
	// ввода появляется управляющий символ, соответствующий клавише
	// прерывания). Примером клавиши прерывания может служить комбинация
	// CTRL+C. Это также обычный способ остановки выполняющейся программы;
	//
	// Просто обработка Ctrl+C, которая останавливает автоматическое выполнение команд
	else if (sigNum == SIGINT)
	{
		int reg;
		// Получение состояние регистра "Игнорирование тактовых импульсов"
		sc_regGet(REG_CLOCKIGNORE, &reg);
		// Если флаг не активен (то есть машина выполняет автоматически команды)
		if(reg)
		{
			// Устанавливаем регистр "Игнорирование тактовых импульсов" в неактивное состояние, завершаем функцию
			sc_regSet(REG_CLOCKIGNORE, 0);
			alarm(0);
			mt_gotoXY(1, 23);
			return;
		}
		// Если машина не работает, завершаем выполнение всей программы, при этом восстановив изначальные настройки консоли
		else
		{
			rk_mytermrestore();
			mt_gotoXY(1, 24);
			exit(0);
		}
	}
}

int main()
{
	// Вызов signal определяет действие программы при поступлении сигнала с
	// номером signum. Действие может быть задано как: адрес пользовательской
	// функции (в таком случае в функцию в качестве параметра передаѐтся номер
	// полученного сигнала) или макросы SIG_IGN (для игнорирования сигнала) и
	// SIG_DFL (для использования обработчика по умолчанию).
	// Если действие определено как пользовательская функция, то при поступлении
	// сигнала программа будет прервана, и процессор начнѐт выполнять указанную
	// функцию. После еѐ завершения выполнение программы, получившей
	// сигнал, будет продолжено, и обработчик сигнала будет установлен в SIG_DFL.
	//
	// Подписываем сигнали на обработчик (signalHandler)
	signal(SIGALRM, signalHandler);
	signal(SIGUSR1, signalHandler);
	signal(SIGINT, signalHandler);
	int va;
	// Очищение экрана консоли
	mt_clrscr();
	// Инициализация памяти
	sc_memoryInit();
	// Инициализация графической составляющей машины
	initiateConsole();
	// Перевести каретку вниз
	mt_gotoXY(1, 23);
	enum keys k;
	int reg;
	// Обработка горячих клавиш
	while (1)
	{
		// Получить состояние регистра "Игнорирование тактовых импульсов"
		sc_regGet(REG_CLOCKIGNORE, &reg);
		// Если регистр активен, то продолжаем выполнение цикла, не считывания клавиши пользователя
		if (reg)
			continue;		
		// Считать клавишу пользователя
		rk_readkey(&k);
		// Если нажата стрелочка вниз
		if (k == KEY_DOWN)
		{
			// Если пользовательский курсор находится на одном из регистров (selectedCell указывает на них как значения [100, 101, 102, 103, 104]),
			// то вызывается continue, который проигнорирует дальнейшие инструкции.
			if(selectedCell > 99)
				continue;
			int value, command, operand, prevCounter = selectedCell;
			// Если при курсор находится на 90+ ячейках памяти (то есть в самом низу), то прыгаем на самую верхнюю ячейку памяти
			if(selectedCell + 10 > 99)
				selectedCell -= 90;
			else
				selectedCell += 10;
			// Графически обновляем содержимое памяти и указатель (instructionCounter)
			updateMemory(prevCounter);
			updateMemory(selectedCell);
			updateICounter();
		}
		// Если нажата стрелочка вверх
		else if (k == KEY_UP)
		{
			// Если пользовательский курсор находится на одном из регистров (selectedCell указывает на них как значения [100, 101, 102, 103, 104]),
			// то вызывается continue, который проигнорирует дальнейшие инструкции.
			if(selectedCell > 99)
				continue;
			int value, command, operand, prevCounter = selectedCell;

			// Если при курсор находится на < 10 ячейках памяти (то есть в самом верху), то прыгаем на самую нижнюю ячейку памяти
			if(selectedCell - 10 < 0)
				selectedCell += 90;
			else
				selectedCell -= 10;
			// Графически обновляем содержимое памяти и указатель (instructionCounter)
			updateMemory(prevCounter);
			updateMemory(selectedCell);
			updateICounter();
		}
		// Если нажата стрелочка влево
		else if (k == KEY_LEFT)
		{
			int value, command, operand, prevCounter = selectedCell;
			// Если пользовательский курсор находится на одном из регистров (selectedCell указывает на них как значения [100, 101, 102, 103, 104])
			if(selectedCell > 99)
			{
				selectedCell--;
				// Графически обновляем все регистры
				updateFlag(REG_MEMOUTSIDE);
				updateFlag(REG_UNKNOWNCOMMAND);
				updateFlag(REG_DIVIDEZERO);
				updateFlag(REG_OVERFLOW);
				updateFlag(REG_CLOCKIGNORE);
				// Если при нажатии стрелочки влево, курсор сместился на ячейку (0...99), то графически обновляем эту ячейку
				if(selectedCell < 100)
					updateMemory(selectedCell);
			}
			else
			{
				// Если  курсор находится на левом углу, прыгаем на правый
				if((selectedCell % 10) - 1 < 0)
					selectedCell += 9;
				else
					selectedCell -= 1;
				// Графически обновляем содержимое памяти и указатель (instructionCounter)
				updateMemory(prevCounter);
				updateMemory(selectedCell);
				updateICounter();
			}
		}
		// Если нажата стрелочка вправо
		else if (k == KEY_RIGHT)
		{
			int value, command, operand, prevCounter = selectedCell;
			// Если пользовательский курсор находится на одном из регистров (selectedCell указывает на них как значения [100, 101, 102, 103, 104])
			if(selectedCell >= 99)
			{
				// Если курсор указывает на крайний правый регистр, вызывается continue, который игнорирует дальнейшие инструкции
				if(selectedCell + 1 > 103)
					continue;
				selectedCell++;
				// Если переместились с ячейки памяти на регистр, то графически обновляем ячейку памяти
				if(selectedCell == 100)
					updateMemory(selectedCell - 1);
				// Графически обновляем регистры
				updateFlag(REG_MEMOUTSIDE);
				updateFlag(REG_UNKNOWNCOMMAND);
				updateFlag(REG_DIVIDEZERO);
				updateFlag(REG_OVERFLOW);
				updateFlag(REG_CLOCKIGNORE);
			}
			else
			{
				// Если курсор находится на правом углу, прыгаем на левый
				if ((selectedCell % 10) + 1 > 9)
					selectedCell -= 9;
				else
					selectedCell += 1;
				// Графически обновляем содержимое памяти и указатель (instructionCounter)
				updateMemory(prevCounter);
				updateMemory(selectedCell);
				updateICounter();
			}
		}
		// Если нажат Enter (редактировать текущую ячейку)
		else if (k == KEY_ENTER)
		{
			char temp[50];
			int command, operand, value;
			// Если пользовательский курсор находится на регистре
			if(selectedCell > 99)
			{
				switch(selectedCell - 100)
				{
					case 0:
						// Получаем содержимое регистра
						sc_regGet(REG_MEMOUTSIDE, &value);
						// Инвертируем значение регистра (вкл/выкл)
						sc_regSet(REG_MEMOUTSIDE, 1 - value);
						break;
					case 1:
						// Получаем содержимое регистра
						sc_regGet(REG_UNKNOWNCOMMAND, &value);
						// Инвертируем значение регистра (вкл/выкл)
						sc_regSet(REG_UNKNOWNCOMMAND, 1 - value);
						break;
					case 2:
						// Получаем содержимое регистра
						sc_regGet(REG_DIVIDEZERO, &value);
						// Инвертируем значение регистра (вкл/выкл)
						sc_regSet(REG_DIVIDEZERO, 1 - value);
						break;
					case 3:
						// Получаем содержимое регистра
						sc_regGet(REG_OVERFLOW, &value);
						// Инвертируем значение регистра (вкл/выкл)
						sc_regSet(REG_OVERFLOW, 1 - value);
						break;
					case 4:
						// Получаем содержимое регистра
						sc_regGet(REG_CLOCKIGNORE, &value);
						// Инвертируем значение регистра (вкл/выкл)
						sc_regSet(REG_CLOCKIGNORE, 1 - value);
						break;
				}
				// Очищаем поле ввода
				outputClear();
				continue;
			}
			outputWrite("[CHANGE VALUE] INPUT COMMAND (IN HEX): ");
			// Считываем команду
			scanf("%x", &command);
			// Очищаем буфер ввода от мусора
			while (getchar() != '\n');
			// Очищаем поле ввода
			outputClear();
			outputWrite("[CHANGE VALUE] INPUT OPERAND (IN HEX): ");
			// Считываем операнд
			scanf("%x", &operand);
			// Очищаем буфер ввода от мусора
			while (getchar() != '\n');
			// Очищаем поле ввода
			outputClear();
			// Кодируем команду. Если функция завершилась успешно, меняем содержимое ячейки памяти по адресу (selectedCell) на новое значение (value)
			if(!sc_commandEncode(command, operand, &value))
			{			
				sc_memorySet(selectedCell, value);
				// Графически обновляем ячейку (selectedCell)
				updateMemory(selectedCell);
				// Если редактируемая ячейка является текущей выполняемой, обновляем "большой символ"
				if(selectedCell == instructionCounter)
					updateBigMemory();
			}
			// Очищаем экран
			mt_clrscr();
			// Перерисовываем графическую консоль
			initiateConsole();
		}
		// Если нажата клавиша L (загрузить содержимое файла в память)
		else if (k == KEY_L)
		{
			char temp[50];
			outputWrite("[LOAD FILE] INPUT FILE NAME: ");
			// Ввести название файла
			scanf("%s", temp);
			// Очистить буфер воода от мусора
			while (getchar() != '\n');
			// Загрузить содержимое файла под названием (temp) в память. Если функция выполнена успешно, перерисовываем графическую консоль
			if (!sc_memoryLoad(temp))
			{
				instructionCounter = 0;
				sc_regInit();
				for (int i = 0; i < 100; i++)
					updateMemory(i);
				updateOperation();
				updateICounter();
				for (int i = 0; i <= REG_MAX; i++)
					updateFlag(i);
				updateEAX(0);
				updateBigMemory();
			}
			mt_clrscr();
			initiateConsole();
		}
		// Если нажата клавиша I (сбросить состояние машины)
		else if (k == KEY_I)
		{
			raise(SIGUSR1);
		}
		// Если нажата клавиша R (начать автоматическое выполнение команд)
		else if (k == KEY_R)
		{
			// Установить регистр "Игнорирование тактовых импульсов" в активное состояние
			sc_regSet(REG_CLOCKIGNORE, 1);
			// Вызывать задержку в (tact) секунд
			alarm(tact);
		}
		// Если нажата клавиша F5 (изменить содержимое аккумулятора)
		else if (k == KEY_F5)
		{
			char temp[50];
			outputWrite("[EAX] INPUT VALUE: ");
			int readX;
			// Считать число в 16 системе счисления
			scanf("%x", &readX);
			// Очистить буфер ввода от мусора
			while (getchar() != '\n');
			// Очистить поле ввода
			outputClear();
			// Обновить содержимое аккумулятора
			updateEAX(readX);
		}
		// Если нажата клавиша F6 (изменить значение (instructionCounter))
		else if (k == KEY_F6)
		{
			int temp;
			outputWrite("[INSTRUCTION COUNTER] INPUT VALUE: ");
			// Считать число
			scanf("%d", &temp);
			// Очистить буфер от мусора
			while (getchar() != '\n');
			// Очистить поле ввода
			outputClear();
			// Если указана неверная ячейка памяти, устанавливаем регистр "Выход за пределы памяти" в активное состояние
			if(temp < 0 || temp > 99)
			{
				sc_regSet(REG_MEMOUTSIDE, 1);
				continue;
			}
			// Графически обновляем консоль
			int prevICounter = instructionCounter;
			instructionCounter = temp;
			updateMemory(prevICounter);
			updateMemory(instructionCounter);
			updateBigMemory();
			updateICounter();
			updateOperation();
		}
		// Если нажата клавиша TAB (установить (instructionCounter) на текущую указываемую ячейку пользователем)
		else if (k == KEY_TAB)
		{
			// Если курсор находится на регистре, дальнейшие инструкции не выполняются
			if(selectedCell > 99)
				continue;
			// Графически обновляем консоль
			int prevICounter = instructionCounter;
			// Назначаем новую выполняемую команду как (selectedCell)
			instructionCounter = selectedCell;
			updateMemory(prevICounter);
			updateMemory(instructionCounter);
			updateICounter();
			updateBigMemory();
			updateOperation();
		}
		// Если нажата клавиша S (сохранить содержимое памяти в файл)
		else if (k == KEY_S)
		{
			char temp[50];
			outputWrite("[SAVE FILE] INPUT FILE NAME: ");
			// Считать название файла
			scanf("%s", temp);
			// Очистить буфер ввода от мусора
			while (getchar() != '\n');
			// Сохранить содержимое памяти в файл с названием (temp)
			sc_memorySave(temp);
			// Очистить поле ввода
			outputClear();
		}
		// Если нажата клавиша T (выполнить однократно текущую команду)
		else if (k == KEY_T)
		{
			step();
		}
		mt_gotoXY(1, 23);
	}
}
