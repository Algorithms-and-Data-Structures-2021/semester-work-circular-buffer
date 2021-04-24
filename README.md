Circularr Buffer - Кольцевой Буфер на базе Array Deque
[![CMake](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-circular-buffer/actions/workflows/cmake.yml/badge.svg?branch=main)](https://github.com/Algorithms-and-Data-Structures-2021/semester-work-circular-buffer/actions/workflows/cmake.yml)


## Описание

- Реализация кольцевого буфера. 
- Кольцевой буфер(circular buffer) представляет собой замкнутую двухстороннюю очередь в виде массива (array deque), которая при заполнении начинает перезаписывать старые данные.
- Применение:
  - буферизация потоков данных
  - программирование микроконтроллеров
  - организации различных очередей сообщений и буферов приёма-передачи различных коммуникационных интерфейсов

- Операции:
  - Добавление в начало - `Т = О(1)`
  - Добавление в конец - `Т = О(1)`
  - Взятие с конца с удалением - `Т = О(1)`
  - Взятие с начала с удалением - `Т = О(1)`
  - Взятие с конца без удаления - `Т = О(1)`
  - Взятие с начала без удаления - `Т = О(1)`
  - Увеличение вместимости - `Т = О(size)`
  - Очистка - `Т = О(1)`
  - Проверка на заполненность - `Т = О(1)`
  - Проверка на пустоту - `Т = О(1)`

## Команда "TESTING"

| Фамилия Имя     | Вклад (%) | Прозвище              |
| :---            |   ---:    |  ---:                 |
| Казымов Орхан   | 100       |  _босс_качалки_       |

**Девиз команды**
> _Волк не тот, кто не волк, а тот, кто волк_

## Структура проекта

_Описание основных частей семестрового проекта._

Проект состоит из следующих частей:

- [`src`](src)/[`include`](include) - реализация структуры данных (исходный код и заголовочные файлы) - вся реализация СД находится в заголовочных файлах из-за технических нюансов;
- [`benchmark`](benchmark) - контрольные тесты производительности структуры данных (операции добавления, удаления, и пр.);
- [`examples`](examples) - примеры работы со структурой данных;
- [`dataset`](dataset) - наборы данных для запуска контрольных тестов и их генерация;

## Требования (Prerequisites)

1. С++ компилятор c поддержкой стандарта C++17 (например, _GNU GCC 8.1.x_ и выше).
2. Система автоматизации сборки _CMake_ (версия _3.12.x_ и выше).
3. Интерпретатор _Python_ (версия _3.7.x_ и выше).
4. Библиотека _faker_ для _Python_ `pip install Faker`
5. Рекомендуемый объем оперативной памяти - не менее 4 ГБ.
6. Свободное дисковое пространство объемом ~ 3 ГБ (набор данных для контрольных тестов).

## Сборка и запуск

_Инструкция по сборке проекта, генерации тестовых данных, запуска контрольных тестов и примеров работы._

### Пример (Windows)

#### Сборка проекта

Склонируйте проект к себе на устройство через [Git for Windows](https://gitforwindows.org/) (либо используйте
возможности IDE):

```shell
git clone --recurse-submodules https://github.com/Algorithms-and-Data-Structures-2021/semester-work-circular-buffer.git
```

Для ручной сборки проекта в терминале введите:

```shell
# переход в папку с проектом
cd C:\Users\username\asd-projects\semester-work-circular-buffer

# создание папки для файлов сборки (чтобы не засорять папку с проектом) 
mkdir -p build && cd build 

# сборка проекта
cmake .. -DCMAKE_BUILD_TYPE=RelWithDebInfo && cmake --config RelWithDebInfo --build . 
```

#### Генерация тестовых данных

Для хранения тестовых данных используется формат CSV

Генерация тестового набора данных в
формате [comma-seperated values (CSV)](https://en.wikipedia.org/wiki/Comma-separated_values):

```bash
# переход в папку генерации набора данных
cd dataset

# запуск Python-скрипта
python generate_csv_dataset.py <output> --samples 1000 --data_type int
```

- `<output>` - выходной файл;
- `--samples` - количество генерируемых элементов;
- `--data_type` - тип генерируемых данных, доступно 2 типа: int и str.

Тестовые данные представлены в CSV формате (см.
[`dataset/data/dataset-example.csv`](dataset/data/dataset-example.csv)):

```csv
id, full_name
0, "Ramil Safin"
1, "Bulat Abbyasov"
...
```

**Примечание**. Для удобства запуска контрольных тестов рекомендуется организовывать данные в директориях, например:

```shell
dataset/data/
  add/
    01/
      100.csv
      ...
      5000000.csv
    02/ ...
    03/ ...
    ...
    10/ ...
  search/
    01/
      100.csv
      ...
      5000000.csv
    ...
    10/ ...
  ...
```

По названию директории `/dataset/data/add` можно понять, что здесь хранятся наборы данных для контрольных тестов по
**добавлению** элементов в структуру данных. Названия файлов `100.csv`. `5000000.csv` и т.д. хранят информацию о размере набора данных (т.е. количество элементов). 

#### Контрольные тесты (benchmarks)
 Контрольные тесты замеряют время работы функций **добавления и удаления с начала и с конца** на различных значениях **вместимости буфера** - 1) в половину от кол-ва входных данных и 2) на 5 больше чем кол-во входных данных. 

