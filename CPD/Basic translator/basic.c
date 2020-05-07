#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// Коды ошибок
enum errors
{
	// Ошибка открытия входного файла
	ERROR_OPENING_INPUT_FILE,
	// Ошибка открытия выходного файла
	ERROR_OPENING_OUTPUT_FILE,
	// Другой тип ошибки (вроде ошибок в строке и т.п. - то есть все ошибки, не входящие в список выше)
	ERROR_OTHER,
	// Успешно
	SUCCESS
};

int  pr = 99;
char letter[100];
// Ячейки памяти могут хранить значения переменных. Для того, чтобы обозначить, какая ячейка хранит какую переменную - необходима эта функция.
// В нее передается название переменной, после чего функция возвращает номер ячейки, в которой хранится значение этой переменной.
// Если до этого момента такой переменной не было, она инициализируется здесь же.
int variable(char per)
{
	// Переменные будут храниться, начиная с последней ячейки памяти. Изначально, итератор (i) указывает на последнюю ячейку памяти (99)
	int i = 99;
	do
	{
		// letter[i] - данный массив хранит название переменных, которые находятся в каждой ячейке (в данном случае в ячейке по адресу i)
		// Если в ячейке по адресу (i) хранится переменная под названием (per), то возвращаем её адрес (i)
		if (per == letter[i])
			return i;
		// Уменьшаем итератор 99 -> 0
		i--;
	}	while (i != 0);
	// Если цикл закончился и не вернул адрес переменной, то инициализируем её. 
	// В ячейку памяти по адресу (pr) (которая изначальна равна 99) записывается название переменной (per)
	letter[pr] = per;
	// Уменьшаем (pr), тем самым сдвигая адрес новой переменной
	pr--;
	// Возвращаем адрес ячейки памяти, который указывает на переменную (возвращается сумма pr + 1, т.к. выше данный итератор был уменьшен на единицу)
	return (pr + 1);
}
// Основная функция транслятора
// Функция возвращает значения из перечисления (errors), описанного выше
int basic(char *name1, char *name2)
{
	char buf[20], c, a;
	int outputCell = -1, cellNum = 0, flag2 = 1, i, b, extraVar = -1, n[100], err, k, m, o, flag1 = 1, extraVar2 = -1, strNum = 0;
	// outputCell 		- номер ячейки в выходном файле
	// cellNum 			- обрабатываемая строка
	// flag1, flag2 	- флаги окончания считывания программы, устанавливаются в истинное состояние при встрече оператора (END)
	// strNum 			- номер считываемой строки в исходном файле
	//
	// extraVar 		- счетчик для дополнительных переменных, возникающих в случаях вроде if a < 55 (суть в том,
	// что под 55 выделяется отдельная ячейка памяти, под нее нужно выделить переменную)
	//
	// n[100] 			- содержимое ячеек
	// err 				- результат операций считывания scanf()
	// b, k, m, o 		- буферы
	//
	// Структура входных данных имеет следующий вид:
	// 10 INPUT A
	// 20 INPUT B
	// 30 LET A=A*B
	// 40 IF A<9 GOTO 60
	// 50 OUTPUT A
	// 60 END
	// Структура выходного файла:
	// 0 READ 99
	// 1 READ 98
	// 2 LOAD 99
	// 3 MUL 98
	// 4 STORE 99
	// 5 LOAD 99
	// 97 = 9
	// 6 SUB 97
	// 7 JNEG 9
	// 8 WRITE 99
	// 9 HALT
	// Как видно, количество строк увеличилось. Это по большей части связано с тем, что многие операторы с Simple Basic транслируются
	// более сложными конструкциями в Simple Assembler:
	//
	// INPUT A - > READ 99 (в 99 ячейке хранится значение переменной A)
	// INPUT B - > READ 98 (в 99 ячейке хранится значение переменной A)
	//
	// LET A=A*B. Для выполнения этой инструкции нужно проделать следующие действия:
	// 1) Загрузить значение первой переменной в аккумулятор (А)	== 2 LOAD 99
	// 2) Вычесть из аккумулятора значение второй переменной (B)	== 3 MUL 98
	// 3) Занести получившееся значение в переменную А (ячейка 99)	== 4 STORE 99
	// Аккумулятор в данном случае выступает в качестве временного буфера, где выполняются арифметические действия, затем новое значение
	// загружается в нужную ячейку.
	//
	// IF A<9 GOTO 50. Для выполнения этой инструкции нужно проделать следующие действия:
	// 1) Загрузить значение переменной (А) в аккумулятор					== 5 LOAD 99
	// 2) Предоставить под цифровое значение '9' свободную ячейку памяти 	== 97 = 9
	// 3) Вычесть из аккумулятора (в котором хранится значение
	// переменной (A) значения '9'											== 6 SUB 97
	// 4) Вызвать необходимую команду (в данном случае JNEG),
	// которая выполнит переход на ячейку памяти, если в аккумуляторе
	// отрицательное число													== 7 JNEG 9
	// Девятка здесь указывает на ту ячейку памяти, куда транслируется оператор (END)
	// 
	// Отдельно по IF: возможны следующие написания оператора:
	// IF A<B
	// IF A>B
	// IF A=B
	// Главная идея трансляции "ифа" - привести все переменные в одну сторону, выполнить арифметические операции в аккумуляторе
	// и использовать команды (JNEG) или (JZ) - переход на ячейку памяти, если в аккумуляторе число меньше нуля, 
	// и переход на ячейку памяти, если в аккумуляторе ноль соотвественно.
	// То есть, необходимо конструкции выше привести к виду:
	// IF A<B -> IF A-B<0
	// IF A>B -> IF 0>B-A
	// IF A=B -> IF A-B=0
	// Получается, что необходимо вычислить значения выражений, занести все это в аккумулятор, а затем вызвать (JNEG) или (JZ), в зависимости
	// от операции сравнения. (JZ) вызывается при операции сравнения "=".
	// 
	// OUTPUT A -> WRITE 99 (Вывести значение из ячейки 99, где хранится переменная (А))
	// END -> HALT (Завершение программы)
	//
	// Основная проблема состоит в (IF... -->>GOTO<<-- ), поскольку для (GOTO) необходимо указывать номер строки.
	// Для этого используется массив (n[]), где в качестве ключа используется порядковый номер инструкции в исходном файле, 
	// а значение переменной - номер ячейки в выходном файле.
	// К примеру строка:
	// 60 END
	// Имеет порядковый номер 6. Его транслированная команда находится в ячейке под номером 9.
	// Получается, что адрес команды (END)(Basic) n[6] = 9; в девятой ячейки памяти.
	// Поэтому, когда будет обрабатываться (GOTO), необходимо в (GOTO 60) взять число и поделить его на десять,
	// тем самым получив порядковый номер строки, на которую требуется перейти при выполнении инструкции.
	// (cellNum) отвечает за обозначение порядкового номера инструкции
	// outputCell - номер ячейки памяти, где инструкция начинает свою реализацию
	FILE *file1, *file2;
	
	// Открыть входной файл
	file1 = fopen(name1, "rt");
	// Если не удалось открыть входной файл, возвращаем код "Ошибка открытия входного файла"
	if (file1 == NULL)	return ERROR_OPENING_INPUT_FILE;
	
	// Открыть выходной файл
	file2 = fopen(name2, "wt");
	// Если не удалось открыть выходной файл, возвращаем код "Ошибка открытия выходного файла"
	if (file2 == NULL) return ERROR_OPENING_OUTPUT_FILE;
	
	// Инициализация переменных. 100 ячеек освобождается от буквенных обозначений переменных
	for (i = 0; i < 100; i++)
		letter[i] = 0;
	// Инициализация соответствий строк из Basic в Assembler
	for (i = 0; i < 100; i++)
		n[i] = -1;
	
	// Этап проверки на ошибки и указание соответствий строк Basic -> Assembler
	do
	{
		// Инкрементируем номер строки
		cellNum++;
		buf[0] = '\0';
		// Считываем номер строки из файла
		fscanf(file1, "%d", &strNum);
		// Считываем оператор
		fscanf(file1, " %s", buf);
		// Номера строк в Basic должны начинаться с 10 и увеличиваться с шагом в десять по возрастающей. 
		// Проверка на соответствие этому требованию
		if (cellNum * 10 != strNum)
		{
			printf("Ошибка в строке %d. Неверно указан номер строки: строки должны находиться в промежутке [10;+] с шагом в 10 в возрастающей последовательности без пробелов в цифрах и дублей\n\n", strNum);
			return ERROR_OTHER;			
		}
		// Если это комментарий, то просто считываем все до конца строки и игнорируем
		if (!strcmp(buf, "REM"))
		{
			do
			{
				fscanf(file1, "%c", &c);
			} while (c != '\n');
		}
		else
		// Если встречен оператор ввода значения в переменную
		if (!strcmp(buf, "INPUT"))
		{
			// Увеличиваем порядковый счетчик ячеек
			outputCell++;
			// Ставим соответствие (cellNum) строке в Basic - (outputCell) ячейке в Assembler
			n[cellNum] = outputCell;
			// Пропускаем один символ (пробел)
			fseek(file1, 1, 1);
			// Считать название переменной
			fscanf(file1, "%c", &c);
			// Если переменная не является заглавной латинской буквой, выводим ошибку и завершаем работу функции
			if ((c<'A') || (c>'Z'))
			{
				printf("Ошибка в строке %d. Некорректное указание параметров в INPUT '%c' \n\n", strNum, c);
				return ERROR_OTHER;
			}
		}
		else
		// Если встречен оператор вывода значения переменной
		if (!strcmp(buf, "OUTPUT"))
		{
			// Увеличиваем порядковый счетчик ячеек
			outputCell++;
			// Ставим соответствие (cellNum) строке в Basic - (outputCell) ячейке в Assembler
			n[cellNum] = outputCell;
			// Пропускаем один символ (пробел)
			fseek(file1, 1, 1);
			// Считать название переменной
			fscanf(file1, "%c", &c);
			// Если переменная не является заглавной латинской буквой, выводим ошибку и завершаем работу функции
			if ((c<'A') || (c>'Z'))
			{
				printf("Ошибка в строке %d. Некорректное указание параметров в OUTPUT '%c' \n\n", strNum, c);
				return ERROR_OTHER;
			}
		}
		else
		// Если встречен оператор перехода в указанную строку
		if (!strcmp(buf, "GOTO"))
		{
			// Увеличиваем порядковый счетчик ячеек
			outputCell++;
			// Ставим соответствие (cellNum) строке в Basic - (outputCell) ячейке в Assembler
			n[cellNum] = outputCell;
			// Пропускаем один символ (пробел)
			fseek(file1, 1, 1);
			// Считать номер строки
			err = fscanf(file1, "%d", &b);
			// Если функция не смогла считать целочисленное значение, выводим ошибку и завершаем работу функции
			if (!err)
			{
				printf("Ошибка в строке %d. Некорректное указание параметров в GOTO \n\n", strNum);
				return ERROR_OTHER;
			}
		}
		else
		// Если встречен оператор IF
		if (!strcmp(buf, "IF"))
		{
			// Ставим соответствие (cellNum) строке в Basic - (outputCell + 1) ячейке в Assembler
			n[cellNum] = outputCell + 1;
			// Смещаем счетчик ячеек на 3 позиции, так как реализация IF в ассемблере занимает три ячейки
			outputCell += 3;
			// Пропускаем один символ (пробел)
			fseek(file1, 1, 1);
			// Считываем следующее за IF условие. В переменную (c) заносится название переменной, в переменную (а) заносится оператор сравнения
			err = fscanf(file1, " %c%c", &c, &a);
			// Если переменная не является заглавной латинской буквой, выводим ошибку и завершаем работу функции
			if ((c<'A') || (c>'Z'))
			{
				printf("Ошибка в строке %d. Некорректное указание параметров в IF '%c%c' - слева могут находиться только названия переменных\n\n", strNum, c, a);
				return ERROR_OTHER;
			}
			else
				// Условный оператор для операций сравнения
				switch (a)
				{
					case '<':
					case '>':
					case '=':
						// Считываем число после оператора сравнения
						err = fscanf(file1, "%d", &b);
						// Если fscanf не сумел считать целое число - будет произведена попытка считать название переменной
						if (!err)
						{
							// Считать название переменной
							err = fscanf(file1, "%c", &a);
							// Если не удалось считать символ - выводим ошибку и завершаем работу функции
							if (!err)
							{
								printf("Ошибка в строке %d. Некорректное указание параметров в IF '%c' \n\n", strNum, a);
								return ERROR_OTHER;
							}
						}
						// Считать "GOTO"
						fscanf(file1, " GOTO ");
						// Считать номер строки, на которую ссылается "GOTO"
						err = fscanf(file1, "%d", &o);
						// Если не удалось считать целое число - выводим ошибку и завершаем работу функции
						if (!err)
						{
							printf("Ошибка в строке %d. Некорректное указание параметров в GOTO \n\n", strNum);
							return ERROR_OTHER;
						}
						break;
					// Если встречен неизвестный оператор сравнения - выводим ошибку и завершаем работу функции
					default:
						printf("Ошибка в строке %d. Неизвестный символ\n\n", strNum);
						return ERROR_OTHER;
				}
		}
		else
		// Если встречена операция присвоения переменной
		if (!strcmp(buf, "LET"))
		{
			k = 0;
			// Считать название переменной и знак равенства
			fscanf(file1, " %c%c", &a, &c);
			// Считать число
			err = fscanf(file1, "%d", &b);
			// Если считано не число (то есть записана переменная)
			if (err == 0)
			{
				// Ставим соответствие (cellNum) строке в Basic - (outputCell + 1) ячейке в Assembler
				n[cellNum] = outputCell + 1;
				// Считать выражение
				fscanf(file1, "%s", buf);
				// Цикл, проверяющий корректность выражения
				do
				{
					// Если выражение содержит названия переменных/арифм. операции/скобки, то все нормально, иначе выводим ошибку и завершаем программу
					if (((buf[k] >= 'A') && (buf[k] <= 'Z')) || (buf[k] == '*') ||
						(buf[k] == '/') || (buf[k] == '-') || (buf[k] == '+') ||
						(buf[k] == '(') || (buf[k] == ')') || (buf[k] == '='))
						k++;
					else
					{
						printf("Ошибка в строке %d. Некорректный синтаксис LET '%c'. \n\n", strNum, buf[k]);
						return ERROR_OTHER;
					}
				} while (buf[k] != '\0');
				// Если выражение простое вида (А+В), то смещаем счетчик ячеек на три позиции
				if (strlen(buf) == 3)
					outputCell += 3;
				else
				{
					k = 0;
					do
					{
						// Если встречена '(' скобка - с помощью цикла ищем ')'. Если такой нет - выводим ошибку и завершаем работу функции
						if (buf[k] == '(')
						{
							i = k;
							do
							{
								if (buf[i] != '\0')
								{
									printf("Ошибка в строке %d. Не найден символ ')'.\n\n", strNum);
									return ERROR_OTHER;
								}
								i++;
							} while (buf[i] != ')');
						}
						// Если встречена ')' скобка -
						if (buf[k] == ')')
						{
							i = k;
							// Ищем '('. Если такой нет - выводим ошибку и завершаем работу функции
							do
							{
								if (buf[i] != '\0')
								{
									printf("Ошибка в строке %d. Не найден символ '('.\n\n", strNum);
									return ERROR_OTHER;
								}
								i--;
							} while (buf[i] != '(');
							// Переходим на первый символ в скобках
							i = m = i + 1;
							// Проход выражения в скобках 
							do
							{
								// Если встречен оператор умножения/деления - сдвигаем счетчик ячеек на три позиции
								if ((buf[i] == '*') || (buf[i] == '/'))
								{
									outputCell += 3;
									o = i - 1;
									do
									{
										o++;
										buf[o] = buf[o + 2];
									} while (buf[o + 2] != '\0');
									outputCell++;
								}
								i++;
							} while (buf[i] != ')');
							i = m;
							outputCell++;
							// В выражении в скобках ищутся операции сложения/вычитании, после чего смещается счетчик ячеек на одну позицию
							do
							{
								if ((buf[i] == '+') || (buf[i] == '-'))
									outputCell++;
								i++;
							} while (buf[i] != ')');

							outputCell++;
							o = m - 1;
							do
							{
								o++;
								buf[o] = buf[o + k - m + 1];
							} while (buf[o + k - m + 1] != '\0');
							outputCell++;
						}
						k++;
					} while (buf[k] != '\0');

					i = 0;
					do
					{
						if ((buf[i] == '*') || (buf[i] == '/'))
						{
							outputCell += 3;
							o = i - 1;
							do
							{
								o++;
								buf[o] = buf[o + 2];
							} while (buf[o + 2] != '\0');
							outputCell++;
						}
						i++;
					} while (buf[i] != '\0');


					i = 0;
					outputCell++;
					do
					{
						if ((buf[i] == '+') || (buf[i] == '-'))
							outputCell++;
						i++;
					} while (buf[i] != '\0');
					outputCell++;
				}
			}
			else
				n[cellNum] = variable(a);
		}
		else
		// Если встречен оператор конца программы
		if (!strcmp(buf, "END"))
		{
			buf[0] = '\0';
			// Считывание строки
			fscanf(file1, "%s", buf);
			// Если строка не пустая, выводим ошибку и завершаем работу функции
			if (buf[0] != '\0')
			{
				printf("Ошибка в строке %d. Найдены символы после END '%s'.\n\n", strNum, buf);
				return ERROR_OTHER;
			}
			// Смещаем счетчик ячеек на 3 позиции, так как реализация IF в ассемблере занимает три ячейки
			outputCell++;
			// Ставим соответствие (cellNum) строке в Basic - (outputCell + 1) ячейке в Assembler
			n[cellNum] = outputCell;
			// Переводим флаг конца трансляции в состояние 0
			flag1 = 0;
		}
		else
		// Если найдена неизвестная команда, при этом флаг конца трансляции в состоянии 1, выводим ошибку и завершаем работу функции
		if (flag1)
		{
			printf("Ошибка в строке %d. Некорректный синтаксис, или не найден оператор окончания программы END: %s \n\n", strNum, buf);
			return ERROR_OTHER;
		}

	} while (flag1);
	// Переводим курсор считывания файла на самое начало
	fseek(file1, 0, 0);
	// Инициализация соответствий (номер ячейки) - (название хранимой в ней переменной)
	for (i = 0; i < 100; i++)
		letter[i] = '\0';
	outputCell = -1; 
	cellNum = 0; 
	flag2 = 1; 
	// Этап трансляции
	do
	{
		cellNum++;
		fscanf(file1, "%d", &strNum);
		fscanf(file1, " %s", buf);
		if (!strcmp(buf, "IF"))
		{
			fseek(file1, 1, 1);
			fscanf(file1, " %c%c", &c, &a);
			switch (a)
			{
			case '<':
				err = fscanf(file1, "%d", &b);
				// Если символ
				if (err == 0)
				{
					fscanf(file1, "%c", &a);
					outputCell++;
					fprintf(file2, "%d LOAD %d\n", outputCell, variable(c));
					outputCell++;
					fprintf(file2, "%d SUB %d\n", outputCell, variable(a));
					outputCell++;
					fscanf(file1, " GOTO %d", &b);
					if(n[b / 10] == -1)
					{					
						printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
						return ERROR_OTHER;
					}
					fprintf(file2, "%d JNEG %d\n", outputCell, n[b / 10]);
				}
				else
				{
					outputCell++;
					fprintf(file2, "%d LOAD %d\n", outputCell, variable(c));
					fprintf(file2, "%d = %d\n", variable('a' + extraVar2), b);
					outputCell++;
					fprintf(file2, "%d SUB %d\n", outputCell, variable('a' + extraVar2));
					extraVar2++;
					outputCell++;
					fscanf(file1, " GOTO %d", &b);
					if(n[b / 10] == -1)
					{					
						printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
						return ERROR_OTHER;
					}
					fprintf(file2, "%d JNEG %d\n", outputCell, n[b / 10]);
				}
				break;
			case '>':
				err = fscanf(file1, "%d", &b);
				// Если символ
				if (err == 0)
				{
					fscanf(file1, "%c", &a);
					outputCell++;
					fprintf(file2, "%d LOAD %d\n", outputCell, variable(a));
					outputCell++;
					fprintf(file2, "%d SUB %d\n", outputCell, variable(c));
					outputCell++;
					fscanf(file1, " GOTO %d", &b);
					if(n[b / 10] == -1)
					{					
						printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
						return ERROR_OTHER;
					}
					fprintf(file2, "%d JNEG %d\n", outputCell, n[b / 10]);
				}
				else
				{
					fprintf(file2, "%d = %d\n", variable('a' + extraVar2), b);
					outputCell++;
					fprintf(file2, "%d LOAD %d\n", outputCell, variable('a' + extraVar2));
					extraVar2++;
					outputCell++;
					fprintf(file2, "%d SUB %d\n", outputCell, variable(c));
					outputCell++;
					fscanf(file1, " GOTO %d", &b);
					if(n[b / 10] == -1)
					{					
						printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
						return ERROR_OTHER;
					}
					fprintf(file2, "%d JNEG %d\n", outputCell, n[b / 10]);
				}
				break;
			case '=':
				err = fscanf(file1, "%d", &b);
				if (err == 0)
				{
					fscanf(file1, "%c", &a);
					outputCell++;
					fprintf(file2, "%d LOAD %d\n", outputCell, variable(c));
					outputCell++;
					fprintf(file2, "%d SUB %d\n", outputCell, variable(a));
					outputCell++;
					fscanf(file1, " GOTO %d", &b);
					if(n[b / 10] == -1)
					{					
						printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
						return ERROR_OTHER;
					}
					fprintf(file2, "%d JZ %d\n", outputCell, n[b / 10]);
				}
				else
				{
					outputCell++;
					fprintf(file2, "%d LOAD %d\n", outputCell, variable(c));
					fprintf(file2, "%d = %d\n", variable('a' + extraVar2), b);
					outputCell++;
					fprintf(file2, "%d SUB %d\n", outputCell, variable('a' + extraVar2));
					extraVar2++;
					outputCell++;
					fscanf(file1, " GOTO %d", &b);
					if(n[b / 10] == -1)
					{					
						printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
						return ERROR_OTHER;
					}
					fprintf(file2, "%d JZ %d\n", outputCell, n[b / 10]);

				}
				break;
			}
		}
		else
		if (!strcmp(buf, "REM"))
		{
			do
			{
				fscanf(file1, "%c", &c);
			} while (c != '\n');
		}
		else
		if (!strcmp(buf, "INPUT"))
		{
			outputCell++;
			fseek(file1, 1, 1);
			fscanf(file1, "%c", &c);
			i = variable(c);
			fprintf(file2, "%d READ %d\n", outputCell, i);
		}
		else
		if (!strcmp(buf, "OUTPUT"))
		{
			outputCell++;
			fseek(file1, 1, 1);
			fscanf(file1, "%c", &c);
			i = variable(c);
			fprintf(file2, "%d WRITE %d\n", outputCell, i);
		}
		else
		if (!strcmp(buf, "GOTO"))
		{
			outputCell++;
			fseek(file1, 1, 1);
			err = fscanf(file1, "%d", &b);
			if(n[b / 10] == -1)
			{					
				printf("Ошибка в строке %d. GOTO указывает на неизвестную строку: GOTO %d \n\n", strNum, b);
				return ERROR_OTHER;
			}
			fprintf(file2, "%d JUMP %d\n", outputCell, n[b / 10]);
		}
		else
		if (!strcmp(buf, "LET"))
		{
			extraVar = -1;
			k = 0;
			fscanf(file1, " %c%c", &a, &c);
			err = fscanf(file1, "%d", &b);
			if (err == 0)
			{
				fscanf(file1, "%s", buf);
				// Если переменной присваивается не сложное выражение
				if (strlen(buf) == 3)
				{
					switch (buf[1])
					{
					case '*':
						outputCell++;
						fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[0]));
						outputCell++;
						fprintf(file2, "%d MUL %d\n", outputCell, variable(buf[2]));
						outputCell++;
						fprintf(file2, "%d STORE %d\n", outputCell, variable(a));
						break;
					case '/':
						outputCell++;
						fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[0]));
						outputCell++;
						fprintf(file2, "%d DIVIDE %d\n", outputCell, variable(buf[2]));
						outputCell++;
						fprintf(file2, "%d STORE %d\n", outputCell, variable(a));
						break;
					case '-':
						outputCell++;
						fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[0]));
						outputCell++;
						fprintf(file2, "%d SUB %d\n", outputCell, variable(buf[2]));
						outputCell++;
						fprintf(file2, "%d STORE %d\n", outputCell, variable(a));
						break;
					case '+':
						outputCell++;
						fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[0]));
						outputCell++;
						fprintf(file2, "%d ADD %d\n", outputCell, variable(buf[2]));
						outputCell++;
						fprintf(file2, "%d STORE %d\n", outputCell, variable(a));
						break;
					default:
						printf("Ошибка в строке %d. Некорректное указание параметров в IF '%c' \n\n", strNum, c);
						return ERROR_OTHER;
					}
				}
				// Если выражение содержит скобки и много операций, необходимо пройтись по всем скобкам
				else
				{
					do
					{
						if (buf[k] == ')')
						{
							i = k;
							do
							i--;
							while (buf[i] != '(');

							i = m = i + 1;

							do
							{
								if (buf[i] == '*')
								{
									outputCell++;
									fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[i - 1]));
									outputCell++;
									fprintf(file2, "%d MUL %d\n", outputCell, variable(buf[i + 1]));
									extraVar++;
									outputCell++;
									fprintf(file2, "%d STORE %d\n", outputCell, variable('a' + extraVar));
									buf[i - 1] = 'a' + extraVar;
									o = i - 1;
									do
									{
										o++;
										buf[o] = buf[o + 2];
									} while (buf[o + 2] != '\0');
								}
								if (buf[i] == '/')
								{
									outputCell++;
									fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[i - 1]));
									outputCell++;
									fprintf(file2, "%d DIVIDE %d\n", outputCell, variable(buf[i + 1]));
									extraVar++;
									outputCell++;
									fprintf(file2, "%d STORE %d\n", outputCell, variable('a' + extraVar));
									buf[i - 1] = 'a' + extraVar;
									o = i - 1;
									do
									{
										o++;
										buf[o] = buf[o + 2];
									} while (buf[o + 2] != '\0');
								}
								i++;
							} while (buf[i] != ')');

							i = m;
							outputCell++;
							fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[i]));
							do
							{
								if (buf[i] == '+')
								{
									outputCell++;
									fprintf(file2, "%d ADD %d\n", outputCell, variable(buf[i + 1]));
								}
								if (buf[i] == '-')
								{
									outputCell++;
									fprintf(file2, "%d SUB %d\n", outputCell, variable(buf[i + 1]));
								}
								i++;
							} while (buf[i] != ')');

							extraVar++;
							outputCell++;
							fprintf(file2, "%d STORE %d\n", outputCell, variable('a' + extraVar));
							buf[m - 1] = 'a' + extraVar;

							o = m - 1;
							do
							{
								o++;
								buf[o] = buf[o + k - m + 1];
							} while (buf[o + k - m + 1] != '\0');
						}
						k++;
					} while (buf[k] != '\0');

					i = 0;
					do
					{
						if (buf[i] == '*')
						{
							outputCell++;
							fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[i - 1]));
							outputCell++;
							fprintf(file2, "%d MUL %d\n", outputCell, variable(buf[i + 1]));
							extraVar++;
							outputCell++;
							fprintf(file2, "%d STORE %d\n", outputCell, variable('a' + extraVar));
							buf[i - 1] = 'a' + extraVar;
							o = i - 1;
							do
							{
								o++;
								buf[o] = buf[o + 2];
							} while (buf[o + 2] != '\0');

						}
						if (buf[i] == '/')
						{
							outputCell++;
							fprintf(file2, "%d LOAD %d\n", outputCell, variable(buf[i - 1]));
							outputCell++;
							fprintf(file2, "%d DIVIDE %d\n", outputCell, variable(buf[i + 1]));
							extraVar++;
							outputCell++;
							fprintf(file2, "%d STORE %d\n", outputCell, variable('a' + extraVar));
							buf[i - 1] = 'a' + extraVar;
							o = i - 1;
							do
							{
								o++;
								buf[o] = buf[o + 2];
							} while (buf[o + 2] != '\0');
						}
						i++;
					} while (buf[i] != '\0');

					i = 0;
					do
					{
						if (buf[i] == '+')
						{
							outputCell++;
							fprintf(file2, "%d ADD %d\n", outputCell, variable(buf[i + 1]));
						}
						if (buf[i] == '-')
						{
							outputCell++;
							fprintf(file2, "%d SUB %d\n", outputCell, variable(buf[i + 1]));
						}
						i++;
					} while (buf[i] != '\0');
					outputCell++;
					fprintf(file2, "%d STORE %d\n", outputCell, variable(a));
				}
			}
			else
			{
				n[cellNum] = variable(a);
				fprintf(file2, "%d = %d\n", variable(a), b);
			}
		}
		else
		if (!strcmp(buf, "END"))
		{
			fprintf(file2, "%d HALT", outputCell + 1);
			flag2 = 0;
		}
	} while (flag2);
	fclose(file1);
	fclose(file2);
	return SUCCESS;
}

int main(int argc, char **argv)
{
	// Если количество необходимых аргументов, переданных программе, не равно 3 (первый аргумент всегда является названием функции, так что, 
	// фактически, при запуске необходимо ввести 2 аргумента, а именно - "(название входного файла) (название выходного файла)"), то выводим справку.
	if (argc != 3) 
	{ 
		printf("\nТранслятор Simple BASIC to Simple ASSEMBLER\n  использование: ./BAS INPUT_FILE.basic OUTPUT_FILE.sa"); 
		return 0; 
	}
	// Запускаем главную функцию трансляции, в которую передаем название входного файла (argv[1]) и название выходного файла (argv[2]).
	// Функция возвращает код ошибки, в случае если при трансляции что то пошло не так.
	int err = basic(argv[1], argv[2]);
	switch (err)
	{
		case SUCCESS: 					printf("Файл транслирован успешно\n"); break;
		case ERROR_OPENING_INPUT_FILE: 	printf("Ошибка при открытии исходного файла\n"); break;
		case ERROR_OPENING_OUTPUT_FILE: printf("Ошибка при открытии выходного файла\n"); break;
	}
	return 0;
}