Для запуска контрольных тестов необходимо предварительно сгенерировать или скачать готовый набор тестовых данных.

генерация данных:
```bash

# просто скопируйте этот код и вставьте в bash-консоль, например, в консоль clion
# важно находиться в директории проекта т.е. в semester-work-circular-buffer

cd dataset/; rm data -r; mkdir data; cd data/; mkdir Enqueue; cd Enqueue/; mkdir int; cd int/; for i in {01..10}; do mkdir $i; done; cd ../../../; for ((samples = 100; samples < 1000001; samples *= 10)); do for path_ in data/Enqueue/int/{01..10}/; do python generate_csv_dataset.py "$path_$samples.csv" --samples $samples; done; done; for ((samples = 500; samples < 5000001; samples *= 10)); do for path_ in data/Enqueue/int/{01..10}/; do python generate_csv_dataset.py "$path_$samples.csv" --samples $samples; done; done; cd ../;

# ОЧЕНЬ ВАЖНОЕ ЗАМЕЧАНИЕ:
# В вышенаписанном коде есть знак доллара `$`. По неизвестным мне причинам, если смотреть на файл README.md в Clion, 
# знак доллара может отображатся с бэк-слешом в начале `\$` проследите чтобы при копировании кода перед знаком доллара не было бэк-слеша

```

**Примечание**. Во избежание "захламления" репозитория большим объёмом данных рекомендуется указать ссылку на архив с
набором данных, который при необходимости можно скачать по ссылке. Наборы данных должны находиться в папке семестровой
работы на [Google Drive](https://drive.google.com/drive/folders/1h1ojX6_vL8X1GczpKUUJCW6cxpVAbDCz?usp=sharing).

##### Список контрольных тестов

| Название                  | Описание                                | Метрики         |
| :---                      | ---                                     | :---            |
| `EnqueueBack`             | Добавление элементов в конец            | _время_         |
| `EnqueueFront`            | Добавление элементов в начало           | _время_         |
| `DequeueBack`             | Удаление элемента с конца               | _время_         |
| `DequeueFront`            | Удаление элемента с начала              | _время_         |


## Источники

_Список использованных при реализации структуры данных источников._

- Видео:
  - https://www.youtube.com/watch?v=WJres9mgiAk&ab_channel=Jenny%27slecturesCS%2FITNET%26JRF
  - https://www.youtube.com/watch?v=GbBrp6K7IvM&t=17s&ab_channel=eapbg
  - https://www.youtube.com/watch?v=39HHWATPcwY&t=78s&ab_channel=JeffZhang
  - https://www.youtube.com/watch?v=ZkL7YK0AnNU&t=554s&ab_channel=JeffZhang
- Статьи:
  - https://www.wikiwand.com/en/Circular_buffer
  - https://embeddedartistry.com/blog/2017/05/17/creating-a-circular-buffer-in-c-and-c/#:~:text=Circular%20buffers%20(also%20known%20as,added%2C%20the%20head%20pointer%20advances.
